#include "common.h"
#include "game/overlays/minigame.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/sprite.h"
#include "math.h"

u16 mgFlowOpeningTime = 0;
u16 mgFlowStartTime = 0;
u16 mgFlowPlayTime = 0;
u16 mgFlowFinishTime = 0;
u16 mgFlowResultTime = 0;
u16 mgFlowResultWait = 0;
s32 mgRecordX = 0x90;
s32 mgRecordY = 0xD0;
s32 mgRecordPrio = 1;
s16 mgRecordPad = 0; /* Unreferenced. */
s16 mgRecordTime = -1;
s32 mgRecordNo = -1;
s16 mgFlowSeqNo = -1;
s16 mgFlowSeqTime = 75;
s16 mgFlowResultF = 0;
f32 mgRecordZoomAngle = 0.0f;
s32 mgFlowTimerMesF = 0;
s32 mgRecordNewF = 0;

extern s32 omovl;
extern u8 storySceneNo;
extern s16 mgTimeSprAnim;
extern s16 mgRecordSprAnim;
extern s16 mgTimeGrpTbl[];

void MgFlowInit(MinigameFlow *flow) {
    flow->state = MG_STATE_OPENING;
    mgFlow = flow;
    if (flow->timeDisp == MG_TIME_DISP_RECORD) {
        MgRecordSprLoad();
        MgTimeSprLoad();
        MgRecordGrpCreate(mgRecordX, mgRecordY);
        MgTimeGrpCreate(mgRecordX, mgRecordY + 12);
        switch ((u32)omovl) {
            case 0x10:
                mgRecordNo = 1;
                mgRecordTime = GWMgRecordGet(mgRecordNo);
                break;
            case 0x23:
                mgRecordNo = 2;
                mgRecordTime = GWMgRecordGet(mgRecordNo);
                break;
            case 0x46:
                mgRecordNo = storySceneNo + 5;
                mgRecordTime = GWMgRecordGet(mgRecordNo);
                break;
        }
        MgTimeDispSet(1, mgRecordTime);
        MgTimeDispSet(0, 0);
    }

    switch (mgFlow->gauge & MG_GAUGE_LAYOUT_MASK) {
        case MG_GAUGE_CORNERS_4:
            MgGaugeInit(4, mgFlow->gauge & MG_GAUGE_LENGTH_MASK);
            MgGaugeRangeSet(0, 0.0f, 100.0f);
            MgGaugePosSet(0, 24, 16, 0);
            MgGaugeDispOn(0);
            MgGaugeRangeSet(1, 0.0f, 100.0f);
            MgGaugePosSet(1, 296 - (mgFlow->gauge & MG_GAUGE_LENGTH_MASK) * 10, 16, 0);
            MgGaugeDispOn(1);
            MgGaugeRangeSet(2, 0.0f, 100.0f);
            MgGaugePosSet(2, 24, 200, 0);
            MgGaugeDispOn(2);
            MgGaugeRangeSet(3, 0.0f, 100.0f);
            MgGaugePosSet(3, 296 - (mgFlow->gauge & MG_GAUGE_LENGTH_MASK) * 10, 200, 0);
            MgGaugeDispOn(3);
            break;
        case MG_GAUGE_TOP_2:
            MgGaugeInit(2, mgFlow->gauge & MG_GAUGE_LENGTH_MASK);
            MgGaugeRangeSet(0, 0.0f, 100.0f);
            MgGaugePosSet(0, 24, 16, 0);
            MgGaugeDispOn(0);
            MgGaugeRangeSet(1, 0.0f, 100.0f);
            MgGaugePosSet(1, 296 - (mgFlow->gauge & MG_GAUGE_LENGTH_MASK) * 10, 16, 0);
            MgGaugeDispOn(1);
            break;
        case MG_GAUGE_RIGHT_2:
            MgGaugeInit(2, mgFlow->gauge & MG_GAUGE_LENGTH_MASK);
            MgGaugeRangeSet(0, 0.0f, 100.0f);
            MgGaugePosSet(0, 296 - (mgFlow->gauge & MG_GAUGE_LENGTH_MASK) * 10, 16, 0);
            MgGaugeDispOn(0);
            MgGaugeRangeSet(1, 0.0f, 100.0f);
            MgGaugePosSet(1, 296 - (mgFlow->gauge & MG_GAUGE_LENGTH_MASK) * 10, 130, 0);
            MgGaugeDispOn(1);
            break;
    }

    mgFlowOpeningTime = 0;
    mgFlowStartTime = 0;
    mgFlowPlayTime = 0;
    mgFlowFinishTime = 0;
    mgFlowResultTime = 0;
    mgFlowResultWait = 0;
    mgFlowResultF = 0;
}

