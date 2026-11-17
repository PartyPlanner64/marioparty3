#include "common.h"
#include "mgmode.h"
#include "game/hmfmath.h"

extern MgmodeEsprite *mgmode_battleMenuSprTbl;
extern s16 mgmode_battleTypeNum;
extern s16 mgmode_battleTypeTbl[8];
extern u8 mgmode_starPlayerTbl[4];
extern u8 mgmode_starPlayerNum;
extern s16 mgModeSelNo;
extern s16 mgModeMgNo;
extern s16 mgModeStar[4];
extern s16 mgModeType;
extern s16 mgModeMgList[8];
extern u8 mgmode_typeMgTbl[][25];
extern s16 mgmode_typeUnlockNumTbl[];
extern s16 mgmode_typeMgNumTbl[];
extern s16 mgmode_winId;
extern u8 mgModeGroupBak[4];
extern s16 mgmode_mdlTbl7[];
extern s16 mgmode_mdlTbl32[];
extern s16 mgmode_mdlTbl[];
extern s16 mgmode_motTbl11[];
extern s16 mgmode_motTbl7[];
extern s16 mgmode_motTbl6;
extern s16 mgmode_motTbl4;
extern s16 mgModeMgListIdx;
extern MgmodeEsprite *mgmode_battleBoardSprTbl;
extern s16 mgmode_battleStarAnim;
extern u16 mgmode_battleStarSprTbl[28];
extern s16 mgmode_padNo;
extern MgmodeEspriteDef mgmode_battleMenuSprDefTbl[];
extern s16 mgModeCoinRate;
extern u8 mgmode_exitF;
extern s16 mgmode_exitMode;
extern s16 mgmode_exitEvtNo;
extern s16 mgmode_exitOvlNo;
extern MgmodeSpaceCoord mgmode_battleTypeCursorTbl[];
extern s16 mgmode_battleStarSprNum;
extern ModeCameraPreset *mgmode_cameraPresetTbl;
extern f32 mgmode_cameraFar;
extern s16 mgmode_battlePlayerAnimTbl[4];
extern s16 mgmode_battlePlayerChrTbl[4];
extern s16 mgmode_battleConfettiTbl[4];
extern MgmodeModelEntry mgmode_battleMdlDefTbl[];
extern HuMtx4F mgmode_battleDoorMtx;
extern s16 mgmode_zClearF;
extern u8 mgmode_cameraPresetNo;
extern s16 mgmode_motTbl5;
extern s16 mgmode_motTbl15[];
extern s16 mgmode_motTbl19[];
extern s16 mgmode_motTbl23[];
extern s16 mgmode_motTbl27[];
extern u8 mgmode_chrVoiceTbl[];
extern MgmodeEspriteDef mgmode_battleBoardSprDefTbl[];

void mgmode_BattleSetupExec(void);
s16 mgmode_BattleTypeChoice(s32 arg0);
void mgmode_BattlePlayerPosSet(s16 arg0);
void mgmode_BattlePlayerEnterExec(s16 arg0);
void mgmode_BattleGoalHide(void);
void mgmode_BattleTypeHide(void);
void mgmode_BattleMgListShuffle(void);
void mgmode_BattlePlayerExitExec(s16 arg0);
s16 mgmode_BattleMgRouletteExec(s16 category);
s16 mgmode_TeamChoice(s16 arg0);
void mgmode_TeamChoiceKill(void);
void mgmode_BattleMenuClose(void);
s16 mgmode_BattleGoalChoice(s32 arg0);
MgmodeEsprite *mgmode_SprListCreate(MgmodeEspriteDef *defs);
void mgmode_SprListAttrSet(MgmodeEsprite *arg0, s16 index, s16 arg2);
void mgmode_MgPicKill(void);
void mgmode_SprListKill(MgmodeEsprite *arg0);
void mgmode_SprListDispOff(MgmodeEsprite *arg0, s16 index);
void mgmode_SprListTPLvlSet(MgmodeEsprite *arg0, s16 index, s16 tpLvl);
void mgmode_SprListScaleSet(MgmodeEsprite *arg0, s16 index, f32 x, f32 y);
void mgmode_ConfettiOn(s16 index);
void mgmode_ConfettiOff(s16 index);
s16 mgmode_MgPicCreate(void);
void mgmode_MgPicLoad(s16 arg0);
void mgmode_MdlPosCopy(s16 dstModel, s16 srcModel);
void mgmode_SprListPosSet(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3);
void mgmode_SprListDispOn(MgmodeEsprite *arg0, s16 index);
void mgmode_CursorMoveTimeSet(s16 arg0);
void mgmode_CursorSelMove(s16 arg0);
s16 mgmode_CursorPadNextGet(s16 stickX, s16 stickY);
void mgmode_DpadStickSet(void);
void mgmode_BattleEnterExec(void);
s32 mgmode_BattleResultExec(void);
void mgmode_BattleBoardCreate(void);
s16 mgmode_BattleStarPlayerGet(s16 mgIndex);
s32 mgmode_BattleStarAdd(void);
void mgmode_BattleBoardKill(void);
void mgmode_BattleTypeTitleClose(void);
void mgmode_BattleGoalTitleClose(void);
void mgmode_BattleConfettiSet(s32 arg0);
void mgmode_CameraPresetSet(s16 arg0);
void mgmode_MdlListCreate(MgmodeModelEntry *entries);
s16 mgmode_ConfettiCreate(f32 arg0, f32 arg1, f32 arg2, f32 arg3);

s16 mgmode_battleMgPicSpr = -1;
ModeCameraPreset mgmode_battleCameraPresetTbl[7] = {
    { { 4.0f, 0.0f, 0.0f }, { 0.0f, 178.9f, -391.4f }, 1480.0f, 40.0f },
    { { 4.0f, 0.0f, 0.0f }, { 0.0f, 178.9f, -391.4f }, 1060.0f, 40.0f },
    { { 0.0f, 0.0f, 0.0f }, { -36.0f, 206.8f, -390.0f }, 1190.0f, 21.0f },
    { { 0.0f, 184.0f, 0.0f }, { 11.7f, 110.9f, 979.4f }, 630.0f, 40.0f },
    { { 0.0f, 184.0f, 0.0f }, { 11.7f, 90.9f, 978.7f }, 120.0f, 40.0f },
    { { 356.0f, 12.0f, 0.0f }, { -224.5f, 103.7f, -342.3f }, 400.0f, 40.0f },
    { { 4.0f, 302.0f, 0.0f }, { 53.2f, 134.8f, 80.5f }, 290.0f, 40.0f }
};
MgmodeSpaceCoord mgmode_battleCursorPosTbl[3] = {
    { 160, 121 }, { 160, 120 }, { -1, -1 }
};
u8 mgmode_battleGoalTbl[4] = {
    3, 5, 7, 0
};
u8 mgmode_battleChrMotTbl[8] = {
    0x37, 0x36, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37
};
MgmodeSpaceCoord mgmode_battleGoalCursorPosTbl[4] = {
    { 180, 91 }, { 180, 121 }, { 180, 151 }, { -1, -1 }
};
s16 mgmode_battleGoalPosYTbl[4] = {
    91, 121, 151, 0
};
MgmodeSpaceCoord mgmode_battleTypeCursorPosTbl[6] = {
    { 180, 79 }, { 180, 101 }, { 180, 123 }, { 180, 145 }, { 180, 167 }, { -1, -1 }
};
s32 mgmode_battleRowSprTbl[3] = {
    0x120023, 0x120024, 0x120025
};
s32 mgmode_battleRowTeamSprTbl[3] = {
    0x120026, 0x120027, 0x120028
};
s32 mgmode_battleRow3SprTbl[3] = {
    0x120029, 0x12002A, 0x12002B
};
s16 mgmode_battleStarPosXTbl[24] = {
    -10, 11, 32, 0, 0, 0, 0,
    -31, -10, 11, 32, 53, 0, 0,
    -52, -31, -10, 11, 32, 53, 74,
    0, 0, 0
};

