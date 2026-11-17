#include "common_board.h"
#include "game/board.h"
#include "mgcall.h"
#include "status.h"
#include "item.h"
#include "player.h"
#include "move.h"
#include "pause.h"
#include "main.h"
#include "model.h"

extern u32 scRetraceCnt;
typedef struct ItemRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} ItemRect;

typedef struct DefinitelyNotItemRect {
    s8 x[100500];
} DefinitelyNotItemRect;

typedef struct ItemRectTable {
    ItemRect *rects[6];
} ItemRectTable; // sizeof 0x18

typedef struct DefinitelyNotItemRectTable {
    DefinitelyNotItemRect *notRects[6];
} DefinitelyNotItemRectTable; // sizeof 0x18

typedef struct Sp18Struct {
    ItemRectTable rectTable;
    DefinitelyNotItemRectTable notRectTable1;
    DefinitelyNotItemRectTable notRectTable2;
} Sp18Struct;

u8 mbMgCall4PTbl[] = { 21, 22, 23, 24, 25, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 44 };
// *EasyTbl: subsets used when the easy minigame pack is selected (flag 0x20).
u8 mbMgCall4PEasyTbl[] = { 21, 25, 28, 29, 30, 33, 34, 38, 40 };
u8 mbMgCall1vs3Tbl[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
u8 mbMgCall1vs3EasyTbl[] = { 2, 3, 4, 5, 6, 9, 10 };
u8 mbMgCall2vs2Tbl[] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
u8 mbMgCall2vs2EasyTbl[] = { 11, 12, 16, 17, 19 };
u8 mbMgCallBattleTbl[] = { 26, 41, 42, 43, 45, 46, 47, 48 };
u8 mbMgCallBattleEasyTbl[] = { 42, 43, 45, 46 };
u8 mbMgCallItemTbl[] = { 59, 60, 61, 62, 63, 64 };
u8 mbMgCallItemEasyTbl[] = { 59, 60, 61, 62, 63, 64 };
u8 mbMgCall1vs1Tbl[] = { 49, 50, 51, 52, 53, 54, 55, 56, 57, 58 };
u8 mbMgCall1vs1EasyTbl[] = { 49, 50, 51, 53, 55, 56, 57 };
u8 mbMgCallListNumTbl[] = { 5, 3, 3, 3, 3, 5 };
u8 mbMgCallHisLenTbl[] = { 10, 5, 5, 3, 3, 5 }; /* full pack: recent minigame avoid count per category */
u8 mbMgCallHisLenEasyTbl[] = { 3, 3, 1, 3, 1, 2 }; /* easy pack (flag 0x20): recent minigame avoid count per category */
u8 mbMgCallColorTbl[][3] = {
    { 25, 163, 92 },
    { 52, 86, 206 },
    { 219, 42, 106 },
    { 222, 119, 31 },
    { 26, 142, 177 },
    { 215, 61, 109 }
};
ItemRect mbMgCallRect3Tbl[] = {
    { 60, 348, 200, 20 },
    { 60, 368, 200, 20 },
    { 60, 388, 200, 20 }
};
ItemRect mbMgCallRect5Tbl[] = {
    { 60, 328, 200, 20 },
    { 60, 348, 200, 20 },
    { 60, 368, 200, 20 },
    { 60, 388, 200, 20 },
    { 60, 408, 200, 20 }
};
u8 mbMgCallBgYTbl[] = { 50, 30, 30, 30, 30, 50 };
u8 mbMgCallCursorYTbl[] = { 114, 134, 134, 134, 134, 114 };
s8 mbMgCallCursorAnimTbl[][2] = {
    { 1, 0 },
    { 9, 15 },
    { 11, 8 },
    { 13, 0 }
};
// Indexed by minigame ID, starting at 1.
u8 mbMgCallMesColTbl[] = {
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};
u32 mbMgCallSeTime = 0;
u8 mbMgCallMgNumTbl[] = { 20, 10, 10, 6, 8, 10 };
u8 mbMgCallMgNumEasyTbl[] = { 9, 7, 5, 6, 4, 7 };

extern Vec mbCameraFocusPos;
extern ItemRectTable const mbMgCallRectTbl;
extern DefinitelyNotItemRectTable const mbMgCallMgTbl;
extern DefinitelyNotItemRectTable const mbMgCallMgEasyTbl;
extern ItemSlotEntry mbMgCallSlotTbl[5];
extern s8 mbMgCallMgList[5]; // generated minigame list
extern s8 mbMgCallType;


typedef struct Unk800CC3DC {
    char unk_00[4];
    s8 unk_04[8]; // unknown size
} Unk800CC3DC;

extern Unk800CC3DC mbMgHisIdxWork;
extern UnkData_CD0A0 mbMgHis;
extern omObjData *mbMgCallListObj;
extern s16 mbMgCallBgGrp;
extern s16 mbMgCallBgAnim;
extern s16 mbMgCallCursorAnim;
extern u8 mbMgHisIdx[];
extern u16 mbMgCallSlotBaseY;
extern s16 mbMgCallCursorGrp;

static void MBMgCallCursorSprCreate(void);


static void MBMgCallCursorFXPlay(void) {
    if (scRetraceCnt >= (mbMgCallSeTime + 4)) {
        HuAudFXPlay(0x104);
        mbMgCallSeTime = scRetraceCnt;
    }
}

static void MBMgCallListExec(omObjData *arg0) {
    ItemSlotEntry *entry = NULL;
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
                for (i = 0; i < mbMgCallListNumTbl[mbMgCallType]; i++) {
                    new_var = 0xE0;
                    entry = &mbMgCallSlotTbl[i];
                    HuWinPosSet(entry->obj, (entry->x + (entry->w / 2)), (entry->y + ((entry->h / 2) - new_var)));
                    HuWinScaleSet(entry->obj, 0.0f, arg0->scale.y);
                }

                new_var = 0xE0;
                HuSprPosSet(mbMgCallBgGrp, 0, 0xA0, (mbMgCallSlotBaseY + (mbMgCallBgYTbl[mbMgCallType] - new_var)));

                HuSprScaleSet(mbMgCallBgGrp, 0, sindf(arg0->scale.x), arg0->scale.y);
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

            for (i = 0; i < mbMgCallListNumTbl[mbMgCallType]; i++) {
                new_var = 0xE0;
                entry = &mbMgCallSlotTbl[i];
                HuWinPosSet(entry->obj, (entry->x + (entry->w / 2)), (entry->y + ((entry->h / 2) - new_var)));
                HuWinScaleSet(entry->obj, sindf(arg0->scale.x), arg0->scale.y);
            }

            new_var = 0xE0;
            HuSprPosSet(mbMgCallBgGrp, 0, 0xA0,
                                (mbMgCallSlotBaseY + (mbMgCallBgYTbl[mbMgCallType] - new_var)));

            HuSprScaleSet(mbMgCallBgGrp, 0, sindf(arg0->scale.x), arg0->scale.y);

            if (arg0->scale.x >= 90.0f) {
                MBMgCallCursorFXPlay();
                arg0->work[0] = 1;
                arg0->scale.x = 1.0f;
                arg0->scale.z = -1.0f;
                arg0->scale.y = 0.0f;
                arg0->work[1] = 0;
                arg0->work[2] = MBRand((f32)mbMgCallListNumTbl[mbMgCallType]);
                arg0->work[3] = 0;
                MBMgCallCursorSprCreate();
            }
            break;
        case 1:
            arg0->scale.z += arg0->scale.x;

            if (arg0->scale.z >= 1.0f) {
                if ((arg0->work[3] != 0) && (arg0->scale.x <= 0.08f)) {
                    arg0->work[3]--;
                }
                arg0->scale.z -= 1.0f;
                if (arg0->scale.y == 0.0f) {
                    arg0->work[1]++;
                    arg0->work[1] = arg0->work[1] % mbMgCallListNumTbl[mbMgCallType];
                } else {
                    arg0->work[1]--;
                    if (arg0->work[1] >= 0x80U) {
                        arg0->work[1] = mbMgCallListNumTbl[mbMgCallType] - 1;
                    }
                }
                MBMgCallCursorFXPlay();
            }

            for (i = 0; i < mbMgCallListNumTbl[mbMgCallType]; i++) {
                entry = &mbMgCallSlotTbl[i];
                if (i == arg0->work[1]) {
                    HuWinBGColSet(entry->obj, 0, 0xC8, 0);
                    HuWinBGTPLvlSet(entry->obj, 0x100);
                    HuWinPriSet(entry->obj, 0x2328);
                } else {
                    HuWinBGColSet(entry->obj, 0x40, 0x40, 0x80);
                    HuWinBGTPLvlSet(entry->obj, 0);
                    HuWinPriSet(entry->obj, 0x2710);
                }
            }

            if ((arg0->work[1] == arg0->work[2]) || (arg0->scale.x < 1.0f)) {
                arg0->scale.x -= 0.02;
            }

            if (arg0->scale.x <= 0.08f) {
                arg0->scale.x = 0.08f;
                if ((arg0->work[1] == arg0->work[2]) && (arg0->work[3] == 0) && ((arg0->scale.z + 0.08f) >= 1.0f)) {
                    if ((rand8() & 0xF) || (arg0->scale.y == 1.0f) || (arg0->work[1] == 0)) {
                        if ((GwSystem.show_minigame_explanations == FALSE) || (GwSystem.current_board_index == 6)) {
                            HuAudFXPlay(0x105);
                        } else {
                            HuAudFXPlay(0x112);
                        }

                        arg0->work[0] = 2;
                        arg0->work[3] = 0x3C;
                        HuWinNoCRSet(entry->obj);
                        HuWinHomeClear(mbMgCallSlotTbl[arg0->work[1]].obj);
                        HuWinMesSet(mbMgCallSlotTbl[arg0->work[1]].obj,
                                            mbMgCallMgList[arg0->work[1]] + FILE_FROM_OVL_ID(boardcall) - 1, HUWIN_POS_CENTER, 4);
                        HuWinMesColSet(mbMgCallSlotTbl[arg0->work[1]].obj, 1);
                        HuWinMesDefColSet(mbMgCallSlotTbl[arg0->work[1]].obj, 0xA0, 0xA0, 0xA0);
                        HuWinBGColSet(mbMgCallSlotTbl[arg0->work[1]].obj, 0xFE, 0xFF, 0xD0);
                        HuWinMesSpeedSet(mbMgCallSlotTbl[arg0->work[1]].obj, 0);
                    } else {
                        arg0->scale.y = 1.0f;
                        arg0->work[2]--;
                        if (arg0->work[2] >= 128) {
                            arg0->work[2] = mbMgCallListNumTbl[mbMgCallType] - 1;
                        }
                    }
                }
            }
            break;
        case 2:
            if (arg0->work[3] != 0) {
                arg0->work[3]--;
            } else {
                mbMgHis.recentMinigames[mbMgCallType][mbMgHisIdxWork.unk_04[mbMgCallType]] = mbMgCallMgList[arg0->work[2]];
                mbMgHisIdxWork.unk_04[mbMgCallType]++;

                if (_CheckFlag(0x20) != 0) {
                    mbMgHisIdxWork.unk_04[mbMgCallType] = (mbMgHisIdxWork.unk_04[mbMgCallType] % (s32)mbMgCallHisLenEasyTbl[mbMgCallType]);
                } else {
                    mbMgHisIdxWork.unk_04[mbMgCallType] = (mbMgHisIdxWork.unk_04[mbMgCallType] % (s32)mbMgCallHisLenTbl[mbMgCallType]);
                }
                GWMgNoSet(mbMgCallMgList[arg0->work[2]]);
                if (GwSystem.current_board_index != 6) {
                    MBTelopMgTypeKill();
                    MBMgCallClose();
                }
            }
            arg0->rot.z += 1.0f;
            if (arg0->rot.z >= 13.0f) {
                arg0->rot.z -= 13.0f;
            }
            break;
    }
    if (mbMgCallCursorGrp != -1) {

        for (i = 0; !(arg0->rot.z < (f32)*mbMgCallCursorAnimTbl[i]); i++) {}

        HuSprPosSet(mbMgCallCursorGrp, 0,
                            (mbMgCallCursorAnimTbl[i][1] + 50),
                            (mbMgCallCursorYTbl[mbMgCallType] + (arg0->work[1] * 20)));
    }
}

