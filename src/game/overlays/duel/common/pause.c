#include "common_duel.h"
#include "ovl_81.h"

typedef struct UnkD8250PrcData {
    /* 0x00 */ s32 *unk_00;
    /* 0x04 */ u16 unk_04;
} UnkD8250PrcData; // sizeof 0x8

extern UnkOvl81_2 *D_801053E0_name_81;
extern s16 D_801053E4_name_81;
extern s16 D_801053E6_name_81;
extern s32 D_801053E8_name_81;
extern s32 D_801053EC_name_81;
extern s16 D_801053F0_name_81[];
extern s16 D_801053F4_name_81;
extern s8 omOvlSeKeepF;

s32 D_80101230_name_81[] = { 0x1300AB, 0x1300AC, 0x1300AD, 0x1300AE, 0x1300AF, 0x1300B0 };
s16 D_80101248_name_81 = 0;
s16 D_8010124A_name_81 = 0;
s32 D_8010124C_name_81 = 0;
s32 D_80101250_name_81 = 0;
u8 D_80101254_name_81[][3] = { { 254, 255, 164 }, { 255, 164, 172 }, { 204, 255, 131 } };
s32 D_80101260_name_81[] = { 0x1D01, 0x1D0A, 0x1D04 };
s32 D_8010126C_name_81[] = { 0x5102, 0x5105, 0x5127, 0x512C, 0x5121, 0x5108, 0x510C, 0x5110 };
s32 D_8010128C_name_81[] = { 0x13008C, 0x13008D, 0x13008F, 0x130092, 0x130095, 0x130099, 0x13009B, 0x13009A };
s32 D_801012AC_name_81[] = { 0x13008D, 0x13008E };
s32 D_801012B4_name_81[] = { 0x13008F, 0x130090 };
s32 D_801012BC_name_81[] = { 0x130091, 0x130092, 0x130093 };
s32 D_801012C8_name_81[] = { 0x130094, 0x130095, 0x130096 };
s32 D_801012D4_name_81[] = { 0x130097, 0x130098, 0x130099 };
s32 D_801012E0_name_81 = 0x1300B1;
s32 D_801012E4_name_81 = 0x1300B2;
s32 D_801012E8_name_81 = 0x13009D;
s32 D_801012EC_name_81[] = { 0x511F, 0x5120 };
s32 D_801012F4_name_81[] = { 0x1300D8, 0x1300D9, 0x1300DB, 0x1300DC, 0x1300DD, 0x1300DE, 0x1300DF, 0x1300E1 };
s32 D_80101314_name_81[] = { 0x13009E, 0x13009F, 0x1300A0, 0x1300A1, 0x1300A2, 0x1300A6, 0x1300A5, 0x1300A4, 0x1300A3 };
s8 D_80101338_name_81[] = { 0, -1, 1, -1, 2, -1, 3, -1 };
s8 D_80101340_name_81[] = { 4, 8, 4, 7, 4, 6, 4, 5 };
s16 D_80101348_name_81[] = { 90, 230 };
s16 D_8010134C_name_81[] = { 62, 122 };
s16 D_80101350_name_81[][4] = {
    { 0, 1, 0, 1 },
    { -1, 0, -1, 0 },
    { 0, 1, 0, 1 },
    { -1, 0, -1, 0 }
};
u8 D_80101370_name_81[] = { 0, 1, 2, 3 };
u32 D_80101374_name_81[] = { 8, 0x20001, 0x2002B, 0x20036, 0x20023, 0x20035, 0x20038, 0x20032, 0x20003 };
s32 D_80101398_name_81[] = { 8, 0x30001, 0x3002B, 0x30020, 0x30023, 0x30035, 0x30038, 0x30032, 0x30003 };
s32 D_801013BC_name_81[] = { 8, 0x70001, 0x7002B, 0x70020, 0x70023, 0x70035, 0x70038, 0x70032, 0x70003 };
s32 D_801013E0_name_81[] = { 8, 0x40001, 0x4002B, 0x40020, 0x40023, 0x40035, 0x40038, 0x40032, 0x40003 };
s32 D_80101404_name_81[] = { 8, 0x50001, 0x5002B, 0x50020, 0x50023, 0x50035, 0x50038, 0x50032, 0x50003 };
s32 D_80101428_name_81[] = { 8, 0x60001, 0x6002B, 0x60020, 0x60023, 0x60035, 0x60038, 0x60032, 0x60003 };
s32 D_8010144C_name_81[] = { 8, 0x80001, 0x3002B, 0x80020, 0x30023, 0x80035, 0x80038, 0x80032, 0x80003 };
s32 D_80101470_name_81[] = { 8, 0x70001, 0x7002B, 0x70020, 0x70023, 0x9000D, 0x90010, 0x9000A, 0x70003 };
s32 *D_80101494_name_81[] = {
    (s32 *)D_80101374_name_81,
    D_80101398_name_81,
    D_801013BC_name_81,
    D_801013E0_name_81,
    D_80101404_name_81,
    D_80101428_name_81,
    D_8010144C_name_81,
    D_80101470_name_81,
};
u8 D_801014B4_name_81[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
u8 D_801014BC_name_81[] = { 15, 16, 17, 18, 19, 20, 21, 22 };

s32 func_800F1784_name_81(s32 arg0);
s32 func_800F2618_name_81(s32 arg0);

void func_800F0480_name_81(Object *obj, s16 slot, s16 chr, s32 dataNum) {
    obj->omObj1->work[0] = (u8)CharAnimCreate(obj->omObj1->model[0], slot, chr, dataNum);
    obj->omObj1->work[1] = (u8)slot;
    obj->omObj1->work[2] = (u8)chr;
}

void func_800F04FC_name_81(GW_PLAYER *player, s16 slot, s16 arg2) {
    s16 chr = player->chr;
    Object *obj = player->player_obj;
    s32 dataNum = CharMotionDataNumGetTbl(chr, slot, arg2);

    if (dataNum != -1) {
        obj->omObj1->work[0] = (u8)CharAnimCreate(obj->omObj1->model[0], slot, chr, dataNum);
        obj->omObj1->work[1] = (u8)slot;
        obj->omObj1->work[2] = (u8)chr;
    }
}

void func_800F05AC_name_81(void) {
}

void func_800F05B4_name_81(Object *obj, s32 dataNum) {
    Hu3DAnimDataKill(obj->omObj1->work[0]);
    obj->omObj1->work[0] = (u8)Hu3DAnimDataRead(dataNum);
    CharAnimSet(obj->omObj1->model[0], obj->omObj1->work[1], obj->omObj1->work[2], obj->omObj1->work[0]);
}

void func_800F061C_name_81(GW_PLAYER *player, s16 arg1) {
    Object *obj = player->player_obj;
    s32 dataNum = CharMotionDataNumGetTbl(obj->omObj1->work[2], obj->omObj1->work[1], arg1);

    if (dataNum != -1) {
        Hu3DAnimDataKill(obj->omObj1->work[0]);
        obj->omObj1->work[0] = (u8)Hu3DAnimDataRead(dataNum);
        CharAnimSet(obj->omObj1->model[0], obj->omObj1->work[1], obj->omObj1->work[2], obj->omObj1->work[0]);
    }
}

void func_800F06A8_name_81(Object *obj) {
    CharAnimAttrSet(obj->omObj1->work[1], obj->omObj1->work[2], 1, 1);
}

void func_800F06D4_name_81(Object *obj) {
    CharAnimAttrSet(obj->omObj1->work[1], obj->omObj1->work[2], 1, 0);
}

s32 func_800F0700_name_81(s32 arg0) {
    return arg0;
}

static void func_800F0708_name_81(UnkBoard4 *arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    u8 temp_s0;
    void *temp_s5;
    s32 i;

    temp_s5 = DataRead(0x13008A);
    sprintf(omDBGStrBuf, "%2d", arg2);

    for (i = 0; i < 2; i++) {
        temp_s0 = omDBGStrBuf[i];
        arg0->unk_0C[arg1] = HuSprAnimRead(temp_s5);
        if (temp_s0 != 0x20) {
            HuSprGrpMemberSet(arg0->unk_0A, arg1, arg0->unk_0C[arg1], temp_s0 - 0x30);
        } else {
            HuSprGrpMemberSet(arg0->unk_0A, arg1, arg0->unk_0C[arg1], 0xA);
        }

        HuSprPriSet(arg0->unk_0A, arg1, 7);
        HuSprAttrSet(arg0->unk_0A, arg1, 0x01001000);
        HuSprPosSet(arg0->unk_0A, arg1, arg3, arg4);
        HuSprColorSet(arg0->unk_0A, arg1, D_80101254_name_81[D_80101250_name_81][0], D_80101254_name_81[D_80101250_name_81][1], D_80101254_name_81[D_80101250_name_81][2]);
        arg1 += 1;
        arg3 += 0xE;
    }
    DataClose(temp_s5);
}

static UnkBoard4 *func_800F08BC_name_81(void) {
    UnkBoard4 *temp_s1;
    void *data;

    temp_s1 = func_800F4528_name_81(0x10, 0);
    if (GwSystem.playMode & 4) {
        data = DataRead(0x13008B);
        D_80101250_name_81 = 2;
    } else if (GwSystem.total_turns == 20) {
        D_80101250_name_81 = 0;
        data = DataRead(0x130084);
    } else {
        D_80101250_name_81 = 1;
        data = DataRead(0x130086);
    }
    temp_s1->unk_0C[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(temp_s1->unk_0A, 0, temp_s1->unk_0C[0], 0);
    HuSprPriSet(temp_s1->unk_0A, 0, 7);
    HuSprAttrSet(temp_s1->unk_0A, 0, 0x1000);
    HuSprPosSet(temp_s1->unk_0A, 0, 0xA0, 0x73);
    HuSprColorSet(temp_s1->unk_0A, 0, D_80101254_name_81[D_80101250_name_81][0], D_80101254_name_81[D_80101250_name_81][1], D_80101254_name_81[D_80101250_name_81][2]);
    DataClose(data);

    if (GwSystem.total_turns == 20) {
        data = DataRead(0x130088);
    } else {
        data = DataRead(0x130089);
    }
    temp_s1->unk_0C[1] = HuSprAnimRead(data);
    HuSprGrpMemberSet(temp_s1->unk_0A, 1, temp_s1->unk_0C[1], 0);
    HuSprPriSet(temp_s1->unk_0A, 1, 7);
    HuSprAttrSet(temp_s1->unk_0A, 1, 0x1000);
    HuSprPosSet(temp_s1->unk_0A, 1, 0xA0, 0x90);
    HuSprColorSet(temp_s1->unk_0A, 1, D_80101254_name_81[D_80101250_name_81][0], D_80101254_name_81[D_80101250_name_81][1], D_80101254_name_81[D_80101250_name_81][2]);
    DataClose(data);

    if (GwSystem.total_turns == 20) {
        func_800F0708_name_81(temp_s1, 2, 20, 0xCB, 0x90);
        func_800F0708_name_81(temp_s1, 4, GwSystem.current_turn, 0xA1, 0x90);
    }

    data = DataRead(0x130083);
    temp_s1->unk_0C[6] = HuSprAnimRead(data);
    HuSprGrpMemberSet(temp_s1->unk_0A, 6, temp_s1->unk_0C[6], 0);
    HuSprPriSet(temp_s1->unk_0A, 6, 7);
    HuSprAttrSet(temp_s1->unk_0A, 6, 0x1000);
    HuSprPosSet(temp_s1->unk_0A, 6, 0xA0, 0x3C);
    DataClose(data);

    data = DataRead(D_80101230_name_81[GwSystem.current_board_index]);
    temp_s1->unk_0C[7] = HuSprAnimRead(data);
    HuSprGrpMemberSet(temp_s1->unk_0A, 7, temp_s1->unk_0C[7], 0);
    HuSprPriSet(temp_s1->unk_0A, 7, 6);
    HuSprAttrSet(temp_s1->unk_0A, 7, 0x1000);
    HuSprPosSet(temp_s1->unk_0A, 7, 0xA0, 0x22);
    DataClose(data);
    return temp_s1;
}

static void func_800F0C30_name_81(UnkBoard4 *arg0) {
    func_800F4584_name_81(arg0);
}

static s16 func_800F0C4C_name_81(s32 arg0) {
    DuelHelpWin *temp_s3;
    DuelHelpWin *temp_s2;
    s16 var_s0;
    UnkBoard4 *temp_s1;

    temp_s3 = func_800E1824_name_81(0xA, 0xAE, 0);
    temp_s2 = func_800E1824_name_81(5, 0xBC, 0);
    temp_s1 = func_800F08BC_name_81();
    HuPrcVSleep();

    while (1) {
        HuPrcVSleep();
        if (HuPadBtnDown[arg0] & A_BUTTON) {
            var_s0 = 4;
            break;
        } else if (HuPadBtnDown[arg0] & START_BUTTON) {
            var_s0 = 0;
            break;
        }
    }

    func_800F0C30_name_81(temp_s1);
    func_800E1854_name_81(temp_s3);
    func_800E1854_name_81(temp_s2);
    return var_s0;
}

void func_800F0D1C_name_81(UnkOvl81_2 *arg0, s16 arg1) {
    s32 i;
    Object *obj;
    s16 temp_s2;
    s16 temp = arg0->unk_0A;

    obj = arg0->obj;
    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.5f;
    temp_s2 = (arg1 - temp) / 14;

    for (i = 0; i < 14; i++) {
        temp = arg0->unk_0A;
        func_800E4EAC_name_81(arg0, (temp + temp_s2), 8);
        HuPrcVSleep();
    }
    func_800E4EAC_name_81(arg0, arg1, 8);
}

void func_800F0DF8_name_81(s16 arg0, s32 arg1) {
    HuWinHomeClear(arg0);
    HuWinMesSet(arg0, func_800F0700_name_81(arg1), -1, -1);
}

static void func_800F0E4C_name_81(s32 arg0, s16 arg1) {
    HuWinHomeClear(arg0);
    HuWinMesSet(arg0, D_80101260_name_81[arg1], HUWIN_POS_CENTER, HUWIN_POS_CENTER);
}

static s32 func_800F0EA8_name_81(s16 arg0, s16 arg1, s16 arg2) {
    s16 sp18[2];
    s16 sp20[2];
    s32 win;

    HuWinMesMaxSizeGet(1, sp18, D_80101260_name_81[0]);
    HuWinMesMaxSizeGet(1, sp20, D_80101260_name_81[1]);

    if (sp20[0] > sp18[0]) {
        D_801053F0_name_81[0] = sp20[0];
    } else {
        D_801053F0_name_81[0] = sp18[0];
    }
    D_801053F0_name_81[1] = sp18[1];
    arg1 += 0xA0;
    win = HuWinCreate(arg1 - (D_801053F0_name_81[0] / 2), arg2,
                      D_801053F0_name_81[0], D_801053F0_name_81[1], 0, 4);
    HuWinPriSet(win, 9);
    HuWinBGTPLvlSet(win, 0);
    HuWinMesSpeedSet(win, 0);
    HuWinAttrSet(win, HUWIN_ATTR_NONE, HUWIN_ATTR_OUTLINE);
    func_800F0E4C_name_81(win, arg0);
    return win;
}

void func_800F0FE8_name_81(void) {
    UnkD8250PrcData *work;
    s32 *mes;
    s16 sel;
    s16 sel2;
    s16 prev;
    s32 i;
    GW_SYSTEM *system;

    work = HuPrcCurrentGet()->user_data;

    mes = work->unk_00;
    sel = work->unk_04;
    system = &GwSystem;
    prev = -1;

    if (D_8010124C_name_81 != 0) {
        D_801053E8_name_81 = func_800F0EA8_name_81(0, 0, 0x92);
        D_801053EC_name_81 = func_800F0EA8_name_81(2, 0x64, 0x92);
    }

    while (1) {
        if (D_8010124C_name_81 != 0) {
            sel2 = D_80101248_name_81;
        } else {
            sel2 = HuWinChoiceNowGet(sel);
        }

        if (((sel2 != prev) && (sel2 != -1)) || (D_8010124A_name_81 != 0)) {
            if ((D_8010124A_name_81 == 0) && (D_8010124C_name_81 != 0)) {
                switch (sel2) {
                    case 0:
                    case 7:
                        func_800F0E4C_name_81(D_801053E8_name_81, 0);
                        break;
                    default:
                        func_800F0E4C_name_81(D_801053E8_name_81, 1);
                }
            }

            prev = sel2;
            D_8010124A_name_81 = 0;

            switch (mes[prev]) {
                case 0x5102:
                    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
                        if (GwPlayer[i].stat & 1) {
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x5104), i);
                        } else {
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x5103), i);
                        }
                    }
                    break;

                case 0x5105:
                    if (system->show_minigame_explanations == 0) {
                        HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x5106), 0);
                    } else {
                        HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x5107), 0);
                    }
                    break;

                case 0x5108:
                    switch (system->message_speed) {
                        case 0:
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x5109), 0);
                            break;
                        case 1:
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x510A), 0);
                            break;
                        case 2:
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x510B), 0);
                            break;
                    }
                    break;

                case 0x510C:
                    switch (system->save_mode) {
                        case 0:
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x510D), 0);
                            break;
                        case 1:
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x510E), 0);
                            break;
                        case 2:
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x510F), 0);
                            break;
                    }
                    break;

                case 0x5121:
                    switch (system->walk_speed) {
                        case 0:
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x5122), 0);
                            break;
                        case 1:
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x5123), 0);
                            break;
                        case 2:
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x5124), 0);
                            break;
                    }
                    break;

                case 0x5127:
                    switch (system->show_com_minigames) {
                        case 0:
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x5128), 0);
                            break;
                        case 1:
                            HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x5129), 0);
                            break;
                    }
                    break;

                case 0x512C:
                    if (_CheckFlag(0x20) != 0) {
                        HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x512B), 0);
                    } else {
                        HuWinInsertMesSet(D_801053E0_name_81->win_id, func_800F0700_name_81(0x512A), 0);
                    }
                    break;
            }

            func_800F0DF8_name_81(D_801053E0_name_81->win_id, mes[prev]);
        }
        HuPrcVSleep();
    }
}

