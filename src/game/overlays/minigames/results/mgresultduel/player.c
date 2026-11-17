#include "common.h"
#include "game/object.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/hmfspr.h"
#include "game/hmfmath.h"
#include "math.h"
#include "game/overlays/duel/common/ovl_81.h"
#include "mgresultduel.h"

extern s8 mgresultduel_playerOrderTbl[];
extern s8 mgresultduel_coinDir;
extern s16 mgresultduel_hostAnimLink;
extern omObjFunc mgresultduel_coinFunc;
extern omObjFunc mgresultduel_hostFunc; // mgresultduel_hostWork.func (see undefined_syms.txt).
extern omObjData *mgresultduel_coinObj;
extern ResultDuelObj mgresultduel_player2PWork;
extern ResultDuelObj mgresultduel_player1PWork;
extern ResultDuelObj mgresultduel_hostWork;
extern ResultDuelObj mgresultduel_gateGuyWork;
extern s32 mgresultduel_hostAnimTbl[3];
extern s32 mgresultduel_prizeCoin;
extern s32 omCharModelNoTbl[][6];
extern s8 mgresultduel_winSide;
extern u16 mgresultduel_coinSprMdl;
extern u16 mgresultduel_coinEffSprMdl;
extern UnkResultDuelStruct mgresultduel_coinTbl[20];
extern UnkResultDuelStruct mgresultduel_coinEffTbl[20];
extern const f32 mgresultduel_hostPathTbl[5][3];
extern const f32 mgresultduel_hostPathTimeTbl[];

s32 mgresultduel_coinTimer = 0;
s32 mgresultduel_coinNum = 0;
s32 mgresultduel_coinOutCnt = 0;
s32 mgresultduel_coinLandCnt = 0;
s32 mgresultduel_coinMax = 0;
s32 mgresultduel_coinInterval = 0;
s32 mgresultduel_coinVibF = 0;
s8 mgresultduel_coinEndF = 0;

void mgresultduel_Player1PIdle(omObjData *);
void mgresultduel_Player1PCoinWatch(omObjData *);
void mgresultduel_Player1PDestroy(void);
void mgresultduel_Player2PIdle(omObjData *);
void mgresultduel_Player2PDestroy(void);
void mgresultduel_Player1PLoseEnd(omObjData *);
void mgresultduel_Player1PEnter(omObjData *);
void mgresultduel_Player2PCoinWatch(omObjData *);
void mgresultduel_Player2PLose(omObjData *);
void mgresultduel_Player2PEnter(omObjData *);
void mgresultduel_PlayerDrawReactStart(void);
void mgresultduel_PlayerReactWait(omObjData *);
void mgresultduel_CoinAddStart(void);
void mgresultduel_CoinIdle(omObjData *);
void mgresultduel_CoinDestroy(void);
void mgresultduel_CoinInit(s32);
void mgresultduel_CoinSpout(omObjData *);
void mgresultduel_CoinAdd(omObjData *);
void mgresultduel_GateGuyBellStart(void);
void mgresultduel_GateGuyCoinEndStart(void);
void mgresultduel_GateGuyStompStart(void);
void mgresultduel_PlayerReactStart(s8);
void MBDStatusBounceExec(s32);
void MBDCoinChangePosCreate(s32, s32, s32, s32);
void MBDPlayerCoinAdd(s32, s32);
void mgresultduel_HostIdle(omObjData *);
void mgresultduel_HostDestroy(void);
void mgresultduel_HostStomp(omObjData *);
void mgresultduel_HmfAnimSet(s16, s16, s16);
void mgresultduel_HostStompStart(void);
void mgresultduel_HostSmileStart(void);
void mgresultduel_HostSmile(omObjData *);

