#include "common.h"
#include "game/hmfspr.h"
#include "mgresultbattle.h"

extern u16 mgresultbattle_coinNumIconSprTbl[];
extern u16 mgresultbattle_coinNumDigitSprTbl[4][3];
extern omObjData *mgresultbattle_podiumObj;
extern omObjData *mgresultbattle_coinNumObj;
extern omObjFunc mgresultbattle_coinNumFunc;
extern omObjFunc mgresultbattle_podiumFunc;

const s32 mgresultbattle_podiumFileTbl[4] = { 0x001B0001, 0x001B0002, 0x001B0003, 0x001B0004 };

const f32 mgresultbattle_podiumRotTbl[4] = { 10.0f, 2.0f, -2.0f, -10.0f };

void mgresultbattle_PodiumDestroy(void);
void mgresultbattle_PodiumUpdate(omObjData *obj);
void mgresultbattle_CoinNumIdle(omObjData *obj);
void mgresultbattle_CoinNumDestroy(void);
void mgresultbattle_CoinNumShow(omObjData *obj);
void mgresultbattle_CoinNumSet(s16 group, s16 x, s16 y);

void mgresultbattle_PodiumProc(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x14, 8, 8, -1, NULL);
    mgresultbattle_podiumObj = obj;
    obj->model[0] = Hu3DModelRead(0x1B0005, 0x2B9);

    for (i = 0; i < 4; i++) {
        obj->model[i + 1] = Hu3DModelRead(
            mgresultbattle_podiumFileTbl[GwPlayer[mgresultbattle_playerOrderTbl[i]].bonusCoin], 0x16B9);
        Hu3DMotionAttrSet(obj->model[i + 1], 2, 0);
        Hu3DMotionAttrSet(obj->model[i + 1], 1, 1);
        Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(obj->model[i + 1], mgresultbattle_playerPosTbl[i].x, mgresultbattle_playerPosTbl[i].y,
                        mgresultbattle_playerPosTbl[i].z);
        Hu3DModelRotSet(obj->model[i + 1], 0.0f, mgresultbattle_podiumRotTbl[i], 0.0f);
        Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(obj->model[i + 1], Hu3DMotion[Hu3DData[obj->model[i + 1]].motId].unk02);
        Hu3DMotionAttrSet(obj->model[i + 1], 1, 1);
    }

    obj->trans.x = 0.0f;
    obj->trans.y = -5.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(NULL, mgresultbattle_PodiumDestroy);
    mgresultbattle_podiumFunc = mgresultbattle_PodiumUpdate;
    HuPrcSleep(2);

    while (TRUE) {
        mgresultbattle_podiumFunc(obj);
        HuPrcVSleep();
    }
}

void mgresultbattle_PodiumDestroy(void) {
}

void mgresultbattle_PodiumUpdate(omObjData *obj) {
    HuMtx4F mtx;
    s32 i;

    for (i = 0; i < 4; i++) {
        Hu3DModelObjMtxFrameGet(obj->model[i + 1], Hu3DData[obj->model[i + 1]].motTime, "chara", &mtx);
        Hu3DModelPosSet(mgresultbattle_playerWorkTbl[i].obj->model[1], mtx[3][0] + mgresultbattle_playerPosTbl[i].x,
                        mtx[3][1] + mgresultbattle_playerPosTbl[i].y, mtx[3][2] + mgresultbattle_playerPosTbl[i].z);
    }
}

void mgresultbattle_PodiumMotionStart(void) {
    omObjData *obj = mgresultbattle_podiumObj;
    s32 i;

    for (i = 0; i < 4; i++) {
        Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionAttrSet(obj->model[i + 1], 1, 0);
        Hu3DMotionTimeSet(obj->model[i + 1], 0.0f);
    }
}

void mgresultbattle_CoinNumProc(void) {
    omObjData *obj;
    s16 sprite;
    s32 i;
    s32 j;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    mgresultbattle_coinNumObj = obj;

    sprite = HuSprAnimDataRead(0x1B0006);
    for (j = 0; j < 4; j++) {
        mgresultbattle_coinNumIconSprTbl[j] = espEntry(sprite, 0, 0);
        espDispOff(mgresultbattle_coinNumIconSprTbl[j]);
    }

    sprite = HuSprAnimDataRead(0x1B0007);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            mgresultbattle_coinNumDigitSprTbl[i][j] = espEntry(sprite, 0, 0);
            espDispOff(mgresultbattle_coinNumDigitSprTbl[i][j]);
        }
    }

    omPrcSetDestructor(0, mgresultbattle_CoinNumDestroy);
    mgresultbattle_coinNumFunc = mgresultbattle_CoinNumIdle;

    while (TRUE) {
        mgresultbattle_coinNumFunc(obj);
        HuPrcVSleep();
    }
}

