#include "common.h"
#include "overlays/mgresultboard.h"

extern UnkTemp D_8010AFB0_mgresultboard[];
extern PlayerResult D_8010B048_mgresultboard[4];

extern omObjData *D_8010AFE0_mgresultboard;
extern void (*D_8010AFE4_mgresultboard)(omObjData *);
extern s32 D_8010AE80_mgresultboard[8];
extern Vec D_8010AC60_mgresultboard[4];
extern s32 D_8010AAF8_mgresultboard;

void func_8010A334_mgresultboard(omObjData *);
void func_8010A350_mgresultboard(void);
void func_8010A358_mgresultboard(void);
void func_8010A3E4_mgresultboard(omObjData *);
s32 func_8010A454_mgresultboard(omObjData *, s8, s8);
void func_8010A4A0_mgresultboard(omObjData *);

void func_8010A000_mgresultboard(void) {
    omObjData *obj;
    void *modelData;
    void *animData;
    s32 anim;
    s32 i;

    anim = 0;
    obj = omAddObj(0x14, 0xC, 0, -1, NULL);
    D_8010AFE0_mgresultboard = obj;
    modelData = DataRead(0x180003);
    for (i = 0; i < 8; i++) {
        obj->model[i + 1] = Hu3DModelCreate(modelData, 0x2A0);
        func_8001C814_main(obj->model[i + 1], 2, 0);
        func_8001C814_main(obj->model[i + 1], 1, 0);
        Hu3DModelCameraSet(obj->model[i + 1], 2);
        Hu3DModelPosSet(obj->model[i + 1], D_8010AC60_mgresultboard[i & 3].x, D_8010AC60_mgresultboard[i & 3].y,
                        D_8010AC60_mgresultboard[i & 3].z);
        if (i == 0) {
            animData = DataRead(0x180007);
            anim = (s16)HmfAnimCreate(HmfModelData[obj->model[1]].hmf, animData, 0, "y004_010_DEF");
            D_8010AE80_mgresultboard[0] = anim;
            HuMemMemoryFreePerm(animData);
        } else {
            D_8010AE80_mgresultboard[i] =
                HmfAnimLink(HmfModelData[obj->model[i + 1]].hmf, anim, 0, "y004_010_DEF");
        }
        func_80032FC0_main(D_8010AE80_mgresultboard[i], 1, 1);
        Hu3DModelRemakeStatic(obj->model[i + 1]);
        func_8001C514_main(obj->model[i + 1]);
        if (i < 4) {
            Hu3DMotionTimeSet(obj->model[i + 1], 40.0f);
            func_80032FF8_main(D_8010AE80_mgresultboard[i], D_8010B048_mgresultboard[i].unk_01);
        } else {
            Hu3DMotionTimeSet(obj->model[i + 1], 20.0f);
            func_80032FF8_main(D_8010AE80_mgresultboard[i], rand8() & 3);
        }
    }
    HuMemMemoryFreePerm(modelData);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    func_8010A358_mgresultboard();
    omPrcSetDestructor(0, func_8010A350_mgresultboard);
    while (D_8010AAF8_mgresultboard == 0) {
        HuPrcVSleep();
    }
    func_8010A3E4_mgresultboard(obj);
    D_8010AFE4_mgresultboard = func_8010A334_mgresultboard;
    while (TRUE) {
        D_8010AFE4_mgresultboard(obj);
        HuPrcVSleep();
    }
}

void func_8010A334_mgresultboard(omObjData *arg0) {
    func_8010A4A0_mgresultboard(arg0);
}

void func_8010A350_mgresultboard(void) {
}

void func_8010A358_mgresultboard(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010AFB0_mgresultboard[i].unk_00 = 0;
        D_8010AFB0_mgresultboard[i].unk_02 = 0;
        D_8010AFB0_mgresultboard[i].unk_04 = -1;
        D_8010AFB0_mgresultboard[i].unk_06 = i;
        D_8010AFB0_mgresultboard[i].unk_08 = i + 4;
        D_8010AFB0_mgresultboard[i].unk_0A = 0;
    }
}

void func_8010A3E4_mgresultboard(omObjData *arg0) {
    s8 i;

    for (i = 0; i < 4; i++) {
        func_8010A454_mgresultboard(arg0, i, D_8010B048_mgresultboard[i].unk_01);
    }
}

s32 func_8010A454_mgresultboard(omObjData *arg0, s8 arg1, s8 arg2) {
    D_8010AFB0_mgresultboard[arg1].unk_02 = arg2;
    D_8010AFB0_mgresultboard[arg1].unk_04 = -1;
    D_8010AFB0_mgresultboard[arg1].unk_00 = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4EB420", func_8010A4A0_mgresultboard);

s32 func_8010A864_mgresultboard(omObjData *arg0, s8 arg1, s8 arg2) {
    if (D_8010AFB0_mgresultboard[arg1].unk_04 >= 0) {
        return 0;
    }

    D_8010AFB0_mgresultboard[arg1].unk_04 = arg2;

    if (D_8010AFB0_mgresultboard[arg1].unk_08 >= 0) {
        func_8001C258_main(arg0->model[D_8010AFB0_mgresultboard[arg1].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }

    D_8010AFB0_mgresultboard[arg1].unk_00 = 1;
    return 1;
}
