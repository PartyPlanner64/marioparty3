#include "common.h"
#include "game/hmfspr.h"
#include "mgresultbattle.h"

typedef struct MgResultBattleGroupSprites {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
} MgResultBattleGroupSprites; // Size 0x6

extern u16 D_80108F30_mgresultbattle[];
extern MgResultBattleGroupSprites D_80108F38_mgresultbattle[];
extern omObjData *D_80108F7C_mgresultbattle;
extern omObjFunc D_80108F88_mgresultbattle;
extern Vec D_801089D0_mgresultbattle[4];

void func_801082C0_mgresultbattle(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_80107D10_mgresultbattle);

void func_80107F94_mgresultbattle(void) {
}

void func_80107F9C_mgresultbattle(omObjData *obj) {
    HuMtx4F mtx;
    s32 i;

    for (i = 0; i < 4; i++) {
        func_80016B00_main(obj->model[i + 1], HmfModelData[obj->model[i + 1]].motTime, "chara", &mtx);
        Hu3DModelPosSet(D_80108F50_mgresultbattle[i].obj->model[1], mtx[3][0] + D_801089D0_mgresultbattle[i].x,
                        mtx[3][1] + D_801089D0_mgresultbattle[i].y, mtx[3][2] + D_801089D0_mgresultbattle[i].z);
    }
}

void func_801080A0_mgresultbattle(void) {
    omObjData *obj = D_80108F7C_mgresultbattle;
    s32 i;

    for (i = 0; i < 4; i++) {
        func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8001C814_main(obj->model[i + 1], 1, 0);
        Hu3DMotionTimeSet(obj->model[i + 1], 0.0f);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_80108130_mgresultbattle);

void func_8010829C_mgresultbattle(void) {
}

void func_801082A4_mgresultbattle(void) {
}

void func_801082AC_mgresultbattle(void) {
    D_80108F88_mgresultbattle = func_801082C0_mgresultbattle;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_801082C0_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_80108510_mgresultbattle);

void func_80108858_mgresultbattle(s16 group) {
    espDispOff(D_80108F30_mgresultbattle[group]);
    espDispOff(D_80108F38_mgresultbattle[group].unk_00);
    espDispOff(D_80108F38_mgresultbattle[group].unk_02);
    espDispOff(D_80108F38_mgresultbattle[group].unk_04);
}
