#include "common.h"

typedef struct UnkMstory3Obj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} UnkMstory3Obj; // sizeof 0x14

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern Vec D_801158E0_mstory3;
extern Vec D_80115908_mstory3;
extern Vec D_80115914_mstory3;
extern Vec D_80115920_mstory3;
extern Vec D_8011598C_mstory3;
extern Vec D_80115998_mstory3;
extern Vec D_8011592C_mstory3;
extern Vec D_80115938_mstory3;
extern Vec D_80115944_mstory3;
extern Vec D_80115950_mstory3;
extern Vec D_8011595C_mstory3;
extern Vec D_801159BC_mstory3;
extern Vec D_801159C8_mstory3;
extern Vec D_801159D4_mstory3;
extern Vec D_801159E0_mstory3;
extern Vec D_801159F8_mstory3;
extern Vec D_80115A10_mstory3;
extern Vec D_80115A1C_mstory3;
extern Vec D_80115A28_mstory3;
extern Vec D_80115A34_mstory3;
extern Vec D_80115A40_mstory3;
extern Vec D_80115A4C_mstory3;
extern Vec D_80115A58_mstory3;
extern Vec D_80115A64_mstory3;
extern Vec D_80115A70_mstory3;
extern Vec D_80115A7C_mstory3;
extern Vec D_80115A88_mstory3;
extern Vec D_80115A94_mstory3;
extern Vec D_80115AA0_mstory3;
extern Vec D_80115B24_mstory3;
extern Vec D_80115B30_mstory3;
extern Vec D_80115B3C_mstory3;
extern Vec D_80115B48_mstory3;
extern Vec D_80115B54_mstory3;
extern Vec D_80115478_mstory3[];
extern s16 D_80115C9C_mstory3[];
extern s16 D_80115CA2_mstory3[];
extern UnkMstory3Obj D_80115CB0_mstory3[11];
extern s16 D_80115D8C_mstory3;
extern s16 D_80115D9C_mstory3;
extern s16 D_80115DA0_mstory3;
extern s16 D_80115DA2_mstory3;
extern s16 D_80115D8E_mstory3;
extern s16 D_80115D90_mstory3;
extern s16 D_80115D92_mstory3;
extern s16 D_80115D94_mstory3;
extern s16 D_80115D96_mstory3;
extern s16 D_80115DB0_mstory3;

MstoryPath *func_8010C9F0_mstory3(Vec *points, s32 flags);
void func_8010CCF4_mstory3(MstoryPath *path, f32 t, Vec *out);
void func_8010D59C_mstory3(MstoryPath *path);
void func_8010D774_mstory3(omObjData *obj);
void func_80110978_mstory3(omObjData *obj);
void func_80114FA4_mstory3(omObjData *obj);
void func_801122BC_mstory3(void);
void func_80114AF8_mstory3(void);
void func_80105F54_mstory3(void);
void func_8010D77C_mstory3(void);
void func_8010D97C_mstory3(void);
void func_8010F660_mstory3(void);
void func_80110CB4_mstory3(void);
void func_801110B4_mstory3(void);
void func_80111764_mstory3(void);
void func_801122C4_mstory3(void);
void func_8011249C_mstory3(void);
void func_80112B88_mstory3(void);
void func_801134E0_mstory3(void);
void func_80113968_mstory3(void);
void func_80113BB0_mstory3(void);
void func_801149D0_mstory3(void);
void func_80114B00_mstory3(void);
void func_801061C4_mstory3(void);
void func_80106220_mstory3(void);
void func_80106DC4_mstory3(omObjData *obj, const Vec *pos, s32 frames);
void func_80106CF0_mstory3(s16 model, s16 arg1, s16 arg2);
void func_80106DE0_mstory3(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_80107070_mstory3(omObjData *obj, const Vec *pos, s32 frames);
void func_8010733C_mstory3(omObjData *obj, f32 speed, s16 frames);
void func_801074D8_mstory3(omObjData *obj, f32 speed, s16 frames);
void func_80107244_mstory3(s16 model);
void func_80107674_mstory3(omObjData *obj, omObjData *target);
void func_8010DA00_mstory3(omObjData *obj);
void func_8011065C_mstory3(omObjData *obj);
void func_80110A84_mstory3(omObjData *obj);
void func_80111E2C_mstory3(omObjData *obj);
void func_80111F3C_mstory3(omObjData *obj);
void func_801125C4_mstory3(omObjData *obj);
void func_80112834_mstory3(omObjData *obj);
void func_8011270C_mstory3(omObjData *obj);
void func_8011268C_mstory3(omObjData *obj);
void func_80112EF0_mstory3(omObjData *obj);
void func_80112FB0_mstory3(omObjData *obj);
void func_8011322C_mstory3(omObjData *obj);
void func_80113874_mstory3(omObjData *obj);
void func_80114920_mstory3(omObjData *obj);
void func_8011522C_mstory3(omObjData *obj);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010C9F0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010CCF4_mstory3);

