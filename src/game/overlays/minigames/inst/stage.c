#include "common.h"
#include "inst.h"

extern InstModelHooks *inst_hookTbl[][2];
extern const s32 inst_boxFileTbl1[][2];
extern s32 inst_picNo;
extern s8 inst_introSkipF;
extern s8 inst_mgType;
extern f32 inst_cameraTilt;
extern void *inst_picData;
extern void *inst_picAlpha;
extern void *inst_picHeader;
extern InstObjectState inst_boxWork;
extern s32 inst_boxOpenCnt;
extern f32 inst_picScaleOfs;
extern s32 inst_boxCloseCnt;

extern const char inst_mg4PHook4Name[];
extern const char inst_mg4PHook3Name[];
extern const char inst_mg4PHook2Name[];
extern const char inst_mg4PHook1Name[];
extern const char inst_emptyHookName[];
extern const char inst_mg2vs2Hook4Name[];
extern const char inst_mg2vs2Hook3Name[];
extern const char inst_mg2vs2Hook2Name[];
extern const char inst_mg2vs2Hook1Name[];
extern const char inst_mg3vs1Hook4Name[];
extern const char inst_mg3vs1Hook3Name[];
extern const char inst_mg3vs1Hook2Name[];
extern const char inst_mg3vs1Hook1Name[];
extern const char inst_battleHook4Name[];
extern const char inst_battleHook3Name[];
extern const char inst_battleHook2Name[];
extern const char inst_battleHook1Name[];
extern const char inst_duelHook2Name[];
extern const char inst_duelHook1Name[];
extern const char inst_itemChrHookName[];
extern const char inst_itemHook5Name[];
extern const char inst_itemHook4Name[];
extern const char inst_itemHook3Name[];
extern const char inst_itemHook2Name[];
extern const char inst_itemHook1Name[];
extern const char inst_omakeHook1Name[];
extern const char inst_lastHook1Name[];
extern const char inst_picNodeName[];
extern const char inst_frameNodeName[];

const InstModelHooks4 inst_mg4PPlayerHooks = {4, {inst_mg4PHook1Name, inst_mg4PHook2Name, inst_mg4PHook3Name, inst_mg4PHook4Name}};

const char inst_mg4PHook4Name[] = "4p_4";

const char inst_mg4PHook3Name[] = "4p_3";

const char inst_mg4PHook2Name[] = "4p_2";

const char inst_mg4PHook1Name[] = "4p_1";

const InstModelHooks inst_mg4PItemHooks = {0, {inst_emptyHookName}};

const char inst_emptyHookName[4] = "";

const InstModelHooks4 inst_mg2vs2PlayerHooks = {4, {inst_mg2vs2Hook1Name, inst_mg2vs2Hook2Name, inst_mg2vs2Hook3Name, inst_mg2vs2Hook4Name}};

const char inst_mg2vs2Hook4Name[] = "2vs2_4";

const char inst_mg2vs2Hook3Name[] = "2vs2_3";

const char inst_mg2vs2Hook2Name[] = "2vs2_2";

const char inst_mg2vs2Hook1Name[] = "2vs2_1";

const InstModelHooks inst_mg2vs2ItemHooks = {0, {inst_emptyHookName}};

const InstModelHooks4 inst_mg3vs1PlayerHooks = {4, {inst_mg3vs1Hook1Name, inst_mg3vs1Hook2Name, inst_mg3vs1Hook3Name, inst_mg3vs1Hook4Name}};

const char inst_mg3vs1Hook4Name[] = "3vs1_4";

const char inst_mg3vs1Hook3Name[] = "3vs1_3";

const char inst_mg3vs1Hook2Name[] = "3vs1_2";

const char inst_mg3vs1Hook1Name[] = "3vs1_1";

const InstModelHooks inst_mg3vs1ItemHooks = {0, {inst_emptyHookName}};

const InstModelHooks4 inst_battlePlayerHooks = {4, {inst_battleHook1Name, inst_battleHook2Name, inst_battleHook3Name, inst_battleHook4Name}};

const char inst_battleHook4Name[] = "battle4";

const char inst_battleHook3Name[] = "battle3";

const char inst_battleHook2Name[] = "battle2";

const char inst_battleHook1Name[] = "battle1";

const InstModelHooks inst_battleItemHooks = {0, {inst_emptyHookName}};

const InstModelHooks2 inst_duelPlayerHooks = {2, {inst_duelHook1Name, inst_duelHook2Name}};

const char inst_duelHook2Name[] = "duel2";

const char inst_duelHook1Name[] = "duel1";

const InstModelHooks inst_duelItemHooks = {0, {inst_emptyHookName}};

const InstModelHooks inst_itemPlayerHooks = {1, {inst_itemChrHookName}};

const char inst_itemChrHookName[] = "item_chara";

const InstModelHooks5 inst_itemItemHooks = {5, {inst_itemHook1Name, inst_itemHook2Name, inst_itemHook3Name, inst_itemHook4Name, inst_itemHook5Name}};

