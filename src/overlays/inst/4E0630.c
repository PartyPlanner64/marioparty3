#include "common.h"
#include "inst.h"

extern InstModelHooks *D_8010D4C0_inst[][2];
extern const s32 D_8010D910_inst[][2];
extern s32 D_8010D4A4_inst;
extern s8 D_8010D408_inst;
extern s8 D_8010D40A_inst;
extern f32 D_8010D414_inst;
extern void *D_8010DC10_inst;
extern void *D_8010DC14_inst;
extern void *D_8010DC18_inst;
extern InstObjectState D_8010DDD8_inst;
extern s32 D_8010D508_inst;
extern f32 D_8010D50C_inst;
extern s32 D_8010D510_inst;

extern const char D_8010D784_inst[];
extern const char D_8010D78C_inst[];
extern const char D_8010D794_inst[];
extern const char D_8010D79C_inst[];
extern const char D_8010D7AC_inst[];
extern const char D_8010D7C4_inst[];
extern const char D_8010D7CC_inst[];
extern const char D_8010D7D4_inst[];
extern const char D_8010D7DC_inst[];
extern const char D_8010D800_inst[];
extern const char D_8010D808_inst[];
extern const char D_8010D810_inst[];
extern const char D_8010D818_inst[];
extern const char D_8010D83C_inst[];
extern const char D_8010D844_inst[];
extern const char D_8010D84C_inst[];
extern const char D_8010D854_inst[];
extern const char D_8010D870_inst[];
extern const char D_8010D878_inst[];
extern const char D_8010D890_inst[];
extern const char D_8010D8B4_inst[];
extern const char D_8010D8BC_inst[];
extern const char D_8010D8C4_inst[];
extern const char D_8010D8CC_inst[];
extern const char D_8010D8D4_inst[];
extern const char D_8010D8E4_inst[];
extern const char D_8010D8FC_inst[];
extern const char D_8010D978_inst[];
extern const char D_8010D980_inst[];

const InstModelHooks4 D_8010D770_inst = {4, {D_8010D79C_inst, D_8010D794_inst, D_8010D78C_inst, D_8010D784_inst}};

const char D_8010D784_inst[] = "4p_4";

const char D_8010D78C_inst[] = "4p_3";

const char D_8010D794_inst[] = "4p_2";

const char D_8010D79C_inst[] = "4p_1";

const InstModelHooks D_8010D7A4_inst = {0, {D_8010D7AC_inst}};

const char D_8010D7AC_inst[4] = "";

const InstModelHooks4 D_8010D7B0_inst = {4, {D_8010D7DC_inst, D_8010D7D4_inst, D_8010D7CC_inst, D_8010D7C4_inst}};

const char D_8010D7C4_inst[] = "2vs2_4";

const char D_8010D7CC_inst[] = "2vs2_3";

const char D_8010D7D4_inst[] = "2vs2_2";

const char D_8010D7DC_inst[] = "2vs2_1";

const InstModelHooks D_8010D7E4_inst = {0, {D_8010D7AC_inst}};

const InstModelHooks4 D_8010D7EC_inst = {4, {D_8010D818_inst, D_8010D810_inst, D_8010D808_inst, D_8010D800_inst}};

const char D_8010D800_inst[] = "3vs1_4";

const char D_8010D808_inst[] = "3vs1_3";

const char D_8010D810_inst[] = "3vs1_2";

const char D_8010D818_inst[] = "3vs1_1";

const InstModelHooks D_8010D820_inst = {0, {D_8010D7AC_inst}};

const InstModelHooks4 D_8010D828_inst = {4, {D_8010D854_inst, D_8010D84C_inst, D_8010D844_inst, D_8010D83C_inst}};

const char D_8010D83C_inst[] = "battle4";

const char D_8010D844_inst[] = "battle3";

const char D_8010D84C_inst[] = "battle2";

const char D_8010D854_inst[] = "battle1";

const InstModelHooks D_8010D85C_inst = {0, {D_8010D7AC_inst}};

const InstModelHooks2 D_8010D864_inst = {2, {D_8010D878_inst, D_8010D870_inst}};

const char D_8010D870_inst[] = "duel2";

const char D_8010D878_inst[] = "duel1";

