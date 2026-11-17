#include "common.h"
#include "mgresultboard.h"

extern omObjData *mgresultboard_coinIconObj;
extern s32 mgresultboard_initDoneF;
extern void (*mgresultboard_coinIconFunc)(omObjData *);

void mgresultboard_CoinIconIdle(omObjData *);
void mgresultboard_CoinIconDestroy(void);

Vec mgresultboard_coinIconPosTbl[4] = {
    { 86.0f, 90.0f, 0.0f },
    { 86.0f, 30.0f, 0.0f },
    { 86.0f, -30.0f, 0.0f },
    { 86.0f, -90.0f, 0.0f }
};

void mgresultboard_CoinIconProc(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x14, 0xE, 0, -1, NULL);
    mgresultboard_coinIconObj = obj;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            obj->model[1] = Hu3DModelRead3(0x180001, 0x2B9);
        } else {
            obj->model[i + 1] = Hu3DModelLink(obj->model[1]);
        }
        Hu3DMotionAttrSet(obj->model[i + 1], 2, 0);
        Hu3DModelPosSet(obj->model[i + 1], mgresultboard_coinIconPosTbl[i].x, mgresultboard_coinIconPosTbl[i].y,
                        mgresultboard_coinIconPosTbl[i].z);
        Hu3DMotionTimeSet(obj->model[i + 1], 0.0f);
        Hu3DModelCameraSet(obj->model[i + 1], HU3D_CAM1);
        Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    omPrcSetDestructor(0, mgresultboard_CoinIconDestroy);
    while (mgresultboard_initDoneF == 0) {
        HuPrcVSleep();
    }
    mgresultboard_coinIconFunc = mgresultboard_CoinIconIdle;
    while (TRUE) {
        mgresultboard_coinIconFunc(obj);
        HuPrcVSleep();
    }
}

void mgresultboard_CoinIconIdle(omObjData *arg0) {
}

void mgresultboard_CoinIconDestroy(void) {
}