void MBMgCallHisInit(void) {
    s32 category;
    s32 minigameCategoryIndex;

    for (category = 0; category < MINIGAME_TYPE_END; category++) {
        for (minigameCategoryIndex = 0; minigameCategoryIndex < PREV_MINIGAME_LIST_LENGTH; minigameCategoryIndex++) {
            mbMgHis.recentMinigames[category][minigameCategoryIndex] = -1;
        }
        mbMgHisIdx[category] = 0;
    }
}

void MBMgCallInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbMgCallSlotTbl); i++) {
        mbMgCallSlotTbl[i].obj = -1;
    }

    mbMgCallListObj = NULL;
    mbMgCallBgAnim = -1;
    mbMgCallBgGrp = -1;
    mbMgCallCursorAnim = -1;
    mbMgCallCursorGrp = -1;
}

void MBMgCallClose(void) {
    ItemSlotEntry *entry;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mbMgCallSlotTbl); i++) {
        entry = &mbMgCallSlotTbl[i];
        if (entry->obj != -1) {
            HuWinKill(entry->obj);
            entry->obj = -1;
        }
    }

    if (mbMgCallListObj != NULL) {
        omDelObj(mbMgCallListObj);
        mbMgCallListObj = NULL;
    }

    if (mbMgCallBgGrp != -1) {
        HuSprGrpKill(mbMgCallBgGrp);
        mbMgCallBgGrp = -1;
    }

    if (mbMgCallBgAnim != -1) {
        HuSprAnimKill(mbMgCallBgAnim);
        mbMgCallBgAnim = -1;
    }

    if (mbMgCallCursorGrp != -1) {
        HuSprGrpKill(mbMgCallCursorGrp);
        mbMgCallCursorGrp = -1;
    }

    if (mbMgCallCursorAnim != -1) {
        HuSprAnimKill(mbMgCallCursorAnim);
        mbMgCallCursorAnim = -1;
    }
}