Process *func_800F1340_name_81(s32 *arg0, s32 arg1, s16 arg2) {
    Process *prc = omAddPrcObj(func_800F0FE8_name_81, 0x1005, 0, 0x40);
    UnkD8250PrcData *data = HuMemMemoryAlloc(prc->heap, sizeof(UnkD8250PrcData));

    prc->user_data = data;
    data->unk_00 = arg0;
    data->unk_04 = arg2;
    D_8010124C_name_81 = arg1;
    return prc;
}

void func_800F13C0_name_81(Process *arg0) {
    if (D_8010124C_name_81 != 0) {
        HuWinKill(D_801053E8_name_81);
        HuWinKill(D_801053EC_name_81);
    }
    omDelPrcObj(arg0);
}

static s16 func_800F140C_name_81(s32 arg0, s16 arg1) {
    s16 sp18[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp18, arg0);
    temp_v0 = HuWinCreate(0xA0 - sp18[0] / 2, arg1, sp18[0], sp18[1], 0, 0);
    HuWinMesSet(temp_v0, arg0, -1, -1);
    return temp_v0;
}

s16 func_800F14A8_name_81(void) {
    s16 var_t0;
    s16 var_a1;

    var_t0 = 0;
    var_a1 = winData->unk64;
    while (winData[var_a1].unk64 != -1) {
        if (winData[var_a1].attr & HUWIN_ATTR_PAUSE) {
            var_t0 |= (u8)winData[var_a1].stat; // TODO: why required cast?
        }
        var_a1 = winData[var_a1].unk64;
    }

    if (GwSystem.playMode & 4) {
        var_t0 = 1;
    }
    return var_t0;
}