const InstModelHooks D_8010D880_inst = {0, {D_8010D7AC_inst}};

const InstModelHooks D_8010D888_inst = {1, {D_8010D890_inst}};

const char D_8010D890_inst[] = "item_chara";

const InstModelHooks5 D_8010D89C_inst = {5, {D_8010D8D4_inst, D_8010D8CC_inst, D_8010D8C4_inst, D_8010D8BC_inst, D_8010D8B4_inst}};

const char D_8010D8B4_inst[] = "item5";

const char D_8010D8BC_inst[] = "item4";

const char D_8010D8C4_inst[] = "item3";

const char D_8010D8CC_inst[] = "item2";

const char D_8010D8D4_inst[] = "item1";

const InstModelHooks D_8010D8DC_inst = {1, {D_8010D8E4_inst}};

const char D_8010D8E4_inst[] = "omake1";

const InstModelHooks D_8010D8EC_inst = {0, {D_8010D7AC_inst}};

const InstModelHooks D_8010D8F4_inst = {1, {D_8010D8FC_inst}};

const char D_8010D8FC_inst[] = "last1";

const InstModelHooks D_8010D904_inst = {0, {D_8010D7AC_inst}};

const s32 D_8010D90C_inst[][2] = {
    {0x10, 0x18}, {0x11, 0x19}, {0x12, 0x1A},
    {0x13, 0x1B}, {0x14, 0x1C}, {0x15, 0x1D},
    {0x15, 0x1D}, {0x17, 0x1F}, {0x16, 0x1E},
};

const s32 D_8010D954_inst[] = {
    0x170020, 0x170021, 0x170022, 0x170023, 0x170024,
    0x170025, 0x170025, 0x170027, 0x170026,
};

const char D_8010D978_inst[] = "gamen";

const char D_8010D980_inst[] = "frame";

s16 func_8000B0D4_main(s32, u16);
void func_80107E98_inst(void);
s32 func_80107E20_inst(void);
void func_80107BE4_inst(void);
void func_80107938_inst(omObjData *);
void func_8010815C_inst(omObjData *);
void func_80107EE0_inst(void);
void func_80108AF0_inst(s16, void *, void *, void *);
void func_80107470_inst(void); /* extern */
void func_801079CC_inst(omObjData *);
s32 func_8010B10C_inst(void);
void func_80107E18_inst(omObjData *);
void func_80107F98_inst(omObjData *);
void func_8010B124_inst(void);
void func_80107A24_inst(omObjData *); /* extern */
void func_80107BF8_inst(omObjData *); /* extern */
HmfSkeletonNode *func_8001D33C_main(s16, const char *);