static void MBMgCallListBgSprCreate(void) {
    void *data;

    if (mbMgCallBgGrp == -1) {
        mbMgCallBgGrp = HuSprGrpCreate(1, 0);
        data = DataRead(0x130116);
        mbMgCallBgAnim = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(mbMgCallBgGrp, 0, mbMgCallBgAnim, 0);
        HuSprPriSet(mbMgCallBgGrp, 0, 0x4770);
        HuSprAttrSet(mbMgCallBgGrp, 0, HUSPR_ATTR_XLU);
        HuSprPosSet(mbMgCallBgGrp, 0, 0xA0, mbMgCallBgYTbl[mbMgCallType] + mbMgCallSlotBaseY);
    }
}

static void MBMgCallCursorSprCreate(void) {
    void *data;

    if (mbMgCallCursorGrp == -1) {
        mbMgCallCursorGrp = HuSprGrpCreate(1, 4);
        data = DataRead(0x130210);
        mbMgCallCursorAnim = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(mbMgCallCursorGrp, 0, mbMgCallCursorAnim, 0);
        HuSprPriSet(mbMgCallCursorGrp, 0, 0x100);
        HuSprAttrSet(mbMgCallCursorGrp, 0, HUSPR_ATTR_NONE);
        HuSprPosSet(mbMgCallCursorGrp, 0, 0x32, mbMgCallCursorYTbl[mbMgCallType]);
    }
}

