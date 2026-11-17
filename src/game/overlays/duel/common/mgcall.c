#include "common_duel.h"
#include "game/board.h"
#include "ovl_81.h"

typedef struct UnkC5770 {
    /* 0x00 */ s32 state;
    /* 0x04 */ char unk_04[0xC];
} UnkC5770; // sizeof 0x10

typedef struct UnkC5770Rect {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 w;
    /* 0x06 */ s16 h;
} UnkC5770Rect; // sizeof 0x8

extern u32 scRetraceCnt;
extern UnkData_CD0A0 mbMgHis;
extern s8 mbMgHisIdx[];
u8 mbdMgCall1vs1Tbl[] = { 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 0 };
u8 mbdMgCall1vs1EasyTbl[] = { 49, 50, 51, 53, 55, 56, 57, 0 };
u8 mbdMgCallPartnerTbl[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
    2, 3, 4, 5, 6, 7, 8, 9, 11,
    1, 2, 3, 4, 5, 6, 7, 8, 9, 11,
    0
};
u8 mbdMgCallListNumTbl[] = { 5, 3 };
u8 mbdMgCallHisLenTbl[] = { 5, 1, 2, 1 };
UnkC5770Rect mbdMgCallRect5Tbl[] = {
    { 60, 328, 200, 20 },
    { 60, 348, 200, 20 },
    { 60, 368, 200, 20 },
    { 60, 388, 200, 20 },
    { 60, 408, 200, 20 },
};
UnkC5770Rect mbdMgCallRect3Tbl[] = {
    { 95, 330, 130, 20 },
    { 95, 354, 130, 20 },
    { 95, 378, 130, 20 },
};
u8 mbdMgCallBgYTbl[] = { 50, 34 };
u8 mbdMgCallCursorXTbl[] = { 50, 80 };
u8 mbdMgCallCursorStepTbl[] = { 20, 24 };
u8 mbdMgCallCursorYTbl[] = { 114, 116 };
s8 mbdMgCallCursorAnimTbl[][2] = { { 1, 0 }, { 9, 15 }, { 11, 8 }, { 13, 0 } };
s32 mbdMgCallMesBaseTbl[] = { 0x4700, 0x1F20 };
// Indexed by minigame number - 1.
u8 mbdMgCallMesColTbl[] = {
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7
};
u32 mbdMgCallSeTime = 0;
s32 mbdMgCallHelpF = 0;
DuelHelpWin *mbdMgCallHelpWin = NULL;
Object *mbdMgCallMdlObj = NULL;
s32 mbdMgCallPad[2] = { 0 }; /* Unreferenced. */
f32 mbdCoinChangeScrPosTbl[2][2] = { { 70.0f, 64.0f }, { 250.0f, 160.0f } };

extern UnkC5770B70 mbdMgCallSlotTbl[5];
extern omObjData *mbdMgCallListObj;
extern s8 mbdMgCallMgList[5];
extern s8 mbdMgCallType;
extern s8 mbdMgCallPackOfs;
extern s16 mbdMgCallBgGrp;
extern s16 mbdMgCallBgAnim;
extern s16 mbdMgCallCursorGrp;
extern s16 mbdMgCallCursorAnim;
extern s32 mbdMgCallMode;
extern s16 mbdCoinChangeGrp[2];
extern s16 mbdCoinChangeAnimTbl[2][2];
extern omObjData *mbdCoinChangeObj[2];
extern u8 mbdCoinChangeMode;
extern f32 mbdCoinChangePosTbl[2][2];

void MBDMgCallCursorSprCreate(void);
void MBDMgCallListCreate(s32 arg0);
void MBDMgCallListCreateProc(void);
void MBDMgCallExec(void);
void MBDMgCallListProc(void);
void MBDCoinChangeKill(s32 arg0);
void MBDCoinChangeCreateEx(s32 arg0, s32 coins, s32 arg2, s32 arg3);

void MBDMgCallCursorFXPlay(void) {
    if (scRetraceCnt >= (mbdMgCallSeTime + 4)) {
        HuAudFXPlay(0x104);
        mbdMgCallSeTime = scRetraceCnt;
    }
}