const char inst_itemHook5Name[] = "item5";

const char inst_itemHook4Name[] = "item4";

const char inst_itemHook3Name[] = "item3";

const char inst_itemHook2Name[] = "item2";

const char inst_itemHook1Name[] = "item1";

const InstModelHooks inst_omakePlayerHooks = {1, {inst_omakeHook1Name}};

const char inst_omakeHook1Name[] = "omake1";

const InstModelHooks inst_omakeItemHooks = {0, {inst_emptyHookName}};

const InstModelHooks inst_lastPlayerHooks = {1, {inst_lastHook1Name}};

const char inst_lastHook1Name[] = "last1";

const InstModelHooks inst_lastItemHooks = {0, {inst_emptyHookName}};

const s32 inst_boxFileTbl[][2] = {
    {0x10, 0x18}, {0x11, 0x19}, {0x12, 0x1A},
    {0x13, 0x1B}, {0x14, 0x1C}, {0x15, 0x1D},
    {0x15, 0x1D}, {0x17, 0x1F}, {0x16, 0x1E},
};

const s32 inst_frameFileTbl[] = {
    0x170020, 0x170021, 0x170022, 0x170023, 0x170024,
    0x170025, 0x170025, 0x170027, 0x170026,
};

const char inst_picNodeName[] = "gamen";

const char inst_frameNodeName[] = "frame";

void inst_BoxMotionStart(void);
s32 inst_BoxMotionEndCheck(void);
void inst_PicPulseStart(void);
void inst_BoxOpenWait(omObjData *);
void inst_BoxOpenNow(omObjData *);
void inst_BoxDestroy(void);
void inst_PicLoad(s16 model, void *imageHeader, void *imageData, u8 *alpha);
void inst_BoxMain(void); /* extern */
void inst_BoxOpenStart(omObjData *);
s32 inst_OpenCheck(void);
void inst_BoxIdle(omObjData *);
void inst_BoxClose(omObjData *);
void inst_PlayerCloseStart(void);
void inst_BoxOpen(omObjData *); /* extern */
void inst_PicPulse(omObjData *); /* extern */

void inst_BoxMain(void) {
    s32 i;
    s32 j;
    omObjData *object;
    InstModelHooks *hooks;
    s32 group;
    HmfMotionNode *node;
    HmfData *data;
    HmfModelData_Unk64_Unk60_Struct *material;

    object = omAddObj(20, 10, 5, -1, NULL);
    inst_boxWork.object = object;
    object->model[0] = Hu3DModelRead3(inst_boxFileTbl[inst_mgType][0] | 0x170000, 0x16B9);
    object->model[1] = Hu3DModelRead3(0x170029, 0x1E89);
    object->model[2] = Hu3DModelRead3(inst_frameFileTbl[inst_mgType], 0x1AB9);
    object->model[3] = Hu3DModelRead3(0x170028, 0x2B9);
    object->model[4] = Hu3DModelRead3(inst_boxFileTbl1[inst_mgType][0] | 0x170000, 0x239);
    Hu3DMotionAttrSet(object->model[0], 2, 0);
    Hu3DMotionAttrSet(object->model[1], 2, 0);
    Hu3DMotionAttrSet(object->model[2], 2, 0);
    Hu3DMotionAttrSet(object->model[3], 2, 0);
    Hu3DMotionAttrSet(object->model[0], 1, 1);
    Hu3DMotionAttrSet(object->model[1], 1, 1);
    Hu3DMotionAttrSet(object->model[2], 1, 1);
    Hu3DMotionAttrSet(object->model[3], 1, 1);
    Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
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
        hooks = inst_hookTbl[inst_mgType][group];
        for (j = 0; j < hooks->count; j++) {
            node = (HmfMotionNode *)Hu3DModelObjPtrGet(object->model[0], hooks->nodes[j]);
            data = node->unk54;
            for (i = 0; i < node->unk00; i++) {
                if (node->unk50[i] >= 0) {
                    material = &data->unk60[node->unk50[i]];
                    material->unk24 = 1;
                }
            }
        }
    }
    inst_picData = DataRead(inst_picNo | 0x170000);
    inst_picHeader = DataRead((inst_picNo + 1) | 0x170000);
    inst_picAlpha = DataRead(0x170007);
    inst_PicLoad(object->model[1], inst_picHeader, inst_picData, inst_picAlpha);
    Hu3DData[object->model[1]].rot.x = -90.0f;
    omPrcSetDestructor(NULL, inst_BoxDestroy);
    if (inst_introSkipF == 0) {
        inst_boxWork.update = inst_BoxOpenWait;
    } else {
        inst_boxWork.update = inst_BoxOpenNow;
    }
    while (1) {
        inst_boxWork.update(object);
        HuPrcVSleep();
    }
}

void inst_BoxOpenWait(omObjData *obj) {
    if ((s8)inst_OpenCheck() == 1) {
        Hu3DMotionAttrSet(obj->model[1], 1, 0);
        Hu3DMotionAttrSet(obj->model[2], 1, 0);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        inst_boxWork.update = inst_BoxOpenStart;
    }
}

