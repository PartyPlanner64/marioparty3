#include "common.h"
#include "inst.h"

extern u16 mgBattleCoinPot;
extern omObjData *inst_winObj;
extern s32 inst_titleInCnt;
extern s32 inst_titleY;
extern s16 inst_titleYHalf;
extern u16 inst_titleSprTbl[2];
extern u16 inst_coinPotDigitSprTbl[3];
extern s8 inst_hostNo;
extern s8 inst_mgNo;
extern s8 inst_practiceF;
extern s8 inst_winPage;
extern s32 inst_winMes;
extern const MinigameTable *inst_mgData;
extern s8 inst_playerOrderTbl[4];
extern s8 inst_practiceStartF;
extern s8 inst_introSkipF;
extern s8 inst_startF;
extern s8 inst_mgType;
extern s32 inst_winOpenF;
extern s8 inst_winStartF;
extern void (*inst_winFunc)(s32);
extern UnkInstWin inst_win;
extern GAMEMES inst_titleMes;
extern GAMEMES inst_practiceMes;

const InstSpritePos inst_coinPotDigitPosTbl[3] = {{0, 95}, {0, 105}, {0, 115}};
const s16 inst_practiceMesTbl[2][3] = {
    {0x3900, 0x3901, 0x3902},
    {0x3908, 0x3909, 0x390A},
};
const s16 inst_practiceVsMesTbl[2][3] = {
    {0x3910, 0x3912, 0x3914},
    {0x390C, 0x390D, 0x390E},
};
const s16 inst_practiceAltMesTbl[] = {0x3904, 0x3905, 0x3906, 0x0000};
const s16 inst_practiceSpecialMesTbl[2][3] = {
    {0x3803, 0x3804, 0x3805},
    {0x380A, 0x380B, 0x380C},
};
const s16 inst_practiceOmakeMesTbl[] = {0x3811, 0x3812, 0x3813, 0x0000};


void inst_TitleCreate(const char *, s32, s32);
void inst_PracticeLabelCreate(void);
void inst_PracticeLabelDispOff(void);
void inst_WinPlayerSet(void);
void inst_WinDestroy(void);
void inst_WinStartWait(void);

void inst_WinPageMain(s32);
void inst_WinPracticeMain(s32 arg0);
void inst_WinPageIconSet(s32);
void inst_PracticeOn(void);
u16 inst_PadBtnDownGet(s32);
void inst_PracticeOff(void);
void inst_TitlePosSet(s32, s32);
void inst_WinTitleIn(s32 arg0); /* extern */

void inst_WinMain(void) {
    s32 digits[3];
    s32 i;
    s32 score;
    s32 sprite;
    s16 slot;
    omObjData *object;
    const InstSpritePos *positions;
    u16 *sprites;

    object = omAddObj(20, 5, 0, -1, NULL);
    inst_winObj = object;
    inst_mgData = &mgDataTbl[inst_mgNo];
    inst_titleSprTbl[0] = espEntry(HuSprAnimDataRead(0x170008), 0, 1);
    espAttrSet(inst_titleSprTbl[0], 0x1000);
    espTPLvlSet(inst_titleSprTbl[0], 255);
    espPosSet(inst_titleSprTbl[0], 160, -100);
    inst_TitleCreate((const char *)(inst_mgNo + 0x4700), 160, -100);
    inst_PracticeLabelCreate();
    inst_PracticeLabelDispOff();
    if (inst_mgType == 3) {
        inst_titleSprTbl[1] = espEntry(HuSprAnimDataRead(0x17000E), 0, 1);
        espAttrSet(inst_titleSprTbl[1], 0x1000);
        espTPLvlSet(inst_titleSprTbl[1], 255);
        espPosSet(inst_titleSprTbl[1], 160, -78);
        score = mgBattleCoinPot;
        sprite = HuSprAnimDataRead(0x1300CF);
        if (score >= 1000) {
            score = 999;
        } else if (score < 0) {
            score = 0;
        }
        digits[0] = score / 100 % 10;
        digits[1] = score / 10 - score / 100 * 10;
        digits[2] = score % 10;
        for (i = 0; i < 3; i++) {
            slot = espEntry(sprite, 0, 0);
            sprites = inst_coinPotDigitSprTbl;
            sprites[i] = slot;
            positions = inst_coinPotDigitPosTbl;
            espPosSet(sprites[i], positions[i].x, -78);
            espBankSet(sprites[i], (u16)digits[i], 0);
        }
    }
    inst_win.curGroup = HuWinExCreateStyled(72, 188, 7);
    HuWinMesPalSet(inst_win.curGroup, 2, 0, 255, 255);
    HuWinMesPalSet(inst_win.curGroup, 4, 96, 255, 64);
    HuWinMesPalSet(inst_win.curGroup, 6, 255, 255, 64);
    HuWinGet(inst_win.curGroup)->spacing_x = 1;
    inst_WinPlayerSet();
    inst_win.mainMembers[0] = HuWinAnimSet(inst_win.curGroup, 0x17000B, 60, -33, 0);
    inst_win.mainMembers[1] = HuWinAnimSet(inst_win.curGroup, 0x170009, 148, -33, 0);
    inst_win.mainMembers[2] = HuWinAnimSet(inst_win.curGroup, 0x17000A, 200, -33, 0);
    inst_win.helpMembers[0] = HuWinAnimSet(inst_win.curGroup, 0x17000D, 60, -33, 0);
    inst_win.helpMembers[1] = HuWinAnimSet(inst_win.curGroup, 0x17000F, 200, -33, 0);
    inst_win.member = HuWinAnimSet(inst_win.curGroup, 0x17000C, 38, -33, 0);
    inst_winPage = 0;
    inst_winMes = inst_mgData->message;
    if (inst_mgType == 4 && inst_hostNo != 2) {
        inst_winMes++;
    }
    HuWinMesSet(inst_win.curGroup, inst_winMes, -1, -1);
    omPrcSetDestructor(NULL, inst_WinDestroy);
    inst_winFunc = (void (*)(s32))inst_WinStartWait;
    while (1) {
        inst_winFunc((s32)object);
        HuPrcVSleep();
    }
}