void mgresultduel_Player1PProc(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 5, 8, -1, NULL);
    mgresultduel_player1PWork.obj = obj;
    chr = GwPlayer[mgresultduel_playerOrderTbl[0]].chr;

    obj->model[1] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][3], 0x2B9);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], -460.0f, 0.0f, 2300.0f);

    obj->model[2] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelPosSet(obj->model[2], -460.0f, -5.0f, 2300.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);

    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x36));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x25));
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, mgresultduel_Player1PDestroy);
    mgresultduel_player1PWork.func = mgresultduel_Player1PIdle;

    while (TRUE) {
        mgresultduel_player1PWork.func(obj);
        HuPrcVSleep();
    }
}

void mgresultduel_Player1PIdle(omObjData *arg0) {
}

void mgresultduel_Player1PCoinWatch(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[arg0->motion[4]].motId, 0, 0x1E, 2);
    mgresultduel_player1PWork.func = mgresultduel_Player1PIdle;
}

void mgresultduel_Player1PWin(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[arg0->motion[2]].motId, 0, 0x1E, 0);
    mgresultduel_player1PWork.func = mgresultduel_PlayerReactWait;
}

void mgresultduel_Player1PLose(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[arg0->motion[3]].motId, 0, 0x1E, 0);
    mgresultduel_player1PWork.func = mgresultduel_Player1PIdle;
}

void mgresultduel_Player1PLoseEnd(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[arg0->motion[3]].motId, 0, 0x1E, 0);
    mgresultduel_player1PWork.func = mgresultduel_PlayerReactWait;
}

void mgresultduel_Player1PDestroy(void) {
}

void mgresultduel_Player1PEnter(omObjData *arg0) {
    f32 i;
    f32 x;
    f32 rot;

    Hu3DModelRotSet(arg0->model[1], 0.0f, 90.0f, 0.0f);
    Hu3DMotionModelSet(arg0->model[1], arg0->motion[1]);
    Hu3DMotionAttrSet(arg0->model[1], 2, 2);
    for (i = 0.0f; i < 240.0f; i += 16.0f) {
        Hu3DModelPosSet(arg0->model[1], -460.0f + i, 0.0f, 2300.0f);
        Hu3DModelPosSet(arg0->model[2], -460.0f + i, -5.0f, 2300.0f);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(arg0->model[1], x = -220.0f, 0.0f, 2300.0f);
    Hu3DModelPosSet(arg0->model[2], x, -5.0f, 2300.0f);
    for (rot = 90.0f; rot >= 0.0f; rot -= 8.0f) {
        Hu3DModelRotSet(arg0->model[1], 0.0f, rot, 0.0f);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[arg0->motion[0]].motId, 0, 0x1E, 2);
    mgresultduel_player1PWork.func = mgresultduel_Player1PIdle;
    if (mgresultduel_winSide != 2) {
        mgresultduel_HostStompStart();
    } else {
        mgresultduel_PlayerDrawReactStart();
    }
}

void mgresultduel_Player2PProc(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 5, 8, -1, NULL);
    mgresultduel_player2PWork.obj = obj;
    chr = GwPlayer[mgresultduel_playerOrderTbl[1]].chr;

    obj->model[1] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][3], 0x2B9);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], 460.0f, 0.0f, 2300.0f);

    obj->model[2] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelPosSet(obj->model[2], 460.0f, -5.0f, 2300.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);

    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x36));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x25));
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, mgresultduel_Player2PDestroy);
    mgresultduel_player2PWork.func = mgresultduel_Player2PIdle;

    while (TRUE) {
        mgresultduel_player2PWork.func(obj);
        HuPrcVSleep();
    }
}

void mgresultduel_Player2PIdle(omObjData *arg0) {
}

void mgresultduel_Player2PCoinWatch(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[arg0->motion[4]].motId, 0, 0x1E, 2);
    mgresultduel_player2PWork.func = mgresultduel_Player2PIdle;
}

void mgresultduel_Player2PWin(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[arg0->motion[2]].motId, 0, 0x1E, 0);
    mgresultduel_player2PWork.func = mgresultduel_PlayerReactWait;
}

