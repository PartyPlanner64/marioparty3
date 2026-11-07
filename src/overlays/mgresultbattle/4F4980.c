#include "common.h"
#include "mgresultbattle.h"

typedef struct {
    /* 0x00 */ u8 state;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ f32 unk1C;
} ResultBattleEffect; /* size = 0x20 */

void func_80107610_mgresultbattle(omObjData *);

extern omObjData *D_80108F90_mgresultbattle;
extern omObjFunc D_80108F94_mgresultbattle;
extern s32 D_801088E0_mgresultbattle[];
extern ResultBattleEffect D_80108A30_mgresultbattle[40];

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F4980", func_80106BA0_mgresultbattle);

void func_80106E98_mgresultbattle(void) {
}

void func_80106EA0_mgresultbattle(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_801088E0_mgresultbattle[i] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F4980", func_80106ED0_mgresultbattle);

void func_80107260_mgresultbattle(f32 x, f32 y, f32 z, s32 count, f32 arg4) {
    s32 n;
    s32 i;

    n = 0;
    for (i = 0; i < 40; i++) {
        if (D_80108A30_mgresultbattle[i].state == 1) {
            D_80108A30_mgresultbattle[i].state = 4;
            D_80108A30_mgresultbattle[i].unk08 = n++;
            D_80108A30_mgresultbattle[i].x = x + (u8)(rand8() % 50);
            D_80108A30_mgresultbattle[i].y = y;
            D_80108A30_mgresultbattle[i].z = z + (u8)(rand8() % 50);
            D_80108A30_mgresultbattle[i].unk18 = 0;
            D_80108A30_mgresultbattle[i].unk1C = arg4;
        }
        if (n >= count) {
            break;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089A0_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F4980", func_80107400_mgresultbattle);

void func_801075EC_mgresultbattle(void) {
}

void func_801075F4_mgresultbattle(void) {
}

void func_801075FC_mgresultbattle(void) {
    D_80108F94_mgresultbattle = func_80107610_mgresultbattle;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F4980", func_80107610_mgresultbattle);

void func_80107B5C_mgresultbattle(f32 arg0, f32 arg1, f32 arg2) {
    omObjData *itemObj = D_80108F90_mgresultbattle;

    Hu3DModelPosSet(itemObj->model[1], arg0, arg1, arg2);
    Hu3DModelPosSet(itemObj->model[3], arg0, arg1, arg2);
}

void func_80107BDC_mgresultbattle(f32 arg0) {
    omObjData *itemObj = D_80108F90_mgresultbattle;

    Hu3DModelRotSet(itemObj->model[1], 0.0f, 0.0f, arg0);
    Hu3DModelRotSet(itemObj->model[3], 0.0f, 0.0f, arg0);
}

void func_80107C44_mgresultbattle(void) {
    omObjData *itemObj = D_80108F90_mgresultbattle;

    func_8001C258_main(itemObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(itemObj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(itemObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void func_80107CA4_mgresultbattle(void) {
    omObjData *itemObj = D_80108F90_mgresultbattle;

    func_8001C258_main(itemObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(itemObj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(itemObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089C0_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089D0_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089D4_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_801089D8_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_80108A00_mgresultbattle);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultbattle/4F4980", D_80108A10_mgresultbattle);
