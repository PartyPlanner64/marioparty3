#include "common.h"
#include "mgresultboard.h"

extern UnkTemp mgresultboard_scoreFlapTbl[4][5];
extern UnkTemp mgresultboard_faceFlapTbl[];
extern PlayerResult mgresultboard_resultTbl[4];
extern s32 mgresultboard_faceAnimTbl[8];
extern f32 mgresultboard_speed;
extern s32 mgresultboard_initDoneF;
extern omObjData *mgresultboard_faceObj;
extern void (*mgresultboard_faceFunc)(omObjData *);
extern omObjData *mgresultboard_scoreObj;
extern void (*mgresultboard_scoreFunc)(omObjData *);
extern s32 mgresultboard_scoreAnimTbl[40];
extern s32 mgresultboard_scoreAnimDataTbl[2];

void mgresultboard_FaceFlapInit(void);
void mgresultboard_FaceFlapSetAll(omObjData *);
void mgresultboard_FaceUpdate(omObjData *);
void mgresultboard_FaceDestroy(void);
s32 mgresultboard_FaceFlapSet(omObjData *, s8, s8, s8);
void mgresultboard_FaceFlapUpdate(omObjData *);
void mgresultboard_ScoreIdle(omObjData *);
void mgresultboard_ScoreFlapSetAll(omObjData *);
void mgresultboard_ScoreFlapUpdate(omObjData *);
void mgresultboard_ScoreDestroy(void);
void mgresultboard_ScoreFlapInit(void);
s32 mgresultboard_StarSet(omObjData *, s8, s16);
s32 mgresultboard_CoinSet(omObjData *, s8, s16);
void mgresultboard_HmfAnimIdxSet(s16, s16, s16);

Vec mgresultboard_facePosTbl[4] = {
    { -84.0f, 90.0f, 0.0f },
    { -84.0f, 30.0f, 0.0f },
    { -84.0f, -30.0f, 0.0f },
    { -84.0f, -90.0f, 0.0f }
};

Vec mgresultboard_starDigitPosTbl[8] = {
    { 16.0f, 90.0f, 0.0f },
    { 36.0f, 90.0f, 0.0f },
    { 16.0f, 30.0f, 0.0f },
    { 36.0f, 30.0f, 0.0f },
    { 16.0f, -30.0f, 0.0f },
    { 36.0f, -30.0f, 0.0f },
    { 16.0f, -90.0f, 0.0f },
    { 36.0f, -90.0f, 0.0f }
};

Vec mgresultboard_coinDigitPosTbl[12] = {
    { 121.0f, 90.0f, 0.0f },
    { 141.0f, 90.0f, 0.0f },
    { 161.0f, 90.0f, 0.0f },
    { 121.0f, 30.0f, 0.0f },
    { 141.0f, 30.0f, 0.0f },
    { 161.0f, 30.0f, 0.0f },
    { 121.0f, -30.0f, 0.0f },
    { 141.0f, -30.0f, 0.0f },
    { 161.0f, -30.0f, 0.0f },
    { 121.0f, -90.0f, 0.0f },
    { 141.0f, -90.0f, 0.0f },
    { 161.0f, -90.0f, 0.0f }
};

const u8 mgresultboard_faceBankTbl[8][3] = {
    { 0, 1, 2 },
    { 3, 4, 5 },
    { 6, 7, 8 },
    { 9, 10, 11 },
    { 12, 13, 14 },
    { 15, 16, 17 },
    { 18, 19, 20 },
    { 21, 22, 23 }
};