void mgresultduel_Player2PLose(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[arg0->motion[3]].motId, 0, 0x1E, 0);
    mgresultduel_player2PWork.func = mgresultduel_Player2PIdle;
}

void mgresultduel_Player2PEnter(omObjData *arg0) {
    f32 i;
    f32 x;
    f32 rot;

    Hu3DModelRotSet(arg0->model[1], 0.0f, -90.0f, 0.0f);
    Hu3DMotionModelSet(arg0->model[1], arg0->motion[1]);
    Hu3DMotionAttrSet(arg0->model[1], 2, 2);
    for (i = 0.0f; i < 240.0f; i += 16.0f) {
        Hu3DModelPosSet(arg0->model[1], 460.0f - i, 0.0f, 2300.0f);
        Hu3DModelPosSet(arg0->model[2], 460.0f - i, -5.0f, 2300.0f);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(arg0->model[1], x = 220.0f, 0.0f, 2300.0f);
    Hu3DModelPosSet(arg0->model[2], x, -5.0f, 2300.0f);
    for (rot = 90.0f; rot >= 0.0f; rot -= 8.0f) {
        Hu3DModelRotSet(arg0->model[1], 0.0f, -rot, 0.0f);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[arg0->motion[0]].motId, 0, 0x1E, 2);
    mgresultduel_player2PWork.func = mgresultduel_Player2PIdle;
}

void mgresultduel_Player2PDestroy(void) {
}

void mgresultduel_PlayerEnterStart(void) {
    mgresultduel_player1PWork.func = mgresultduel_Player1PEnter;
    mgresultduel_player2PWork.func = mgresultduel_Player2PEnter;
}

void mgresultduel_PlayerCoinWatchStart(s8 arg0) {
    if (arg0 == -1) {
        mgresultduel_player1PWork.func = mgresultduel_Player1PCoinWatch;
    } else {
        mgresultduel_player2PWork.func = mgresultduel_Player2PCoinWatch;
    }
}

void mgresultduel_PlayerReactStart(s8 arg0) {
    HuPrcSleep(2);
    if (arg0 == -1) {
        HuAudFXPanning(PlayerFXPlay(0x28F, mgresultduel_playerOrderTbl[0]), 0x20);
        HuAudFXPanning(PlayerFXPlay(0x26B, mgresultduel_playerOrderTbl[1]), 0x60);
        mgresultduel_player1PWork.func = mgresultduel_Player1PWin;
        mgresultduel_player2PWork.func = mgresultduel_Player2PLose;
    } else {
        HuAudFXPanning(PlayerFXPlay(0x26B, mgresultduel_playerOrderTbl[0]), 0x20);
        HuAudFXPanning(PlayerFXPlay(0x28F, mgresultduel_playerOrderTbl[1]), 0x60);
        mgresultduel_player1PWork.func = mgresultduel_Player1PLose;
        mgresultduel_player2PWork.func = mgresultduel_Player2PWin;
    }
    mgresultduel_HostSmileStart();
}

void mgresultduel_PlayerDrawReactStart(void) {
    HuPrcSleep(2);
    mgresultduel_player1PWork.func = mgresultduel_Player1PLoseEnd;
    mgresultduel_player2PWork.func = mgresultduel_Player2PLose;
}

void mgresultduel_PlayerReactWait(omObjData *obj) {
    f32 time;
    f32 endTime;
    s16 model;

    model = obj->model[1];
    time = Hu3DData[model].motTime;
    endTime = Hu3DMotion[Hu3DData[model].motId].unk02;
    while (endTime <= time) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    mgresultduel_CoinAddStart();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void mgresultduel_CoinProc(void) {
    omObjData *obj;
    void *data;
    s8 i;

    obj = omAddObj(20, 42, 0, -1, NULL);
    mgresultduel_coinObj = obj;

    data = DataRead(0x210026);
    mgresultduel_coinSprMdl = Hu3DSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    Hu3DModelObjAttrSet(Hu3DSprModelData[mgresultduel_coinSprMdl].modelId, 0x70000000, 0x70000000);
    for (i = 0; i < 20; i++) {
        mgresultduel_coinTbl[i].unk00 = 0;
        mgresultduel_coinTbl[i].unk02 = Hu3DSprModelLink(mgresultduel_coinSprMdl, 8);
        mgresultduel_coinTbl[i].unk04 = 0;
        obj->model[i + 1] = Hu3DSprModelData[mgresultduel_coinTbl[i].unk02].modelId;
        Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
        Hu3DModelCameraSet(obj->model[i + 1], HU3D_CAM0);
        Hu3DMotionSpeedSet(obj->model[i + 1], 2.0f);
        Hu3DModelScaleSet(Hu3DSprModelData[i + 1].modelId, 1.5f, 1.5f, 1.5f);
    }

    data = DataRead(0xC);
    mgresultduel_coinEffSprMdl = Hu3DSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    Hu3DModelObjAttrSet(Hu3DSprModelData[mgresultduel_coinEffSprMdl].modelId, 0x70000000, 0x70000000);
    Hu3DModelScaleSet(Hu3DSprModelData[mgresultduel_coinEffSprMdl].modelId, 1.0f, 1.0f, 1.0f);
    for (i = 0; i < 20; i++) {
        mgresultduel_coinEffTbl[i].unk00 = 0;
        mgresultduel_coinEffTbl[i].unk02 = Hu3DSprModelLink(mgresultduel_coinEffSprMdl, 8);
        mgresultduel_coinEffTbl[i].unk04 = 0;
        obj->model[i + 21] = Hu3DSprModelData[mgresultduel_coinEffTbl[i].unk02].modelId;
        Hu3DModelPosSet(obj->model[i + 21], 0.0f, 400.0f, 0.0f);
        Hu3DModelCameraSet(obj->model[i + 21], HU3D_CAM0);
        Hu3DMotionSpeedSet(obj->model[i + 21], 1.0f);
        Hu3DModelScaleSet(Hu3DSprModelData[i + 21].modelId, 3.0f, 3.0f, 3.0f);
    }

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, mgresultduel_CoinDestroy);
    mgresultduel_coinFunc = mgresultduel_CoinIdle;

    while (TRUE) {
        mgresultduel_coinFunc(obj);
        HuPrcVSleep();
    }
}

void mgresultduel_CoinIdle(omObjData *arg0) {
}

void mgresultduel_CoinDestroy(void) {
}

void mgresultduel_CoinInit(s32 arg0) {
    omObjData *obj;
    s8 i;

    obj = mgresultduel_coinObj;
    if (arg0 > 0) {
        arg0 = (arg0 > 50) ? 50 : arg0;
        mgresultduel_coinNum = arg0;
        mgresultduel_coinOutCnt = 0;
        mgresultduel_coinTimer = 0;
        mgresultduel_coinLandCnt = 0;
        if (arg0 <= 100) {
            mgresultduel_coinMax = arg0;
        } else {
            mgresultduel_coinMax = 100;
        }
        mgresultduel_coinInterval = 4;
        for (i = 0; i < 20; i++) {
            mgresultduel_coinTbl[i].unk00 = 0;
            mgresultduel_coinTbl[i].unk04 = 0;
            mgresultduel_coinTbl[i].pos.x = mgresultduel_coinTbl[i].pos.y =
                mgresultduel_coinTbl[i].pos.z = 0.0f;
            mgresultduel_coinTbl[i].unk14 = -10.0f;
            Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
        }
    }
}

void mgresultduel_CoinSpoutStart(s32 arg0, s32 arg1) {
    mgresultduel_coinDir = arg1;
    mgresultduel_CoinInit(arg0);
    mgresultduel_coinFunc = mgresultduel_CoinSpout;
}

void mgresultduel_CoinSpout(omObjData *obj) {
    HmfModelEntry *entry;
    HmfAnimSet *animSet;
    HmfAnimRot *rot;
    s8 i;
    s8 count;
    s32 max;
    f32 x;
    f32 y;
    f32 z;
    f32 t;

    if (mgresultduel_coinOutCnt < mgresultduel_coinMax) {
        count = 0;
        for (i = 0; i < 20; i++) {
            if (mgresultduel_coinTbl[i].unk00 == 1) {
                continue;
            }
            if (mgresultduel_coinTimer % mgresultduel_coinInterval != 0) {
                continue;
            }
            entry = &Hu3DSprModelData[mgresultduel_coinTbl[i].unk02];
            animSet = &Hu3DAnimSetData[(u16)entry->unk_02];
            rot = &animSet->rot[entry->pointIdx];
            Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            if (mgresultduel_coinNum >= 20) {
                max = (rand8() & 1) + 1;
            } else {
                max = 1;
            }
            Hu3DModelPosSet(obj->model[i + 1], 0.0f, 400.0f, 0.0f);
            mgresultduel_coinTbl[i].pos.x = (u8)(rand8() % 40) - 20;
            mgresultduel_coinTbl[i].pos.y = (u8)(rand8() % 40) - 20;
            mgresultduel_coinTbl[i].pos.z = (u8)(rand8() % 40) - 20;
            mgresultduel_coinTbl[i].unk00 = 1;
            mgresultduel_coinTbl[i].unk04 = 0;
            entry->nodeIdx = rand8() % rot->frameCount;
            entry->unk_08 = 0;
            mgresultduel_coinOutCnt++;
            if (mgresultduel_coinOutCnt >= mgresultduel_coinMax) {
                break;
            }
            count++;
            if (count >= max) {
                break;
            }
        }
    } else if (!mgresultduel_coinEndF) {
        mgresultduel_GateGuyCoinEndStart();
        mgresultduel_coinEndF = 1;
    }

    for (i = 0; i < 20; i++) {
        if (mgresultduel_coinTbl[i].unk00 == 0) {
            continue;
        }
        t = mgresultduel_coinTbl[i].unk04;
        x = t * 8.8f + mgresultduel_coinTbl[i].pos.x;
        y = sindf(t * 7.2f) * 170.0f + mgresultduel_coinTbl[i].pos.y;
        z = mgresultduel_coinTbl[i].pos.z;
        Hu3DModelPosSet(obj->model[i + 1], x * mgresultduel_coinDir, y + 170.0f, z + 2300.0f);
        mgresultduel_coinTbl[i].unk04++;
        if (mgresultduel_coinTbl[i].unk04 < 25) {
            continue;
        }
        mgresultduel_coinLandCnt++;
        mgresultduel_coinTbl[i].unk00 = 0;
        Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[i + 21], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(obj->model[i + 21], x * mgresultduel_coinDir, y + 170.0f, z + 2300.0f);
        Hu3DMotionTimeSet(obj->model[i + 21], 0);
        Hu3DSprModelFrameSet(mgresultduel_coinEffTbl[i].unk02, 0);
        HuAudFXPlay(9);
        if (mgresultduel_coinVibF == 0) {
            if (mgresultduel_winSide == -1) {
                if (!(GwPlayer[mgresultduel_playerOrderTbl[0]].stat & 1)) {
                    omVibrate(mgresultduel_playerOrderTbl[0], 5, 0, 5);
                }
            } else {
                if (!(GwPlayer[mgresultduel_playerOrderTbl[1]].stat & 1)) {
                    omVibrate(mgresultduel_playerOrderTbl[1], 5, 0, 5);
                }
            }
            mgresultduel_coinVibF = 1;
        }
    }

    mgresultduel_coinTimer++;
    if (mgresultduel_coinNum <= mgresultduel_coinLandCnt) {
        mgresultduel_coinEndF = 0;
        mgresultduel_PlayerReactStart(mgresultduel_winSide);
        mgresultduel_coinFunc = mgresultduel_CoinIdle;
    }
}

void mgresultduel_CoinAddStart(void) {
    mgresultduel_coinFunc = mgresultduel_CoinAdd;
}

void mgresultduel_CoinAdd(omObjData *arg0) {
    omObjData *obj;
    Vec pos;
    Vec2f screenPos;
    s16 player;

    MBDStatusBounceExec(-1);
    if (mgresultduel_winSide != 2) {
        if (mgresultduel_winSide == -1) {
            obj = mgresultduel_player1PWork.obj;
        } else {
            obj = mgresultduel_player2PWork.obj;
        }
        pos.x = Hu3DData[obj->model[1]].pos.x;
        pos.y = Hu3DData[obj->model[1]].pos.y + 120.0f;
        pos.z = Hu3DData[obj->model[1]].pos.z;
        Hu3D3Dto2D(0, &pos, &screenPos);
        MBDCoinChangeInit();
        if (mgresultduel_winSide == -1) {
            player = mgresultduel_playerOrderTbl[0];
            MBDCoinChangePosCreate(mgresultduel_playerOrderTbl[0], mgresultduel_prizeCoin, screenPos.x, screenPos.y);
        } else {
            player = mgresultduel_playerOrderTbl[1];
            MBDCoinChangePosCreate(mgresultduel_playerOrderTbl[1], mgresultduel_prizeCoin, screenPos.x, screenPos.y);
        }
        HuPrcSleep(20);
        MBDPlayerCoinAdd(player, mgresultduel_prizeCoin);
        HuPrcSleep(20);
        MBDCoinChangeClose();
    } else {
        HuPrcSleep(40);
    }
    mgresultduel_GateGuyBellStart();
    mgresultduel_coinFunc = mgresultduel_CoinIdle;
}

void mgresultduel_HostProc(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 5, 6, -1, NULL);
    mgresultduel_hostWork.obj = obj;
    obj->model[1] = Hu3DModelRead(0xA0075, 0x2A9);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);

    data = DataRead(0xA007E);
    mgresultduel_hostAnimTbl[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mgresultduel_hostAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(mgresultduel_hostAnimTbl[0], 0);
    mgresultduel_hostAnimLink =
        Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mgresultduel_hostAnimTbl[0], 0, "c204n_0_DEF");
    mgresultduel_hostAnimTbl[0] = Hu3DAnimData[mgresultduel_hostAnimTbl[0]].animIdx;

    data = DataRead(0xA0081);
    mgresultduel_hostAnimTbl[1] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);

    data = DataRead(0xA0084);
    mgresultduel_hostAnimTbl[2] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);

    mgresultduel_HmfAnimSet(obj->model[1], mgresultduel_hostAnimLink, mgresultduel_hostAnimTbl[0]);

    obj->model[2] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelPosSet(obj->model[2], 0.0f, -5.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);

    omObjMotionRead(obj, 0, 0xA0076);
    omObjMotionRead(obj, 1, 0xA0077);
    omObjMotionRead(obj, 2, 0xA0078);
    omObjMotionRead(obj, 3, 0xA007A);
    omObjMotionRead(obj, 4, 0xA007B);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], 700.0f, 300.0f, 1600.0f);
    Hu3DModelPosSet(obj->model[2], 700.0f, -5.0f, 1600.0f);
    omPrcSetDestructor(0, mgresultduel_HostDestroy);
    mgresultduel_hostWork.func = mgresultduel_HostIdle;

    while (TRUE) {
        mgresultduel_hostFunc(obj);
        HuPrcVSleep();
    }
}