void MBDMgCallListExec(omObjData *arg0) {
    UnkC5770B70 *entry;
    s32 i;
    s16 new_var;

    switch (arg0->work[0]) {
        case 3:
            break;
        case 0:
            if (arg0->work[1] == 0) {
                arg0->scale.y += 0.1f;
                if (arg0->scale.y > 1.0f) {
                    arg0->scale.y = 1.0f;
                }
                for (i = 0; i < mbdMgCallListNumTbl[mbdMgCallType]; i++) {
                    new_var = 0xE0;
                    entry = &mbdMgCallSlotTbl[i];
                    HuWinPosSet(entry->windowId, entry->x + (entry->w / 2), entry->y + ((entry->h / 2) - new_var));
                    HuWinScaleSet(entry->windowId, 0.0f, arg0->scale.y);
                }

                new_var = 0xE0;
                HuSprPosSet(mbdMgCallBgGrp, 0, 0xA0, mbdMgCallSlotTbl[0].y + (mbdMgCallBgYTbl[mbdMgCallType] - new_var));
                HuSprScaleSet(mbdMgCallBgGrp, 0, sindf(arg0->scale.x), arg0->scale.y);
                if (arg0->scale.y >= 1.0f) {
                    arg0->work[0] = 4;
                    arg0->work[1] = 5;
                }
            } else {
                arg0->work[1] -= 1;
            }
            break;
        case 4:
            if (arg0->work[1] != 0) {
                arg0->work[1] -= 1;
                break;
            }

            arg0->scale.x += 10.0f;
            if (arg0->scale.x > 90.0f) {
                arg0->scale.x = 90.0f;
            }

            for (i = 0; i < mbdMgCallListNumTbl[mbdMgCallType]; i++) {
                new_var = 0xE0;
                entry = &mbdMgCallSlotTbl[i];
                HuWinPosSet(entry->windowId, entry->x + (entry->w / 2), entry->y + ((entry->h / 2) - new_var));
                HuWinScaleSet(entry->windowId, sindf(arg0->scale.x), arg0->scale.y);
            }

            new_var = 0xE0;
            HuSprPosSet(mbdMgCallBgGrp, 0, 0xA0, mbdMgCallSlotTbl[0].y + (mbdMgCallBgYTbl[mbdMgCallType] - new_var));
            HuSprScaleSet(mbdMgCallBgGrp, 0, sindf(arg0->scale.x), arg0->scale.y);

            if (arg0->scale.x >= 90.0f) {
                MBDMgCallCursorFXPlay();
                arg0->work[0] = 1;
                arg0->scale.x = 1.0f;
                arg0->scale.z = -1.0f;
                arg0->scale.y = 0.0f;
                arg0->work[1] = 0;
                arg0->work[2] = MBDRand(mbdMgCallListNumTbl[mbdMgCallType]);
                arg0->work[3] = 0;
                MBDMgCallCursorSprCreate();
            }
            break;
        case 1:
            arg0->scale.z += arg0->scale.x;

            if (arg0->scale.z >= 1.0f) {
                if (arg0->work[3] != 0 && arg0->scale.x <= 0.08f) {
                    arg0->work[3]--;
                }
                arg0->scale.z -= 1.0f;
                if (arg0->scale.y == 0.0f) {
                    arg0->work[1]++;
                    arg0->work[1] = arg0->work[1] % mbdMgCallListNumTbl[mbdMgCallType];
                } else {
                    arg0->work[1]--;
                    if (arg0->work[1] >= 0x80U) {
                        arg0->work[1] = mbdMgCallListNumTbl[mbdMgCallType] - 1;
                    }
                }
                MBDMgCallCursorFXPlay();
            }

            for (i = 0; i < mbdMgCallListNumTbl[mbdMgCallType]; i++) {
                entry = &mbdMgCallSlotTbl[i];
                if (i == arg0->work[1]) {
                    HuWinBGColSet(entry->windowId, 0, 0xC8, 0);
                    HuWinBGTPLvlSet(entry->windowId, 0x100);
                    HuWinPriSet(entry->windowId, 0x2328);
                } else {
                    HuWinBGColSet(entry->windowId, 0x40, 0x40, 0x80);
                    HuWinBGTPLvlSet(entry->windowId, 0);
                    HuWinPriSet(entry->windowId, 0x2710);
                }
            }

            if (arg0->work[1] == arg0->work[2] || arg0->scale.x < 1.0f) {
                arg0->scale.x -= 0.02;
            }

            if (arg0->scale.x <= 0.08f) {
                arg0->scale.x = 0.08f;
                if (arg0->work[1] == arg0->work[2] && arg0->work[3] == 0 && arg0->scale.z + 0.08f >= 1.0f) {
                    if ((rand8() & 0xF) || arg0->scale.y == 1.0f || arg0->work[1] == 0) {
                        if (GwSystem.show_minigame_explanations == FALSE || GwSystem.current_board_index == 6) {
                            HuAudFXPlay(0x105);
                        } else {
                            HuAudFXPlay(0x112);
                        }

                        arg0->work[0] = 2;
                        arg0->work[3] = 60;
                        HuWinNoCRSet(mbdMgCallSlotTbl[arg0->work[1]].windowId);
                        HuWinHomeClear(mbdMgCallSlotTbl[arg0->work[1]].windowId);
                        HuWinMesSet(mbdMgCallSlotTbl[arg0->work[1]].windowId,
                                    mbdMgCallMesBaseTbl[mbdMgCallType] + mbdMgCallMgList[arg0->work[1]] - 1,
                                    HUWIN_POS_CENTER, 4);
                        HuWinMesColSet(mbdMgCallSlotTbl[arg0->work[1]].windowId, 1);
                        HuWinMesDefColSet(mbdMgCallSlotTbl[arg0->work[1]].windowId, 0xA0, 0xA0, 0xA0);
                        HuWinBGColSet(mbdMgCallSlotTbl[arg0->work[1]].windowId, 0xFE, 0xFF, 0xD0);
                        HuWinMesSpeedSet(mbdMgCallSlotTbl[arg0->work[1]].windowId, 0);
                    } else {
                        arg0->scale.y = 1.0f;
                        arg0->work[2]--;
                        if (arg0->work[2] >= 0x80U) {
                            arg0->work[2] = mbdMgCallListNumTbl[mbdMgCallType] - 1;
                        }
                    }
                }
            }
            break;
        case 2:
            if (arg0->work[3] != 0) {
                arg0->work[3]--;
            } else {
                mbMgHis.recentMinigames[mbdMgCallType][mbMgHisIdx[mbdMgCallType]] = mbdMgCallMgList[arg0->work[2]];
                mbMgHisIdx[mbdMgCallType]++;
                mbMgHisIdx[mbdMgCallType] = mbMgHisIdx[mbdMgCallType] % mbdMgCallHisLenTbl[mbdMgCallType + mbdMgCallPackOfs];
                GWMgNoSet(mbdMgCallMgList[arg0->work[2]]);
                if (GwSystem.current_board_index != 6 || mbdMgCallType == 1) {
                    MBDTelopMgTypeKill();
                    MBDMgCallClose();
                }
            }
            arg0->rot.z += 1.0f;
            if (arg0->rot.z >= 13.0f) {
                arg0->rot.z -= 13.0f;
            }
            break;
    }

    if (mbdMgCallCursorGrp != -1) {
        for (i = 0; !(arg0->rot.z < (f32)*mbdMgCallCursorAnimTbl[i]); i++) {}

        HuSprPosSet(mbdMgCallCursorGrp, 0, mbdMgCallCursorXTbl[mbdMgCallType] + mbdMgCallCursorAnimTbl[i][1],
                    mbdMgCallCursorYTbl[mbdMgCallType] + mbdMgCallCursorStepTbl[mbdMgCallType] * arg0->work[1]);
    }
}