void func_800F159C_name_81(UnkBoard4 *arg0, s32 arg1) {
    void *data;
    s32 dataNum;
    GW_SYSTEM *system = &GwSystem;

    switch (arg1) {
        case 1:
            dataNum = D_801012AC_name_81[system->show_minigame_explanations];
            break;
        case 2:
            dataNum = D_801012B4_name_81[system->show_com_minigames];
            break;
        case 5:
            dataNum = D_801012BC_name_81[system->message_speed];
            break;
        case 4:
            dataNum = D_801012C8_name_81[system->walk_speed];
            break;
        case 6:
            dataNum = D_801012D4_name_81[system->save_mode];
            break;
        case 3:
            if (_CheckFlag(0x20) != 0) {
                dataNum = D_801012E4_name_81;
            } else {
                dataNum = D_801012E0_name_81;
            }
            break;
        default:
            return;
    }

    data = DataRead(dataNum);
    HuSprAnimKill(arg0->unk_0C[arg1]);
    arg0->unk_0C[arg1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(arg0->unk_0A, arg1, arg0->unk_0C[arg1], 0);
    HuSprPriSet(arg0->unk_0A, arg1, 8);
    HuSprAttrSet(arg0->unk_0A, arg1, 0x1000);
    HuSprPosSet(arg0->unk_0A, arg1,
                ((arg1 % 4) << 6) + 0x46,
                ((arg1 / 4) * 0x3C) + 0x3C);
    D_8010124A_name_81 = 1;
}

s32 func_800F1784_name_81(s32 arg0) {
    void *data;
    Process *mesProc;
    UnkBoard4 *icons;
    UnkBoard4 *cursor;
    s32 dataNum;
    s8 ret;
    s16 sel;
    s16 prevSel;
    s32 i;
    u8 sleepFlag;
    GW_SYSTEM *system;
    GW_COMMON *common = &GwCommon;
    s8 temp;

    ret = 4;
    sel = 0;
    prevSel = 0;
    mesProc = NULL;
    icons = NULL; // s4
    cursor = NULL;
    sleepFlag = 0;
    system = &GwSystem;

    if (!D_801053E6_name_81) {
        sel = D_80101248_name_81;
        prevSel = sel;
        icons = func_800F4528_name_81(8, 0);

        for (i = 0; i < 8; i++) {
            switch (i) {
                case 0:
                    if ((func_800F14A8_name_81()) != 0) {
                        dataNum = D_801012E8_name_81;
                    } else {
                        dataNum = D_8010128C_name_81[0];
                    }
                    break;
                case 1:
                    dataNum = D_801012AC_name_81[system->show_minigame_explanations];
                    break;
                case 2:
                    dataNum = D_801012B4_name_81[system->show_com_minigames];
                    break;
                case 5:
                    dataNum = D_801012BC_name_81[system->message_speed];
                    break;
                case 4:
                    dataNum = D_801012C8_name_81[system->walk_speed];
                    break;
                case 6:
                    dataNum = D_801012D4_name_81[system->save_mode];
                    break;
                case 3:
                    if (_CheckFlag(0x20) != 0) {
                        dataNum = D_801012E4_name_81;
                    } else {
                        dataNum = D_801012E0_name_81;
                    }
                    break;
                default:
                    dataNum = D_8010128C_name_81[i];
                    break;
            }

            data = DataRead(dataNum);
            icons->unk_0C[i] = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(icons->unk_0A, i, icons->unk_0C[i], 0);
            HuSprPriSet(icons->unk_0A, i, 8);
            HuSprAttrSet(icons->unk_0A, i, 0x1000);
            HuSprPosSet(icons->unk_0A, i,
                        ((i % 4) << 6) + 0x46,
                        ((i / 4) * 0x3C) + 0x3C);
        }

        if (D_801053E0_name_81 == NULL) {
            HuPrcVSleep();
            D_801053E0_name_81 = func_800E4B64_name_81(0, 8);
            HuVecCopyXYZ(&D_801053E0_name_81->obj->scale, 1.0f, 1.0f, 1.0f);
            HuWinTabWidthSet(D_801053E0_name_81->win_id, 0x2C);
            MBDModelTempAllocFree(D_801053E0_name_81->obj);
            Hu3DModelAttrSet(D_801053E0_name_81->obj->omObj1->model[0], HU3D_ATTR_NOPAUSE, HU3D_ATTR_NOPAUSE);
            D_801053E0_name_81->obj->flags |= 0x10;
            func_800E4EAC_name_81(D_801053E0_name_81, 0x104, 8);
            func_800F0D1C_name_81(D_801053E0_name_81, 0x69);
            HuWinExPriSet(D_801053E0_name_81->win_id, 5);
            HuWinExOpen(D_801053E0_name_81->win_id, 1);
        }

        cursor = func_800F4528_name_81(1, 0);
        data = DataRead(0x13009C);
        cursor->unk_0C[0] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(cursor->unk_0A, 0, cursor->unk_0C[0], 0);
        HuSprPriSet(cursor->unk_0A, 0, 7);
        HuSprAttrSet(cursor->unk_0A, 0, 0x1000);
        HuSprPosSet(cursor->unk_0A, 0,
                    ((D_80101248_name_81 % 4) * 64) + 0x2A,
                    ((D_80101248_name_81 / 4) * 60) + 0x20);

        mesProc = func_800F1340_name_81(D_8010126C_name_81, 1, -1);

    restart:
        while (1) {
            HuPrcVSleep();

            if (ContBtnRep[arg0] & L_JPAD) {
                sel--;
                if ((sel == 3) || (sel == -1)) {
                    sel += 4;
                }
            }
            if (ContBtnRep[arg0] & R_JPAD) {
                sel++;
                if ((sel == 4) || (sel == 8)) {
                    sel -= 4;
                }
            }
            if (ContBtnRep[arg0] & U_JPAD) {
                sel -= 4;
                if (sel < 0) {
                    sel += 8;
                }
            }
            if (ContBtnRep[arg0] & D_JPAD) {
                sel += 4;
                if (sel >= 8) {
                    sel -= 8;
                }
            }

            if (ContBtnDown[arg0] & A_BUTTON) {
                HuAudFXPlay(2);
                break;
            }
            if (ContBtnDown[arg0] & B_BUTTON) {
                HuAudFXPlay(4);
                sel = -1;
                break;
            }

            if (sel != -1) {
                D_80101248_name_81 = sel;
            }
            if (prevSel != sel) {
                prevSel = sel;
                HuAudFXPlay(1);
            }
            HuSprPosSet(cursor->unk_0A, 0,
                        ((D_80101248_name_81 % 4) * 64) + 0x2A,
                        ((D_80101248_name_81 / 4) * 0x3C) + 0x20);
        }

        switch (sel) {
            case 0:
                if ((func_800F14A8_name_81()) == 0) {
                    ret = 2;
                }
                break;
            case 1:
                system->show_minigame_explanations ^= 1;
                func_800F159C_name_81(icons, 1);
                break;
            case 2:
                system->show_com_minigames ^= 1;
                func_800F159C_name_81(icons, 2);
                break;
            case 5:
                temp = (system->message_speed + 1);
                system->message_speed = temp % 3;
                func_800F159C_name_81(icons, 5);
                break;
            case 4:
                temp = (system->walk_speed + 1);
                system->walk_speed = temp % 3;
                func_800F159C_name_81(icons, 4);
                break;
            case 6:
                temp = (system->save_mode + 1);
                system->save_mode = temp % 3;
                func_800F159C_name_81(icons, 6);
                break;
            case 3:
                if (_CheckFlag(0x20) != 0) {
                    _ClearFlag(0x20);
                } else {
                    _SetFlag(0x20);
                }
                func_800F159C_name_81(icons, 3);
                break;
            case 7:
                ret = 9;
                break;
            case -1:
                ret = 1;
                break;
        }

        common->unk9E = system->save_mode;
        common->unk9F = system->show_minigame_explanations;
        common->unkA0 = system->message_speed;
        common->unkA1 = system->walk_speed;
        common->unkA2 = system->show_com_minigames;
        func_800EBAD4_name_81(common->unkA0);
        if ((ret == 2) || (ret == 9)) {
            func_800F4584_name_81(icons);
            func_800F4584_name_81(cursor);
            icons = NULL;
            cursor = NULL;
        }
    } else {
        ret = 0;
    }

    switch (ret) {
        case 0:
        case 1:
            if (D_801053E0_name_81 != NULL) {
                HuWinExClose(D_801053E0_name_81->win_id, 1);
                func_800F0D1C_name_81(D_801053E0_name_81, 0x104);
                func_800E4E64_name_81(D_801053E0_name_81);
                D_801053E0_name_81 = NULL;
                if (icons != NULL) {
                    func_800F4584_name_81(icons);
                    func_800F4584_name_81(cursor);
                }
                sleepFlag = 1;
            }
            break;
        case 4:
            goto restart;
    }

    if (mesProc != NULL) {
        func_800F13C0_name_81(mesProc);
    }
    if (sleepFlag != 0) {
        HuPrcSleep(5);
    }
    return ret;
}

static s32 func_800F2090_name_81(s32 arg0) {
    Process *temp_s3;
    s16 temp_v0;
    s16 temp;

    temp_v0 = func_800F140C_name_81(func_800F0700_name_81(0x511E), 0x36);
    HuWinPriSet(temp_v0, 5);
    HuWinBGTPLvlSet(temp_v0, 0xFF);
    HuWinMesSet(temp_v0, func_800F0700_name_81(0x511E), -1, -1);
    HuWinMesSpeedSet(temp_v0, 0);

    while ((HuWinStatGet(temp_v0)) != 0) {
        HuPrcVSleep();
    }

    temp_s3 = func_800F1340_name_81(D_801012EC_name_81, 0, temp_v0);
    HuWinActivePlayerSet(temp_v0, 1 << arg0);
    temp = HuWinChoiceGet(temp_v0, 0, 0);
    if (temp == 1) {
        D_801053E6_name_81 = 1;
    }
    func_800F13C0_name_81(temp_s3);
    HuWinKill(temp_v0);
    return 4;
}

s32 func_800F21CC_name_81(s16 arg0) {
    s32 i;
    s16 chr = arg0;

    for (i = 0; i < 4; i++) {
        GW_PLAYER *player = MBDGetPlayerStruct(i);
        if (player->stat & PLAYER_IS_CPU) {
            continue;
        }
        if (player->pad == chr) {
            return 1;
        }
    }
    return 0;
}

void func_800F2238_name_81(GW_PLAYER *arg0, s16 arg1) {
    GW_PLAYER *player;
    s32 i;
    u8 pad;

    pad = arg0->pad;
    if (arg1 < 4) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            player = MBDGetPlayerStruct(i);
            if (player->pad != arg1) {
                continue;
            }
            player->pad = pad;
            arg0->pad = arg1;
            arg0->stat &= ~1;
            return;
        }
    } else {
        arg0->stat |= 1;
    }
}

