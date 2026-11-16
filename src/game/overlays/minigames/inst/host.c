#include "common.h"
#include "inst.h"

extern s8 inst_introSkipF;
extern s32 inst_hostAnimTbl[2];
extern s16 inst_hostAnimTblHalf;
extern s16 inst_hostAnimLink;
extern InstObjectState inst_hostWork;
extern void (*inst_hostFunc)(omObjData *);
extern s32 inst_hostWaitCnt;
extern s32 inst_hostJumpCnt;

void inst_HostReset(omObjData *);
void inst_HostWait(omObjData *);
void inst_HostJump(omObjData *);
void inst_HostLand(omObjData *);
void inst_HostIdle(omObjData *);
void inst_HmfAnimSet(s16, s16, s16);
void inst_WinOpen(void);
void inst_WinStart(void);

void inst_HostMain(void) {
    omObjData *object;
    void *data;

    object = omAddObj(25, 5, 5, -1, NULL);
    inst_hostWork.object = object;
    object->model[0] = Hu3DModelRead(0xA0075, 0x16A9);
    omObjMotionRead(object, 0, 0xA0076);
    omObjMotionRead(object, 1, 0xA0077);
    omObjMotionRead(object, 2, 0xA0078);
    omObjMotionRead(object, 3, 0xA0079);
    Hu3DMotionModelSet(object->model[0], object->motion[1]);
    Hu3DMotionAttrSet(object->model[0], 2, 2);
    data = DataRead(0xA007E);
    inst_hostAnimTbl[0] = (s16)Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "c204n_0_DEF");
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DModelDynamicFree(object->model[0]);
    Hu3DAnimAttrSet(inst_hostAnimTblHalf, 1, 0);
    Hu3DAnimBankSet(inst_hostAnimTblHalf, 0);
    inst_hostAnimLink = Hu3DAnimLink(Hu3DData[object->model[0]].hmf, inst_hostAnimTblHalf, 0, "c204n_0_DEF");
    inst_hostAnimTbl[0] = Hu3DAnimData[inst_hostAnimTbl[0]].animIdx;
    data = DataRead(0xA007F);
    inst_hostAnimTbl[1] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    inst_HmfAnimSet(object->model[0], inst_hostAnimLink, inst_hostAnimTblHalf);
    object->trans.x = -86.0f;
    object->trans.y = -148.0f;
    object->trans.z = 253.0f;
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
        object->trans.x = -86.0f;
        object->trans.y = 52.0f;
        object->trans.z = 253.0f;
        object->rot.x = -20.0f;
        object->rot.y = 15.0f;
        inst_hostWork.update = inst_HostIdle;
    } else {
        inst_hostFunc = inst_HostReset;
    }
    while (1) {
        inst_hostFunc(object);
        HuPrcVSleep();
    }
}

void inst_HostReset(omObjData *object) {
    object->trans.x = -86.0f;
    object->trans.y = -148.0f;
    object->trans.z = 253.0f;
    object->rot.x = -20.0f;
    object->rot.y = 15.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DMotionModelSet(object->model[0], object->motion[1]);
    Hu3DMotionAttrSet(object->model[0], 2, 2);
    inst_HmfAnimSet(object->model[0], inst_hostAnimLink, inst_hostAnimTblHalf);
    inst_hostFunc = inst_HostWait;
}

void inst_HostWait(omObjData *object) {
    inst_hostWaitCnt++;
    if (inst_hostWaitCnt >= 100) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        HuAudFXPlay(0x135);
        inst_hostFunc = inst_HostJump;
        inst_hostWaitCnt = 0;
        inst_WinStart();
    }
}

void inst_HostJump(omObjData *object) {
    inst_hostJumpCnt++;
    object->trans.y = sindf(inst_hostJumpCnt * 5) * 200.0f + -148.0f;
    if (inst_hostJumpCnt >= 17) {
        object->trans.y = 52.0f;
        inst_hostJumpCnt = 0;
        Hu3DMotionModelSet(object->model[0], object->motion[2]);
        Hu3DMotionAttrSet(object->model[0], 2, 0);
        HuPrcSleep(10);
        HuAudFXPlay(0x2A7);
        inst_hostFunc = inst_HostLand;
    }
}

void inst_HostLand(omObjData *object) {
    s16 model = object->model[0];
    f32 time = Hu3DData[model].motTime;

    if (Hu3DMotion[Hu3DData[model].motId].unk02 <= time) {
        Hu3DMotionModelSet(model, object->motion[3]);
        Hu3DMotionAttrSet(object->model[0], 2, 2);
        inst_WinOpen();
        inst_hostFunc = inst_HostIdle;
    }
}

void inst_HostIdle(omObjData *object) {
}

void inst_HmfAnimSet(s16 model, s16 animSlot, s16 anim) {
    HmfAnim *entry;

    if (animSlot >= 0) {
        if (anim == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            Hu3DModelAnimStart(Hu3DData[model].hmf);
            entry = &Hu3DAnimData[animSlot];
            entry->animIdx = anim;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}
