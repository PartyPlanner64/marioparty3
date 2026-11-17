#include "common_board.h"
#include "game/overlays/party/common/move.h"
#include "game/overlays/party/common/model.h"
#include "game/overlays/party/common/status.h"
#include "game/overlays/party/common/back.h"
#include "game/overlays/party/common/helpwin.h"
#include "game/overlays/party/common/pause.h"
#include "game/overlays/party/common/player.h"
#include "game/overlays/party/common/main.h"
#include "game/overlays/party/common/window.h"
#include "game/overlays/party/common/vibrate.h"
#include "game/overlays/party/common/sprgrp.h"
#include "game/overlays/party/common/item.h"
#include "game/overlays/party/common/mgcall.h"

typedef struct KoopaWinPos {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
} KoopaWinPos; // sizeof 0x8

typedef struct UnkBowser2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
} UnkBowser2; // sizeof 0x24

typedef struct KoopaRouletteWork {
    /* 0x00 */ s16 windows[5][5];
    /* 0x32 */ u8 events[5];
} KoopaRouletteWork; // sizeof 0x38

void MBPlayerRevAllSet(void);
void MBPlayerRevAllReset(void);
void koopa_SpellEffExec(s32);
void MBStatusPulseStart(s32);
void MBStatusPulseStop(s32);
void koopa_MainProc(void);
void koopa_ExitCheckObjMain(omObjData *);
void koopa_SysInit(void);
void koopa_BackInit(void);
void koopa_ExitObjMain(omObjData *);
void koopa_BackClose(void);
void koopa_SysClose(void);
void koopa_StatusShowExec(void);
void koopa_RouletteCreate(void);
void koopa_RouletteObjMain(omObjData *);
void koopa_CursorCreate(void);
void koopa_CursorKill(void);
void koopa_RouletteKill(void);
s32 koopa_CoinAmountGet(s32, s32);
s32 koopa_SuitGiveExec(void);
s32 koopa_PhoneGiveExec(void);
s32 koopa_RevSetExec(void);
s32 koopa_RevResetExec(void);
s32 koopa_ShuffleExec(void);
s32 koopa_RevoExec(void);
s32 koopa_LeaveExec(void);
s32 koopa_CoinTakeExec(void);
s32 koopa_CoinTakeAllExec(void);

// Aliases into koopa_rouletteWork (see undefined_syms.txt).
extern s16 koopa_rouletteWinTbl[5][5];
extern u8 koopa_rouletteEventTbl[5];

extern u32 scRetraceCnt;

//.data
void *koopa_helpWin = 0;

s32 koopa_rouletteMesTbl[] = {
    0x00004200,
    0x00004201,
    0x00004202,
    0x00004203,
    0x00004204,
    0x00004205,
    0x00004206,
    0x00004207,
    0x00004208,
    0x00004209,
};

KoopaWinPos koopa_rouletteWinPosTbl[] = {
    { 64, -206, 200, 20 },
    { 64, -186, 200, 20 },
    { 64, -166, 200, 20 },
    { 64, -146, 200, 20 },
    { 64, -126, 200, 20 }
};

u8 koopa_cursorPosY = 94;
s8 koopa_cursorOfsTbl[] = { 1, 0, 9, 15, 11, 8, 13, 0 };
Vec koopa_koopaPos = { 0.0f, 0.0f, 2250.0f };
Vec koopa_leavePos = { 0.0f, 0.0f, -1000.0f };

UnkBowser2 koopa_koopaMot = {
    0x00000008, 0x000A0035, 0x000A0032, 0x000A0038,
    0x000A0040, 0x000A0043, 0x000A0041, 0x000A0042, 0x000A0044
};

s32 (*koopa_eventFuncTbl[])(void) = {
    koopa_CoinTakeExec,
    koopa_CoinTakeAllExec,
    koopa_SuitGiveExec,
    koopa_PhoneGiveExec,
    koopa_RevSetExec,
    koopa_RevResetExec,
    koopa_ShuffleExec,
    koopa_RevoExec,
    koopa_LeaveExec,
    koopa_LeaveExec
};

u32 koopa_cursorSeTime = 0;
s16 koopa_shuffleBlockMasuTbl[] = { 90, 89, 87, 71, 70, 84, 85, 86, 62, 61, 58, 59, 60, -1 };
u16 koopa_coinAmountTbl[2][3][4] = {
    { { 20, 20, 10, 10 },
      { 20, 20, 15, 15 },
      { 30, 30, 20, 20 } },
    { { 10, 10, 10, 10 },
      { 20, 20, 20, 20 },
      { 30, 30, 30, 30 } }
};

// unused
s16 koopa_unusedCoinTbl[][2] = {
    { 20, 20 },
    { 30, 30 },
    { 30, 30 },
    { 40, 40 },
    { 30, 40 },
    { 50, 50 },
    { 0, 0 }
};

//.bss
u8 koopa_boardNo BSS;
s32 koopa_playerNo BSS;
Object *koopa_koopaMdl BSS;
s32 koopa_introAltF BSS; // 1-in-5 alternate intro: Bowser starts in motion 7 and plays motion 4 backwards
s32 koopa_rouletteStopOfs BSS;
s32 koopa_rouletteLeaveF BSS;
char koopa_coinStr[16] BSS;
KoopaRouletteWork koopa_rouletteWork BSS;
omObjData *koopa_rouletteObj BSS;
s16 koopa_lampSprGrpTbl[2] BSS;
s16 koopa_lampSpr BSS;
s16 koopa_titleSprGrp BSS;
s16 koopa_titleSpr BSS;
s16 koopa_backSprGrp BSS;
s16 koopa_backSpr BSS;
s16 koopa_cursorSprGrp BSS;
s16 koopa_cursorSpr BSS;
s32 koopa_rouletteResult BSS;
s32 koopa_result2 BSS;