void inst_WinStartWait(void) {
    if (inst_introSkipF == 1) {
        inst_winStartF = 1;
    }
    if (inst_winStartF == 1) {
        inst_winFunc = inst_WinTitleIn;
    }
}

void inst_WinIdle(s32 arg0) {
}

void inst_WinTitleIn(s32 arg0) {
    s32 i;
    s32 value;
    s16 *y;
    u16 *sprites;
    const InstSpritePos *positions;

    if (inst_introSkipF == 0) {
        espPosSet(inst_titleSprTbl[0], 160, *(y = &inst_titleYHalf));
        inst_TitlePosSet(160, *y);
        value = inst_mgType;
        if (value == 3) {
            espPosSet(inst_titleSprTbl[1], 160, *y + 22);
            for (i = 0, sprites = inst_coinPotDigitSprTbl, positions = inst_coinPotDigitPosTbl; i < 3; i++) {
                espPosSet(sprites[i], positions[i].x, inst_titleYHalf + 22);
            }
        }
        inst_titleInCnt++;
        inst_titleY = sindf(inst_titleInCnt * 6) * 96.0f + -64.0f;
        if (inst_titleInCnt < 15) {
            return;
        }
        inst_titleInCnt = 0;
        inst_titleY = -64;
        espPosSet(inst_titleSprTbl[0], 160, 32);
        inst_TitlePosSet(160, 32);
        value = inst_mgType;
        if (value == 3) {
            espPosSet(inst_titleSprTbl[1], 160, 54);
            for (i = 0, sprites = inst_coinPotDigitSprTbl, positions = inst_coinPotDigitPosTbl; i < 3; i++) {
                espPosSet(sprites[i], positions[i].x, 54);
            }
        }
    } else {
        espPosSet(inst_titleSprTbl[0], 160, 32);
        inst_TitlePosSet(160, 32);
        value = inst_mgType;
        if (value == 3) {
            espPosSet(inst_titleSprTbl[1], 160, 54);
            for (i = 0, sprites = inst_coinPotDigitSprTbl, positions = inst_coinPotDigitPosTbl; i < 3; i++) {
                espPosSet(sprites[i], positions[i].x, 54);
            }
        }
        HuWinExOpenNow(inst_win.curGroup);
        value = 1;
        inst_winOpenF = value;
    }
    inst_PracticeOff();
    inst_winFunc = inst_WinPageMain;
}

