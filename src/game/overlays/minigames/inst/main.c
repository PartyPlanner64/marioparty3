#include "common.h"
#include "inst.h"

extern InstModelHooks *inst_hookTbl[][2];
extern const s32 inst_boxFileTbl[][2];
extern const s32 inst_boxFileTbl1[][2];
extern const s32 inst_frameFileTbl[];

extern const char inst_picNodeName[];
extern const char inst_frameNodeName[];
extern s32 inst_mainState;
extern s32 inst_winOpenF;
extern s32 inst_mainTimer;
extern s16 inst_mainTimerHalf;
extern s8 inst_mainDoneF;
extern s8 inst_mainUnusedF;
extern s8 inst_practiceStartF;
extern s8 inst_startF;
extern Vec inst_cameraPosTbl[4];
extern Vec inst_cameraTargetTbl[4];
extern s8 inst_practiceF;
extern u8 storySceneNo;
extern s32 inst_picNo;
extern u32 inst_cameraMoveTime;
extern f32 CFanOfs;
extern f32 CFanLen;

extern s8 inst_playerOrderTbl[4];
extern s8 inst_playerOrderTbl1[3];
extern s8 inst_playerOrderTbl2[2];
extern s8 inst_practiceRetF;
extern s8 inst_introSkipF;
extern s8 inst_mgType;
extern s8 inst_mgNo;
extern s8 inst_hostNo;
extern s8 inst_exitWipeF;
extern f32 inst_cameraTilt;
extern Vec inst_cameraPos;
extern Vec inst_cameraTarget;
extern Vec inst_cameraUp;
extern void *inst_picData;
extern void *inst_picAlpha;
extern void *inst_picHeader;
extern InstObjectState inst_boxWork;
extern s32 inst_boxOpenCnt;
extern f32 inst_picScaleOfs;
extern s32 inst_boxCloseCnt;
extern s8 inst_itemPrizeTbl[5];
extern u8 inst_itemPrizeATbl[8];
extern u8 inst_itemPrizeBTbl[8];
extern u16 mgInstColumnTbl[5];
extern u16 mgInstSlotTbl[5];


s32 MBTurnTierGet(s32);
s32 MBPlayerRankCalc(s32);

s32 inst_CameraMove(Vec *, Vec *, Vec *, Vec *, s32);
void inst_BoxMotionStart(void);
s32 inst_BoxMotionEndCheck(void);
void inst_OpenStart(void);
s32 inst_OpenDoneCheck(void);
void inst_PicPulseStart(void);
u16 inst_PadBtnDownAutoGet(u16, s16);
void inst_PracticeLabelDispOff(void);
void inst_MainObjMain(omObjData *); /* extern */
void inst_MgStart(void);        /* extern */
void inst_ExitObjMain(omObjData *); /* extern */
void inst_MesClose(void);
void inst_BackCreate(void);         /* extern */
void inst_CameraObjMain(omObjData *);  /* extern */
void inst_CameraReset(void);         /* extern */
void inst_CameraTiltCalc(Vec *, Vec *); /* extern */
void inst_ItemPrizeInit(void);         /* extern */
void inst_TeamShuffle(void);         /* extern */
void inst_PicNoSet(void);         /* extern */
void inst_BoxOpenWait(omObjData *);
void inst_BoxOpenNow(omObjData *);
void inst_BoxDestroy(void);
void inst_PicLoad(s16 model, void *imageHeader, void *imageData, u8 *alpha);
void inst_BoxMain(void); /* extern */
void inst_BoxOpenStart(omObjData *);
s32 inst_OpenCheck(void);
void inst_BoxIdle(omObjData *);
void inst_BoxClose(omObjData *);
void inst_PlayerCloseStart(void);
void inst_BoxOpen(omObjData *); /* extern */
void inst_PicPulse(omObjData *); /* extern */
void inst_HostMain(void);        /* extern */
void inst_ItemHostMain(void);        /* extern */
void inst_ItemHostWait(omObjData *); /* extern */
void inst_BattleHostMain(void);        /* extern */
void inst_PlayerMain(void);        /* extern */
void inst_WinMain(void);        /* extern */

