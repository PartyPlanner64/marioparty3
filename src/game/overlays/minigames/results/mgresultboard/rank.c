#include "common.h"
#include "mgresultboard.h"

extern UnkTemp mgresultboard_rankFlapTbl[];
extern PlayerResult mgresultboard_resultTbl[4];

extern omObjData *mgresultboard_rankObj;
extern void (*mgresultboard_rankFunc)(omObjData *);
extern s32 mgresultboard_rankAnimTbl[8];
extern s32 mgresultboard_initDoneF;
extern f32 mgresultboard_speed;

void mgresultboard_RankUpdate(omObjData *);
void mgresultboard_RankDestroy(void);
void mgresultboard_RankFlapInit(void);
void mgresultboard_RankFlapSetAll(omObjData *);
s32 mgresultboard_RankFlapSet(omObjData *, s8, s8);
void mgresultboard_RankFlapUpdate(omObjData *);

Vec mgresultboard_rankPosTbl[4] = {
    { -142.5f, 90.0f, 0.0f },
    { -142.5f, 30.0f, 0.0f },
    { -142.5f, -30.0f, 0.0f },
    { -142.5f, -90.0f, 0.0f }
};

void mgresultboard_RankProc(void) {
    omObjData *obj;
    void *modelData;
    void *animData;
    s32 anim;
    s32 i;

    anim = 0;
    obj = omAddObj(0x14, 0xC, 0, -1, NULL);
    mgresultboard_rankObj = obj;
    modelData = DataRead(0x180003);
    for (i = 0; i < 8; i++) {
        obj->model[i + 1] = Hu3DModelCreate(modelData, 0x2A0);
        Hu3DMotionAttrSet(obj->model[i + 1], 2, 0);
        Hu3DMotionAttrSet(obj->model[i + 1], 1, 0);
        Hu3DModelCameraSet(obj->model[i + 1], 2);
        Hu3DModelPosSet(obj->model[i + 1], mgresultboard_rankPosTbl[i & 3].x, mgresultboard_rankPosTbl[i & 3].y,
                        mgresultboard_rankPosTbl[i & 3].z);
        if (i == 0) {
            animData = DataRead(0x180007);
            anim = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, animData, 0, "y004_010_DEF");
            mgresultboard_rankAnimTbl[0] = anim;
            HuMemMemoryFreePerm(animData);
        } else {
            mgresultboard_rankAnimTbl[i] =
                Hu3DAnimLink(Hu3DData[obj->model[i + 1]].hmf, anim, 0, "y004_010_DEF");
        }
        Hu3DAnimAttrSet(mgresultboard_rankAnimTbl[i], 1, 1);
        Hu3DModelRemakeStatic(obj->model[i + 1]);
        Hu3DModelDynamicFree(obj->model[i + 1]);
        if (i < 4) {
            Hu3DMotionTimeSet(obj->model[i + 1], 40.0f);
            Hu3DAnimBankSet(mgresultboard_rankAnimTbl[i], mgresultboard_resultTbl[i].rank);
        } else {
            Hu3DMotionTimeSet(obj->model[i + 1], 20.0f);
            Hu3DAnimBankSet(mgresultboard_rankAnimTbl[i], rand8() & 3);
        }
    }
    HuMemMemoryFreePerm(modelData);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    mgresultboard_RankFlapInit();
    omPrcSetDestructor(0, mgresultboard_RankDestroy);
    while (mgresultboard_initDoneF == 0) {
        HuPrcVSleep();
    }
    mgresultboard_RankFlapSetAll(obj);
    mgresultboard_rankFunc = mgresultboard_RankUpdate;
    while (TRUE) {
        mgresultboard_rankFunc(obj);
        HuPrcVSleep();
    }
}

void mgresultboard_RankUpdate(omObjData *arg0) {
    mgresultboard_RankFlapUpdate(arg0);
}

void mgresultboard_RankDestroy(void) {
}

void mgresultboard_RankFlapInit(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        mgresultboard_rankFlapTbl[i].unk_00 = 0;
        mgresultboard_rankFlapTbl[i].unk_02 = 0;
        mgresultboard_rankFlapTbl[i].unk_04 = -1;
        mgresultboard_rankFlapTbl[i].unk_06 = i;
        mgresultboard_rankFlapTbl[i].unk_08 = i + 4;
        mgresultboard_rankFlapTbl[i].unk_0A = 0;
    }
}

