#include "common.h"
#include "overlays/mgresultboard.h"

extern UnkTemp D_8010AEA8_mgresultboard[5][5];
extern UnkTemp D_8010AFE8_mgresultboard[];
extern PlayerResult D_8010B048_mgresultboard[4];
extern s32 D_8010ADB0_mgresultboard[8];
extern f32 D_8010AAF4_mgresultboard;
extern s32 D_8010AAF8_mgresultboard;
extern omObjData *D_8010AFA8_mgresultboard;
extern void (*D_8010AFAC_mgresultboard)(omObjData *);
extern Vec D_8010AB40_mgresultboard[4];
extern u8 D_8010AD28_mgresultboard[4][3];
extern omObjData *D_8010AEA0_mgresultboard;
extern void (*D_8010AEA4_mgresultboard)(omObjData *);
extern s32 D_8010ADD0_mgresultboard[40];
extern s32 D_8010AE70_mgresultboard[2];
extern Vec D_8010AB70_mgresultboard[8];
extern Vec D_8010ABD0_mgresultboard[12];

void func_801080C4_mgresultboard(void);
void func_80108150_mgresultboard(omObjData *);
void func_801081CC_mgresultboard(omObjData *);
void func_801081E8_mgresultboard(void);
s32 func_801081F0_mgresultboard(omObjData *, s8, s8, s8);
void func_80108330_mgresultboard(omObjData *);
void func_80108BBC_mgresultboard(omObjData *);
void func_80108BC4_mgresultboard(omObjData *);
void func_80108C60_mgresultboard(omObjData *);
void func_8010913C_mgresultboard(void);
void func_80109144_mgresultboard(void);
s32 func_80109744_mgresultboard(omObjData *, s8, s16);
s32 func_80109DAC_mgresultboard(omObjData *, s8, s16);
void func_80109F30_mgresultboard(s16, s16, s16);

void func_80107D00_mgresultboard(void) {
    omObjData *obj;
    void *modelData;
    void *animData;
    s32 anim;
    s32 i;

    anim = 0;
    obj = omAddObj(0x14, 0xC, 0, -1, NULL);
    D_8010AFA8_mgresultboard = obj;
    modelData = DataRead(0x180004);
    for (i = 0; i < 8; i++) {
        obj->model[i + 1] = Hu3DModelCreate(modelData, 0x2A0);
        func_8001C814_main(obj->model[i + 1], 2, 0);
        Hu3DModelPosSet(obj->model[i + 1], D_8010AB40_mgresultboard[i & 3].x, D_8010AB40_mgresultboard[i & 3].y,
                        D_8010AB40_mgresultboard[i & 3].z);
        Hu3DModelCameraSet(obj->model[i + 1], 2);
        if (i == 0) {
            animData = DataRead(0x180008);
            anim = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, animData, 0, "ys04_04_DEF");
            D_8010ADB0_mgresultboard[0] = anim;
            HuMemMemoryFreePerm(animData);
        } else {
            D_8010ADB0_mgresultboard[i] = HmfAnimLink(HmfModelData[obj->model[i + 1]].hmf, anim, 0, "ys04_04_DEF");
        }
        Hu3DModelRemakeStatic(obj->model[i + 1]);
        func_8001C514_main(obj->model[i + 1]);
        func_80032FC0_main(D_8010ADB0_mgresultboard[i], 1, 1);
        func_80032FF8_main(D_8010ADB0_mgresultboard[i], D_8010AD28_mgresultboard[i][0]);
        if (i < 4) {
            Hu3DMotionTimeSet(obj->model[i + 1], 40.0f);
            func_80032FF8_main(D_8010ADB0_mgresultboard[i],
                               D_8010AD28_mgresultboard[D_8010B048_mgresultboard[i].unk_02][D_8010B048_mgresultboard[i].unk_03]);
        } else {
            Hu3DMotionTimeSet(obj->model[i + 1], 20.0f);
            func_80032FF8_main(D_8010ADB0_mgresultboard[i],
                               D_8010AD28_mgresultboard[D_8010B048_mgresultboard[rand8() & 3].unk_02][rand8() % 3]);
        }
    }
    HuMemMemoryFreePerm(modelData);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    func_801080C4_mgresultboard();
    omPrcSetDestructor(0, func_801081E8_mgresultboard);
    while (D_8010AAF8_mgresultboard == 0) {
        HuPrcVSleep();
    }
    D_8010AFAC_mgresultboard = func_801081CC_mgresultboard;
    func_80108150_mgresultboard(obj);
    while (TRUE) {
        D_8010AFAC_mgresultboard(obj);
        HuPrcVSleep();
    }
}