void func_80107470_inst(void) {
    s32 i;
    s32 j;
    omObjData *object;
    InstModelHooks *hooks;
    s32 group;
    HmfMotionNode *node;
    HmfData *data;
    HmfModelData_Unk64_Unk60_Struct *material;

    object = omAddObj(20, 10, 5, -1, NULL);
    D_8010DDD8_inst.object = object;
    object->model[0] = func_8000B0D4_main(D_8010D90C_inst[D_8010D40A_inst][0] | 0x170000, 0x16B9);
    object->model[1] = func_8000B0D4_main(0x170029, 0x1E89);
    object->model[2] = func_8000B0D4_main(D_8010D954_inst[D_8010D40A_inst], 0x1AB9);
    object->model[3] = func_8000B0D4_main(0x170028, 0x2B9);
    object->model[4] = func_8000B0D4_main(D_8010D910_inst[D_8010D40A_inst][0] | 0x170000, 0x239);
    func_8001C814_main(object->model[0], 2, 0);
    func_8001C814_main(object->model[1], 2, 0);
    func_8001C814_main(object->model[2], 2, 0);
    func_8001C814_main(object->model[3], 2, 0);
    func_8001C814_main(object->model[0], 1, 1);
    func_8001C814_main(object->model[1], 1, 1);
    func_8001C814_main(object->model[2], 1, 1);
    func_8001C814_main(object->model[3], 1, 1);
    func_8001C258_main(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->trans.x = 0;
    object->trans.y = 0;
    object->trans.z = 0;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], 56.0f, 0.0f, 61.5f);
    Hu3DModelPosSet(object->model[2], 56.0f, 0.0f, 61.5f);
    Hu3DModelPosSet(object->model[3], 56.0f, 0.0f, 61.5f);
    Hu3DModelPosSet(object->model[4], object->trans.x, object->trans.y, object->trans.z);
    object->scale.x = object->scale.y = object->scale.z = 0.5f;
    for (i = 0; i < 5; i++) {
        Hu3DModelScaleSet(object->model[i], 0.5f, 0.5f, 0.5f);
    }
    for (i = 0; i < 3; i++) {
        Hu3DModelScaleSet(object->model[i + 1], 0.45f, 0.45f, 0.45f);
    }
    for (group = 0; group < 2; group++) {
        hooks = D_8010D4C0_inst[D_8010D40A_inst][group];
        for (j = 0; j < hooks->count; j++) {
            node = (HmfMotionNode *)func_8001D33C_main(object->model[0], hooks->nodes[j]);
            data = node->unk54;
            for (i = 0; i < node->unk00; i++) {
                if (node->unk50[i] >= 0) {
                    material = &data->unk60[node->unk50[i]];
                    material->unk24 = 1;
                }
            }
        }
    }
    D_8010DC10_inst = DataRead(D_8010D4A4_inst | 0x170000);
    D_8010DC18_inst = DataRead((D_8010D4A4_inst + 1) | 0x170000);
    D_8010DC14_inst = DataRead(0x170007);
    func_80108AF0_inst(object->model[1], D_8010DC18_inst, D_8010DC10_inst, D_8010DC14_inst);
    HmfModelData[object->model[1]].rot.x = -90.0f;
    omPrcSetDestructor(NULL, func_80107EE0_inst);
    if (D_8010D408_inst == 0) {
        D_8010DDD8_inst.update = func_80107938_inst;
    } else {
        D_8010DDD8_inst.update = func_8010815C_inst;
    }
    while (1) {
        D_8010DDD8_inst.update(object);
        HuPrcVSleep();
    }
}

void func_80107938_inst(omObjData *obj) {
    if ((s8)func_8010B10C_inst() == 1) {
        func_8001C814_main(obj->model[1], 1, 0);
        func_8001C814_main(obj->model[2], 1, 0);
        func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        D_8010DDD8_inst.update = func_801079CC_inst;
    }
}

void func_801079CC_inst(omObjData *obj) {
    func_8001C814_main(obj->model[3], 1, 0);
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    D_8010DDD8_inst.update = func_80107A24_inst;
}

void func_80107A24_inst(omObjData *object) {
    f32 duration = D_800CCF58_main[HmfModelData[object->model[3]].motId].unk02 - 25.0f;
    f32 angle = ((f32)D_8010D508_inst / duration) * D_8010D414_inst;
    s32 i;

    HmfModelData[object->model[1]].rot.x = angle - 90.0f;
    HmfModelData[object->model[2]].rot.x = angle;
    D_8010D50C_inst = (0.15f / duration) * D_8010D508_inst;
    for (i = 0; i < 3; i++) {
        Hu3DModelScaleSet(object->model[i + 1], D_8010D50C_inst + 0.45f, D_8010D50C_inst + 0.45f,
                          D_8010D50C_inst + 0.45f);
    }
    D_8010D508_inst++;
    if ((f32)D_8010D508_inst == duration) {
        D_8010DDD8_inst.update = func_80107E18_inst;
        D_8010D50C_inst = 0;
        D_8010D508_inst = 0;
    }
}

void func_80107BE4_inst(void) {
    D_8010DDD8_inst.update = func_80107BF8_inst;
}