void inst_BoxOpenStart(omObjData *obj) {
    Hu3DMotionAttrSet(obj->model[3], 1, 0);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    inst_boxWork.update = inst_BoxOpen;
}

void inst_BoxOpen(omObjData *object) {
    f32 duration = Hu3DMotion[Hu3DData[object->model[3]].motId].unk02 - 25.0f;
    f32 angle = ((f32)inst_boxOpenCnt / duration) * inst_cameraTilt;
    s32 i;

    Hu3DData[object->model[1]].rot.x = angle - 90.0f;
    Hu3DData[object->model[2]].rot.x = angle;
    inst_picScaleOfs = (0.15f / duration) * inst_boxOpenCnt;
    for (i = 0; i < 3; i++) {
        Hu3DModelScaleSet(object->model[i + 1], inst_picScaleOfs + 0.45f, inst_picScaleOfs + 0.45f,
                          inst_picScaleOfs + 0.45f);
    }
    inst_boxOpenCnt++;
    if ((f32)inst_boxOpenCnt == duration) {
        inst_boxWork.update = inst_BoxIdle;
        inst_picScaleOfs = 0;
        inst_boxOpenCnt = 0;
    }
}

void inst_PicPulseStart(void) {
    inst_boxWork.update = inst_PicPulse;
}

void inst_PicPulse(omObjData *object) {
    HmfSkeletonNode *nodes[2];
    s32 i;
    s32 j;
    f32 scale;

    nodes[0] = Hu3DModelObjPtrGet(object->model[1], inst_picNodeName);
    nodes[1] = Hu3DModelObjPtrGet(object->model[2], inst_frameNodeName);
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
    inst_boxWork.update = inst_BoxIdle;
}

void inst_BoxIdle(omObjData *object) {
}

s32 inst_BoxMotionEndCheck(void) {
    s16 modelId = inst_boxWork.object->model[0];
    f32 unk40 = Hu3DData[modelId].motTime;
    return Hu3DMotion[Hu3DData[modelId].motId].unk02 <= unk40;
}

void inst_BoxMotionStart(void) {
    Hu3DMotionTimeSet(inst_boxWork.object->model[0], 0);
    Hu3DMotionAttrSet(inst_boxWork.object->model[0], 1, 0);
}

void inst_BoxDestroy(void) {
    DataClose(inst_picHeader);
    DataClose(inst_picData);
    DataClose(inst_picAlpha);
}

void inst_BoxCloseStart(void) {
    omObjData *object = inst_boxWork.object;

    Hu3DMotionAttrSet(object->model[3], 1, 0);
    Hu3DMotionAttrSet(object->model[3], 4, 4);
    Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    inst_PlayerCloseStart();
    inst_boxWork.update = inst_BoxClose;
}

void inst_BoxClose(omObjData *obj) {
    f32 duration = Hu3DMotion[Hu3DData[obj->model[3]].motId].unk02 - 25.0f;
    f32 angle = inst_cameraTilt - ((f32)inst_boxCloseCnt / duration) * inst_cameraTilt;

    Hu3DData[obj->model[1]].rot.x = angle - 90.0f;
    Hu3DData[obj->model[2]].rot.x = angle;
    inst_boxCloseCnt++;
    if ((f32)inst_boxCloseCnt == duration) {
        inst_boxWork.update = inst_PicPulse;
        inst_boxCloseCnt = 0;
    }
}

s32 inst_BoxMotionStartCheck(void) {
    f32 unk40 = Hu3DData[inst_boxWork.object->model[0]].motTime;
    return unk40 == 0.0f;
}

void inst_BoxMotionRevStart(void) {
    omObjData *obj = inst_boxWork.object;

    Hu3DMotionAttrSet(obj->model[0], 1, 0);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionAttrSet(obj->model[0], 4, 4);
}

void inst_BoxOpenNow(omObjData *obj) {
    HmfSkeletonNode *nodes[2];
    s32 i;
    f32 duration = Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02;

    Hu3DMotionAttrSet(obj->model[0], 1, 0);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionTimeSet(obj->model[0], duration);
    Hu3DData[obj->model[1]].rot.x = inst_cameraTilt - 90.0f;
    Hu3DData[obj->model[2]].rot.x = inst_cameraTilt;
    for (i = 0; i < 3; i++) {
        Hu3DModelScaleSet(obj->model[i + 1], 0.6f, 0.6f, 0.6f);
        Hu3DModelAttrSet(obj->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    nodes[0] = Hu3DModelObjPtrGet(obj->model[1], inst_picNodeName);
    nodes[1] = Hu3DModelObjPtrGet(obj->model[2], inst_frameNodeName);
    for (i = 0; i < 2; i++) {
        nodes[i]->unk4C[0][0] = 1.3f;
        nodes[i]->unk4C[1][1] = 1.3f;
        nodes[i]->unk4C[2][2] = 1.3f;
    }
    inst_boxWork.update = inst_BoxIdle;
}