void mgresultduel_HostIdle(omObjData *arg0) {
}

void mgresultduel_HostStomp(omObjData *obj) {
    omObjData *otherObj;
    f32 values[4];
    f32 pos[3];
    f32 x;
    f32 y;
    f32 z;
    f32 t;
    s8 i;
    s8 j;
    s32 seg;
    s32 started;

    otherObj = mgresultduel_gateGuyWork.obj;
    x = 700.0f;
    z = 1600.0f;
    started = 0;
    Hu3DModelPosSet(obj->model[1], x, 300.0f, z);
    seg = 0;
    Hu3DModelPosSet(obj->model[2], x, -0.5f, z);
    HuPrcVSleep();
    t = 0.0f;
    while (TRUE) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 4; j++) {
                values[j] = mgresultduel_hostPathTbl[j + seg][i];
            }
            pos[i] = InterpolateBMLine(values, &mgresultduel_hostPathTimeTbl[seg], t);
        }
        t += 1.0f;
        if (mgresultduel_hostPathTimeTbl[seg + 2] <= t) {
            seg++;
            if (seg + 3 >= 5) {
                break;
            }
        }
        Hu3DModelPosSet(obj->model[1], pos[0], pos[1], pos[2]);
        Hu3DModelPosSet(obj->model[2], pos[0], -0.5f, pos[2]);
        HuPrcVSleep();
    }

    x = pos[0];
    z = pos[2];
    Hu3DModelPosSet(obj->model[1], x, pos[1], z);
    Hu3DModelPosSet(obj->model[2], x, -0.5f, z);
    mgresultduel_HmfAnimSet(obj->model[1], mgresultduel_hostAnimLink, mgresultduel_hostAnimTbl[1]);
    HuPrcSleep(12);
    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    for (i = 0; i < 6; i++) {
        y = sindf(i * 15.0f) * 120.0f;
        Hu3DModelPosSet(obj->model[1], x, pos[1] - y, z);
        if (i >= 2 && started != TRUE) {
            mgresultduel_GateGuyStompStart();
            started = 1;
        }
        HuPrcVSleep();
    }

    HuPrcSleep(2);
    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
    for (i = 0; i < 12; i++) {
        y = cosdf(i * 7.5f) * 120.0f;
        Hu3DModelPosSet(obj->model[1], x, pos[1] - y, z);
        HuPrcVSleep();
    }

    x = Hu3DData[otherObj->model[1]].pos.x;
    z = Hu3DData[otherObj->model[1]].pos.z;
    Hu3DModelPosSet(obj->model[1], x, pos[1], z);
    Hu3DModelPosSet(obj->model[2], x, -0.5f, z);
    HuPrcVSleep();
    for (i = 0; i < 10; i++) {
        y = sindf(i * 9.0f) * 50.0f;
        Hu3DModelPosSet(obj->model[1], x, y + pos[1], z);
        HuPrcVSleep();
    }
    mgresultduel_hostFunc = mgresultduel_HostIdle;
}