// TODO: this function is a confusing mess. BUG_FIX macros should work to make it act correctly?
void MBMgCallListCreate(s32 arg0) {
    Sp18Struct sp18;
    ItemSlotEntry *entry;
    omObjData *obj;
    s32 category;
    s32 minigame;
    s32 forbidCount;
    s32 count;
    s32 i;
    s32 j;
    s32 k;

    sp18.rectTable = mbMgCallRectTbl;
    sp18.notRectTable1 = mbMgCallMgTbl;
    sp18.notRectTable2 = mbMgCallMgEasyTbl;

    switch (arg0) {
        case -1:
            category = MBMgTypeCalc();
            if (category == -1) {
                category = 3;
            }
            break;
        case 0:
        default:
            category = 3;
            break;
        case 1:
            category = 4;
            break;
        case 2:
            category = 5;
            break;
    }

    mbMgCallType = category;

    for (i = 0; i < mbMgCallListNumTbl[category]; i++) {
        entry = &mbMgCallSlotTbl[i];

#ifdef BUG_FIX
        // new way to get xy and width/height. Original code crashes for some reason but this logic works out the same
        entry->x = mbMgCallRectTbl.rects[category]->x;
        entry->y = mbMgCallRectTbl.rects[category]->y + (i * 20);
        entry->w = mbMgCallRectTbl.rects[category]->w;
        entry->h = mbMgCallRectTbl.rects[category]->h;
#else
        entry->x = sp18.rectTable.rects[category][i].x;
        entry->y = sp18.rectTable.rects[category][i].y;
        entry->w = sp18.rectTable.rects[category][i].w;
        entry->h = sp18.rectTable.rects[category][i].h;
#endif

        entry->obj = HuWinCreate(
            (entry->x + (entry->w / 2)),
            (entry->y + (entry->h / 2)),
            entry->w,
            entry->h,
            0, 4);
        HuWinPriSet(entry->obj, 0x2328);
        HuWinDummy(entry->obj);
        HuWinCenterPosSet(entry->obj, entry->w / 2, entry->h / 2);
        HuWinBGTPLvlSet(entry->obj, 0);

        while (1) {
#ifdef BUG_FIX
            if (_CheckFlag(0x20)) {
                mbMgCallMgList[i] = ((u8 *)mbMgCallMgEasyTbl.notRects[category])[MBRand(mbMgCallMgNumEasyTbl[category])];
            } else {
                mbMgCallMgList[i] = ((u8 *)mbMgCallMgTbl.notRects[category])[MBRand(mbMgCallMgNumTbl[category])];
            }
#else
            if (_CheckFlag(0x20)) {
                mbMgCallMgList[i] = sp18.notRectTable2.notRects[category]->x[MBRand(mbMgCallMgNumEasyTbl[category])];
            } else {
                mbMgCallMgList[i] = sp18.notRectTable1.notRects[category]->x[MBRand(mbMgCallMgNumTbl[category])];
            }
#endif

            for (j = 0; j < i; j++) {
                if (j == i) {
                    continue;
                }
                if (mbMgCallMgList[j] == mbMgCallMgList[i]) {
                    break;
                }
            }

            if (j != i) {
                continue;
            }

            forbidCount = _CheckFlag(0x20) ? mbMgCallHisLenEasyTbl[category] : mbMgCallHisLenTbl[category];
            for (k = 0; k < forbidCount; k++) {
                if (mbMgCallMgList[i] == mbMgHis.recentMinigames[category][k]) {
                    break;
                }
            }

            if (k != forbidCount) {
                continue;
            }

            if (MBTurnTierGet(CUR_TURN) == TURN_TIER_EARLY_GAME) {
                minigame = mbMgCallMgList[i];
                if (minigame == puddle_paddle) {
                    continue;
                }

                if (minigame == ((minigame >= etch_n_catch) ? parasol_plummet : river_raiders)) {
                    continue;
                }
            }
            break;
        }

        HuWinNoCRSet(entry->obj);

        if (GWMgUnlockCheck(mbMgCallMgList[i] - 1) != FALSE) {
            HuWinMesSet(entry->obj, mbMgCallMgList[i] + FILE_FROM_OVL_ID(boardcall) - 1, HUWIN_POS_CENTER, 4);
        } else {
            HuWinMesSet(entry->obj, 0x4748, HUWIN_POS_CENTER, 4);
        }

        HuWinMesColSet(entry->obj, mbMgCallMesColTbl[mbMgCallMgList[i] - 1]);
        HuWinMesSpeedSet(entry->obj, 0);
    }

    obj = omAddObj(-0x8000, 0, 0, -1, MBMgCallListExec);
    mbMgCallListObj = obj;
    obj->work[0] = 3;
    obj->work[1] = 5;
    obj->trans.y = 0.0f;
    obj->scale.x = 10.0f;
    obj->scale.y = 0.0f;
    obj->rot.z = 0.0f;
    MBMgCallListBgSprCreate();

    HuSprColorSet(mbMgCallBgGrp, 0,
                        mbMgCallColorTbl[mbMgCallType][0],
                        mbMgCallColorTbl[mbMgCallType][1],
                        mbMgCallColorTbl[mbMgCallType][2]);
}

void MBMgCallListClose(void) {
    mbMgCallListObj->work[0] = 0;
}

// Fisher–Yates shuffle via selection with removal
void MBArrayShuffle(u8 *output, s32 count) {
    s8 pool[256];
    s32 i;
    s32 j;
    s32 randIndex;

    for (i = 0; i <= count; i++) {
        pool[i] = i;
    }

    for (i = 0; i <= count; i++) {
        randIndex = MBRand((f32)(count - i + 1));
        output[i] = pool[randIndex];

        /* Remove picked element by shifting the rest down */
        for (j = randIndex; j < count; j++) {
            pool[j] = pool[j + 1];
        }
    }
}

