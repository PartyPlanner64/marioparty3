#include "common.h"
#include "game/hmfspr.h"
#include "mgresultbattle.h"

typedef struct {
    /* 0x00 */ u8 state;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ f32 unk1C;
} ResultBattleEffect; /* size = 0x20 */

void func_80106E98_mgresultbattle(void);
void func_80106ED0_mgresultbattle(omObjData *);
void func_80107610_mgresultbattle(omObjData *);
void func_801075EC_mgresultbattle(void);
void func_801075F4_mgresultbattle(omObjData *);
void func_80107CA4_mgresultbattle(void);

extern ResultBattlePlayerObj D_80108F90_mgresultbattle;
extern s32 D_801088E0_mgresultbattle[];
extern ResultBattleEffect D_80108A30_mgresultbattle[40];
extern omObjData *D_80108F74_mgresultbattle;
extern omObjFunc D_80108F78_mgresultbattle;

void func_80106BA0_mgresultbattle(void) {
    omObjData *obj;
    void *data;
    u16 sprite1;
    u16 sprite2;
    s32 i;

    obj = omAddObj(0x14, 0x58, 8, -1, NULL);
    D_80108F74_mgresultbattle = obj;

    data = DataRead(0x210026);
    sprite1 = HmfSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    func_8001C2FC_main(D_800CBB60_main[sprite1].modelId, 0x70000000, 0x70000000);

    data = DataRead(0xC);
    sprite2 = HmfSprModelCreate(data, 0x2BD, 8);
    DataClose(data);
    func_8001C2FC_main(D_800CBB60_main[sprite2].modelId, 0x70000000, 0x70000000);

    for (i = 0; i < 40; i++) {
        D_80108A30_mgresultbattle[i].state = 1;
        D_80108A30_mgresultbattle[i].unk02 = func_80014618_main(sprite1, 8);
        D_80108A30_mgresultbattle[i].unk04 = func_80014618_main(sprite2, 8);
        D_80108A30_mgresultbattle[i].unk08 = 0;
        D_80108A30_mgresultbattle[i].unk18 = 0;
        D_80108A30_mgresultbattle[i].unk1C = 0.0f;
        obj->model[i + 1] = D_800CBB60_main[D_80108A30_mgresultbattle[i].unk02].modelId;
        Hu3DMotionSpeedSet(obj->model[i + 1], 2.0f);
        Hu3DModelScaleSet(D_800CBB60_main[i + 1].modelId, 3.0f, 3.0f, 3.0f);
        func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        obj->model[i + 41] = D_800CBB60_main[D_80108A30_mgresultbattle[i].unk04].modelId;
        Hu3DModelScaleSet(D_800CBB60_main[i + 41].modelId, 3.0f, 3.0f, 3.0f);
    }

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(NULL, func_80106E98_mgresultbattle);
    D_80108F78_mgresultbattle = func_80106ED0_mgresultbattle;

    while (TRUE) {
        D_80108F78_mgresultbattle(obj);
        HuPrcVSleep();
    }
}

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

void func_80107400_mgresultbattle(void) {
    omObjData *itemObj;

    itemObj = omAddObj(20, 4, 8, -1, NULL);
    D_80108F90_mgresultbattle.obj = itemObj;
    itemObj->model[1] = func_8000B108_main(0xA00A5, 0x2B9);
    func_8001C814_main(itemObj->model[1], 2, 2);
    func_8001C258_main(itemObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    itemObj->model[2] = func_8000B108_main(0x1B0000, 0x2B9);
    func_8001C258_main(itemObj->model[2], 0x4000, 0x4000);
    func_8001C814_main(itemObj->model[2], 2, 2);
    func_8001C258_main(itemObj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelHookSet(itemObj->model[2], itemObj->model[1], "item_hook");
    itemObj->model[3] = func_8000B108_main(0x130200, 0x2B9);
    func_8001C814_main(itemObj->model[3], 2, 2);
    func_8001C258_main(itemObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8000B460_main(itemObj, 0, 0xA00A6);
    func_8000B460_main(itemObj, 1, 0xA00B6);
    func_8001C5B4_main(itemObj->model[1], itemObj->motion[1]);
    func_8001C814_main(itemObj->model[1], 2, 2);
    func_80107CA4_mgresultbattle();
    itemObj->trans.x = 0.0f;
    itemObj->trans.y = 0.0f;
    itemObj->trans.z = 0.0f;
    Hu3DModelPosSet(itemObj->model[0], itemObj->trans.x, itemObj->trans.y, itemObj->trans.z);
    omPrcSetDestructor(NULL, func_801075EC_mgresultbattle);
    D_80108F90_mgresultbattle.func = func_801075F4_mgresultbattle;
    while (TRUE) {
        D_80108F90_mgresultbattle.func(itemObj);
        HuPrcVSleep();
    }
}

void func_801075EC_mgresultbattle(void) {
}

void func_801075F4_mgresultbattle(omObjData *object) {
}

void func_801075FC_mgresultbattle(void) {
    D_80108F90_mgresultbattle.func = func_80107610_mgresultbattle;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F4980", func_80107610_mgresultbattle);

void func_80107B5C_mgresultbattle(f32 arg0, f32 arg1, f32 arg2) {
    omObjData *itemObj = D_80108F90_mgresultbattle.obj;

    Hu3DModelPosSet(itemObj->model[1], arg0, arg1, arg2);
    Hu3DModelPosSet(itemObj->model[3], arg0, arg1, arg2);
}

void func_80107BDC_mgresultbattle(f32 arg0) {
    omObjData *itemObj = D_80108F90_mgresultbattle.obj;

    Hu3DModelRotSet(itemObj->model[1], 0.0f, 0.0f, arg0);
    Hu3DModelRotSet(itemObj->model[3], 0.0f, 0.0f, arg0);
}

void func_80107C44_mgresultbattle(void) {
    omObjData *itemObj = D_80108F90_mgresultbattle.obj;

    func_8001C258_main(itemObj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(itemObj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(itemObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void func_80107CA4_mgresultbattle(void) {
    omObjData *itemObj = D_80108F90_mgresultbattle.obj;

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
