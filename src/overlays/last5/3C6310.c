#include "common.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/106640.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/113520.h"

static Vec D_80107480_last5 = { 750.0f, 0.0f, 2250.0f };
static Vec D_8010748C_last5 = { 150.0f, 0.0f, 1750.0f };
static Vec D_80107498_last5[2] = {
    { 150.0f, 0.0f, 2000.0f },
    { 150.0f, 0.0f, 2000.0f }
};
static Vec D_801074B0_last5 = { 0.0f, 0.0f, 2250.0f };
static u32 D_801074BC_last5[] = { 0x00000001, 0x000A0019 };
static u32 D_801074C4_last5[] = { 0x00000001, 0x000A00FB };
static u32 D_801074CC_last5[] = { 0x00000001, 0x000A00D0 };
static u32 D_801074D4_last5[] = { 0x00000002, 0x000A0035, 0x000A0042 };
static u32 D_801074E0_last5[] = { 0x00000001, 0x000A0125 };
static u8 D_801074E8_last5[] = { 0x05, 0x0F, 0x32, 0x64 };
static u8 D_801074EC_last5[] = { 0x32, 0x55, 0x5F, 0x64 };
static s32 D_801074F0_last5[] = { 0x00000011, 0x00000049, 0x00000081, 0x000000B9 };
static u32 D_80107500_last5 = 0x000A002A;
static u32 D_80107504_last5 = 0x000A002B;

static u8 D_80107550_last5;
static s32 D_80107558_last5[4];
static s32 D_80107568_last5[4];
static UnkBoard8 *D_80107578_last5;
static Object *D_8010757C_last5;

void func_800138EC_main(s16 arg0, s32 arg1, s32 arg2);
void func_800EC5B4_shared_board(s16 arg0, s32 arg1);
void func_80105F9C_last5(void);
void func_80107178_last5(void);
void func_801072FC_last5(omObjData *);
void func_80107358_last5(void);
void func_80107384_last5(void);
void func_801073B0_last5(void);
void func_80107450_last5(void);

void func_801059A0_last5(void) {
    s32 i;

    D_80107550_last5 = GwSystem.current_board_index;
    omInitObjMan(0x32, 0x32);
    func_801073B0_last5();
    func_80107358_last5();
    func_800D95C4_shared_board(1000.0f);
    HuWinInit();
    func_800F453C_shared_board();
    func_800F7108_shared_board();
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBStatusPosSet(i, 0x1E, -0x32);
    }
    omAddPrcObj(func_80107178_last5, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_801072FC_last5);
}

s16 func_80105A68_last5(s16 *arg0, s16 arg1, s16 arg2) {
    return HuWinExCreate(-1, arg1, arg2, arg0[0], arg0[1], 0);
}

void func_80105AAC_last5(s16 arg0) {
    winData[arg0].unk20 = 1;
    HuPrcVSleep();
    func_800EE2C0_shared_board(arg0);
}

s16 func_80105B04_last5(s32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, s16 arg6, s16 arg7) {
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
    window = func_80105A68_last5(sp10, arg6, arg7);

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
    func_800EE2C0_shared_board(window);
    return window;
}

void func_80105C9C_last5(s16 arg0) {
    HuWinExAnimOut(arg0, 0);
    HuWinKill(arg0);
}

void func_80105CD4_last5(omObjData *arg0) {
    f32 scale;

    arg0->work[0]++;
    arg0->rot.x += 30.0f;
    scale = sindf(arg0->rot.x) + 1.0f;
    arg0->scale.x = scale;
    HuSprScaleSet(D_80107578_last5->spriteGroup, 1, scale, scale);
    if (arg0->rot.x >= 360.0f) {
        arg0->rot.x -= 360.0f;
    }
    if (arg0->work[0] >= 0x15) {
        func_80055458_main(D_80107578_last5->spriteGroup, 0, (0x1F - arg0->work[0]) * 25);
        func_80055458_main(D_80107578_last5->spriteGroup, 1, (0x1F - arg0->work[0]) * 25);
    }
}