void MgRecordPosSet(s32 arg0, s32 arg1) {
    mgRecordX = arg0;
    mgRecordY = arg1;
}

void MgRecordPrioSet(s32 arg0) {
    mgRecordPrio = arg0;
}

void MgTimeSprLoad(void) {
    void *data;

    data = DataRead(0x31);
    mgTimeSprAnim = HuSprAnimRead(data);
    DataClose(data);
}

void MgRecordSprLoad(void) {
    void *data;

    data = DataRead(0x31);
    mgRecordSprAnim = HuSprAnimRead(data);
    DataClose(data);
    espPalColorSet(mgRecordSprAnim, 0.0f, 1.0f, 0.0f);
}

s16 MgTimeGrpCreate(s32 x, s32 y) {
    s16 group;
    s16 member;
    s16 memberX;

    group = mgTimeGrpTbl[0] = HuSprGrpCreate(7, 5);
    HuSprGrpMemberSet(group, 0, mgTimeSprAnim, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprDispOff(group, 0);
    HuSprPosSet(group, 0, x - 16, y);
    HuSprPriSet(group, 0, (u16)mgRecordPrio);

    memberX = 4;
    for (member = 1; member < 7; member++) {
        HuSprPriSet(group, member, (u16)mgRecordPrio);
        HuSprGrpMemberSet(group, member, mgTimeSprAnim, 0);
        HuSprPosSet(group, member, memberX, 0);
        HuSprAttrReset(group, member, 0xFFFF);
        HuSprDispOff(group, member);
        if (member == 3) {
            memberX += 8;
        } else {
            memberX += 12;
        }
        HuSprParentSet(group, member, 0);
    }

    HuSprDispOn(group, 2);
    return group;
}

s16 MgRecordGrpCreate(s32 x, s32 y) {
    s16 group;
    s16 member;
    s16 memberX;

    group = mgTimeGrpTbl[1] = HuSprGrpCreate(7, 5);
    HuSprGrpMemberSet(group, 0, mgRecordSprAnim, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprDispOff(group, 0);
    HuSprPosSet(group, 0, x - 16, y);
    HuSprPriSet(group, 0, (u16)mgRecordPrio);

    memberX = 4;
    for (member = 1; member < 7; member++) {
        HuSprPriSet(group, member, (u16)mgRecordPrio);
        HuSprGrpMemberSet(group, member, mgRecordSprAnim, 0);
        HuSprPosSet(group, member, memberX, 0);
        HuSprAttrReset(group, member, 0xFFFF);
        HuSprDispOff(group, member);
        if (member == 3) {
            memberX += 8;
        } else {
            memberX += 12;
        }
        HuSprParentSet(group, member, 0);
    }

    HuSprDispOn(group, 2);
    return group;
}

void MgTimeDispSet(s16 index, s16 time) {
    s16 group = mgTimeGrpTbl[index];
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

void MgTimeDispZoomSet(s16 index, s16 time) {
    s16 group = mgTimeGrpTbl[index];
    s16 digit;
    s16 seconds;

    mgRecordZoomAngle += 10.0f;
    if (mgRecordZoomAngle > 180.0f) {
        mgRecordZoomAngle = 180.0f;
    }

    HuSprScaleSet(group, 0, sindf(mgRecordZoomAngle) + 1.0f, sindf(mgRecordZoomAngle) + 1.0f);
    HuSprScaleSet(group, 1, sindf(mgRecordZoomAngle) + 1.0f, sindf(mgRecordZoomAngle) + 1.0f);
    HuSprScaleSet(group, 2, sindf(mgRecordZoomAngle) + 1.0f, sindf(mgRecordZoomAngle) + 1.0f);
    HuSprScaleSet(group, 3, sindf(mgRecordZoomAngle) + 1.0f, sindf(mgRecordZoomAngle) + 1.0f);
    HuSprScaleSet(group, 4, sindf(mgRecordZoomAngle) + 1.0f, sindf(mgRecordZoomAngle) + 1.0f);
    HuSprScaleSet(group, 5, sindf(mgRecordZoomAngle) + 1.0f, sindf(mgRecordZoomAngle) + 1.0f);
    HuSprScaleSet(group, 6, sindf(mgRecordZoomAngle) + 1.0f, sindf(mgRecordZoomAngle) + 1.0f);

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

void MgFlowStartDelaySet(s16 arg0) {
    mgFlow->startDelay = arg0;
}

void MgFlowTimerSet(s16 arg0) {
    mgFlow->timer = arg0;
}

void MgFlowResultDelaySet(s16 arg0) {
    mgFlow->resultDelay = arg0;
}

void MgFlowTypeSet(s8 arg0) {
    mgFlow->type = arg0;
}

u8 MgFlowStatGet(void) {
    return mgFlow->state;
}

u16 MgFlowStatTimeGet(void) {
    s32 value;

    switch (mgFlow->state) {
        case MG_STATE_OPENING:
            value = mgFlowOpeningTime;
            break;
        case MG_STATE_START:
            value = mgFlowStartTime;
            break;
        case MG_STATE_PLAY:
            value = mgFlowPlayTime;
            break;
        case MG_STATE_FINISH:
            value = mgFlowFinishTime;
            break;
        case MG_STATE_RESULT:
        default:
            value = mgFlowResultTime;
            break;
    }

    return value;
}

void MgFlowStatSet(u8 arg0) {
    mgFlow->state = arg0;
}

void MgFlowStatNext(void) {
    mgFlow->state++;
}

void MgFlowResultWaitSet(s32 arg0) {
    mgFlowResultWait = arg0;
}

u8 MgFlowMain(void) {
    char *stateNames[] = { "OPENING", "PLAYING", "DIRECTION", "ENDING" };
    s16 mes;

    if (omSysExitReq == 1) {
        MgFlowStatSet(MG_STATE_EXIT);
    }
    MgGaugeUpdate();

    switch (mgFlow->state) {
        case MG_STATE_OPENING:
            if (WipeStatGet() != 0) {
                break;
            }
            if (mgFlow->startDelay == 0) {
                MgFlowStatSet(MG_STATE_START);
            } else if (mgFlow->startDelay != -1) {
                mgFlow->startDelay--;
            }
            mgFlowOpeningTime++;
            break;

        case MG_STATE_START:
            if (mgFlowStartTime == 0) {
                switch (mgFlow->type) {
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
            } else if (mgFlowStartTime == 75.0) {
                MgFlowStatSet(MG_STATE_PLAY);
            }
            if (mgFlowSeqTime == mgFlowStartTime && mgFlowSeqNo != -1) {
                HuAudSeqPlay(mgFlowSeqNo);
            }
            mgFlowStartTime++;
            break;

        case MG_STATE_PLAY:
            if (mgFlowPlayTime == 0 && mgFlow->timeDisp == MG_TIME_DISP_COUNTDOWN) {
                GMesCreate(GMES_MES_TIMER, 30, 160, 24);
            }
            switch (mgFlow->timeDisp) {
                case MG_TIME_DISP_NONE:
                    break;
                case MG_TIME_DISP_RECORD:
                    MgTimeDispSet(0, mgFlowPlayTime * 2);
                    if (mgFlow->timeLimit == mgFlowPlayTime) {
                        MgFlowStatSet(MG_STATE_FINISH);
                    }
                    break;
                case MG_TIME_DISP_COUNTDOWN:
                    GMesTimerValueSet(mgFlow->timer / 30 + 1);
                    break;
            }
            if (mgFlow->timeLimit != -1) {
                if (mgFlow->timeLimit - 900 == mgFlowPlayTime) {
                    GMesCreate(GMES_MES_TIMER, 30, 160, 24);
                    mgFlowTimerMesF = 1;
                } else if (mgFlow->timeLimit - 900 < mgFlowPlayTime) {
                    GMesTimerValueSet((mgFlow->timeLimit - mgFlowPlayTime) / 30 + 1);
                }
            }
            if (mgFlow->timer != -1) {
                switch (mgFlow->timerMode) {
                    case MG_TIMER_COUNT_UP:
                        if (mgFlow->timer >= mgFlow->timeLimit) {
                            MgFlowStatSet(MG_STATE_FINISH);
                        } else {
                            mgFlow->timer++;
                        }
                        break;
                    case MG_TIMER_COUNT_DOWN:
                        if (mgFlow->timer == 0) {
                            MgFlowStatSet(MG_STATE_FINISH);
                            GMesTimerValueSet(0);
                        } else {
                            mgFlow->timer--;
                        }
                        break;
                    case MG_TIMER_NONE:
                        break;
                }
            }
            mgFlowPlayTime++;
            break;

        case MG_STATE_FINISH:
            if (mgFlowFinishTime == 0) {
                mgFlowPlayTime--;
                if (mgFlowPlayTime * 2 < mgRecordTime) {
                    mgFlow->newRecord = TRUE;
                    GWMgRecordSet((s16)mgRecordNo, (u16)(mgFlowPlayTime * 2));
                    mgFlow->resultDelay += 75.0;
                    mgRecordNewF = 1;
                }
                if (mgFlow->timeDisp == MG_TIME_DISP_COUNTDOWN || mgFlowTimerMesF != 0) {
                    GMesTimerEnd();
                }
                switch (mgFlow->type) {
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
            if (mgFlow->finishDelay == 0) {
                MgFlowStatSet(MG_STATE_RESULT);
            } else if (mgFlow->finishDelay != -1) {
                mgFlow->finishDelay--;
            }
            mgFlowFinishTime++;
            break;

        case MG_STATE_RESULT:
            mgFlowResultF = 0;
            if (mgFlowResultTime == 0 && mgFlow->newRecord == TRUE) {
                mgFlowResultWait = 75;
                GMesCreate(GMES_MES_MG_RECORD);
            }
            if (mgFlowResultTime == mgFlowResultWait) {
                switch (mgFlow->resultType) {
                    case MG_RESULT_WIN_1:
                        GMesCreate(GMES_MES_MG_WINNER, GwPlayer[mgFlow->winners[0]].chr);
                        if (mgFlow->newRecord == TRUE) {
                            HuAudSeqPlay(0x6A);
                        } else if (mgFlow->type == MINIGAME_BATTLE) {
                            HuAudSeqPlay(0x67);
                        } else {
                            HuAudSeqPlay(0x65);
                        }
                        break;
                    case MG_RESULT_WIN_2:
                        GMesCreate(GMES_MES_MG_WINNERS_2, GwPlayer[mgFlow->winners[0]].chr,
                                   GwPlayer[mgFlow->winners[1]].chr);
                        if (mgFlow->newRecord == TRUE) {
                            HuAudSeqPlay(0x6A);
                        } else {
                            HuAudSeqPlay(0x66);
                        }
                        break;
                    case MG_RESULT_WIN_3:
                        GMesCreate(GMES_MES_MG_WINNERS_3, GwPlayer[mgFlow->winners[0]].chr,
                                   GwPlayer[mgFlow->winners[1]].chr,
                                   GwPlayer[mgFlow->winners[2]].chr);
                        HuAudSeqPlay(0x66);
                        break;
                    case MG_RESULT_WIN_4:
                        GMesCreate(GMES_MES_MG_WINNERS_4, GwPlayer[mgFlow->winners[0]].chr,
                                   GwPlayer[mgFlow->winners[1]].chr,
                                   GwPlayer[mgFlow->winners[2]].chr,
                                   GwPlayer[mgFlow->winners[3]].chr);
                        HuAudSeqPlay(0x66);
                        break;
                    case MG_RESULT_DRAW:
                        GMesCreate(GMES_MES_MG_DRAW);
                        HuAudSeqPlay(0x6C);
                        break;
                    case MG_RESULT_GOT_ITEM:
                        GMesCreate(GMES_MES_36);
                        HuAudSeqPlay(0x68);
                        break;
                    case MG_RESULT_GOT_ITEM_ALT:
                        GMesCreate(GMES_MES_37);
                        HuAudSeqPlay(0x69);
                        break;
                    case MG_RESULT_GAME_OVER:
                        GMesCreate(GMES_MES_29);
                        HuAudSeqPlay(0x6B);
                        break;
                    case MG_RESULT_LOSER:
                        GMesCreate(GMES_MES_MG_LOSER);
                        break;
                    case MG_RESULT_NONE:
                        break;
                }
                mgFlowResultF = 1;
            }
            if (mgFlow->resultDelay == 0) {
                MgFlowStatSet(MG_STATE_EXIT);
            } else if (mgFlow->resultDelay != -1) {
                mgFlow->resultDelay--;
            }
            if (mgRecordNewF != 0) {
                MgTimeDispZoomSet(1, mgFlowPlayTime * 2);
            }
            mgFlowResultTime++;
            break;

        case MG_STATE_EXIT:
            break;
    }

    switch (mgFlow->gauge & MG_GAUGE_LAYOUT_MASK) {
        case MG_GAUGE_CORNERS_4:
            MgGaugeValueSet(2, mgFlow->gaugeValue[2]);
            MgGaugeValueSet(3, mgFlow->gaugeValue[3]);
        case MG_GAUGE_TOP_2:
        case MG_GAUGE_RIGHT_2:
            MgGaugeValueSet(0, mgFlow->gaugeValue[0]);
            MgGaugeValueSet(1, mgFlow->gaugeValue[1]);
            break;
    }

    return mgFlow->state;
}
