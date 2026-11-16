#include "common.h"
#include "game/object.h"
#include "math.h"
#include "game/overlays/duel/common/ovl_81.h"
#include "mgresultduel.h"

extern s8 mgresultduel_playerOrderTbl[];
extern s32 mgresultduel_prizeCoin;
extern s16 mgresultduel_prizeCoinHalf; // Low half of mgresultduel_prizeCoin (see undefined_syms.txt).
extern s8 mgresultduel_winSide;
extern ResultDuelObj mgresultduel_gateGuyWork;

s8 mgresultduel_mainState = 0;
s32 mgresultduel_mainTimer = 0;
s8 mgresultduel_exitWipeF = 0;

const s16 mgresultduel_statusPosTbl[2][2] = { { 30, 40 }, { 194, 40 } };
extern Addr D_128CC60;

void MBDStatusPosSet(s32, s16, s16);
void MBDStatusScaleSet(s32, f32, f32);
void mgresultduel_MainObjMain(omObjData *);
void mgresultduel_ExitObjMain(omObjData *);
void mgresultduel_SysClose(void);
void mgresultduel_GateGuyProc(void);
void mgresultduel_Player1PProc(void);
void mgresultduel_Player2PProc(void);
void mgresultduel_CoinProc(void);
void mgresultduel_HostProc(void);
void mgresultduel_GateGuyDestroy(omObjData *);
void mgresultduel_GateGuyIdle(omObjData *);
void mgresultduel_GateGuyStomp(omObjData *);
void mgresultduel_GateGuyCoinEnd(omObjData *);
void mgresultduel_GateGuyBellUpdate(omObjData *);
void mgresultduel_GateGuyBellInit(omObjData *, s32);
void mgresultduel_PlayerEnterStart(void);
void mgresultduel_PlayerCoinWatchStart(s8);
void mgresultduel_CoinSpoutStart(s32, s32);

void mgresultduel_ObjectSetup(void) {
    s16 coins[2];
    s8 count = 0;
    s8 i;
    s8 j;
    s8 player;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == GwPlayer[j].group) {
                mgresultduel_playerOrderTbl[count] = j;
                count++;
                if (count >= 4) {
                    break;
                }
            }
        }
        if (count >= 4) {
            break;
        }
    }

    omInitObjMan(50, 20);
    Hu3DSprModelInit(120);
    MBDStatusCreate();
    MBDStatusPosSet(0, mgresultduel_statusPosTbl[0][0], mgresultduel_statusPosTbl[0][1]);
    MBDStatusPosSet(1, mgresultduel_statusPosTbl[1][0], mgresultduel_statusPosTbl[1][1]);
    MBDStatusScaleSet(0, 0.0f, 0.0f);
    MBDStatusScaleSet(1, 0.0f, 0.0f);
    Hu3DCamInit(1);
    MBDBackArcInit(D_128CC60);
    MBDBackLoad(23);
    MBDCameraNearFarSet(1000.0f, 10000.0f);

    coins[0] = GwPlayer[mgresultduel_playerOrderTbl[0]].gameCoin + GwPlayer[mgresultduel_playerOrderTbl[0]].bonusCoin;
    coins[1] = GwPlayer[mgresultduel_playerOrderTbl[1]].gameCoin + GwPlayer[mgresultduel_playerOrderTbl[1]].bonusCoin;
    if (coins[0] >= coins[1]) {
        if (coins[0] == coins[1]) {
            mgresultduel_winSide = 2;
            mgresultduel_prizeCoin = 0;
        } else {
            player = mgresultduel_playerOrderTbl[0];
            mgresultduel_winSide = -1;
            mgresultduel_prizeCoin = GwPlayer[mgresultduel_playerOrderTbl[player]].gameCoin + GwPlayer[player].bonusCoin;
            if (GwSystem.bank_coins == 0) {
                if (GwSystem.current_turn < 11) {
                    mgresultduel_prizeCoin *= 2;
                } else if (GwSystem.current_turn < 20) {
                    mgresultduel_prizeCoin *= 3;
                } else {
                    mgresultduel_prizeCoin *= 4;
                }
            }
        }
    } else {
        player = mgresultduel_playerOrderTbl[1];
        mgresultduel_winSide = 1;
        mgresultduel_prizeCoin = GwPlayer[mgresultduel_playerOrderTbl[player]].gameCoin + GwPlayer[player].bonusCoin;
        if (GwSystem.bank_coins == 0) {
            if (GwSystem.current_turn < 11) {
                mgresultduel_prizeCoin *= 2;
            } else if (GwSystem.current_turn < 20) {
                mgresultduel_prizeCoin *= 3;
            } else {
                mgresultduel_prizeCoin *= 4;
            }
        }
    }

    if (coins[0] != coins[1]) {
        if (coins[0] >= coins[1]) {
            GwPlayer[mgresultduel_playerOrderTbl[0]].gamePrize += mgresultduel_prizeCoinHalf;
        } else {
            GwPlayer[mgresultduel_playerOrderTbl[1]].gamePrize += mgresultduel_prizeCoinHalf;
        }
    }

    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, 0.0f, 50.0f, 100.0f);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omAddPrcObj(mgresultduel_Player1PProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultduel_Player2PProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultduel_GateGuyProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultduel_HostProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultduel_CoinProc, 0x1001, 0x2000, 0);
    omAddObj(10, 0, 0, -1, mgresultduel_MainObjMain);
    omAddObj(10, 0, 0, -1, mgresultduel_ExitObjMain);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void mgresultduel_MainObjMain(omObjData *object) {
    s32 state;
    s16 playerIdx;

    state = mgresultduel_mainState;
    switch (state) {
        case 0:
            HuAudSeqPlay(0x16);
            mgresultduel_mainTimer = 0;
            state++;
            break;
        case 1:
            mgresultduel_mainTimer++;
            if (mgresultduel_mainTimer >= 20) {
                state++;
            }
            break;
        case 2:
            mgresultduel_PlayerEnterStart();
            state++;
            break;
        case 4:
            if (mgresultduel_winSide != 2) {
                if (mgresultduel_winSide == -1) {
                    playerIdx = mgresultduel_playerOrderTbl[0];
                } else {
                    playerIdx = mgresultduel_playerOrderTbl[1];
                }
                GwPlayer[playerIdx].gameCoin = 0;
                GwPlayer[playerIdx].bonusCoin = 0;
            }
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            HuAudSeqFadeOut(30);
            HuAudFXAllFadeOut(30);
            state++;
            break;
        case 5:
            if (WipeStatGet() == 0) {
                mgresultduel_SysClose();
                omOvlReturnEx(1);
            }
            break;
    }
    mgresultduel_mainState = state;
}

