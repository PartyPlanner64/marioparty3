#include "common.h"
#include "mgresultboard.h"

extern omObjData *mgresultboard_starIconObj;
extern s32 mgresultboard_initDoneF;
extern void (*mgresultboard_starIconFunc)(omObjData *);

void mgresultboard_StarIconIdle(omObjData *);
void mgresultboard_StarIconDestroy(void);

Vec mgresultboard_starIconPosTbl[4] = {
    { -19.0f, 90.0f, 0.0f },
    { -19.0f, 30.0f, 0.0f },
    { -19.0f, -30.0f, 0.0f },
    { -19.0f, -90.0f, 0.0f }
};

void mgresultboard_StarIconProc(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x14, 0xC, 0, -1, NULL);
    mgresultboard_starIconObj = obj;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            obj->model[1] = Hu3DModelRead3(0x180002, 0x2B9);
        } else {
            obj->model[i + 1] = Hu3DModelLink(obj->model[1]);
        }
        Hu3DMotionAttrSet(obj->model[i + 1], 2, 0);
        Hu3DModelPosSet(obj->model[i + 1], mgresultboard_starIconPosTbl[i].x, mgresultboard_starIconPosTbl[i].y,
                        mgresultboard_starIconPosTbl[i].z);
        Hu3DMotionTimeSet(obj->model[i + 1], 0.0f);
        Hu3DModelCameraSet(obj->model[i + 1], HU3D_CAM1);
        Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    omPrcSetDestructor(0, mgresultboard_StarIconDestroy);
    while (mgresultboard_initDoneF == 0) {
        HuPrcVSleep();
    }
    mgresultboard_starIconFunc = mgresultboard_StarIconIdle;
    while (TRUE) {
        mgresultboard_starIconFunc(obj);
        HuPrcVSleep();
    }
}

void mgresultboard_StarIconIdle(omObjData *arg0) {
}

void mgresultboard_StarIconDestroy(void) {
}