void func_801080C4_mgresultboard(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010AFE8_mgresultboard[i].unk_00 = 0;
        D_8010AFE8_mgresultboard[i].unk_02 = 0;
        D_8010AFE8_mgresultboard[i].unk_04 = -1;
        D_8010AFE8_mgresultboard[i].unk_06 = i;
        D_8010AFE8_mgresultboard[i].unk_08 = i + 4;
        D_8010AFE8_mgresultboard[i].unk_0A = 0;
    }
}

void func_80108150_mgresultboard(omObjData *arg0) {
    s8 i;

    for (i = 0; i < 4; i++) {
        func_801081F0_mgresultboard(arg0, i, D_8010B048_mgresultboard[i].unk_02, D_8010B048_mgresultboard[i].unk_03);
    }
}

void func_801081CC_mgresultboard(omObjData *arg0) {
    func_80108330_mgresultboard(arg0);
}

void func_801081E8_mgresultboard(void) {
}

s32 func_801081F0_mgresultboard(omObjData *arg0, s8 arg1, s8 arg2, s8 arg3) {
    D_8010AFE8_mgresultboard[arg1].unk_02 = arg2 * 3 + arg3;
    D_8010AFE8_mgresultboard[arg1].unk_04 = -1;
    D_8010AFE8_mgresultboard[arg1].unk_00 = 0;
    return 1;
}