void inst_WinPageMain(s32 arg0) {
    if (inst_startF == 1) {
        return;
    }
    if (inst_PadBtnDownGet(0x10) != 0) {
        inst_PracticeOn();
        inst_winFunc = inst_WinPracticeMain;
        return;
    }
    switch (inst_winPage) {
        case 0:
            if (inst_PadBtnDownGet(1) != 0) {
                inst_winMes = inst_mgData->unk_0A[0];
                if (inst_mgData->unk_0A[1] < 0) {
                    inst_WinPageIconSet(1);
                    inst_winPage = 1;
                } else {
                    inst_WinPageIconSet(3);
                    inst_winPage = 3;
                }
                HuWinMesSet(inst_win.curGroup, inst_winMes, -1, -1);
            }
            break;
        case 1:
            if (inst_PadBtnDownGet(1) != 0) {
                inst_winMes = inst_mgData->finalMessage;
                if (inst_mgType == 4 && inst_hostNo != 2) {
                    inst_winMes++;
                }
                HuWinMesSet(inst_win.curGroup, inst_winMes, -1, -1);
                inst_WinPageIconSet(2);
                inst_winPage = 2;
            }
            break;
        case 3:
            if (inst_PadBtnDownGet(1) != 0) {
                if (inst_mgData->unk_0A[1] < 0) {
                    inst_winMes = inst_mgData->finalMessage;
                    if (inst_mgType == 4 && inst_hostNo != 2) {
                        inst_winMes++;
                    }
                    inst_WinPageIconSet(2);
                    inst_winPage = 2;
                } else {
                    inst_winMes = inst_mgData->unk_0A[1];
                    inst_WinPageIconSet(4);
                    inst_winPage = 4;
                }
                HuWinMesSet(inst_win.curGroup, inst_winMes, -1, -1);
            }
            break;
        case 4:
            if (inst_PadBtnDownGet(1) != 0) {
                if (inst_mgData->unk_0A[2] < 0) {
                    inst_winMes = inst_mgData->finalMessage;
                    if (inst_mgType == 4 && inst_hostNo != 2) {
                        inst_winMes++;
                    }
                    inst_WinPageIconSet(2);
                    inst_winPage = 2;
                } else {
                    inst_winMes = inst_mgData->unk_0A[2];
                    inst_WinPageIconSet(6);
                    inst_winPage = 6;
                }
                HuWinMesSet(inst_win.curGroup, inst_winMes, -1, -1);
            }
            break;
        case 6:
            if (inst_PadBtnDownGet(1) != 0) {
                if (inst_mgData->unk_0A[3] < 0) {
                    inst_winMes = inst_mgData->finalMessage;
                    if (inst_mgType == 4 && inst_hostNo != 2) {
                        inst_winMes++;
                    }
                    inst_WinPageIconSet(2);
                    inst_winPage = 2;
                } else {
                    inst_winMes = inst_mgData->unk_0A[3];
                    inst_WinPageIconSet(7);
                    inst_winPage = 7;
                }
                HuWinMesSet(inst_win.curGroup, inst_winMes, -1, -1);
            }
            break;
        case 7:
            if (inst_PadBtnDownGet(1) != 0) {
                inst_winMes = inst_mgData->finalMessage;
                inst_WinPageIconSet(2);
                inst_winPage = 2;
                if (inst_mgType == 4 && inst_hostNo != 2) {
                    inst_winMes++;
                }
                HuWinMesSet(inst_win.curGroup, inst_winMes, -1, -1);
            }
            break;
        case 2:
            if (inst_PadBtnDownGet(1) != 0) {
                inst_winMes = inst_mgData->message;
                if (inst_mgType == 4 && inst_hostNo != 2) {
                    inst_winMes++;
                }
                HuWinMesSet(inst_win.curGroup, inst_winMes, -1, -1);
                inst_WinPageIconSet(0);
                inst_winPage = 0;
            }
            break;
    }
}

s32 inst_PracticeCancelCheck(void) {
    s32 changed = 0;

    if ((inst_PadBtnDownGet(0x10) != 0) && (inst_startF != 1)) {
        changed = 1;
        inst_PracticeOff();
        inst_winFunc = inst_WinPageMain;
    }
    HuPrcVSleep();
    return changed;
}