void func_80107BF8_inst(omObjData *object) {
    HmfSkeletonNode *nodes[2];
    s32 i;
    s32 j;
    f32 scale;

    nodes[0] = func_8001D33C_main(object->model[1], D_8010D978_inst);
    nodes[1] = func_8001D33C_main(object->model[2], D_8010D980_inst);
    if (nodes[0] == (HmfSkeletonNode *)-1 || nodes[1] == (HmfSkeletonNode *)-1) {
        osSyncPrintf("ERROR\n");
    }
    for (i = 0; i < 5; i++) {
        scale = sindf(i * 18.0f) * 0.5f;
        for (j = 0; j < 2; j++) {
            nodes[j]->unk4C[0][0] = scale + 1.0f;
            nodes[j]->unk4C[1][1] = scale + 1.0f;
            nodes[j]->unk4C[2][2] = scale + 1.0f;
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 5; i++) {
        scale = cosdf(i * 18.0f) * 0.5f;
        if (scale < 0.3f) {
            scale = 0.3f;
        }
        for (j = 0; j < 2; j++) {
            nodes[j]->unk4C[0][0] = scale + 1.0f;
            nodes[j]->unk4C[1][1] = scale + 1.0f;
            nodes[j]->unk4C[2][2] = scale + 1.0f;
        }
        HuPrcVSleep();
    }
    for (j = 0; j < 2; j++) {
        nodes[j]->unk4C[0][0] = 1.3f;
        nodes[j]->unk4C[1][1] = 1.3f;
        nodes[j]->unk4C[2][2] = 1.3f;
    }
    D_8010DDD8_inst.update = func_80107E18_inst;
}

void func_80107E18_inst(omObjData *object) {
}

s32 func_80107E20_inst(void) {
    s16 modelId = D_8010DDD8_inst.object->model[0];
    f32 unk40 = HmfModelData[modelId].motTime;
    return D_800CCF58_main[HmfModelData[modelId].motId].unk02 <= unk40;
}

void func_80107E98_inst(void) {
    Hu3DMotionTimeSet(D_8010DDD8_inst.object->model[0], 0);
    func_8001C814_main(D_8010DDD8_inst.object->model[0], 1, 0);
}

void func_80107EE0_inst(void) {
    DataClose(D_8010DC18_inst);
    DataClose(D_8010DC10_inst);
    DataClose(D_8010DC14_inst);
}

void func_80107F18_inst(void) {
    omObjData *object = D_8010DDD8_inst.object;

    func_8001C814_main(object->model[3], 1, 0);
    func_8001C814_main(object->model[3], 4, 4);
    func_8001C258_main(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8010B124_inst();
    D_8010DDD8_inst.update = func_80107F98_inst;
}

void func_80107F98_inst(omObjData *obj) {
    f32 duration = D_800CCF58_main[HmfModelData[obj->model[3]].motId].unk02 - 25.0f;
    f32 angle = D_8010D414_inst - ((f32)D_8010D510_inst / duration) * D_8010D414_inst;

    HmfModelData[obj->model[1]].rot.x = angle - 90.0f;
    HmfModelData[obj->model[2]].rot.x = angle;
    D_8010D510_inst++;
    if ((f32)D_8010D510_inst == duration) {
        D_8010DDD8_inst.update = func_80107BF8_inst;
        D_8010D510_inst = 0;
    }
}

s32 func_801080A8_inst(void) {
    f32 unk40 = HmfModelData[D_8010DDD8_inst.object->model[0]].motTime;
    return unk40 == 0.0f;
}

void func_801080FC_inst(void) {
    omObjData *obj = D_8010DDD8_inst.object;

    func_8001C814_main(obj->model[0], 1, 0);
    func_8001C258_main(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C814_main(obj->model[0], 4, 4);
}

void func_8010815C_inst(omObjData *obj) {
    HmfSkeletonNode *nodes[2];
    s32 i;
    f32 duration = D_800CCF58_main[HmfModelData[obj->model[0]].motId].unk02;

    func_8001C814_main(obj->model[0], 1, 0);
    func_8001C258_main(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionTimeSet(obj->model[0], duration);
    HmfModelData[obj->model[1]].rot.x = D_8010D414_inst - 90.0f;
    HmfModelData[obj->model[2]].rot.x = D_8010D414_inst;
    for (i = 0; i < 3; i++) {
        Hu3DModelScaleSet(obj->model[i + 1], 0.6f, 0.6f, 0.6f);
        func_8001C258_main(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    nodes[0] = func_8001D33C_main(obj->model[1], D_8010D978_inst);
    nodes[1] = func_8001D33C_main(obj->model[2], D_8010D980_inst);
    for (i = 0; i < 2; i++) {
        nodes[i]->unk4C[0][0] = 1.3f;
        nodes[i]->unk4C[1][1] = 1.3f;
        nodes[i]->unk4C[2][2] = 1.3f;
    }
    D_8010DDD8_inst.update = func_80107E18_inst;
}
