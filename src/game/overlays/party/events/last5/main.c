#include "common_board.h"
#include "game/overlays/party/common/back.h"
#include "game/overlays/party/common/model.h"
#include "game/overlays/party/common/player.h"
#include "game/overlays/party/common/pause.h"
#include "game/overlays/party/common/status.h"
#include "game/overlays/party/common/sprgrp.h"
#include "game/overlays/party/common/move.h"
#include "game/overlays/party/common/vibrate.h"

static Vec last5_hostPos = { 750.0f, 0.0f, 2250.0f };
static Vec last5_hostWalkPos = { 150.0f, 0.0f, 1750.0f };
static Vec last5_starPosTbl[2] = {
    { 150.0f, 0.0f, 2000.0f },
    { 150.0f, 0.0f, 2000.0f }
};
static Vec last5_npcPos = { 0.0f, 0.0f, 2250.0f };
static u32 last5_kinopioMot[] = { 0x00000001, 0x000A0019 };
static u32 last5_koopaJrMot[] = { 0x00000001, 0x000A00FB };
static u32 last5_whompMot[] = { 0x00000001, 0x000A00D0 };
static u32 last5_koopaMot[] = { 0x00000002, 0x000A0035, 0x000A0042 };
static u32 last5_starMot[] = { 0x00000001, 0x000A0125 };
static u8 last5_starRankChanceTbl[] = { 0x05, 0x0F, 0x32, 0x64 };
static u8 last5_koopaRankChanceTbl[] = { 0x32, 0x55, 0x5F, 0x64 };
static s32 last5_statusPosYTbl[] = { 0x00000011, 0x00000049, 0x00000081, 0x000000B9 };
static u32 last5_kinopioFaceAnimA = 0x000A002A;
static u32 last5_kinopioFaceAnimB = 0x000A002B;

static u8 last5_boardNo;
static s32 last5_playerRankTbl[4];
static s32 last5_rankPlayerTbl[4];
static UnkBoard8 *last5_titleSprGrp;
static Object *last5_starMdl;

void MBDlgWinExecAllKey(s16 arg0, s32 arg1);
void last5_StatusSlideProc(void);
void last5_MainProc(void);
void last5_ExitCheckObjMain(omObjData *);
void last5_SysInit(void);
void last5_SysClose(void);
void last5_BackInit(void);
void last5_BackClose(void);

void last5_ObjectSetup(void) {
    s32 i;

    last5_boardNo = GwSystem.current_board_index;
    omInitObjMan(0x32, 0x32);
    last5_BackInit();
    last5_SysInit();
    MBShadowHeightMaxSet(1000.0f);
    HuWinInit();
    MBStatusCreate();
    MBStatusItemDispOff();
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBStatusPosSet(i, 0x1E, -0x32);
    }
    omAddPrcObj(last5_MainProc, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, last5_ExitCheckObjMain);
}

s16 last5_WinCreate(s16 *arg0, s16 arg1, s16 arg2) {
    return HuWinExCreate(-1, arg1, arg2, arg0[0], arg0[1], 0);
}

void last5_WinKeyWait(s16 arg0) {
    winData[arg0].stat = HUWIN_STAT_DRAWMES;
    HuPrcVSleep();
    MBWinComKeyAllWaitKeep(arg0);
}

s16 last5_WinMesOpen(s32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, s16 arg6, s16 arg7) {
    s16 sp10[2];
    s16 window;

    if (arg1 != 0) {
        HuWinInsertMesSizeGet(arg1, 0);
    }
    if (arg2 != 0) {
        HuWinInsertMesSizeGet(arg2, 1);
    }
    if (arg3 != 0) {
        HuWinInsertMesSizeGet(arg3, 2);
    }
    if (arg4 != 0) {
        HuWinInsertMesSizeGet(arg4, 3);
    }
    if (arg5 != 0) {
        HuWinInsertMesSizeGet(arg5, 4);
    }

    HuWinMesMaxSizeGet(1, sp10, arg0);
    window = last5_WinCreate(sp10, arg6, arg7);

    if (arg1 != 0) {
        HuWinInsertMesSet(window, arg1, 0);
    }
    if (arg2 != 0) {
        HuWinInsertMesSet(window, arg2, 1);
    }
    if (arg3 != 0) {
        HuWinInsertMesSet(window, arg3, 2);
    }
    if (arg4 != 0) {
        HuWinInsertMesSet(window, arg4, 3);
    }
    if (arg5 != 0) {
        HuWinInsertMesSet(window, arg5, 4);
    }

    HuWinMesSet(window, arg0, -1, -1);
    HuWinExAnimIn(window);
    MBWinComKeyAllWaitKeep(window);
    return window;
}