void func_8010D59C_mstory3(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010D5CC_mstory3(void) {
    D_80115DB0_mstory3 = GwStory.unk1;
    func_80105F54_mstory3();
    D_80115D8C_mstory3 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8010F660_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80110CB4_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_801110B4_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80111764_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_801122C4_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112B88_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_801134E0_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113968_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113BB0_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80114B00_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010D97C_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_8011249C_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_801149D0_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010D77C_mstory3, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115D8C_mstory3, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8010D774_mstory3(omObjData *obj) {
}

void func_8010D77C_mstory3(void) {
    s16 seNo;
    s8 vol;
    f32 z;

    while (TRUE) {
        if (D_80115CB0_mstory3[0].unk_0C == 1 && Hu3DData[D_80115CB0_mstory3[0].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)D_80115CB0_mstory3[0].unk_10, D_80115DB0_mstory3);
        }
        if (D_80115CB0_mstory3[2].unk_0C == 1 && Hu3DData[D_80115CB0_mstory3[2].obj->model[1]].motTime == 0.0f) {
            seNo = CharFXPlay((s16)D_80115CB0_mstory3[2].unk_10, 6);
            z = Hu3DData[D_80115CB0_mstory3[2].obj->model[1]].pos.z;
            if (z <= 0.0f) {
                vol = z / 15.0f + 127.0f;
            } else {
                vol = 127;
            }
            HuAudFXVolSet(seNo, vol);
        }
        if (D_80115CB0_mstory3[1].unk_0C == 1 && Hu3DData[D_80115CB0_mstory3[1].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)D_80115CB0_mstory3[1].unk_10, 7);
        }
        HuPrcVSleep();
    }
}

void func_8010D974_mstory3(void) {
}

void func_8010D97C_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 0, 0, -1, NULL);
    D_80115CB0_mstory3[10].obj = obj;
    D_80115CB0_mstory3[10].unk_08 = 0;
    D_80115CB0_mstory3[10].func = func_8010DA00_mstory3;
    omPrcSetDestructor(0, func_8010D974_mstory3);
    while (1) {
        D_80115CB0_mstory3[10].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010DA00_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010E170_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010EBE4_mstory3);

void func_8010F658_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010F660_mstory3);

void func_8010FCA4_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

void func_8010FD64_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_80107070_mstory3(obj, &D_801158E0_mstory3, 10);
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115880_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011588C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115898_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158A4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158B0_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158BC_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158C8_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158D4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158E0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010FDB0_mstory3);

void func_801103E8_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80107070_mstory3(obj, &D_80115908_mstory3, 5);
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

void func_80110474_mstory3(omObjData *obj) {
    D_80115CB0_mstory3[0].unk_0C = 1;
    D_80115CB0_mstory3[0].unk_10 = 31;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801074D8_mstory3(obj, 1.5f, 60);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[0].unk_0C = 0;
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

void func_80110558_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107070_mstory3(obj, &D_80115914_mstory3, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

void func_80110628_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, &D_80115920_mstory3, 5);
    D_80115CB0_mstory3[0].func = func_8011065C_mstory3;
}

void func_8011065C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_8011067C_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107070_mstory3(obj, &D_8011592C_mstory3, 10);
    D_80115CB0_mstory3[0].unk_0C = 1;
    D_80115CB0_mstory3[0].unk_10 = 31;
    func_801074D8_mstory3(obj, 6.0f, 30);
    D_80115CB0_mstory3[0].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[0].func = func_80110A84_mstory3;
}

