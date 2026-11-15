#include "common.h"
#include "overlays/minigame.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/sprite.h"
#include "math.h"

u16 D_800EB910_minigame = 0;
u16 D_800EB912_minigame = 0;
u16 D_800EB914_minigame = 0;
u16 D_800EB916_minigame = 0;
u16 D_800EB918_minigame = 0;
u16 D_800EB91A_minigame = 0;
s32 D_800EB91C_minigame = 0x90;
s32 D_800EB920_minigame = 0xD0;
s32 D_800EB924_minigame = 1;
s16 D_800EB928_minigame = 0; /* Unreferenced. */
s16 D_800EB92A_minigame = -1;
s32 D_800EB92C_minigame = -1;
s16 D_800EB930_minigame = -1;
s16 D_800EB932_minigame = 75;
s16 D_800EB934_minigame = 0;
f32 D_800EB938_minigame = 0.0f;
s32 D_800EB93C_minigame = 0;
s32 D_800EB940_minigame = 0;

extern s32 omovl;
extern u8 D_800CE20A_main;
extern s16 D_800EBDE4_minigame;
extern s16 D_800EBDE6_minigame;
extern s16 D_800EBDE8_minigame[];

void func_800E5EA0_minigame(MinigameFlow *flow) {
    flow->state = MG_STATE_OPENING;
    D_800EBDE0_minigame = flow;
    if (flow->timeDisp == MG_TIME_DISP_RECORD) {
        func_800E62A8_minigame();
        func_800E6268_minigame();
        func_800E64B8_minigame(D_800EB91C_minigame, D_800EB920_minigame);
        func_800E6300_minigame(D_800EB91C_minigame, D_800EB920_minigame + 12);
        switch ((u32)omovl) {
            case 0x10:
                D_800EB92C_minigame = 1;
                D_800EB92A_minigame = GWMgRecordGet(D_800EB92C_minigame);
                break;
            case 0x23:
                D_800EB92C_minigame = 2;
                D_800EB92A_minigame = GWMgRecordGet(D_800EB92C_minigame);
                break;
            case 0x46:
                D_800EB92C_minigame = D_800CE20A_main + 5;
                D_800EB92A_minigame = GWMgRecordGet(D_800EB92C_minigame);
                break;
        }
        func_800E6670_minigame(1, D_800EB92A_minigame);
        func_800E6670_minigame(0, 0);
    }

    switch (D_800EBDE0_minigame->gauge & MG_GAUGE_LAYOUT_MASK) {
        case MG_GAUGE_CORNERS_4:
            func_800E9C20_minigame(4, D_800EBDE0_minigame->gauge & MG_GAUGE_LENGTH_MASK);
            func_800EA0FC_minigame(0, 0.0f, 100.0f);
            func_800E9F40_minigame(0, 24, 16, 0);
            func_800EA2A8_minigame(0);
            func_800EA0FC_minigame(1, 0.0f, 100.0f);
            func_800E9F40_minigame(1, 296 - (D_800EBDE0_minigame->gauge & MG_GAUGE_LENGTH_MASK) * 10, 16, 0);
            func_800EA2A8_minigame(1);
            func_800EA0FC_minigame(2, 0.0f, 100.0f);
            func_800E9F40_minigame(2, 24, 200, 0);
            func_800EA2A8_minigame(2);
            func_800EA0FC_minigame(3, 0.0f, 100.0f);
            func_800E9F40_minigame(3, 296 - (D_800EBDE0_minigame->gauge & MG_GAUGE_LENGTH_MASK) * 10, 200, 0);
            func_800EA2A8_minigame(3);
            break;
        case MG_GAUGE_TOP_2:
            func_800E9C20_minigame(2, D_800EBDE0_minigame->gauge & MG_GAUGE_LENGTH_MASK);
            func_800EA0FC_minigame(0, 0.0f, 100.0f);
            func_800E9F40_minigame(0, 24, 16, 0);
            func_800EA2A8_minigame(0);
            func_800EA0FC_minigame(1, 0.0f, 100.0f);
            func_800E9F40_minigame(1, 296 - (D_800EBDE0_minigame->gauge & MG_GAUGE_LENGTH_MASK) * 10, 16, 0);
            func_800EA2A8_minigame(1);
            break;
        case MG_GAUGE_RIGHT_2:
            func_800E9C20_minigame(2, D_800EBDE0_minigame->gauge & MG_GAUGE_LENGTH_MASK);
            func_800EA0FC_minigame(0, 0.0f, 100.0f);
            func_800E9F40_minigame(0, 296 - (D_800EBDE0_minigame->gauge & MG_GAUGE_LENGTH_MASK) * 10, 16, 0);
            func_800EA2A8_minigame(0);
            func_800EA0FC_minigame(1, 0.0f, 100.0f);
            func_800E9F40_minigame(1, 296 - (D_800EBDE0_minigame->gauge & MG_GAUGE_LENGTH_MASK) * 10, 130, 0);
            func_800EA2A8_minigame(1);
            break;
    }

    D_800EB910_minigame = 0;
    D_800EB912_minigame = 0;
    D_800EB914_minigame = 0;
    D_800EB916_minigame = 0;
    D_800EB918_minigame = 0;
    D_800EB91A_minigame = 0;
    D_800EB934_minigame = 0;
}