void last5_WinClose(s16 arg0) {
    HuWinExAnimOut(arg0, 0);
    HuWinKill(arg0);
}

void last5_TitleObjMain(omObjData *arg0) {
    f32 scale;

    arg0->work[0]++;
    arg0->rot.x += 30.0f;
    scale = sindf(arg0->rot.x) + 1.0f;
    arg0->scale.x = scale;
    HuSprScaleSet(last5_titleSprGrp->spriteGroup, 1, scale, scale);
    if (arg0->rot.x >= 360.0f) {
        arg0->rot.x -= 360.0f;
    }
    if (arg0->work[0] >= 0x15) {
        HuSprTPLvlSet(last5_titleSprGrp->spriteGroup, 0, (0x1F - arg0->work[0]) * 25);
        HuSprTPLvlSet(last5_titleSprGrp->spriteGroup, 1, (0x1F - arg0->work[0]) * 25);
    }
}

void last5_TitleExec(void) {
    void *data;
    omObjData *obj;

    last5_titleSprGrp = MBSprGrpCreate(2, 0);
    data = DataRead(0x1301DE);
    last5_titleSprGrp->model[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(last5_titleSprGrp->spriteGroup, 0, last5_titleSprGrp->model[0], 0);
    HuSprPriSet(last5_titleSprGrp->spriteGroup, 0, 0x11);
    HuSprAttrSet(last5_titleSprGrp->spriteGroup, 0, 0x1000);
    HuSprPosSet(last5_titleSprGrp->spriteGroup, 0, 0xA0, 0x64);
    data = DataRead(0x1301DF);
    last5_titleSprGrp->model[1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(last5_titleSprGrp->spriteGroup, 1, last5_titleSprGrp->model[1], 3);
    HuSprPriSet(last5_titleSprGrp->spriteGroup, 1, 0x10);
    HuSprAttrSet(last5_titleSprGrp->spriteGroup, 1, 0x1000);
    HuSprPosSet(last5_titleSprGrp->spriteGroup, 1, 0xA0, 0x64);
    obj = omAddObj(0x1000, 0, 0, -1, last5_TitleObjMain);
    HuPrcSleep(0x1E);
    omDelObj(obj);
    MBSprGrpKill(last5_titleSprGrp);
    HuPrcSleep(0xA);
}

void last5_StatusSlideProc(void) {
    Process *proc;
    s32 player;
    s32 i;

    proc = HuPrcCurrentGet();
    player = *(s32 *)proc->user_data;
    for (i = 0; i < 0x6E; i += 5) {
        MBStatusPosSet(last5_rankPlayerTbl[player], 0x1E,
                       sindf(i) * 250.0f - (0xF1 - last5_statusPosYTbl[player]));
        HuPrcVSleep();
    }
    MBStatusPosSet(last5_rankPlayerTbl[player], 0x1E, last5_statusPosYTbl[player]);
    omDelPrcObj(0);
}

Process *last5_StatusSlideCreate(s32 arg0) {
    Process *proc;
    s32 *work;

    proc = omAddPrcObj(last5_StatusSlideProc, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(proc->heap, 0x10);
    proc->user_data = work;
    *work = arg0;
    return proc;
}

void last5_KoopaExec(void) {
    Object *model;
    Object *coinModel;
    Vec forward;
    s16 window;
    s32 winner;
    s32 i;
    s32 value;
    s32 step;

    model = MBModelFileCreate(0xA002F, 9, 0.7f, 1.4f, last5_koopaMot);
    HuVecCopy3F(&model->coords, &last5_hostPos);
    MBVecDirGet(&model->coords, &last5_hostWalkPos, &model->rot);
    HuVecCopyXYZ(&model->scale, 2.0f, 2.0f, 2.0f);
    coinModel = MBModelCreate(0x39, last5_koopaJrMot);
    HuVecCopy3F(&coinModel->coords, &last5_npcPos);
    HuAudSeqPlay(0x13);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(WIPE_STARS, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    last5_TitleExec();
    HuAudFXPlay(0x2A0);
    MBDlgWinExecAllKey(-1, 0x430A);
    for (value = 0; value < 4; value++) {
        HuPrcChildLink(HuPrcCurrentGet(), last5_StatusSlideCreate(value));
        {
            s32 rankMes[] = { 0x430B, 0x430C, 0x430D, 0x430E };
            window = last5_WinMesOpen(rankMes[MBPlayerRankCalc(last5_rankPlayerTbl[value])],
                                         mbCharNameMesTbl[GwPlayer[last5_rankPlayerTbl[value]].chr],
                                         0, 0, 0, 0, 0x8C, 0x6E);
            last5_WinClose(window);
        }
        HuPrcChildWatch();
    }
    MBDlgWinExecAllKey(-1, 0x430F);
    MBMotionSet(model, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&model->coords, &last5_hostWalkPos, &model->coords, 0x3C));
    HuPrcChildWatch();
    MBVecForwardSet(&forward);
    HuPrcChildLink(HuPrcCurrentGet(), MBVecRotLerpCreate(&model->rot, &forward, &model->rot, 0xA));
    HuPrcChildWatch();
    MBMotionShiftSet(model, -1, 0, 5, 2);
    winner = 0;
    value = MBRand(100.0f);
    for (step = 0; step < 4; step++) {
        if (value < last5_koopaRankChanceTbl[step]) {
            winner = step;
            break;
        }
    }
    HuAudFXPlay(0x29D);
    window = last5_WinMesOpen(0x4310, mbCharNameMesTbl[GwPlayer[last5_rankPlayerTbl[winner]].chr],
                                 0, 0, 0, 0, 0xA0, 0x50);
    last5_WinKeyWait(window);
    last5_WinClose(window);
    value = 0x1E;
    step = 0xA;
    while (value >= -0xA0) {
        for (i = 0; i < 4; i++) {
            if (winner != i) {
                MBStatusPosSet(last5_rankPlayerTbl[i], value, last5_statusPosYTbl[i]);
            }
        }
        value -= step;
        step += 2;
        HuPrcVSleep();
    }
    value = last5_statusPosYTbl[winner];
    while (last5_statusPosYTbl[0] < value) {
        MBStatusPosSet(last5_rankPlayerTbl[winner], 0x1E, value);
        HuPrcVSleep();
        value -= 0xA;
    }
    MBStatusPosSet(last5_rankPlayerTbl[winner], 0x1E, last5_statusPosYTbl[0]);
    MBPlayerVibrate(last5_rankPlayerTbl[winner], 2);
    window = last5_WinMesOpen(0x4311, mbCharNameMesTbl[GwPlayer[last5_rankPlayerTbl[winner]].chr],
                                 0, 0, 0, 0, 0x50, 0x64);
    last5_WinClose(window);
    MBCoinTakeCreate(last5_rankPlayerTbl[winner], -0xA);
    HuPrcSleep(0x1E);
    MBMotionSet(model, 1, 2);
    MBVecDirGet(&model->coords, &last5_hostPos, &model->rot);
    value = 0x1E;
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&model->coords, &last5_hostPos, &model->coords, 0x1E));
    step = 0xA;
    while (value >= -0xA0) {
        MBStatusPosSet(last5_rankPlayerTbl[winner], value, last5_statusPosYTbl[0]);
        value -= step;
        step += 2;
        HuPrcVSleep();
    }
    HuPrcChildWatch();
    MBDlgWinExecAllKey(-1, 0x4312);
    MBMotionShiftSet(coinModel, 0, 0, 5, 2);
    HuPrcSleep(0x14);
}

void last5_StarHoverObjMain(omObjData *arg0) {
    last5_starMdl->velocity.x = sindf(arg0->rot.x) * 20.0f + arg0->rot.y;
    arg0->rot.x += 5.0f;
    if (arg0->rot.x >= 360.0f) {
        arg0->rot.x -= 360.0f;
    }
}

void last5_StarExec(void) {
    Object *model;
    Object *faceModel;
    Vec forward;
    s16 window;
    s16 light;
    s32 flag = 0;
    omObjData *obj = NULL;
    s32 winner;
    s32 i;
    s32 j;
    s32 value;
    s32 step;

    model = MBModelCreate(0xB, last5_whompMot);
    HuVecCopy3F(&model->coords, &last5_hostPos);
    MBVecDirGet(&model->coords, &last5_hostWalkPos, &model->rot);
    HuVecCopyXYZ(&model->scale, 1.5f, 1.5f, 1.5f);
    last5_starMdl = MBModelCreate(0x3A, last5_starMot);
    AuraCreate(last5_starMdl->omObj1->model[0]);
    HuVecCopy3F(&last5_starMdl->coords, &last5_starPosTbl[0]);
    last5_starMdl->velocity.x = 1000.0f;
    light = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(light, 10.0f, 20.0f, 10.0f);
    Hu3DParticleAttrSet(light, 1, 0);
    EffectRangeSet(light, 300.0f);
    faceModel = MBModelCreate(9, last5_kinopioMot);
    HuVecCopy3F(&faceModel->coords, &last5_npcPos);
    MBGuideFaceCreate(faceModel, 2, 0xA, last5_kinopioFaceAnimA);
    HuAudSeqPlay(0x13);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(WIPE_STARS, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    last5_TitleExec();
    HuAudFXPlay(0x298);
    MBDlgWinExecAllKey(-1, 0x4300);
    for (i = 0; i < 4; i++) {
        HuPrcChildLink(HuPrcCurrentGet(), last5_StatusSlideCreate(i));
        {
            s32 rankMes[] = { 0x4301, 0x4302, 0x4303, 0x4304 };
            window = last5_WinMesOpen(rankMes[MBPlayerRankCalc(last5_rankPlayerTbl[i])],
                                         mbCharNameMesTbl[GwPlayer[last5_rankPlayerTbl[i]].chr], 0, 0, 0, 0, 0x8C,
                                         0x6E);
            last5_WinClose(window);
        }
        HuPrcChildWatch();
    }
    MBDlgWinExecAllKey(-1, 0x4305);
    winner = 3;
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].chr == CHAR_MARIO) {
            winner = last5_playerRankTbl[i];
            break;
        }
    }
    if (i != 4 && MBRand(6.0f) == 0) {
        flag = 1;
    }
    if (flag == 1) {
        MBMotionSet(model, 0, 2);
        value = 0x1E;
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBPlayerPosMoveCreate(&model->coords, &last5_hostWalkPos, &model->coords, 0x1E));
        HuPrcChildWatch();
        step = 0xA;
        MBVecForwardSet(&forward);
        HuPrcChildLink(HuPrcCurrentGet(), MBVecRotLerpCreate(&model->rot, &forward, &model->rot, 0xA));
        HuPrcChildWatch();
        MBMotionSet(model, -1, 2);
        HuAudFXPlay(0x25D);
        window = last5_WinMesOpen(0x4307, 0, 0, 0, 0, 0, 0xA0, 0x50);
        last5_WinKeyWait(window);
        last5_WinClose(window);
    } else {
        Hu3DParticleAttrSet(light, 0, 1);
        HuAudFXPlay(0x157);
        while (400.0f <= last5_starMdl->velocity.x) {
            last5_starMdl->velocity.x -= 20.0f;
            EffectPosSet(light, last5_starMdl->coords.x, last5_starMdl->velocity.x - 100.0f,
                               last5_starMdl->coords.z);
            HuPrcVSleep();
        }
        obj = omAddObj(0x1000, 0, 0, -1, last5_StarHoverObjMain);
        obj->rot.y = last5_starMdl->velocity.x;
        obj->rot.x = 180.0f;
        winner = 3;
        value = MBRand(100.0f);
        for (step = 0; step < 4; step++) {
            if (value < last5_starRankChanceTbl[step]) {
                winner = step;
                break;
            }
        }
        HuAudFXPlay(0x159);
        MBMotionShiftSet(last5_starMdl, 0, 0, 5, 2);
        window = last5_WinMesOpen(0x4306, mbCharNameMesTbl[GwPlayer[last5_rankPlayerTbl[winner]].chr], 0, 0, 0, 0,
                                     0xA0, 0x50);
        last5_WinKeyWait(window);
        last5_WinKeyWait(window);
        last5_WinClose(window);
        MBMotionShiftSet(last5_starMdl, -1, 0, 5, 2);
        value = 0x1E;
        step = 0xA;
    }
    do {
        for (j = 0; j < 4; j++) {
            if (winner != j) {
                MBStatusPosSet(last5_rankPlayerTbl[j], value, last5_statusPosYTbl[j]);
            }
        }
        value -= step;
        step += 2;
        HuPrcVSleep();
    } while (value >= -0xA0);
    value = last5_statusPosYTbl[winner];
    while (last5_statusPosYTbl[0] < value) {
        MBStatusPosSet(last5_rankPlayerTbl[winner], 0x1E, value);
        HuPrcVSleep();
        value -= 0xA;
    }
    MBStatusPosSet(last5_rankPlayerTbl[winner], 0x1E, last5_statusPosYTbl[0]);
    MBPlayerVibrate(last5_rankPlayerTbl[winner], 2);
    window = last5_WinMesOpen(0x4308, mbCharNameMesTbl[GwPlayer[last5_rankPlayerTbl[winner]].chr], 0, 0, 0, 0, 0x50,
                                 0x64);
    last5_WinClose(window);
    MBCoinTakeCreate(last5_rankPlayerTbl[winner], 0xA);
    HuPrcSleep(0x1E);
    if (flag != 0) {
        MBMotionSet(model, 0, 2);
        MBVecDirGet(&model->coords, &last5_hostPos, &model->rot);
        step = 0xA;
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBPlayerPosMoveCreate(&model->coords, &last5_hostPos, &model->coords, 0x1E));
        value = 0x1E;
        while (value >= -0xA0) {
            MBStatusPosSet(last5_rankPlayerTbl[winner], value, last5_statusPosYTbl[0]);
            value -= step;
            step += 2;
            HuPrcVSleep();
        }
        HuPrcChildWatch();
    } else {
        omDelObj(obj);
        value = 0x1E;
        step = 0xA;
        while (value >= -0xA0) {
            MBStatusPosSet(last5_rankPlayerTbl[winner], value, last5_statusPosYTbl[0]);
            value -= step;
            step += 2;
            last5_starMdl->velocity.x += 20.0f;
            EffectPosSet(light, last5_starMdl->coords.x, last5_starMdl->velocity.x - 100.0f,
                               last5_starMdl->coords.z);
            HuPrcVSleep();
        }
        while (last5_starMdl->velocity.x <= 1000.0f) {
            last5_starMdl->velocity.x += 20.0f;
            EffectPosSet(light, last5_starMdl->coords.x, last5_starMdl->velocity.x - 100.0f,
                               last5_starMdl->coords.z);
            HuPrcVSleep();
        }
        Hu3DParticleAttrSet(light, 1, 0);
    }
    EffectStop(light);
    MBDlgWinExecAllKey(-1, 0x4309);
    MBGuideFaceSet(faceModel, last5_kinopioFaceAnimB);
    MBMotionShiftSet(faceModel, 0, 0, 5, 2);
    HuPrcSleep(0x14);
}