s32 func_800F22E8_name_81(GW_PLAYER *arg0, s16 arg1) {
    s32 count;
    u32 port;

    if (func_800F37B8_name_81(arg0->turn) != 0) {
        count = 4;
        if (arg1 > 0) {
            port = 0;
        } else {
            port = 3;
        }
        for (; count != 0; count--) {
            if ((func_800F21CC_name_81(port) == 0) && (CheckControllerRead(port) != 0)) {
                return port;
            }
            port += arg1;
        }
        return 4;
    }

    if (arg1 > 0) {
        port = arg0->pad + 1;
    } else {
        port = arg0->pad - 1;
    }

    for (; port < 4; port += arg1) {
        if ((func_800F21CC_name_81(port) == 0)) {
            if (CheckControllerRead(port) != 0) {
                return port;
            }
        }
    }
    return 4;
}

void func_800F23FC_name_81(s16 arg0) {
    D_801053F4_name_81 = arg0;
}

void func_800F2408_name_81(UnkBoard4 *arg0, s16 arg1) {
    HuSprPosSet(arg0->unk_0A, 0, (D_80101348_name_81[arg1] - 50), (D_8010134C_name_81[arg1] - 8));
    HuSprPosSet(arg0->unk_0A, 1, (D_80101348_name_81[arg1] + 50), (D_8010134C_name_81[arg1] + 4));
    HuSprPosSet(arg0->unk_0A, 2, (D_80101348_name_81[arg1] - 50), (D_8010134C_name_81[arg1] + 4));
}