void inst_ObjectSetup(void) {
    void (*procFunc)(void) = NULL;
    s16 var_a1 = 0;
    s16 i;
    s16 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < MB_MAX_PLAYERS; j++) {
            if (i != GwPlayer[j].group) {
                continue;
            }
            inst_playerOrderTbl[var_a1] = j;
            var_a1++;

            if (var_a1 >= 4) {
                break;
            }
        }
        if (var_a1 >= 4) {
            break;
        }
    }
    inst_mgNo = GwSystem.minigame_index - 1;
    inst_mgType = mgDataTbl[inst_mgNo].minigameType;

    if (_CheckFlag(FLAG_MG_PRACTICE) != 0) {
        inst_practiceRetF = 1;
        inst_introSkipF = 1;
    } else {
        inst_practiceRetF = 0;
        if ((GWMgUnlockCheck(inst_mgNo)) != 0) {
            inst_introSkipF = 1;
        }
    }

    GWMgUnlockSet(-1);
    _ClearFlag(0xF);
    inst_TeamShuffle();
    inst_ItemPrizeInit();
    inst_PicNoSet();

    if ((GwSystem.show_minigame_explanations == 1) || (inst_mgType == 6)) {
        inst_MgStart();
        return;
    }

    MapCollInit(1);
    omInitObjMan(0x1E, 0x1E);
    HuWinInit();
    CamSetupInit(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 15.0f, 500.0f, 8000.0f);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, inst_CameraObjMain), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DSprModelInit(0x28);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    omAddPrcObj(inst_BoxMain, 0x1001, 0x1000, 0);
    omAddPrcObj(inst_WinMain, 0x1001, 0x1000, 0);
    omAddPrcObj(inst_PlayerMain, 0x1001, 0x1000, 0);

    switch (inst_mgType) {
        case 5:
            procFunc = inst_ItemHostMain;
            inst_hostNo = 1;
            break;
        case 4:
            if (omovlhisidx <= 0) {
                break;
            }
            if (GwSystem.playMode & 2) {
                procFunc = inst_HostMain;
                inst_hostNo = 0;
                break;
            }
        case 3:
            procFunc = inst_BattleHostMain;
            inst_hostNo = 2;
            break;
        case 0:
        case 1:
        case 2:
        case 6:
        case 7:
        case 8:
        default:
            procFunc = inst_HostMain;
            inst_hostNo = 0;
            break;
    }

    omAddPrcObj(procFunc, 0x1001, 0x800, 0);
    omAddObj(0, 0, 0, -1, inst_MainObjMain);
    omAddObj(0, 0, 0, -1, inst_ExitObjMain);
    inst_BackCreate();
    inst_CameraTiltCalc(&inst_cameraPosTbl[2], &inst_cameraTargetTbl[2]);
    inst_CameraReset();
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void inst_MainObjMain(omObjData *object) {
    s32 i;

    switch (inst_mainState) {
        case 0:
            HuAudSeqPlay(0x10);
            inst_CameraReset();
            inst_mainTimer = 0;
            inst_mainUnusedF = 0;
            if (inst_introSkipF == 0) {
                inst_mainState++;
            } else {
                inst_cameraPos.x = inst_cameraPosTbl[2].x;
                inst_cameraPos.y = inst_cameraPosTbl[2].y;
                inst_cameraPos.z = inst_cameraPosTbl[2].z;
                inst_cameraTarget.x = inst_cameraTargetTbl[2].x;
                inst_cameraTarget.y = inst_cameraTargetTbl[2].y;
                inst_cameraTarget.z = inst_cameraTargetTbl[2].z;
                inst_cameraUp.x = 0.0f;
                inst_cameraUp.y = 1.0f;
                inst_cameraUp.z = -0.000001f;
                inst_mainState = 6;
            }
            break;
        case 1:
            inst_mainTimer++;
            if (inst_mainTimer >= 21) {
                inst_BoxMotionStart();
                inst_mainState += 2;
            }
            break;
        case 2:
            if (inst_CameraMove(&inst_cameraPosTbl[0], &inst_cameraPosTbl[1], &inst_cameraTargetTbl[0], &inst_cameraTargetTbl[1], 5)) {
                inst_BoxMotionStart();
                inst_mainState++;
            }
            break;
        case 3:
            if (inst_BoxMotionEndCheck()) {
                inst_OpenStart();
                inst_mainState++;
            }
            break;
        case 4:
            if ((s8)inst_OpenDoneCheck()) {
                inst_mainState++;
            }
            break;
        case 5:
            if (inst_CameraMove(&inst_cameraPosTbl[1], &inst_cameraPosTbl[2], &inst_cameraTargetTbl[1], &inst_cameraTargetTbl[2], 7)) {
                inst_PicPulseStart();
                inst_mainState++;
            }
            break;
        case 6:
            inst_mainTimer = 60;
            inst_mainState++;
            break;
        case 7:
            if (inst_winOpenF == 1) {
                inst_mainTimer--;
                if (inst_PadBtnDownAutoGet(0x1000, inst_mainTimerHalf) || inst_practiceStartF == 1) {
                    inst_mainTimer = 0;
                    switch (inst_mgType) {
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                            if (!(GwPlayer[inst_playerOrderTbl[0]].stat & 1)) {
                                omVibrate(inst_playerOrderTbl[0], 10, 0, 10);
                            }
                            break;
                        case 4:
                            for (i = 0; i < 2; i++) {
                                if (!(GwPlayer[inst_playerOrderTbl[i]].stat & 1)) {
                                    omVibrate(inst_playerOrderTbl[i], 10, 0, 10);
                                }
                            }
                            break;
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        default:
                            for (i = 0; i < 4; i++) {
                                if (!(GwPlayer[inst_playerOrderTbl[i]].stat & 1)) {
                                    omVibrate(inst_playerOrderTbl[i], 10, 0, 10);
                                }
                            }
                            break;
                    }
                    inst_PracticeLabelDispOff();
                    inst_startF = 1;
                    inst_mainState++;
                }
            }
            break;
        case 8:
            inst_mainTimer++;
            if (inst_mainTimer >= 15) {
                inst_mainDoneF = 1;
                inst_mainState++;
            }
            break;
        case 9:
            WipeColorSet(255, 255, 255);
            WipeCreateOut(WIPE_FADE, 20);
            HuAudSeqFadeOut(30);
            HuAudFXPlay(0x154);
            inst_mainState++;
            break;
        case 10:
            if (inst_CameraMove(&inst_cameraPosTbl[2], &inst_cameraPosTbl[3], &inst_cameraTargetTbl[2], &inst_cameraTargetTbl[3], 25) && !WipeStatGet()) {
                inst_MesClose();
                inst_MgStart();
            }
            break;
    }
}