void MBDMgCallPartnerListExec(omObjData *arg0) {
    UnkC5770B70 *entry;
    s32 i;
    s32 rnd;
    s16 new_var;

    switch (arg0->work[0]) {
        case 3:
            break;
        case 0:
            if (arg0->work[1] == 0) {
                arg0->scale.y += 0.25f;
                if (arg0->scale.y > 1.0f) {
                    arg0->scale.y = 1.0f;
                }
                for (i = 0; i < mbdMgCallListNumTbl[mbdMgCallType]; i++) {
                    new_var = 0xE0;
                    entry = &mbdMgCallSlotTbl[i];
                    HuWinPosSet(entry->windowId, entry->x + (entry->w / 2), entry->y + ((entry->h / 2) - new_var));
                    HuWinScaleSet(entry->windowId, 0.0f, arg0->scale.y);
                }

                new_var = 0xE0;
                HuSprPosSet(mbdMgCallBgGrp, 0, 0xA0, mbdMgCallSlotTbl[0].y + (mbdMgCallBgYTbl[mbdMgCallType] - new_var));
                HuSprScaleSet(mbdMgCallBgGrp, 0, sindf(arg0->scale.x), arg0->scale.y);
                if (arg0->scale.y >= 1.0f) {
                    arg0->work[0] = 4;
                    arg0->work[1] = 0;
                }
            } else {
                arg0->work[1] -= 1;
            }
            break;
        case 4:
            if (arg0->work[1] != 0) {
                arg0->work[1] -= 1;
                break;
            }

            arg0->scale.x += 30.0f;
            if (arg0->scale.x > 90.0f) {
                arg0->scale.x = 90.0f;
            }

            for (i = 0; i < mbdMgCallListNumTbl[mbdMgCallType]; i++) {
                new_var = 0xE0;
                entry = &mbdMgCallSlotTbl[i];
                HuWinPosSet(entry->windowId, entry->x + (entry->w / 2), entry->y + ((entry->h / 2) - new_var));
                HuWinScaleSet(entry->windowId, sindf(arg0->scale.x), arg0->scale.y);
            }

            new_var = 0xE0;
            HuSprPosSet(mbdMgCallBgGrp, 0, 0xA0, mbdMgCallSlotTbl[0].y + (mbdMgCallBgYTbl[mbdMgCallType] - new_var));
            HuSprScaleSet(mbdMgCallBgGrp, 0, sindf(arg0->scale.x), arg0->scale.y);

            if (arg0->scale.x >= 90.0f) {
                MBDMgCallCursorFXPlay();
                arg0->work[0] = 1;
                arg0->scale.x = 1.0f;
                arg0->scale.z = -1.0f;
                arg0->scale.y = 0.0f;
                arg0->work[1] = 0;
                arg0->work[2] = MBDRand(mbdMgCallListNumTbl[mbdMgCallType]);
                arg0->work[3] = 0;
                MBDMgCallCursorSprCreate();
                mbdMgCallHelpWin = MBDHelpWinCreate(1, 0xC0, 1);
                mbdMgCallHelpF = 0;
            }
            break;
        case 1:
            arg0->scale.z += arg0->scale.x;

            if (arg0->scale.z >= 1.0f) {
                if (arg0->work[3] != 0 && arg0->scale.x <= 0.08f) {
                    arg0->work[3]--;
                }
                arg0->scale.z -= 1.0f;
                if (arg0->scale.y >= 0.0f) {
                    arg0->work[1]++;
                    arg0->work[1] = arg0->work[1] % mbdMgCallListNumTbl[mbdMgCallType];
                } else {
                    arg0->work[1]--;
                    if (arg0->work[1] >= 0x80U) {
                        arg0->work[1] = mbdMgCallListNumTbl[mbdMgCallType] - 1;
                    }
                }
                MBDMgCallCursorFXPlay();
            }

            for (i = 0; i < mbdMgCallListNumTbl[mbdMgCallType]; i++) {
                entry = &mbdMgCallSlotTbl[i];
                if (i == arg0->work[1]) {
                    HuWinBGColSet(entry->windowId, 0, 0xC8, 0);
                    HuWinBGTPLvlSet(entry->windowId, 0x100);
                    HuWinPriSet(entry->windowId, 0x2328);
                } else {
                    HuWinBGColSet(entry->windowId, 0x40, 0x40, 0x80);
                    HuWinBGTPLvlSet(entry->windowId, 0);
                    HuWinPriSet(entry->windowId, 0x2710);
                }
            }

            if (mbdMgCallHelpF == 0) {
                if (MBDPlayerComCheck(GwSystem.current_player_index) != 0) {
                    mbdMgCallHelpF = 1;
                } else if (ContBtnDown[GwPlayer[GwSystem.current_player_index].pad] & A_BUTTON) {
                    mbdMgCallHelpF = 1;
                }
                break;
            }

            if (arg0->work[1] == arg0->work[2] || arg0->scale.x < 1.0f) {
                arg0->scale.x -= 0.02;
            }

            if (arg0->scale.x <= 0.08f) {
                arg0->scale.x = 0.08f;
                if (arg0->work[1] == arg0->work[2] && arg0->work[3] == 0 && arg0->scale.z + 0.08f >= 1.0f) {
                    if (arg0->scale.y != 0.0f) {
                    selected:
                        HuAudFXPlay(0x105);
                        switch (mbdMgCallMgList[arg0->work[2]]) {
                            case 1:
                            case 6:
                                MBDPlayerVibrate(-1, 4);
                                break;
                            case 2:
                            case 5:
                            case 7:
                            case 8:
                                MBDPlayerVibrate(-1, 2);
                                break;
                            case 9:
                                MBDPlayerVibrate(-1, 1);
                                break;
                            case 10:
                                MBDPlayerVibrate(-1, 3);
                                break;
                        }

                        arg0->work[0] = 2;
                        arg0->work[3] = 60;
                        HuWinNoCRSet(mbdMgCallSlotTbl[arg0->work[1]].windowId);
                        HuWinHomeClear(mbdMgCallSlotTbl[arg0->work[1]].windowId);
                        HuWinMesSet(mbdMgCallSlotTbl[arg0->work[1]].windowId,
                                    mbdMgCallMesBaseTbl[mbdMgCallType] + mbdMgCallMgList[arg0->work[1]] - 1,
                                    HUWIN_POS_CENTER, 4);
                        HuWinMesColSet(mbdMgCallSlotTbl[arg0->work[1]].windowId, 1);
                        HuWinMesDefColSet(mbdMgCallSlotTbl[arg0->work[1]].windowId, 0xA0, 0xA0, 0xA0);
                        HuWinBGColSet(mbdMgCallSlotTbl[arg0->work[1]].windowId, 0xFE, 0xFF, 0xD0);
                        HuWinMesSpeedSet(mbdMgCallSlotTbl[arg0->work[1]].windowId, 0);
                    } else {
                        rnd = MBDRand(100.0f);
                        if (rnd < 15) {
                            goto selected;
                        } else if (rnd < 65) {
                            arg0->scale.y = 1.0f;
                            arg0->work[2] += 1;
                            arg0->work[2] = arg0->work[2] % mbdMgCallListNumTbl[mbdMgCallType];
                        } else if (rnd < 85) {
                            arg0->scale.y = 1.0f;
                            arg0->work[2] += 2;
                            arg0->work[2] = arg0->work[2] % mbdMgCallListNumTbl[mbdMgCallType];
                        } else if (rnd < 95) {
                            arg0->scale.y = -1.0f;
                            arg0->work[2]--;
                            if (arg0->work[2] >= 0x80U) {
                                arg0->work[2] = mbdMgCallListNumTbl[mbdMgCallType] - 1;
                            }
                        } else {
                            arg0->scale.y = -1.0f;
                            arg0->work[2]--;
                            if (arg0->work[2] >= 0x80U) {
                                arg0->work[2] = mbdMgCallListNumTbl[mbdMgCallType] - 1;
                            }
                            arg0->work[2]--;
                            if (arg0->work[2] >= 0x80U) {
                                arg0->work[2] = mbdMgCallListNumTbl[mbdMgCallType] - 1;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            if (arg0->work[3] != 0) {
                arg0->work[3]--;
            } else {
                mbMgHis.recentMinigames[mbdMgCallType][mbMgHisIdx[mbdMgCallType]] = mbdMgCallMgList[arg0->work[2]];
                mbMgHisIdx[mbdMgCallType]++;
                mbMgHisIdx[mbdMgCallType] = mbMgHisIdx[mbdMgCallType] % mbdMgCallHisLenTbl[mbdMgCallType + mbdMgCallPackOfs];
                GWMgNoSet(mbdMgCallMgList[arg0->work[2]]);
                if (GwSystem.current_board_index != 6 || mbdMgCallType == 1) {
                    MBDHelpWinKill(mbdMgCallHelpWin);
                    MBDMgCallClose();
                }
            }
            arg0->rot.z += 1.0f;
            if (arg0->rot.z >= 13.0f) {
                arg0->rot.z -= 13.0f;
            }
            break;
    }

    if (mbdMgCallCursorGrp != -1) {
        for (i = 0; !(arg0->rot.z < (f32)*mbdMgCallCursorAnimTbl[i]); i++) {}

        HuSprPosSet(mbdMgCallCursorGrp, 0, mbdMgCallCursorXTbl[mbdMgCallType] + mbdMgCallCursorAnimTbl[i][1],
                    mbdMgCallCursorYTbl[mbdMgCallType] + mbdMgCallCursorStepTbl[mbdMgCallType] * arg0->work[1]);
    }
}

void MBDMgCallHisInit(void) {
    s32 category;
    s32 minigameCategoryIndex;

    for (category = 0; category <= 0; category++) {
        for (minigameCategoryIndex = 0; minigameCategoryIndex < PREV_MINIGAME_LIST_LENGTH; minigameCategoryIndex++) {
            mbMgHis.recentMinigames[category][minigameCategoryIndex] = -1;
        }
        mbMgHisIdx[category] = 0;
    }
}

void MBDMgCallInit(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        mbdMgCallSlotTbl[i].windowId = -1;
    }
    mbdMgCallListObj = NULL;
    mbdMgCallBgAnim = -1;
    mbdMgCallBgGrp = -1;
    mbdMgCallCursorAnim = -1;
    mbdMgCallCursorGrp = -1;
}

void MBDMgCallClose(void) {
    UnkC5770B70 *entry;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbdMgCallSlotTbl); i++) {
        entry = &mbdMgCallSlotTbl[i];
        if (entry->windowId != -1) {
            HuWinKill(entry->windowId);
            entry->windowId = -1;
        }
    }

    if (mbdMgCallListObj != NULL) {
        omDelObj(mbdMgCallListObj);
        mbdMgCallListObj = NULL;
    }

    if (mbdMgCallBgGrp != -1) {
        HuSprGrpKill(mbdMgCallBgGrp);
        mbdMgCallBgGrp = -1;
    }

    if (mbdMgCallBgAnim != -1) {
        HuSprAnimKill(mbdMgCallBgAnim);
        mbdMgCallBgAnim = -1;
    }

    if (mbdMgCallCursorGrp != -1) {
        HuSprGrpKill(mbdMgCallCursorGrp);
        mbdMgCallCursorGrp = -1;
    }

    if (mbdMgCallCursorAnim != -1) {
        HuSprAnimKill(mbdMgCallCursorAnim);
        mbdMgCallCursorAnim = -1;
    }
}

void MBDMgCallListBgSprCreate(void) {
    void *data;

    if (mbdMgCallBgGrp == -1) {
        mbdMgCallBgGrp = HuSprGrpCreate(1, 0);
        if (mbdMgCallType == 1) {
            data = DataRead(0x130106);
        } else {
            data = DataRead(0x130116);
        }
        mbdMgCallBgAnim = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(mbdMgCallBgGrp, 0, mbdMgCallBgAnim, 0);
        HuSprPriSet(mbdMgCallBgGrp, 0, 0x4770);
        HuSprAttrSet(mbdMgCallBgGrp, 0, 0x1000);
        HuSprPosSet(mbdMgCallBgGrp, 0, 0xA0, mbdMgCallBgYTbl[mbdMgCallType] + mbdMgCallSlotTbl[0].y);
        if (mbdMgCallType != 1) {
            HuSprColorSet(mbdMgCallBgGrp, 0, 0xD7, 0x3D, 0xBE);
        } else {
            HuSprColorSet(mbdMgCallBgGrp, 0, 0, 0x64, 0);
        }
    }
}

void MBDMgCallCursorSprCreate(void) {
    s32 files[2] = { 0x130210, 0x130105 };
    void *data;

    if (mbdMgCallCursorGrp == -1) {
        mbdMgCallCursorGrp = HuSprGrpCreate(1, 4);
        data = DataRead(files[mbdMgCallType]);
        mbdMgCallCursorAnim = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(mbdMgCallCursorGrp, 0, mbdMgCallCursorAnim, 0);
        HuSprPriSet(mbdMgCallCursorGrp, 0, 0x100);
        HuSprAttrSet(mbdMgCallCursorGrp, 0, 0);
        HuSprPosSet(mbdMgCallCursorGrp, 0, mbdMgCallCursorXTbl[mbdMgCallType], 0x9A);
    }
}

void MBDMgCallListCreate(s32 arg0) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);
    UnkC5770Rect *rects[2] = { mbdMgCallRect5Tbl, mbdMgCallRect3Tbl };
    u8 *mgLists[4] = { mbdMgCall1vs1Tbl, mbdMgCallPartnerTbl, mbdMgCall1vs1EasyTbl, mbdMgCallPartnerTbl };
    u8 mgCounts[4] = { 10, 30, 7, 30 };
    s32 winStyles[2] = { 5, 20 };
    UnkC5770B70 *entry;
    omObjData *obj;
    s32 listOffset;
    s32 i;
    s32 j;
    s32 k;
    s32 type;

    type = arg0; // A separate copy of arg0 is needed for regalloc.
    mbdMgCallType = type;
    listOffset = (_CheckFlag(0x20) != 0) * 2;
    mbdMgCallPackOfs = listOffset;

    for (i = 0; i < mbdMgCallListNumTbl[type]; i++) {
        entry = &mbdMgCallSlotTbl[i];
        entry->x = rects[type][i].x;
        entry->y = rects[type][i].y;
        entry->w = rects[type][i].w;
        entry->h = rects[type][i].h;

        entry->windowId = HuWinCreate(entry->x + (entry->w / 2), entry->y + (entry->h / 2), entry->w, entry->h, 0, winStyles[type]);
        HuWinPriSet(entry->windowId, 0x2328);
        HuWinDummy(entry->windowId);
        HuWinCenterPosSet(entry->windowId, entry->w / 2, entry->h / 2);
        HuWinBGTPLvlSet(entry->windowId, 0);

        while (1) {
            mbdMgCallMgList[i] = mgLists[type + listOffset][MBDRand(mgCounts[type + listOffset])];

            for (j = 0; j < i; j++) {
                if (j == i) {
                    continue;
                }
                if (mbdMgCallMgList[j] == mbdMgCallMgList[i]) {
                    break;
                }
            }
            if (j != i) {
                continue;
            }

            if (type != 1) {
                for (k = 0; k < mbdMgCallHisLenTbl[type + listOffset]; k++) {
                    if (mbdMgCallMgList[i] == mbMgHis.recentMinigames[type][k]) {
                        break;
                    }
                }
                if (k != mbdMgCallHisLenTbl[type + listOffset]) {
                    continue;
                }
            } else {
                switch (mbdMgCallMgList[i]) {
                    case 1:
                        if (player->star == 5) {
                            continue;
                        }
                        break;
                    case 2:
                        if (GwPlayer[0].clink == GwPlayer[1].clink && GwPlayer[0].cidx == GwPlayer[1].cidx) {
                            continue;
                        }
                        break;
                    case 3:
                        if (GwPlayer[GwSystem.current_player_index].coin == 0) {
                            continue;
                        }
                        break;
                    case 7:
                        if (player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 2) {
                            continue;
                        }
                        if (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 2) {
                            continue;
                        }
                        if (player->stats.partners.frontID == -1 && player->stats.partners.backID == -1) {
                            continue;
                        }
                        break;
                    case 8:
                        if (player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 1) {
                            continue;
                        }
                        if (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 1) {
                            continue;
                        }
                        /* fallthrough */
                    case 9:
                        if (player->stats.partners.frontID == -1 && player->stats.partners.backID == -1) {
                            continue;
                        }
                        break;
                    case 10:
                        if (MBDMasuTypeNumGet(MBD_MASU_TYPE_CHR(GwPlayer[GwSystem.current_player_index].chr)) != 0) {
                            break;
                        }
                        /* fallthrough */
                    case 6:
                        if (MBDMasuTypeNumGet(MBD_MASU_TYPE_CHR(GwPlayer[(s8)(GwSystem.current_player_index ^ 1)].chr)) == 0) {
                            continue;
                        }
                        break;
                }
            }

            HuWinNoCRSet(entry->windowId);

            if (mbdMgCallType != 1 && GWMgUnlockCheck(mbdMgCallMgList[i] - 1) == FALSE) {
                HuWinMesSet(entry->windowId, 0x4748, HUWIN_POS_CENTER, 4);
            } else {
                do { // Needed for regalloc.
                    HuWinMesSet(entry->windowId, mbdMgCallMesBaseTbl[type] + mbdMgCallMgList[i] - 1, HUWIN_POS_CENTER, 4);
                } while (0);
            }

            HuWinMesColSet(entry->windowId, mbdMgCallMesColTbl[mbdMgCallMgList[i] - 1]);
            HuWinMesSpeedSet(entry->windowId, 0);
            break;
        }
    }

    if (mbdMgCallType != 1) {
        obj = omAddObj(-0x8000, 0, 0, -1, MBDMgCallListExec);
        mbdMgCallListObj = obj;
        obj->work[1] = 5;
    } else {
        obj = omAddObj(-0x8000, 0, 0, -1, MBDMgCallPartnerListExec);
        mbdMgCallListObj = obj;
        obj->work[1] = 0;
    }
    obj->work[0] = 3;
    obj->trans.y = 0.0f;
    obj->rot.z = 0.0f;
    obj->scale.x = 10.0f;
    obj->scale.y = 0.0f;
    MBDMgCallListBgSprCreate();
}