void func_800F24DC_name_81(void) {
    f32 var_f20;
    s32 var_v0;
    UnkBoard4 *temp_s1;

    temp_s1 = HuPrcCurrentGet()->user_data;
    var_f20 = 0.0f;
    while (1) {
        HuPrcVSleep();
        if (D_801053F4_name_81 != 0) {
            var_v0 = (s16)(sindf(var_f20) * 255.0f); // TODO: s16 cast
            if (var_v0 < 0) {
                var_v0 = -var_v0;
            }
            var_f20 += 6.0f;
            if (var_f20 > 360.0f) {
                var_f20 -= 360.0f;
            }
            HuSprColorSet(temp_s1->unk_0A, 1, 0xFFU, var_v0, 0U);
            HuSprColorSet(temp_s1->unk_0A, 2, 0xFFU, var_v0, 0U);
            HuSprDispOn(temp_s1->unk_0A, 1);
            HuSprDispOn(temp_s1->unk_0A, 2);
        } else {
            var_f20 = 0.0f;
            HuSprDispOff(temp_s1->unk_0A, 1);
            HuSprDispOff(temp_s1->unk_0A, 2);
        }
    }
}

s32 func_800F2618_name_81(s32 arg0) {
    s16 sel;
    UnkBoard4 *panel;
    UnkBoard4 *chr;
    UnkBoard4 *icon;
    UnkBoard4 *cursor;
    UnkBoard4 *bg;
    Process *proc;
    GW_PLAYER *player;
    void *data;
    s32 mess;
    s16 dir;
    s32 i;
    s32 diff;

    mess = 0;
    sel = 0;
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if ((func_800F37B8_name_81(i) == 0) && (GwPlayer[i].pad == arg0)) {
            sel = i;
            break;
        }
    }

    bg = func_800F4528_name_81(1, 0);
    data = DataRead(0x1300AA);
    bg->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(bg->unk_0A, 0, bg->unk_0C[0], 0);
    HuSprPriSet(bg->unk_0A, 0, 8);
    HuSprAttrSet(bg->unk_0A, 0, 0x1000);
    HuSprPosSet(bg->unk_0A, 0, 0xA0, (D_8010134C_name_81[0] + D_8010134C_name_81[1]) / 2);

    panel = func_800F4528_name_81(4, 0);
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (i == 0) {
            data = DataRead(0x1300A7);
            panel->unk_0C[2] = HuSprAnimRead(data);
            DataClose(data);
        }
        HuSprGrpMemberSet(panel->unk_0A, i + 2, panel->unk_0C[2], 0);
        HuSprPriSet(panel->unk_0A, i + 2, 8);
        HuSprAttrSet(panel->unk_0A, i + 2, 0x1000);
        HuSprPosSet(panel->unk_0A, i + 2, D_80101348_name_81[i], D_8010134C_name_81[i]);
    }

    chr = func_800F4528_name_81(2, 0);
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        data = DataRead(D_801012F4_name_81[MBDGetPlayerStruct(i)->chr]);
        chr->unk_0C[i] = HuSprAnimRead(data);
        HuSprGrpMemberSet(chr->unk_0A, i, chr->unk_0C[i], 0);
        HuSprPriSet(chr->unk_0A, i, 7);
        HuSprAttrSet(chr->unk_0A, i, 0x1000);
        HuSprPosSet(chr->unk_0A, i, D_80101348_name_81[i] - 20, D_8010134C_name_81[i] + 4);
        DataClose(data);
        if (i != 0) {
            HuSprAttrSet(chr->unk_0A, i, 1);
        }
    }

    icon = func_800F4528_name_81(9, 0);
    for (i = 0; i < 9; i++) {
        data = DataRead(D_80101314_name_81[i]);
        icon->unk_0C[i] = HuSprAnimRead(data);
        DataClose(data);
    }
    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        if (func_800F37B8_name_81(i) != 0) {
            HuSprGrpMemberSet(icon->unk_0A, i,
                              icon->unk_0C[D_80101340_name_81[GwPlayer[i].cpu_difficulty * 2 + 0]], 0);
            HuSprGrpMemberSet(icon->unk_0A, i + 2,
                              icon->unk_0C[D_80101340_name_81[GwPlayer[i].cpu_difficulty * 2 + 1]], 0);
            HuSprPosSet(icon->unk_0A, i,
                        D_80101348_name_81[i] + 16,
                        D_8010134C_name_81[i] - 6);
        } else {
            HuSprGrpMemberSet(icon->unk_0A, i,
                              icon->unk_0C[D_80101338_name_81[GwPlayer[i].pad * 2]], 0);
            HuSprGrpMemberSet(icon->unk_0A, i + 2,
                              icon->unk_0C[D_80101338_name_81[GwPlayer[i].pad * 2]], 0);
            HuSprPosSet(icon->unk_0A, i,
                        D_80101348_name_81[i] + 16,
                        D_8010134C_name_81[i] + 2);
            HuSprDispOff(icon->unk_0A, i + 2);
        }
        HuSprPriSet(icon->unk_0A, i, 7);
        HuSprAttrSet(icon->unk_0A, i, 0x01001000);
        HuSprPriSet(icon->unk_0A, i + 2, 7);
        HuSprAttrSet(icon->unk_0A, i + 2, 0x01001000);
        HuSprPosSet(icon->unk_0A, i + 2,
                    D_80101348_name_81[i] + 16,
                    D_8010134C_name_81[i] + 10);
    }

    cursor = func_800F4528_name_81(3, 0);
    data = DataRead(0x13009C);
    cursor->unk_0C[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(cursor->unk_0A, 0, cursor->unk_0C[0], 0);
    HuSprAttrSet(cursor->unk_0A, 0, 0x1808);
    HuSprPriSet(cursor->unk_0A, 0, 8);
    DataClose(data);

    data = DataRead(0x1300A9);
    cursor->unk_0C[1] = HuSprAnimRead(data);
    HuSprGrpMemberSet(cursor->unk_0A, 1, cursor->unk_0C[1], 0);
    HuSprAttrSet(cursor->unk_0A, 1, 0x9808);
    HuSprPriSet(cursor->unk_0A, 1, 8);
    HuSprColorSet(cursor->unk_0A, 1, 0xFF, 0, 0);
    HuSprAttrSet(cursor->unk_0A, 1, 1);
    DataClose(data);

    data = DataRead(0x1300A9);
    cursor->unk_0C[2] = HuSprAnimRead(data);
    HuSprGrpMemberSet(cursor->unk_0A, 2, cursor->unk_0C[2], 0);
    HuSprAttrSet(cursor->unk_0A, 2, 0x9808);
    HuSprPriSet(cursor->unk_0A, 2, 8);
    HuSprColorSet(cursor->unk_0A, 2, 0xFF, 0, 0);
    DataClose(data);

    func_800F2408_name_81(cursor, sel);
    func_800F23FC_name_81(0);
    proc = omAddPrcObj(func_800F24DC_name_81, 0x1005, 0, 0);
    proc->user_data = cursor;

    do {
        if (mess != 0x5112) {
            mess = 0x5112;
            func_800F0DF8_name_81(D_801053E0_name_81->win_id, 0x5112);
        }
        HuPrcVSleep();

        dir = -1;
        if (ContBtnDown[arg0] & U_JPAD)
            dir = 0;
        if (ContBtnDown[arg0] & D_JPAD)
            dir = 1;
        if (ContBtnDown[arg0] & L_JPAD)
            dir = 2;
        if (ContBtnDown[arg0] & R_JPAD)
            dir = 3;

        if (dir != -1) {
            sel += D_80101350_name_81[sel][dir];
            func_800F2408_name_81(cursor, sel);
            HuAudFXPlay(1);
        } else if (HuPadBtnDown[arg0] & A_BUTTON) {
            HuAudFXPlay(2);
            player = MBDGetPlayerStruct(sel);
            func_800F23FC_name_81(1);
            diff = player->cpu_difficulty;
            i = (func_800F37B8_name_81(sel) != 0) ? 4 : -1;

            while (1) {
                HuPrcVSleep();
                if (mess != 0x5113) {
                    mess = 0x5113;
                    func_800F0DF8_name_81(D_801053E0_name_81->win_id, 0x5113);
                }

                if (ContBtnDown[arg0] & L_JPAD) {
                    if ((i != 4) || (diff == 0)) {
                        i = func_800F22E8_name_81(player, -1);
                        if (i == 4) {
                            diff = _CheckFlag(0x2D) ? 3 : 2;
                        }
                    } else {
                        diff--;
                    }
                    func_800F3B54_name_81(sel, diff);
                    HuAudFXPlay(1);
                } else if (ContBtnDown[arg0] & R_JPAD) {
                    if (_CheckFlag(0x2D) != 0) {
                        if ((i != 4) || (diff == 3)) {
                            i = func_800F22E8_name_81(player, 1);
                            diff = -(i != 4) & diff;
                        } else {
                            diff++;
                        }

                    } else if ((i != 4) || (diff == 2)) {
                        i = func_800F22E8_name_81(player, 1);
                        diff = -(i != 4) & diff;
                    } else {
                        diff++;
                    }
                    func_800F3B54_name_81(sel, diff);
                    HuAudFXPlay(1);
                }

                if (i >= 0) {
                    func_800F2238_name_81(player, i);
                    if (func_800F37B8_name_81(sel) != 0) {
                        HuSprGrpMemberSet(icon->unk_0A, sel,
                                          icon->unk_0C[D_80101340_name_81[GwPlayer[sel].cpu_difficulty * 2 + 0]], 0);
                        HuSprGrpMemberSet(icon->unk_0A, sel + 2,
                                          icon->unk_0C[D_80101340_name_81[GwPlayer[sel].cpu_difficulty * 2 + 1]], 0);
                        HuSprPosSet(icon->unk_0A, sel,
                                    D_80101348_name_81[sel] + 16,
                                    D_8010134C_name_81[sel] - 6);
                        HuSprDispOn(icon->unk_0A, sel + 2);
                    } else {
                        HuSprGrpMemberSet(icon->unk_0A, sel,
                                          icon->unk_0C[D_80101338_name_81[GwPlayer[sel].pad * 2]], 0);
                        HuSprPosSet(icon->unk_0A, sel,
                                    D_80101348_name_81[sel] + 16,
                                    D_8010134C_name_81[sel] + 2);
                        HuSprDispOff(icon->unk_0A, sel + 2);
                    }
                }

                if (ContBtnDown[arg0] & A_BUTTON) {
                    HuAudFXPlay(2);
                    func_800F3B54_name_81(sel, diff);
                    break;
                }
                if (ContBtnDown[arg0] & B_BUTTON) {
                    HuAudFXPlay(4);
                    break;
                }
            }

            func_800F23FC_name_81(0);
            HuPrcVSleep();
        }
    } while (!(HuPadBtnDown[arg0] & B_BUTTON));

    HuAudFXPlay(4);
    omDelPrcObj(proc);
    func_800F4584_name_81(cursor);
    func_800F4584_name_81(icon);
    func_800F4584_name_81(chr);
    func_800F4584_name_81(panel);
    func_800F4584_name_81(bg);
    return 4;
}