void mgmode_BattleRoomProc(void) {
    s16 size[2];
    HmfMotionNode *node;
    MgmodeModelEntry *entry;
    void *anim;
    s16 choice;
    s16 changed;
    s16 model;
    s16 chr;
    s16 i;

    mgmode_cameraPresetTbl = mgmode_battleCameraPresetTbl;
    mgmode_cameraFar = 2500.0f;
    HuWinMesMaxSizeBetGet(size, 0x5600, 0x560E);
    mgmode_winId = HuWinExCreate(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
    HuWinActivePlayerSet(mgmode_winId, 1 << mgmode_padNo);
    HuWinPriSet(mgmode_winId, 5);
    for (i = 0; i < 4; i++) {
        chr = mgmode_battlePlayerChrTbl[i] = GwPlayer[i].chr;
        mgmode_battleMdlDefTbl[i + 7].unk_00 = CharMotionDataNumGet(chr, 0xA1);
        mgmode_battleMdlDefTbl[i + 11].unk_00 = CharMotionDataNumGet(chr, 0x2);
        mgmode_battleMdlDefTbl[i + 15].unk_00 = CharMotionDataNumGet(chr, 0x33);
        mgmode_battleMdlDefTbl[i + 19].unk_00 = CharMotionDataNumGet(chr, 0x3A);
        mgmode_battleMdlDefTbl[i + 23].unk_00 = CharMotionDataNumGet(chr, 0x2F);
        mgmode_battleMdlDefTbl[i + 27].unk_00 = CharMotionDataNumGet(chr, mgmode_battleChrMotTbl[chr]);
        entry = &mgmode_battleMdlDefTbl[i + 7];
        mgmode_battleConfettiTbl[i] = mgmode_ConfettiCreate(entry->pos.x, 400.0f, entry->pos.z, 30.0f);
    }
    mgmode_MdlListCreate(mgmode_battleMdlDefTbl);
    node = Hu3DModelObjPtrGet(mgmode_mdlTbl[0], "door");
    mtxCopy(mgmode_battleDoorMtx, node->unk58);
    Hu3DModelCameraSet(mgmode_mdlTbl[4], 2);
    Hu3DModelScaleSet(mgmode_mdlTbl[4], 0.7f, 0.7f, 0.7f);
    Hu3DModelScaleSet(mgmode_mdlTbl[31], 0.7f, 0.7f, 0.7f);
    for (i = 0; i < 4; i++) {
        model = mgmode_mdlTbl[i + 7];
        Hu3DModelCameraSet(model, 2);
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelScaleSet(model, 0.7f, 0.7f, 0.7f);
        Hu3DModelScaleSet(model, 0.7f, 0.7f, 0.7f);
        mgmode_battlePlayerAnimTbl[i] = CharAnimCreate(model, 1, mgmode_battlePlayerChrTbl[i],
                                                  CharMotionDataNumGetTbl(mgmode_battlePlayerChrTbl[i], 1, 0));
        Hu3DModelDynamicFree(model);
    }
    model = mgmode_mdlTbl[4];
    anim = DataRead(0xA002A);
    Hu3DAnimCreate(Hu3DData[model].hmf, anim, 0, "c180n_0_DEF");
    DataClose(anim);
    Hu3DModelRemakeStatic(model);
    Hu3DModelDynamicFree(model);
    if (omovlevtno != 4) {
        Hu3DMotionSet(mgmode_mdlTbl[4], mgmode_motTbl5);
        Hu3DMotionAttrSet(mgmode_mdlTbl[4], 2, 2);
        mgmode_CameraPresetSet(0);
        WipeCreateIn(WIPE_TYPE_PREV, 0);
        RepeatVibrator(mgmode_padNo, 5, 0, 5);
        HuAudFXPlay(0x2EB);
        for (i = 0; i < 19; i++) {
            HuPrcVSleep();
            mtxCopy(node->unk58, mgmode_battleDoorMtx);
            mtxRotCat(node->unk58, 0.0f, -i * 5, 0.0f);
        }
        mgmode_CameraPresetMove(1, 10, 1, (void (*)(s16 *))-1);
        HuPrcSleep(5);
        mtxCopy(node->unk58, mgmode_battleDoorMtx);
        mgmode_CameraPresetMove(5, 20, 1, (void (*)(s16 *))-1);
    } else {
        mgmode_zClearF = 1;
        if (mgmode_BattleResultExec()) {
            goto resume;
        }
        mgmode_CameraPresetMove(5, 10, 1, (void (*)(s16 *))-1);
        HuAudSeqPlay(0x4C);
    }
    mgmode_CursorPosTblSet(mgmode_battleCursorPosTbl);
    mgmode_CursorSelSet(0);
    mgmode_CursorDispSet(1);
    HuWinMesSet(mgmode_winId, 0x5600, -1, -1);
    HuWinExAnimIn(mgmode_winId);
    goto loop;
resume:
    HuWinExAnimIn(mgmode_winId);
    HuAudSeqPlay(0x4C);
    mgmode_BattleEnterExec();
loop:
    while (TRUE) {
        HuPrcVSleep();
        mgmode_CursorMoveTimeSet(5);
        switch (mgmode_cameraPresetNo) {
            case 5:
                if (HuPadBtnDown[mgmode_padNo] & A_BUTTON) {
                    HuAudFXPlay(2);
                    Hu3DMotionShiftSet(mgmode_mdlTbl[4], mgmode_motTbl4, 0, 8, 2);
                    mgmode_CursorDispSet(0);
                    HuAudFXPlay(0x299);
                    HuWinMesSet(mgmode_winId, 0x5603, -1, -1);
                    while (HuWinStatGet(mgmode_winId) != 0) {
                        HuPrcVSleep();
                    }
                    while (TRUE) {
                        HuWinMesSet(mgmode_winId, 0x5604, -1, -1);
                        while (HuWinStatGet(mgmode_winId) != 0) {
                            HuPrcVSleep();
                        }
                        if ((s16)HuWinChoiceGet(mgmode_winId, 0, 0) != 0) {
                            choice = -1;
                            break;
                        }
                        HuWinMesSet(mgmode_winId, 0x5605, -1, -1);
                        while (HuWinStatGet(mgmode_winId) != 0) {
                            HuPrcVSleep();
                        }
                        choice = HuWinChoiceGet(mgmode_winId, 0, 0);
                        if (choice == -1) {
                            continue;
                        }
                        if (choice == 0) {
                            HuWinMesSet(mgmode_winId, 0x5606, -1, -1);
                            while (HuWinStatGet(mgmode_winId) != 0) {
                                HuPrcVSleep();
                            }
                        }
                        break;
                    }
                    if (choice == -1) {
                        mgmode_CursorDispSet(1);
                        HuWinMesSet(mgmode_winId, 0x5600, -1, -1);
                        while (HuWinStatGet(mgmode_winId) != 0) {
                            HuPrcVSleep();
                        }
                    } else {
                        mgmode_BattleEnterExec();
                    }
                } else {
                    changed = FALSE;
                    if ((ContBtnDown[mgmode_padNo] & L_JPAD) ||
                        (HuPadBtnDown[mgmode_padNo] & B_BUTTON)) {
                        HuAudFXPlay(1);
                        HuWinExAnimOut(mgmode_winId, 0);
                        mgmode_CursorMoveTimeSet(20);
                        mgmode_CursorSelMove(1);
                        mgmode_CameraPresetMove(3, 20, 1, (void (*)(s16 *))-1);
                        changed = TRUE;
                    }
                    if (ContBtnDown[mgmode_padNo] & R_JPAD) {
                        HuAudFXPlay(1);
                        HuWinExAnimOut(mgmode_winId, 0);
                        mgmode_CursorMoveTimeSet(25);
                        mgmode_CursorSelMove(1);
                        mgmode_CameraPresetMove(6, 10, 0, (void (*)(s16 *))-1);
                        mgmode_CameraPresetMove(3, 15, 1, (void (*)(s16 *))-1);
                        changed = TRUE;
                    }
                    if (changed) {
                        HuWinMesSet(mgmode_winId, 0x5601, -1, -1);
                        HuWinExAnimIn(mgmode_winId);
                    }
                }
                break;
            case 3:
                if (HuPadBtnDown[mgmode_padNo] & A_BUTTON) {
                    HuAudFXPlay(2);
                    HuWinMesSet(mgmode_winId, 0x5602, -1, -1);
                    while (HuWinStatGet(mgmode_winId) != 0) {
                        HuPrcVSleep();
                    }
                    if ((s16)HuWinChoiceGet(mgmode_winId, 0, 0) != 0) {
                        HuWinMesSet(mgmode_winId, 0x5601, -1, -1);
                        while (HuWinStatGet(mgmode_winId) != 0) {
                            HuPrcVSleep();
                        }
                        break;
                    }
                    mgmode_CursorDispSet(0);
                    HuWinExAnimOut(mgmode_winId, 0);
                    mgmode_CameraPresetMove(3, 20, 1, (void (*)(s16 *))-1);
                    node = Hu3DModelObjPtrGet(mgmode_mdlTbl[0], "door");
                    RepeatVibrator(mgmode_padNo, 5, 0, 5);
                    HuAudFXPlay(0x2EB);
                    for (i = 0; i < 19; i++) {
                        HuPrcVSleep();
                        mtxCopy(node->unk58, mgmode_battleDoorMtx);
                        mtxRotCat(node->unk58, 0.0f, -i * 5, 0.0f);
                    }
                    mgmode_CameraPresetMove(4, 20, 1, (void (*)(s16 *))-1);
                    mgmode_exitF = 1;
                    mgmode_exitMode = 0x80;
                    HuAudSeqFadeOut(60);
                    while (TRUE) {
                        HuPrcVSleep();
                    }
                } else {
                    changed = FALSE;
                    if (ContBtnDown[mgmode_padNo] & L_JPAD) {
                        HuAudFXPlay(1);
                        HuWinExAnimOut(mgmode_winId, 0);
                        mgmode_CursorMoveTimeSet(25);
                        mgmode_CursorSelMove(0);
                        mgmode_CameraPresetMove(6, 10, 0, (void (*)(s16 *))-1);
                        mgmode_CameraPresetMove(5, 15, 1, (void (*)(s16 *))-1);
                        changed = TRUE;
                    }
                    if (ContBtnDown[mgmode_padNo] & R_JPAD) {
                        HuAudFXPlay(1);
                        HuWinExAnimOut(mgmode_winId, 0);
                        mgmode_CursorMoveTimeSet(20);
                        mgmode_CursorSelMove(0);
                        mgmode_CameraPresetMove(5, 20, 1, (void (*)(s16 *))-1);
                        changed = TRUE;
                    }
                    if (changed) {
                        HuWinMesSet(mgmode_winId, 0x5600, -1, -1);
                        HuWinExAnimIn(mgmode_winId);
                    }
                }
                break;
        }
        if (Hu3DData[mgmode_mdlTbl[4]].motId != mgmode_motTbl5 &&
            Hu3DData[mgmode_mdlTbl[4]].motIdShift != mgmode_motTbl5) {
            Hu3DMotionShiftSet(mgmode_mdlTbl[4], mgmode_motTbl5, 0, 8, 2);
        }
    }
}

void mgmode_BattleEnterExec(void) {
    HuWinMesSet(mgmode_winId, 0x5607, -1, -1);
    while (HuWinStatGet(mgmode_winId) != 0) {
        HuPrcVSleep();
    }
    mgmode_CameraPresetMove(2, 10, 1, (void (*)(s16 *))-1);
    mgmode_BattleSetupExec();
    mgmode_CameraPresetMove(5, 10, 1, (void (*)(s16 *))-1);
    mgmode_CursorPosTblSet(mgmode_battleCursorPosTbl);
    mgmode_CursorSelSet(0);
    mgmode_CursorDispSet(1);
    HuWinMesSet(mgmode_winId, 0x5600, -1, -1);
    while (HuWinStatGet(mgmode_winId) != 0) {
        HuPrcVSleep();
    }
}

void mgmode_BattleSetupExec(void) {
    s16 i;
    s16 state;
    s16 back;
    s16 result;
    f32 t;
    f32 sx;
    f32 sy;

    HuPrcSleep(3);
    mgmode_battleMenuSprTbl = mgmode_SprListCreate(mgmode_battleMenuSprDefTbl);
    mgmode_SprListPosSet(mgmode_battleMenuSprTbl, 0, 180, 110);
    for (i = 0; i < 9; i++) {
        mgmode_SprListDispOff(mgmode_battleMenuSprTbl, i);
        mgmode_SprListAttrSet(mgmode_battleMenuSprTbl, i, 0x4000);
    }
    HuAudFXPlay(0x243);
    HuPrcSleep(5);
    mgmode_SprListDispOn(mgmode_battleMenuSprTbl, 0);
    for (i = 0; i < 11; i++) {
        t = i / 10.0f;
        sx = sindf(t * 90.0f);
        sy = cosdf(t * 270.0f + 90.0f);
        if (sy < 0.0f) {
            sy = -sy;
        }
        mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, 0, sx, sy);
        HuPrcVSleep();
    }
    for (i = 0, mgmode_battleTypeNum = 0; i < 5; i++) {
        if (mgmode_typeUnlockNumTbl[i] >= 3) {
            mgmode_battleTypeTbl[mgmode_battleTypeNum] = i;
            mgmode_battleTypeNum++;
        }
    }
    mgModeMgListIdx = 0;
    state = 0;
    back = 0;
    while (state != 4) {
        switch (state) {
            case 0:
                mgModeSelNo = mgmode_BattleGoalChoice(back);
                if (mgModeSelNo == -1) {
                    mgmode_BattleGoalHide();
                    state = 4;
                } else {
                    back = 0;
                    state++;
                }
                break;
            case 1:
                result = mgmode_BattleTypeChoice(back);
                if (result == -1) {
                    mgmode_BattleTypeHide();
                    back = 1;
                    state--;
                } else {
                    mgModeType = mgmode_battleTypeTbl[result];
                    if (mgModeType != 1 && mgModeType != 2) {
                        for (i = 0; i < 4; i++) {
                            GwPlayer[i].group = i;
                        }
                        state++;
                    }
                    state++;
                }
                break;
            case 2:
                HuWinMesSet(mgmode_winId, 0x560A, -1, -1);
                while (HuWinStatGet(mgmode_winId) != 0) {
                    HuPrcVSleep();
                }
                result = mgmode_TeamChoice(mgModeType);
                mgmode_TeamChoiceKill();
                if (result != 0) {
                    state++;
                } else {
                    back = 1;
                    state--;
                }
                break;
            case 3:
                for (i = 0; i < 4; i++) {
                    mgModeGroupBak[i] = GwPlayer[i].group;
                }
                mgmode_BattlePlayerEnterExec(mgModeType);
                mgmode_BattleMgListShuffle();
                HuWinMesSet(mgmode_winId, 0x560B, -1, -1);
                while (HuWinStatGet(mgmode_winId) != 0) {
                    HuPrcVSleep();
                }
                mgModeMgNo = mgmode_BattleMgRouletteExec(mgModeType);
                HuPrcSleep(20);
                HuWinInsertMesSet(mgmode_winId, mgModeMgNo + 0x4700, 0);
                HuWinMesSet(mgmode_winId, 0x560D, -1, -1);
                while (HuWinStatGet(mgmode_winId) != 0) {
                    HuPrcVSleep();
                }
                HuWinMesSet(mgmode_winId, 0x560E, -1, -1);
                while (HuWinStatGet(mgmode_winId) != 0) {
                    HuPrcVSleep();
                }
                result = HuWinChoiceGet(mgmode_winId, 0, 0);
                if (result == -1) {
                    mgmode_BattlePlayerExitExec(mgModeType);
                    mgmode_MgPicKill();
                    mgmode_battleMgPicSpr = -1;
                    state -= 2;
                    if (mgModeType == 1 || mgModeType == 2) {
                        state++;
                    }
                    break;
                }
                if (result == 0) {
                    GwSystem.show_minigame_explanations = 1;
                } else {
                    GwSystem.show_minigame_explanations = 0;
                }
                _SetFlag(0xD);
                for (i = 0; i < 4; i++) {
                    mgModeStar[i] = 0;
                }
                GwSystem.minigame_index = (u8)mgModeMgNo + 1;
                mgModeCoinRate = 100;
                omOvlHisChg(0, 0x69, 4, 0x84);
                mgmode_exitF = 1;
                mgmode_exitOvlNo = 0x70;
                mgmode_exitEvtNo = 0;
                mgmode_exitMode = 2;
                if (mgModeType == 0 || mgModeType == 3) {
                    for (i = 0; i < 4; i++) {
                        GwPlayer[i].star = mgModeStar[i];
                        GwPlayer[i].coin = rand8() & 0xF;
                    }
                }
                while (TRUE) {
                    HuPrcVSleep();
                }
        }
    }
    mgmode_BattleMenuClose();
    mgmode_MgPicKill();
    mgmode_battleMgPicSpr = -1;
    mgmode_CursorDispSet(0);
    mgmode_SprListKill(mgmode_battleMenuSprTbl);
}