static void MBMgCallColorGet(u8 *outSpaceTypes) {
    s32 redAssignmentFlags[MB_MAX_PLAYERS];
    u8 shuffledOrder[MB_MAX_PLAYERS];
    s32 greenCount;
    s32 blueCount;
    s32 i;
    s32 greenIndex;
    s32 randPercent;

    /* Zero out redAssignmentFlags array */
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        redAssignmentFlags[i] = 0;
    }

    /* Count how many players are BLUE and HAPPENING */
    greenCount = 0;
    blueCount = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (MBStatusColorGet(i) == SPACE_BLUE) {
            blueCount++;
        } else if (MBStatusColorGet(i) != SPACE_RED) {
            greenCount += MBStatusColorGet(i) == SPACE_GREEN;
        }
    }

    randPercent = MBRand(100.0f);

    /* Decide which green slots become SPACE_RED */
    switch (greenCount) {
        case 1:
            switch (blueCount) {
                case 3:
                    if (randPercent < 30) {
                        redAssignmentFlags[0] = 1;
                    }
                    break;
                case 2:
                    if (randPercent < 50) {
                        redAssignmentFlags[0] = 1;
                    }
                    break;
                case 1:
                    if (randPercent < 50) {
                        redAssignmentFlags[0] = 1;
                    }
                    break;
                case 0:
                    if (randPercent < 70) {
                        redAssignmentFlags[0] = 1;
                    }
                    break;
            }
            break;

        case 2:
            switch (blueCount) {
                case 2:
                    if (randPercent < 15) {
                        redAssignmentFlags[1] = 1;
                        redAssignmentFlags[0] = 1;
                    } else if (randPercent < 30) {
                        redAssignmentFlags[1] = 1;
                    }
                    break;
                case 1:
                    if (randPercent < 25) {
                        redAssignmentFlags[1] = 1;
                        redAssignmentFlags[0] = 1;
                    } else if (randPercent < 75) {
                        redAssignmentFlags[1] = 1;
                    }
                    break;
                case 0:
                    if (randPercent < 70) {
                        redAssignmentFlags[1] = 1;
                        redAssignmentFlags[0] = 1;
                    } else if (randPercent < 85) {
                        redAssignmentFlags[1] = 1;
                    }
                    break;
            }
            break;

        case 3:
            switch (blueCount) {
                case 1:
                    if (randPercent < 7) {
                        redAssignmentFlags[2] = 1;
                        redAssignmentFlags[1] = 1;
                        redAssignmentFlags[0] = 1;
                    } else if (randPercent < 22) {
                        redAssignmentFlags[2] = 1;
                        redAssignmentFlags[1] = 1;
                    } else if (randPercent < 30) {
                        redAssignmentFlags[2] = 1;
                    }
                    break;
                case 0:
                    if (randPercent < 70) {
                        redAssignmentFlags[2] = 1;
                        redAssignmentFlags[1] = 1;
                        redAssignmentFlags[0] = 1;
                    } else if (randPercent < 78) {
                        redAssignmentFlags[2] = 1;
                        redAssignmentFlags[1] = 1;
                    } else if (randPercent < 93) {
                        redAssignmentFlags[2] = 1;
                    }
                    break;
            }
            break;

        case 4:
            if (randPercent < 35) {
                redAssignmentFlags[3] = 1;
                redAssignmentFlags[2] = 1;
                redAssignmentFlags[1] = 1;
                redAssignmentFlags[0] = 1;
            } else if (randPercent < 42) {
                redAssignmentFlags[3] = 1;
                redAssignmentFlags[2] = 1;
                redAssignmentFlags[1] = 1;
            } else if (randPercent < 57) {
                redAssignmentFlags[3] = 1;
                redAssignmentFlags[2] = 1;
            } else if (randPercent < 65) {
                redAssignmentFlags[3] = 1;
            }
            break;
    }

    /* Shuffle Happening player indices */
    MBArrayShuffle(shuffledOrder, greenCount - 1);

    greenIndex = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        switch (MBStatusColorGet(i)) {
            case SPACE_RED:
                outSpaceTypes[i] = SPACE_RED;
                break;
            case SPACE_BLUE:
                outSpaceTypes[i] = SPACE_BLUE;
                break;
            case SPACE_GREEN:
                if (redAssignmentFlags[shuffledOrder[greenIndex++]] == FALSE) {
                    outSpaceTypes[i] = SPACE_BLUE;
                } else {
                    outSpaceTypes[i] = SPACE_RED;
                }
                break;
        }
    }
}

ItemRectTable const mbMgCallRectTbl = {
    { mbMgCallRect5Tbl,
      mbMgCallRect3Tbl,
      mbMgCallRect3Tbl,
      mbMgCallRect3Tbl,
      mbMgCallRect3Tbl,
      mbMgCallRect5Tbl }
};

DefinitelyNotItemRectTable const mbMgCallMgTbl = {
    { (DefinitelyNotItemRect *)mbMgCall4PTbl,
      (DefinitelyNotItemRect *)mbMgCall1vs3Tbl,
      (DefinitelyNotItemRect *)mbMgCall2vs2Tbl,
      (DefinitelyNotItemRect *)mbMgCallItemTbl,
      (DefinitelyNotItemRect *)mbMgCallBattleTbl,
      (DefinitelyNotItemRect *)mbMgCall1vs1Tbl }
};