void mgresultboard_FaceProc(void) {
    omObjData *obj;
    void *modelData;
    void *animData;
    s32 anim;
    s32 i;

    anim = 0;
    obj = omAddObj(0x14, 0xC, 0, -1, NULL);
    mgresultboard_faceObj = obj;
    modelData = DataRead(0x180004);
    for (i = 0; i < 8; i++) {
        obj->model[i + 1] = Hu3DModelCreate(modelData, 0x2A0);
        Hu3DMotionAttrSet(obj->model[i + 1], 2, 0);
        Hu3DModelPosSet(obj->model[i + 1], mgresultboard_facePosTbl[i & 3].x, mgresultboard_facePosTbl[i & 3].y,
                        mgresultboard_facePosTbl[i & 3].z);
        Hu3DModelCameraSet(obj->model[i + 1], 2);
        if (i == 0) {
            animData = DataRead(0x180008);
            anim = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, animData, 0, "ys04_04_DEF");
            mgresultboard_faceAnimTbl[0] = anim;
            HuMemMemoryFreePerm(animData);
        } else {
            mgresultboard_faceAnimTbl[i] = Hu3DAnimLink(Hu3DData[obj->model[i + 1]].hmf, anim, 0, "ys04_04_DEF");
        }
        Hu3DModelRemakeStatic(obj->model[i + 1]);
        Hu3DModelDynamicFree(obj->model[i + 1]);
        Hu3DAnimAttrSet(mgresultboard_faceAnimTbl[i], 1, 1);
        Hu3DAnimBankSet(mgresultboard_faceAnimTbl[i], mgresultboard_faceBankTbl[i][0]);
        if (i < 4) {
            Hu3DMotionTimeSet(obj->model[i + 1], 40.0f);
            Hu3DAnimBankSet(mgresultboard_faceAnimTbl[i],
                            mgresultboard_faceBankTbl[mgresultboard_resultTbl[i].chr][mgresultboard_resultTbl[i].unk_03]);
        } else {
            Hu3DMotionTimeSet(obj->model[i + 1], 20.0f);
            Hu3DAnimBankSet(mgresultboard_faceAnimTbl[i],
                            mgresultboard_faceBankTbl[mgresultboard_resultTbl[rand8() & 3].chr][rand8() % 3]);
        }
    }
    HuMemMemoryFreePerm(modelData);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    mgresultboard_FaceFlapInit();
    omPrcSetDestructor(0, mgresultboard_FaceDestroy);
    while (mgresultboard_initDoneF == 0) {
        HuPrcVSleep();
    }
    mgresultboard_faceFunc = mgresultboard_FaceUpdate;
    mgresultboard_FaceFlapSetAll(obj);
    while (TRUE) {
        mgresultboard_faceFunc(obj);
        HuPrcVSleep();
    }
}

void mgresultboard_FaceFlapInit(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        mgresultboard_faceFlapTbl[i].unk_00 = 0;
        mgresultboard_faceFlapTbl[i].unk_02 = 0;
        mgresultboard_faceFlapTbl[i].unk_04 = -1;
        mgresultboard_faceFlapTbl[i].unk_06 = i;
        mgresultboard_faceFlapTbl[i].unk_08 = i + 4;
        mgresultboard_faceFlapTbl[i].unk_0A = 0;
    }
}

void mgresultboard_FaceFlapSetAll(omObjData *arg0) {
    s8 i;

    for (i = 0; i < 4; i++) {
        mgresultboard_FaceFlapSet(arg0, i, mgresultboard_resultTbl[i].chr, mgresultboard_resultTbl[i].unk_03);
    }
}

void mgresultboard_FaceUpdate(omObjData *arg0) {
    mgresultboard_FaceFlapUpdate(arg0);
}

void mgresultboard_FaceDestroy(void) {
}

s32 mgresultboard_FaceFlapSet(omObjData *arg0, s8 arg1, s8 arg2, s8 arg3) {
    mgresultboard_faceFlapTbl[arg1].unk_02 = arg2 * 3 + arg3;
    mgresultboard_faceFlapTbl[arg1].unk_04 = -1;
    mgresultboard_faceFlapTbl[arg1].unk_00 = 0;
    return 1;
}