void func_80105DEC_last5(void) {
    void *data;
    omObjData *obj;

    D_80107578_last5 = func_800F2C48_shared_board(2, 0);
    data = DataRead(0x1301DE);
    D_80107578_last5->model[0] = HuSprAnimRead(data);
    DataClose(data);
    func_80055024_main(D_80107578_last5->spriteGroup, 0, D_80107578_last5->model[0], 0);
    HuSprPriSet(D_80107578_last5->spriteGroup, 0, 0x11);
    HuSprAttrSet(D_80107578_last5->spriteGroup, 0, 0x1000);
    HuSprPosSet(D_80107578_last5->spriteGroup, 0, 0xA0, 0x64);
    data = DataRead(0x1301DF);
    D_80107578_last5->model[1] = HuSprAnimRead(data);
    DataClose(data);
    func_80055024_main(D_80107578_last5->spriteGroup, 1, D_80107578_last5->model[1], 3);
    HuSprPriSet(D_80107578_last5->spriteGroup, 1, 0x10);
    HuSprAttrSet(D_80107578_last5->spriteGroup, 1, 0x1000);
    HuSprPosSet(D_80107578_last5->spriteGroup, 1, 0xA0, 0x64);
    obj = omAddObj(0x1000, 0, 0, -1, func_80105CD4_last5);
    HuPrcSleep(0x1E);
    omDelObj(obj);
    func_800F2CA4_shared_board(D_80107578_last5);
    HuPrcSleep(0xA);
}

void func_80105F9C_last5(void) {
    Process *proc;
    s32 player;
    s32 i;

    proc = HuPrcCurrentGet();
    player = *(s32 *)proc->user_data;
    for (i = 0; i < 0x6E; i += 5) {
        MBStatusPosSet(D_80107568_last5[player], 0x1E,
                       sindf(i) * 250.0f - (0xF1 - D_801074F0_last5[player]));
        HuPrcVSleep();
    }
    MBStatusPosSet(D_80107568_last5[player], 0x1E, D_801074F0_last5[player]);
    omDelPrcObj(0);
}