void inst_WinPracticeMain(s32 arg0) {
    s8 i;
    s32 message;

    if (inst_startF != 1) {
        for (i = 0; i < 3; i++) {
            switch (inst_mgNo) {
                case 8:
                case 16:
                case 27:
                    message = inst_practiceAltMesTbl[i];
                    break;
                default:
                    switch (inst_mgType) {
                        case 5:
                            message = inst_practiceMesTbl[1][i];
                            break;
                        case 4:
                            message = inst_practiceVsMesTbl[0][i];
                            message += inst_hostNo != 2;
                            break;
                        case 3:
                            message = inst_practiceVsMesTbl[1][i];
                            break;
                        case 7:
                            if (inst_mgNo == 70) {
                                message = inst_practiceSpecialMesTbl[1][i];
                            } else {
                                message = inst_practiceOmakeMesTbl[i];
                            }
                            break;
                        case 8:
                            message = inst_practiceSpecialMesTbl[0][i];
                            break;
                        case 0:
                        case 1:
                        case 2:
                        case 6:
                        default:
                            message = inst_practiceMesTbl[0][i];
                            break;
                    }
                    break;
            }
            HuWinMesSet(inst_win.curGroup, message, -1, -1);
            while (HuWinStatGet(inst_win.curGroup) != 0) {
                if (inst_PracticeCancelCheck() != 0) {
                    return;
                }
            }
        }
        message = inst_mgData->finalMessage;
        if (inst_mgType == 4) {
            message += inst_hostNo != 2;
        }
        HuWinMesSet(inst_win.curGroup, message, -1, -1);
        while (HuWinStatGet(inst_win.curGroup) != 0) {
            if (inst_PracticeCancelCheck() != 0) {
                return;
            }
        }
        while (inst_PadBtnDownGet(0x8000) == 0) {
            if (inst_PracticeCancelCheck() != 0) {
                return;
            }
        }
        inst_practiceStartF = 1;
        inst_winFunc = inst_WinIdle;
    }
}

void inst_WinOpen(void) {
    if (inst_introSkipF == 0) {
        HuAudFXPlay(0x11D);
        HuWinExOpen(inst_win.curGroup, 0);
        inst_winOpenF = 1;
    }
}

void inst_WinClose(void) {
    HuWinExClose(inst_win.curGroup, 1);
}

void inst_WinDestroy(void) {
    GMesClose();
}

void inst_WinStart(void) {
    inst_winStartF = 1;
}

u16 inst_PadBtnDownGet(s32 buttons) {
    u16 pressed = 0;
    s8 i;

    switch (inst_mgType) {
        case 5:
        case 6:
        case 7:
        case 8:
            if (!(GwPlayer[inst_playerOrderTbl[0]].stat & 1)) {
                pressed = HuPadBtnDown[GwPlayer[inst_playerOrderTbl[0]].pad] & buttons;
            }
            break;
        case 4:
            for (i = 0; i < 2; i++) {
                if (!(GwPlayer[inst_playerOrderTbl[i]].stat & 1)) {
                    pressed = HuPadBtnDown[GwPlayer[inst_playerOrderTbl[i]].pad] & buttons;
                    if (pressed != 0) {
                        break;
                    }
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
                    pressed = HuPadBtnDown[GwPlayer[inst_playerOrderTbl[i]].pad] & buttons;
                    if (pressed != 0) {
                        break;
                    }
                }
            }
            break;
    }
    return pressed;
}

u16 inst_PadBtnDownAutoGet(u16 buttons, s16 wait) {
    s32 cpu = 0;
    u16 pressed = 0;
    s8 i;

    switch (inst_mgType) {
        case 5:
        case 6:
        case 7:
        case 8:
            cpu = GwPlayer[inst_playerOrderTbl[0]].stat & 1;
            break;
        case 4:
            if ((GwPlayer[inst_playerOrderTbl[0]].stat & 1) && (GwPlayer[inst_playerOrderTbl[1]].stat & 1)) {
                cpu = 1;
            }
            break;
    }
    for (i = 0; i < 4; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }
    if ((i < 4) & (cpu != 1)) {
        pressed = inst_PadBtnDownGet(buttons);
    } else if (wait == 0) {
        pressed = 1;
    }
    return pressed;
}

void inst_WinPageIconSet(s32 arg0) {
    TextWindow *window = &winData[inst_win.curGroup];
    s16 member = inst_win.member;

    HuSprGrpMemberSet(window->group, member, window->sprite_id[member], arg0 & 0xFF);
}

void inst_WinPlayerSet(void) {
    s8 i;
    s32 pads;

    for (i = 0; i < 4; i++) {
        HuWinInsertMesSet(inst_win.curGroup, GwPlayer[inst_playerOrderTbl[i]].chr + 0x1C00, i);
    }
    pads = 0;
    switch (inst_mgType) {
        case 5:
        case 6:
        case 7:
        case 8:
            pads |= 1 << GwPlayer[inst_playerOrderTbl[0]].pad;
            break;
        case 4:
            for (i = 0; i < 2; i++) {
                if (!(GwPlayer[inst_playerOrderTbl[i]].stat & 1)) {
                    pads |= 1 << GwPlayer[inst_playerOrderTbl[i]].pad;
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
                    pads |= 1 << GwPlayer[inst_playerOrderTbl[i]].pad;
                }
            }
            break;
    }
    HuWinActivePlayerSet(inst_win.curGroup, pads);
}