void MBDMgCallListCreateProc(void) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);
    UnkC5770Rect *rects[2] = { mbdMgCallRect5Tbl, mbdMgCallRect3Tbl };
    u8 *mgLists[4] = { mbdMgCall1vs1Tbl, mbdMgCallPartnerTbl, mbdMgCall1vs1EasyTbl, mbdMgCallPartnerTbl };
    u8 mgCounts[4] = { 10, 30, 7, 30 };
    s32 winStyles[2] = { 5, 20 };
    UnkC5770B70 *entry;
    omObjData *obj;
    s32 listOffset;
    s32 i;
    s32 j;
    s32 k;
    s32 arg0;

    arg0 = mbdMgCallMode;
    mbdMgCallType = arg0;
    listOffset = (_CheckFlag(0x20) != 0) * 2;
    mbdMgCallPackOfs = listOffset;
    if (mbdMgCallMdlObj != NULL) {
        Hu3DMotionSpeedSet(mbdMgCallMdlObj->omObj1->model[0], 2.0f);
    }

    for (i = 0; i < mbdMgCallListNumTbl[arg0]; i++) {
        entry = &mbdMgCallSlotTbl[i];
        entry->x = rects[arg0][i].x;
        entry->y = rects[arg0][i].y;
        entry->w = rects[arg0][i].w;
        entry->h = rects[arg0][i].h;

        entry->windowId = HuWinCreate(entry->x + (entry->w / 2), entry->y + (entry->h / 2), entry->w, entry->h, 0, winStyles[arg0]);
        HuWinPriSet(entry->windowId, 0x2328);
        HuWinDummy(entry->windowId);
        HuWinCenterPosSet(entry->windowId, entry->w / 2, entry->h / 2);
        HuWinBGTPLvlSet(entry->windowId, 0);
        HuPrcVSleep();

        while (1) {
            mbdMgCallMgList[i] = mgLists[arg0 + listOffset][MBDRand(mgCounts[arg0 + listOffset])];

            for (j = 0; j < i; j++) {
                if (j == i) {
                    continue;
                }
                if (mbdMgCallMgList[j] == mbdMgCallMgList[i]) {
                    break;
                }
            }
            if (j != i) {
                continue;
            }

            if (arg0 != 1) {
                for (k = 0; k < mbdMgCallHisLenTbl[arg0 + listOffset]; k++) {
                    if (mbdMgCallMgList[i] == mbMgHis.recentMinigames[arg0][k]) {
                        break;
                    }
                }
                if (k != mbdMgCallHisLenTbl[arg0 + listOffset]) {
                    continue;
                }
            } else {
                switch (mbdMgCallMgList[i]) {
                    case 1:
                        if (player->star == 5) {
                            continue;
                        }
                        break;
                    case 2:
                        if (GwPlayer[0].clink == GwPlayer[1].clink && GwPlayer[0].cidx == GwPlayer[1].cidx) {
                            continue;
                        }
                        break;
                    case 3:
                        if (GwPlayer[GwSystem.current_player_index].coin == 0) {
                            continue;
                        }
                        break;
                    case 7:
                        if (player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 2) {
                            continue;
                        }
                        if (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 2) {
                            continue;
                        }
                        if (player->stats.partners.frontID == -1 && player->stats.partners.backID == -1) {
                            continue;
                        }
                        break;
                    case 8:
                        if (player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 1) {
                            continue;
                        }
                        if (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 1) {
                            continue;
                        }
                        /* fallthrough */
                    case 9:
                        if (player->stats.partners.frontID == -1 && player->stats.partners.backID == -1) {
                            continue;
                        }
                        break;
                    case 10:
                        if (MBDMasuTypeNumGet(MBD_MASU_TYPE_CHR(GwPlayer[GwSystem.current_player_index].chr)) != 0) {
                            break;
                        }
                        /* fallthrough */
                    case 6:
                        if (MBDMasuTypeNumGet(MBD_MASU_TYPE_CHR(GwPlayer[(s8)(GwSystem.current_player_index ^ 1)].chr)) == 0) {
                            continue;
                        }
                        break;
                }
            }

            HuWinNoCRSet(entry->windowId);

            if (mbdMgCallType != 1 && GWMgUnlockCheck(mbdMgCallMgList[i] - 1) == FALSE) {
                HuWinMesSet(entry->windowId, 0x4748, HUWIN_POS_CENTER, 4);
            } else {
                do { // Needed for regalloc.
                    HuWinMesSet(entry->windowId, mbdMgCallMesBaseTbl[arg0] + mbdMgCallMgList[i] - 1, HUWIN_POS_CENTER, 4);
                } while (0);
            }

            HuWinMesColSet(entry->windowId, mbdMgCallMesColTbl[mbdMgCallMgList[i] - 1]);
            HuWinMesSpeedSet(entry->windowId, 0);
            break;
        }
        HuPrcVSleep();
    }

    if (mbdMgCallType != 1) {
        obj = omAddObj(-0x8000, 0, 0, -1, MBDMgCallListExec);
        mbdMgCallListObj = obj;
        obj->work[1] = 5;
    } else {
        obj = omAddObj(-0x8000, 0, 0, -1, MBDMgCallPartnerListExec);
        mbdMgCallListObj = obj;
        obj->work[1] = 0;
    }
    obj->work[0] = 3;
    obj->trans.y = 0.0f;
    obj->rot.z = 0.0f;
    obj->scale.x = 10.0f;
    obj->scale.y = 0.0f;
    MBDMgCallListBgSprCreate();
    if (mbdMgCallMdlObj != NULL) {
        Hu3DMotionSpeedSet(mbdMgCallMdlObj->omObj1->model[0], 1.0f);
    }
    omDelPrcObj(NULL);
}

