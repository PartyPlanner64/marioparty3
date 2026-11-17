#include "common.h"
#include "game/hmfspr.h"
#include "mgresultbattle.h"

void mgresultbattle_CoinDestroy(void);
void mgresultbattle_CoinUpdate(omObjData *);
void mgresultbattle_HostFly(omObjData *);
void mgresultbattle_HostDestroy(void);
void mgresultbattle_HostIdle(omObjData *);
void mgresultbattle_HostPosSet(f32 arg0, f32 arg1, f32 arg2);
void mgresultbattle_HostRotSet(f32 arg0);
void mgresultbattle_HostDispOn(void);
void mgresultbattle_HostDispOff(void);

extern ResultBattlePlayerObj mgresultbattle_hostWork;
extern ResultBattleEffect mgresultbattle_coinTbl[40];
extern omObjData *mgresultbattle_coinObj;
extern omObjFunc mgresultbattle_coinFunc;
extern const s32 mgresultbattle_coinRestWeightTbl[];

s32 mgresultbattle_coinHitTbl[4] = { 0 };

void mgresultbattle_CoinProc(void) {
    omObjData *obj;
    void *data;
    u16 sprite1;
    u16 sprite2;
    s32 i;

    obj = omAddObj(0x14, 0x58, 8, -1, NULL);
    mgresultbattle_coinObj = obj;

    data = DataRead(0x210026);
    sprite1 = Hu3DSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    Hu3DModelObjAttrSet(Hu3DSprModelData[sprite1].modelId, 0x70000000, 0x70000000);

    data = DataRead(0xC);
    sprite2 = Hu3DSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    Hu3DModelObjAttrSet(Hu3DSprModelData[sprite2].modelId, 0x70000000, 0x70000000);

    for (i = 0; i < 40; i++) {
        mgresultbattle_coinTbl[i].state = 1;
        mgresultbattle_coinTbl[i].unk02 = Hu3DSprModelLink(sprite1, 8);
        mgresultbattle_coinTbl[i].unk04 = Hu3DSprModelLink(sprite2, 8);
        mgresultbattle_coinTbl[i].unk08 = 0;
        mgresultbattle_coinTbl[i].unk18 = 0.0f;
        mgresultbattle_coinTbl[i].unk1C = 0.0f;
        obj->model[i + 1] = Hu3DSprModelData[mgresultbattle_coinTbl[i].unk02].modelId;
        Hu3DMotionSpeedSet(obj->model[i + 1], 2.0f);
        Hu3DModelScaleSet(Hu3DSprModelData[i + 1].modelId, 3.0f, 3.0f, 3.0f);
        Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        obj->model[i + 41] = Hu3DSprModelData[mgresultbattle_coinTbl[i].unk04].modelId;
        Hu3DModelScaleSet(Hu3DSprModelData[i + 41].modelId, 3.0f, 3.0f, 3.0f);
    }

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(NULL, mgresultbattle_CoinDestroy);
    mgresultbattle_coinFunc = mgresultbattle_CoinUpdate;

    while (TRUE) {
        mgresultbattle_coinFunc(obj);
        HuPrcVSleep();
    }
}

void mgresultbattle_CoinDestroy(void) {
}

void mgresultbattle_CoinHitReset(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mgresultbattle_coinHitTbl[i] = 0;
    }
}