void last5_MainProc(void) {
    s32 i;
    s32 rank;
    s32 count;
    s32 *rankPtr;

    for (i = 0; i < 4; i++) {
        last5_playerRankTbl[i] = MBPlayerRankCalc(i);
    }
    for (rank = 0, rankPtr = last5_playerRankTbl, count = 0; rank < 4; rank++) {
        for (i = 0; i < 4; i++) {
            if (rankPtr[i] == rank) {
                count++;
                if (count >= 2) {
                    rankPtr[i] = rank + count - 1;
                }
            }
        }
        count = 0;
    }
    for (i = 0; i < 4; i++) {
        last5_rankPlayerTbl[last5_playerRankTbl[i]] = i;
    }
    if (MBRand(3.0f) == 0) {
        last5_KoopaExec();
    } else {
        last5_StarExec();
    }
    omSysExitReq = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void last5_ExitObjMain(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        last5_BackClose();
        last5_SysClose();
        MBStatusKill();
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void last5_ExitCheckObjMain(omObjData *arg0) {
    if (omSysExitReq != 0) {
        WipeColorSet(0xFF, 0xFF, 0xFF);
        WipeCreateOut(WIPE_STARS, 0x14);
        HuAudSeqFadeOut(0x3C);
        arg0->func = &last5_ExitObjMain;
    }
}

void last5_SysInit(void) {
    MBModelInit();
    MBPlayerMotInit();
    MBMotShiftInit();
}

void last5_SysClose(void) {
    MBMotShiftClose();
    MBPlayerClose();
    MBModelClose();
}

void last5_BackInit(void) {
    s32 sp10[] = { 4, 7, 0xA, 0xD, 0x10, 0x13 };

    Hu3DCamInit(1);
    MBBackArcInit((u32)hvq_data_ROM_START);
    MBBackLoad(sp10[GwSystem.current_board_index]);
    MBCameraNearFarSet(1000.0f, 10000.0f);
}

void last5_BackClose(void) {
    MBBackKill();
    MBBackClose();
}