void MBDMgCallListStart(s32 arg0) {
    mbdMgCallMode = arg0;
    if (arg0 != 1) {
        omAddPrcObj(MBDMgCallListCreateProc, 0, 0, 0);
    } else {
        MBDMgCallListCreate(arg0);
    }
}

void MBDMgCallListClose(void) {
    mbdMgCallListObj->work[0] = 0;
}

void MBDArrayShuffle(u8 *output, s32 count) {
    s8 pool[256];
    s32 i;
    s32 j;
    s32 randIndex;

    for (i = 0; i <= count; i++) {
        pool[i] = i;
    }

    for (i = 0; i <= count; i++) {
        randIndex = MBDRand(count - i + 1);
        output[i] = pool[randIndex];

        for (j = randIndex; j < count; j++) {
            pool[j] = pool[j + 1];
        }
    }
}

void MBDMgCallExec(void) {
    Process *process = HuPrcCurrentGet();
    s32 waitTime = 0;
    Object *spinObj = MBDAuraObjGet();
    f32 angle = 360.0f;
    s32 spinning = 0;
    s32 growing = 0;
    s32 hideTimer = 0;
    f32 scale = 0.0f;
    Object *obj;
    UnkC5770 *work;
    HmfModel *model;
    f32 zero;
    s32 i;

    obj = MBDModelFileCreate(0x130204, -1, 1.4f, scale, NULL);
    Hu3DModelAttrSet(obj->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
    Hu3DModelLayerSet(obj->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    MBDModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &spinObj->coords);
    HuVecCopyXYZ(&obj->scale, scale, 1.0f, 1.0f);
    obj->coords.y += 38.0f;
    work = process->user_data;

    while (TRUE) {
        if (spinning) {
            sincosdf(angle, &Hu3DData[spinObj->omObj1->model[0]].mtx[2][0], &Hu3DData[spinObj->omObj1->model[0]].mtx[2][2]);
            Hu3DData[spinObj->omObj1->model[0]].mtx[0][2] = -Hu3DData[spinObj->omObj1->model[0]].mtx[2][0];

            model = &Hu3DData[spinObj->omObj1->model[0]];
            model->mtx[0][0] = model->mtx[2][2];

            model = &Hu3DData[spinObj->omObj1->model[0]];
            zero = 0.0f;
            model->mtx[3][2] = zero;
            model->mtx[3][1] = zero;
            model->mtx[3][0] = zero;
            model->mtx[2][3] = zero;
            model->mtx[2][1] = zero;
            model->mtx[1][3] = zero;
            model->mtx[1][2] = zero;
            model->mtx[1][0] = zero;
            model->mtx[0][3] = zero;
            model->mtx[0][1] = zero;

            model = &Hu3DData[spinObj->omObj1->model[0]];
            model->mtx[3][3] = 1.0f;
            model->mtx[1][1] = 1.0f;

            if (angle > 0.0f) {
                angle -= 30.0f;
                if (angle <= 270.0f) {
                    growing = 1;
                }
            } else if (++hideTimer >= 2) {
                MBDModelDispOff(spinObj);
            }

            if (growing == 1) {
                HuVecCopyXYZ(&obj->scale, scale, 1.0f, 1.0f);
                scale += 0.12f;
                if (scale > 1.0f) {
                    scale = 1.0f;
                }
            }
        }

        switch (work->state) {
            case 0:
                work->state = 1;
                break;
            case 1:
                HuPrcSleep(1);
                MBDTelopMgTypeCreate(0, &obj->coords);
                HuPrcSleep(15);
                work->state++;
                break;
            case 2:
                MBDStatusDispMoveSet(2);
                MBDVsSprCreate();
                work->state++;
                waitTime = 0;
                break;
            case 3:
                if (++waitTime >= 5 && !spinning) {
                    spinning = 1;
                    HuAudFXPlay(0x206);
                }
                if (MBDStatusMoveCheck() == 0) {
                    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
                        if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
                            break;
                        }
                    }

                    if (i != MBD_MAX_PLAYERS) {
                        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
                            if ((HuPadBtnDown[GwPlayer[i].pad] & A_BUTTON) && !(GwPlayer[i].stat & PLAYER_IS_CPU)) {
                                break;
                            }
                        }
                        if (i == MBD_MAX_PLAYERS) {
                            break;
                        }
                    }
                    MBDMgCallListClose();
                    MBDStatusDispMoveSet(5);
                    work->state++;
                }
                break;
            case 4:
                if (MBDTelopMgTypeStatGet() == 0) {
                    MBDVsSprKill();
                    MBDModelKill(obj);
                    omDelPrcObj(NULL);
                }
                break;
        }

        HuPrcVSleep();
    }
}