void mgresultbattle_CoinUpdate(omObjData *obj) {
    f32 dist;
    s32 i;
    s32 j;

    for (i = 0; i < 40; i++) {
        switch (mgresultbattle_coinTbl[i].state) {
            case 1:
                break;
            case 4:
                if (--mgresultbattle_coinTbl[i].unk08 > 0) {
                    break;
                }
                mgresultbattle_coinTbl[i].state = 2;
                /* fallthrough */
            case 2:
                Hu3DModelScaleSet(obj->model[i + 1], 1.5f, 1.5f, 1.5f);
                Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelPosSet(obj->model[i + 1], mgresultbattle_coinTbl[i].x, mgresultbattle_coinTbl[i].y,
                                mgresultbattle_coinTbl[i].z);
                mgresultbattle_coinTbl[i].y -= mgresultbattle_coinTbl[i].unk18;
                mgresultbattle_coinTbl[i].unk18 += 4.0f;
                if (mgresultbattle_coinTbl[i].y <= mgresultbattle_coinTbl[i].unk1C) {
                    HuAudFXPlay(0x106);
                    for (j = 0; j < 4; j++) {
                        if (GwPlayer[mgresultbattle_playerOrderTbl[j]].stat & 1) {
                            continue;
                        }
                        if (mgresultbattle_coinHitTbl[j] != 0) {
                            continue;
                        }
                        dist = mgresultbattle_playerPosTbl[j].x - mgresultbattle_coinTbl[i].x;
                        if ((dist > 0.0f ? dist : -(mgresultbattle_playerPosTbl[j].x - mgresultbattle_coinTbl[i].x)) <
                            100.0f) {
                            omVibrate(mgresultbattle_playerOrderTbl[j], 5, 0, 5);
                            mgresultbattle_coinHitTbl[j] = 1;
                            break;
                        }
                    }
                    mgresultbattle_coinTbl[i].state = 1;
                    Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DSprModelFrameSet(mgresultbattle_coinTbl[i].unk04, 0);
                    Hu3DModelPosSet(obj->model[i + 41], mgresultbattle_coinTbl[i].x,
                                    mgresultbattle_coinTbl[i].unk1C, mgresultbattle_coinTbl[i].z);
                    Hu3DModelAttrSet(obj->model[i + 41], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                }
                break;
        }
    }
}

void mgresultbattle_CoinDrop(f32 x, f32 y, f32 z, s32 count, f32 arg4) {
    s32 n;
    s32 i;

    n = 0;
    for (i = 0; i < 40; i++) {
        if (mgresultbattle_coinTbl[i].state == 1) {
            mgresultbattle_coinTbl[i].state = 4;
            mgresultbattle_coinTbl[i].unk08 = n++;
            mgresultbattle_coinTbl[i].x = x + (u8)(rand8() % 50);
            mgresultbattle_coinTbl[i].y = y;
            mgresultbattle_coinTbl[i].z = z + (u8)(rand8() % 50);
            mgresultbattle_coinTbl[i].unk18 = 0.0f;
            mgresultbattle_coinTbl[i].unk1C = arg4;
        }
        if (n >= count) {
            break;
        }
    }
}

const s8 mgresultbattle_coinShareDivTbl[8] = { 0, 0, 0, 1, 0, 0, 0, 0 };

const Vec mgresultbattle_hostUnusedPos = { 0.0f, 300.0f, 0.0f }; /* Unreferenced. */

void mgresultbattle_HostProc(void) {
    omObjData *itemObj;

    itemObj = omAddObj(20, 4, 8, -1, NULL);
    mgresultbattle_hostWork.obj = itemObj;
    itemObj->model[1] = Hu3DModelRead(0xA00A5, 0x2B9);
    Hu3DMotionAttrSet(itemObj->model[1], 2, 2);
    Hu3DModelAttrSet(itemObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    itemObj->model[2] = Hu3DModelRead(0x1B0000, 0x2B9);
    Hu3DModelAttrSet(itemObj->model[2], HU3D_ATTR_HOOK, HU3D_ATTR_HOOK);
    Hu3DMotionAttrSet(itemObj->model[2], 2, 2);
    Hu3DModelAttrSet(itemObj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelHookSet(itemObj->model[2], itemObj->model[1], "item_hook");
    itemObj->model[3] = Hu3DModelRead(0x130200, 0x2B9);
    Hu3DMotionAttrSet(itemObj->model[3], 2, 2);
    Hu3DModelAttrSet(itemObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    omObjMotionRead(itemObj, 0, 0xA00A6);
    omObjMotionRead(itemObj, 1, 0xA00B6);
    Hu3DMotionModelSet(itemObj->model[1], itemObj->motion[1]);
    Hu3DMotionAttrSet(itemObj->model[1], 2, 2);
    mgresultbattle_HostDispOff();
    itemObj->trans.x = 0.0f;
    itemObj->trans.y = 0.0f;
    itemObj->trans.z = 0.0f;
    Hu3DModelPosSet(itemObj->model[0], itemObj->trans.x, itemObj->trans.y, itemObj->trans.z);
    omPrcSetDestructor(NULL, mgresultbattle_HostDestroy);
    mgresultbattle_hostWork.func = mgresultbattle_HostIdle;
    while (TRUE) {
        mgresultbattle_hostWork.func(itemObj);
        HuPrcVSleep();
    }
}

void mgresultbattle_HostDestroy(void) {
}

void mgresultbattle_HostIdle(omObjData *object) {
}

void mgresultbattle_HostFlyStart(void) {
    mgresultbattle_hostWork.func = mgresultbattle_HostFly;
}

void mgresultbattle_HostFly(omObjData *obj) {
    s32 weights[4];
    Vec2f pos;
    f32 t;
    f32 angle;
    f32 rot;
    s32 count;
    s32 player;
    s32 total;
    s32 r;
    s32 i;

    player = 3;
    mgresultbattle_HostDispOn();
    rot = 0.0f;
    HuAudFXPlay(0x25B);
    t = rot;
    mgresultbattle_CoinHitReset();
    for (i = 0; i < 60; i++) {
        angle = t * 2.6666667f + 10.0f;
        t += 1.0f;
        pos.x = cosdf(angle) * 750.0f;
        pos.y = -sindf(angle) * 400.0f;
        mgresultbattle_HostPosSet(pos.x + 0.0f, pos.y + 950.0f, 0.0f);
        mgresultbattle_HostRotSet(sindf(rot) * 25.0f);
        rot += 1.5f;
        if (player >= 0 && pos.x + 0.0f <= mgresultbattle_playerPosTbl[player].x) {
            count = GwPlayer[mgresultbattle_playerOrderTbl[player]].gameCoin;
            if (count > 0) {
                if (count > 10) {
                    count = 10;
                }
                mgresultbattle_CoinDrop(
                    mgresultbattle_playerPosTbl[player].x, pos.y + 950.0f + 0.0f, 0.0f, count,
                    Hu3DData[mgresultbattle_playerWorkTbl[player].obj->model[1]].pos.y + 160.0f);
            }
            player--;
        }
        HuPrcVSleep();
    }

    rot = 0.0f;
    if (mgresultbattle_coinRest > 0) {
        HuPrcSleep(30);
        mgresultbattle_CoinHitReset();
        total = 0;
        for (i = 0; i < 4; i++) {
            weights[i] = mgresultbattle_coinRestWeightTbl[GwPlayer[i].bonusCoin];
            total += weights[i];
        }
        r = rand16() % total + 1;
        total = 0;
        player = 4;
        for (i = 0; i < 4; i++) {
            total += weights[i];
            if (total >= r) {
                player = i;
                break;
            }
        }
        GwPlayer[mgresultbattle_playerOrderTbl[player]].gameCoin += mgresultbattle_coinRest;

        t = 0.0f;
        for (i = 0; i < 40; i++) {
            angle = t * 4.0f + 10.0f;
            t += 1.0f;
            pos.x = -cosdf(angle) * 750.0f;
            pos.y = -sindf(angle) * 400.0f;
            mgresultbattle_HostPosSet(pos.x + 0.0f, pos.y + 950.0f, 0.0f);
            mgresultbattle_HostRotSet(-sindf(rot) * 25.0f);
            rot += 1.5f;
            if (player >= 0 && pos.x + 0.0f >= mgresultbattle_playerPosTbl[player].x) {
                count = mgresultbattle_coinRest;
                if (count > 0) {
                    if (count > 10) {
                        count = 10;
                    }
                    mgresultbattle_CoinDrop(
                        mgresultbattle_playerPosTbl[player].x, pos.y + 950.0f + 0.0f, 0.0f, count,
                        Hu3DData[mgresultbattle_playerWorkTbl[player].obj->model[1]].pos.y + 160.0f);
                }
                player = -1;
            }
            HuPrcVSleep();
        }
    }
    mgresultbattle_HostDispOff();
    mgresultbattle_CoinNumShowStart();
    mgresultbattle_hostWork.func = mgresultbattle_HostIdle;
}

void mgresultbattle_HostPosSet(f32 arg0, f32 arg1, f32 arg2) {
    omObjData *itemObj = mgresultbattle_hostWork.obj;

    Hu3DModelPosSet(itemObj->model[1], arg0, arg1, arg2);
    Hu3DModelPosSet(itemObj->model[3], arg0, arg1, arg2);
}

void mgresultbattle_HostRotSet(f32 arg0) {
    omObjData *itemObj = mgresultbattle_hostWork.obj;

    Hu3DModelRotSet(itemObj->model[1], 0.0f, 0.0f, arg0);
    Hu3DModelRotSet(itemObj->model[3], 0.0f, 0.0f, arg0);
}

void mgresultbattle_HostDispOn(void) {
    omObjData *itemObj = mgresultbattle_hostWork.obj;

    Hu3DModelAttrSet(itemObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(itemObj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(itemObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void mgresultbattle_HostDispOff(void) {
    omObjData *itemObj = mgresultbattle_hostWork.obj;

    Hu3DModelAttrSet(itemObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(itemObj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(itemObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

const s32 mgresultbattle_coinRestWeightTbl[] = { 10, 20, 30, 40 };

const Vec mgresultbattle_playerPosTbl[4] = {
    { -450.0f, 0.0f, 0.0f },
    { -150.0f, 0.0f, 0.0f },
    { 150.0f, 0.0f, 0.0f },
    { 450.0f, 0.0f, 0.0f }
};