void func_80110774_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[0].unk_08 == 1) {
        func_80106CF0_mstory3(obj->model[1], D_80115DA2_mstory3, D_80115DA0_mstory3);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        func_80107070_mstory3(obj, &D_80115944_mstory3, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        D_80115CB0_mstory3[0].unk_08 = 2;
        D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[0].unk_08 == 2) {
        func_80106CF0_mstory3(obj->model[1], D_80115DA2_mstory3, D_80115D9C_mstory3);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        func_80107070_mstory3(obj, &D_80115938_mstory3, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        D_80115CB0_mstory3[0].unk_08 = 3;
        D_80115CB0_mstory3[0].func = func_80110978_mstory3;
    } else if (D_80115CB0_mstory3[0].unk_08 == 3) {
        func_80107070_mstory3(obj, &D_80115944_mstory3, 10);
        D_80115CB0_mstory3[0].func = func_80110978_mstory3;
    }
}

void func_80110978_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80110998_mstory3(omObjData *obj) {
    HuPrcSleep(5);
    D_80115CB0_mstory3[0].unk_0C = 1;
    D_80115CB0_mstory3[0].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    func_8010733C_mstory3(obj, 20.0f, 15);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[0].unk_0C = 0;
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

void func_80110A84_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[0].unk_08 == 0) {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        func_80107070_mstory3(obj, &D_80115950_mstory3, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        D_80115CB0_mstory3[0].unk_08 = 1;
        D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[0].unk_08 == 1) {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        func_80107070_mstory3(obj, &D_8011595C_mstory3, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        D_80115CB0_mstory3[0].unk_08 = 2;
        D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[0].unk_08 == 2) {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        func_80107070_mstory3(obj, &D_80115950_mstory3, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        D_80115CB0_mstory3[0].unk_08 = 0;
        D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
    }
}

void func_80110CAC_mstory3(void) {
}

void func_80110CB4_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[1].obj = obj;
    D_80115CB0_mstory3[1].unk_08 = 0;
    D_80115CB0_mstory3[1].func = func_8010D774_mstory3;
    D_80115CB0_mstory3[1].unk_0C = 0;
    D_80115CB0_mstory3[1].unk_10 = 31;
    obj->model[1] = func_8000B108_main(0x90000, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8000B460_main(obj, 0, 0x90004);
    func_8000B460_main(obj, 1, 0x1D007A);
    func_8000B460_main(obj, 2, 0x1D0051);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 30, 2);
    Hu3DModelPosSet(obj->model[1], 150.0f, 0.0f, 384.0f);
    Hu3DModelPosSet(obj->model[2], 150.0f, -5.0f, 384.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    omPrcSetDestructor(0, func_80110CAC_mstory3);
    while (1) {
        D_80115CB0_mstory3[1].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115908_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115914_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115920_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011592C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115938_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115944_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115950_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011595C_mstory3);

const Vec D_80115974_mstory3 = { 200.0f, 0.0f, 1200.0f };

void func_80110E30_mstory3(omObjData *obj) {
    HuAudFXPlay(0x28E);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    D_80115CB0_mstory3[1].unk_0C = 1;
    D_80115CB0_mstory3[1].unk_10 = 40;
    func_80106DC4_mstory3(obj, &D_80115974_mstory3, 40);
    D_80115CB0_mstory3[1].unk_0C = 0;
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_80115CB0_mstory3[1].func = func_8010D774_mstory3;
}

void func_80110F04_mstory3(omObjData *obj) {
    Vec pos;

    pos.x = Hu3DData[D_80115CB0_mstory3[8].obj->model[2]].pos.x;
    pos.y = Hu3DData[D_80115CB0_mstory3[8].obj->model[2]].pos.y;
    pos.z = Hu3DData[D_80115CB0_mstory3[8].obj->model[2]].pos.z;
    pos.x += 0.5f;
    Hu3DModelPosSet(D_80115CB0_mstory3[8].obj->model[2], pos.x, pos.y, pos.z);
    func_8000CFA4_main(D_80115CB0_mstory3[8].obj->model[5], pos.x, pos.y - 40.0f, pos.z);
}

void func_80110FE8_mstory3(omObjData *obj) {
    omObjData *target = D_80115CB0_mstory3[2].obj;

    func_8001C258_main(target->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(target->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_801061C4_mstory3();
    HuPrcSleep(3);
    func_80106220_mstory3();
    D_80115CB0_mstory3[1].func = func_8010D774_mstory3;
}

const Vec D_80115980_mstory3 = { 138.0f, 100.0f, 214.0f };

void func_80111064_mstory3(void) {
    func_80106DE0_mstory3(D_80115CB0_mstory3[3].obj, &D_80115980_mstory3, 180, 0);
    D_80115CB0_mstory3[1].func = func_8010D774_mstory3;
}

void func_801110AC_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_801110B4_mstory3);

void func_80111500_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(D_80115CB0_mstory3[2].obj->model[1], Hu3DData[D_80115CB0_mstory3[2].obj->motion[1]].motId, 0, 10,
                       2);
    func_80107070_mstory3(obj, &D_8011598C_mstory3, 10);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[2].obj->model[1], Hu3DData[D_80115CB0_mstory3[2].obj->motion[0]].motId, 0, 10,
                       2);
    D_80115CB0_mstory3[2].func = func_8010D774_mstory3;
}

void func_801115D8_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    D_80115CB0_mstory3[8].func = func_80114920_mstory3;
    Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[13]].motId, 0, 10, 2);
    Hu3DMotionSpeedSet(D_80115CB0_mstory3[0].obj->model[1], 0.5f);
    D_80115CB0_mstory3[2].unk_0C = 1;
    D_80115CB0_mstory3[2].unk_10 = 40;
    func_80106DC4_mstory3(obj, &D_80115998_mstory3, 60);
    D_80115CB0_mstory3[2].unk_0C = 0;
    Hu3DMotionSpeedSet(D_80115CB0_mstory3[0].obj->model[1], 1.0f);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[2].unk_08 = 1;
    D_80115CB0_mstory3[2].func = func_8010D774_mstory3;
}

