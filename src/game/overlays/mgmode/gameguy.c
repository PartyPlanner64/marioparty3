#include "common.h"
#include "mgmode.h"
#include "gcc/memory.h"
#include "gcc/string.h"
#include "game/hmfmath.h"

extern u8 mgmode_gambleTitleStr[256];
extern GAMEMES mgmode_gambleTitleMes;
extern u8 *mgmode_spotBufTbl[3];
extern s16 mgmode_spotAnim;
extern s16 mgmode_spotGrp;
extern u8 Hu3DBufNo;
extern MgmodeEspriteDef mgmode_gambleCoinSprDefTbl[];
extern MgmodeEspriteDef mgmode_gambleBoardSprDefTbl[];
extern s16 mgmode_mdlTbl[];
extern s16 mgmode_winId;
extern s16 mgmode_padNo;
extern s16 mgModeCoinBase;
extern s16 mgmode_motTbl10;
extern s16 mgmode_motTbl11;
extern s16 mgmode_mdlTbl8[];
extern s16 mgmode_motTbl9;
extern s16 mgmode_motTbl8;
extern s16 mgmode_motTbl14;
extern s16 mgmode_motTbl12;
extern s16 mgmode_motTbl4;
extern s16 mgmode_motTbl6;
extern s16 mgmode_motTbl7;
extern s16 mgmode_gambleConfettiNo;
extern s16 mgModeMgList[8];
extern s16 mgModeMgListIdx;
extern s16 mgModeMgNo;
extern u8 mgmode_exitF;
extern s16 mgmode_exitMode;
extern s16 mgmode_exitEvtNo;
extern s16 mgmode_motTbl13;
extern s16 mgmode_playerNo;
extern s16 mgmode_exitOvlNo;
extern ModeCameraPreset *mgmode_cameraPresetTbl;
extern f32 mgmode_cameraFar;
extern s16 mgmode_gamblePlayerChr;
extern s16 mgmode_gamblePlayerAnim;
extern MgmodeModelEntry mgmode_gambleMdlDefTbl[];
extern HuMtx4F mgmode_gambleDoorMtx;
extern s16 mgmode_zClearF;
extern u8 mgmode_cameraPresetNo;
extern s16 mgmode_motTbl5;

void mgmode_GambleBetNumSet(s16 value);
void mgmode_GambleCoinNumSet(s16 value);
void mgmode_SprListNumSet(MgmodeEsprite *sprites, s16 base, s16 value, s16 digits);
MgmodeEsprite *mgmode_SprListCreate(MgmodeEspriteDef *defs);
void mgmode_SprListKill(MgmodeEsprite *arg0);
void mgmode_SprListPosSet(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3);
void mgmode_SprListDispOn(MgmodeEsprite *arg0, s16 index);
void mgmode_SprListDispOff(MgmodeEsprite *arg0, s16 index);
void mgmode_SprListScaleSet(MgmodeEsprite *arg0, s16 index, f32 x, f32 y);
void mgmode_SprListPatNoSet(MgmodeEsprite *arg0, s16 index, s16 arg2);
void mgmode_SprListPriSet(MgmodeEsprite *arg0, s16 index, u16 arg2);
void mgmode_GambleTitleKill(void);
void mgmode_SpotClear(void);
void mgmode_GambleTitleTPLvlSet(s16 arg0);
void mgmode_MgPicKill(void);
void mgmode_MotionEndWait(s16 index);
void mgmode_GambleCalcDispSet(s16 arg0, s16 arg1, s16 arg2);
void mgmode_GambleBetDispOn(s16 x, s16 y, s16 value);
void mgmode_MdlPosCopy(s16 dstModel, s16 srcModel);
void mgmode_GambleMgListBuild(void);
void mgmode_GambleBoardCreate(s32 animate);
s16 mgmode_GambleMgRouletteExec(void);
s16 mgmode_GambleBetChoice(void);
void mgmode_GambleCoinCreate(s16 value);
s16 mgmode_MgPicCreate(void);
void mgmode_MgPicLoad(s16 arg0);
void mgmode_GambleTitleSet(s32 mesId, s16 x, s16 y);
void mgmode_SpotUpdate(f32 arg0, f32 arg1);
void mgmode_ConfettiOn(s16 index);
void mgmode_ConfettiOff(s16 index);
void mgmode_GambleBetExec(void);
void mgmode_GambleExitExec(void);
void mgmode_GamblePlayerEnterExec(void);
void mgmode_GamblePlayerExitExec(void);
void mgmode_GambleBoardKill(void);
void mgmode_GambleBetDispOff(void);
void mgmode_GambleCoinKill(void);
void mgmode_CameraPresetSet(s16 arg0);
void mgmode_GambleBoardClear(void);
void mgmode_GambleMgPicClose(void);
void mgmode_GamblePayoutExec(void);
void mgmode_GambleRewardExec(void);
void mgmode_GambleSpotProc(void);
void mgmode_RecordSave(void);
s32 mgmode_GambleQuitCheck(void);
void mgmode_GambleTitleInit(void);
void mgmode_SpotInit(void);
void mgmode_MdlListCreate(MgmodeModelEntry *entries);
s16 mgmode_ConfettiCreate(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void mgmode_CursorMoveTimeSet(s16 arg0);
void mgmode_CursorSelMove(s16 arg0);
void mgmode_GambleEnterExec(void);
s32 mgmode_GambleResultExec(void);

MgmodeEsprite *mgmode_gambleBoardSprTbl = (MgmodeEsprite *)-1;
s16 mgmode_gambleMgPicSpr = -1;
s32 mgmode_gambleSpotWaitF = 0;
s32 mgmode_gambleClearF = 0;
ModeCameraPreset mgmode_gambleCameraPresetTbl[7] = {
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 87.0f, -395.0f }, 1490.0f, 40.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 87.0f, -395.0f }, 960.0f, 40.0f },
    { { 10.0f, 88.0f, 0.0f }, { -395.6f, 126.8f, 0.9f }, 440.0f, 40.0f },
    { { 6.0f, 180.0f, 0.0f }, { 1.6f, 98.0f, 717.7f }, 360.0f, 40.0f },
    { { 0.0f, 184.0f, 0.0f }, { 11.7f, 90.9f, 978.7f }, 120.0f, 40.0f },
    { { 8.0f, 356.0f, 0.0f }, { 38.7f, 126.8f, -118.8f }, 610.0f, 40.0f },
    { { 0.0f, 0.0f, 0.0f }, { -41.0f, 202.8f, -80.4f }, 320.0f, 40.0f }
};
MgmodeSpaceCoord mgmode_gambleCursorPosTbl[3] = {
    { 97, 142 }, { 160, 120 }, { -1, -1 }
};
s16 mgmode_gambleMgTbl[4] = {
    0x42, 0x43, 0x44, 0x45
};
u8 mgmode_gambleMgMaxTbl[4] = {
    2, 1, 3, 2
};
u8 mgmode_gambleMgDefaultTbl[8] = {
    2, 0, 3, 2, 3, 1, 2, 0
};
MgmodeEsprite *mgmode_gambleCoinSprTbl = (MgmodeEsprite *)-1;