void mgresultduel_ExitObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        if (mgresultduel_exitWipeF == 0) {
            WipeCreateOut(WIPE_TYPE_NORMAL, 0x14);
            mgresultduel_exitWipeF = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            HuAudFXAllFadeOut(30);
            mgresultduel_SysClose();
            omOvlReturnEx(1);
        }
    }
}

void mgresultduel_SysClose(void) {
    MBDBackKill();
    MBDBackClose();
    MBDStatusKill();
}

void mgresultduel_GateGuyProc(void) {
    omObjData *temp_v0;

    temp_v0 = omAddObj(0x14, 5, 8, -1, NULL);
    mgresultduel_gateGuyWork.obj = temp_v0;
    temp_v0->model[1] = Hu3DModelRead(0xA011B, 0x2B9);
    Hu3DMotionAttrSet(temp_v0->model[1], 2, 2);
    Hu3DModelScaleSet(temp_v0->model[1], 0.9f, 0.9f, 0.9f);
    temp_v0->model[2] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelScaleSet(temp_v0->model[2], 2.0f, 1.0f, 2.0f);
    omObjMotionRead(temp_v0, 0, 0xA011C);
    omObjMotionRead(temp_v0, 1, 0xA011D);
    omObjMotionRead(temp_v0, 2, 0xA011E);
    omObjMotionRead(temp_v0, 3, 0xA011F);
    omObjMotionRead(temp_v0, 4, 0xA0120);
    Hu3DMotionModelSet(temp_v0->model[1], temp_v0->motion[4]);
    Hu3DMotionAttrSet(temp_v0->model[1], 2, 2);
    mgresultduel_GateGuyBellInit(temp_v0, -1);
    temp_v0->trans.x = 0.0f;
    temp_v0->trans.y = 0.0f;
    temp_v0->trans.z = 0.0f;
    Hu3DModelPosSet(temp_v0->model[0], temp_v0->trans.x, temp_v0->trans.y, temp_v0->trans.z);
    Hu3DModelPosSet(temp_v0->model[1], 0.0f, 0.0f, 2300.0f);
    Hu3DModelPosSet(temp_v0->model[2], 0.0f, 0.0f, 2300.0f);
    omPrcSetDestructor(0, mgresultduel_GateGuyDestroy);
    mgresultduel_gateGuyWork.func = mgresultduel_GateGuyIdle;
    while (1) {
        mgresultduel_gateGuyWork.func(temp_v0);
        HuPrcVSleep();
    }
}