void func_8011175C_mstory3(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011598C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115998_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80111764_mstory3);

const Vec D_801159B0_mstory3 = { 10.0f, 378.9f, 0.0f };

void func_80111A58_mstory3(omObjData *obj) {
    HuPrcSleep(60);
    D_80115CB0_mstory3[0].func = func_8010FCA4_mstory3;
    D_80115CB0_mstory3[4].func = func_801125C4_mstory3;
    func_80107070_mstory3(obj, &D_801159B0_mstory3, 30);
    func_80106DC4_mstory3(obj, &D_801159D4_mstory3, 20);
    HuPrcSleep(30);
    func_80107070_mstory3(obj, &D_801159BC_mstory3, 10);
    func_80106DC4_mstory3(obj, &D_801159E0_mstory3, 15);
    D_80115CB0_mstory3[0].func = func_8010FD64_mstory3;
    func_80107070_mstory3(obj, &D_801159C8_mstory3, 10);
    D_80115CB0_mstory3[3].unk_08 = 1;
    D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159BC_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159C8_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159D4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159E0_mstory3);

void func_80111B34_mstory3(omObjData *obj) {
    f32 baseY = Hu3DData[obj->model[1]].pos.y;
    f32 ofs;
    s16 i;

    for (i = 0; i < 12; i++) {
        ofs = sindf(i * 15.0) * 80.0f;
        Hu3DData[obj->model[1]].pos.y = baseY + ofs;
        HuPrcVSleep();
    }
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D94_mstory3);
    D_80115CB0_mstory3[3].unk_08 = 1;
    D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
}

void func_80111C50_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3);
    func_80107070_mstory3(obj, &D_801159F8_mstory3, 5);
    D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159F8_mstory3);

void func_80111CB8_mstory3(omObjData *obj) {
    f32 baseY = Hu3DData[obj->model[1]].pos.y;
    f32 ofs;
    s16 i;

    for (i = 0; i < 10; i++) {
        ofs = sindf(i * 15.0) * 100.0f;
        Hu3DData[obj->model[1]].pos.y = baseY + ofs;
        HuPrcVSleep();
    }
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D94_mstory3);
    D_80115CB0_mstory3[0].func = func_80110558_mstory3;
    D_80115CB0_mstory3[4].func = func_8011268C_mstory3;
    D_80115CB0_mstory3[5].func = func_80112EF0_mstory3;
    D_80115CB0_mstory3[3].unk_08 = 1;
    D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
}

void func_80111DF8_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, &D_80115A10_mstory3, 5);
    D_80115CB0_mstory3[3].func = func_80111E2C_mstory3;
}

void func_80111E2C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80111E4C_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[3].unk_08 == 1) {
        func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3);
        func_80107070_mstory3(obj, &D_80115A1C_mstory3, 10);
        D_80115CB0_mstory3[3].unk_08 = 2;
        D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[3].unk_08 == 2) {
        func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D92_mstory3);
        func_80107070_mstory3(obj, &D_80115A28_mstory3, 10);
        D_80115CB0_mstory3[3].unk_08 = 3;
        D_80115CB0_mstory3[3].func = func_80111F3C_mstory3;
    } else if (D_80115CB0_mstory3[3].unk_08 == 3) {
        func_80107070_mstory3(obj, &D_80115A1C_mstory3, 10);
        D_80115CB0_mstory3[3].func = func_80111F3C_mstory3;
    }
}

void func_80111F3C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80111F5C_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_8010733C_mstory3(obj, 20.0f, 60);
    D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
}

void func_80111FA4_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[3].unk_08 == 0) {
        func_80107070_mstory3(obj, &D_80115A34_mstory3, 10);
        D_80115CB0_mstory3[3].unk_08 = 1;
        D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[3].unk_08 == 1) {
        func_80107070_mstory3(obj, &D_80115A40_mstory3, 10);
        D_80115CB0_mstory3[3].unk_08 = 2;
        D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[3].unk_08 == 2) {
        func_80107070_mstory3(obj, &D_80115A34_mstory3, 10);
        D_80115CB0_mstory3[3].unk_08 = 0;
        D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
    }
}