Process *func_801060A4_last5(s32 arg0) {
    Process *proc;
    s32 *work;

    proc = omAddPrcObj(func_80105F9C_last5, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(proc->heap, 0x10);
    proc->user_data = work;
    *work = arg0;
    return proc;
}

void func_80106100_last5(void) {
    Object *model;
    Object *coinModel;
    Vec forward;
    s16 window;
    s32 winner;
    s32 i;
    s32 value;
    s32 step;

    model = MBModelFileCreate(0xA002F, 9, 0.7f, 1.4f, D_801074D4_last5);
    HuVecCopy3F(&model->coords, &D_80107480_last5);
    MBVecDirGet(&model->coords, &D_8010748C_last5, &model->rot);
    HuVecCopyXYZ(&model->scale, 2.0f, 2.0f, 2.0f);
    coinModel = MBModelCreate(0x39, D_801074C4_last5);
    HuVecCopy3F(&coinModel->coords, &D_801074B0_last5);
    HuAudSeqPlay(0x13);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(2, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_80105DEC_last5();
    HuAudFXPlay(0x2A0);
    func_800EC5B4_shared_board(-1, 0x430A);
    for (value = 0; value < 4; value++) {
        HuPrcChildLink(HuPrcCurrentGet(), func_801060A4_last5(value));
        {
            s32 rankMes[] = { 0x430B, 0x430C, 0x430D, 0x430E };
            window = func_80105B04_last5(rankMes[BoardPlayerRankCalc(D_80107568_last5[value])],
                                         mbCharNameMesTbl[GwPlayer[D_80107568_last5[value]].chr],
                                         0, 0, 0, 0, 0x8C, 0x6E);
            func_80105C9C_last5(window);
        }
        HuPrcChildWait();
    }
    func_800EC5B4_shared_board(-1, 0x430F);
    MBMotionSet(model, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&model->coords, &D_8010748C_last5, &model->coords, 0x3C));
    HuPrcChildWait();
    MBVecForwardSet(&forward);
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&model->rot, &forward, &model->rot, 0xA));
    HuPrcChildWait();
    MBMotionShiftSet(model, -1, 0, 5, 2);
    winner = 0;
    value = MBRand(100.0f);
    for (step = 0; step < 4; step++) {
        if (value < D_801074EC_last5[step]) {
            winner = step;
            break;
        }
    }
    HuAudFXPlay(0x29D);
    window = func_80105B04_last5(0x4310, mbCharNameMesTbl[GwPlayer[D_80107568_last5[winner]].chr],
                                 0, 0, 0, 0, 0xA0, 0x50);
    func_80105AAC_last5(window);
    func_80105C9C_last5(window);
    value = 0x1E;
    step = 0xA;
    while (value >= -0xA0) {
        for (i = 0; i < 4; i++) {
            if (winner != i) {
                MBStatusPosSet(D_80107568_last5[i], value, D_801074F0_last5[i]);
            }
        }
        value -= step;
        step += 2;
        HuPrcVSleep();
    }
    value = D_801074F0_last5[winner];
    while (D_801074F0_last5[0] < value) {
        MBStatusPosSet(D_80107568_last5[winner], 0x1E, value);
        HuPrcVSleep();
        value -= 0xA;
    }
    MBStatusPosSet(D_80107568_last5[winner], 0x1E, D_801074F0_last5[0]);
    MBPlayerVibrate(D_80107568_last5[winner], 2);
    window = func_80105B04_last5(0x4311, mbCharNameMesTbl[GwPlayer[D_80107568_last5[winner]].chr],
                                 0, 0, 0, 0, 0x50, 0x64);
    func_80105C9C_last5(window);
    MBCoinTakeCreate(D_80107568_last5[winner], -0xA);
    HuPrcSleep(0x1E);
    MBMotionSet(model, 1, 2);
    MBVecDirGet(&model->coords, &D_80107480_last5, &model->rot);
    value = 0x1E;
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&model->coords, &D_80107480_last5, &model->coords, 0x1E));
    step = 0xA;
    while (value >= -0xA0) {
        MBStatusPosSet(D_80107568_last5[winner], value, D_801074F0_last5[0]);
        value -= step;
        step += 2;
        HuPrcVSleep();
    }
    HuPrcChildWait();
    func_800EC5B4_shared_board(-1, 0x4312);
    MBMotionShiftSet(coinModel, 0, 0, 5, 2);
    HuPrcSleep(0x14);
}

void func_801066E0_last5(omObjData *arg0) {
    D_8010757C_last5->velocity.x = sindf(arg0->rot.x) * 20.0f + arg0->rot.y;
    arg0->rot.x += 5.0f;
    if (arg0->rot.x >= 360.0f) {
        arg0->rot.x -= 360.0f;
    }
}