DefinitelyNotItemRectTable const mbMgCallMgEasyTbl = {
    { (DefinitelyNotItemRect *)mbMgCall4PEasyTbl,
      (DefinitelyNotItemRect *)mbMgCall1vs3EasyTbl,
      (DefinitelyNotItemRect *)mbMgCall2vs2EasyTbl,
      (DefinitelyNotItemRect *)mbMgCallItemEasyTbl,
      (DefinitelyNotItemRect *)mbMgCallBattleEasyTbl,
      (DefinitelyNotItemRect *)mbMgCall1vs1EasyTbl }
};

static void MBMgCallExec(void) {
    u8 sp10[MB_MAX_PLAYERS];
    u8 spaceTypes[MB_MAX_PLAYERS];
    u32 sp20[2];
    s32 init;
    Object *temp_v0;
    Process *process;
    s32 var_s1;
    s32 xVelocity;
    u32 var_s5;
    u32 *temp_s2;
    s32 j, k;

    process = HuPrcCurrentGet();
    sp20[0] = 1;
    sp20[1] = (0x000A << 16) | 0x007C;
    var_s5 = 0;
    xVelocity = 0;
    init = 0;
    do {
        temp_v0 = MBModelCreate(0x3B, sp20);
        MBModelTempAllocFree(temp_v0);
        HuVecCopy3F(&temp_v0->coords, &mbCameraFocusPos);
    } while (0);
    HuVecCopyXYZ(&temp_v0->scale, 1.2f, 1.2f, 1.2f);
    temp_v0->velocity.x = 120.0f;
    MBMotionSet(temp_v0, 0, 0);
    HuPrcVSleep();
    Hu3DMotionAttrSet(temp_v0->omObj1->model[0], 2, 1);
    temp_s2 = process->user_data;

    for (;;) {
        switch (var_s5) {
            case 0:
                break;
            case 1:
                if ((init == 0) && (temp_v0->velocity.x < 100.0f)) {
                    init = 1;
                    HuAudFXPlay(0x156);
                }
                if ((temp_v0->velocity.x > 30.0f)) {
                    temp_v0->velocity.x -= 10.0f;
                } else {
                    var_s5 = 2;
                    xVelocity = 0;
                    Hu3DMotionAttrSet(temp_v0->omObj1->model[0], 1, 0);
                }
                break;
            case 2:
                if (xVelocity++ >= 0xA) {
                    xVelocity = 5;
                    var_s5 = 3;
                }
                break;
            case 3:
                if (xVelocity != 0) {
                    temp_v0->velocity.x += (f32)xVelocity;
                    xVelocity -= 1;
                    break;
                }

                var_s5 = 4;
                break;

            case 4:
                if (xVelocity++ >= 0xF) {
                    MBModelDispOff(temp_v0);
                }
                break;
        }

        switch (*temp_s2) {
            case 0:
                MBStatusDispMoveSet(4);
                *temp_s2 = 0xAU;
                break;
            case 10:
                if (MBStatusMoveCheck() == 0) {
                    *temp_s2 = 0xBU;
                }
                break;
            case 11:
                for (var_s1 = 0, j = 0; j < MB_MAX_PLAYERS; j++) {
                    if (MBStatusColorGet(j) == SPACE_HAPPENING) {
                        var_s1 = 1;
                        sp10[j] = 1;
                    } else {
                        sp10[j] = 0;
                    }
                }

                if (var_s1) {
                    *temp_s2 = 0xC;
                } else {
                    *temp_s2 = 1;
                    var_s5 = 1;
                }
                break;
            case 12:
                MBMgCallColorGet(spaceTypes);
                HuAudFXPlay(0x13F);
                for (j = 0; j < 24; j++) {
                    for (k = 0; k < MB_MAX_PLAYERS; k++) {
                        s16 temp = sp10[k] != 0; // TODO: regalloc hack
                        if (temp) {
                            MBStatusColorSet(k, j + 5);
                        }
                    }
                    HuPrcVSleep();
                }

                for (j = 0; j < MB_MAX_PLAYERS; j++) {
                    if (MBStatusColorGet(j) != spaceTypes[j]) {
                        MBStatusColorSet(j, spaceTypes[j]);
                    }
                }

                *temp_s2 = 1;
                var_s5 = 1;
                break;
            case 1:
                if (MBStatusMoveCheck() == 0) {
                    HuPrcSleep(1);
                    MBTelopMgTypeCreate(0, 0x25);
                    HuPrcSleep(5);
                    *temp_s2 += 1;
                }
                break;
            case 2:
                MBStatusDispMoveSet(2);
                MBVsSprCreate();
                *temp_s2 = *temp_s2 + 1;
                break;
            case 3:
                if (MBStatusMoveCheck() == 0) {
                    for (j = 0; j < MB_MAX_PLAYERS; j++) {
                        if (!(GwPlayer[j].stat & PLAYER_IS_CPU)) {
                            break;
                        }
                    }

                    if (j != MB_MAX_PLAYERS) {
                        for (j = 0; j < MB_MAX_PLAYERS; j++) {
                            if ((HuPadBtnDown[GwPlayer[j].pad] & A_BUTTON) && !(GwPlayer[j].stat & PLAYER_IS_CPU)) {
                                break;
                            }
                        }
                        if (j == MB_MAX_PLAYERS) {
                            break;
                        }
                    }
                    if (MBMgTypeCalc() != -1) {
                        MBMgCallListClose();
                        MBStatusDispMoveSet(5);
                    } else {
                        GWMgNoSet(-1);
                    }
                    *temp_s2 += 1;
                    break;
                }
                break;
            case 4:
                if ((MBMgTypeCalc() == -1) || (MBTelopMgTypeStatGet() == 0)) {
                    MBVsSprKill();
                    MBModelKill(temp_v0);
                    omDelPrcObj(NULL);
                }
                break;
        }

        HuPrcVSleep();
    }
}