void inst_MgStart(void) {
    s32 unused[6]; // Retain the original stack frame.

    omOvlCallEx(mgDataTbl[inst_mgNo].overlay, 0, 0x14);
    if (inst_practiceF == 1) {
        _SetFlag(0xF);
        return;
    }
    if (_CheckFlag(0xD) != 0) {
        goto pop_history;
    }
    switch (inst_mgType) {
        case 6:
            omOvlHisChg(1, 0x72, 0, 0x14);
            return;
        case 4:
            if (GwSystem.playMode & 2) {
                omOvlHisChg(1, 0x73, 0, 0x4010);
                return;
            }
            goto pop_history;
        case 3:
            omOvlHisChg(1, 0x74, 0, 0x12);
            return;
        case 5:
        case 7:
        case 8:
        pop_history:
            if (omovlhisidx > 0) {
                omovlhisidx--;
            }
            return;
        default:
            omOvlHisChg(1, 0x71, 0, 0x12);
            return;
    }
}

void inst_ExitObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        if (inst_exitWipeF == 0) {
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            inst_exitWipeF = 1;
        } else if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            inst_MesClose();
            omOvlReturnEx(1);
        }
    }
}

void inst_BackCreate(void) {
    static const s32 inst_backFileTbl[] = {
        0x170000, 0x170001, 0x170002, 0x170003, 0x170004,
        0x170005, 0x170005, 0x170006, 0x140067, 0,
    };
    u16 espriteSlot;

    espriteSlot = espEntry(HuSprAnimDataRead(inst_backFileTbl[inst_mgType]), 0, 0);
    espPosSet(espriteSlot, 0xA0, 0x78);
    espAttrSet(espriteSlot, HUSPR_ATTR_BG);
}