void func_80106768_last5(void) {
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

    model = MBModelCreate(0xB, D_801074CC_last5);
    HuVecCopy3F(&model->coords, &D_80107480_last5);
    MBVecDirGet(&model->coords, &D_8010748C_last5, &model->rot);
    HuVecCopyXYZ(&model->scale, 1.5f, 1.5f, 1.5f);
    D_8010757C_last5 = MBModelCreate(0x3A, D_801074E0_last5);
    func_800461B4_main(D_8010757C_last5->omObj1->model[0]);
    HuVecCopy3F(&D_8010757C_last5->coords, &D_80107498_last5[0]);
    D_8010757C_last5->velocity.x = 1000.0f;
    light = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(light, 10.0f, 20.0f, 10.0f);
    func_800138EC_main(light, 1, 0);
    func_8000D018_main(light, 300.0f);
    faceModel = MBModelCreate(9, D_801074BC_last5);
    HuVecCopy3F(&faceModel->coords, &D_801074B0_last5);
    MBGuideFaceCreate(faceModel, 2, 0xA, D_80107500_last5);
    HuAudSeqPlay(0x13);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateIn(2, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_80105DEC_last5();
    HuAudFXPlay(0x298);
    func_800EC5B4_shared_board(-1, 0x4300);
    for (i = 0; i < 4; i++) {
        HuPrcChildLink(HuPrcCurrentGet(), func_801060A4_last5(i));
        {
            s32 rankMes[] = { 0x4301, 0x4302, 0x4303, 0x4304 };
            window = func_80105B04_last5(rankMes[BoardPlayerRankCalc(D_80107568_last5[i])],
                                         mbCharNameMesTbl[GwPlayer[D_80107568_last5[i]].chr], 0, 0, 0, 0, 0x8C,
                                         0x6E);
            func_80105C9C_last5(window);
        }
        HuPrcChildWait();
    }
    func_800EC5B4_shared_board(-1, 0x4305);
    winner = 3;
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].chr == 0) {
            winner = D_80107558_last5[i];
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
                       MBPlayerPosMoveCreate(&model->coords, &D_8010748C_last5, &model->coords, 0x1E));
        HuPrcChildWait();
        step = 0xA;
        MBVecForwardSet(&forward);
        HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&model->rot, &forward, &model->rot, 0xA));
        HuPrcChildWait();
        MBMotionSet(model, -1, 2);
        HuAudFXPlay(0x25D);
        window = func_80105B04_last5(0x4307, 0, 0, 0, 0, 0, 0xA0, 0x50);
        func_80105AAC_last5(window);
        func_80105C9C_last5(window);
    } else {
        func_800138EC_main(light, 0, 1);
        HuAudFXPlay(0x157);
        while (400.0f <= D_8010757C_last5->velocity.x) {
            D_8010757C_last5->velocity.x -= 20.0f;
            func_8000CFA4_main(light, D_8010757C_last5->coords.x, D_8010757C_last5->velocity.x - 100.0f,
                               D_8010757C_last5->coords.z);
            HuPrcVSleep();
        }
        obj = omAddObj(0x1000, 0, 0, -1, func_801066E0_last5);
        obj->rot.y = D_8010757C_last5->velocity.x;
        obj->rot.x = 180.0f;
        winner = 3;
        value = MBRand(100.0f);
        for (step = 0; step < 4; step++) {
            if (value < D_801074E8_last5[step]) {
                winner = step;
                break;
            }
        }
        HuAudFXPlay(0x159);
        MBMotionShiftSet(D_8010757C_last5, 0, 0, 5, 2);
        window = func_80105B04_last5(0x4306, mbCharNameMesTbl[GwPlayer[D_80107568_last5[winner]].chr], 0, 0, 0, 0,
                                     0xA0, 0x50);
        func_80105AAC_last5(window);
        func_80105AAC_last5(window);
        func_80105C9C_last5(window);
        MBMotionShiftSet(D_8010757C_last5, -1, 0, 5, 2);
        value = 0x1E;
        step = 0xA;
    }
    do {
        for (j = 0; j < 4; j++) {
            if (winner != j) {
                MBStatusPosSet(D_80107568_last5[j], value, D_801074F0_last5[j]);
            }
        }
        value -= step;
        step += 2;
        HuPrcVSleep();
    } while (value >= -0xA0);
    value = D_801074F0_last5[winner];
    while (D_801074F0_last5[0] < value) {
        MBStatusPosSet(D_80107568_last5[winner], 0x1E, value);
        HuPrcVSleep();
        value -= 0xA;
    }
    MBStatusPosSet(D_80107568_last5[winner], 0x1E, D_801074F0_last5[0]);
    MBPlayerVibrate(D_80107568_last5[winner], 2);
    window = func_80105B04_last5(0x4308, mbCharNameMesTbl[GwPlayer[D_80107568_last5[winner]].chr], 0, 0, 0, 0, 0x50,
                                 0x64);
    func_80105C9C_last5(window);
    MBCoinTakeCreate(D_80107568_last5[winner], 0xA);
    HuPrcSleep(0x1E);
    if (flag != 0) {
        MBMotionSet(model, 0, 2);
        MBVecDirGet(&model->coords, &D_80107480_last5, &model->rot);
        step = 0xA;
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBPlayerPosMoveCreate(&model->coords, &D_80107480_last5, &model->coords, 0x1E));
        value = 0x1E;
        while (value >= -0xA0) {
            MBStatusPosSet(D_80107568_last5[winner], value, D_801074F0_last5[0]);
            value -= step;
            step += 2;
            HuPrcVSleep();
        }
        HuPrcChildWait();
    } else {
        omDelObj(obj);
        value = 0x1E;
        step = 0xA;
        while (value >= -0xA0) {
            MBStatusPosSet(D_80107568_last5[winner], value, D_801074F0_last5[0]);
            value -= step;
            step += 2;
            D_8010757C_last5->velocity.x += 20.0f;
            func_8000CFA4_main(light, D_8010757C_last5->coords.x, D_8010757C_last5->velocity.x - 100.0f,
                               D_8010757C_last5->coords.z);
            HuPrcVSleep();
        }
        while (D_8010757C_last5->velocity.x <= 1000.0f) {
            D_8010757C_last5->velocity.x += 20.0f;
            func_8000CFA4_main(light, D_8010757C_last5->coords.x, D_8010757C_last5->velocity.x - 100.0f,
                               D_8010757C_last5->coords.z);
            HuPrcVSleep();
        }
        func_800138EC_main(light, 1, 0);
    }
    func_8000D044_main(light);
    func_800EC5B4_shared_board(-1, 0x4309);
    MBGuideFaceSet(faceModel, D_80107504_last5);
    MBMotionShiftSet(faceModel, 0, 0, 5, 2);
    HuPrcSleep(0x14);
}