s32 func_80108250_mgresultboard(omObjData *arg0, s8 arg1, s8 arg2, s8 arg3) {
    if (D_8010AFE8_mgresultboard[arg1].unk_04 >= 0) {
        return 0;
    }
    D_8010AFE8_mgresultboard[arg1].unk_04 = arg2 * 3 + arg3;
    if (D_8010AFE8_mgresultboard[arg1].unk_08 >= 0) {
        func_8001C258_main(arg0->model[D_8010AFE8_mgresultboard[arg1].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    D_8010AFE8_mgresultboard[arg1].unk_00 = 1;
    return 1;
}

void func_80108330_mgresultboard(omObjData *obj) {
    s16 cur;
    s16 next;
    s16 model;
    s16 temp;
    f32 time;
    f32 endTime;
    s8 i;

    for (i = 0; i < 4; i++) {
        next = D_8010AFE8_mgresultboard[i].unk_08;
        cur = D_8010AFE8_mgresultboard[i].unk_06;
        model = obj->model[cur + 1];
        time = HmfModelData[model].motTime;
        endTime = D_800CCF58_main[HmfModelData[model].motId].unk02;
        switch (D_8010AFE8_mgresultboard[i].unk_00) {
            case 1:
                if (cur >= 0) {
                    func_8001C814_main(model, 1, 0);
                    func_8001C258_main(obj->model[cur + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DMotionSpeedSet(obj->model[cur + 1], D_8010AAF4_mgresultboard);
                }
                if (next >= 0) {
                    func_8001C814_main(obj->model[next + 1], 1, 0);
                    func_8001C258_main(obj->model[next + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DMotionSpeedSet(obj->model[next + 1], D_8010AAF4_mgresultboard);
                }
                if (D_8010AFE8_mgresultboard[i].unk_04 >= 0) {
                    if (endTime <= time) {
                        func_80032FF8_main(D_8010ADB0_mgresultboard[next], D_8010AFE8_mgresultboard[i].unk_04);
                        D_8010AFE8_mgresultboard[i].unk_02 = D_8010AFE8_mgresultboard[i].unk_04;
                        D_8010AFE8_mgresultboard[i].unk_04 = -1;
                        if (cur >= 0) {
                            Hu3DMotionTimeSet(obj->model[cur + 1], 0.0f);
                        }
                        if (next >= 0) {
                            Hu3DMotionTimeSet(obj->model[next + 1], 20.0f);
                        }
                        temp = D_8010AFE8_mgresultboard[i].unk_06;
                        D_8010AFE8_mgresultboard[i].unk_06 = D_8010AFE8_mgresultboard[i].unk_08;
                        D_8010AFE8_mgresultboard[i].unk_08 = temp;
                    }
                    break;
                }
                D_8010AFE8_mgresultboard[i].unk_00 = 0;
            case 0:
                if (endTime <= time) {
                    if (cur >= 0) {
                        Hu3DMotionTimeSet(obj->model[next + 1], 20.0f);
                        func_8001C814_main(obj->model[next + 1], 1, 1);
                        func_8001C258_main(obj->model[next + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        func_80032FF8_main(D_8010ADB0_mgresultboard[next], D_8010AFE8_mgresultboard[i].unk_02);
                    }
                    if (next >= 0) {
                        Hu3DMotionTimeSet(obj->model[cur + 1], endTime);
                        func_8001C814_main(obj->model[cur + 1], 1, 1);
                    }
                }
                break;
        }
    }
}

void func_80108700_mgresultboard(void) {
    omObjData *obj;
    void *data;
    s32 i;

    obj = omAddObj(0x14, 0x32, 0, -1, NULL);
    D_8010AEA0_mgresultboard = obj;
    obj->model[1] = func_8000B0D4_main(0x180000, 0x2A8);
    data = DataRead(0x180005);
    D_8010ADD0_mgresultboard[0] = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, data, 0, "zero_DEF");
    HuMemMemoryFreePerm(data);
    D_8010AE70_mgresultboard[0] = D_800D1714_main[D_8010ADD0_mgresultboard[0]].animIdx;
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8010ADD0_mgresultboard[0], 1, 1);
    func_80032FF8_main(D_8010ADD0_mgresultboard[0], 0);
    Hu3DModelCameraSet(obj->model[1], 2);
    data = DataRead(0x180006);
    D_8010AE70_mgresultboard[1] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0x180000);
    for (i = 1; i < 40; i++) {
        obj->model[i + 1] = Hu3DModelCreate(data, 0x2A0);
        Hu3DModelCameraSet(obj->model[i + 1], 2);
        D_8010ADD0_mgresultboard[i] =
            HmfAnimLink(HmfModelData[obj->model[i + 1]].hmf, D_8010ADD0_mgresultboard[0], 0, "zero_DEF");
        Hu3DModelRemakeStatic(obj->model[i + 1]);
        func_8001C514_main(obj->model[i + 1]);
        func_80032FC0_main(D_8010ADD0_mgresultboard[i], 1, 1);
        func_80032FF8_main(D_8010ADD0_mgresultboard[i], 0);
    }
    HuMemMemoryFreePerm(data);
    for (i = 0; i < 8; i++) {
        Hu3DModelPosSet(obj->model[i + 1], D_8010AB70_mgresultboard[i].x, D_8010AB70_mgresultboard[i].y,
                        D_8010AB70_mgresultboard[i].z);
        Hu3DMotionTimeSet(obj->model[i + 1], 40.0f);
        func_8001C814_main(obj->model[i + 1], 2, 0);
        Hu3DModelPosSet(obj->model[i + 21], D_8010AB70_mgresultboard[i].x, D_8010AB70_mgresultboard[i].y,
                        D_8010AB70_mgresultboard[i].z);
        Hu3DMotionTimeSet(obj->model[i + 21], 20.0f);
        func_8001C814_main(obj->model[i + 21], 2, 0);
    }
    for (i = 0; i < 12; i++) {
        Hu3DModelPosSet(obj->model[i + 9], D_8010ABD0_mgresultboard[i].x, D_8010ABD0_mgresultboard[i].y,
                        D_8010ABD0_mgresultboard[i].z);
        Hu3DMotionTimeSet(obj->model[i + 9], 40.0f);
        func_8001C814_main(obj->model[i + 9], 2, 0);
        Hu3DModelPosSet(obj->model[i + 29], D_8010ABD0_mgresultboard[i].x, D_8010ABD0_mgresultboard[i].y,
                        D_8010ABD0_mgresultboard[i].z);
        Hu3DMotionTimeSet(obj->model[i + 29], 20.0f);
        func_8001C814_main(obj->model[i + 29], 2, 0);
    }
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    func_80109144_mgresultboard();
    omPrcSetDestructor(0, func_8010913C_mgresultboard);
    while (D_8010AAF8_mgresultboard == 0) {
        HuPrcVSleep();
    }
    D_8010AEA4_mgresultboard = func_80108BBC_mgresultboard;
    func_80108BC4_mgresultboard(obj);
    while (TRUE) {
        D_8010AEA4_mgresultboard(obj);
        func_80108C60_mgresultboard(obj);
        HuPrcVSleep();
    }
}

void func_80108BBC_mgresultboard(omObjData *arg0) {
}

void func_80108BC4_mgresultboard(omObjData *arg0) {
    s8 i;

    for (i = 0; i < 4; i++) {
        func_80109744_mgresultboard(arg0, i, D_8010B048_mgresultboard[i].score);
        func_80109DAC_mgresultboard(arg0, i, D_8010B048_mgresultboard[i].coin);
    }
}

void func_80108C60_mgresultboard(omObjData *obj) {
    f32 time;
    f32 maxTime;
    s16 nextModel;
    s16 curModel;
    s16 model;
    s8 i;
    s8 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            nextModel = D_8010AEA8_mgresultboard[i][j].unk_08;
            curModel = D_8010AEA8_mgresultboard[i][j].unk_06;
            model = obj->model[curModel + 1];
            time = HmfModelData[model].motTime;
            maxTime = D_800CCF58_main[HmfModelData[model].motId].unk02;
            switch (D_8010AEA8_mgresultboard[i][j].unk_00) {
                case 1:
                    if (curModel >= 0) {
                        func_8001C814_main(obj->model[curModel + 1], 1, 0);
                        func_8001C258_main(obj->model[curModel + 1], 4, 0);
                        Hu3DMotionSpeedSet(obj->model[curModel + 1], D_8010AAF4_mgresultboard);
                    }
                    if (nextModel >= 0) {
                        func_8001C814_main(obj->model[nextModel + 1], 1, 0);
                        func_8001C258_main(obj->model[nextModel + 1], 4, 0);
                        Hu3DMotionSpeedSet(obj->model[nextModel + 1], D_8010AAF4_mgresultboard);
                    }
                    if (D_8010AEA8_mgresultboard[i][j].unk_04 >= 0) {
                        if (time >= maxTime) {
                            func_80032FF8_main(D_8010ADD0_mgresultboard[nextModel],
                                               D_8010AEA8_mgresultboard[i][j].unk_04);
                            D_8010AEA8_mgresultboard[i][j].unk_02 = D_8010AEA8_mgresultboard[i][j].unk_04;
                            D_8010AEA8_mgresultboard[i][j].unk_04 = -1;
                            if (curModel >= 0) {
                                Hu3DMotionTimeSet(obj->model[curModel + 1], 0.0f);
                            }
                            if (nextModel >= 0) {
                                Hu3DMotionTimeSet(obj->model[nextModel + 1], 20.0f);
                            }
                            model = D_8010AEA8_mgresultboard[i][j].unk_06;
                            D_8010AEA8_mgresultboard[i][j].unk_06 = D_8010AEA8_mgresultboard[i][j].unk_08;
                            D_8010AEA8_mgresultboard[i][j].unk_08 = model;
                            if (D_8010AEA8_mgresultboard[i][j].unk_0A == 0) {
                                func_80109F30_mgresultboard(obj->model[nextModel + 1],
                                                            D_8010ADD0_mgresultboard[nextModel],
                                                            D_8010AE70_mgresultboard[0]);
                            } else {
                                func_80109F30_mgresultboard(obj->model[nextModel + 1],
                                                            D_8010ADD0_mgresultboard[nextModel],
                                                            D_8010AE70_mgresultboard[1]);
                            }
                        }
                        break;
                    }
                    D_8010AEA8_mgresultboard[i][j].unk_00 = 0;
                    /* fallthrough */
                case 0:
                    if (time >= maxTime) {
                        if (nextModel >= 0) {
                            Hu3DMotionTimeSet(obj->model[nextModel + 1], 20.0f);
                            func_8001C814_main(obj->model[nextModel + 1], 1, 1);
                            func_8001C258_main(obj->model[nextModel + 1], 4, 4);
                        }
                        if (curModel >= 0) {
                            func_80032FF8_main(D_8010ADD0_mgresultboard[curModel],
                                               D_8010AEA8_mgresultboard[i][j].unk_02);
                            Hu3DMotionTimeSet(obj->model[curModel + 1], maxTime);
                            func_8001C814_main(obj->model[curModel + 1], 1, 1);
                        }
                    }
                    break;
            }
        }
    }
}

void func_8010913C_mgresultboard(void) {
}

void func_80109144_mgresultboard(void) {
    static const s16 D_8010AD58_mgresultboard[4][5] = {
        { 0, 1, 8, 9, 10 },
        { 2, 3, 11, 12, 13 },
        { 4, 5, 14, 15, 16 },
        { 6, 7, 17, 18, 19 },
    };
    s8 i;
    s8 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            D_8010AEA8_mgresultboard[i][j].unk_00 = 0;
            D_8010AEA8_mgresultboard[i][j].unk_02 = 0;
            D_8010AEA8_mgresultboard[i][j].unk_04 = -1;
            D_8010AEA8_mgresultboard[i][j].unk_06 = D_8010AD58_mgresultboard[i][j];
            D_8010AEA8_mgresultboard[i][j].unk_08 = D_8010AD58_mgresultboard[i][j] + 20;
            D_8010AEA8_mgresultboard[i][j].unk_0A = 0;
        }
        for (; j < 5; j++) {
            D_8010AEA8_mgresultboard[i][j].unk_00 = 0;
            D_8010AEA8_mgresultboard[i][j].unk_02 = 0;
            D_8010AEA8_mgresultboard[i][j].unk_04 = -1;
            D_8010AEA8_mgresultboard[i][j].unk_06 = D_8010AD58_mgresultboard[i][j];
            D_8010AEA8_mgresultboard[i][j].unk_08 = D_8010AD58_mgresultboard[i][j] + 20;
            D_8010AEA8_mgresultboard[i][j].unk_0A = 0;
        }
    }
}

s32 func_801092E0_mgresultboard(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[2];
    s16 value;
    s8 i;

    if (D_8010AEA8_mgresultboard[arg1][0].unk_04 >= 0) {
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
        D_8010AEA8_mgresultboard[arg1][i].unk_04 = digits[i];
        if (D_8010AEA8_mgresultboard[arg1][i].unk_08 >= 0) {
            func_8001C258_main(arg0->model[D_8010AEA8_mgresultboard[arg1][i].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        D_8010AEA8_mgresultboard[arg1][i].unk_00 = 1;
    }
    return 1;
}

s32 func_80109498_mgresultboard(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[2];
    s16 value;
    s8 i;

    if (D_8010AEA8_mgresultboard[arg1][0].unk_04 >= 0) {
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
        D_8010AEA8_mgresultboard[arg1][i].unk_04 = digits[i];
        if (D_8010AEA8_mgresultboard[arg1][i].unk_08 >= 0) {
            func_8001C258_main(arg0->model[D_8010AEA8_mgresultboard[arg1][i].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        D_8010AEA8_mgresultboard[arg1][i].unk_00 = 1;
    }
    return 1;
}

s32 func_80109650_mgresultboard(s32 arg0, s8 arg1) {
    s8 i;

    if (D_8010AEA8_mgresultboard[arg1][0].unk_04 >= 0) {
        return 0;
    }

    for (i = 0; i < 2; i++) {
        D_8010AEA8_mgresultboard[arg1][i].unk_00 = 0;
    }
    return 1;
}

s32 func_801096E0_mgresultboard(s32 arg0, s8 arg1) {
    s8 i;

    for (i = 0; i < 2; i++) {
        D_8010AEA8_mgresultboard[arg1][i].unk_00 = 1;
    }
    return 1;
}

s32 func_80109744_mgresultboard(omObjData *arg0, s8 arg1, s16 arg2) {
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
        D_8010AEA8_mgresultboard[arg1][i].unk_02 = digits[i];
        D_8010AEA8_mgresultboard[arg1][i].unk_04 = -1;
        D_8010AEA8_mgresultboard[arg1][i].unk_00 = 0;
    }
    return 1;
}

s32 func_80109878_mgresultboard(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[3];
    s16 value;
    s8 i;

    if (D_8010AEA8_mgresultboard[arg1][2].unk_04 >= 0) {
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
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_04 = digits[i];
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_00 = 1;
        if (D_8010AEA8_mgresultboard[arg1][i + 2].unk_08 >= 0) {
            func_8001C258_main(arg0->model[D_8010AEA8_mgresultboard[arg1][i + 2].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_0A = 0;
    }
    return 1;
}

s32 func_80109A90_mgresultboard(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[3];
    s16 value;
    s8 i;

    if (D_8010AEA8_mgresultboard[arg1][2].unk_04 >= 0) {
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
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_04 = digits[i];
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_00 = 1;
        if (D_8010AEA8_mgresultboard[arg1][i + 2].unk_08 >= 0) {
            func_8001C258_main(arg0->model[D_8010AEA8_mgresultboard[arg1][i + 2].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_0A = 1;
    }
    return 1;
}

s32 func_80109CB0_mgresultboard(s32 arg0, s8 arg1) {
    s8 i;

    if (D_8010AEA8_mgresultboard[arg1][2].unk_04 >= 0) {
        return 0;
    }

    for (i = 0; i < 4; i++) {
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_00 = 0;
    }
    return 1;
}

s32 func_80109D44_mgresultboard(s32 arg0, s8 arg1) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_00 = 1;
    }
    return 1;
}

s32 func_80109DAC_mgresultboard(omObjData *arg0, s8 arg1, s16 arg2) {
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
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_02 = digits[i];
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_04 = -1;
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_00 = 0;
    }
    return 1;
}

void func_80109F30_mgresultboard(s16 model, s16 anim, s16 animIdx) {
    if (anim >= 0) {
        if (animIdx == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            HmfAnim *entry;

            func_80033970_main(HmfModelData[model].hmf);
            entry = &D_800D1714_main[anim];

            entry->animIdx = animIdx;
        }
    }
}