void func_8011204C_mstory3(omObjData *obj) {
    f32 rotY;
    f32 ofs;
    s16 i;

    if (D_80115CB0_mstory3[3].unk_08 == 0) {
        HuPrcSleep(30);
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 10; i++) {
        ofs = sindf(i * 9.0f) * 120.0f;
        Hu3DData[obj->model[1]].rot.y = rotY + ofs;
        HuPrcVSleep();
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 15; i++) {
        ofs = sindf(i * 4.5f) * 240.0f;
        Hu3DData[obj->model[1]].rot.y = rotY - ofs;
        HuPrcVSleep();
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 10; i++) {
        ofs = sindf(i * 9.0f) * 120.0f;
        Hu3DData[obj->model[1]].rot.y = rotY + ofs;
        HuPrcVSleep();
    }
    if (D_80115CB0_mstory3[3].unk_08 == 0) {
        D_80115CB0_mstory3[3].unk_08 = 0;
        D_80115CB0_mstory3[3].func = func_80111CB8_mstory3;
    } else {
        D_80115CB0_mstory3[3].unk_08 = 0;
        D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
    }
}

void func_801122BC_mstory3(void) {
}

void func_801122C4_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[4].obj = obj;
    D_80115CB0_mstory3[4].unk_08 = 0;
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    func_8000B460_main(obj, 3, 0xA0129);
    func_8000B460_main(obj, 4, 0xA012A);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 0.0f, 200.0f, 150.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, -5.0f, 150.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    omPrcSetDestructor(0, func_801122BC_mstory3);
    while (1) {
        D_80115CB0_mstory3[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8011249C_mstory3(void) {
    f32 angle = 0.0f;
    omObjData *obj = D_80115CB0_mstory3[4].obj;
    Vec pos;
    f32 ofs;

    pos.y = Hu3DData[obj->model[1]].pos.y;
    while (TRUE) {
        pos.x = Hu3DData[obj->model[1]].pos.x;
        pos.z = Hu3DData[obj->model[1]].pos.z;
        ofs = sindf(angle) * 25.0f + 25.0f;
        angle += 2.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        Hu3DModelPosSet(obj->model[1], pos.x, ofs + pos.y, pos.z);
        HuPrcVSleep();
    }
}

void func_801125C4_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, &D_80115A4C_mstory3, 20);
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
}

void func_801125F8_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_80107070_mstory3(obj, &D_80115A58_mstory3, 5);
    D_80115CB0_mstory3[8].unk_08 = 2;
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
}

void func_80112650_mstory3(omObjData *obj) {
    func_801074D8_mstory3(obj, 2.0f, 60);
    D_80115CB0_mstory3[4].unk_08 = 1;
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
}

void func_8011268C_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_80107070_mstory3(obj, &D_80115A64_mstory3, 10);
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
}

void func_801126D8_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, &D_80115A70_mstory3, 5);
    D_80115CB0_mstory3[4].func = func_8011270C_mstory3;
}

void func_8011270C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_8011272C_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[4].unk_08 == 1) {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        func_80107070_mstory3(obj, &D_80115A7C_mstory3, 10);
        D_80115CB0_mstory3[4].unk_08 = 2;
        D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[4].unk_08 == 2) {
        func_80107070_mstory3(obj, &D_80115A88_mstory3, 10);
        D_80115CB0_mstory3[4].unk_08 = 3;
        D_80115CB0_mstory3[4].func = func_80112834_mstory3;
    } else if (D_80115CB0_mstory3[4].unk_08 == 3) {
        func_80107070_mstory3(obj, &D_80115A7C_mstory3, 10);
        D_80115CB0_mstory3[4].func = func_80112834_mstory3;
    }
}

void func_80112834_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80112854_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_8010733C_mstory3(obj, 20.0f, 60);
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
}

void func_8011289C_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[4].unk_08 == 0) {
        func_80107070_mstory3(obj, &D_80115A94_mstory3, 10);
        D_80115CB0_mstory3[4].unk_08 = 1;
        D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[4].unk_08 == 1) {
        func_80107070_mstory3(obj, &D_80115AA0_mstory3, 10);
        D_80115CB0_mstory3[4].unk_08 = 2;
        D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[4].unk_08 == 2) {
        func_80107070_mstory3(obj, &D_80115A94_mstory3, 10);
        D_80115CB0_mstory3[4].unk_08 = 0;
        D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
    }
}

