#include "common.h"
#include "inst.h"

extern s8 inst_introSkipF;
extern s32 inst_itemHostAnim;
extern s16 inst_itemHostAnimHalf;
extern InstObjectState inst_itemHostWork;
extern void (*inst_itemHostFunc)(omObjData *);
extern s32 inst_itemHostWaitCnt;
extern s32 inst_itemHostJumpCnt;

void inst_ItemHostReset(omObjData *);
void inst_ItemHostWait(omObjData *);
void inst_ItemHostJump(omObjData *);
void inst_ItemHostLand(omObjData *);
void inst_ItemHostIdle(omObjData *);
void inst_WinOpen(void);
void inst_WinStart(void);

void inst_ItemHostMain(void) {
    omObjData *object;
    void *data;

    object = omAddObj(25, 5, 8, -1, NULL);
    inst_itemHostWork.object = object;
    object->model[0] = Hu3DModelRead(0xA0000, 0x16A9);
    omObjMotionRead(object, 0, 0xA0001);
    omObjMotionRead(object, 1, 0xA0002);
    omObjMotionRead(object, 2, 0xA0006);
    omObjMotionRead(object, 3, 0xA0023);
    omObjMotionRead(object, 4, 0xA0018);
    Hu3DMotionModelSet(object->model[0], object->motion[1]);
    Hu3DMotionAttrSet(object->model[0], 2, 2);
    data = DataRead(0xA002A);
    inst_itemHostAnim = (s16)Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "c160n_0_DEF");
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DModelDynamicFree(object->model[0]);
    Hu3DAnimAttrSet(inst_itemHostAnimHalf, 1, 0);
    Hu3DAnimBankSet(inst_itemHostAnimHalf, 0);
    object->trans.x = -91.0f;
    object->trans.y = -171.0f;
    object->trans.z = 210.0f;
    object->rot.x = -20.0f;
    object->rot.y = 15.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.5f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    object->scale.x = object->scale.y = object->scale.z = 0.4f;
    Hu3DModelScaleSet(object->model[0], 0.4f, 0.4f, 0.4f);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (inst_introSkipF == 1) {
        Hu3DMotionModelSet(object->model[0], object->motion[3]);
        Hu3DMotionAttrSet(object->model[0], 2, 2);
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        object->trans.x = -91.0f;
        object->trans.y = 29.0f;
        object->trans.z = 210.0f;
        object->rot.x = -20.0f;
        object->rot.y = 15.0f;
        inst_itemHostWork.update = inst_ItemHostIdle;
    } else {
        inst_itemHostFunc = inst_ItemHostReset;
    }
    while (1) {
        inst_itemHostFunc(object);
        HuPrcVSleep();
    }
}

void inst_ItemHostReset(omObjData *object) {
    object->trans.x = -91.0f;
    object->trans.y = -171.0f;
    object->trans.z = 210.0f;
    object->rot.x = -20.0f;
    object->rot.y = 15.0f;
    Hu3DModelPosSet(*object->model, object->trans.x, object->trans.y, object->trans.z);
    inst_itemHostFunc = inst_ItemHostWait;
}

void inst_ItemHostWait(omObjData *object) {
    inst_itemHostWaitCnt++;
    if (inst_itemHostWaitCnt >= 100) {
        inst_itemHostFunc = inst_ItemHostJump;
        inst_itemHostWaitCnt = 0;
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        HuAudFXPlay(0x298);
        inst_WinStart();
    }
}

void inst_ItemHostJump(omObjData *object) {
    inst_itemHostJumpCnt++;
    object->trans.y = sindf(inst_itemHostJumpCnt * 5) * 200.0f + -171.0f;
    if (inst_itemHostJumpCnt == 13) {
        Hu3DMotionModelSet(object->model[0], object->motion[4]);
        Hu3DMotionAttrSet(object->model[0], 2, 0);
    }
    if (inst_itemHostJumpCnt >= 17) {
        object->trans.y = 29.0f;
        inst_itemHostJumpCnt = 0;
        inst_itemHostFunc = inst_ItemHostLand;
    }
}

void inst_ItemHostLand(omObjData *object) {
    s16 model = object->model[0];

    if (Hu3DMotion[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        Hu3DMotionShiftSet(model, Hu3DData[object->motion[3]].motId, 0, 30, 2);
        inst_WinOpen();
        inst_itemHostFunc = inst_ItemHostIdle;
    }
}

void inst_ItemHostIdle(omObjData *object) {
}