void mgresultboard_RankFlapSetAll(omObjData *arg0) {
    s8 i;

    for (i = 0; i < 4; i++) {
        mgresultboard_RankFlapSet(arg0, i, mgresultboard_resultTbl[i].rank);
    }
}

s32 mgresultboard_RankFlapSet(omObjData *arg0, s8 arg1, s8 arg2) {
    mgresultboard_rankFlapTbl[arg1].unk_02 = arg2;
    mgresultboard_rankFlapTbl[arg1].unk_04 = -1;
    mgresultboard_rankFlapTbl[arg1].unk_00 = 0;
    return 1;
}

void mgresultboard_RankFlapUpdate(omObjData *obj) {
    s16 cur;
    s16 next;
    s16 model;
    s16 temp;
    f32 time;
    f32 endTime;
    s8 i;

    for (i = 0; i < 4; i++) {
        next = mgresultboard_rankFlapTbl[i].unk_08;
        cur = mgresultboard_rankFlapTbl[i].unk_06;
        model = obj->model[cur + 1];
        time = Hu3DData[model].motTime;
        endTime = Hu3DMotion[Hu3DData[model].motId].unk02;
        switch (mgresultboard_rankFlapTbl[i].unk_00) {
            case 1:
                if (cur >= 0) {
                    Hu3DMotionAttrSet(model, 1, 0);
                    Hu3DModelAttrSet(obj->model[cur + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DMotionSpeedSet(obj->model[cur + 1], mgresultboard_speed);
                }
                if (next >= 0) {
                    Hu3DMotionAttrSet(obj->model[next + 1], 1, 0);
                    Hu3DModelAttrSet(obj->model[next + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DMotionSpeedSet(obj->model[next + 1], mgresultboard_speed);
                }
                if (mgresultboard_rankFlapTbl[i].unk_04 >= 0) {
                    if (endTime <= time) {
                        Hu3DAnimBankSet(mgresultboard_rankAnimTbl[next], mgresultboard_rankFlapTbl[i].unk_04);
                        mgresultboard_rankFlapTbl[i].unk_02 = mgresultboard_rankFlapTbl[i].unk_04;
                        mgresultboard_rankFlapTbl[i].unk_04 = -1;
                        if (cur >= 0) {
                            Hu3DMotionTimeSet(obj->model[cur + 1], 0.0f);
                        }
                        if (next >= 0) {
                            Hu3DMotionTimeSet(obj->model[next + 1], 20.0f);
                        }
                        temp = mgresultboard_rankFlapTbl[i].unk_06;
                        mgresultboard_rankFlapTbl[i].unk_06 = mgresultboard_rankFlapTbl[i].unk_08;
                        mgresultboard_rankFlapTbl[i].unk_08 = temp;
                    }
                    break;
                }
                mgresultboard_rankFlapTbl[i].unk_00 = 0;
            case 0:
                if (endTime <= time) {
                    if (next >= 0) {
                        Hu3DMotionTimeSet(obj->model[next + 1], 20.0f);
                        Hu3DMotionAttrSet(obj->model[next + 1], 1, 1);
                        Hu3DModelAttrSet(obj->model[next + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                    if (cur >= 0) {
                        Hu3DAnimBankSet(mgresultboard_rankAnimTbl[cur], mgresultboard_rankFlapTbl[i].unk_02);
                        Hu3DMotionTimeSet(obj->model[cur + 1], endTime);
                        Hu3DMotionAttrSet(obj->model[cur + 1], 1, 1);
                    }
                }
                break;
        }
    }
}

s32 mgresultboard_RankFlapFlip(omObjData *arg0, s8 arg1, s8 arg2) {
    if (mgresultboard_rankFlapTbl[arg1].unk_04 >= 0) {
        return 0;
    }

    mgresultboard_rankFlapTbl[arg1].unk_04 = arg2;

    if (mgresultboard_rankFlapTbl[arg1].unk_08 >= 0) {
        Hu3DModelAttrSet(arg0->model[mgresultboard_rankFlapTbl[arg1].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }

    mgresultboard_rankFlapTbl[arg1].unk_00 = 1;
    return 1;
}