void inst_MesClose(void) {
    GameMesStub();
    HuWinAllKill();
}

s32 inst_CameraMove(Vec *startPosition, Vec *endPosition, Vec *startTarget, Vec *endTarget, s32 duration) {
    s32 done;

    inst_cameraPos.x = (endPosition->x - startPosition->x) * sindf(inst_cameraMoveTime * (90.0f / duration)) + startPosition->x;
    inst_cameraPos.y = (endPosition->y - startPosition->y) * sindf(inst_cameraMoveTime * (90.0f / duration)) + startPosition->y;
    inst_cameraPos.z = (endPosition->z - startPosition->z) * sindf(inst_cameraMoveTime * (90.0f / duration)) + startPosition->z;
    inst_cameraTarget.x = (endTarget->x - startTarget->x) * sindf(inst_cameraMoveTime * (90.0f / duration)) + startTarget->x;
    inst_cameraTarget.y = (endTarget->y - startTarget->y) * sindf(inst_cameraMoveTime * (90.0f / duration)) + startTarget->y;
    inst_cameraTarget.z = (endTarget->z - startTarget->z) * sindf(inst_cameraMoveTime * (90.0f / duration)) + startTarget->z;
    inst_cameraUp.x = 0.0f;
    inst_cameraUp.y = 1.0f;
    inst_cameraUp.z = -0.000001f;
    inst_cameraMoveTime++;
    done = 0;
    if (inst_cameraMoveTime > duration) {
        inst_cameraMoveTime = 0;
        done = 1;
    }
    return done;
}

void inst_CameraObjMain(omObjData *object) {
    CFanParam[0] = inst_cameraPos.x;
    CFanParam[1] = inst_cameraPos.z;
    CFanParam[-1] = 0.0f;
    CFanParam[2] = gCameraList->fov;
    CFanParam[3] = CFanLen;
    CFanParam[4] = CFanOfs;
    Hu3DCameraPosSetV(0, &inst_cameraPos, &inst_cameraTarget, &inst_cameraUp);
    Hu3DCamUpdateMtx(0);
}

void inst_CameraReset(void) {
    inst_cameraPos.x = inst_cameraPosTbl[1].x;
    inst_cameraPos.y = inst_cameraPosTbl[1].y;
    inst_cameraPos.z = inst_cameraPosTbl[1].z;
    inst_cameraTarget.x = inst_cameraTargetTbl[1].x;
    inst_cameraTarget.y = inst_cameraTargetTbl[1].y;
    inst_cameraTarget.z = inst_cameraTargetTbl[1].z;
    inst_cameraUp.x = 0.0f;
    inst_cameraUp.y = 1.0f;
    inst_cameraUp.z = -0.000001f;
}

void inst_CameraTiltCalc(Vec *arg0, Vec *arg1) {
    inst_cameraTilt = 90.0f - atan2df(arg0->y - arg1->y, arg0->z - arg1->z);
}