static s16 func_800F32CC_name_81(s16 arg0, s32 arg1) {
    switch (arg0) {
        case 1:
            return func_800F0C4C_name_81(arg1);
        case 2:
            return func_800F2618_name_81(arg1);
        case 4:
            return func_800F1784_name_81(arg1);
        case 9:
            return func_800F2090_name_81(arg1);
        default:
            return 0;
    }
}

static void func_800F336C_name_81(void) {
    UnkBoard4 *temp_s1;
    s16 var_s2;
    s16 temp_v0;
    s32 temp_s3;
    void *temp_v0_2;

    temp_s3 = (s32)HuPrcCurrentGet()->user_data;
    var_s2 = 1;
    temp_v0 = func_800F73AC_name_81();

    if (temp_v0 != 0) {
        func_800F73C0_name_81();
    }

    HuPrcVSleep();
    Hu3DPauseF = 1;
    temp_s1 = func_800F4528_name_81(1, 0);
    temp_v0_2 = DataRead(0x13025D);
    temp_s1->unk_0C[0] = HuSprAnimRead(temp_v0_2);
    HuSprGrpMemberSet(temp_s1->unk_0A, 0, temp_s1->unk_0C[0], 0U);
    HuSprPriSet(temp_s1->unk_0A, 0, 9U);
    HuSprAttrSet(temp_s1->unk_0A, 0, 0x1000);
    HuSprPosSet(temp_s1->unk_0A, 0, 0xA0, 0x78);
    HuSprScaleSet(temp_s1->unk_0A, 0, 40.0f, 30.0f);
    HuSprColorTPLvlSet(temp_s1->unk_0A, 0, 0, 0, 0, 0xC0);
    DataClose(temp_v0_2);

    do {
        HuPrcVSleep();
        var_s2 = func_800F32CC_name_81(var_s2, temp_s3);
    } while (var_s2 != 0);

    if (D_801053E6_name_81 == 0) {
        Hu3DPauseF = 0;
    }

    func_800F4584_name_81(temp_s1);

    if (temp_v0 != 0) {
        func_800F740C_name_81();
    }

    omDelPrcObj(NULL);
}