s32 mgresultboard_FaceFlapFlip(omObjData *arg0, s8 arg1, s8 arg2, s8 arg3) {
    if (mgresultboard_faceFlapTbl[arg1].unk_04 >= 0) {
        return 0;
    }
    mgresultboard_faceFlapTbl[arg1].unk_04 = arg2 * 3 + arg3;
    if (mgresultboard_faceFlapTbl[arg1].unk_08 >= 0) {
        Hu3DModelAttrSet(arg0->model[mgresultboard_faceFlapTbl[arg1].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    mgresultboard_faceFlapTbl[arg1].unk_00 = 1;
    return 1;
}

void mgresultboard_FaceFlapUpdate(omObjData *obj) {
    s16 cur;
    s16 next;
    s16 model;
    s16 temp;
    f32 time;
    f32 endTime;
    s8 i;

    for (i = 0; i < 4; i++) {
        next = mgresultboard_faceFlapTbl[i].unk_08;
        cur = mgresultboard_faceFlapTbl[i].unk_06;
        model = obj->model[cur + 1];
        time = Hu3DData[model].motTime;
        endTime = Hu3DMotion[Hu3DData[model].motId].unk02;
        switch (mgresultboard_faceFlapTbl[i].unk_00) {
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
                if (mgresultboard_faceFlapTbl[i].unk_04 >= 0) {
                    if (endTime <= time) {
                        Hu3DAnimBankSet(mgresultboard_faceAnimTbl[next], mgresultboard_faceFlapTbl[i].unk_04);
                        mgresultboard_faceFlapTbl[i].unk_02 = mgresultboard_faceFlapTbl[i].unk_04;
                        mgresultboard_faceFlapTbl[i].unk_04 = -1;
                        if (cur >= 0) {
                            Hu3DMotionTimeSet(obj->model[cur + 1], 0.0f);
                        }
                        if (next >= 0) {
                            Hu3DMotionTimeSet(obj->model[next + 1], 20.0f);
                        }
                        temp = mgresultboard_faceFlapTbl[i].unk_06;
                        mgresultboard_faceFlapTbl[i].unk_06 = mgresultboard_faceFlapTbl[i].unk_08;
                        mgresultboard_faceFlapTbl[i].unk_08 = temp;
                    }
                    break;
                }
                mgresultboard_faceFlapTbl[i].unk_00 = 0;
            case 0:
                if (endTime <= time) {
                    if (cur >= 0) {
                        Hu3DMotionTimeSet(obj->model[next + 1], 20.0f);
                        Hu3DMotionAttrSet(obj->model[next + 1], 1, 1);
                        Hu3DModelAttrSet(obj->model[next + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        Hu3DAnimBankSet(mgresultboard_faceAnimTbl[next], mgresultboard_faceFlapTbl[i].unk_02);
                    }
                    if (next >= 0) {
                        Hu3DMotionTimeSet(obj->model[cur + 1], endTime);
                        Hu3DMotionAttrSet(obj->model[cur + 1], 1, 1);
                    }
                }
                break;
        }
    }
}

void mgresultboard_ScoreProc(void) {
    omObjData *obj;
    void *data;
    s32 i;

    obj = omAddObj(0x14, 0x32, 0, -1, NULL);
    mgresultboard_scoreObj = obj;
    obj->model[1] = Hu3DModelRead3(0x180000, 0x2A8);
    data = DataRead(0x180005);
    mgresultboard_scoreAnimTbl[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, "zero_DEF");
    HuMemMemoryFreePerm(data);
    mgresultboard_scoreAnimDataTbl[0] = Hu3DAnimData[mgresultboard_scoreAnimTbl[0]].animIdx;
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mgresultboard_scoreAnimTbl[0], 1, 1);
    Hu3DAnimBankSet(mgresultboard_scoreAnimTbl[0], 0);
    Hu3DModelCameraSet(obj->model[1], 2);
    data = DataRead(0x180006);
    mgresultboard_scoreAnimDataTbl[1] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0x180000);
    for (i = 1; i < 40; i++) {
        obj->model[i + 1] = Hu3DModelCreate(data, 0x2A0);
        Hu3DModelCameraSet(obj->model[i + 1], 2);
        mgresultboard_scoreAnimTbl[i] =
            Hu3DAnimLink(Hu3DData[obj->model[i + 1]].hmf, mgresultboard_scoreAnimTbl[0], 0, "zero_DEF");
        Hu3DModelRemakeStatic(obj->model[i + 1]);
        Hu3DModelDynamicFree(obj->model[i + 1]);
        Hu3DAnimAttrSet(mgresultboard_scoreAnimTbl[i], 1, 1);
        Hu3DAnimBankSet(mgresultboard_scoreAnimTbl[i], 0);
    }
    HuMemMemoryFreePerm(data);
    for (i = 0; i < 8; i++) {
        Hu3DModelPosSet(obj->model[i + 1], mgresultboard_starDigitPosTbl[i].x, mgresultboard_starDigitPosTbl[i].y,
                        mgresultboard_starDigitPosTbl[i].z);
        Hu3DMotionTimeSet(obj->model[i + 1], 40.0f);
        Hu3DMotionAttrSet(obj->model[i + 1], 2, 0);
        Hu3DModelPosSet(obj->model[i + 21], mgresultboard_starDigitPosTbl[i].x, mgresultboard_starDigitPosTbl[i].y,
                        mgresultboard_starDigitPosTbl[i].z);
        Hu3DMotionTimeSet(obj->model[i + 21], 20.0f);
        Hu3DMotionAttrSet(obj->model[i + 21], 2, 0);
    }
    for (i = 0; i < 12; i++) {
        Hu3DModelPosSet(obj->model[i + 9], mgresultboard_coinDigitPosTbl[i].x, mgresultboard_coinDigitPosTbl[i].y,
                        mgresultboard_coinDigitPosTbl[i].z);
        Hu3DMotionTimeSet(obj->model[i + 9], 40.0f);
        Hu3DMotionAttrSet(obj->model[i + 9], 2, 0);
        Hu3DModelPosSet(obj->model[i + 29], mgresultboard_coinDigitPosTbl[i].x, mgresultboard_coinDigitPosTbl[i].y,
                        mgresultboard_coinDigitPosTbl[i].z);
        Hu3DMotionTimeSet(obj->model[i + 29], 20.0f);
        Hu3DMotionAttrSet(obj->model[i + 29], 2, 0);
    }
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    mgresultboard_ScoreFlapInit();
    omPrcSetDestructor(0, mgresultboard_ScoreDestroy);
    while (mgresultboard_initDoneF == 0) {
        HuPrcVSleep();
    }
    mgresultboard_scoreFunc = mgresultboard_ScoreIdle;
    mgresultboard_ScoreFlapSetAll(obj);
    while (TRUE) {
        mgresultboard_scoreFunc(obj);
        mgresultboard_ScoreFlapUpdate(obj);
        HuPrcVSleep();
    }
}

void mgresultboard_ScoreIdle(omObjData *arg0) {
}

void mgresultboard_ScoreFlapSetAll(omObjData *arg0) {
    s8 i;

    for (i = 0; i < 4; i++) {
        mgresultboard_StarSet(arg0, i, mgresultboard_resultTbl[i].star);
        mgresultboard_CoinSet(arg0, i, mgresultboard_resultTbl[i].coin);
    }
}

void mgresultboard_ScoreFlapUpdate(omObjData *obj) {
    f32 time;
    f32 maxTime;
    s16 nextModel;
    s16 curModel;
    s16 model;
    s8 i;
    s8 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            nextModel = mgresultboard_scoreFlapTbl[i][j].unk_08;
            curModel = mgresultboard_scoreFlapTbl[i][j].unk_06;
            model = obj->model[curModel + 1];
            time = Hu3DData[model].motTime;
            maxTime = Hu3DMotion[Hu3DData[model].motId].unk02;
            switch (mgresultboard_scoreFlapTbl[i][j].unk_00) {
                case 1:
                    if (curModel >= 0) {
                        Hu3DMotionAttrSet(obj->model[curModel + 1], 1, 0);
                        Hu3DModelAttrSet(obj->model[curModel + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DMotionSpeedSet(obj->model[curModel + 1], mgresultboard_speed);
                    }
                    if (nextModel >= 0) {
                        Hu3DMotionAttrSet(obj->model[nextModel + 1], 1, 0);
                        Hu3DModelAttrSet(obj->model[nextModel + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DMotionSpeedSet(obj->model[nextModel + 1], mgresultboard_speed);
                    }
                    if (mgresultboard_scoreFlapTbl[i][j].unk_04 >= 0) {
                        if (time >= maxTime) {
                            Hu3DAnimBankSet(mgresultboard_scoreAnimTbl[nextModel],
                                            mgresultboard_scoreFlapTbl[i][j].unk_04);
                            mgresultboard_scoreFlapTbl[i][j].unk_02 = mgresultboard_scoreFlapTbl[i][j].unk_04;
                            mgresultboard_scoreFlapTbl[i][j].unk_04 = -1;
                            if (curModel >= 0) {
                                Hu3DMotionTimeSet(obj->model[curModel + 1], 0.0f);
                            }
                            if (nextModel >= 0) {
                                Hu3DMotionTimeSet(obj->model[nextModel + 1], 20.0f);
                            }
                            model = mgresultboard_scoreFlapTbl[i][j].unk_06;
                            mgresultboard_scoreFlapTbl[i][j].unk_06 = mgresultboard_scoreFlapTbl[i][j].unk_08;
                            mgresultboard_scoreFlapTbl[i][j].unk_08 = model;
                            if (mgresultboard_scoreFlapTbl[i][j].unk_0A == 0) {
                                mgresultboard_HmfAnimIdxSet(obj->model[nextModel + 1],
                                                            mgresultboard_scoreAnimTbl[nextModel],
                                                            mgresultboard_scoreAnimDataTbl[0]);
                            } else {
                                mgresultboard_HmfAnimIdxSet(obj->model[nextModel + 1],
                                                            mgresultboard_scoreAnimTbl[nextModel],
                                                            mgresultboard_scoreAnimDataTbl[1]);
                            }
                        }
                        break;
                    }
                    mgresultboard_scoreFlapTbl[i][j].unk_00 = 0;
                    /* fallthrough */
                case 0:
                    if (time >= maxTime) {
                        if (nextModel >= 0) {
                            Hu3DMotionTimeSet(obj->model[nextModel + 1], 20.0f);
                            Hu3DMotionAttrSet(obj->model[nextModel + 1], 1, 1);
                            Hu3DModelAttrSet(obj->model[nextModel + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        }
                        if (curModel >= 0) {
                            Hu3DAnimBankSet(mgresultboard_scoreAnimTbl[curModel],
                                            mgresultboard_scoreFlapTbl[i][j].unk_02);
                            Hu3DMotionTimeSet(obj->model[curModel + 1], maxTime);
                            Hu3DMotionAttrSet(obj->model[curModel + 1], 1, 1);
                        }
                    }
                    break;
            }
        }
    }
}

void mgresultboard_ScoreDestroy(void) {
}

void mgresultboard_ScoreFlapInit(void) {
    static const s16 mgresultboard_scoreFlapMdlTbl[4][5] = {
        { 0, 1, 8, 9, 10 },
        { 2, 3, 11, 12, 13 },
        { 4, 5, 14, 15, 16 },
        { 6, 7, 17, 18, 19 },
    };
    s8 i;
    s8 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            mgresultboard_scoreFlapTbl[i][j].unk_00 = 0;
            mgresultboard_scoreFlapTbl[i][j].unk_02 = 0;
            mgresultboard_scoreFlapTbl[i][j].unk_04 = -1;
            mgresultboard_scoreFlapTbl[i][j].unk_06 = mgresultboard_scoreFlapMdlTbl[i][j];
            mgresultboard_scoreFlapTbl[i][j].unk_08 = mgresultboard_scoreFlapMdlTbl[i][j] + 20;
            mgresultboard_scoreFlapTbl[i][j].unk_0A = 0;
        }
        for (; j < 5; j++) {
            mgresultboard_scoreFlapTbl[i][j].unk_00 = 0;
            mgresultboard_scoreFlapTbl[i][j].unk_02 = 0;
            mgresultboard_scoreFlapTbl[i][j].unk_04 = -1;
            mgresultboard_scoreFlapTbl[i][j].unk_06 = mgresultboard_scoreFlapMdlTbl[i][j];
            mgresultboard_scoreFlapTbl[i][j].unk_08 = mgresultboard_scoreFlapMdlTbl[i][j] + 20;
            mgresultboard_scoreFlapTbl[i][j].unk_0A = 0;
        }
    }
}

s32 mgresultboard_StarFlip(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[2];
    s16 value;
    s8 i;

    if (mgresultboard_scoreFlapTbl[arg1][0].unk_04 >= 0) {
        return 0;
    }
    if (arg2 >= 100) {
        arg2 = 99;
    }
    value = (arg2 < 0) ? 0 : arg2;
    digits[0] = (value / 10) % 10;
    digits[1] = value % 10;
    if (digits[0] == 0) {
        digits[0] = 11;
    }
    for (i = 0; i < 2; i++) {
        mgresultboard_scoreFlapTbl[arg1][i].unk_04 = digits[i];
        if (mgresultboard_scoreFlapTbl[arg1][i].unk_08 >= 0) {
            Hu3DModelAttrSet(arg0->model[mgresultboard_scoreFlapTbl[arg1][i].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        mgresultboard_scoreFlapTbl[arg1][i].unk_00 = 1;
    }
    return 1;
}

s32 mgresultboard_StarPlusFlip(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[2];
    s16 value;
    s8 i;

    if (mgresultboard_scoreFlapTbl[arg1][0].unk_04 >= 0) {
        return 0;
    }
    if (arg2 >= 100) {
        arg2 = 99;
    }
    value = (arg2 < 0) ? 0 : arg2;
    digits[0] = (value / 10) % 10;
    digits[1] = value % 10;
    if (digits[0] == 0) {
        digits[0] = 10;
    }
    for (i = 0; i < 2; i++) {
        mgresultboard_scoreFlapTbl[arg1][i].unk_04 = digits[i];
        if (mgresultboard_scoreFlapTbl[arg1][i].unk_08 >= 0) {
            Hu3DModelAttrSet(arg0->model[mgresultboard_scoreFlapTbl[arg1][i].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        mgresultboard_scoreFlapTbl[arg1][i].unk_00 = 1;
    }
    return 1;
}

s32 mgresultboard_StarFlipStop(s32 arg0, s8 arg1) {
    s8 i;

    if (mgresultboard_scoreFlapTbl[arg1][0].unk_04 >= 0) {
        return 0;
    }

    for (i = 0; i < 2; i++) {
        mgresultboard_scoreFlapTbl[arg1][i].unk_00 = 0;
    }
    return 1;
}

s32 mgresultboard_StarFlipStart(s32 arg0, s8 arg1) {
    s8 i;

    for (i = 0; i < 2; i++) {
        mgresultboard_scoreFlapTbl[arg1][i].unk_00 = 1;
    }
    return 1;
}

s32 mgresultboard_StarSet(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[2];
    s16 value;
    s8 i;

    if (arg2 >= 100) {
        arg2 = 99;
    }
    value = (arg2 < 0) ? 0 : arg2;
    digits[0] = (value / 10) % 10;
    digits[1] = value % 10;
    if (digits[0] == 0) {
        digits[0] = 11;
    }
    for (i = 0; i < 2; i++) {
        mgresultboard_scoreFlapTbl[arg1][i].unk_02 = digits[i];
        mgresultboard_scoreFlapTbl[arg1][i].unk_04 = -1;
        mgresultboard_scoreFlapTbl[arg1][i].unk_00 = 0;
    }
    return 1;
}

s32 mgresultboard_CoinFlip(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[3];
    s16 value;
    s8 i;

    if (mgresultboard_scoreFlapTbl[arg1][2].unk_04 >= 0) {
        return 0;
    }
    if (arg2 >= 1000) {
        arg2 = 999;
    }
    value = (arg2 < 0) ? 0 : arg2;
    digits[0] = (value / 100) % 10;
    digits[1] = (value / 10) % 10;
    digits[2] = value % 10;
    if (digits[0] == 0) {
        digits[0] = 11;
    }
    for (i = 0; i < 3; i++) {
        mgresultboard_scoreFlapTbl[arg1][i + 2].unk_04 = digits[i];
        mgresultboard_scoreFlapTbl[arg1][i + 2].unk_00 = 1;
        if (mgresultboard_scoreFlapTbl[arg1][i + 2].unk_08 >= 0) {
            Hu3DModelAttrSet(arg0->model[mgresultboard_scoreFlapTbl[arg1][i + 2].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        mgresultboard_scoreFlapTbl[arg1][i + 2].unk_0A = 0;
    }
    return 1;
}

s32 mgresultboard_CoinPlusFlip(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[3];
    s16 value;
    s8 i;

    if (mgresultboard_scoreFlapTbl[arg1][2].unk_04 >= 0) {
        return 0;
    }
    if (arg2 >= 1000) {
        arg2 = 999;
    }
    value = (arg2 < 0) ? 0 : arg2;
    digits[0] = (value / 100) % 10;
    digits[1] = (value / 10) % 10;
    digits[2] = value % 10;
    if (digits[0] == 0) {
        digits[0] = 10;
    }
    for (i = 0; i < 3; i++) {
        mgresultboard_scoreFlapTbl[arg1][i + 2].unk_04 = digits[i];
        mgresultboard_scoreFlapTbl[arg1][i + 2].unk_00 = 1;
        if (mgresultboard_scoreFlapTbl[arg1][i + 2].unk_08 >= 0) {
            Hu3DModelAttrSet(arg0->model[mgresultboard_scoreFlapTbl[arg1][i + 2].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        mgresultboard_scoreFlapTbl[arg1][i + 2].unk_0A = 1;
    }
    return 1;
}

s32 mgresultboard_CoinFlipStop(s32 arg0, s8 arg1) {
    s8 i;

    if (mgresultboard_scoreFlapTbl[arg1][2].unk_04 >= 0) {
        return 0;
    }

    for (i = 0; i < 4; i++) {
        mgresultboard_scoreFlapTbl[arg1][i + 2].unk_00 = 0;
    }
    return 1;
}

s32 mgresultboard_CoinFlipStart(s32 arg0, s8 arg1) {
    s8 i;

    for (i = 0; i < 4; i++) {
        mgresultboard_scoreFlapTbl[arg1][i + 2].unk_00 = 1;
    }
    return 1;
}

s32 mgresultboard_CoinSet(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[3];
    s16 value;
    s8 i;

    if (arg2 >= 1000) {
        arg2 = 999;
    }
    value = (arg2 < 0) ? 0 : arg2;
    digits[0] = (value / 100) % 10;
    digits[1] = (value / 10) % 10;
    digits[2] = value % 10;
    if (digits[0] == 0) {
        digits[0] = 11;
    }
    for (i = 0; i < 3; i++) {
        mgresultboard_scoreFlapTbl[arg1][i + 2].unk_02 = digits[i];
        mgresultboard_scoreFlapTbl[arg1][i + 2].unk_04 = -1;
        mgresultboard_scoreFlapTbl[arg1][i + 2].unk_00 = 0;
    }
    return 1;
}

void mgresultboard_HmfAnimIdxSet(s16 model, s16 anim, s16 animIdx) {
    if (anim >= 0) {
        if (animIdx == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            HmfAnim *entry;

            Hu3DModelAnimStart(Hu3DData[model].hmf);
            entry = &Hu3DAnimData[anim];

            entry->animIdx = animIdx;
        }
    }
}