void func_80112944_mstory3(omObjData *obj) {
    f32 rotY;
    f32 ofs;
    s16 i;

    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 15; i++) {
        ofs = sindf(i * 6.0f) * 30.0f;
        Hu3DData[obj->model[1]].rot.y = rotY + ofs;
        HuPrcVSleep();
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 30; i++) {
        ofs = sindf(i * 3.0f) * 60.0f;
        Hu3DData[obj->model[1]].rot.y = rotY - ofs;
        HuPrcVSleep();
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 15; i++) {
        ofs = sindf(i * 6.0f) * 30.0f;
        Hu3DData[obj->model[1]].rot.y = rotY + ofs;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
}

void func_80112B80_mstory3(void) {
}

void func_80112B88_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    D_80115CB0_mstory3[5].obj = obj;
    D_80115CB0_mstory3[5].unk_08 = 0;
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8000B460_main(obj, 3, 0x1D0032);
    func_8000B460_main(obj, 4, 0x1D0034);
    func_8000B460_main(obj, 5, 0x1D0033);
    func_8000B460_main(obj, 6, 0x1D0035);
    func_8000B460_main(obj, 7, 0xA0038);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], -700.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -700.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 270.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    omPrcSetDestructor(0, func_80112B80_mstory3);
    while (1) {
        D_80115CB0_mstory3[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A10_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A1C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A28_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A34_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A40_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A4C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A58_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A64_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A70_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A7C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A88_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A94_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115AA0_mstory3);

const Vec D_80115AAC_mstory3 = { -350.0f, 0.0f, 480.0f };
// Unreferenced zero-filled rodata.
const Vec D_80115AB8_mstory3[9] = { 0 };

void func_80112DA0_mstory3(omObjData *obj) {
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80115CB0_mstory3[0].func = func_80110474_mstory3;
    D_80115CB0_mstory3[4].func = func_80112650_mstory3;
    D_80115CB0_mstory3[1].func = func_80110F04_mstory3;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106DC4_mstory3(obj, &D_80115AAC_mstory3, 60);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (TRUE) {
        if (D_80115CB0_mstory3[4].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[4].unk_08 = 0;
    D_80115CB0_mstory3[1].func = func_8010D774_mstory3;
    D_80115CB0_mstory3[5].unk_08 = 1;
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
}

void func_80112EF0_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80107070_mstory3(obj, &D_80115B24_mstory3, 10);
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
}

void func_80112F7C_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, &D_80115B30_mstory3, 5);
    D_80115CB0_mstory3[5].func = func_80112FB0_mstory3;
}

void func_80112FB0_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80112FD0_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106DC4_mstory3(obj, &D_80115B3C_mstory3, 60);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[5].unk_08 = 1;
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
}

void func_801130A4_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
}

void func_8011315C_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106DC4_mstory3(obj, &D_80115B48_mstory3, 30);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[5].obj->model[1], Hu3DData[D_80115CB0_mstory3[5].obj->motion[2]].motId, 0, 10,
                       2);
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8011322C_mstory3);

void func_801134D8_mstory3(void) {
}

void func_801134E0_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[6].obj = obj;
    D_80115CB0_mstory3[6].unk_08 = 0;
    D_80115CB0_mstory3[6].func = func_8010D774_mstory3;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F1);
    func_8000B460_main(obj, 2, 0x1D0039);
    func_8000B460_main(obj, 3, 0x1D003A);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 500.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], 500.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 270.0f, 0.0f);
    omPrcSetDestructor(0, func_801134D8_mstory3);
    while (1) {
        D_80115CB0_mstory3[6].func(obj);
        HuPrcVSleep();
    }
}

void func_80113668_mstory3(omObjData *obj) {
    func_80106DC4_mstory3(obj, &D_80115B54_mstory3, 60);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[6].func = func_8010D774_mstory3;
}

