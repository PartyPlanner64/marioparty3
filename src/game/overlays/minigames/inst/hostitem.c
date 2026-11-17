#include "common.h"

extern s8 inst_introSkipF;
extern s8 inst_mgType;
extern s32 inst_battleHostAnim;
extern s16 inst_battleHostAnimHalf;
extern omObjData *inst_battleHostObj;
extern s32 inst_battleHostWaitCnt;
extern s32 inst_battleHostJumpCnt;
extern void (*inst_battleHostFunc)(omObjData *);

void inst_BattleHostReset(omObjData *);
void inst_BattleHostWait(omObjData *);
void inst_BattleHostJump(omObjData *);
void inst_BattleHostLand(omObjData *);
void inst_BattleHostIdle(omObjData *object);
void inst_WinOpen(void);
void inst_WinStart(void);

void inst_BattleHostMain(void) {
    omObjData *object;
    void *data;

    object = omAddObj(25, 5, 8, -1, NULL);
    inst_battleHostObj = object;
    object->model[0] = Hu3DModelRead(0xA00A5, 0x16A9);
    omObjMotionRead(object, 0, 0xA00B4);
    omObjMotionRead(object, 1, 0xA00B5);
    if (inst_mgType == 3) {
        object->model[1] = Hu3DModelRead(0x170047, 0x16B9);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_HOOK, HU3D_ATTR_HOOK);
        Hu3DMotionAttrSet(object->model[1], 2, 2);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelHookSet(object->model[1], object->model[0], "item_hook");
    }
    Hu3DMotionModelSet(object->model[0], object->motion[0]);
    Hu3DMotionAttrSet(object->model[0], 2, 2);
    data = DataRead(0xA00B8);
    inst_battleHostAnim = (s16)Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "c164m_0_DEF");
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DModelDynamicFree(object->model[0]);
    Hu3DAnimAttrSet(inst_battleHostAnimHalf, 1, 0);
    Hu3DAnimBankSet(inst_battleHostAnimHalf, 0);
    object->trans.x = inst_mgType == 3 ? -86.0f : -91.0f;
    object->trans.y = inst_mgType == 3 ? -150.0f : -164.0f;
    object->trans.z = 210.0f;
    object->rot.x = -20.0f;
    object->rot.y = 15.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.5f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    object->scale.x = object->scale.y = object->scale.z = 0.4f;
    Hu3DModelScaleSet(object->model[0], 0.4f, 0.4f, 0.4f);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (inst_introSkipF == 1) {
        Hu3DMotionModelSet(object->model[0], object->motion[0]);
        Hu3DMotionAttrSet(object->model[0], 2, 2);
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        object->trans.x = inst_mgType == 3 ? -86.0f : -91.0f;
        object->trans.y = inst_mgType == 3 ? 50.0f : 36.0f;
        object->trans.z = 210.0f;
        object->rot.x = -20.0f;
        object->rot.y = 15.0f;
        inst_battleHostFunc = inst_BattleHostLand;
    } else {
        inst_battleHostFunc = inst_BattleHostReset;
    }
    while (1) {
        inst_battleHostFunc(object);
        HuPrcVSleep();
    }
}

void inst_BattleHostReset(omObjData *object) {
    object->trans.x = inst_mgType == 3 ? -86.0f : -91.0f;
    object->trans.y = inst_mgType == 3 ? -150.0f : -164.0f;
    object->trans.z = 210.0f;
    object->rot.x = -20.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    inst_battleHostFunc = inst_BattleHostWait;
}

void inst_BattleHostWait(omObjData *object) {
    inst_battleHostWaitCnt++;
    if (inst_battleHostWaitCnt >= 110) {
        Hu3DMotionModelSet(object->model[0], object->motion[1]);
        Hu3DMotionAttrSet(object->model[0], 2, 0);
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        HuAudFXPlay(0x25B);
        inst_battleHostFunc = inst_BattleHostJump;
        inst_battleHostWaitCnt = 0;
        inst_WinStart();
    }
}

void inst_BattleHostJump(omObjData *object) {
    f32 height;
    f32 finalHeight;

    inst_battleHostJumpCnt++;
    height = sindf(inst_battleHostJumpCnt * 5) * 200.0f;
    if (inst_mgType == 3) {
        object->trans.y = height + -150.0f;
    } else {
        object->trans.y = height + -164.0f;
    }
    if (inst_battleHostJumpCnt >= 17) {
        if (inst_mgType == 3) {
            finalHeight = 50.0f;
        } else {
            finalHeight = 36.0f;
        }
        object->trans.y = finalHeight;
        inst_battleHostJumpCnt = 0;
        inst_battleHostFunc = inst_BattleHostLand;
    }
}

void inst_BattleHostLand(omObjData *object) {
    s16 model = object->model[0];

    if (Hu3DMotion[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime + 15.0f) {
        Hu3DMotionShiftSet(model, Hu3DData[object->motion[0]].motId, 0, 30, 2);
        inst_WinOpen();
        inst_battleHostFunc = inst_BattleHostIdle;
    }
}

void inst_BattleHostIdle(omObjData *object) {
}