void mgresultduel_HostDestroy(void) {
}

void mgresultduel_HmfAnimSet(s16 model, s16 anim, s16 animIdx) {
    HmfAnim *entry;

    if (anim >= 0) {
        if (animIdx == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            Hu3DModelAnimStart(Hu3DData[model].hmf);
            entry = &Hu3DAnimData[anim];
            entry->animIdx = animIdx;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}

void mgresultduel_HostStompStart(void) {
    mgresultduel_hostFunc = mgresultduel_HostStomp;
}

void mgresultduel_HostSmileStart(void) {
    mgresultduel_hostFunc = mgresultduel_HostSmile;
}

void mgresultduel_HostSmile(omObjData *arg0) {
    mgresultduel_HmfAnimSet(arg0->model[1], mgresultduel_hostAnimLink, mgresultduel_hostAnimTbl[2]);
    mgresultduel_hostFunc = mgresultduel_HostIdle;
}

const f32 mgresultduel_hostPathTbl[5][3] = {
    { 1000.0f, 2000.0f, 1500.0f },
    { 600.0f, 600.0f, 1800.0f },
    { 300.0f, 50.0f, 2000.0f },
    { 0.0f, 300.0f, 2300.0f },
    { 0.0f, 800.0f, 2400.0f }
};

const f32 mgresultduel_hostPathTimeTbl[] = { 0.0f, 5.0f, 15.0f, 40.0f, 80.0f };