typedef struct UnkSize10 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 curPlayerNo;
    /* 0x08 */ char unk_08[0x08];
} UnkSize10;

// TODO: this and MBMgCallBattleCreate might potentially use different structs that happen to be the same size. unsure
Process *MBMgCallCreate(void) {
    Process *proc;
    UnkSize10 *data;

    proc = omAddPrcObj(&MBMgCallExec, 0, 0x2000, 0x40);
    data = HuMemMemoryAlloc(proc->heap, sizeof(UnkSize10));
    proc->user_data = data;
    data->unk_00 = 0;
    return proc;
}

static void MBMgCallBattleExec(void) {
    UnkSize10 *temp_s0;
    s32 i;

    temp_s0 = HuPrcCurrentGet()->user_data;

    while (1) {
        switch (temp_s0->unk_00) {
            case 0:
                MBStatusDispMoveSet(4);
                HuPrcSleep(0x14);
                temp_s0->unk_00++;
                break;
            case 1:
                if (MBStatusMoveCheck() == 0) {
                    HuPrcSleep(1);
                    MBTelopMgTypeCreate(temp_s0->curPlayerNo, 7);
                    HuPrcSleep(5);
                    temp_s0->unk_00++;
                }
                /* fallthrough */
            case 2:
                MBStatusDispMoveSet(2);
                MBVsSprCreate();
                temp_s0->unk_00++;
                break;
            case 3:
                if (MBStatusMoveCheck() == 0) {
                    for (i = 0; i < MB_MAX_PLAYERS; i++) {
                        if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
                            break;
                        }
                    }
                    if (i == MB_MAX_PLAYERS) {
                        MBMgCallListClose();
                        MBStatusDispMoveSet(5);
                        temp_s0->unk_00++;
                        break;
                    } else {
                        for (i = 0; i < MB_MAX_PLAYERS; i++) {
                            if (!(HuPadBtnDown[GwPlayer[i].pad] & A_BUTTON) || (GwPlayer[i].stat & PLAYER_IS_CPU)) {
                                continue;
                            } else {
                                break;
                            }
                        }
                        if (i != MB_MAX_PLAYERS) {
                            MBMgCallListClose();
                            MBStatusDispMoveSet(5);
                            temp_s0->unk_00++;
                            break;
                        }
                    }
                }
                break;
            case 4:
                if (mbMgCallBgGrp == -1) {
                    MBVsSprKill();
                    omDelPrcObj(NULL);
                }
                break;
        }
        HuPrcVSleep();
    }
}