//.text
void koopa_ObjectSetup(void) {
    s32 i;

    koopa_boardNo = GwSystem.current_board_index;
    koopa_playerNo = GwSystem.playerIndexVisitingBowser;
    omInitObjMan(0x32, 0x32);
    koopa_BackInit();
    koopa_SysInit();
    MBShadowHeightMaxSet(1000.0f);
    HuWinInit();
    MBStatusCreate();
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBStatusPosSet(i, 0x1E, -0x32);
    }
    omAddPrcObj(koopa_MainProc, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, koopa_ExitCheckObjMain);
    MBMasuInit();
    MBMasuCreate(0x13, 0x23A);
    omGameSysInit();
}

void koopa_CursorFXPlay(void) {
    if (scRetraceCnt >= (koopa_cursorSeTime + 4)) {
        HuAudFXPlay(0x104);
        koopa_cursorSeTime = scRetraceCnt;
    }
}

void koopa_RouletteObjMain(omObjData *obj) {
    s16 *window;
    s32 i;
    s32 index = 0;
    u16 buttons;

    switch (obj->work[0]) {
        case 0:
            obj->trans.y += 16.0f;
            for (i = 0; i < 5; i++) {
                window = koopa_rouletteWinTbl[i];
                HuWinPosSet(window[0], window[1] + window[3] / 2, (window[2] + window[4] / 2) + (s16)obj->trans.y);
            }
            if (koopa_backSprGrp != -1) {
                HuSprPosSet(koopa_backSprGrp, 0, koopa_rouletteWinTbl[0][1] + 100, (s32)obj->trans.y + koopa_rouletteWinTbl[0][2] + 50);
            }
            if (koopa_titleSprGrp != -1) {
                HuSprPosSet(koopa_titleSprGrp, 0, koopa_rouletteWinTbl[0][1] + 100, (s32)obj->trans.y + koopa_rouletteWinTbl[0][2] - 30);
            }
            for (i = 0; i < 2; i++) {
                if (koopa_lampSprGrpTbl[i] != -1) {
                    HuSprPosSet(koopa_lampSprGrpTbl[i], 0, koopa_rouletteWinTbl[0][1] + i * 200, (s32)obj->trans.y + koopa_rouletteWinTbl[0][2] - 40);
                }
            }
            if (obj->trans.y >= 288.0f) {
                koopa_CursorFXPlay();
                koopa_helpWin = MBHelpWinCreate(23, 200, 1);
                obj->work[0] = 1;
                obj->scale.x = 0.5f;
                obj->scale.z = -1.0f;
                obj->scale.y = 0;
                obj->work[1] = 0;
                obj->work[3] = 0;
                obj->trans.z = 0;
                obj->rot.y = koopa_rouletteStopOfs;
                if (koopa_rouletteLeaveF != 0) {
                    for (i = 0; i < 5; i++) {
                        if (koopa_rouletteEventTbl[i] >= 8) {
                            index = i - (s32)obj->rot.y;
                            break;
                        }
                    }
                    if (index < 0) {
                        index += 5;
                    } else {
                        index %= 5;
                    }
                    obj->work[2] = index;
                } else {
                    obj->work[2] = 0;
                }
                i = MBRand(100.0f);
                if (i < 60) {
                    obj->mdlcnt = 20;
                } else if (i < 90) {
                    obj->mdlcnt = 14;
                } else {
                    obj->mdlcnt = 8;
                }
                obj->mtncnt = 0;
                koopa_CursorCreate();
            }
            break;
        case 1:
            if (obj->trans.z == 0) {
                if (GwPlayer[koopa_playerNo].stat & 1) {
                    obj->trans.z = 1.0f;
                } else {
                    buttons = ContBtnDown[GwPlayer[koopa_playerNo].pad];
                    if (buttons & A_BUTTON) {
                        obj->trans.z = 1.0f;
                    }
                }
                if (obj->trans.z == 1.0f && koopa_helpWin != 0) {
                    MBHelpWinKill(koopa_helpWin);
                    koopa_helpWin = 0;
                }
                if (koopa_rouletteLeaveF == 0) {
                    for (i = 0;; i++) {
                        index = i + obj->work[1];
                        if (index < 0) {
                            index += 5;
                        } else {
                            index %= 5;
                        }
                        if (koopa_rouletteEventTbl[index] < 8) {
                            index -= (s32)obj->rot.y;
                            if (index < 0) {
                                index += 5;
                                break;
                            }
                            index %= 5;
                            break;
                        }
                    }
                    obj->work[2] = index;
                }
            }
            if (obj->mtncnt != 0) {
                obj->scale.x = obj->mdlcnt / 100.0f;
            }
            obj->scale.z += obj->scale.x;
            if (obj->scale.z >= 1.0f) {
                if (obj->work[3] != 0 && obj->scale.x <= 0.08f) {
                    obj->work[3]--;
                }
                obj->scale.z -= 1.0f;
                if (obj->scale.y == 0) {
                    obj->work[1] = (obj->work[1] + 1) % 5;
                } else {
                    obj->work[1]--;
                    if (obj->work[1] >= 128) {
                        obj->work[1] = 4;
                    }
                }
                koopa_CursorFXPlay();
            }
            for (i = 0; i < 5; i++) {
                window = koopa_rouletteWinTbl[i];
                if (i == obj->work[1]) {
                    HuWinBGColSet(window[0], 0, 200, 0);
                    HuWinBGTPLvlSet(window[0], 256);
                    HuWinPriSet(window[0], 9000);
                } else {
                    HuWinBGColSet(window[0], 64, 64, 128);
                    HuWinBGTPLvlSet(window[0], 0);
                    HuWinPriSet(window[0], 10000);
                }
            }
            if (obj->trans.z != 0 && (obj->work[1] == obj->work[2] || obj->scale.x < 1.0f)) {
                if (obj->mtncnt == 0) {
                    obj->scale.x -= 0.01f;
                }
            }
            if (obj->scale.x <= 0.08f || obj->mtncnt != 0) {
                if (obj->mtncnt == 0) {
                    obj->scale.x = 0.08f;
                }
                if (obj->work[1] == obj->work[2] && obj->work[3] == 0 && obj->scale.z + obj->scale.x >= 1.0f) {
                    if ((obj->rot.y > 0 ? obj->rot.y : 0.0f - obj->rot.y) <= 0.5f) {
                        HuAudFXPlay(0x105);
                        switch (koopa_rouletteEventTbl[obj->work[2]]) {
                            case 0:
                            case 2:
                            case 3:
                            case 8:
                            case 9:
                                MBPlayerVibrate(koopa_playerNo, 2);
                                break;
                            case 1:
                                MBPlayerVibrate(0, 2);
                                MBPlayerVibrate(1, 2);
                                MBPlayerVibrate(2, 2);
                                MBPlayerVibrate(3, 2);
                                break;
                            case 4:
                            case 5:
                                MBPlayerVibrate(0, 3);
                                MBPlayerVibrate(1, 3);
                                MBPlayerVibrate(2, 3);
                                MBPlayerVibrate(3, 3);
                                break;
                            case 6:
                                MBPlayerVibrate(0, 4);
                                MBPlayerVibrate(1, 4);
                                MBPlayerVibrate(2, 4);
                                MBPlayerVibrate(3, 4);
                                break;
                            case 7:
                                MBPlayerVibrate(0, 5);
                                MBPlayerVibrate(1, 5);
                                MBPlayerVibrate(2, 5);
                                MBPlayerVibrate(3, 5);
                                break;
                        }
                        obj->work[0] = 2;
                        obj->work[3] = 60;
                        HuWinHomeClear(koopa_rouletteWinTbl[obj->work[1]][0]);
                        if (koopa_rouletteEventTbl[obj->work[1]] == 0) {
                            HuWinInsertMesSet(koopa_rouletteWinTbl[obj->work[1]][0], (u32)koopa_coinStr, 0);
                            HuWinInsertMesSizeGet((u32)koopa_coinStr, 0);
                        }
                        HuWinMesSet(koopa_rouletteWinTbl[obj->work[1]][0], koopa_rouletteMesTbl[koopa_rouletteEventTbl[obj->work[1]]], HUWIN_POS_CENTER, 4);
                        HuWinMesColSet(koopa_rouletteWinTbl[obj->work[1]][0], 1);
                        HuWinMesDefColSet(koopa_rouletteWinTbl[obj->work[1]][0], 160, 160, 160);
                        HuWinBGColSet(koopa_rouletteWinTbl[obj->work[1]][0], 254, 255, 208);
                        HuWinMesSpeedSet(koopa_rouletteWinTbl[obj->work[1]][0], 0);
                    } else {
                        obj->mtncnt = 1;
                        if (obj->rot.y >= 0.5f) {
                            obj->rot.y -= 1.0f;
                            obj->work[2] = (obj->work[2] + 1) % 5;
                        } else {
                            obj->rot.y += 1.0f;
                            obj->scale.y = 1.0f;
                            obj->work[2]--;
                            if (obj->work[2] >= 128) {
                                obj->work[2] = 4;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            if (obj->work[3] == 0) {
                obj->work[0] = 4;
                koopa_CursorKill();
            } else {
                obj->work[3]--;
                obj->rot.z += 1.0f;
                if (obj->rot.z >= 13.0f) {
                    obj->rot.z -= 13.0f;
                }
            }
            break;
        case 3:
            break;
        case 4:
            obj->trans.y -= 32.0f;
            for (i = 0; i < 5; i++) {
                window = koopa_rouletteWinTbl[i];
                HuWinPosSet(window[0], window[1] + window[3] / 2, (window[2] + window[4] / 2) + (s16)obj->trans.y);
            }
            if (koopa_backSprGrp != -1) {
                HuSprPosSet(koopa_backSprGrp, 0, koopa_rouletteWinTbl[0][1] + 100, (s32)obj->trans.y + koopa_rouletteWinTbl[0][2] + 50);
            }
            if (koopa_titleSprGrp != -1) {
                HuSprPosSet(koopa_titleSprGrp, 0, koopa_rouletteWinTbl[0][1] + 100, (s32)obj->trans.y + koopa_rouletteWinTbl[0][2] - 30);
            }
            for (i = 0; i < 2; i++) {
                if (koopa_lampSprGrpTbl[i] != -1) {
                    HuSprPosSet(koopa_lampSprGrpTbl[i], 0, koopa_rouletteWinTbl[0][1] + i * 200, (s32)obj->trans.y + koopa_rouletteWinTbl[0][2] - 40);
                }
            }
            if (obj->trans.y <= 0) {
                koopa_rouletteResult = koopa_rouletteEventTbl[obj->work[2]];
                koopa_RouletteKill();
            }
            break;
    }
    if (koopa_cursorSprGrp != -1) {
        for (i = 0;; i++) {
            if (obj->rot.z < koopa_cursorOfsTbl[i * 2]) {
                break;
            }
        }
        HuSprPosSet(koopa_cursorSprGrp, 0, koopa_cursorOfsTbl[i * 2 + 1] + 50, koopa_cursorPosY + obj->work[1] * 20);
    }
}

s32 koopa_RouletteResultGet(void) {
    return koopa_rouletteResult;
}

s32 koopa_Result2Get(void) {
    return koopa_result2;
}

s32 koopa_RouletteStatGet(void) {
    if (koopa_rouletteObj == NULL) {
        return -1;
    }
    return koopa_rouletteObj->work[0];
}

void koopa_RouletteInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(koopa_rouletteWinTbl); i++) {
        koopa_rouletteWinTbl[i][0] = -1;
    }

    koopa_rouletteObj = NULL;

    for (i = 0; i < ARRAY_COUNT(koopa_lampSprGrpTbl); i++) {
        koopa_lampSprGrpTbl[i] = -1;
    }

    koopa_lampSpr = -1;
    koopa_titleSpr = -1;
    koopa_titleSprGrp = -1;
    koopa_backSpr = -1;
    koopa_backSprGrp = -1;
    koopa_cursorSpr = -1;
    koopa_cursorSprGrp = -1;
    koopa_rouletteResult = -1;
    koopa_helpWin = 0;
}

void koopa_CursorKill(void) {
    if (koopa_cursorSprGrp != -1) {
        HuSprGrpKill(koopa_cursorSprGrp);
        koopa_cursorSprGrp = -1;
    }
    if (koopa_cursorSpr != -1) {
        HuSprAnimKill(koopa_cursorSpr);
        koopa_cursorSpr = -1;
    }
}

void koopa_RouletteKill(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(koopa_rouletteWinTbl); i++) {
        s16 *temp = koopa_rouletteWinTbl[i];
        if (temp[0] != -1) {
            HuWinKill(temp[0]);
            temp[0] = -1;
        }
    }

    if (koopa_helpWin != 0) {
        MBHelpWinKill(koopa_helpWin);
        koopa_helpWin = 0;
    }

    if (koopa_rouletteObj != NULL) {
        omDelObj(koopa_rouletteObj);
        koopa_rouletteObj = NULL;
    }

    if (koopa_backSprGrp != -1) {
        HuSprGrpKill(koopa_backSprGrp);
        koopa_backSprGrp = -1;
    }

    if (koopa_backSpr != -1) {
        HuSprAnimKill(koopa_backSpr);
        koopa_backSpr = -1;
    }

    if (koopa_titleSprGrp != -1) {
        HuSprGrpKill(koopa_titleSprGrp);
        koopa_titleSprGrp = -1;
    }

    if (koopa_titleSpr != -1) {
        HuSprAnimKill(koopa_titleSpr);
        koopa_titleSpr = -1;
    }

    for (i = 0; i < ARRAY_COUNT(koopa_lampSprGrpTbl); i++) {
        if (koopa_lampSprGrpTbl[i] != -1) {
            HuSprGrpKill(koopa_lampSprGrpTbl[i]);
            koopa_lampSprGrpTbl[i] = -1;
        }
    }

    if (koopa_lampSpr != -1) {
        HuSprAnimKill(koopa_lampSpr);
        koopa_lampSpr = -1;
    }

    koopa_CursorKill();
}

void koopa_RouletteSprCreate(void) {
    s32 randVal;
    s32 var_v0_2;
    void *temp_v0;
    s32 i;

    if (koopa_backSprGrp == -1) {
        koopa_backSprGrp = HuSprGrpCreate(1, 5);
        temp_v0 = DataRead(0x1301EB);
        koopa_backSpr = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(koopa_backSprGrp, 0, koopa_backSpr, 0);
        HuSprPriSet(koopa_backSprGrp, 0, 0x4770);
        HuSprAttrSet(koopa_backSprGrp, 0, HUSPR_ATTR_XLU);
        HuSprPosSet(koopa_backSprGrp, 0, koopa_rouletteWinTbl[0][1] + 0x64, koopa_rouletteWinTbl[0][2] + 0x32);
        HuSprColorSet(koopa_backSprGrp, 0, 0, 0, 0);
        koopa_titleSprGrp = HuSprGrpCreate(1, 5);
        temp_v0 = DataRead(0x1301E9);
        koopa_titleSpr = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(koopa_titleSprGrp, 0, koopa_titleSpr, 0);
        HuSprPriSet(koopa_titleSprGrp, 0, 0x4770);
        HuSprAttrSet(koopa_titleSprGrp, 0, HUSPR_ATTR_XLU);
        HuSprPosSet(koopa_titleSprGrp, 0, koopa_rouletteWinTbl[0][1] + 0x64, koopa_rouletteWinTbl[0][2] - 0x1E);
        temp_v0 = DataRead(0x130260);
        koopa_lampSpr = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        randVal = MBRand(5.0f);
        for (i = 0; i < ARRAY_COUNT(koopa_lampSprGrpTbl); i++) {
            koopa_lampSprGrpTbl[i] = HuSprGrpCreate(1, 5);
            HuSprGrpMemberSet(koopa_lampSprGrpTbl[i], 0, koopa_lampSpr, 1);
            HuSprPriSet(koopa_lampSprGrpTbl[i], 0, 0x4770);
            HuSprAttrSet(koopa_lampSprGrpTbl[i], 0, HUSPR_ATTR_XLU);
            HuSprPosSet(koopa_lampSprGrpTbl[i], 0, koopa_rouletteWinTbl[0][1] + (i * 0xC8), (koopa_rouletteWinTbl[0][2] - 0x28));
            if ((randVal == 0) && (koopa_rouletteLeaveF == 0)) {
                var_v0_2 = koopa_rouletteStopOfs;
                if (var_v0_2 == 0) {
                    HuSprColorSet(koopa_lampSprGrpTbl[i], 0, 0, 0, 0xFF);
                } else {
                    if (var_v0_2 < 0) {
                        var_v0_2 = -var_v0_2;
                    }
                    if (var_v0_2 < 2) {
                        HuSprColorSet(koopa_lampSprGrpTbl[i], 0, 0xFF, 0xFF, 0);
                    } else {
                        HuSprColorSet(koopa_lampSprGrpTbl[i], 0, 0xFF, 0, 0);
                    }
                }
            } else {
                HuSprColorSet(koopa_lampSprGrpTbl[i], 0, 0xFF, 0, 0);
            }
        }
    }
}

void koopa_CursorCreate(void) {
    void *temp_v0;

    if (koopa_cursorSprGrp == -1) {
        koopa_cursorSprGrp = HuSprGrpCreate(1, 5);
        temp_v0 = DataRead(0x1301EA);
        koopa_cursorSpr = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(koopa_cursorSprGrp, 0, koopa_cursorSpr, 0);
        HuSprPriSet(koopa_cursorSprGrp, 0, 0x100);
        HuSprAttrSet(koopa_cursorSprGrp, 0, HUSPR_ATTR_XLU);
        HuSprPosSet(koopa_cursorSprGrp, 0, 0x32, koopa_cursorPosY);
    }
}

s32 koopa_ShuffleBlockCheck(void) {
    s32 var_s3;
    GW_PLAYER *temp_s1;
    s32 i, j;

    if (GwSystem.current_board_index == CHILLY_WATERS) {
        for (var_s3 = 0, i = 0; i < MB_MAX_PLAYERS; i++) {
            temp_s1 = MBPlayerGet(i);
            for (j = 0; koopa_shuffleBlockMasuTbl[j] != -1; j++) {
                if (MBMasuLinkMasuIdGet(temp_s1->clink, temp_s1->cidx) == koopa_shuffleBlockMasuTbl[j]) {
                    var_s3++;
                    break;
                }
            }
        }
        if (var_s3 < 2) {
            return 0;
        } else {
            return 1;
        }
    }
    return 0;
}

const char koopa_coinFmtStr[] = "%d";
const char koopa_emptyStr[] = "";

void koopa_RouletteCreate(void) {
    u8 order[5];
    u8 events[5];
    s32 i;
    s32 randVal;
    s16 *window;
    KoopaWinPos *positions = koopa_rouletteWinPosTbl;

    i = MBRand(256.0f);
    if (i < 70) {
        koopa_rouletteStopOfs = 0;
    } else if (i < 115) {
        koopa_rouletteStopOfs = 1;
    } else if (i < 160) {
        koopa_rouletteStopOfs = 2;
    } else if (i < 185) {
        koopa_rouletteStopOfs = 3;
    } else if (i < 200) {
        koopa_rouletteStopOfs = 4;
    } else if (i < 225) {
        koopa_rouletteStopOfs = -1;
    } else if (i < 240) {
        koopa_rouletteStopOfs = -2;
    } else {
        koopa_rouletteStopOfs = -3;
    }
    if (MBRand(70.0f) == 0) {
        koopa_rouletteLeaveF = 1;
    } else {
        koopa_rouletteLeaveF = 0;
    }
    for (i = 0; i < 5; i++) {
        window = koopa_rouletteWinTbl[i];
        window[1] = positions[i].unk_00;
        window[2] = positions[i].unk_02;
        window[3] = positions[i].unk_04;
        window[4] = positions[i].unk_06;
        window[0] = HuWinCreate(window[1] + window[3] / 2, window[2] + window[4] / 2, window[3], window[4], 0, 4);
        HuWinDummy(window[0]);
        HuWinCenterPosSet(window[0], window[3] / 2, window[4] / 2);
        HuWinBGTPLvlSet(window[0], 0);
        switch (i) {
            case 0:
            case 1:
                events[i] = 0;
                break;
            case 2:
                events[i] = MBRand(2.0f) + 8;
                break;
            case 3:
            case 4:
            retry:
                randVal = MBRand(100.0f);
                if (randVal < 20) {
                    if (i == 4 && events[3] == 1) {
                        goto retry;
                    }
                    events[i] = 1;
                } else if (randVal < 60) {
                    if (i == 4 && (events[3] == 2 || events[3] == 3)) {
                        goto retry;
                    }
                    events[i] = MBRand(2.0f) + 2;
                } else if (randVal < 90) {
                    if (i == 4 && (events[3] == 4 || events[3] == 5)) {
                        goto retry;
                    }
                    events[i] = MBRand(2.0f) + 4;
                } else {
                    if (i == 4 && (events[3] == 6 || events[3] == 7)) {
                        goto retry;
                    }
                    events[i] = MBRand(2.0f) + 6;
                    if (events[i] == 6 && koopa_ShuffleBlockCheck()) {
                        goto retry;
                    }
                }
                break;
        }
    }
    MBArrayShuffle(order, 4);
    for (i = 0; i < 5; i++) {
        koopa_rouletteEventTbl[i] = events[order[i]];
    }
    for (i = 0; i < 5; i++) {
        window = koopa_rouletteWinTbl[i];
        if (koopa_rouletteEventTbl[i] == 0) {
            sprintf(koopa_coinStr, koopa_coinFmtStr, koopa_CoinAmountGet(0, koopa_playerNo));
            HuWinInsertMesSet(window[0], (u32)koopa_coinStr, 0);
            HuWinInsertMesSizeGet((u32)koopa_coinStr, 0);
        }
        HuWinMesSet(window[0], koopa_rouletteMesTbl[koopa_rouletteEventTbl[i]], HUWIN_POS_CENTER, 4);
        HuWinMesSpeedSet(window[0], 0);
    }
    koopa_rouletteObj = omAddObj(0x8000, 0, 0, -1, koopa_RouletteObjMain);
    koopa_rouletteObj->work[0] = 3;
    koopa_rouletteObj->trans.y = 0;
    koopa_rouletteObj->rot.z = 0;
    koopa_RouletteSprCreate();
}

void koopa_RouletteStart(void) {
    koopa_rouletteObj->work[0] = 0;
}

s32 koopa_CoinAmountGet(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 playerRank;

    temp_s0 = MBTurnTierGet(CUR_TURN);
    playerRank = MBPlayerRankCalc(arg1);
    return koopa_coinAmountTbl[arg0][temp_s0][playerRank];
}

s32 koopa_CoinGiftGet(s32 playerIndex) {
    s32 temp_s0;
    s32 playerRank;

    temp_s0 = MBTurnTierGet(CUR_TURN);
    playerRank = MBPlayerRankCalc(playerIndex);
    return koopa_coinAmountTbl[2][temp_s0][playerRank];
}

void koopa_StatusShowExec(void) {
    MBStatusVsPlayerBSet(koopa_playerNo);
    MBStatusDispMoveSet(0x18);
    MBStatusVsPlayerBSet(-1);
    HuPrcSleep(20);
}

void koopa_StatusShow(void) {
    MBStatusVsPlayerBSet(koopa_playerNo);
    MBStatusDispMoveSet(0x18);
    MBStatusVsPlayerBSet(-1);
}

s32 koopa_CoinTakeExec(void) {
    s32 temp_v0;

    temp_v0 = koopa_CoinAmountGet(0, koopa_playerNo);
    sprintf(koopa_coinStr, koopa_coinFmtStr, temp_v0);
    if (GwPlayer[koopa_playerNo].coin >= temp_v0) {
        MBWinInsertOpen(0x420D, koopa_coinStr, 0, 0, 0, 0);
    } else {
        MBWinInsertOpen(0x420E, koopa_coinStr, 0, 0, 0, 0);
    }

    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    koopa_StatusShowExec();
    MBMotionShiftSet(koopa_koopaMdl, 2, 0, 5, 0);
    MBMotionEndShiftSet(koopa_koopaMdl, -1, 2);
    HuPrcSleep(14);
    HuAudFXPlay(0x29F);
    MBCoinTakeCreate(koopa_playerNo, -temp_v0);
    MBPlayerVibrate(koopa_playerNo, 3);
    HuPrcSleep(30);
    MBWinOpen(0x420F);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    return 0;
}

s32 koopa_CoinTakeAllExec(void) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0_2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v0_2;
    s32 i;

    temp_v0 = koopa_CoinAmountGet(1, koopa_playerNo);
    sprintf(koopa_coinStr, koopa_coinFmtStr, temp_v0);
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (GwPlayer[i].coin < temp_v0) {
            break;
        }
    }

    if (i == 4) {
        MBWinInsertOpen(0x4210, koopa_coinStr, 0, 0, 0, 0);
    } else {
        MBWinInsertOpen(0x4211, koopa_coinStr, 0, 0, 0, 0);
    }

    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    MBStatusDispMoveSet(0);
    HuPrcSleep(20);
    MBMotionShiftSet(koopa_koopaMdl, 2, 0, 5, 0);
    MBMotionEndShiftSet(koopa_koopaMdl, -1, 2);
    HuPrcSleep(14);
    HuAudFXPlay(0x29F);
    var_a0_2 = -10000;
    var_s1 = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        temp_v1 = GwPlayer[i].coin - temp_v0;
        if (var_a0_2 < temp_v1) {
            var_a0_2 = temp_v1;
            var_s1 = i;
        }
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBCoinTakeCreateSound(i, -temp_v0, i == var_s1);
        MBPlayerVibrate(i, 3);
    }

    HuPrcSleep(30);
    MBWinOpen(0x420F);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    return 0;
}