void mgmode_GambleRoomProc(void) {
    s16 size[2];
    HmfMotionNode *node;
    s16 choice;
    s16 changed;
    s16 i;

    HuWinMesMaxSizeBetGet(size, 0x5800, 0x5813);
    mgmode_winId = HuWinExCreate(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
    HuWinActivePlayerSet(mgmode_winId, 1 << mgmode_padNo);
    HuWinPriSet(mgmode_winId, 10);
    mgmode_GambleTitleInit();
    mgmode_SpotInit();
    mgmode_cameraPresetTbl = mgmode_gambleCameraPresetTbl;
    mgmode_cameraFar = 2500.0f;
    mgmode_gamblePlayerChr = GwPlayer[mgmode_playerNo].chr;
    mgmode_gambleMdlDefTbl[8].unk_00 = CharMotionDataNumGet(mgmode_gamblePlayerChr, 0xA1);
    mgmode_gambleMdlDefTbl[9].unk_00 = CharMotionDataNumGet(mgmode_gamblePlayerChr, 0x2);
    mgmode_gambleMdlDefTbl[10].unk_00 = CharMotionDataNumGet(mgmode_gamblePlayerChr, 0x33);
    mgmode_gambleMdlDefTbl[11].unk_00 = CharMotionDataNumGet(mgmode_gamblePlayerChr, 0x3A);
    mgmode_gambleMdlDefTbl[12].unk_00 = CharMotionDataNumGet(mgmode_gamblePlayerChr, 0x2F);
    mgmode_gambleMdlDefTbl[13].unk_00 = CharMotionDataNumGet(mgmode_gamblePlayerChr, 0x37);
    mgmode_gambleMdlDefTbl[14].unk_00 = CharMotionDataNumGet(mgmode_gamblePlayerChr, 0x9B);
    mgmode_MdlListCreate(mgmode_gambleMdlDefTbl);
    Hu3DModelCameraSet(mgmode_mdlTbl[4], HU3D_CAM1);
    Hu3DModelCameraSet(mgmode_mdlTbl[8], HU3D_CAM1);
    mgmode_gamblePlayerAnim = CharAnimCreate(mgmode_mdlTbl[8], 1, mgmode_gamblePlayerChr,
                                           CharMotionDataNumGetTbl(mgmode_gamblePlayerChr, 1, 0));
    Hu3DModelDynamicFree(mgmode_mdlTbl[8]);
    Hu3DModelAttrSet(mgmode_mdlTbl[18], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
    Hu3DModelRemakeStatic(mgmode_mdlTbl[18]);
    Hu3DModelDynamicFree(mgmode_mdlTbl[18]);
    Hu3DModelPosSet(mgmode_mdlTbl[18], -208.0f, 0.0f, -332.0f);
    Hu3DModelCameraSet(mgmode_mdlTbl[15], HU3D_CAM1);
    mgmode_gambleConfettiNo = mgmode_ConfettiCreate(2.0f, 400.0f, -332.0f, 50.0f);
    node = Hu3DModelObjPtrGet(mgmode_mdlTbl[0], "door");
    mtxCopy(mgmode_gambleDoorMtx, node->unk58);
    if (omovlevtno == 3) {
        Hu3DMotionSet(mgmode_mdlTbl[4], mgmode_motTbl5);
        Hu3DMotionAttrSet(mgmode_mdlTbl[4], 2, 2);
        mgmode_CameraPresetSet(0);
        WipeCreateIn(WIPE_TYPE_PREV, 0);
        node = Hu3DModelObjPtrGet(mgmode_mdlTbl[0], "door");
        RepeatVibrator(mgmode_padNo, 5, 0, 5);
        HuAudFXPlay(0x2EB);
        for (i = 0; i < 19; i++) {
            HuPrcVSleep();
            mtxCopy(node->unk58, mgmode_gambleDoorMtx);
            mtxRotCat(node->unk58, 0.0f, i * 5, 0.0f);
        }
        mgmode_CameraPresetMove(1, 10, 1, (void (*)(s16 *))-1);
        HuPrcSleep(5);
        mtxCopy(node->unk58, mgmode_gambleDoorMtx);
        mgmode_CameraPresetMove(2, 20, 1, (void (*)(s16 *))-1);
        HuAudFXPlay(0x2A1);
    } else {
        mgmode_zClearF = 1;
        if (mgmode_GambleResultExec()) {
            mgmode_GambleBetExec();
            mgmode_GamblePlayerExitExec();
        }
        mgmode_GambleExitExec();
        if (mgmode_gambleClearF != 0) {
            HuAudSeqPlay(0x4D);
        }
        Hu3DMotionSet(mgmode_mdlTbl[4], mgmode_motTbl5);
        Hu3DMotionAttrSet(mgmode_mdlTbl[4], 2, 2);
        mgmode_zClearF = 0;
    }
    mgmode_CursorPosTblSet(mgmode_gambleCursorPosTbl);
    mgmode_CursorSelSet(0);
    mgmode_CursorDispSet(1);
    HuWinMesSet(mgmode_winId, 0x5800, -1, -1);
    HuWinExAnimIn(mgmode_winId);
    while (TRUE) {
        HuPrcVSleep();
        mgmode_CursorMoveTimeSet(5);
        switch (mgmode_cameraPresetNo) {
            case 2:
                changed = FALSE;
                if (HuPadBtnDown[mgmode_padNo] & A_BUTTON) {
                    HuAudFXPlay(2);
                    Hu3DMotionShiftSet(mgmode_mdlTbl[4], mgmode_motTbl4, 0, 8, 2);
                    mgmode_CursorDispSet(0);
                    while (TRUE) {
                        HuWinMesSet(mgmode_winId, 0x5803, -1, -1);
                        while (HuWinStatGet(mgmode_winId) != 0) {
                            HuPrcVSleep();
                        }
                        HuWinMesSet(mgmode_winId, 0x5804, -1, -1);
                        while (HuWinStatGet(mgmode_winId) != 0) {
                            HuPrcVSleep();
                        }
                        if ((s16)HuWinChoiceGet(mgmode_winId, 0, 0) != 0) {
                            choice = -1;
                            break;
                        }
                        HuWinMesSet(mgmode_winId, 0x5805, -1, -1);
                        while (HuWinStatGet(mgmode_winId) != 0) {
                            HuPrcVSleep();
                        }
                        choice = HuWinChoiceGet(mgmode_winId, 0, 0);
                        if (choice == -1) {
                            continue;
                        }
                        if (choice == 0) {
                            HuWinMesSet(mgmode_winId, 0x5806, -1, -1);
                            while (HuWinStatGet(mgmode_winId) != 0) {
                                HuPrcVSleep();
                            }
                        }
                        break;
                    }
                    if (choice != -1) {
                        HuWinMesSet(mgmode_winId, 0x5807, -1, -1);
                        while (HuWinStatGet(mgmode_winId) != 0) {
                            HuPrcVSleep();
                        }
                        mgmode_GambleEnterExec();
                    }
                    mgmode_CursorDispSet(1);
                    HuWinMesSet(mgmode_winId, 0x5800, -1, -1);
                    HuWinExAnimIn(mgmode_winId);
                } else if ((ContBtnDown[mgmode_padNo] & L_JPAD) ||
                           (HuPadBtnDown[mgmode_padNo] & B_BUTTON)) {
                    HuAudFXPlay(1);
                    HuWinExAnimOut(mgmode_winId, 0);
                    mgmode_CursorMoveTimeSet(20);
                    mgmode_CursorSelMove(1);
                    mgmode_CameraPresetMove(3, 20, 1, (void (*)(s16 *))-1);
                    changed = TRUE;
                } else if (ContBtnDown[mgmode_padNo] & R_JPAD) {
                    HuAudFXPlay(1);
                    HuWinExAnimOut(mgmode_winId, 0);
                    mgmode_CursorMoveTimeSet(30);
                    mgmode_CursorSelMove(1);
                    mgmode_CameraPresetMove(5, 15, 0, (void (*)(s16 *))-1);
                    mgmode_CameraPresetMove(3, 15, 1, (void (*)(s16 *))-1);
                    changed = TRUE;
                }
                if (changed) {
                    HuWinMesSet(mgmode_winId, 0x5801, -1, -1);
                    HuWinExAnimIn(mgmode_winId);
                }
                break;
            case 3:
                changed = FALSE;
                if (HuPadBtnDown[mgmode_padNo] & A_BUTTON) {
                    HuAudFXPlay(2);
                    HuWinMesSet(mgmode_winId, 0x5802, -1, -1);
                    while (HuWinStatGet(mgmode_winId) != 0) {
                        HuPrcVSleep();
                    }
                    if ((s16)HuWinChoiceGet(mgmode_winId, 0, 0) != 0) {
                        HuWinMesSet(mgmode_winId, 0x5801, -1, -1);
                        while (HuWinStatGet(mgmode_winId) != 0) {
                            HuPrcVSleep();
                        }
                        break;
                    }
                    mgmode_CursorDispSet(0);
                    HuWinExAnimOut(mgmode_winId, 0);
                    HuPrcSleep(10);
                    node = Hu3DModelObjPtrGet(mgmode_mdlTbl[0], "door");
                    RepeatVibrator(mgmode_padNo, 5, 0, 5);
                    HuAudFXPlay(0x2EB);
                    for (i = 0; i < 19; i++) {
                        HuPrcVSleep();
                        mtxCopy(node->unk58, mgmode_gambleDoorMtx);
                        mtxRotCat(node->unk58, 0.0f, i * 5, 0.0f);
                    }
                    mgmode_CameraPresetMove(4, 20, 1, (void (*)(s16 *))-1);
                    mgmode_exitF = 1;
                    mgmode_exitMode = 0x80;
                    HuAudSeqFadeOut(60);
                    while (TRUE) {
                        HuPrcVSleep();
                    }
                } else if (ContBtnDown[mgmode_padNo] & R_JPAD) {
                    HuAudFXPlay(1);
                    HuWinExAnimOut(mgmode_winId, 0);
                    mgmode_CursorMoveTimeSet(20);
                    mgmode_CursorSelMove(0);
                    mgmode_CameraPresetMove(2, 20, 1, (void (*)(s16 *))-1);
                    changed = TRUE;
                } else if (ContBtnDown[mgmode_padNo] & L_JPAD) {
                    HuAudFXPlay(1);
                    HuWinExAnimOut(mgmode_winId, 0);
                    mgmode_CursorMoveTimeSet(30);
                    mgmode_CursorSelMove(0);
                    mgmode_CameraPresetMove(5, 15, 0, (void (*)(s16 *))-1);
                    mgmode_CameraPresetMove(2, 15, 1, (void (*)(s16 *))-1);
                    changed = TRUE;
                }
                if (changed) {
                    HuWinMesSet(mgmode_winId, 0x5800, -1, -1);
                    HuWinExAnimIn(mgmode_winId);
                }
                break;
        }
        if (Hu3DData[mgmode_mdlTbl[4]].motId != mgmode_motTbl5 &&
            Hu3DData[mgmode_mdlTbl[4]].motIdShift != mgmode_motTbl5) {
            Hu3DMotionShiftSet(mgmode_mdlTbl[4], mgmode_motTbl5, 0, 8, 2);
        }
    }
}

void mgmode_GambleEnterExec(void) {
    f32 radius;
    f32 t;
    s16 i;

    HuWinExAnimOut(mgmode_winId, 0);
    Hu3DModelAttrSet(mgmode_mdlTbl[18], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelScaleSet(mgmode_mdlTbl[18], 1.0f, 0.0f, 1.0f);
    mgmode_CameraPresetMove(6, 20, 1, (void (*)(s16 *))-1);
    radius = 144.0f;
    Hu3DModelPosSet(mgmode_mdlTbl[4], -352.0f, 637.5f, -332.0f);
    Hu3DMotionShiftSet(mgmode_mdlTbl[4], mgmode_motTbl6, 0, 10, 0);
    for (i = 0; i < 11; i++) {
        if (i < 6) {
            Hu3DModelScaleSet(mgmode_mdlTbl[18], 1.0f, sindf(i / 5.0f * 90.0f), 1.0f);
        }
        t = i / 10.0f * 90.0f;
        Hu3DData[mgmode_mdlTbl[4]].pos.x = sindf(t) * radius + -352.0;
        Hu3DData[mgmode_mdlTbl[4]].pos.y = cosdf(t) * 200.0f + 63.75f;
        Hu3DData[mgmode_mdlTbl[4]].rot.y = cosdf(t) * 75.0f + 15.0f;
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(mgmode_mdlTbl[4], mgmode_motTbl4, 0, 8, 2);
    HuAudFXPlay(0x51A);
    mgmode_GamblePlayerEnterExec();
    mgmode_GambleBetExec();
    mgmode_GamblePlayerExitExec();
    mgmode_GambleExitExec();
}

void mgmode_GambleBetExec(void) {
    s16 i;

    mgModeCoinBase = 10;
    mgModeMgListIdx = 0;
    mgmode_GambleMgListBuild();
    mgmode_GambleCoinCreate(mgModeCoinBase);
    HuPrcVSleep();
    mgmode_GambleBoardCreate(1);
    HuWinMesSet(mgmode_winId, 0x5808, -1, -1);
    HuWinExAnimIn(mgmode_winId);
    mgModeMgNo = mgmode_GambleMgRouletteExec();
    HuWinInsertMesSet(mgmode_winId, mgModeMgNo + 0x4700, 0);
    HuWinMesSet(mgmode_winId, 0x580A, -1, -1);
    while (HuWinStatGet(mgmode_winId) != 0) {
        HuPrcVSleep();
    }
    HuWinMesSet(mgmode_winId, 0x580B, -1, -1);
    mgModeCoinRate = -1;
    do {
        mgModeCoinRate = mgmode_GambleBetChoice();
        if (mgModeCoinRate < 0) {
            HuWinMesSet(mgmode_winId, 0x5813, -1, -1);
            while (HuWinStatGet(mgmode_winId) != 0) {
                HuPrcVSleep();
            }
            if ((s16)HuWinChoiceGet(mgmode_winId, 0, 0) == 0) {
                return;
            }
            HuWinMesSet(mgmode_winId, 0x580B, -1, -1);
        }
    } while (mgModeCoinRate < 0);
    mgModeCoinBase -= mgModeCoinRate;
    GwPlayer[0].gameCoin = mgModeCoinRate;
    GwPlayer[0].group = 0;
    for (i = 1; i < 4; i++) {
        GwPlayer[i].group = 1;
    }
    _SetFlag(0xD);
    GwSystem.minigame_index = (u8)mgModeMgNo + 1;
    omOvlHisChg(0, 0x69, 5, 0x84);
    mgmode_exitF = 1;
    mgmode_exitOvlNo = 0x70;
    mgmode_exitEvtNo = 0;
    mgmode_exitMode = 2;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void mgmode_GambleExitExec(void) {
    f32 radius;
    f32 t;
    s16 i;

    HuWinExAnimOut(mgmode_winId, 0);
    mgmode_GambleTitleKill();
    mgmode_GambleBetDispOff();
    mgmode_MgPicKill();
    mgmode_gambleMgPicSpr = -1;
    mgmode_GambleBoardKill();
    mgmode_GambleCoinKill();
    HuAudFXPlay(0x519);
    Hu3DMotionShiftSet(mgmode_mdlTbl[4], mgmode_motTbl7, 0, 8, 0);
    radius = 144.0f;
    for (i = 0; i < 9; i++) {
        if (i < 6) {
            Hu3DModelScaleSet(mgmode_mdlTbl[18], 1.0f, cosdf(i / 5.0f * 90.0f), 1.0f);
        }
        t = i / 8.0f * 90.0f;
        Hu3DData[mgmode_mdlTbl[4]].pos.x = cosdf(t) * radius + -352.0;
        Hu3DData[mgmode_mdlTbl[4]].pos.y = sindf(t) * 100.0f + 63.75f;
        Hu3DData[mgmode_mdlTbl[4]].rot.y = -sindf(t) * 100.0f + 15.0f;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(mgmode_mdlTbl[4], -436.0f, 0.0f, 92.0f);
    Hu3DData[mgmode_mdlTbl[4]].rot.y = 100.0f;
    Hu3DMotionShiftSet(mgmode_mdlTbl[4], mgmode_motTbl4, 0, 8, 0);
    mgmode_CameraPresetMove(2, 20, 1, (void (*)(s16 *))-1);
    Hu3DModelAttrSet(mgmode_mdlTbl[18], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void mgmode_GambleMgListBuild(void) {
    u8 counts[4] = { 0, 0, 0, 0 };
    s16 attempt;
    s16 i;
    s16 type;

    for (attempt = 0; attempt < 100; attempt++) {
        for (i = 0; i < 4; i++) {
            counts[i] = 0;
        }
        type = rand8() & 3;
        mgModeMgList[0] = type;
        counts[type]++;
        for (i = 1; i < 8; i++) {
            do {
                type = rand8() & 3;
            } while (mgModeMgList[i - 1] == type);
            counts[type]++;
            if (mgmode_gambleMgMaxTbl[type] < counts[type]) {
                break;
            }
            mgModeMgList[i] = type;
        }
        if (i == 8 && mgModeMgList[0] != mgModeMgList[7]) {
            break;
        }
    }
    if (attempt == 100) {
        for (i = 0; i < 8; i++) {
            mgModeMgList[i] = mgmode_gambleMgDefaultTbl[i];
        }
    }
    for (i = 0; i < 8; i++) {
        mgModeMgList[i] = mgmode_gambleMgTbl[mgModeMgList[i]];
    }
}

s32 mgmode_GambleResultExec(void) {
    s16 save = FALSE;
    s16 choice;
    s16 i;

    mgModeMgListIdx++;
    mgModeMgListIdx %= 8;
    mgmode_CameraPresetSet(6);
    mgmode_GambleBoardCreate(0);
    mgmode_gambleMgPicSpr = mgmode_MgPicCreate();
    espPriSet(mgmode_gambleMgPicSpr, 15);
    espAttrSet(mgmode_gambleMgPicSpr, 0x5008);
    espPosSet(mgmode_gambleMgPicSpr, 184, 132);
    mgmode_MgPicLoad(mgDataTbl[mgModeMgNo].flags & 0x7FF);
    mgmode_GambleTitleSet(mgModeMgNo + 0x4700, 184, 62);
    mgmode_GambleCoinCreate(mgModeCoinBase);
    Hu3DModelPosSet(mgmode_mdlTbl[4], -208.0f, 63.75f, -332.0f);
    Hu3DData[mgmode_mdlTbl[4]].rot.y = 15.0f;
    Hu3DModelAttrSet(mgmode_mdlTbl[8], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(mgmode_mdlTbl[8], 2.0f, 0.0f, -332.0f);
    Hu3DModelAttrSet(mgmode_mdlTbl[17], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(mgmode_mdlTbl[17], 2.0f, 63.75f, -332.0f);
    WipeCreateIn(WIPE_TYPE_PREV, 10);
    Hu3DModelAttrSet(mgmode_mdlTbl[18], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    mgmode_GambleMgPicClose();
    HuWinMesSet(mgmode_winId, 0x580C, -1, -1);
    HuWinExAnimIn(mgmode_winId);
    mgmode_GamblePayoutExec();
    while (!(HuPadBtnDown[mgmode_padNo] & (A_BUTTON | B_BUTTON))) {
        HuPrcVSleep();
    }
    if (mgModeCoinBase <= 0) {
        HuWinMesSet(mgmode_winId, 0x5811, -1, -1);
        while (HuWinStatGet(mgmode_winId) != 0) {
            HuPrcVSleep();
        }
        Hu3DMotionShiftSet(mgmode_mdlTbl8[0], mgmode_motTbl13, 0, 4, 0);
        _HuAudPlayerFXPlay(GwPlayer[0].chr + 0x26C, 0);
        HuWinMesSet(mgmode_winId, 0x5812, -1, -1);
        while (HuWinStatGet(mgmode_winId) != 0) {
            HuPrcVSleep();
        }
        choice = HuWinChoiceGet(mgmode_winId, 0, 0);
        mgmode_MotionEndWait(8);
        mgmode_GambleBoardClear();
        Hu3DMotionShiftSet(mgmode_mdlTbl8[0], mgmode_motTbl8, 0, 8, 2);
        if (choice == 0) {
            mgmode_GambleCoinKill();
            HuWinExAnimOut(mgmode_winId, 0);
            return 1;
        }
    } else if (mgModeCoinBase >= 1000) {
        omAddPrcObj(mgmode_GambleSpotProc, 0x3F00, 0x800, 0);
        HuWinMesSet(mgmode_winId, 0x580D, -1, -1);
        while (HuWinStatGet(mgmode_winId) != 0) {
            HuPrcVSleep();
        }
        while (mgmode_gambleSpotWaitF == 0) {
            HuPrcVSleep();
        }
        mgmode_gambleSpotWaitF = 0;
        if (_CheckFlag(0x1F)) {
            HuWinInsertMesSet(mgmode_winId, GwPlayer[mgmode_playerNo].chr + 0x1C00, 0);
            HuWinMesSet(mgmode_winId, 0x5810, -1, -1);
            while (HuWinStatGet(mgmode_winId) != 0) {
                HuPrcVSleep();
            }
        } else {
            _SetFlag(0x1F);
            HuWinMesSet(mgmode_winId, 0x580E, -1, -1);
            while (HuWinStatGet(mgmode_winId) != 0) {
                HuPrcVSleep();
            }
            mgmode_GambleRewardExec();
            HuWinMesSet(mgmode_winId, 0x580F, -1, -1);
            while (HuWinStatGet(mgmode_winId) != 0) {
                HuPrcVSleep();
            }
            HuWinInsertMesSet(mgmode_winId, GwPlayer[mgmode_playerNo].chr + 0x1C00, 0);
            HuWinMesSet(mgmode_winId, 0x5810, -1, -1);
            while (HuWinStatGet(mgmode_winId) != 0) {
                HuPrcVSleep();
            }
            mgmode_MotionEndWait(8);
            save = TRUE;
        }
        mgmode_GambleBoardClear();
        mgmode_GamblePlayerExitExec();
        HuAudSeqFadeOut(60);
        mgmode_gambleClearF = 1;
        if (save) {
            mgmode_RecordSave();
        }
        return 0;
    } else {
        if (HuPadBtnDown[mgmode_padNo] & B_BUTTON) {
            HuAudFXPlay(4);
            if (mgmode_GambleQuitCheck()) {
                goto cancel;
            }
        }
        Hu3DMotionShiftSet(mgmode_mdlTbl8[0], mgmode_motTbl8, 0, 10, 2);
        HuWinMesSet(mgmode_winId, 0x5809, -1, -1);
        while (HuWinStatGet(mgmode_winId) != 0) {
            HuPrcVSleep();
        }
        if (HuWinAttrGet(mgmode_winId) & 8) {
            HuWinExAnimIn(mgmode_winId);
        }
        mgmode_GambleBoardClear();
        mgModeMgNo = mgmode_GambleMgRouletteExec();
        HuWinInsertMesSet(mgmode_winId, mgModeMgNo + 0x4700, 0);
        HuWinMesSet(mgmode_winId, 0x580A, -1, -1);
        while (HuWinStatGet(mgmode_winId) != 0) {
            HuPrcVSleep();
        }
        if (HuWinAttrGet(mgmode_winId) & 8) {
            HuWinExAnimIn(mgmode_winId);
        }
        if (winData[mgmode_winId].input & B_BUTTON) {
            HuAudFXPlay(4);
            if (mgmode_GambleQuitCheck()) {
                goto cancel;
            }
        }
        HuWinMesSet(mgmode_winId, 0x580B, -1, -1);
        if (HuWinAttrGet(mgmode_winId) & 8) {
            HuWinExAnimIn(mgmode_winId);
        }
        mgModeCoinRate = -1;
        do {
            mgModeCoinRate = mgmode_GambleBetChoice();
            if (mgModeCoinRate < 0) {
                if (mgmode_GambleQuitCheck()) {
                    goto cancel;
                }
                HuWinMesSet(mgmode_winId, 0x580B, -1, -1);
                if (HuWinAttrGet(mgmode_winId) & 8) {
                    HuWinExAnimIn(mgmode_winId);
                }
            }
        } while (mgModeCoinRate < 0);
        mgModeCoinBase -= mgModeCoinRate;
        GwPlayer[0].gameCoin = mgModeCoinRate;
        GwPlayer[0].group = 0;
        for (i = 1; i < 4; i++) {
            GwPlayer[i].group = 1;
        }
        _SetFlag(0xD);
        GwSystem.minigame_index = (u8)mgModeMgNo + 1;
        omOvlHisChg(0, 0x69, 5, 0x84);
        mgmode_exitF = 1;
        mgmode_exitOvlNo = 0x70;
        mgmode_exitEvtNo = 0;
        mgmode_exitMode = 2;
        while (TRUE) {
            HuPrcVSleep();
        }
    cancel:
        mgmode_GambleBoardClear();
        Hu3DMotionShiftSet(mgmode_mdlTbl8[0], mgmode_motTbl8, 0, 8, 2);
    }
    mgmode_GamblePlayerExitExec();
    return 0;
}

s32 mgmode_GambleQuitCheck(void) {
    s16 size[2];
    s32 result = FALSE;
    s16 winId;
    s16 choice;

    HuWinMesSet(mgmode_winId, 0x5813, -1, -1);
    while (HuWinStatGet(mgmode_winId) != 0) {
        HuPrcVSleep();
    }
    if ((s16)HuWinChoiceGet(mgmode_winId, 0, 0) == 0) {
        if (mgModeCoinBase < 11) {
            result = TRUE;
        } else {
            HuWinExAnimOut(mgmode_winId, 0);
            HuWinMesMaxSizeGet(1, size, 0x5814);
            winId = HuWinExCreate(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
            HuWinActivePlayerSet(winId, 1 << mgmode_padNo);
            HuWinExAnimIn(winId);
            HuWinMesSet(winId, 0x5814, -1, -1);
            while (HuWinStatGet(winId) != 0) {
                HuPrcVSleep();
            }
            choice = HuWinChoiceGet(winId, 0, 0);
            HuWinExAnimOut(winId, 0);
            HuWinKill(winId);
            if (choice == 0) {
                result = TRUE;
            }
        }
    }
    return result;
}

void mgmode_GambleBoardCreate(s32 animate) {
    s16 i;
    f32 t;
    f32 scaleX;
    f32 scaleY;

    if (mgmode_gambleBoardSprTbl == (MgmodeEsprite *)-1) {
        mgmode_gambleBoardSprTbl = mgmode_SprListCreate(mgmode_gambleBoardSprDefTbl);
        if (animate) {
            HuAudFXPlay(0x243);
            mgmode_SprListScaleSet(mgmode_gambleBoardSprTbl, 0, 0.0f, 0.0f);
            HuPrcSleep(5);
            for (i = 0; i < 11; i++) {
                t = i / 10.0f;
                scaleX = sindf(t * 90.0f);
                scaleY = cosdf(t * 270.0f + 90.0f);
                if (scaleY < 0.0f) {
                    scaleY = -scaleY;
                }
                mgmode_SprListScaleSet(mgmode_gambleBoardSprTbl, 0, scaleX, scaleY);
                HuPrcVSleep();
            }
        }
        mgmode_SprListPriSet(mgmode_gambleBoardSprTbl, 0, 20);
    }
}

void mgmode_GambleBoardKill(void) {
    s16 i;
    f32 scale;

    HuAudFXPlay(0x244);
    for (i = 0; i < 11; i++) {
        scale = cosdf(i / 10.0f * 90.0f);
        mgmode_SprListScaleSet(mgmode_gambleBoardSprTbl, 0, scale, scale);
        HuPrcVSleep();
    }
    mgmode_SprListKill(mgmode_gambleBoardSprTbl);
    mgmode_gambleBoardSprTbl = (MgmodeEsprite *)-1;
}

void mgmode_GamblePayoutExec(void) {
    s16 rate = mgModeCoinRate;
    s16 coins = GwPlayer[0].bonusCoin;
    s16 i;

    mgmode_SprListDispOn(mgmode_gambleBoardSprTbl, 1);
    mgmode_SprListPosSet(mgmode_gambleBoardSprTbl, 1, 184, 46);
    mgmode_SprListDispOn(mgmode_gambleBoardSprTbl, 2);
    mgmode_SprListPosSet(mgmode_gambleBoardSprTbl, 2, 184, 98);
    mgmode_GambleBetDispOn(184, 122, mgModeCoinBase);
    mgmode_GambleCalcDispSet(rate, 0, 0);
    mgmode_GambleBetNumSet(mgModeCoinBase);
    mgmode_GambleCoinNumSet(mgModeCoinBase);
    HuPrcSleep(10);
    for (i = 0; i <= coins; i++) {
        mgmode_GambleCalcDispSet(rate, i, rate * i);
        mgmode_GambleBetNumSet(mgModeCoinBase + rate * i);
        mgmode_GambleCoinNumSet(mgModeCoinBase + rate * i);
        HuAudFXPlay(9);
        HuPrcSleep(2);
    }
    mgModeCoinBase += coins * rate;
    if (coins == 0) {
        Hu3DMotionShiftSet(mgmode_mdlTbl8[0], mgmode_motTbl11, 0, 8, 0);
        _HuAudPlayerFXPlay(GwPlayer[0].chr + 0x287, 0);
    } else {
        Hu3DMotionShiftSet(mgmode_mdlTbl8[0], mgmode_motTbl10, 0, 8, 0);
        _HuAudPlayerFXPlay(GwPlayer[0].chr + 0x275, 0);
    }
    mgmode_MotionEndWait(8);
}

void mgmode_MotionEndWait(s16 index) {
    while (Hu3DMotionShiftTimeGet(mgmode_mdlTbl[index]) != -1.0f ||
           Hu3DData[mgmode_mdlTbl[index]].motTime <
               Hu3DMotion[Hu3DData[mgmode_mdlTbl[index]].motId].unk02) {
        HuPrcVSleep();
    }
}

void mgmode_GambleBoardClear(void) {
    s16 i;
    s16 j;
    f32 scale;

    for (i = 0; i < 10; i++) {
        scale = 1.0f - i / 10.0f;
        for (j = 1; j < 21; j++) {
            mgmode_SprListScaleSet(mgmode_gambleBoardSprTbl, j, scale, scale);
        }
        HuPrcVSleep();
    }
    for (j = 1; j < 21; j++) {
        mgmode_SprListDispOff(mgmode_gambleBoardSprTbl, j);
        mgmode_SprListScaleSet(mgmode_gambleBoardSprTbl, j, 1.0f, 1.0f);
    }
}

void mgmode_GambleCalcDispSet(s16 arg0, s16 arg1, s16 arg2) {
    s16 i;

    if (arg2 >= 10000) {
        arg2 = 9999;
    }
    mgmode_SprListNumSet(mgmode_gambleBoardSprTbl, 3, arg0, 3);
    for (i = 0; i < 3; i++) {
        mgmode_SprListPosSet(mgmode_gambleBoardSprTbl, i + 3, i * 16 + 104, 70);
    }
    mgmode_SprListNumSet(mgmode_gambleBoardSprTbl, 8, arg1, 2);
    for (i = 0; i < 2; i++) {
        mgmode_SprListPosSet(mgmode_gambleBoardSprTbl, i + 8, i * 16 + 168, 70);
    }
    mgmode_SprListNumSet(mgmode_gambleBoardSprTbl, 11, arg2, 4);
    for (i = 0; i < 4; i++) {
        mgmode_SprListPosSet(mgmode_gambleBoardSprTbl, i + 11, i * 16 + 216, 70);
    }
    mgmode_SprListDispOn(mgmode_gambleBoardSprTbl, 7);
    mgmode_SprListPosSet(mgmode_gambleBoardSprTbl, 7, 152, 70);
    mgmode_SprListDispOn(mgmode_gambleBoardSprTbl, 10);
    mgmode_SprListPatNoSet(mgmode_gambleBoardSprTbl, 10, 3);
    mgmode_SprListPosSet(mgmode_gambleBoardSprTbl, 10, 200, 70);
}

s16 mgmode_GambleMgRouletteExec(void) {
    s16 i;
    s16 prev;
    s16 type;
    s16 result;

    if (mgmode_gambleMgPicSpr == -1) {
        mgmode_gambleMgPicSpr = mgmode_MgPicCreate();
        espPriSet(mgmode_gambleMgPicSpr, 15);
        espAttrSet(mgmode_gambleMgPicSpr, 0x5008);
        espPosSet(mgmode_gambleMgPicSpr, 184, 132);
        for (i = 0; i < 10; i++) {
            espTPLvlSet(mgmode_gambleMgPicSpr, i / 10.0f * 255.0f);
            HuPrcVSleep();
        }
    }
    prev = -1;
    type = rand8() & 3;
    mgmode_MgPicLoad(mgDataTbl[mgmode_gambleMgTbl[type]].flags & 0x7FF);
    mgmode_GambleTitleSet(mgmode_gambleMgTbl[type] + 0x4700, 184, 62);
    for (i = 0; i < 30; i++) {
        HuPrcVSleep();
        while (type == prev) {
            type = rand8() & 3;
        }
        prev = type;
        mgmode_GambleTitleKill();
        mgmode_MgPicLoad(mgDataTbl[mgmode_gambleMgTbl[type]].flags & 0x7FF);
        mgmode_GambleTitleSet(mgmode_gambleMgTbl[type] + 0x4700, 184, 62);
        HuAudFXPlay(0x104);
    }
    HuPrcVSleep();
    result = mgModeMgList[mgModeMgListIdx];
    mgmode_GambleTitleKill();
    mgmode_MgPicLoad(mgDataTbl[result].flags & 0x7FF);
    mgmode_GambleTitleSet(result + 0x4700, 184, 62);
    HuPrcVSleep();
    HuAudFXPlay(0x105);
    return result;
}

s16 mgmode_GambleBetChoice(void) {
    s16 value = 0;
    s16 delta;

    mgmode_GambleBetDispOn(184, 126, 0);
    while (TRUE) {
        HuPrcVSleep();
        if ((HuPadBtnDown[mgmode_padNo] & A_BUTTON) && value != 0) {
            HuAudFXPlay(0x247);
            break;
        }
        if (HuPadBtnDown[mgmode_padNo] & B_BUTTON) {
            HuAudFXPlay(4);
            value = -1;
            break;
        }
        if (ContBtnRep[mgmode_padNo] & L_JPAD) {
            delta = 10;
        } else if (ContBtnRep[mgmode_padNo] & R_JPAD) {
            delta = -10;
        } else if (ContBtnRep[mgmode_padNo] & U_JPAD) {
            delta = 1;
        } else if (ContBtnRep[mgmode_padNo] & D_JPAD) {
            delta = -1;
        } else {
            delta = 0;
        }
        if (delta != 0) {
            HuAudFXPlay(0x246);
        }
        if ((value == mgModeCoinBase || value == 100) && delta > 0) {
            value = 0;
        } else if (value + delta >= 100 || value + delta > mgModeCoinBase) {
            value = mgModeCoinBase;
            if (value > 100) {
                value = 100;
            }
        } else if (value + delta < 0) {
            value = mgModeCoinBase;
            if (value > 100) {
                value = 100;
            }
        } else {
            value += delta;
        }
        mgmode_GambleBetNumSet(value);
        mgmode_GambleCoinNumSet(mgModeCoinBase - value);
    }
    return value;
}

void mgmode_GambleMgPicClose(void) {
    s16 i;
    s16 tpLvl;

    for (i = 0; i < 10; i++) {
        tpLvl = (1.0f - i / 10.0f) * 255.0f;
        espTPLvlSet(mgmode_gambleMgPicSpr, tpLvl);
        mgmode_GambleTitleTPLvlSet(tpLvl);
        HuPrcVSleep();
    }
    mgmode_GambleTitleKill();
    mgmode_MgPicKill();
    mgmode_gambleMgPicSpr = -1;
}

void mgmode_GambleRewardExec(void) {
    s16 model = mgmode_mdlTbl8[7];
    s16 camera;
    f32 scale;
    f32 y;
    s16 i;

    camera = EffectCreate(0xB0004, 0x2A9);
    Hu3DModelCameraSet(camera, HU3D_CAM1);
    EffectRangeSet(camera, 50.0f);
    EffectParamSet(camera, 2.0f, 20.0f, 0.0f);
    Hu3DMotionShiftSet(mgmode_mdlTbl8[0], mgmode_motTbl8, 0, 8, 0);
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(model, 2.0f, 500.0f, -382.0f);
    EffectPosSet(camera, 2.0f, 500.0f, -332.0f);
    Hu3DModelRotSet(model, 30.0f, 80.0f, 3.0f);
    HuTranslateF(Hu3DData[model].mtx, 0.0f, 0.0f, 20.0f);
    scale = 1.0f;
    HuAudFXPlay(0x249);
    for (i = 0; i < 51; i++) {
        y = (1.0f - sindf(i / 50.0f * 90.0f)) * 400.0f + 100.0f;
        Hu3DData[model].pos.y = y;
        EffectPosSet(camera, 2.0f, y + 30.0f, -332.0f);
        if (i == 10) {
            Hu3DMotionShiftSet(mgmode_mdlTbl8[0], mgmode_motTbl14, 0, 8, 0);
        }
        if (i == 40) {
            Hu3DMotionShiftSet(mgmode_mdlTbl8[0], mgmode_motTbl10, 0, 8, 0);
            RepeatVibrator(mgmode_padNo, 20, 0, 20);
        }
        if (i > 30) {
            scale -= 0.1f;
            if (scale < 0.0f) {
                scale = 0.0f;
            }
            Hu3DModelScaleSet(model, scale, scale, scale);
        }
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    EffectStop(camera);
}

void mgmode_GambleSpotProc(void) {
    s16 i;

    mgmode_gambleSpotWaitF = 0;
    HuAudFXPlay(0x248);
    mgmode_SpotClear();
    HuSprDispOn(mgmode_spotGrp, 0);
    for (i = 0; i < 31; i++) {
        if (i == 15) {
            mgmode_ConfettiOn(mgmode_gambleConfettiNo);
        }
        if (i == 25) {
            Hu3DMotionShiftSet(mgmode_mdlTbl8[0], mgmode_motTbl12, 0, 8, 0);
            _HuAudPlayerFXPlay(GwPlayer[0].chr + 0x263, 0);
        }
        HuSprTPLvlSet(mgmode_spotGrp, 0, i / 30.0f * 220.0f);
        mgmode_SpotUpdate(186.0f, sindf(i / 30.0f * 90.0f) * 10.0f);
        HuPrcVSleep();
    }
    mgmode_MotionEndWait(8);
    mgmode_gambleSpotWaitF = 1;
    do {
        HuPrcVSleep();
    } while (mgmode_gambleSpotWaitF != 0);
    for (i = 0; i < 11; i++) {
        HuSprTPLvlSet(mgmode_spotGrp, 0, (1.0f - i / 30.0f) * 220.0f);
        HuPrcVSleep();
    }
    HuSprDispOff(mgmode_spotGrp, 0);
    mgmode_ConfettiOff(mgmode_gambleConfettiNo);
    omDelPrcObj(NULL);
}

void mgmode_GamblePlayerEnterExec(void) {
    s16 model = mgmode_mdlTbl8[0];
    s16 other = mgmode_mdlTbl8[9];
    f32 dx = 198.0f;
    f32 dz = 210.0f;
    f32 angle;
    f32 t;
    f32 x;
    f32 z;
    s16 i;

    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(other, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionSet(model, mgmode_motTbl9);
    Hu3DMotionAttrSet(model, 2, 2);
    angle = atan2df(dx, dz) + 180.0f;
    Hu3DModelPosSet(model, 200.0f, 0.0f, -122.0f);
    Hu3DModelRotSet(model, 0.0f, angle, 0.0f);
    for (i = 0; i < 16; i++) {
        t = 1.0f - i / 15.0f;
        x = dx * t + 2.0f;
        z = dz * t + -332.0f;
        Hu3DModelPosSet(model, x, 0.0f, z);
        mgmode_MdlPosCopy(other, model);
        if (i < 12 && i % 5 == 0) {
            _HuAudPlayerFXPlay(GwPlayer[0].chr + 0x29, 0);
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, mgmode_motTbl8, 0, 8, 2);
    for (i = 0; i < 9; i++) {
        t = 1.0f - i / 8.0f;
        Hu3DData[model].rot.y = t * angle;
        HuPrcVSleep();
    }
}

void mgmode_GamblePlayerExitExec(void) {
    s16 model = mgmode_mdlTbl8[0];
    s16 other = mgmode_mdlTbl8[9];
    f32 dx = -198.0f;
    f32 dz = -210.0f;
    f32 angle;
    f32 t;
    f32 x;
    f32 z;
    s16 i;

    Hu3DMotionShiftSet(model, mgmode_motTbl9, 0, 8, 2);
    angle = atan2df(dx, dz) + 180.0f;
    for (i = 0; i < 9; i++) {
        t = i / 8.0f;
        Hu3DData[model].rot.y = t * angle;
        HuPrcVSleep();
    }
    for (i = 0; i < 16; i++) {
        t = 1.0f - i / 15.0f;
        x = dx * t + 200.0f;
        z = dz * t + -122.0f;
        Hu3DModelPosSet(model, x, 0.0f, z);
        mgmode_MdlPosCopy(other, model);
        if (i < 12 && i % 5 == 0) {
            _HuAudPlayerFXPlay(GwPlayer[0].chr + 0x29, 0);
        }
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(other, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void mgmode_GambleBetDispOn(s16 x, s16 y, s16 value) {
    s16 left;
    s16 i;

    left = x - 40;
    mgmode_SprListPosSet(mgmode_gambleBoardSprTbl, 0xF, left, y);
    mgmode_SprListDispOn(mgmode_gambleBoardSprTbl, 0xF);
    mgmode_SprListPosSet(mgmode_gambleBoardSprTbl, 0x10, x - 24, y);
    mgmode_SprListDispOn(mgmode_gambleBoardSprTbl, 0x10);
    for (i = 0; i < 4; i++) {
        mgmode_SprListPosSet(mgmode_gambleBoardSprTbl, i + 0x11, left + (i + 2) * 16, y);
    }
    mgmode_GambleBetNumSet(value);
}

void mgmode_GambleBetNumSet(s16 value) {
    mgmode_SprListNumSet(mgmode_gambleBoardSprTbl, 0x11, value, 4);
}

void mgmode_GambleBetDispOff(void) {
    s16 i;

    mgmode_SprListDispOff(mgmode_gambleBoardSprTbl, 0xF);
    mgmode_SprListDispOff(mgmode_gambleBoardSprTbl, 0x10);

    for (i = 0; i < 4; i++) {
        mgmode_SprListDispOff(mgmode_gambleBoardSprTbl, i + 0x11);
    }
}

void mgmode_GambleCoinCreate(s16 value) {
    if (mgmode_gambleCoinSprTbl == (MgmodeEsprite *)-1) {
        mgmode_gambleCoinSprTbl = mgmode_SprListCreate(mgmode_gambleCoinSprDefTbl);
        mgmode_GambleCoinNumSet(value);
    }
}

void mgmode_GambleCoinNumSet(s16 value) {
    mgmode_SprListNumSet(mgmode_gambleCoinSprTbl, 2, value, 4);
}

void mgmode_SprListNumSet(MgmodeEsprite *sprites, s16 base, s16 value, s16 digits) {
    u8 buf[8];
    s16 offset;
    s16 i;

    if (value >= 10000) {
        value = 9999;
    }
    sprintf((char *)buf, "%4d", value);
    offset = 4 - digits;
    for (i = 0; i < digits; i++) {
        if (buf[offset + i] < '0') {
            mgmode_SprListDispOff(sprites, base + i);
        } else {
            mgmode_SprListDispOn(sprites, base + i);
            mgmode_SprListPatNoSet(sprites, base + i, buf[offset + i] & 0xF);
        }
    }
}

void mgmode_GambleCoinKill(void) {
    mgmode_SprListKill(mgmode_gambleCoinSprTbl);
    mgmode_gambleCoinSprTbl = (MgmodeEsprite *)-1;
}

void mgmode_GambleTitleInit(void) {
    s16 i;

    for (i = 0; i < 16; i++) {
        mgmode_gambleTitleMes.strSprId[i] = mgmode_gambleTitleMes.strGId[i] = -1;
    }
}

void mgmode_GambleTitleSet(s32 mesId, s16 x, s16 y) {
    u8 *str;
    s16 len;
    s16 count;
    s16 i;

    str = MessDataMesGet((void *)mesId);
    len = strlen((char *)str);
    count = 0;
    for (i = 0; i <= len; i++) {
        if (str[i] >= '0') {
            mgmode_gambleTitleStr[count++] = str[i];
        }
    }
    mgmode_gambleTitleStr[count] = 0;
    MessDataMesFree(str);
    mgmode_gambleTitleMes.subMode = count;
    GameMesStrCreate(&mgmode_gambleTitleMes, (char *)mgmode_gambleTitleStr, 0, -1, -1);
    for (i = 0; i < mgmode_gambleTitleMes.subMode; i++) {
        HuSprPriSet(mgmode_gambleTitleMes.strGId[0], i + 1, 10);
        HuSprScaleSet(mgmode_gambleTitleMes.strGId[0], i + 1, 0.7f, 1.0f);
    }
    HuSprPosSet(mgmode_gambleTitleMes.strGId[0], 0, x, y);
}

void mgmode_GambleTitleKill(void) {
    s16 i;

    if (mgmode_gambleTitleMes.strGId[0] != GMES_ID_NONE) {
        GMesSprKill(&mgmode_gambleTitleMes);
        for (i = 0; i < 16; i++) {
            mgmode_gambleTitleMes.strSprId[i] = mgmode_gambleTitleMes.strGId[i] = GMES_ID_NONE;
        }
    }
}

void mgmode_GambleTitleTPLvlSet(s16 arg0) {
    int i;

    i = 0;
    if (mgmode_gambleTitleMes.subMode > 0) {
        do {
            i++;
            HuSprTPLvlSet(mgmode_gambleTitleMes.strGId[0], (s16)i, arg0);
        } while ((s16)i < mgmode_gambleTitleMes.subMode);
    }
}

void mgmode_SpotInit(void) {
    HuSprite *sprite;

    mgmode_spotAnim = HuSprAnimDataRead(0x12003D);
    mgmode_spotGrp = HuSprGrpCreate(5, 0);
    HuSprGrpMemberSet(mgmode_spotGrp, 0, mgmode_spotAnim, 0);
    HuSprAttrReset(mgmode_spotGrp, 0, 0xFFFF);
    HuSprAttrSet(mgmode_spotGrp, 0, 0x9008);
    HuSprPosSet(mgmode_spotGrp, 0, 160, 120);
    HuSprPriSet(mgmode_spotGrp, 0, 15);
    HuSprScaleSet(mgmode_spotGrp, 0, 1.0f, 2.0f);
    sprite = HuSprGet(mgmode_spotGrp, 0);
    HuMemFree(sprite->data->pat->data);
    mgmode_spotBufTbl[0] = HuMemAllocTag(0x4B00, 0x7918);
    mgmode_spotBufTbl[1] = HuMemAllocTag(0x4B00, 0x7918);
    mgmode_spotBufTbl[2] = HuMemAllocTag(0x4B00, 0x7918);
    sprite->data->pat->data = mgmode_spotBufTbl[0];
    mgmode_SpotClear();
}

void mgmode_SpotClear(void) {
    memset(mgmode_spotBufTbl[0], 0xFF, 0x4B00);
    memset(mgmode_spotBufTbl[1], 0xFF, 0x4B00);
    memset(mgmode_spotBufTbl[2], 0xFF, 0x4B00);
}

void mgmode_SpotUpdate(f32 centerX, f32 angle) {
    u8 *dst;
    f32 spread;
    s16 y;
    s16 x;
    s16 left;
    s16 right;
    u8 *p;
    u8 pixel;

    dst = mgmode_spotBufTbl[Hu3DBufNo];
    spread = sindf(angle);
    for (y = 0; y < 120; y++) {
        left = centerX - spread * (y + 100);
        right = centerX + spread * (y + 100);
        for (x = 0; x < 320; x++) {
            if (left < x && x < right) {
                pixel = *dst;
                *dst = (x & 1) ? pixel & 0xF0 : pixel & 0xF;
            } else {
                pixel = *dst;
                *dst = (x & 1) ? pixel | 0xF : pixel | 0xF0;
            }
            dst += x & 1;
        }

        p = &mgmode_spotBufTbl[Hu3DBufNo][(y * 320 + left - 1) / 2];
        *p &= ((left - 1) & 1) ? 0xF0 : 0xF;
        *p |= ((left - 1) & 1) ? 0xA : 0xA0;
        p = &mgmode_spotBufTbl[Hu3DBufNo][(y * 320 + right + 1) / 2];
        *p &= ((right + 1) & 1) ? 0xF0 : 0xF;
        *p |= ((right + 1) & 1) ? 0xA : 0xA0;
        p = &mgmode_spotBufTbl[Hu3DBufNo][(y * 320 + left) / 2];
        *p &= (left & 1) ? 0xF0 : 0xF;
        *p |= (left & 1) ? 0x4 : 0x40;
        p = &mgmode_spotBufTbl[Hu3DBufNo][(y * 320 + right) / 2];
        *p &= (right & 1) ? 0xF0 : 0xF;
        *p |= (right & 1) ? 0x4 : 0x40;
    }
    HuSprGet(mgmode_spotGrp, 0)->data->pat->data = mgmode_spotBufTbl[Hu3DBufNo];
}