void inst_ItemPrizeInit(void) {
    static const u8 inst_itemPrizeAWeightTbl[8][5] = {
        {40, 40, 30, 20, 20},
        {20, 20, 10, 10, 10},
        {10, 10, 10, 5, 5},
        {10, 10, 12, 15, 5},
        {2, 2, 5, 10, 10},
        {10, 10, 20, 20, 20},
        {3, 5, 10, 10, 10},
        {5, 3, 3, 10, 20},
    };
    static const s8 inst_itemPrizeAColumnTbl[4][3] = {
        {0, 1, 2},
        {0, 0, 3},
        {0, 0, 4},
        {0, 0, 4},
    };
    static const u8 inst_itemPrizeBWeightTbl[8][5] = {
        {30, 30, 30, 20, 20},
        {20, 20, 10, 10, 10},
        {10, 10, 15, 10, 15},
        {10, 10, 5, 15, 15},
        {10, 10, 10, 5, 5},
        {7, 10, 15, 20, 20},
        {5, 5, 12, 10, 5},
        {8, 5, 3, 10, 20},
    };
    static const s8 inst_itemPrizeBColumnTbl[4][3] = {
        {0, 1, 2},
        {0, 0, 3},
        {0, 0, 4},
        {0, 0, 4},
    };
    static const struct {
        s8 normal[5];
        s8 replacement[4];
        s8 preferred;
    } inst_itemPrizeSlotParam = {{20, 10, 20, 30, 20}, {20, 10, 10, 20}, 40};
    static const s8 inst_chrItemPrizeTbl[12] = {10, 1, 6, 5, 8, 3, 4, 2, 0, 0, 0, 0};
    u8 weights[8];
    s8 selected[8];
    s8 i;
    s8 j;
    s8 tier;
    s8 rank;
    s8 total;
    s8 sum;
    s8 found;
    u8 random;
    u16 start;
    u8 *choices;
    s8 column;

    if (inst_mgType == 5) {
        if (_CheckFlag(0x1C)) {
            start = (u8)(rand8() & 3);
            if (rand8() & 1) {
                for (i = 0; i < 5; i++) {
                    inst_itemPrizeTbl[i] = inst_itemPrizeATbl[i + start];
                }
            } else {
                for (i = 0; i < 5; i++) {
                    inst_itemPrizeTbl[i] = inst_itemPrizeBTbl[i + start];
                }
            }
            for (i = 0; i < 5; i++) {
                mgInstColumnTbl[i] = inst_itemPrizeTbl[i];
            }
        } else if (inst_practiceRetF == 0) {
            for (i = 0; i < 8; i++) {
                selected[i] = 0;
            }
            tier = MBTurnTierGet(-1);
            rank = MBPlayerRankCalc(inst_playerOrderTbl[0]);
            if ((u8)(rand8() % 3) == 0) {
                choices = inst_itemPrizeATbl;
                column = inst_itemPrizeAColumnTbl[rank][tier];
                for (i = 0; i < 8; i++) {
                    weights[i] = inst_itemPrizeAWeightTbl[i][column];
                }
            } else {
                choices = inst_itemPrizeBTbl;
                column = inst_itemPrizeBColumnTbl[rank][tier];
                for (i = 0; i < 8; i++) {
                    weights[i] = inst_itemPrizeBWeightTbl[i][column];
                }
            }
            total = 100;
            for (j = 0; j < 5; j++) {
                random = rand8() % (total + 1);
                sum = 0;
                for (i = 0; i < 8; i++) {
                    if (selected[i] == 0) {
                        sum += weights[i];
                        if (sum >= random) {
                            selected[i] = 1;
                            total -= weights[i];
                            inst_itemPrizeTbl[j] = choices[i];
                            break;
                        }
                    }
                }
            }
            for (i = 0; i < 5; i++) {
                mgInstColumnTbl[i] = inst_itemPrizeTbl[i];
            }
            column = inst_chrItemPrizeTbl[GwPlayer[inst_playerOrderTbl[0]].chr];
            found = -1;
            for (i = 0; i < 5; i++) {
                if (column == mgInstColumnTbl[i]) {
                    found = i;
                    break;
                }
            }
            if (found >= 0) {
                for (i = 0, j = 0; i < 5; i++) {
                    if (i == found) {
                        mgInstSlotTbl[i] = inst_itemPrizeSlotParam.preferred;
                    } else {
                        mgInstSlotTbl[i] = inst_itemPrizeSlotParam.replacement[j];
                        j++;
                    }
                }
            } else {
                for (i = 0; i < 5; i++) {
                    mgInstSlotTbl[i] = inst_itemPrizeSlotParam.normal[i];
                }
            }
        } else {
            for (i = 0; i < 5; i++) {
                inst_itemPrizeTbl[i] = mgInstColumnTbl[i];
            }
        }
    }
}