void func_800F3500_name_81(s32 arg0) {
    Process *temp_s1_2;
    Process *temp_v0;
    s32 temp_s2;
    s32 i;

    func_800E9190_name_81();
    winPauseF = 1;
    omAllPause();
    temp_s2 = _CheckFlag(0x20) != 0;

    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i) != 0) {
            ResetVibrator(i);
        }
    }

    HuAudSeqVolSet(0x60);
    if (mbSubMusNo != -1) {
        msmMusSetVolume(mbSubMusNo, 0x60);
    }

    Hu3DModelModeSet(HuSprBGHookMdl, 2);
    Hu3DModelCameraSet(HuSprBGHookMdl, HU3D_CAM0);
    D_801053E0_name_81 = NULL;
    D_801053E4_name_81 = 0;
    D_801053E6_name_81 = 0;
    temp_s1_2 = HuPrcCurrentGet();
    temp_v0 = omAddPrcObj(func_800F336C_name_81, 0xEFFFU, 0x1000, 0);
    temp_v0->user_data = (void *)arg0;
    omPrcSetStatBit(temp_v0, OM_STAT_NOALLPAUSE);
    HuPrcChildLink(temp_s1_2, temp_v0);
    HuPrcChildWatch();
    Hu3DModelModeSet(HuSprBGHookMdl, 6);
    HuAudSeqVolSet(0x7F);
    if (mbSubMusNo != -1) {
        msmMusSetVolume(mbSubMusNo, 0x7F);
    }
    if (((_CheckFlag(0x20) != 0) && (temp_s2 == 0)) || ((_CheckFlag(0x20) == 0) && (temp_s2 != 0))) {
        func_800DF154_name_81();
    }
    if (D_801053E6_name_81 != 0) {
        omOvlSeKeepF = 0;
        HuAudSeqFadeOut(0x5A);
        if (mbSubMusNo != -1) {
            msmMusFadeOut(mbSubMusNo, 0x5A);
            mbSubMusNo = -1;
            HuAudSeqStop();
        }
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x11);
        func_800FC4E4_name_81();
        func_800FC108_name_81();
        if (GwSystem.playMode & 4) {
            omOvlReturnEx(3);
        } else {
            omOvlReturnEx(1);
        }

        omOvlKill();
        HuPrcVSleep();
    }
    omAllUPause();
    winPauseF = 0;
    func_800E9180_name_81();
}