Process *MBMgCallBattleCreate(void) {
    Process *temp_v0;
    UnkSize10 *temp_v0_2;

    temp_v0 = omAddPrcObj(&MBMgCallBattleExec, 0, 0x2000, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(temp_v0->heap, sizeof(UnkSize10));
    temp_v0->user_data = temp_v0_2;
    temp_v0_2->unk_00 = 0;
    temp_v0_2->curPlayerNo = 2;
    return temp_v0;
}

static void MBMgCallGambleProc(void) {
    u32 sp20[2];
    Object *temp_v0;
    Process *process;
    s32 var_s1;
    s32 xVelocity;
    u32 var_s5;
    UnkSize10 *temp_s2;
    s32 j, k;

    process = HuPrcCurrentGet();
    sp20[0] = 1;
    sp20[1] = (0x000A << 16) | 0x001B;
    var_s5 = 1;
    xVelocity = 0;

    temp_v0 = MBModelCreate(9, sp20);
    MBModelTempAllocFree(temp_v0);
    HuVecCopy3F(&temp_v0->coords, &MBPlayerGet(CUR_PLAYER)->player_obj->coords);

    temp_v0->velocity.x = 120.0f;
    MBMotionSet(temp_v0, 0, 0);
    HuPrcVSleep();
    Hu3DMotionAttrSet(temp_v0->omObj1->model[0], 2, 1);
    temp_s2 = process->user_data;
    HuAudFXPlay(0x156);

    for (;;) {
        switch (var_s5) {
            case 0:
                break;
            case 1:
                if ((temp_v0->velocity.x > 30.0f)) {
                    temp_v0->velocity.x -= 10.0f;
                } else {
                    var_s5 = 2;
                    xVelocity = 0;
                    Hu3DMotionAttrSet(temp_v0->omObj1->model[0], 1, 0);
                }
                break;
            case 2:
                if (xVelocity++ >= 0xA) {
                    xVelocity = 5;
                    var_s5 = 3;
                }
                break;
            case 3:
                if (xVelocity != 0) {
                    temp_v0->velocity.x += (f32)xVelocity;
                    xVelocity -= 1;
                    break;
                }

                var_s5 = 4;
                break;

            case 4:
                if (xVelocity++ >= 0xF) {
                    MBModelDispOff(temp_v0);
                }
                break;
        }

        switch (temp_s2->unk_00) {
            case 0:
                MBStatusDispMoveSet(temp_s2->curPlayerNo + 6);
                MBTelopMgTypeCreate(1, 0x1F);
                temp_s2->unk_00++;
                break;
            case 1:
                if ((MBStatusMoveCheck() == 0) &&
                    (((HuPadBtnDown[GwPlayer[temp_s2->curPlayerNo].pad] & A_BUTTON) && !(GwPlayer[temp_s2->curPlayerNo].stat & 1)) || (GwPlayer[temp_s2->curPlayerNo].stat & 1))) {
                    MBMgCallListClose();
                    MBStatusDispMoveSet(5);
                    temp_s2->unk_00++;
                    break;
                }
                break;
            case 2:
                if (mbMgCallBgGrp == -1) {
                    MBModelKill(temp_v0);
                    omDelPrcObj(NULL);
                }
                break;
        }
        HuPrcVSleep();
    }
}

Process *MBMgCallGambleCreate(void) {
    Process *temp_v0;
    UnkSize10 *temp_v0_2;

    temp_v0 = omAddPrcObj(MBMgCallGambleProc, 0, 0x2000, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(temp_v0->heap, sizeof(UnkSize10));
    temp_v0->user_data = temp_v0_2;
    temp_v0_2->unk_00 = 0;
    temp_v0_2->curPlayerNo = GwSystem.current_player_index;
    return temp_v0;
}

typedef struct UnkSize10_2 {
    s32 unk_00;
    s32 curPlayerNo;
    s32 unk_08;
    char unk_0C[4];
} UnkSize10_2;

static void MBMgCallKettouProc(void) {
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    UnkSize10_2 *temp_s0;

    temp_s0 = HuPrcCurrentGet()->user_data;
    while (1) {
        switch (temp_s0->unk_00) {
            case 0:
                MBTelopMgTypeCreate(3, 7);
                MBStatusTeamPlayerSet(temp_s0->curPlayerNo, temp_s0->unk_08);
                MBStatusDispMoveSet(0x1B);
                MBVsSprCreate();
                temp_s0->unk_00++;
                break;
            case 1:
                if ((MBStatusMoveCheck() == 0) &&
                    (((GwPlayer[temp_s0->curPlayerNo].stat & PLAYER_IS_CPU) && (GwPlayer[temp_s0->unk_08].stat & PLAYER_IS_CPU)) || ((HuPadBtnDown[GwPlayer[temp_s0->curPlayerNo].pad] & A_BUTTON) && !(GwPlayer[temp_s0->curPlayerNo].stat & PLAYER_IS_CPU)) || ((HuPadBtnDown[GwPlayer[temp_s0->unk_08].pad] & A_BUTTON) && !(GwPlayer[temp_s0->unk_08].stat & PLAYER_IS_CPU)))) {
                    MBMgCallListClose();
                    MBStatusDispMoveSet(5);
                    temp_s0->unk_00++;
                    break;
                }
                break;
            case 2:
                if (mbMgCallBgGrp == -1) {
                    MBVsSprKill();
                    omDelPrcObj(NULL);
                }
                break;
        }
        HuPrcVSleep();
    }
}

Process *MBMgCallKettouCreate(s32 arg0, s32 arg1) {
    Process *temp_v0;
    UnkSize10_2 *temp_v0_2;

    temp_v0 = omAddPrcObj(MBMgCallKettouProc, 0, 0x2000, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(temp_v0->heap, sizeof(UnkSize10_2));
    temp_v0->user_data = temp_v0_2;
    temp_v0_2->unk_00 = 0;
    temp_v0_2->curPlayerNo = arg0;
    temp_v0_2->unk_08 = arg1;
    return temp_v0;
}

static void MBMgCallTutorialExec(void) {
    u8 happeningPlayers[MB_MAX_PLAYERS];
    u8 spaceTypes[MB_MAX_PLAYERS];
    s32 i;
    s32 j;
    s32 *temp_s3;

    temp_s3 = HuPrcCurrentGet()->user_data;

    while (1) {
        switch (*temp_s3) {
            case 10:
                if (MBStatusMoveCheck() == 0) {
                    *temp_s3 = 0xB;
                }
                break;
            case 11:
                for (j = 0, i = 0; i < MB_MAX_PLAYERS; i++) {
                    if (MBStatusColorGet(i) == SPACE_HAPPENING) {
                        j = 1;
                        happeningPlayers[i] = 1;
                    } else {
                        happeningPlayers[i] = 0;
                    }
                }
                if (j == 0) {
                    *temp_s3 = 1;
                } else {
                    *temp_s3 = 0xC;
                }
                break;
            case 12:
                MBMgCallColorGet(spaceTypes);
                HuAudFXPlay(0x13F);
                for (i = 0; i < 24; i++) {
                    for (j = 0; j < MB_MAX_PLAYERS; j++) {
                        if (happeningPlayers[j] != 0) {
                            MBStatusColorSet(j, i + 5);
                        }
                    }
                    HuPrcVSleep();
                }
                for (i = 0; i < MB_MAX_PLAYERS; i++) {
                    if (MBStatusColorGet(i) != spaceTypes[i]) {
                        MBStatusColorSet(i, spaceTypes[i]);
                    }
                }
                *temp_s3 = 1;
                break;
            case 1:
                omDelPrcObj(NULL);
                break;
        }
        HuPrcVSleep();
    }
}

Process *MBMgCallTutorialCreate(void) {
    Process *temp_v0;
    UnkSize10_2 *temp_v0_2;

    temp_v0 = omAddPrcObj(MBMgCallTutorialExec, 0, 0x2000, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(temp_v0->heap, sizeof(UnkSize10_2));
    temp_v0->user_data = temp_v0_2;
    temp_v0_2->unk_00 = 0xA;
    return temp_v0;
}