void mgmode_BattleMenuClose(void) {
    s16 i;
    f32 scale;

    HuAudFXPlay(0x244);
    for (i = 0; i < 11; i++) {
        scale = cosdf(i / 10.0f * 90.0f);
        mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, 0, scale, scale);
        HuPrcVSleep();
    }
}

s16 mgmode_BattleGoalChoice(s32 arg0) {
    s16 i;
    s16 j;
    s16 frame;
    s16 next;
    s16 sel;
    f32 dist;

    if (arg0 != 0) {
        for (i = 1; i < 6; i++) {
            mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, mgModeSelNo + 1, 1.0f, cosdf(i / 5.0f * 90.0f));
            HuPrcVSleep();
        }
        mgmode_SprListDispOff(mgmode_battleMenuSprTbl, mgModeSelNo + 1);
    }
    HuWinMesSet(mgmode_winId, 0x5608, -1, -1);
    while (HuWinStatGet(mgmode_winId) != 0) {
        HuPrcVSleep();
    }
    mgmode_SprListPosSet(mgmode_battleMenuSprTbl, 1, 180, 91);
    mgmode_SprListPosSet(mgmode_battleMenuSprTbl, 2, 180, 121);
    mgmode_SprListPosSet(mgmode_battleMenuSprTbl, 3, 180, 151);
    for (i = 1; i < 15; i++) {
        for (j = 0; j < 3; j++) {
            frame = i - j * 3;
            if (frame < 0) {
                mgmode_SprListDispOff(mgmode_battleMenuSprTbl, j + 1);
            } else if (frame < 9) {
                mgmode_SprListDispOn(mgmode_battleMenuSprTbl, j + 1);
                mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, j + 1, 1.0f, sindf(frame / 8.0f * 90.0f));
            }
        }
        HuPrcVSleep();
    }
    sel = 0;
    mgmode_CursorPosTblSet(mgmode_battleGoalCursorPosTbl);
    mgmode_CursorSelSet(0);
    mgmode_CursorMoveTimeSet(5);
    mgmode_CursorDispSet(1);
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
            sel = next;
        } else if (HuPadBtnDown[mgmode_padNo] & A_BUTTON) {
            HuAudFXPlay(2);
            dist = 47 - mgmode_battleGoalPosYTbl[sel];
            for (i = 1; i < 6; i++) {
                for (j = 0; j < 3; j++) {
                    if (j == sel) {
                        mgmode_SprListPosSet(mgmode_battleMenuSprTbl, sel + 1, 180,
                                             mgmode_battleGoalPosYTbl[j] + dist * sindf(i / 5.0f * 90.0f));
                    } else {
                        mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, j + 1, 1.0f, cosdf(i / 5.0f * 90.0f));
                    }
                }
                HuPrcVSleep();
            }
            mgmode_SprListDispOff(mgmode_battleMenuSprTbl, 1);
            mgmode_SprListDispOff(mgmode_battleMenuSprTbl, 2);
            mgmode_SprListDispOff(mgmode_battleMenuSprTbl, 3);
            mgmode_SprListDispOn(mgmode_battleMenuSprTbl, sel + 1);
            break;
        } else if (HuPadBtnDown[mgmode_padNo] & B_BUTTON) {
            HuAudFXPlay(4);
            sel = -1;
            break;
        }
    }
    mgmode_CursorDispSet(0);
    HuPrcSleep(5);
    return sel;
}