void func_800E6248_minigame(s32 arg0, s32 arg1) {
    D_800EB91C_minigame = arg0;
    D_800EB920_minigame = arg1;
}

void func_800E625C_minigame(s32 arg0) {
    D_800EB924_minigame = arg0;
}

void func_800E6268_minigame(void) {
    void *data;

    data = DataRead(0x31);
    D_800EBDE4_minigame = HuSprAnimRead(data);
    DataClose(data);
}

void func_800E62A8_minigame(void) {
    void *data;

    data = DataRead(0x31);
    D_800EBDE6_minigame = HuSprAnimRead(data);
    DataClose(data);
    func_8000B880_main(D_800EBDE6_minigame, 0.0f, 1.0f, 0.0f);
}

s16 func_800E6300_minigame(s32 x, s32 y) {
    s16 group;
    s16 member;
    s16 memberX;

    group = D_800EBDE8_minigame[0] = HuSprGrpCreate(7, 5);
    HuSprGrpMemberSet(group, 0, D_800EBDE4_minigame, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprDispOff(group, 0);
    HuSprPosSet(group, 0, x - 16, y);
    HuSprPriSet(group, 0, (u16)D_800EB924_minigame);

    memberX = 4;
    for (member = 1; member < 7; member++) {
        HuSprPriSet(group, member, (u16)D_800EB924_minigame);
        HuSprGrpMemberSet(group, member, D_800EBDE4_minigame, 0);
        HuSprPosSet(group, member, memberX, 0);
        HuSprAttrReset(group, member, 0xFFFF);
        HuSprDispOff(group, member);
        if (member == 3) {
            memberX += 8;
        } else {
            memberX += 12;
        }
        func_800554C4_main(group, member, 0);
    }

    HuSprDispOn(group, 2);
    return group;
}

s16 func_800E64B8_minigame(s32 x, s32 y) {
    s16 group;
    s16 member;
    s16 memberX;

    group = D_800EBDE8_minigame[1] = HuSprGrpCreate(7, 5);
    HuSprGrpMemberSet(group, 0, D_800EBDE6_minigame, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprDispOff(group, 0);
    HuSprPosSet(group, 0, x - 16, y);
    HuSprPriSet(group, 0, (u16)D_800EB924_minigame);

    memberX = 4;
    for (member = 1; member < 7; member++) {
        HuSprPriSet(group, member, (u16)D_800EB924_minigame);
        HuSprGrpMemberSet(group, member, D_800EBDE6_minigame, 0);
        HuSprPosSet(group, member, memberX, 0);
        HuSprAttrReset(group, member, 0xFFFF);
        HuSprDispOff(group, member);
        if (member == 3) {
            memberX += 8;
        } else {
            memberX += 12;
        }
        func_800554C4_main(group, member, 0);
    }

    HuSprDispOn(group, 2);
    return group;
}

void func_800E6670_minigame(s16 index, s16 time) {
    s16 group = D_800EBDE8_minigame[index];
    s16 digit;
    s16 seconds;

    HuSprDispOn(group, 0);
    digit = time / 3600;
    HuSprBankSet(group, 0, digit, 0);
    HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_BANK);
    time -= digit * 3600;

    HuSprDispOn(group, 1);
    HuSprBankSet(group, 1, 10, 0);
    HuSprAnimModeSet(group, 1, HUSPR_ANIM_MODE_BANK);

    HuSprDispOn(group, 2);
    digit = time / 600;
    HuSprBankSet(group, 2, digit, 0);
    HuSprAnimModeSet(group, 2, HUSPR_ANIM_MODE_BANK);
    time -= digit * 600;

    seconds = time / 60;
    digit = seconds;
    HuSprDispOn(group, 3);
    HuSprBankSet(group, 3, seconds, 0);
    HuSprAnimModeSet(group, 3, HUSPR_ANIM_MODE_BANK);
    time = time * 100 / 60 - digit * 100;

    HuSprDispOn(group, 4);
    HuSprBankSet(group, 4, 11, 0);
    HuSprAnimModeSet(group, 4, HUSPR_ANIM_MODE_BANK);

    HuSprDispOn(group, 5);
    HuSprBankSet(group, 5, time / 10, 0);
    HuSprAnimModeSet(group, 5, HUSPR_ANIM_MODE_BANK);
    time %= 10;

    HuSprDispOn(group, 6);
    HuSprBankSet(group, 6, time, 0);
    HuSprAnimModeSet(group, 6, HUSPR_ANIM_MODE_BANK);
}

void func_800E6968_minigame(s16 index, s16 time) {
    s16 group = D_800EBDE8_minigame[index];
    s16 digit;
    s16 seconds;

    D_800EB938_minigame += 10.0f;
    if (D_800EB938_minigame > 180.0f) {
        D_800EB938_minigame = 180.0f;
    }

    HuSprScaleSet(group, 0, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprScaleSet(group, 1, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprScaleSet(group, 2, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprScaleSet(group, 3, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprScaleSet(group, 4, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprScaleSet(group, 5, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);
    HuSprScaleSet(group, 6, sindf(D_800EB938_minigame) + 1.0f, sindf(D_800EB938_minigame) + 1.0f);

    HuSprDispOn(group, 0);
    digit = time / 3600;
    HuSprBankSet(group, 0, digit, 0);
    HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_BANK);
    time -= digit * 3600;

    HuSprDispOn(group, 1);
    HuSprBankSet(group, 1, 10, 0);
    HuSprAnimModeSet(group, 1, HUSPR_ANIM_MODE_BANK);

    HuSprDispOn(group, 2);
    digit = time / 600;
    HuSprBankSet(group, 2, digit, 0);
    HuSprAnimModeSet(group, 2, HUSPR_ANIM_MODE_BANK);
    time -= digit * 600;

    seconds = time / 60;
    digit = seconds;
    HuSprDispOn(group, 3);
    HuSprBankSet(group, 3, seconds, 0);
    HuSprAnimModeSet(group, 3, HUSPR_ANIM_MODE_BANK);
    time = time * 100 / 60 - digit * 100;

    HuSprDispOn(group, 4);
    HuSprBankSet(group, 4, 11, 0);
    HuSprAnimModeSet(group, 4, HUSPR_ANIM_MODE_BANK);

    HuSprDispOn(group, 5);
    HuSprBankSet(group, 5, time / 10, 0);
    HuSprAnimModeSet(group, 5, HUSPR_ANIM_MODE_BANK);
    time %= 10;

    HuSprDispOn(group, 6);
    HuSprBankSet(group, 6, time, 0);
    HuSprAnimModeSet(group, 6, HUSPR_ANIM_MODE_BANK);
}

void func_800E6E4C_minigame(s16 arg0) {
    D_800EBDE0_minigame->startDelay = arg0;
}

void func_800E6E5C_minigame(s16 arg0) {
    D_800EBDE0_minigame->timer = arg0;
}

void func_800E6E6C_minigame(s16 arg0) {
    D_800EBDE0_minigame->resultDelay = arg0;
}

void func_800E6E7C_minigame(s8 arg0) {
    D_800EBDE0_minigame->type = arg0;
}

u8 func_800E6E8C_minigame(void) {
    return D_800EBDE0_minigame->state;
}

u16 func_800E6E9C_minigame(void) {
    s32 value;

    switch (D_800EBDE0_minigame->state) {
        case MG_STATE_OPENING:
            value = D_800EB910_minigame;
            break;
        case MG_STATE_START:
            value = D_800EB912_minigame;
            break;
        case MG_STATE_PLAY:
            value = D_800EB914_minigame;
            break;
        case MG_STATE_FINISH:
            value = D_800EB916_minigame;
            break;
        case MG_STATE_RESULT:
        default:
            value = D_800EB918_minigame;
            break;
    }

    return value;
}

void func_800E6F0C_minigame(u8 arg0) {
    D_800EBDE0_minigame->state = arg0;
}

void func_800E6F1C_minigame(void) {
    D_800EBDE0_minigame->state++;
}

void func_800E6F34_minigame(s32 arg0) {
    D_800EB91A_minigame = arg0;
}

u8 func_800E6F40_minigame(void) {
    char *stateNames[] = { "OPENING", "PLAYING", "DIRECTION", "ENDING" };
    s16 mes;

    if (D_800D530C_main == 1) {
        func_800E6F0C_minigame(MG_STATE_EXIT);
    }
    func_800EA518_minigame();

    switch (D_800EBDE0_minigame->state) {
        case MG_STATE_OPENING:
            if (WipeStatGet() != 0) {
                break;
            }
            if (D_800EBDE0_minigame->startDelay == 0) {
                func_800E6F0C_minigame(MG_STATE_START);
            } else if (D_800EBDE0_minigame->startDelay != -1) {
                D_800EBDE0_minigame->startDelay--;
            }
            D_800EB910_minigame++;
            break;

        case MG_STATE_START:
            if (D_800EB912_minigame == 0) {
                switch (D_800EBDE0_minigame->type) {
                    case MINIGAME_4P:
                        mes = 3;
                        break;
                    case MINIGAME_1V3:
                        mes = 5;
                        break;
                    case MINIGAME_2V2:
                        mes = 4;
                        break;
                    case MINIGAME_ITEM:
                        mes = 8;
                        break;
                    case MINIGAME_BATTLE:
                        mes = 6;
                        break;
                    case 6:
                        mes = 9;
                        break;
                    case MINIGAME_1V1:
                    case 7:
                        mes = 7;
                        break;
                }
                GMesCreate(mes);
            } else if (D_800EB912_minigame == 75.0) {
                func_800E6F0C_minigame(MG_STATE_PLAY);
            }
            if (D_800EB932_minigame == D_800EB912_minigame && D_800EB930_minigame != -1) {
                HuAudSeqPlay(D_800EB930_minigame);
            }
            D_800EB912_minigame++;
            break;

        case MG_STATE_PLAY:
            if (D_800EB914_minigame == 0 && D_800EBDE0_minigame->timeDisp == MG_TIME_DISP_COUNTDOWN) {
                GMesCreate(0x1A, 30, 160, 24);
            }
            switch (D_800EBDE0_minigame->timeDisp) {
                case MG_TIME_DISP_NONE:
                    break;
                case MG_TIME_DISP_RECORD:
                    func_800E6670_minigame(0, D_800EB914_minigame * 2);
                    if (D_800EBDE0_minigame->timeLimit == D_800EB914_minigame) {
                        func_800E6F0C_minigame(MG_STATE_FINISH);
                    }
                    break;
                case MG_TIME_DISP_COUNTDOWN:
                    func_8003F578_main(D_800EBDE0_minigame->timer / 30 + 1);
                    break;
            }
            if (D_800EBDE0_minigame->timeLimit != -1) {
                if (D_800EBDE0_minigame->timeLimit - 900 == D_800EB914_minigame) {
                    GMesCreate(0x1A, 30, 160, 24);
                    D_800EB93C_minigame = 1;
                } else if (D_800EBDE0_minigame->timeLimit - 900 < D_800EB914_minigame) {
                    func_8003F578_main((D_800EBDE0_minigame->timeLimit - D_800EB914_minigame) / 30 + 1);
                }
            }
            if (D_800EBDE0_minigame->timer != -1) {
                switch (D_800EBDE0_minigame->timerMode) {
                    case MG_TIMER_COUNT_UP:
                        if (D_800EBDE0_minigame->timer >= D_800EBDE0_minigame->timeLimit) {
                            func_800E6F0C_minigame(MG_STATE_FINISH);
                        } else {
                            D_800EBDE0_minigame->timer++;
                        }
                        break;
                    case MG_TIMER_COUNT_DOWN:
                        if (D_800EBDE0_minigame->timer == 0) {
                            func_800E6F0C_minigame(MG_STATE_FINISH);
                            func_8003F578_main(0);
                        } else {
                            D_800EBDE0_minigame->timer--;
                        }
                        break;
                    case MG_TIMER_NONE:
                        break;
                }
            }
            D_800EB914_minigame++;
            break;

        case MG_STATE_FINISH:
            if (D_800EB916_minigame == 0) {
                D_800EB914_minigame--;
                if (D_800EB914_minigame * 2 < D_800EB92A_minigame) {
                    D_800EBDE0_minigame->newRecord = TRUE;
                    GWMgRecordSet((s16)D_800EB92C_minigame, (u16)(D_800EB914_minigame * 2));
                    D_800EBDE0_minigame->resultDelay += 75.0;
                    D_800EB940_minigame = 1;
                }
                if (D_800EBDE0_minigame->timeDisp == MG_TIME_DISP_COUNTDOWN || D_800EB93C_minigame != 0) {
                    func_8003F5C0_main();
                }
                switch (D_800EBDE0_minigame->type) {
                    case MINIGAME_4P:
                        mes = 0xE;
                        break;
                    case MINIGAME_1V3:
                        mes = 0x10;
                        break;
                    case MINIGAME_2V2:
                        mes = 0xF;
                        break;
                    case MINIGAME_ITEM:
                        mes = 0x13;
                        break;
                    case MINIGAME_BATTLE:
                        mes = 0x11;
                        break;
                    case 6:
                        mes = 0x14;
                        break;
                    case MINIGAME_1V1:
                    case 7:
                        mes = 0x12;
                        break;
                }
                GMesCreate(mes);
                HuAudSeqFadeOut(120);
            }
            if (D_800EBDE0_minigame->finishDelay == 0) {
                func_800E6F0C_minigame(MG_STATE_RESULT);
            } else if (D_800EBDE0_minigame->finishDelay != -1) {
                D_800EBDE0_minigame->finishDelay--;
            }
            D_800EB916_minigame++;
            break;

        case MG_STATE_RESULT:
            D_800EB934_minigame = 0;
            if (D_800EB918_minigame == 0 && D_800EBDE0_minigame->newRecord == TRUE) {
                D_800EB91A_minigame = 75;
                GMesCreate(0x1B);
            }
            if (D_800EB918_minigame == D_800EB91A_minigame) {
                switch (D_800EBDE0_minigame->resultType) {
                    case MG_RESULT_WIN_1:
                        GMesCreate(0x16, GwPlayer[D_800EBDE0_minigame->winners[0]].chr);
                        if (D_800EBDE0_minigame->newRecord == TRUE) {
                            HuAudSeqPlay(0x6A);
                        } else if (D_800EBDE0_minigame->type == MINIGAME_BATTLE) {
                            HuAudSeqPlay(0x67);
                        } else {
                            HuAudSeqPlay(0x65);
                        }
                        break;
                    case MG_RESULT_WIN_2:
                        GMesCreate(0x1E, GwPlayer[D_800EBDE0_minigame->winners[0]].chr,
                                   GwPlayer[D_800EBDE0_minigame->winners[1]].chr);
                        if (D_800EBDE0_minigame->newRecord == TRUE) {
                            HuAudSeqPlay(0x6A);
                        } else {
                            HuAudSeqPlay(0x66);
                        }
                        break;
                    case MG_RESULT_WIN_3:
                        GMesCreate(0x22, GwPlayer[D_800EBDE0_minigame->winners[0]].chr,
                                   GwPlayer[D_800EBDE0_minigame->winners[1]].chr,
                                   GwPlayer[D_800EBDE0_minigame->winners[2]].chr);
                        HuAudSeqPlay(0x66);
                        break;
                    case MG_RESULT_WIN_4:
                        GMesCreate(0x23, GwPlayer[D_800EBDE0_minigame->winners[0]].chr,
                                   GwPlayer[D_800EBDE0_minigame->winners[1]].chr,
                                   GwPlayer[D_800EBDE0_minigame->winners[2]].chr,
                                   GwPlayer[D_800EBDE0_minigame->winners[3]].chr);
                        HuAudSeqPlay(0x66);
                        break;
                    case MG_RESULT_DRAW:
                        GMesCreate(0x20);
                        HuAudSeqPlay(0x6C);
                        break;
                    case MG_RESULT_GOT_ITEM:
                        GMesCreate(0x24);
                        HuAudSeqPlay(0x68);
                        break;
                    case MG_RESULT_GOT_ITEM_ALT:
                        GMesCreate(0x25);
                        HuAudSeqPlay(0x69);
                        break;
                    case MG_RESULT_GAME_OVER:
                        GMesCreate(0x1D);
                        HuAudSeqPlay(0x6B);
                        break;
                    case MG_RESULT_LOSER:
                        GMesCreate(0x17);
                        break;
                    case MG_RESULT_NONE:
                        break;
                }
                D_800EB934_minigame = 1;
            }
            if (D_800EBDE0_minigame->resultDelay == 0) {
                func_800E6F0C_minigame(MG_STATE_EXIT);
            } else if (D_800EBDE0_minigame->resultDelay != -1) {
                D_800EBDE0_minigame->resultDelay--;
            }
            if (D_800EB940_minigame != 0) {
                func_800E6968_minigame(1, D_800EB914_minigame * 2);
            }
            D_800EB918_minigame++;
            break;

        case MG_STATE_EXIT:
            break;
    }

    switch (D_800EBDE0_minigame->gauge & MG_GAUGE_LAYOUT_MASK) {
        case MG_GAUGE_CORNERS_4:
            func_800EA178_minigame(2, D_800EBDE0_minigame->gaugeValue[2]);
            func_800EA178_minigame(3, D_800EBDE0_minigame->gaugeValue[3]);
        case MG_GAUGE_TOP_2:
        case MG_GAUGE_RIGHT_2:
            func_800EA178_minigame(0, D_800EBDE0_minigame->gaugeValue[0]);
            func_800EA178_minigame(1, D_800EBDE0_minigame->gaugeValue[1]);
            break;
    }

    return D_800EBDE0_minigame->state;
}