void inst_TitleCreate(const char *message, s32 x, s32 y) {
    char *text = MessDataMesGet((char *)message);

    inst_titleMes.subMode = -1;
    inst_titleMes.subMode = GameMesStrCreate(&inst_titleMes, text + 1, 0, -1, -1);
    inst_titleMes.pos.x = (s16)x;
    inst_titleMes.pos.y = (s16)y;
    HuSprPosSet(inst_titleMes.strGId[inst_titleMes.subMode], 0, inst_titleMes.pos.x,
                       inst_titleMes.pos.y);
    MessDataMesFree(text);
}

void inst_TitlePosSet(s32 x, s32 y) {
    HuSprPosSet(inst_titleMes.strGId[inst_titleMes.subMode], 0, x, y);
}

void inst_PracticeLabelCreate(void) {
    inst_practiceMes.subMode = GameMesStrCreate(&inst_practiceMes, "PRACTICE", 0, -1, -1);
    inst_practiceMes.pos.x = 216.0f;
    inst_practiceMes.pos.y = 90.0f;
    HuSprPosSet(inst_practiceMes.strGId[inst_practiceMes.subMode], 0, 216, 90);
}

void inst_PracticeLabelDispOn(void) {
    inst_practiceMes.pos.x = 216.0f;
    inst_practiceMes.pos.y = 90.0f;
    HuSprPosSet(inst_practiceMes.strGId[inst_practiceMes.subMode], 0, 0xD8, 0x5A);
}

void inst_PracticeLabelDispOff(void) {
    inst_practiceMes.pos.x = 512.0f;
    inst_practiceMes.pos.y = 512.0f;
    HuSprPosSet(inst_practiceMes.strGId[inst_practiceMes.subMode], 0, 0x200, 0x200);
}

void inst_PracticeOff(void) {
    TextWindow *window = &winData[inst_win.curGroup];
    s8 i;

    if (inst_startF != 1) {
        inst_PracticeLabelDispOff();
        HuSprDispOn(window->group, inst_win.member);
        for (i = 0; i < 3; i++) {
            if (i != 1) {
                HuSprDispOn(window->group, inst_win.mainMembers[i]);
            }
        }
        for (i = 0; i < 2; i++) {
            HuSprDispOff(window->group, inst_win.helpMembers[i]);
        }
        inst_winMes = inst_mgData->message;
        if ((inst_mgType == 4) && (inst_hostNo != 2)) {
            inst_winMes++;
        }
        HuWinMesSet(inst_win.curGroup, inst_winMes, -1, -1);
        inst_WinPageIconSet(0);
        inst_winPage = 0;
        inst_practiceF = 0;
    }
}

void inst_PracticeOn(void) {
    TextWindow *window = &winData[inst_win.curGroup];
    s8 i;
    s32 message;

    if (inst_startF != 1) {
        inst_PracticeLabelDispOn();
        for (i = 0; i < 2; i++) {
            HuSprDispOn(window->group, inst_win.helpMembers[i]);
        }
        HuSprDispOff(window->group, inst_win.member);
        for (i = 0; i < 3; i++) {
            if (i != 1) {
                HuSprDispOff(window->group, inst_win.mainMembers[i]);
            }
        }
        switch (inst_mgNo) {
            case 8:
            case 16:
            case 27:
                message = inst_practiceAltMesTbl[0];
                break;
            default:
                switch (inst_mgType) {
                    case 5:
                        message = inst_practiceMesTbl[1][0];
                        break;
                    case 4:
                        message = inst_practiceVsMesTbl[0][0];
                        message += inst_hostNo != 2;
                        break;
                    case 3:
                        message = inst_practiceVsMesTbl[1][0];
                        break;
                    case 7:
                        if (inst_mgNo == 70) {
                            message = inst_practiceSpecialMesTbl[1][0];
                        } else {
                            message = inst_practiceOmakeMesTbl[0];
                        }
                        break;
                    case 8:
                        message = inst_practiceSpecialMesTbl[0][0];
                        break;
                    case 0:
                    case 1:
                    case 2:
                    case 6:
                    default:
                        message = inst_practiceMesTbl[0][0];
                        break;
                }
                break;
        }
        HuWinMesSet(inst_win.curGroup, message, -1, -1);
        inst_practiceF = 1;
    }
}