void mgmode_BattleGoalHide(void) {
    s16 i;
    s16 j;
    s16 frame;

    for (i = 1; i < 15; i++) {
        for (j = 0; j < 3; j++) {
            frame = i - (2 - j) * 3;
            if (frame < 0) {
                continue;
            }
            if (frame >= 9) {
                mgmode_SprListDispOff(mgmode_battleMenuSprTbl, j + 1);
            } else {
                mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, j + 1, 1.0f, cosdf(frame / 8.0f * 90.0f));
            }
        }
        HuPrcVSleep();
    }
}

s16 mgmode_BattleTypeChoice(s32 arg0) {
    s16 i;
    s16 j;
    s16 frame;
    s16 next;
    s16 sel;
    f32 dist;

    if (arg0 != 0) {
        for (i = 1; i < 6; i++) {
            mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, mgModeType + 4, 1.0f, cosdf(i / 5.0f * 90.0f));
            HuPrcVSleep();
        }
        mgmode_SprListDispOff(mgmode_battleMenuSprTbl, mgModeType + 4);
    }
    HuWinMesSet(mgmode_winId, 0x5609, -1, -1);
    while (HuWinStatGet(mgmode_winId) != 0) {
        HuPrcVSleep();
    }
    for (i = 1; i <= mgmode_battleTypeNum * 3 + 8; i++) {
        for (j = 0; j < mgmode_battleTypeNum; j++) {
            mgmode_SprListPosSet(mgmode_battleMenuSprTbl, mgmode_battleTypeTbl[j] + 4, 180, j * 22 + 79);
            frame = i - j * 3;
            if (frame < 0) {
                mgmode_SprListDispOff(mgmode_battleMenuSprTbl, mgmode_battleTypeTbl[j] + 4);
            } else if (frame < 9) {
                mgmode_SprListDispOn(mgmode_battleMenuSprTbl, mgmode_battleTypeTbl[j] + 4);
                mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, mgmode_battleTypeTbl[j] + 4, 1.0f,
                                     sindf(frame / 8.0f * 90.0f));
            }
        }
        HuPrcVSleep();
    }
    for (j = 0; j < mgmode_battleTypeNum; j++) {
        mgmode_battleTypeCursorTbl[j] = mgmode_battleTypeCursorPosTbl[j];
    }
    mgmode_battleTypeCursorTbl[j].x = mgmode_battleTypeCursorTbl[j].y = -1;
    sel = 0;
    mgmode_CursorPosTblSet(mgmode_battleTypeCursorTbl);
    mgmode_CursorSelSet(0);
    mgmode_CursorMoveTimeSet(5);
    mgmode_CursorDispSet(1);
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
            sel = next;
        } else if (HuPadBtnDown[mgmode_padNo] & A_BUTTON) {
            HuAudFXPlay(2);
            dist = -9 - sel * 22;
            for (i = 1; i < 6; i++) {
                for (j = 0; j < mgmode_battleTypeNum; j++) {
                    if (j == sel) {
                        mgmode_SprListPosSet(mgmode_battleMenuSprTbl, mgmode_battleTypeTbl[j] + 4, 180,
                                             j * 22 + 79 + dist * sindf(i / 5.0f * 90.0f));
                    } else {
                        mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, mgmode_battleTypeTbl[j] + 4, 1.0f,
                                             cosdf(i / 5.0f * 90.0f));
                    }
                }
                HuPrcVSleep();
            }
            for (j = 0; j < 5; j++) {
                mgmode_SprListDispOff(mgmode_battleMenuSprTbl, mgmode_battleTypeTbl[j] + 4);
            }
            mgmode_SprListDispOn(mgmode_battleMenuSprTbl, mgmode_battleTypeTbl[sel] + 4);
            break;
        } else if (HuPadBtnDown[mgmode_padNo] & B_BUTTON) {
            HuAudFXPlay(4);
            sel = -1;
            break;
        }
    }
    mgmode_CursorDispSet(0);
    HuPrcSleep(5);
    return sel;
}

void mgmode_BattleMgListShuffle(void) {
    s16 list[20];
    s16 count;
    s16 i;
    s16 j;
    s16 r;
    s16 tmp;
    s16 category;

    category = mgModeType;
    count = 0;
    for (i = 0; i < mgmode_typeMgNumTbl[category]; i++) {
        if (mgmode_typeMgTbl[category][i] != 0xFF) {
            list[count++] = mgmode_typeMgTbl[category][i];
        }
    }
    for (i = 0; i < count * 2; i++) {
        j = i % count;
        r = (rand8() * count) >> 8;
        tmp = list[j];
        list[j] = list[r];
        list[r] = tmp;
    }
    for (i = 0; i < mgmode_typeUnlockNumTbl[category]; i++) {
        mgModeMgList[i] = list[i];
    }
}

void mgmode_BattleTypeHide(void) {
    s16 i;

    for (i = 0; i < mgmode_battleTypeNum; i++) {
        mgmode_SprListDispOff(mgmode_battleMenuSprTbl, mgmode_battleTypeTbl[i] + 4);
    }
}