Process *MBDMgCallCreate(void) {
    Process *process = omAddPrcObj(MBDMgCallExec, 0, 0x2000, 0x40);
    UnkC5770 *work = HuMemMemoryAlloc(process->heap, sizeof(UnkC5770));

    process->user_data = work;
    work->state = 0;
    return process;
}

void MBDMgCallListProc(void) {
    MBDMgCallListStart(1);
    HuPrcVSleep();
    MBDMgCallListClose();
    do {
        HuPrcVSleep();
    } while (mbdMgCallListObj != NULL);
    omDelPrcObj(NULL);
}

void MBDMgCallListProcCreate(void) {
    omAddPrcObj(MBDMgCallListProc, 0, 0x2000, 0);
}

void MBDCoinChangeObjMain(omObjData *arg0) {
    Vec pos;
    Vec2f screenPos;
    s32 i;

    switch (mbdCoinChangeMode) {
        case 1:
            pos.x = GwPlayer[arg0->work[3]].player_obj->coords.x;
            pos.y = GwPlayer[arg0->work[3]].player_obj->coords.y + 30.0f;
            pos.z = GwPlayer[arg0->work[3]].player_obj->coords.z;
            MBDCamera3Dto2D(&pos, &screenPos);
            break;
        case 0:
            screenPos.x = mbdCoinChangeScrPosTbl[arg0->work[3]][0];
            screenPos.y = mbdCoinChangeScrPosTbl[arg0->work[3]][1];
            break;
        default:
            screenPos.x = mbdCoinChangePosTbl[arg0->work[3]][0];
            screenPos.y = mbdCoinChangePosTbl[arg0->work[3]][1];
            break;
    }

    if (arg0->work[0] < 10) {
        if (arg0->rot.x > 0.0f) {
            arg0->trans.y -= 1.5f;
        } else {
            arg0->trans.y += 1.5f;
        }
        HuSprPosSet(mbdCoinChangeGrp[arg0->work[3]], 0, screenPos.x, (screenPos.y + arg0->trans.y));
    } else if (arg0->work[0] >= 0x18U) {
        arg0->scale.x += 0.4f;
        arg0->scale.y -= 0.3f;

        if (arg0->scale.x < 0.0f) {
            arg0->scale.x = 0.0f;
        }
        if (arg0->scale.y < 0.0f) {
            arg0->scale.y = 0.0f;
        }

        for (i = 1; i < arg0->work[1]; i++) {
            HuSprScaleSet(mbdCoinChangeGrp[arg0->work[3]], i, arg0->scale.x, arg0->scale.y);
        }
    } else if (arg0->work[0] >= 22) {
        arg0->scale.y -= 0.3f;
        if (arg0->scale.y < 0.0f) {
            arg0->scale.y = 0.0f;
        }

        for (i = 1; i < arg0->work[1]; i++) {
            HuSprScaleSet(mbdCoinChangeGrp[arg0->work[3]], i, arg0->scale.x, arg0->scale.y);
        }
    }

    if (arg0->work[0] >= 30) {
        MBDCoinChangeKill(arg0->work[3]);
        return;
    }

    arg0->work[0]++;
}