s16 MBDGetCurrentPlayerIndex(void) {
    return GwSystem.current_player_index;
}

GW_PLAYER *MBDGetPlayerStruct(s32 player) {
    if (player < 0) {
        player = MBDGetCurrentPlayerIndex();
    }
    return &GwPlayer[player];
}

s32 func_800F379C_name_81(s16 playerIndex) {
    if (playerIndex == GwSystem.current_player_index) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 func_800F37B8_name_81(s16 playerIndex) {
    return MBDGetPlayerStruct(playerIndex)->stat & PLAYER_IS_CPU;
}

void func_800F37E0_name_81(s32 playerIndex, s32 amount) {
    GW_PLAYER *player;

    player = MBDGetPlayerStruct(playerIndex);
    player->coin = player->coin + amount;
    if (player->coin > 999) {
        player->coin = 999;
    }
    if (player->coin < 0) {
        player->coin = 0;
    }
    if (player->coinPrize <= player->coin) {
        player->coinPrize = player->coin;
    }
}

s32 func_800F3850_name_81(s32 playerIndex, s32 requiredCoins) {
    if (MBDGetPlayerStruct(playerIndex)->coin >= requiredCoins) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void func_800F3880_name_81(s32 playerIndex, s16 arg1, u16 arg2) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);

    if (player == MBDGetPlayerStruct(CUR_PLAYER)) {
        MBDMotionSet(player->player_obj, arg1, arg2);
    }
}

void func_800F38DC_name_81(s32 playerIndex, s16 arg1, u16 arg2) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);

    if (player == MBDGetPlayerStruct(CUR_PLAYER)) {
        MBDMotionSet(player->player_obj, arg1, arg2);
        if (arg1 < 4) {
            func_800F89D0_name_81(playerIndex, PARTNER_FRONT, arg1, arg2);
            func_800F89D0_name_81(playerIndex, PARTNER_BACK, arg1, arg2);
        }
    }
}

void func_800F397C_name_81(s32 playerIndex, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);

    if (player == MBDGetPlayerStruct(CUR_PLAYER)) {
        MBDMotionShiftSet(player->player_obj, arg1, arg2, arg3, arg4);
    }
}

void func_800F3A04_name_81(s32 playerIndex, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);

    if (player == MBDGetPlayerStruct(CUR_PLAYER)) {
        MBDMotionShiftSet(player->player_obj, arg1, arg2, arg3, arg4);
        if (arg1 < 4) {
            func_800F8AEC_name_81(playerIndex, PARTNER_FRONT, arg1, arg2, arg3, arg4);
            func_800F8AEC_name_81(playerIndex, PARTNER_BACK, arg1, arg2, arg3, arg4);
        }
    }
}

void func_800F3AF4_name_81(s32 playerIndex, f32 arg1) {
    Hu3DMotionSpeedSet(MBDGetPlayerStruct(playerIndex)->player_obj->omObj1->model[0], arg1);
    func_800F8CD8_name_81(playerIndex, arg1);
}

void func_800F3B54_name_81(s32 playerIndex, u8 cpuDifficulty) {
    MBDGetPlayerStruct(playerIndex)->cpu_difficulty = D_80101370_name_81[cpuDifficulty];
}

void func_800F3B8C_name_81(void) {
}

void func_800F3B94_name_81(s32 playerIndex, Vec *scale) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);

    HuVecCopy3F(&player->player_obj->scale, scale);
    if (player->stats.partners.frontID != PARTNER_NONE) {
        HuVecCopy3F(&MBDGetPlayerPartnerRef(playerIndex, PARTNER_FRONT)->scale, scale);
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        HuVecCopy3F(&MBDGetPlayerPartnerRef(playerIndex, PARTNER_BACK)->scale, scale);
    }
}

void func_800F3C28_name_81(void) {
    GW_PLAYER *player = HuPrcCurrentGet()->user_data;

    while (1) {
        HuPrcVSleep();
        if (player->stat & PLAYER_UNK_04) {
            continue;
        }
        HuVecCopyXYZ(&player->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
}

void func_800F3C98_name_81(s16 playerIndex, s32 *arg1, s32 arg2) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);
    Process *proc;
    u8 chr;

    player->turn = playerIndex;
    chr = player->chr;

    switch (arg2) {
        case 0:
            player->player_obj = func_800D8010_name_81(D_801014B4_name_81[chr], arg1);
            break;
        case 1:
        case 2:
            player->player_obj = func_800D8010_name_81(D_801014BC_name_81[chr], arg1);
            break;
    }

    proc = omAddPrcObj(func_800F3C28_name_81, 0x5000, 0, 0);
    player->unk_20 = proc;
    proc->user_data = player;
}

void func_800F3D50_name_81(s16 playerIndex, s32 *arg1) {
    func_800F3C98_name_81(playerIndex, arg1, 0);
}

void func_800F3D74_name_81(s16 playerIndex) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);

    func_800F3C98_name_81(playerIndex, D_80101494_name_81[player->chr], 0);
}

void func_800F3DC0_name_81(s16 playerIndex) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex); // unused, like the ovl_80 counterpart

    func_800F3C98_name_81(playerIndex, NULL, 0);
}

void func_800F3DFC_name_81(s16 playerIndex) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);

    func_800F3C98_name_81(playerIndex, D_80101494_name_81[player->chr], 0);
    func_800F8108_name_81(playerIndex);
    func_800ED214_name_81(playerIndex);
}

u8 func_800F3E58_name_81(s16 playerIndex) {
    return D_801014BC_name_81[MBDGetPlayerStruct(playerIndex)->chr];
}

void func_800F3E88_name_81(s16 playerIndex, u8 arg1) {
    func_800D898C_name_81(MBDGetPlayerStruct(playerIndex)->player_obj, arg1);
}

void func_800F3EC0_name_81(s16 playerIndex) {
    GW_PLAYER *player = MBDGetPlayerStruct(playerIndex);

    if (player->player_obj != NULL) {
        if (player->unk_20 != NULL) {
            omDelPrcObj(player->unk_20);
        }
        MBDModelKill(player->player_obj);
        player->player_obj = NULL;
    }
}

void func_800F3F18_name_81(s16 playerIndex) {
    func_800F3EC0_name_81(playerIndex);
    func_800F82EC_name_81(playerIndex);
}

void func_800F3F4C_name_81(void) {
    s32 i, j;

    for (j = 0; j < 3; j++) {
        MBDGetPlayerStruct(j)->player_obj = NULL;
    }
    MBDPartnerObjClear();

    for (i = 1; i < 8; i++) {
        for (j = 0; j < D_80101374_name_81[0]; j++) {
            D_80101494_name_81[i][j + 1] = CharMotionDataNumGet(i, D_80101374_name_81[j + 1]);
        }
    }
}

void func_800F4030_name_81(void) {
    s32 i;

    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
        func_800F3EC0_name_81(i);
    }
    func_800F7FDC_name_81();
}