void func_801136E8_mstory3(omObjData *obj) {
    s16 i;
    f32 y;

    Hu3DMotionShiftSet(obj->model[1], Hu3DData[D_80115CB0_mstory3[6].obj->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(10);
    for (i = 0; i < 10; i++) {
        y = sindf(i * 9.0f) * 100.0f;
        Hu3DData[D_80115CB0_mstory3[5].obj->model[1]].pos.y = y;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[6].unk_08 = 1;
    D_80115CB0_mstory3[6].func = func_8010D774_mstory3;
}

void func_80113800_mstory3(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[D_80115CB0_mstory3[6].obj->motion[3]].motId, 0, 0xA, 2);
    HuPrcSleep(0xA);
    D_80115CB0_mstory3[6].func = func_80113874_mstory3;
}

void func_80113874_mstory3(omObjData *obj) {
    omObjData *obj6 = D_80115CB0_mstory3[6].obj;
    omObjData *obj7 = D_80115CB0_mstory3[7].obj;
    omObjData *obj5 = D_80115CB0_mstory3[5].obj;

    Hu3DData[obj6->model[2]].pos.x = Hu3DData[obj6->model[1]].pos.x += 10.0f;
    Hu3DData[obj7->model[2]].pos.x = Hu3DData[obj7->model[1]].pos.x += 10.0f;
    Hu3DData[obj5->model[1]].pos.x += 10.0f;
    Hu3DData[obj5->model[2]].pos.x += 10.0f;
}

void func_80113960_mstory3(void) {
}

void func_80113968_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[7].obj = obj;
    D_80115CB0_mstory3[7].unk_08 = 0;
    D_80115CB0_mstory3[7].func = func_8010D774_mstory3;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    Hu3DModelPosSet(obj->model[1], 500.0f, 0.0f, 700.0f);
    Hu3DModelPosSet(obj->model[2], 500.0f, -5.0f, 700.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 270.0f, 0.0f);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[D_80115CB0_mstory3[6].obj->motion[1]].motId, 0, 10, 2);
    omPrcSetDestructor(0, func_80113960_mstory3);
    while (1) {
        D_80115CB0_mstory3[7].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B24_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B30_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B3C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B48_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B54_mstory3);

const Vec D_80115B60_mstory3 = { -400.0f, 0.0f, 700.0f };

void func_80113AA8_mstory3(omObjData *obj) {
    func_80106DC4_mstory3(obj, &D_80115B60_mstory3, 60);
    Hu3DModelPosSet(obj->model[1], -500.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -500.0f, 0.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115CB0_mstory3[7].unk_08 = 1;
    D_80115CB0_mstory3[7].func = func_8010D774_mstory3;
}

void func_80113B3C_mstory3(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[D_80115CB0_mstory3[6].obj->motion[3]].motId, 0, 0xA, 2);
    D_80115CB0_mstory3[7].func = func_8010D774_mstory3;
}

void func_80113BA8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113BB0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80113E68_mstory3);

void func_80114260_mstory3(void) {
    func_80107674_mstory3(D_80115CB0_mstory3[5].obj, D_80115CB0_mstory3[0].obj);
    func_80107674_mstory3(D_80115CB0_mstory3[0].obj, D_80115CB0_mstory3[5].obj);
    func_80107674_mstory3(D_80115CB0_mstory3[4].obj, D_80115CB0_mstory3[5].obj);
    func_80107674_mstory3(D_80115CB0_mstory3[3].obj, D_80115CB0_mstory3[5].obj);
}

void func_801142C0_mstory3(omObjData *obj) {
    MstoryPath *path;
    Vec pos;
    s16 i;

    path = func_8010C9F0_mstory3(D_80115478_mstory3, 0);
    Hu3DModelPosSet(obj->model[2], -100.0f, 200.0f, 100.0f);
    func_8000CFA4_main(obj->model[5], -100.0f, 200.0f, 100.0f);
    func_8001C258_main(obj->model[2], 4, 0);
    func_8001C258_main(obj->model[5], 4, 0);
    func_800138EC_main(obj->model[5], 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 30; i++) {
        func_8010CCF4_mstory3(path, (i * (1.0f / 30.0f)) * (i * (1.0f / 30.0f)), &pos);
        pos.x -= 100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115CB0_mstory3[8].obj->model[5], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8010D59C_mstory3(path);
    D_80115CB0_mstory3[8].unk_08 = 1;
    D_80115CB0_mstory3[8].func = func_8010D774_mstory3;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_80114474_mstory3);

void func_8011475C_mstory3(omObjData *obj) {
    Vec pos;
    s16 i;

    pos.x = Hu3DData[obj->model[4]].pos.x;
    pos.y = Hu3DData[obj->model[4]].pos.y;
    pos.z = Hu3DData[obj->model[4]].pos.z;
    for (i = 0; i < 50; i++) {
        pos.x -= 3.5;
        pos.y += 1.75;
        pos.z += 19.25;
        Hu3DData[obj->model[2]].pos.z = Hu3DData[obj->model[4]].pos.z = pos.z;
        Hu3DData[obj->model[2]].pos.y = Hu3DData[obj->model[4]].pos.y = pos.y;
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[4]].pos.x = pos.x;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[8].func = func_8010D774_mstory3;
}

void func_80114920_mstory3(omObjData *obj) {
    s16 i;

    for (i = 0; i < 60; i++) {
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[4]].pos.x += 15.0f;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[8].func = func_8010D774_mstory3;
}

void func_801149D0_mstory3(void) {
    while (TRUE) {
        if (D_80115D96_mstory3 == 1) {
            Hu3DData[D_80115CB0_mstory3[8].obj->model[2]].rot.y += 12.0f;
            Hu3DData[D_80115CB0_mstory3[8].obj->model[7]].pos.x = Hu3DData[D_80115CB0_mstory3[8].obj->model[4]].pos.x;
            Hu3DData[D_80115CB0_mstory3[8].obj->model[7]].pos.y = -85.8f;
            Hu3DData[D_80115CB0_mstory3[8].obj->model[7]].pos.z = Hu3DData[D_80115CB0_mstory3[8].obj->model[4]].pos.z;
        }
        HuPrcVSleep();
    }
}

void func_80114AF8_mstory3(void) {
}

void func_80114B00_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[9].obj = obj;
    D_80115CB0_mstory3[9].unk_08 = 0;
    D_80115CB0_mstory3[9].func = func_8010D774_mstory3;
    obj->model[1] = func_8000B108_main(0x1D0030, 0x2A8);
    obj->model[2] = func_8000B108_main(0x83, 0x2B9);
    obj->model[3] = func_8000B108_main(0x83, 0x2B9);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8001FA68_main(obj->model[1]);
    func_8001F9E4_main(obj->model[1], 255);
    Hu3DModelPosSet(obj->model[1], 0.0f, -25.0f, 800.0f);
    Hu3DModelScaleSet(obj->model[1], 0.0f, 0.0f, 1.0f);
    func_8000B460_main(obj, 0, 0x1D0030);
    func_8000B460_main(obj, 1, 0x83);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    omPrcSetDestructor(0, func_80114AF8_mstory3);
    while (1) {
        D_80115CB0_mstory3[9].func(obj);
        HuPrcVSleep();
    }
}