void MBDCoinChangeInit(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        mbdCoinChangeGrp[i] = -1;
        mbdCoinChangeObj[i] = NULL;
        for (j = 0; j < 2; j++) {
            mbdCoinChangeAnimTbl[i][j] = -1;
        }
    }
}

void MBDCoinChangeKill(s32 arg0) {
    s32 i;

    if (mbdCoinChangeGrp[arg0] != -1) {
        HuSprGrpKill(mbdCoinChangeGrp[arg0]);
        mbdCoinChangeGrp[arg0] = -1;
    }
    if (mbdCoinChangeObj[arg0] != NULL) {
        omDelObj(mbdCoinChangeObj[arg0]);
        mbdCoinChangeObj[arg0] = NULL;
    }

    for (i = 0; i < 2; i++) {
        if (mbdCoinChangeAnimTbl[arg0][i] != -1) {
            HuSprAnimKill(mbdCoinChangeAnimTbl[arg0][i]);
            mbdCoinChangeAnimTbl[arg0][i] = -1;
        }
    }
}

void MBDCoinChangeClose(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        MBDCoinChangeKill(i);
    }
}

void MBDCoinChangeCreateEx(s32 arg0, s32 coins, s32 arg2, s32 arg3) {
    Vec pos;
    Vec2f screenPos;
    s16 grp;
    s32 x;
    s32 count;
    void *data;
    s32 i;

    if (mbdCoinChangeGrp[arg0] == -1) {
        if (coins < -999) {
            coins = -999;
        }
        if (coins > 999) {
            coins = 999;
        }
        if (coins == 0) {
            HuAudFXPlay(0x203);
        }
        mbdCoinChangeObj[arg0] = omAddObj(-0x8000, 0, 0, -1, MBDCoinChangeObjMain);
        mbdCoinChangeObj[arg0]->work[0] = 0;
        mbdCoinChangeObj[arg0]->rot.x = coins;
        mbdCoinChangeObj[arg0]->trans.y = 0.0f;
        mbdCoinChangeObj[arg0]->scale.x = 1.0f;
        mbdCoinChangeObj[arg0]->scale.y = 2.0f;
        mbdCoinChangeObj[arg0]->work[3] = arg0;
        mbdCoinChangeObj[arg0]->work[1] = 6;
        mbdCoinChangeGrp[arg0] = grp = HuSprGrpCreate(6, 5);
        data = DataRead(0x130112);
        mbdCoinChangeAnimTbl[arg0][0] = HuSprAnimRead(data);
        DataClose(data);

        if (coins > 0) {
            data = DataRead(0x130213);
        } else {
            data = DataRead(0x130214);
        }

        mbdCoinChangeAnimTbl[arg0][1] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(grp, 1, mbdCoinChangeAnimTbl[arg0][0], 0);
        HuSprPriSet(grp, 1, 0x2010);
        HuSprAttrSet(grp, 1, 0x1000);

        count = 2;
        HuSprGrpMemberSet(grp, 2, mbdCoinChangeAnimTbl[arg0][1], 0);
        HuSprAnimModeSet(grp, 2, HUSPR_ANIM_MODE_BANK);

        if (coins > 0) {
            HuSprBankSet(grp, count, 10, 0);
        } else {
            HuSprBankSet(grp, count, 11, 0);
        }

        HuSprPriSet(grp, count, 0x2010);
        HuSprAttrSet(grp, count, 0x1000);

        count++;
        coins = (coins < 0) ? -coins : coins;

        if (coins >= 100) {
            HuSprGrpMemberSet(grp, count, mbdCoinChangeAnimTbl[arg0][1], 0);
            HuSprAnimModeSet(grp, count, HUSPR_ANIM_MODE_BANK);
            HuSprBankSet(grp, count, coins / 100, 0);
            HuSprPriSet(grp, count, 0x2010);
            HuSprAttrSet(grp, count, 0x1000);
            count++;
        }

        if (coins >= 10) {
            HuSprGrpMemberSet(grp, count, mbdCoinChangeAnimTbl[arg0][1], 0);
            HuSprAnimModeSet(grp, count, HUSPR_ANIM_MODE_BANK);
            HuSprBankSet(grp, count, (coins / 10) % 10, 0);
            HuSprPriSet(grp, count, 0x2010);
            HuSprAttrSet(grp, count, 0x1000);
            count++;
        }

        coins = coins % 10;

        HuSprGrpMemberSet(grp, count, mbdCoinChangeAnimTbl[arg0][1], 0);
        HuSprAnimModeSet(grp, count, HUSPR_ANIM_MODE_BANK);
        HuSprBankSet(grp, count, coins, 0);
        HuSprPriSet(grp, count, 0x2010);
        HuSprAttrSet(grp, count, 0x1000);
        count++;

        if (arg2 == -1 && arg3 == -1) {
            if (mbdCoinChangeMode != 0) {
                pos.x = GwPlayer[arg0].player_obj->coords.x;
                pos.y = GwPlayer[arg0].player_obj->coords.y + 30.0f;
                pos.z = GwPlayer[arg0].player_obj->coords.z;
                MBDCamera3Dto2D(&pos, &screenPos);
                HuSprPosSet(grp, 0, screenPos.x, screenPos.y);
            } else {
                HuSprPosSet(grp, 0, mbdCoinChangeScrPosTbl[arg0][0], mbdCoinChangeScrPosTbl[arg0][1]);
            }
        } else {
            HuSprPosSet(grp, 0, arg2, arg3);
        }

        x = count - 2;
        x = -(x * 8);

        for (i = 1; i < count; i++) {
            HuSprPosSet(grp, i, x, 0);
            x += 16;
        }

        for (; count < 6; count++) {
            HuSprDispOff(grp, count);
        }
    }
}

void MBDCoinChangeStatusCreate(s32 arg0, s32 arg1) {
    mbdCoinChangeMode = 0;
    MBDCoinChangeCreateEx(arg0, arg1, -1, -1);
}

void MBDCoinChangeCreate(s32 arg0, s32 arg1) {
    mbdCoinChangeMode = 1;
    MBDCoinChangeCreateEx(arg0, arg1, -1, -1);
}

void MBDCoinChangePosCreate(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    mbdCoinChangeMode = 2;
    mbdCoinChangePosTbl[arg0][0] = arg2;
    mbdCoinChangePosTbl[arg0][1] = arg3;
    MBDCoinChangeCreateEx(arg0, arg1, arg2, arg3);
}