void inst_TeamShuffle(void) {
    s32 i;
    s32 first;
    s32 second;
    s32 humans;
    s32 temp;

    if (inst_practiceRetF == 1) {
        return;
    }
    switch ((s8)(inst_mgNo - 6)) {
        case 12:
            if (rand8() & 1) {
                temp = inst_playerOrderTbl[0];
                inst_playerOrderTbl[0] = inst_playerOrderTbl[1];
                inst_playerOrderTbl[1] = temp;
            }
            if (rand8() & 1) {
                temp = inst_playerOrderTbl2[0];
                inst_playerOrderTbl2[0] = inst_playerOrderTbl2[1];
                inst_playerOrderTbl2[1] = temp;
            }
            for (i = 0; i < 4; i++) {
                GwPlayer[inst_playerOrderTbl[i]].group = i;
            }
            break;
        case 8:
            if (rand8() & 1) {
                temp = inst_playerOrderTbl[0];
                inst_playerOrderTbl[0] = inst_playerOrderTbl[1];
                inst_playerOrderTbl[1] = temp;
            }
            if (rand8() & 1) {
                temp = inst_playerOrderTbl2[0];
                inst_playerOrderTbl2[0] = inst_playerOrderTbl2[1];
                inst_playerOrderTbl2[1] = temp;
            }
            for (i = 0; i < 4; i++) {
                GwPlayer[inst_playerOrderTbl[i]].group = i;
            }
            break;
        case 7:
            for (i = 0, humans = 0; i < 2; i++) {
                if (!(GwPlayer[inst_playerOrderTbl[i]].stat & 1)) {
                    humans++;
                }
            }
            if (humans == 1) {
                if (GwPlayer[inst_playerOrderTbl[0]].stat & 1) {
                    temp = inst_playerOrderTbl[0];
                    inst_playerOrderTbl[0] = inst_playerOrderTbl[1];
                    inst_playerOrderTbl[1] = temp;
                }
            } else if (rand8() & 1) {
                temp = inst_playerOrderTbl[0];
                inst_playerOrderTbl[0] = inst_playerOrderTbl[1];
                inst_playerOrderTbl[1] = temp;
            }
            for (i = 0, humans = 0; i < 2; i++) {
                if (!(GwPlayer[inst_playerOrderTbl2[i]].stat & 1)) {
                    humans++;
                }
            }
            if (humans == 1) {
                if (GwPlayer[inst_playerOrderTbl2[0]].stat & 1) {
                    temp = inst_playerOrderTbl2[0];
                    inst_playerOrderTbl2[0] = inst_playerOrderTbl2[1];
                    inst_playerOrderTbl2[1] = temp;
                }
            } else if (rand8() & 1) {
                temp = inst_playerOrderTbl2[0];
                inst_playerOrderTbl2[0] = inst_playerOrderTbl2[1];
                inst_playerOrderTbl2[1] = temp;
            }
            for (i = 0; i < 4; i++) {
                GwPlayer[inst_playerOrderTbl[i]].group = i;
            }
            break;
        case 0:
        case 1:
            for (i = 0; i < 5; i++) {
                first = (u8)(rand8() % 3);
                second = (u8)(rand8() % 3);
                if (second == first) {
                    second++;
                    second %= 3;
                }
                temp = inst_playerOrderTbl1[first];
                inst_playerOrderTbl1[first] = inst_playerOrderTbl1[second];
                inst_playerOrderTbl1[second] = temp;
            }
            for (i = 0; i < 4; i++) {
                GwPlayer[inst_playerOrderTbl[i]].group = i;
            }
            break;
    }
}

void inst_PicNoSet(void) {
    s32 variant;
    u32 flags;
    u32 count;
    s32 message = 0;
    s32 choose = 1;

    if (inst_practiceRetF == 1) {
        if ((inst_mgNo == 29) | (inst_mgNo == 55)) {
            message = mgDataTbl[inst_mgNo].flags & 0x7FF;
            message += storySceneNo * 2;
            choose = 0;
        }
    }
    if (choose == 1) {
        flags = mgDataTbl[inst_mgNo].flags;
        message = flags & 0x7FF;
        if (flags & 0x4000) {
            if (inst_mgNo != 70) {
                count = (flags & 0x3800) >> 11;
                variant = rand8() % count;
                storySceneNo = variant;
            } else {
                variant = storySceneNo;
            }
            message += variant * 2;
        } else if (inst_mgNo == 71) {
            storySceneNo = 2;
        } else if ((inst_mgNo == 30) && (_CheckFlag(0x1C) != 0)) {
            storySceneNo = 1;
        } else {
            storySceneNo = 0;
        }
    }
    inst_picNo = message;
}