void func_80114CD8_mstory3(omObjData *obj) {
    s16 i;
    f32 scale;

    HuPrcSleep(10);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_8001C258_main(obj->model[3], 4, 0);
    func_8001C258_main(obj->model[4], 4, 0);
    HuAudFXPlay(0x220);
    for (i = 0; i < 10; i++) {
        scale = sindf(i * 9.0f) * 2.0f;
        Hu3DModelScaleSet(obj->model[1], scale, scale, 1.0f);
        HuPrcVSleep();
    }
    Hu3DData[D_80115CB0_mstory3[2].obj->model[1]].pos.x = Hu3DData[D_80115CB0_mstory3[2].obj->model[2]].pos.x = 100.0f;
    Hu3DData[D_80115CB0_mstory3[3].obj->model[1]].rot.y = 0.0f;
    Hu3DData[D_80115CB0_mstory3[4].obj->model[1]].rot.y = 0.0f;
    Hu3DData[D_80115CB0_mstory3[0].obj->model[1]].rot.y = 0.0f;
    Hu3DMotionShiftSet(D_80115CB0_mstory3[4].obj->model[1], Hu3DData[D_80115CB0_mstory3[4].obj->motion[4]].motId, 0, 10, 2);
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D94_mstory3);
    D_80115CB0_mstory3[9].func = func_80114FA4_mstory3;
}

void func_80114EF8_mstory3(omObjData *obj) {
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    HuPrcSleep(30);
    Hu3DMotionSpeedSet(D_80115CB0_mstory3[2].obj->model[1], 1.0f);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[2].obj->model[1], Hu3DData[D_80115CB0_mstory3[2].obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[9].unk_08 = 1;
    D_80115CB0_mstory3[9].func = func_8010D774_mstory3;
}

void func_80114FA4_mstory3(omObjData *obj) {
    f32 angle;
    s16 i;

    for (i = 2; i < 5; i++) {
        if (D_80115C9C_mstory3[i] == 0) {
            if ((u8)(rand8() % 7) == 0) {
                angle = (u8)(rand8() % 200) - 10.0f;
                Hu3DModelPosSet(obj->model[i], cosdf(angle) * 175.0f, sindf(angle) * 175.0f, 500.0f);
                func_8001C5B4_main(obj->model[i], obj->motion[1]);
                D_80115C9C_mstory3[i] = 1;
                D_80115CA2_mstory3[i] = 10;
            }
        } else if (--D_80115CA2_mstory3[i] <= 0) {
            D_80115C9C_mstory3[i] = 0;
        }
    }
}

void func_8011517C_mstory3(omObjData *obj) {
    do {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[8 + (rand8() & 1)]].motId, 0, 10, 0);
        func_80107244_mstory3(obj->model[1]);
        HuPrcVSleep();
    } while (D_80115CB0_mstory3[2].unk_08 != 1);
    D_80115CB0_mstory3[2].func = func_8011522C_mstory3;
}

void func_8011522C_mstory3(omObjData *obj) {
    D_80115CB0_mstory3[5].func = func_8011322C_mstory3;
    D_80115CB0_mstory3[2].func = func_8010D774_mstory3;
    D_80115CB0_mstory3[2].unk_08 = 0;
}