void mgresultbattle_CoinNumIdle(omObjData *obj) {
}

void mgresultbattle_CoinNumDestroy(void) {
}

void mgresultbattle_CoinNumShowStart(void) {
    mgresultbattle_coinNumFunc = mgresultbattle_CoinNumShow;
}

void mgresultbattle_CoinNumShow(omObjData *obj) {
    Vec pos;
    Vec2f screen;
    Vec2f screenPos[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        pos.x = Hu3DData[mgresultbattle_playerWorkTbl[i].obj->model[1]].pos.x;
        pos.y = Hu3DData[mgresultbattle_playerWorkTbl[i].obj->model[1]].pos.y;
        pos.z = Hu3DData[mgresultbattle_playerWorkTbl[i].obj->model[1]].pos.z;
        Hu3D3Dto2D(0, &pos, &screen);
        espPosSet(mgresultbattle_coinNumIconSprTbl[i], screen.x, (s32)screen.y - 48);
        espDispOn(mgresultbattle_coinNumIconSprTbl[i]);
        espScaleSet(mgresultbattle_coinNumIconSprTbl[i], 0.0f, 0.0f);
        screenPos[i] = screen;
    }

    for (i = 0; i < 20; i++) {
        sindf(i * 4.5f);
        HuPrcVSleep();
    }

    for (i = 0; i < 4; i++) {
        espScaleSet(mgresultbattle_coinNumIconSprTbl[i], 1.0f, 1.0f);
        mgresultbattle_CoinNumSet(i, screenPos[i].x, (s32)screenPos[i].y - 48);
    }

    mgresultbattle_PlayerReactStart();
    HuPrcSleep(50);
    mgresultbattle_coinNumFunc = mgresultbattle_CoinNumIdle;
}

void mgresultbattle_CoinNumSet(s16 group, s16 x, s16 y) {
    s32 coins = GwPlayer[mgresultbattle_playerOrderTbl[group]].gameCoin;

    if (coins < 10) {
        espDispOn(mgresultbattle_coinNumDigitSprTbl[group][0]);
        espDispOn(mgresultbattle_coinNumDigitSprTbl[group][1]);
        espPosSet(mgresultbattle_coinNumDigitSprTbl[group][0], x - 6, y - 18);
        espPosSet(mgresultbattle_coinNumDigitSprTbl[group][1], x + 4, y - 18);
        espPatNoSet(mgresultbattle_coinNumDigitSprTbl[group][0], 11);
        espPatNoSet(mgresultbattle_coinNumDigitSprTbl[group][1], coins % 10);
    } else {
        espDispOn(mgresultbattle_coinNumDigitSprTbl[group][0]);
        espDispOn(mgresultbattle_coinNumDigitSprTbl[group][1]);
        espDispOn(mgresultbattle_coinNumDigitSprTbl[group][2]);
        espPosSet(mgresultbattle_coinNumDigitSprTbl[group][0], x - 11, y - 18);
        espPosSet(mgresultbattle_coinNumDigitSprTbl[group][1], x - 1, y - 18);
        espPosSet(mgresultbattle_coinNumDigitSprTbl[group][2], x + 9, y - 18);
        if (coins < 100) {
            espPatNoSet(mgresultbattle_coinNumDigitSprTbl[group][0], 11);
        } else {
            espPatNoSet(mgresultbattle_coinNumDigitSprTbl[group][0], coins / 100 % 10);
        }
        espPatNoSet(mgresultbattle_coinNumDigitSprTbl[group][1], coins / 10 % 10);
        espPatNoSet(mgresultbattle_coinNumDigitSprTbl[group][2], coins % 10);
    }
}

void mgresultbattle_CoinNumHide(s16 group) {
    espDispOff(mgresultbattle_coinNumIconSprTbl[group]);
    espDispOff(mgresultbattle_coinNumDigitSprTbl[group][0]);
    espDispOff(mgresultbattle_coinNumDigitSprTbl[group][1]);
    espDispOff(mgresultbattle_coinNumDigitSprTbl[group][2]);
}