void func_80107178_last5(void) {
    s32 i;
    s32 rank;
    s32 count;
    s32 *rankPtr;

    for (i = 0; i < 4; i++) {
        D_80107558_last5[i] = BoardPlayerRankCalc(i);
    }
    for (rank = 0, rankPtr = D_80107558_last5, count = 0; rank < 4; rank++) {
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
        D_80107568_last5[D_80107558_last5[i]] = i;
    }
    if (MBRand(3.0f) == 0) {
        func_80106100_last5();
    } else {
        func_80106768_last5();
    }
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_801072B0_last5(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        func_80107450_last5();
        func_80107384_last5();
        func_800F4730_shared_board();
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void func_801072FC_last5(omObjData *arg0) {
    if (D_800D530C_main != 0) {
        WipeColorSet(0xFF, 0xFF, 0xFF);
        WipeCreateOut(2, 0x14);
        HuAudSeqFadeOut(0x3C);
        arg0->func = &func_801072B0_last5;
    }
}

void func_80107358_last5(void) {
    MBModelInit();
    func_800F26E8_shared_board();
    func_800EE700_shared_board();
}

void func_80107384_last5(void) {
    func_800EE740_shared_board();
    func_800F27C4_shared_board();
    MBModelClose();
}

void func_801073B0_last5(void) {
    s32 sp10[] = { 4, 7, 0xA, 0xD, 0x10, 0x13 };

    Hu3DCamInit(1);
    func_800E6630_shared_board((u32)hvq_data_ROM_START);
    MBBackLoad(sp10[GwSystem.current_board_index]);
    func_800E9344_shared_board(1000.0f, 10000.0f);
}

void func_80107450_last5(void) {
    MBBackKill();
    MBBackClose();
}