s32 koopa_SuitGiveExec(void) {
    UnkBoard8 *sprite;
    void *data;
    s32 i;

    MBWinOpen(0x4212);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    if (MBItemFindEmpty(koopa_playerNo) == -1) {
        koopa_StatusShowExec();
        MBWinOpen(0x4213);
        MBWinKeyWait(koopa_playerNo);
        MBWinClose();
        HuAudFXPlay(0x29E);
        MBMotionShiftSet(koopa_koopaMdl, 4, 0, 20, 0);
        MBModelMotionWait(koopa_koopaMdl);
        MBMotionShiftSet(koopa_koopaMdl, 7, 0, 5, 2);
        HuPrcSleep(10);
        return 1;
    }
    sprite = MBSprGrpCreate(1, 0);
    data = DataRead(0x21003A);
    sprite->model[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(sprite->spriteGroup, 0, sprite->model[0], 0);
    HuSprAttrReset(sprite->spriteGroup, 0, 0xFFFF);
    HuSprAttrSet(sprite->spriteGroup, 0, HUSPR_ATTR_XLU);
    HuSprPriSet(sprite->spriteGroup, 0, 0x1000);
    HuSprPosSet(sprite->spriteGroup, 0, 160, -32);
    koopa_StatusShow();
    for (i = 0; i <= 120; i += 4) {
        HuSprPosSet(sprite->spriteGroup, 0, 160, i - 32);
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    for (i = 0; i < 70; i += 5) {
        HuSprPosSet(sprite->spriteGroup, 0, sindf(i) * 90.0f + 160.0f, sindf(i + 90) * 50.0f + 38.0f);
        HuSprTPLvlSet(sprite->spriteGroup, 0, 256 - i * 2);
        HuSprScaleSet(sprite->spriteGroup, 0, 1.0f - i / 140.0f, 1.0f - i / 140.0f);
        HuPrcVSleep();
    }
    MBSprGrpKill(sprite);
    HuAudFXPlay(0x10);
    GwPlayer[koopa_playerNo].itemNo[MBItemFindEmpty(koopa_playerNo)] = ITEM_BOWSER_SUIT;
    MBStatusItemIconSprReinit(koopa_playerNo);
    MBWinOpen(0x420F);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    return 0;
}

s32 koopa_PhoneGiveExec(void) {
    UnkBoard8 *sprite;
    void *data;
    s32 i;

    MBWinOpen(0x4214);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    if (MBItemFindEmpty(koopa_playerNo) == -1) {
        koopa_StatusShowExec();
        MBWinOpen(0x4215);
        MBWinKeyWait(koopa_playerNo);
        MBWinClose();
        HuAudFXPlay(0x29E);
        MBMotionShiftSet(koopa_koopaMdl, 4, 0, 20, 0);
        MBModelMotionWait(koopa_koopaMdl);
        MBMotionShiftSet(koopa_koopaMdl, 7, 0, 5, 2);
        HuPrcSleep(10);
        return 1;
    }
    sprite = MBSprGrpCreate(1, 0);
    data = DataRead(0x210034);
    sprite->model[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(sprite->spriteGroup, 0, sprite->model[0], 0);
    HuSprAttrReset(sprite->spriteGroup, 0, 0xFFFF);
    HuSprAttrSet(sprite->spriteGroup, 0, HUSPR_ATTR_XLU);
    HuSprPriSet(sprite->spriteGroup, 0, 0x1000);
    HuSprPosSet(sprite->spriteGroup, 0, 160, -32);
    koopa_StatusShow();
    for (i = 0; i <= 120; i += 4) {
        HuSprPosSet(sprite->spriteGroup, 0, 160, i - 32);
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    for (i = 0; i < 70; i += 5) {
        HuSprPosSet(sprite->spriteGroup, 0, sindf(i) * 90.0f + 160.0f, sindf(i + 90) * 50.0f + 38.0f);
        HuSprTPLvlSet(sprite->spriteGroup, 0, 256 - i * 2);
        HuSprScaleSet(sprite->spriteGroup, 0, 1.0f - i / 140.0f, 1.0f - i / 140.0f);
        HuPrcVSleep();
    }
    HuSprDispOff(sprite->spriteGroup, 0);
    HuAudFXPlay(0x10);
    GwPlayer[koopa_playerNo].itemNo[MBItemFindEmpty(koopa_playerNo)] = ITEM_BOWSER_PHONE;
    MBStatusItemIconSprReinit(koopa_playerNo);
    if (MBItemFindEmpty(koopa_playerNo) != -1 && MBRand(10.0f) == 0) {
        MBWinOpen(0x4216);
        MBWinKeyWait(koopa_playerNo);
        MBWinClose();
        HuSprDispOn(sprite->spriteGroup, 0);
        HuSprTPLvlSet(sprite->spriteGroup, 0, 256);
        for (i = 0; i <= 10; i++) {
            HuSprPosSet(sprite->spriteGroup, 0, 160, 88);
            HuSprScaleSet(sprite->spriteGroup, 0, i / 10.0f, i / 10.0f);
            HuPrcVSleep();
        }
        HuPrcSleep(15);
        for (i = 0; i < 70; i += 5) {
            HuSprPosSet(sprite->spriteGroup, 0, sindf(i) * 90.0f + 160.0f, sindf(i + 90) * 50.0f + 38.0f);
            HuSprTPLvlSet(sprite->spriteGroup, 0, 256 - i * 2);
            HuSprScaleSet(sprite->spriteGroup, 0, 1.0f - i / 140.0f, 1.0f - i / 140.0f);
            HuPrcVSleep();
        }
        HuSprDispOff(sprite->spriteGroup, 0);
        HuAudFXPlay(0x10);
        GwPlayer[koopa_playerNo].itemNo[MBItemFindEmpty(koopa_playerNo)] = ITEM_BOWSER_PHONE;
        MBStatusItemIconSprReinit(koopa_playerNo);
    }
    MBSprGrpKill(sprite);
    MBWinOpen(0x420F);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    return 0;
}

void koopa_SpellEffExec(s32 modelFile) {
    Object *object;
    f32 angle;
    f32 scale;
    s32 i;

    MBMotionShiftSet(koopa_koopaMdl, 5, 0, 5, 0);
    object = MBModelFileCreate(modelFile, -1, 1.0f, NULL, NULL);
    Hu3DModelAttrSet(object->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
    Hu3DModelLayerSet(object->omObj1->model[0], 0);
    HuVecCopy3F(&object->coords, &koopa_koopaMdl->coords);
    object->coords.y += 200.0f;
    angle = 0.0f;
    scale = 1.0f;
    for (i = 0; scale < 12.0f; scale += 0.25) {
        HuVecCopyXYZ(&object->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[object->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        if (i == 5) {
            HuAudFXPlay(0x12D);
        }
        i++;
        HuPrcVSleep();
    }
    for (i = 0; scale >= 1.0f; scale -= 0.25) {
        HuVecCopyXYZ(&object->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[object->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        if (i == 32) {
            HuAudFXPlay(0x13E);
        }
        i++;
        HuPrcVSleep();
    }
    MBModelKill(object);
    MBModelMotionWait(koopa_koopaMdl);
    MBMotionShiftSet(koopa_koopaMdl, -1, 0, 5, 2);
}

s32 koopa_RevSetExec(void) {
    MBWinOpen(0x4217);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    koopa_SpellEffExec(0xB0036);
    MBWinOpen(0x4218);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    MBWinOpen(0x420F);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    MBPlayerRevAllSet();
    return 0;
}

s32 koopa_RevResetExec(void) {
    MBWinOpen(0x421A);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    koopa_SpellEffExec(0xB0037);
    MBWinOpen(0x421B);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    MBWinOpen(0x420F);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    MBPlayerRevAllReset();
    return 0;
}

s32 koopa_ShuffleExec(void) {
    s32 player1;
    s32 player2;
    s32 other1;
    s32 other2;
    s32 i;

    MBWinOpen(0x421D);
    MBWinKeyWait(koopa_playerNo);
    player1 = 0;
    MBWinClose();
    koopa_SpellEffExec(0xB0038);
    player2 = MBRand(3.0f) + 1;
    MBPlayerMasuSwap(player1, player2);
    other2 = -1;
    other1 = -1;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if ((i != player1) & (i != player2)) {
            if (other1 == -1) {
                other1 = i;
            } else {
                other2 = i;
            }
        }
    }
    MBPlayerMasuSwap(other1, other2);
    MBWinOpen(0x421E);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    MBWinOpen(0x420F);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    return 0;
}

void koopa_RevoCoinProc(void) {
    s32 playSound;
    s32 i;
    s32 average = 0;
    s32 soundPlayer;
    s32 maxGain;
    s32 gain;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        average += GwPlayer[i].coin;
    }
    HuAudFXPlay(0x152);
    average /= MB_MAX_PLAYERS;
    maxGain = 0;
    soundPlayer = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBStatusPulseStart(i);
        gain = average - GwPlayer[i].coin;
        if (maxGain < gain) {
            maxGain = gain;
            soundPlayer = i;
        }
    }
    for (i = 0; i < 60; i++) {
        MBStatusColorSet(0, i % 5);
        MBStatusColorSet(1, i % 5);
        MBStatusColorSet(2, i % 5);
        MBStatusColorSet(3, i % 5);
        HuPrcVSleep();
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        playSound = i == soundPlayer;
        MBCoinTakeCreateSound(i, average - GwPlayer[i].coin, playSound);
    }
    for (i = 0; i < 30; i++) {
        MBStatusColorSet(0, i % 5);
        MBStatusColorSet(1, i % 5);
        MBStatusColorSet(2, i % 5);
        MBStatusColorSet(3, i % 5);
        HuPrcVSleep();
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBStatusColorSet(i, GwPlayer[i].color);
        MBStatusPulseStop(i);
    }
    omDelPrcObj(NULL);
}

s32 koopa_RevoExec(void) {
    s32 total = 0;
    s32 i;
    s32 result;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        total += GwPlayer[i].coin;
    }
    if (total >= MB_MAX_PLAYERS) {
        MBWinOpen(0x421F);
        MBWinKeyWait(koopa_playerNo);
        MBWinClose();
        MBStatusDispMoveSet(0);
        HuPrcSleep(20);
        HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(koopa_RevoCoinProc, 0x300, 0x2000, 0));
        koopa_SpellEffExec(0xB0039);
        HuPrcChildWatch();
        MBWinOpen(0x4221);
        MBWinKeyWait(koopa_playerNo);
        MBWinClose();
        MBWinOpen(0x420F);
        MBWinKeyWait(koopa_playerNo);
        MBWinClose();
        result = 0;
    } else {
        MBWinOpen(0x4220);
        MBWinKeyWait(koopa_playerNo);
        MBWinClose();
        HuAudFXPlay(0x29E);
        MBMotionShiftSet(koopa_koopaMdl, 4, 0, 20, 0);
        MBModelMotionWait(koopa_koopaMdl);
        MBMotionShiftSet(koopa_koopaMdl, 7, 0, 5, 2);
        HuPrcSleep(10);
        result = 1;
    }
    return result;
}

s32 koopa_LeaveExec(void) {
    Vec direction;
    s32 i;
    f32 scale;
    Object *object;

    HuPrcSleep(15);
    MBMotionSet(koopa_koopaMdl, 6, 2);
    Hu3DMotionSpeedSet(koopa_koopaMdl->omObj1->model[0], 2.0f);
    MBVecDirGet(&koopa_koopaMdl->coords, &koopa_leavePos, &direction);
    HuPrcChildLink(HuPrcCurrentGet(), MBVecRotLerpCreate(&koopa_koopaMdl->rot, &direction, &koopa_koopaMdl->rot, 10));
    HuPrcChildWatch();
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&koopa_koopaMdl->coords, &koopa_leavePos, &koopa_koopaMdl->coords, 30));
    for (i = 0; i < 30; i++) {
        object = koopa_koopaMdl;
        scale = 2.0f - i / 15.0f;
        HuVecCopyXYZ(&object->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    MBModelDispOff(koopa_koopaMdl);
    MBWinOpen(0x4222);
    MBWinKeyWait(koopa_playerNo);
    MBWinClose();
    return 1;
}

void koopa_MainProc(void) {
    s32 result = 0;

    Hu3DFogSet(0x3CA, 1000, 0, 0, 0);
    koopa_koopaMdl = MBModelFileCreate(0xA002F, 9, 0.7f, 1.4f, (u32 *)&koopa_koopaMot);
    HuVecCopy3F(&koopa_koopaMdl->coords, &koopa_koopaPos);
    HuVecCopyXYZ(&koopa_koopaMdl->scale, 2.0f, 2.0f, 2.0f);
    if (MBRand(5.0f) == 0) {
        MBMotionSet(koopa_koopaMdl, 7, 2);
        koopa_introAltF = 1;
    } else {
        MBMotionSet(koopa_koopaMdl, 1, 2);
        koopa_introAltF = 0;
    }
    koopa_RouletteInit();
    koopa_RouletteCreate();
    HuAudSeqPlay(0x24);
    WipeCreateIn(WIPE_BOWSER, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    if (koopa_introAltF == 0) {
        HuPrcSleep(20);
        MBMotionShiftSet(koopa_koopaMdl, -1, 0, 10, 2);
    } else {
        HuPrcSleep(20);
        MBMotionSet(koopa_koopaMdl, 4, 4);
        Hu3DMotionTimeSet(koopa_koopaMdl->omObj1->model[0], 1024.0f);
        while (MBMotionStartCheck(koopa_koopaMdl) == 0) {
            HuPrcVSleep();
        }
        MBMotionShiftSet(koopa_koopaMdl, -1, 0, 10, 2);
        HuPrcSleep(10);
        MBMotionShiftSet(koopa_koopaMdl, 1, 0, 5, 2);
        HuPrcSleep(36);
        MBMotionShiftSet(koopa_koopaMdl, -1, 0, 10, 2);
    }
    HuPrcSleep(10);
    HuAudFXPlay(0x29D);
    if (GwPlayer[koopa_playerNo].coin == 0) {
        sprintf(koopa_coinStr, koopa_coinFmtStr, koopa_CoinGiftGet(koopa_playerNo));
        MBWinInsertOpen(0x420B, (char *)mbCharNameMesTbl[GwPlayer[koopa_playerNo].chr], (u32)koopa_coinStr, 0, 0, 0);
        MBWinKeyWait(koopa_playerNo);
        MBWinClose();
        koopa_StatusShowExec();
        MBMotionShiftSet(koopa_koopaMdl, 2, 0, 5, 0);
        MBMotionEndShiftSet(koopa_koopaMdl, -1, 2);
        HuPrcSleep(14);
        MBCoinTakeCreate(koopa_playerNo, koopa_CoinGiftGet(koopa_playerNo));
        HuPrcSleep(30);
        MBWinOpen(0x420C);
        MBWinKeyWait(koopa_playerNo);
        MBWinClose();
    } else {
        MBWinInsertOpen(0x420A, (char *)mbCharNameMesTbl[GwPlayer[koopa_playerNo].chr], 0, 0, 0, 0);
        MBWinKeyWait(koopa_playerNo);
        MBWinClose();
        MBMotionShiftSet(koopa_koopaMdl, 2, 0, 5, 0);
        MBMotionEndShiftSet(koopa_koopaMdl, -1, 2);
        HuPrcSleep(14);
        koopa_RouletteStart();
        while (koopa_rouletteObj != NULL) {
            HuPrcVSleep();
        }
        result = koopa_eventFuncTbl[koopa_rouletteResult]();
    }
    if (result == 0) {
        HuAudFXPlay(0x29C);
        MBMotionShiftSet(koopa_koopaMdl, 3, 0, 5, 2);
    }
    HuPrcSleep(20);
    omSysExitReq = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void koopa_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        koopa_BackClose();
        koopa_SysClose();
        MBStatusKill();
        HuWinAllKill();
        MBMasuKill();
        MBMasuClose();
        omOvlReturnEx(1);
    }
}

void koopa_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq != 0) {
        WipeCreateOut(WIPE_BOWSER, 20);
        HuAudSeqFadeOut(60);
        obj->func = koopa_ExitObjMain;
    }
}

void koopa_SysInit(void) {
    MBModelInit();
    MBPlayerMotInit();
    MBMotShiftInit();
    MBSprGrpInit();
}

void koopa_SysClose(void) {
    MBSprGrpClose();
    MBMotShiftClose();
    MBPlayerClose();
    MBModelClose();
}

void koopa_BackInit(void) {
    Hu3DCamInit(1);
    MBBackArcInit((u32)hvq_data_ROM_START);
    MBBackLoad(2);
    MBCameraNearFarSet(100.0f, 10000.0f);
}

void koopa_BackClose(void) {
    MBBackKill();
    MBBackClose();
}