void mgresultduel_GateGuyIdle(omObjData *arg0) {
}

void mgresultduel_GateGuyStomp(omObjData *obj) {
    f32 scale;
    s8 i;

    scale = 0.9f;
    Hu3DModelScaleSet(obj->model[1], scale, scale, scale);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 0x1E, 2);
    mgresultduel_GateGuyBellInit(obj, Hu3DData[obj->motion[1]].motId);
    HuAudFXPlay(0x20F);
    for (i = 0; i < 4; i++) {
        Hu3DModelScaleSet(obj->model[1], 0.9f, 0.9f - sindf(i * 22.5f) * 0.24f, 0.9f);
        HuPrcVSleep();
    }
    HuPrcSleep(2);
    for (i = 0; i < 4; i++) {
        Hu3DModelScaleSet(obj->model[1], 0.9f, 0.9f - cosdf(i * 22.5f) * 0.24f, 0.9f);
        HuPrcVSleep();
    }
    Hu3DModelScaleSet(obj->model[1], 0.9f, 0.9f, 0.9f);
    HuAudFXPlay(0x20D);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[3]].motId, 0, 0x1E, 2);
    mgresultduel_GateGuyBellInit(obj, Hu3DData[obj->motion[3]].motId);
    Hu3DMotionSpeedSet(obj->model[1], 2.0f);
    mgresultduel_PlayerCoinWatchStart(mgresultduel_winSide);
    mgresultduel_CoinSpoutStart(mgresultduel_prizeCoin, mgresultduel_winSide);
    mgresultduel_gateGuyWork.func = mgresultduel_GateGuyIdle;
}

void mgresultduel_GateGuyDestroy(omObjData *arg0) {
}

void mgresultduel_GateGuyStompStart(void) {
    mgresultduel_gateGuyWork.func = mgresultduel_GateGuyStomp;
}

void mgresultduel_GateGuyCoinEndStart(void) {
    mgresultduel_gateGuyWork.func = mgresultduel_GateGuyCoinEnd;
}

void mgresultduel_GateGuyCoinEnd(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[3]].motId, 0, 0x1E, 0);
    Hu3DMotionAttrSet(obj->model[1], 2, 0);
    Hu3DMotionAttrSet(obj->model[1], 4, 4);
    mgresultduel_GateGuyBellInit(obj, Hu3DData[obj->motion[3]].motId);
    Hu3DMotionSpeedSet(obj->model[1], 1.0f);
    while (Hu3DData[obj->model[1]].motTime > 0.0f) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[4]].motId, 0, 0x1E, 2);
    mgresultduel_GateGuyBellInit(obj, Hu3DData[obj->motion[4]].motId);
    mgresultduel_gateGuyWork.func = mgresultduel_GateGuyIdle;
}

void mgresultduel_GateGuyBellStart(void) {
    mgresultduel_gateGuyWork.func = mgresultduel_GateGuyBellUpdate;
}

void mgresultduel_GateGuyBellUpdate(omObjData *obj) {
    HmfMotionNode *node;
    f32 rot;

    node = Hu3DModelObjPtrGet(obj->model[1], "bell");
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
    if (GwSystem.bank_coins == 0) {
        for (rot = 0.0f; rot >= -60.0f; rot -= 2.0f) {
            node->baseRot.y = (GwSystem.bank_coins - 5) * 60 + rot;
            HuPrcVSleep();
        }
        GwSystem.bank_coins = 5;
        HuPrcSleep(10);
    }
    mgresultduel_mainState = 4;
    mgresultduel_gateGuyWork.func = mgresultduel_GateGuyIdle;
}

void mgresultduel_GateGuyBellInit(omObjData *obj, s32 motId) {
    HmfMotionNode *node;

    Hu3DMotionNoMotSet(obj->model[1], Hu3DData[obj->model[1]].motId, "bell", 0x4C, 0x46);
    if ((s16)motId >= 0) {
        Hu3DMotionNoMotSet(obj->model[1], motId, "bell", 0x4C, 0x46);
    }
    node = Hu3DModelObjPtrGet(obj->model[1], "bell");
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
}