void mgmode_BattlePlayerPosSet(s16 arg0) {
    Vec pos[4];
    s16 order[4];
    s16 count;
    s16 i;
    s16 slot;
    s16 rank;

    count = (arg0 != 4) ? 4 : 2;
    for (i = 0; i < count; i++) {
        order[i] = mgModeGroupBak[i];
    }
    // count is 2 or 4, so slot starts at 0; this form keeps rank's copy of slot (matches).
    for (slot = (count & 1) * 2, rank = slot; rank < count || slot < count; rank++) {
        for (i = 0; i < count; i++) {
            if (rank == order[i]) {
                pos[i].x = slot * 80 - 122;
                pos[i].y = 26.0f;
                pos[i].z = -312.0f;
                order[i] = -1;
                slot++;
            }
        }
    }
    for (i = 0; i < count; i++) {
        Hu3DModelAttrSet(mgmode_mdlTbl7[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(mgmode_mdlTbl7[i], pos[i].x, pos[i].y, pos[i].z);
        Hu3DModelAttrSet(mgmode_mdlTbl32[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(mgmode_mdlTbl32[i], pos[i].x, pos[i].y, pos[i].z);
    }
}

void mgmode_BattlePlayerEnterExec(s16 arg0) {
    Vec pos[4];
    Vec delta[4];
    s16 order[4];
    f32 angle[4];
    s16 count;
    HmfMotionNode *node;
    s16 i;
    s16 j;
    s16 slot;
    s16 rank;
    s16 model;
    f32 t;
    f32 rot;

    rot = 0.0f;
    count = (arg0 != 4) ? 4 : 2;
    for (i = 0; i < count; i++) {
        order[i] = mgModeGroupBak[i];
    }
    // count is 2 or 4, so slot starts at 0; this form keeps rank's copy of slot (matches).
    for (slot = (count & 1) * 2, rank = slot; rank < count || slot < count; rank++) {
        for (i = 0; i < count; i++) {
            if (rank == order[i]) {
                pos[i].x = slot * 80 - 122;
                pos[i].y = 26.0f;
                pos[i].z = -312.0f;
                order[i] = -1;
                slot++;
            }
        }
    }
    for (i = 0; i < count; i++) {
        delta[i].x = 400.0f - pos[i].x;
        delta[i].z = 900.0f - pos[i].z;
        Hu3DModelAttrSet(mgmode_mdlTbl[i + 7], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionSet(mgmode_mdlTbl[i + 7], mgmode_motTbl11[i]);
        Hu3DMotionAttrSet(mgmode_mdlTbl[i + 7], 2, 2);
        Hu3DModelAttrSet(mgmode_mdlTbl[i + 32], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        angle[i] = atan2df(delta[i].x, delta[i].z) + 180.0f;
        Hu3DModelRotSet(mgmode_mdlTbl[i + 7], 0.0f, angle[i], 0.0f);
    }
    model = mgmode_mdlTbl[4];
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, "c100_1-atama", 0x4C, 0x46);
    node = Hu3DModelObjPtrGet(model, "c100_1-atama");
    for (j = 0; j < 31; j++) {
        t = 1.0f - sindf(j * 3.0f);
        for (i = 0; i < count; i++) {
            Hu3DModelPosSet(mgmode_mdlTbl[i + 7], pos[i].x + t * delta[i].x, pos[i].y, pos[i].z + t * delta[i].x);
            mgmode_MdlPosCopy(mgmode_mdlTbl[i + 32], mgmode_mdlTbl[i + 7]);
            if (j < 25 && j % 5 == 0) {
                _HuAudPlayerFXPlay(GwPlayer[i].chr + 0x29, i);
            }
        }
        if (j < 10) {
            rot = atan2df(Hu3DData[mgmode_mdlTbl[7]].pos.x - Hu3DData[mgmode_mdlTbl[4]].pos.x,
                          Hu3DData[mgmode_mdlTbl[7]].pos.z - Hu3DData[mgmode_mdlTbl[4]].pos.z) -
                  Hu3DData[mgmode_mdlTbl[4]].rot.y;
            rot *= j / 10.0f;
        } else if (j < 20) {
            rot = atan2df(Hu3DData[mgmode_mdlTbl[7]].pos.x - Hu3DData[mgmode_mdlTbl[4]].pos.x,
                          Hu3DData[mgmode_mdlTbl[7]].pos.z - Hu3DData[mgmode_mdlTbl[4]].pos.z) -
                  Hu3DData[mgmode_mdlTbl[4]].rot.y;
        } else {
            rot -= 5.0f;
        }
        node->baseRot.y = node->rot.y = rot;
        HuPrcVSleep();
    }
    for (i = 0; i < count; i++) {
        Hu3DMotionShiftSet(mgmode_mdlTbl7[i], mgmode_motTbl7[i], 0, 8, 2);
    }
    for (j = 0; j < 9; j++) {
        t = 1.0f - j / 8.0f;
        for (i = 0; i < count; i++) {
            Hu3DModelRotSet(mgmode_mdlTbl7[i], 0.0f, t * angle[i], 0.0f);
        }
        rot -= 5.0f;
        if (rot < 0.0f) {
            rot = 0.0f;
        }
        node->baseRot.y = node->rot.y = rot;
        HuPrcVSleep();
    }
}

void mgmode_BattlePlayerExitExec(s16 arg0) {
    Vec pos[4];
    Vec delta[4];
    f32 angle[4];
    s16 count;
    s16 i;
    s16 j;
    f32 t;

    count = (arg0 != 4) ? 4 : 2;
    for (i = 0; i < count; i++) {
        pos[i].x = Hu3DData[mgmode_mdlTbl[i + 7]].pos.x;
        pos[i].y = Hu3DData[mgmode_mdlTbl[i + 7]].pos.y;
        pos[i].z = Hu3DData[mgmode_mdlTbl[i + 7]].pos.z;
        delta[i].x = 400.0f - pos[i].x;
        delta[i].z = 900.0f - pos[i].z;
        Hu3DModelAttrSet(mgmode_mdlTbl[i + 7], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionShiftSet(mgmode_mdlTbl[i + 7], mgmode_motTbl11[i], 0, 8, 2);
        angle[i] = atan2df(delta[i].x, delta[i].z);
    }
    for (j = 0; j < 9; j++) {
        t = j / 8.0f;
        for (i = 0; i < count; i++) {
            Hu3DModelRotSet(mgmode_mdlTbl[i + 7], 0.0f, t * angle[i], 0.0f);
        }
        HuPrcVSleep();
    }
    for (j = 0; j < 31; j++) {
        if (j == 10) {
            Hu3DMotionShiftSet(mgmode_mdlTbl[4], mgmode_motTbl6, 0, 8, 2);
        }
        t = 1.0f - sindf(j / 30.0f * 90.0f + 90.0f);
        for (i = 0; i < count; i++) {
            Hu3DModelPosSet(mgmode_mdlTbl[i + 7], pos[i].x + t * delta[i].x, pos[i].y, pos[i].z + t * delta[i].z);
            mgmode_MdlPosCopy(mgmode_mdlTbl[i + 32], mgmode_mdlTbl[i + 7]);
            if (j < 25 && j % 5 == 0) {
                _HuAudPlayerFXPlay(GwPlayer[i].chr + 0x29, i);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < count; i++) {
        Hu3DModelAttrSet(mgmode_mdlTbl[i + 7], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(mgmode_mdlTbl[i + 32], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    Hu3DMotionShiftSet(mgmode_mdlTbl[4], mgmode_motTbl4, 0, 8, 2);
}

s16 mgmode_BattleMgRouletteExec(s16 category) {
    s16 list[32];
    s16 count;
    s16 i;
    s16 idx;
    s16 prev;

    if (mgmode_battleMgPicSpr == -1) {
        mgmode_battleMgPicSpr = mgmode_MgPicCreate();
        espAttrSet(mgmode_battleMgPicSpr, 0x4008);
        espPosSet(mgmode_battleMgPicSpr, 180, 134);
        for (i = 0; i < 10; i++) {
            espTPLvlSet(mgmode_battleMgPicSpr, i / 10.0f * 255.0f);
            HuPrcVSleep();
        }
    }
    count = 0;
    for (i = 0; i < mgmode_typeMgNumTbl[category]; i++) {
        if (mgmode_typeMgTbl[category][i] != 0xFF) {
            list[count++] = mgmode_typeMgTbl[category][i];
        }
    }
    prev = -1;
    idx = (rand8() * count) >> 8;
    mgmode_MgPicLoad(mgDataTbl[list[idx]].flags & 0x7FF);
    for (i = 0; i < 30; i++) {
        HuPrcVSleep();
        if (idx == prev) {
            do {
                idx = (rand8() * count) >> 8;
            } while (idx == prev);
            prev = idx;
        } else {
            prev = idx;
        }
        mgmode_MgPicLoad(mgDataTbl[list[idx]].flags & 0x7FF);
        HuAudFXPlay(0x104);
    }
    HuPrcVSleep();
    prev = mgModeMgList[mgModeMgListIdx];
    mgmode_MgPicLoad(mgDataTbl[prev].flags & 0x7FF);
    HuPrcVSleep();
    HuAudFXPlay(0x105);
    return prev;
}

s32 mgmode_BattleResultExec(void) {
    s16 i;
    s16 mesId;
    s16 choice;
    s16 count;

    mgModeMgListIdx++;
    if (mgmode_typeUnlockNumTbl[mgModeType] <= mgModeMgListIdx) {
        mgModeMgListIdx = 0;
    }
    mgmode_CameraPresetSet(2);
    mgmode_BattlePlayerPosSet(mgModeType);
    mgmode_battleMenuSprTbl = mgmode_SprListCreate(mgmode_battleMenuSprDefTbl);
    mgmode_SprListPosSet(mgmode_battleMenuSprTbl, 0, 180, 110);
    for (i = 0; i < 9; i++) {
        if (i != 0) {
            mgmode_SprListDispOff(mgmode_battleMenuSprTbl, i);
        }
        mgmode_SprListAttrSet(mgmode_battleMenuSprTbl, i, 0x4000);
    }
    mgmode_SprListDispOn(mgmode_battleMenuSprTbl, mgModeSelNo + 1);
    mgmode_SprListPosSet(mgmode_battleMenuSprTbl, mgModeSelNo + 1, 180, 42);
    mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, mgModeSelNo + 1, 0.7f, 0.7f);
    mgmode_SprListAttrSet(mgmode_battleMenuSprTbl, mgModeSelNo + 1, 8);
    mgmode_SprListDispOn(mgmode_battleMenuSprTbl, mgModeType + 4);
    mgmode_SprListPosSet(mgmode_battleMenuSprTbl, mgModeType + 4, 180, 59);
    mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, mgModeType + 4, 0.7f, 0.7f);
    mgmode_SprListAttrSet(mgmode_battleMenuSprTbl, mgModeType + 4, 8);
    mgmode_battleMgPicSpr = mgmode_MgPicCreate();
    espAttrSet(mgmode_battleMgPicSpr, 0x4008);
    espPosSet(mgmode_battleMgPicSpr, 180, 134);
    mgmode_MgPicLoad(mgDataTbl[mgModeMgNo].flags & 0x7FF);
    WipeCreateIn(WIPE_FADE, 0xA);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    mgmode_BattleBoardCreate();
    count = mgmode_BattleStarPlayerGet(mgModeMgNo);
    for (i = 0; i < count; i++) {
        HuWinInsertMesSet(mgmode_winId, GwPlayer[mgmode_starPlayerTbl[i]].chr + 0x1C00, i);
        Hu3DMotionShiftSet(mgmode_mdlTbl7[mgmode_starPlayerTbl[i]], mgmode_motTbl15[mgmode_starPlayerTbl[i]], 0, 8, 0);
        HuAudCharVoicePlay((mgmode_chrVoiceTbl[GwPlayer[mgmode_starPlayerTbl[i]].chr] << 16) | 0x33);
    }
    for (i = 0; i < 4; i++) {
        if (Hu3DData[mgmode_mdlTbl7[i]].motIdShift == 0xFF) {
            Hu3DMotionShiftSet(mgmode_mdlTbl7[i], mgmode_motTbl19[i], 0, 8, 0);
        }
    }
    switch (count) {
        case 0:
            HuWinMesSet(mgmode_winId, 0x5613, -1, -1);
            break;
        case 1:
            HuWinMesSet(mgmode_winId, 0x560F, -1, -1);
            break;
        case 2:
            HuWinMesSet(mgmode_winId, 0x5610, -1, -1);
            break;
        case 3:
            HuWinMesSet(mgmode_winId, 0x5611, -1, -1);
            break;
        case 4:
            HuWinMesSet(mgmode_winId, 0x5612, -1, -1);
            break;
    }
    HuWinExAnimIn(mgmode_winId);
    if (mgmode_BattleStarAdd()) {
        for (i = 0; i < mgmode_starPlayerNum; i++) {
            HuWinInsertMesSet(mgmode_winId, GwPlayer[mgmode_starPlayerTbl[i]].chr + 0x1C00, i);
        }
        switch (mgmode_starPlayerNum) {
            case 1:
                HuWinMesSet(mgmode_winId, 0x5614, -1, -1);
                break;
            case 2:
                HuWinMesSet(mgmode_winId, 0x5615, -1, -1);
                break;
            case 3:
                HuWinMesSet(mgmode_winId, 0x5616, -1, -1);
                break;
            case 4:
                HuWinMesSet(mgmode_winId, 0x5617, -1, -1);
                break;
        }
        while (HuWinStatGet(mgmode_winId) != 0) {
            HuPrcVSleep();
        }
        HuWinExAnimOut(mgmode_winId, 0);
        if (mgmode_starPlayerNum != 4) {
            for (i = 0; i < mgmode_starPlayerNum; i++) {
                Hu3DMotionShiftSet(mgmode_mdlTbl7[mgmode_starPlayerTbl[i]], mgmode_motTbl23[mgmode_starPlayerTbl[i]], 0, 8, 0);
                _HuAudPlayerFXPlay(GwPlayer[mgmode_starPlayerTbl[i]].chr + 0x27E, i);
            }
            HuAudFXPlay(0x248);
            mgmode_BattleConfettiSet(1);
        }
        for (i = 0; i < 4; i++) {
            if (Hu3DData[mgmode_mdlTbl7[i]].motIdShift == 0xFF) {
                Hu3DMotionShiftSet(mgmode_mdlTbl7[i], mgmode_motTbl27[i], 0, 8, 0);
            }
        }
        mesId = -1;
        switch (mgmode_starPlayerNum) {
            case 1:
                mesId = GMesCreate(0x16, GwPlayer[mgmode_starPlayerTbl[0]].chr);
                GMesPosSet(mesId, 160.0f, 120.0f);
                break;
            case 2:
                mesId = GMesCreate(0x1E, GwPlayer[mgmode_starPlayerTbl[0]].chr, GwPlayer[mgmode_starPlayerTbl[1]].chr);
                break;
            case 3:
                mesId = GMesCreate(0x22, GwPlayer[mgmode_starPlayerTbl[0]].chr, GwPlayer[mgmode_starPlayerTbl[1]].chr,
                                   GwPlayer[mgmode_starPlayerTbl[2]].chr);
                break;
            case 4:
                GMesCreate(0x20);
                mesId = -1;
                break;
        }
        if (mesId != -1) {
            while (!(GMesStatGet() & GMES_STAT_TIMEEND)) {
                HuPrcVSleep();
            }
        }
        for (i = 0; i < 60; i++) {
            if (HuPadBtnDown[0] & (A_BUTTON | B_BUTTON)) {
                break;
            }
            HuPrcVSleep();
        }
        mgmode_BattleConfettiSet(0);
        HuWinExAnimIn(mgmode_winId);
        HuWinMesSet(mgmode_winId, 0x5618, -1, -1);
        while (HuWinStatGet(mgmode_winId) != 0) {
            HuPrcVSleep();
        }
        choice = (s16)HuWinChoiceGet(mgmode_winId, 0, 0) == 0;
        if (mesId != -1) {
            GMesKill(mesId);
        }
        mgmode_BattleBoardKill();
        HuWinExAnimOut(mgmode_winId, 0);
        HuAudSeqFadeOut(60);
        mgmode_BattlePlayerExitExec(mgModeType);
        mgmode_BattleTypeTitleClose();
        mgmode_BattleGoalTitleClose();
        mgmode_MgPicKill();
        mgmode_battleMgPicSpr = -1;
        mgmode_BattleMenuClose();
        mgmode_SprListKill(mgmode_battleMenuSprTbl);
        return choice;
    }
    for (i = 0; i < 90; i++) {
        if (HuPadBtnDown[0] & (A_BUTTON | B_BUTTON)) {
            break;
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        Hu3DMotionShiftSet(mgmode_mdlTbl7[i], mgmode_motTbl7[i], 0, 8, 2);
    }
    HuWinMesSet(mgmode_winId, 0x560C, -1, -1);
    HuPrcSleep(10);
    mgmode_BattleBoardKill();
    mgModeMgNo = mgmode_BattleMgRouletteExec(mgModeType);
    HuPrcSleep(20);
    HuWinInsertMesSet(mgmode_winId, mgModeMgNo + 0x4700, 0);
    HuWinMesSet(mgmode_winId, 0x560D, -1, -1);
    while (HuWinStatGet(mgmode_winId) != 0) {
        HuPrcVSleep();
    }
    while (TRUE) {
        HuWinMesSet(mgmode_winId, 0x560E, -1, -1);
        while (HuWinStatGet(mgmode_winId) != 0) {
            HuPrcVSleep();
        }
        choice = HuWinChoiceGet(mgmode_winId, 0, 0);
        if (choice != -1) {
            break;
        }
        HuWinMesSet(mgmode_winId, 0x5619, -1, -1);
        while (HuWinStatGet(mgmode_winId) != 0) {
            HuPrcVSleep();
        }
        if ((s16)HuWinChoiceGet(mgmode_winId, 0, 0) == 0) {
            mgmode_BattlePlayerExitExec(mgModeType);
            HuWinExAnimOut(mgmode_winId, 0);
            mgmode_BattleTypeTitleClose();
            mgmode_BattleGoalTitleClose();
            mgmode_MgPicKill();
            mgmode_battleMgPicSpr = -1;
            mgmode_BattleMenuClose();
            mgmode_SprListKill(mgmode_battleMenuSprTbl);
            return 0;
        }
    }
    if (choice == 0) {
        GwSystem.show_minigame_explanations = 1;
    } else {
        GwSystem.show_minigame_explanations = 0;
    }
    _SetFlag(0xD);
    for (i = 0; i < 4; i++) {
        GwPlayer[i].group = mgModeGroupBak[i];
    }
    GwSystem.minigame_index = (u8)mgModeMgNo + 1;
    omOvlHisChg(0, 0x69, 4, 0x84);
    mgmode_exitF = 1;
    mgmode_exitOvlNo = 0x70;
    mgmode_exitEvtNo = 0;
    mgmode_exitMode = 2;
    if (mgModeType == 0 || mgModeType == 3) {
        for (i = 0; i < 4; i++) {
            GwPlayer[i].star = mgModeStar[i];
            GwPlayer[i].coin = rand8() & 0xF;
        }
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

s16 mgmode_BattleStarPlayerGet(s16 mgIndex) {
    s16 i;

    mgmode_starPlayerNum = 0;
    if (mgDataTbl[mgIndex].minigameType != MINIGAME_ITEM) {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].bonusCoin + GwPlayer[i].gameCoin >= 10) {
                mgmode_starPlayerTbl[mgmode_starPlayerNum] = i;
                mgmode_starPlayerNum++;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].bonusCoin == 0) {
                mgmode_starPlayerTbl[mgmode_starPlayerNum] = i;
                mgmode_starPlayerNum++;
            }
        }
    }
    return mgmode_starPlayerNum;
}

void mgmode_BattleBoardCreate(void) {
    s16 chars[4];
    s16 counts[8]; // Only 2 entries used, but the size matches the original stack frame.
    MgmodeEspriteDef *def;
    u16 sprite;
    s16 i;
    s16 j;
    s16 y;
    f32 scaleX;

    mgmode_battleStarAnim = HuSprAnimDataRead(0x12002C);
    for (i = 0; i < 28; i++) {
        sprite = mgmode_battleStarSprTbl[i] = espEntry(mgmode_battleStarAnim, 0, 1);
        espDispOff(sprite);
        espAttrSet(sprite, 0x4008);
        espPriSet(sprite, 8);
    }
    mgmode_battleStarSprNum = 0;
    def = &mgmode_battleBoardSprDefTbl[1];
    mgmode_battleBoardSprDefTbl[0].x = 180;
    mgmode_battleBoardSprDefTbl[0].y = 116;
    switch (mgModeType) {
        case 0:
        case 3:
            for (i = 0; i < 4; i++) {
                def->dataNum = mgmode_battleRowSprTbl[mgModeSelNo];
                def->x = 180;
                def->y = i * 24 + 80;
                def->attr &= 0x7FFF;
                def++;
            }
            for (i = 0; i < 4; i++) {
                chars[i] = GwPlayer[i].chr;
            }
            for (i = 0; i < 4; i++) {
                for (j = 0; j < mgModeStar[i]; j++) {
                    espDispOn(mgmode_battleStarSprTbl[mgmode_battleStarSprNum]);
                    espPosSet(mgmode_battleStarSprTbl[mgmode_battleStarSprNum], mgmode_battleStarPosXTbl[mgModeSelNo * 7 + j] + 180,
                              i * 24 + 80);
                    mgmode_battleStarSprNum++;
                }
            }
            break;
        case 1:
            for (i = 0; i < 2; i++) {
                def->dataNum = mgmode_battleRowTeamSprTbl[mgModeSelNo];
                def->x = 180;
                def->y = i * 48 + 93;
                def->attr &= 0x7FFF;
                def++;
            }
            j = 0;
            for (i = 0; i < 4; i++) {
                if (mgModeGroupBak[i] == 0) {
                    chars[j++] = GwPlayer[i].chr;
                    counts[0] = mgModeStar[i];
                }
            }
            for (i = 0; i < 4; i++) {
                if (mgModeGroupBak[i] == 1) {
                    chars[j++] = GwPlayer[i].chr;
                    counts[1] = mgModeStar[i];
                }
            }
            for (i = 0; i < 2; i++) {
                for (j = 0; j < counts[i]; j++) {
                    espDispOn(mgmode_battleStarSprTbl[mgmode_battleStarSprNum]);
                    espPosSet(mgmode_battleStarSprTbl[mgmode_battleStarSprNum], mgmode_battleStarPosXTbl[mgModeSelNo * 7 + j] + 180,
                              i * 48 + 93);
                    mgmode_battleStarSprNum++;
                }
            }
            break;
        case 2:
            def->dataNum = mgmode_battleRowSprTbl[mgModeSelNo];
            def->x = 180;
            def->y = 80;
            def->attr &= 0x7FFF;
            def++;
            def->dataNum = mgmode_battleRow3SprTbl[mgModeSelNo];
            def->x = 180;
            def->y = 128;
            def->attr &= 0x7FFF;
            j = 0;
            for (i = 0; i < 4; i++) {
                if (mgModeGroupBak[i] == 0) {
                    chars[j++] = GwPlayer[i].chr;
                    counts[0] = mgModeStar[i];
                }
            }
            for (i = 0; i < 4; i++) {
                if (mgModeGroupBak[i] == 1) {
                    chars[j++] = GwPlayer[i].chr;
                    counts[1] = mgModeStar[i];
                }
            }
            for (i = 0; i < 2; i++) {
                if (i == 0) {
                    y = 80;
                } else {
                    y = 128;
                }
                for (j = 0; j < counts[i]; j++) {
                    espDispOn(mgmode_battleStarSprTbl[mgmode_battleStarSprNum]);
                    espPosSet(mgmode_battleStarSprTbl[mgmode_battleStarSprNum], mgmode_battleStarPosXTbl[mgModeSelNo * 7 + j] + 180, y);
                    mgmode_battleStarSprNum++;
                }
            }
            break;
        case 4:
            for (i = 0; i < 2; i++) {
                def->dataNum = mgmode_battleRowSprTbl[mgModeSelNo];
                def->x = 180;
                def->y = i * 24 + 104;
                def->attr &= 0x7FFF;
                def++;
            }
            for (i = 0; i < 2; i++) {
                chars[i] = GwPlayer[i].chr;
            }
            for (i = 2; i < 4; i++) {
                chars[i] = -1;
            }
            for (i = 0; i < 2; i++) {
                for (j = 0; j < mgModeStar[i]; j++) {
                    espDispOn(mgmode_battleStarSprTbl[mgmode_battleStarSprNum]);
                    espPosSet(mgmode_battleStarSprTbl[mgmode_battleStarSprNum], mgmode_battleStarPosXTbl[mgModeSelNo * 7 + j] + 180,
                              i * 24 + 104);
                    mgmode_battleStarSprNum++;
                }
            }
            break;
    }
    def = &mgmode_battleBoardSprDefTbl[5];
    for (i = 0; i < 4; i++) {
        if (chars[i] != -1) {
            def->dataNum += chars[i];
            if (mgModeSelNo == 0) {
                def->x = 149;
            } else if (mgModeSelNo == 1) {
                def->x = 128;
            } else {
                def->x = 107;
            }
            if (mgModeType != 4) {
                def->y = i * 24 + 80;
            } else {
                def->y = i * 24 + 104;
            }
        } else {
            def->attr |= 0x8000;
        }
        def++;
    }
    mgmode_battleBoardSprTbl = mgmode_SprListCreate(mgmode_battleBoardSprDefTbl);
    mgmode_SprListTPLvlSet(mgmode_battleBoardSprTbl, 0, 0);
    if (mgModeSelNo == 0) {
        scaleX = 8.6f;
    } else if (mgModeSelNo == 1) {
        scaleX = 12.8f;
    } else {
        scaleX = 17.0f;
    }
    if (mgModeType == 4) {
        mgmode_SprListScaleSet(mgmode_battleBoardSprTbl, 0, scaleX, 4.9f);
    } else {
        mgmode_SprListScaleSet(mgmode_battleBoardSprTbl, 0, scaleX, 9.8f);
    }
    for (i = 0; i < 28; i++) {
        espScaleSet(mgmode_battleStarSprTbl[i], 0.0f, 0.0f);
    }
    for (i = 0; i < 4; i++) {
        mgmode_SprListTPLvlSet(mgmode_battleBoardSprTbl, i + 5, 0);
    }
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 4; i++) {
            mgmode_SprListTPLvlSet(mgmode_battleBoardSprTbl, i + 1, j / 5.0 * 255.0);
        }
        mgmode_SprListTPLvlSet(mgmode_battleBoardSprTbl, 0, j / 5.0 * 192.0);
        HuPrcVSleep();
    }
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 4; i++) {
            mgmode_SprListTPLvlSet(mgmode_battleBoardSprTbl, i + 5, j / 5.0 * 255.0);
        }
        for (i = 0; i < 28; i++) {
            espScaleSet(mgmode_battleStarSprTbl[i], j / 5.0, j / 5.0);
        }
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
// Only remaining diff: in the `case 4` loop, the sign-extended loop index used
// to load `player` is allocated to a0 in the target but v0 here (which also
// turns the target's `bnezl` at the loop end into `bnez`).
// The `do {} while (0);` after the sprites[count] store ends the CSE block so
// that the store and the following reads of sprites[count] use separately
// computed addresses with the sprites base hoisted into a saved register, as
// in the target (without it, everything after `case 4` is shifted).
// The index pseudo is local to the loop-top block and nothing occupies v0/v1
// there, so local-alloc picks v0; a0 suggests v0/v1 are live across it in the
// original RTL (e.g. a global pseudo). An unrotated `while` test makes the
// index global but lands it in a3 and changes the loop shape.
// Tried without success: do/while(0) at every combination of statement gaps
// and around every contiguous statement range, player temp types
// (u8/u16/s32), store before player load, count++ in the for increment,
// `continue`, while-loop form, static inline helper for the calls, using
// mgmode_starPlayerTbl[i] directly instead of player, an s32 index copy, and
// (from earlier rounds) 40 declaration orders, address casts, `j` as the
// loop variable.
// RTL dumps (-dl/-dg) confirm the index qty (sll/sra feeding the lbu) is
// local and no other qty overlaps it, so local-alloc must pick v0. Getting a0
// needs v0/v1 qtys born before the index dies, or a global index pseudo whose
// conflicts/lower-priority preferences exclude v0/v1 (e.g. live across the
// loop-bottom compare). Also tried without success: do/while with an n != 0
// pre-check, plain while, `mgmode_starPlayerTbl[i++]`, index temp (s32/s16/u8),
// `u8 *` pointer temp, `sprites[(s16)count]` / `*(sprites + count)` / pointer
// stores (CSE merges the addresses without the do/while(0)), store after the
// player load, swapping the count/mgmode_battleStarSprNum increments,
// `sprites[count++]` in espPosSet, and `mgmode_battleStarSprNum++` in the store.
s32 mgmode_BattleStarAdd(void) {
    u16 sprites[4];
    s16 i;
    s16 j;
    s16 count;
    s16 mask;
    s16 y;
    s16 player;
    f32 tpLvl;
    f32 scale;

    count = 0;
    if (mgmode_starPlayerNum == 0) {
        return 0;
    }
    switch (mgModeType) {
        case 0:
        case 3:
            for (i = 0; i < mgmode_starPlayerNum; i++) {
                player = mgmode_starPlayerTbl[i];
                sprites[i] = mgmode_battleStarSprTbl[mgmode_battleStarSprNum];
                count++;
                espDispOn(sprites[i]);
                espPosSet(sprites[i], mgmode_battleStarPosXTbl[mgModeSelNo * 7 + mgModeStar[player]] + 180,
                          player * 24 + 80);
                mgmode_battleStarSprNum++;
            }
            break;
        case 1:
            mask = 0;
            for (i = 0; i < mgmode_starPlayerNum; i++) {
                player = mgmode_starPlayerTbl[i];
                if (!((mask >> mgModeGroupBak[player]) & 1)) {
                    mask |= 1 << mgModeGroupBak[player];
                    sprites[count] = mgmode_battleStarSprTbl[mgmode_battleStarSprNum];
                    espDispOn(sprites[count]);
                    espPosSet(sprites[count], mgmode_battleStarPosXTbl[mgModeSelNo * 7 + mgModeStar[player]] + 180,
                              mgModeGroupBak[player] * 48 + 93);
                    count++;
                    mgmode_battleStarSprNum++;
                }
            }
            break;
        case 2:
            mask = 0;
            for (i = 0; i < mgmode_starPlayerNum; i++) {
                player = mgmode_starPlayerTbl[i];
                if (!((mask >> mgModeGroupBak[player]) & 1)) {
                    mask |= 1 << mgModeGroupBak[player];
                    sprites[count] = mgmode_battleStarSprTbl[mgmode_battleStarSprNum];
                    if (mgModeGroupBak[player] == 0) {
                        y = 80;
                    } else {
                        y = 128;
                    }
                    espDispOn(sprites[count]);
                    espPosSet(sprites[count], mgmode_battleStarPosXTbl[mgModeSelNo * 7 + mgModeStar[player]] + 180, y);
                    count++;
                    mgmode_battleStarSprNum++;
                }
            }
            break;
        case 4:
            for (i = 0; i < mgmode_starPlayerNum; i++) {
                player = mgmode_starPlayerTbl[i];
                sprites[count] = mgmode_battleStarSprTbl[mgmode_battleStarSprNum];
                do {
                } while (0);
                espDispOn(sprites[count]);
                espPosSet(sprites[count], mgmode_battleStarPosXTbl[mgModeSelNo * 7 + mgModeStar[player]] + 180,
                          player * 24 + 104);
                count++;
                mgmode_battleStarSprNum++;
            }
            break;
    }
    for (i = 0; i < mgmode_starPlayerNum; i++) {
        mgModeStar[mgmode_starPlayerTbl[i]]++;
    }
    for (i = 0, mgmode_starPlayerNum = 0; i < 4; i++) {
        if (mgModeStar[i] >= mgmode_battleGoalTbl[mgModeSelNo]) {
            mgmode_starPlayerTbl[mgmode_starPlayerNum] = i;
            mgmode_starPlayerNum++;
            if (!(GwPlayer[i].stat & 1)) {
                RepeatVibrator(GwPlayer[i].pad, 10, 0, 10);
            }
        }
    }
    if (mgmode_starPlayerNum != 0) {
        HuAudFXPlay(0x24B);
    } else {
        HuAudFXPlay(0x24A);
    }
    for (i = 0; i < 31; i++) {
        tpLvl = sindf(i * 3.0f) * 255.0f;
        scale = sindf(i * 5.0f) * 2;
        for (j = 0; j < count; j++) {
            espTPLvlSet(sprites[j], tpLvl);
            espScaleSet(sprites[j], scale, scale);
        }
        HuPrcVSleep();
    }
    return mgmode_starPlayerNum != 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game/overlays/mgmode/battle", mgmode_BattleStarAdd);
#endif

s32 mgmode_BattleGoalCheck(void) {
    s16 i;

    mgmode_BattleStarPlayerGet(mgModeMgNo);
    for (i = 0; i < mgmode_starPlayerNum; i++) {
        if (mgModeStar[mgmode_starPlayerTbl[i]] + 1 >= mgmode_battleGoalTbl[mgModeSelNo]) {
            return 1;
        }
    }
    return 0;
}

void mgmode_BattleBoardKill(void) {
    s16 i;
    s16 j;

    for (i = 0; i < 28; i++) {
        espScaleSet(mgmode_battleStarSprTbl[i], 0.0f, 0.0f);
    }
    for (i = 0; i < 4; i++) {
        mgmode_SprListTPLvlSet(mgmode_battleBoardSprTbl, i + 5, 0);
    }
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 4; i++) {
            mgmode_SprListTPLvlSet(mgmode_battleBoardSprTbl, i + 5, (1.0 - j / 5.0) * 255.0);
        }
        for (i = 0; i < 28; i++) {
            espScaleSet(mgmode_battleStarSprTbl[i], 1.0 - j / 5.0, 1.0 - j / 5.0);
        }
        HuPrcVSleep();
    }
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 4; i++) {
            mgmode_SprListTPLvlSet(mgmode_battleBoardSprTbl, i + 1, (1.0 - j / 5.0) * 255.0);
        }
        mgmode_SprListTPLvlSet(mgmode_battleBoardSprTbl, 0, (1.0 - j / 5.0) * 192.0);
        HuPrcVSleep();
    }
    mgmode_SprListKill(mgmode_battleBoardSprTbl);
    for (i = 0; i < 28; i++) {
        espKill(mgmode_battleStarSprTbl[i]);
    }
    HuSprAnimKill(mgmode_battleStarAnim);
}

void mgmode_BattleTypeTitleClose(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, mgModeType + 4, 0.7f, (1.0f - i / 5.0f) * 0.7f);
        HuPrcVSleep();
    }
}

void mgmode_BattleGoalTitleClose(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        mgmode_SprListScaleSet(mgmode_battleMenuSprTbl, mgModeSelNo + 1, 0.7f, (1.0f - i / 5.0f) * 0.7f);
        HuPrcVSleep();
    }
}

void mgmode_BattleConfettiSet(s32 arg0) {
    s16 order[4];
    s16 i;
    s16 j;
    s16 k;
    s16 count;

    for (j = 0; j < 4; j++) {
        order[j] = mgModeGroupBak[j];
    }

    count = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == order[j]) {
                for (k = 0; k < mgmode_starPlayerNum; k++) {
                    if (mgmode_starPlayerTbl[k] == j) {
                        break;
                    }
                }
                if (k != mgmode_starPlayerNum) {
                    if (arg0) {
                        mgmode_ConfettiOn(count);
                    } else {
                        mgmode_ConfettiOff(count);
                    }
                    order[j] = -1;
                }
                count++;
            }
        }
    }
}
