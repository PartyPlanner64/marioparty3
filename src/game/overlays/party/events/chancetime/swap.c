#include "common.h"
#include "chancetime.h"

extern s16 chancetime_hostEffSprMdlTbl[];
extern s32 chancetime_hostAnimTbl[2];
extern s32 chancetime_hostFaceAnim;
extern ChanceTimeObjState chancetime_dancerWorkTbl[];
extern ChanceTimeObjState chancetime_hostLWork;
extern ChanceTimeObjState chancetime_hostRWork;
extern ChanceTimeObjState chancetime_hostWork;

void chancetime_HostShowTurn(omObjData *object);
void chancetime_HostShowRaise(omObjData *object);
void chancetime_HostShowHook(omObjData *object);
void chancetime_HostEffShow(omObjData *object);
void chancetime_HostHideBegin(omObjData *object);
void chancetime_HostHideWait(omObjData *object);
void chancetime_HostHideTurn(omObjData *object);
void chancetime_HostRExit(omObjData *object);
void chancetime_HostHop(omObjData *object);
void chancetime_HmfAnimSet(s16 model, s16 slot, s16 animIdx);
s32 chancetime_MotionEndCheck(s16 arg0);
void chancetime_MotionEndWait(s16 arg0);
void chancetime_ObjPosMoveV(omObjData *object, Vec *pos, s32 arg2);
void chancetime_ObjPosMoveEx(omObjData *object, Vec *pos, s32 time, s32 faceDir);
void chancetime_ObjRotMoveV(omObjData *object, Vec *rot, s32 time);
void chancetime_ObjRotMove(omObjData *object, f32 x, f32 y, f32 z, s32 arg4);
void chancetime_ObjWalk(omObjData *object, f32 x, f32 y, f32 z, s32 arg4);
void chancetime_HostLJump(omObjData *object);
void chancetime_DancerJump(omObjData *object);
void chancetime_Dancer1Dance(omObjData *object);
void chancetime_Dancer2Dance(omObjData *object);
void chancetime_Dancer3Dance(omObjData *object);
void chancetime_Dancer4Dance(omObjData *object);
void chancetime_HostRJump(omObjData *object);
void chancetime_TitleProc(void);
void chancetime_HostIdle(omObjData *object);
void chancetime_HostDestroy(void);

s32 chancetime_hostHopF = 0;
s32 chancetime_hostHopDoneF = 0;
s32 chancetime_hostTalkF = 0;
Vec chancetime_dancerPos = { 0.0f, 80.0f, -300.0f };
Vec chancetime_dancerPosTbl[4] = {
    { -210.0f, 0.0f, -50.0f },
    { -70.0f, 0.0f, -50.0f },
    { 70.0f, 0.0f, -50.0f },
    { 210.0f, 0.0f, -50.0f },
};
Vec chancetime_hostLJumpPos = { -200.0f, 80.0f, -300.0f };
Vec chancetime_hostRJumpPos = { 200.0f, 80.0f, -300.0f };
s32 chancetime_introEndF = 0;
f32 chancetime_hostShowRot = 0.0f;
s32 chancetime_hostItemHideF = 0;
f32 chancetime_hostLTurnRot = 0.0f;
f32 chancetime_hostRTurnRot = 0.0f;
f32 chancetime_hostRExitX = 0.0f;
f32 chancetime_hostHopTime = 0.0f;
f32 chancetime_hostHopSmallTime = 0.0f;

void chancetime_HostProc(void) {
    omObjData *object;
    void *data;
    u16 sprModel;
    s32 anim;
    s8 i;

    object = omAddObj(20, 10, 16, -1, NULL);
    chancetime_hostWork.obj = object;

    object->model[1] = Hu3DModelRead(0xA0000, 0x2A9);
    Hu3DModelPosSet(object->model[1], -200.0f, 0.0f, -50.0f);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
    object->model[2] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelPosSet(object->model[2], -200.0f, -5.0f, -50.0f);
    Hu3DModelCameraSet(object->model[2], HU3D_CAM1);
    data = DataRead(0xA002A);
    chancetime_hostAnimTbl[0] = (s16)Hu3DAnimCreate(Hu3DData[object->model[1]].hmf, data, 0, "c160n_0_DEF");
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelDynamicFree(object->model[1]);
    Hu3DAnimAttrSet(chancetime_hostAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(chancetime_hostAnimTbl[0], 0);
    chancetime_hostFaceAnim = Hu3DAnimLink(Hu3DData[object->model[1]].hmf, chancetime_hostAnimTbl[0], 0, "c160n_0_DEF");
    data = DataRead(0xA002B);
    chancetime_hostAnimTbl[1] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);

    object->model[3] = Hu3DModelRead(0xA0000, 0x2A9);
    Hu3DModelPosSet(object->model[3], 200.0f, 0.0f, -50.0f);
    Hu3DModelCameraSet(object->model[3], HU3D_CAM1);
    data = DataRead(0xA002A);
    anim = (s16)Hu3DAnimCreate(Hu3DData[object->model[3]].hmf, data, 0, "c160n_0_DEF");
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(object->model[3]);
    Hu3DModelDynamicFree(object->model[3]);
    Hu3DAnimAttrSet(anim, 1, 0);
    Hu3DAnimBankSet(anim, 0);
    object->model[4] = Hu3DModelLink(object->model[2]);
    Hu3DModelPosSet(object->model[4], 200.0f, -5.0f, -50.0f);
    Hu3DModelCameraSet(object->model[4], HU3D_CAM1);

    object->model[5] = Hu3DModelRead(0x1C0008, 0x2B9);
    Hu3DModelCameraSet(object->model[5], HU3D_CAM1);
    Hu3DModelAttrSet(object->model[5], HU3D_ATTR_HOOK, HU3D_ATTR_HOOK);
    Hu3DMotionAttrSet(object->model[5], 2, 2);
    Hu3DModelAttrSet(object->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionAttrSet(object->model[5], 1, 1);
    object->model[6] = Hu3DModelRead(0x1C0008, 0x2B9);
    Hu3DModelCameraSet(object->model[6], HU3D_CAM1);
    Hu3DModelAttrSet(object->model[6], HU3D_ATTR_HOOK, HU3D_ATTR_HOOK);
    Hu3DMotionAttrSet(object->model[6], 2, 2);
    Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionAttrSet(object->model[6], 1, 1);

    for (i = 0; i < 2; i++) {
        data = DataRead(0xB);
        sprModel = Hu3DSprModelCreate(data, 0x6BD, 8);
        HuMemMemoryFreePerm(data);
        Hu3DModelAttrSet(Hu3DSprModelData[sprModel].modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(Hu3DSprModelData[sprModel].modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(Hu3DSprModelData[sprModel].modelId, 3.0f, 3.0f, 3.0f);
        Hu3DMotionAttrSet(Hu3DSprModelData[sprModel].modelId, 2, 0);
        Hu3DModelObjAttrSet(Hu3DSprModelData[sprModel].modelId, 0x70000000, 0x70000000);
        Hu3DModelCameraSet(Hu3DSprModelData[sprModel].modelId, HU3D_CAM1);
        object->model[7 + i] = Hu3DSprModelData[sprModel].modelId;
        chancetime_hostEffSprMdlTbl[i] = sprModel;
    }

    omObjMotionRead(object, 0, 0xA0001);
    omObjMotionRead(object, 1, 0xA0006);
    omObjMotionRead(object, 2, 0xA000F);
    omObjMotionRead(object, 3, 0xA0010);
    omObjMotionRead(object, 4, 0xA0011);
    omObjMotionRead(object, 5, 0xA000C);
    omObjMotionRead(object, 6, 0xA000D);
    omObjMotionRead(object, 7, 0xA000E);
    omObjMotionRead(object, 8, 0xA001C);
    omObjMotionRead(object, 9, 0xA001D);
    omObjMotionRead(object, 10, 0xA001E);
    omObjMotionRead(object, 11, 0xA0016);
    omObjMotionRead(object, 12, 0xA0018);
    Hu3DMotionModelSet(object->model[1], object->motion[0]);
    Hu3DMotionModelSet(object->model[3], object->motion[0]);
    Hu3DMotionAttrSet(object->model[1], 2, 0);
    Hu3DMotionAttrSet(object->model[3], 2, 0);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[3], 0.0f, 0.0f, 0.0f);
    omPrcSetDestructor(0, chancetime_HostDestroy);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[5]].motId, 0, 30, 2);
    Hu3DMotionShiftSet(object->model[3], Hu3DData[object->motion[5]].motId, 0, 30, 2);
    chancetime_hostWork.func = chancetime_HostIdle;
    while (TRUE) {
        chancetime_hostWork.func(object);
        HuPrcVSleep();
    }
}

void chancetime_ObjIdle(omObjData *object) {
}

void chancetime_HostIdle(omObjData *object) {
}

void chancetime_HostDestroy(void) {
}

void chancetime_HostShowBegin(omObjData *object) {
    Hu3DMotionModelSet(object->model[1], object->motion[2]);
    Hu3DMotionAttrSet(object->model[1], 2, 0);
    Hu3DMotionModelSet(object->model[3], object->motion[2]);
    Hu3DMotionAttrSet(object->model[3], 2, 0);
    chancetime_hostWork.func = chancetime_HostShowTurn;
}

void chancetime_HostShowTurn(omObjData *object) {
    chancetime_hostShowRot += 8.0f;
    Hu3DModelRotSet(object->model[1], 0.0f, chancetime_hostShowRot, 0.0f);
    Hu3DModelRotSet(object->model[3], 0.0f, -chancetime_hostShowRot, 0.0f);
    if (chancetime_hostShowRot >= 45.0f) {
        chancetime_hostShowRot = 45.0f;
        Hu3DModelRotSet(object->model[1], 0.0f, chancetime_hostShowRot, 0.0f);
        Hu3DModelRotSet(object->model[3], 0.0f, -chancetime_hostShowRot, 0.0f);
        if (Hu3DMotion[Hu3DData[object->model[1]].motId].unk02 <= Hu3DData[object->model[1]].motTime) {
            chancetime_hostWork.func = chancetime_HostShowRaise;
            chancetime_hostShowRot = 0.0f;
        }
    }
}

void chancetime_HostShowRaise(omObjData *object) {
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[3]].motId, 0, 30, 2);
    Hu3DMotionAttrSet(object->model[5], 1, 0);
    Hu3DMotionShiftSet(object->model[3], Hu3DData[object->motion[3]].motId, 0, 30, 2);
    Hu3DMotionAttrSet(object->model[6], 1, 0);
    chancetime_hostWork.func = chancetime_HostShowHook;
}

void chancetime_HostShowHook(omObjData *object) {
    if (Hu3DMotionShiftTimeGet(object->model[1]) >= 5.0f) {
        Hu3DModelHookSet(object->model[5], object->model[1], "item_hook");
        Hu3DModelAttrSet(object->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionAttrSet(object->model[5], 1, 0);
        Hu3DModelHookSet(object->model[6], object->model[3], "item_hook");
        Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionAttrSet(object->model[6], 1, 0);
        chancetime_HostEffShow(object);
        chancetime_hostWork.func = chancetime_ObjIdle;
    }
}

void chancetime_HostHideBegin(omObjData *object) {
    Hu3DMotionAttrSet(object->model[5], 1, 1);
    Hu3DMotionAttrSet(object->model[6], 1, 1);
    Hu3DMotionTimeSet(object->model[5], 0.0f);
    Hu3DMotionTimeSet(object->model[6], 0.0f);
    Hu3DMotionAttrSet(object->model[5], 2, 0);
    Hu3DMotionAttrSet(object->model[6], 2, 0);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[2]].motId, 0, 30, 0);
    Hu3DMotionShiftSet(object->model[3], Hu3DData[object->motion[2]].motId, 0, 30, 0);
    chancetime_hostWork.func = chancetime_HostHideWait;
}

void chancetime_HostHideWait(omObjData *object) {
    f32 time = Hu3DMotionShiftTimeGet(object->model[1]);

    if (chancetime_hostItemHideF == 0) {
        if (time >= 20.0f) {
            Hu3DModelAttrSet(object->model[5], HU3D_ATTR_HOOK, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(object->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(object->model[6], HU3D_ATTR_HOOK, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            chancetime_HostEffShow(object);
            chancetime_hostItemHideF = 1;
        }
    }
    if (time < 0.0f) {
        Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[0]].motId, 0, 30, 2);
        Hu3DMotionShiftSet(object->model[3], Hu3DData[object->motion[1]].motId, 0, 30, 2);
        chancetime_hostItemHideF = 0;
        chancetime_HmfAnimSet(object->model[1], chancetime_hostFaceAnim, chancetime_hostAnimTbl[1]);
        chancetime_hostWork.func = chancetime_HostHideTurn;
    }
}

void chancetime_HostHideTurn(omObjData *object) {
    s8 count = 0;

    chancetime_hostLTurnRot += 8.0f;
    if (chancetime_hostLTurnRot >= 45.0f) {
        chancetime_hostLTurnRot = 45.0f;
        count++;
    }
    Hu3DModelRotSet(object->model[1], 0.0f, 45.0f - chancetime_hostLTurnRot, 0.0f);
    chancetime_hostRTurnRot += 8.0f;
    if (chancetime_hostRTurnRot >= 135.0f) {
        chancetime_hostRTurnRot = 135.0f;
        count++;
    }
    Hu3DModelRotSet(object->model[3], 0.0f, chancetime_hostRTurnRot + -45.0f, 0.0f);
    if (count >= 2) {
        Hu3DMotionShiftSet(object->model[3], Hu3DData[object->motion[1]].motId, 0, 30, 2);
        chancetime_hostLTurnRot = chancetime_hostRTurnRot = 0.0f;
        chancetime_hostWork.func = chancetime_HostRExit;
    }
}

void chancetime_HostRExit(omObjData *object) {
    s8 count = 0;

    chancetime_hostRExitX += 30.0f;
    if (chancetime_hostRExitX >= 250.0f) {
        chancetime_hostRExitX = 250.0f;
        count++;
    }
    Hu3DModelPosSet(object->model[3], chancetime_hostRExitX + 200.0f, 0.0f, -50.0f);
    Hu3DModelPosSet(object->model[4], chancetime_hostRExitX + 200.0f, -5.0f, -50.0f);
    if (count == 1) {
        chancetime_hostRExitX = 0.0f;
        Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        chancetime_PlayerEnterStart();
        Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[5]].motId, 0, 30, 2);
        Hu3DMotionShiftSet(object->model[3], Hu3DData[object->motion[5]].motId, 0, 30, 2);
        chancetime_hostWork.func = chancetime_HostIdle;
    }
}

void chancetime_HostHop(omObjData *object) {
    Hu3DModelPosSet(object->model[1], -200.0f, sindf(chancetime_hostHopTime * 18.0f) * 50.0f, -50.0f);
    Hu3DModelPosSet(object->model[3], 200.0f, sindf(chancetime_hostHopTime * 18.0f) * 50.0f, -50.0f);
    chancetime_hostHopTime += 1.0f;
    if (chancetime_hostHopTime >= 10.0f) {
        chancetime_hostHopTime = 0.0f;
        Hu3DModelPosSet(object->model[1], -200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(object->model[3], 200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(object->model[2], -200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(object->model[4], 200.0f, 0.0f, -50.0f);
        chancetime_hostHopF = 0;
        chancetime_hostHopDoneF = 1;
        chancetime_hostWork.func = chancetime_ObjIdle;
    }
}

void chancetime_HostHopSmall(omObjData *object) {
    Hu3DModelPosSet(object->model[1], -200.0f, sindf(chancetime_hostHopSmallTime * 36.0f) * 20.0f, -50.0f);
    Hu3DModelPosSet(object->model[3], 200.0f, sindf(chancetime_hostHopSmallTime * 36.0f) * 20.0f, -50.0f);
    chancetime_hostHopSmallTime += 1.0f;
    if (chancetime_hostHopSmallTime >= 5.0f) {
        chancetime_hostHopSmallTime = 0.0f;
        Hu3DModelPosSet(object->model[1], -200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(object->model[3], 200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(object->model[2], -200.0f, 0.0f, -50.0f);
        Hu3DModelPosSet(object->model[4], 200.0f, 0.0f, -50.0f);
        chancetime_hostHopF = 0;
        chancetime_hostHopDoneF = 1;
        chancetime_hostWork.func = chancetime_ObjIdle;
    }
}

void chancetime_HostShowStart(void) {
    chancetime_hostWork.func = chancetime_HostShowBegin;
}

void chancetime_HostHideStart(void) {
    chancetime_hostWork.func = chancetime_HostHideBegin;
}

void chancetime_HostHopStart(void) {
    chancetime_hostHopF = 1;
    chancetime_hostHopDoneF = 0;
    chancetime_hostWork.func = chancetime_HostHop;
}

s32 chancetime_HostHopCheck(void) {
    return chancetime_hostHopDoneF;
}

void chancetime_HostEffShow(omObjData *object) {
    HuMtx4F mtx;
    Vec pos;
    f32 time;
    f32 rot;

    time = Hu3DData[object->model[1]].motTime;
    Hu3DModelObjMtxFrameGet(object->model[1], time, "item_hook", &mtx);
    rot = -Hu3DData[object->model[1]].rot.y;
    pos.x = cosdf(rot) * mtx[3][0] - sindf(rot) * mtx[3][2];
    pos.y = mtx[3][1];
    pos.z = sindf(rot) * mtx[3][0] + cosdf(rot) * mtx[3][2];
    Hu3DModelPosSet(object->model[7], Hu3DData[object->model[1]].pos.x + pos.x,
                    Hu3DData[object->model[1]].pos.y + pos.y - 100.0f,
                    Hu3DData[object->model[1]].pos.z + pos.z + 80.0f);
    Hu3DModelAttrSet(object->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionAttrSet(object->model[7], 2, 0);
    Hu3DMotionAttrSet(object->model[7], 1, 0);
    Hu3DSprModelFrameSet(chancetime_hostEffSprMdlTbl[0], 0);

    time = Hu3DData[object->model[3]].motTime;
    Hu3DModelObjMtxFrameGet(object->model[3], time, "item_hook", &mtx);
    rot = -Hu3DData[object->model[3]].rot.y;
    pos.x = cosdf(rot) * mtx[3][0] - sindf(rot) * mtx[3][2];
    pos.y = mtx[3][1];
    pos.z = sindf(rot) * mtx[3][0] + cosdf(rot) * mtx[3][2];
    Hu3DModelPosSet(object->model[8], Hu3DData[object->model[3]].pos.x + pos.x,
                    Hu3DData[object->model[3]].pos.y + pos.y - 100.0f,
                    Hu3DData[object->model[3]].pos.z + pos.z + 80.0f);
    Hu3DModelAttrSet(object->model[8], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionAttrSet(object->model[8], 2, 0);
    Hu3DMotionAttrSet(object->model[8], 1, 0);
    Hu3DSprModelFrameSet(chancetime_hostEffSprMdlTbl[1], 0);
}

void chancetime_HostTalkEnd(void) {
    omObjData *object = chancetime_hostWork.obj;

    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[5]].motId, 0, 30, 2);
    Hu3DMotionShiftSet(object->model[3], Hu3DData[object->motion[5]].motId, 0, 30, 2);
    chancetime_hostTalkF = 0;
    chancetime_hostWork.func = chancetime_HostIdle;
}

void chancetime_HostTalkStart(void) {
    omObjData *object = chancetime_hostWork.obj;

    chancetime_hostWork.func = chancetime_ObjIdle;
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[4]].motId, 0, 30, 2);
    Hu3DMotionShiftSet(object->model[3], Hu3DData[object->motion[4]].motId, 0, 30, 2);
}

void chancetime_HmfAnimSet(s16 model, s16 slot, s16 animIdx) {
    if (slot >= 0) {
        if (animIdx == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            HmfAnim *anim;

            Hu3DModelAnimStart(Hu3DData[model].hmf);
            anim = &Hu3DAnimData[slot];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

void chancetime_DancerProc(void) {
    omObjData *object;
    omObjData *motObj;
    void *data;
    s32 anim;

    object = omAddObj(20, 4, 0, -1, NULL);
    chancetime_dancerWorkTbl[0].obj = object;
    motObj = chancetime_hostWork.obj;
    object->model[1] = Hu3DModelRead(0xA0000, 0x2A9);
    Hu3DModelPosSet(object->model[1], chancetime_dancerPos.x, chancetime_dancerPos.y, chancetime_dancerPos.z);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
    data = DataRead(0xA002A);
    anim = (s16)Hu3DAnimCreate(Hu3DData[object->model[1]].hmf, data, 0, "c160n_0_DEF");
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelDynamicFree(object->model[1]);
    Hu3DAnimAttrSet(anim, 1, 0);
    Hu3DAnimBankSet(anim, 0);
    object->model[2] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelPosSet(object->model[2], chancetime_dancerPos.x, chancetime_dancerPos.y, chancetime_dancerPos.z);
    Hu3DModelCameraSet(object->model[2], HU3D_CAM1);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[0]].motId, 0, 30, 2);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    chancetime_dancerWorkTbl[0].func = chancetime_DancerJump;
    while (TRUE) {
        chancetime_dancerWorkTbl[0].func(object);
        HuPrcVSleep();
    }
}

void chancetime_DancerJump(omObjData *object) {
    s16 model = object->model[1];
    omObjData *motObj = chancetime_hostWork.obj;
    Vec unusedPos;
    f32 y;
    f32 speed;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(2);
    y = Hu3DData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            Hu3DData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    Hu3DData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(3);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            chancetime_MotionEndWait(model);
        }
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(20);
    omAddPrcObj(chancetime_TitleProc, 0x1001, 0x2000, 0);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[12]].motId, 0, 10, 0);
    // Copied but never read in the original.
    unusedPos.x = Hu3DData[model].pos.x;
    unusedPos.y = Hu3DData[model].pos.y;
    unusedPos.z = Hu3DData[model].pos.z;
    (void)unusedPos;
    speed = 20.0f;
    while (TRUE) {
        Hu3DData[model].pos.y += speed;
        Hu3DData[model].pos.z += 20.0f;
        if (Hu3DData[model].pos.z >= -250.0f) {
            Hu3DData[object->model[2]].pos.x = Hu3DData[model].pos.x;
            Hu3DData[object->model[2]].pos.y = 0.0f;
            Hu3DData[object->model[2]].pos.z = Hu3DData[model].pos.z;
            Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        if (Hu3DData[model].pos.y <= 0.0f) {
            break;
        }
        speed -= 3.0f;
        HuPrcVSleep();
    }
    Hu3DData[model].pos.y = 0.0f;
    Hu3DData[object->model[2]].pos.x = Hu3DData[model].pos.x;
    Hu3DData[object->model[2]].pos.y = 0.0f;
    Hu3DData[object->model[2]].pos.z = Hu3DData[model].pos.z;
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[1]].motId, 0, 10, 2);
    chancetime_ObjWalk(object, 0.0f, 0.0f, 500.0f, 5);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    chancetime_dancerWorkTbl[0].func = chancetime_ObjIdle;
}

void chancetime_Dancer1Proc(void) {
    omObjData *obj;
    omObjData *motObj;
    omObjData *srcObj;

    obj = omAddObj(20, 4, 0, -1, NULL);
    chancetime_dancerWorkTbl[1].obj = obj;
    motObj = chancetime_hostWork.obj;
    srcObj = chancetime_dancerWorkTbl[0].obj;
    obj->model[1] = Hu3DModelLink(srcObj->model[1]);
    Hu3DModelPosSet(obj->model[1], chancetime_dancerPosTbl[0].x, chancetime_dancerPosTbl[0].y, chancetime_dancerPosTbl[0].z);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM1);
    obj->model[2] = Hu3DModelLink(srcObj->model[2]);
    Hu3DModelPosSet(obj->model[2], chancetime_dancerPosTbl[0].x, chancetime_dancerPosTbl[0].y, chancetime_dancerPosTbl[0].z);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM1);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[motObj->motion[0]].motId, 0, 10, 2);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    chancetime_dancerWorkTbl[1].func = chancetime_Dancer1Dance;
    while (TRUE) {
        chancetime_dancerWorkTbl[1].func(obj);
        HuPrcVSleep();
    }
}

void chancetime_Dancer1Dance(omObjData *object) {
    s16 model = object->model[1];
    omObjData *motObj = chancetime_hostWork.obj;
    f32 y;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(4);
    y = Hu3DData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            Hu3DData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    Hu3DData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(1);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            chancetime_MotionEndWait(model);
        }
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[9]].motId, 0, 10, 0);
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[1]].motId, 0, 10, 2);
    chancetime_ObjWalk(object, -400.0f, 0.0f, 300.0f, 10);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    chancetime_dancerWorkTbl[1].func = chancetime_ObjIdle;
}

void chancetime_Dancer2Proc(void) {
    omObjData *obj;
    omObjData *motObj;
    omObjData *srcObj;

    obj = omAddObj(20, 4, 0, -1, NULL);
    chancetime_dancerWorkTbl[2].obj = obj;
    motObj = chancetime_hostWork.obj;
    srcObj = chancetime_dancerWorkTbl[0].obj;
    obj->model[1] = Hu3DModelLink(srcObj->model[1]);
    Hu3DModelPosSet(obj->model[1], chancetime_dancerPosTbl[1].x, chancetime_dancerPosTbl[1].y, chancetime_dancerPosTbl[1].z);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM1);
    obj->model[2] = Hu3DModelLink(srcObj->model[2]);
    Hu3DModelPosSet(obj->model[2], chancetime_dancerPosTbl[1].x, chancetime_dancerPosTbl[1].y, chancetime_dancerPosTbl[1].z);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM1);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[motObj->motion[0]].motId, 0, 10, 2);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    chancetime_dancerWorkTbl[2].func = chancetime_Dancer2Dance;
    while (TRUE) {
        chancetime_dancerWorkTbl[2].func(obj);
        HuPrcVSleep();
    }
}

void chancetime_Dancer2Dance(omObjData *object) {
    s16 model = object->model[1];
    omObjData *motObj = chancetime_hostWork.obj;
    f32 y;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(1);
    y = Hu3DData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            Hu3DData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    Hu3DData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(4);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            chancetime_MotionEndWait(model);
        }
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[9]].motId, 0, 10, 0);
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[1]].motId, 0, 10, 2);
    chancetime_ObjWalk(object, -200.0f, 0.0f, 300.0f, 10);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    chancetime_dancerWorkTbl[2].func = chancetime_ObjIdle;
}

void chancetime_Dancer3Proc(void) {
    omObjData *obj;
    omObjData *motObj;
    omObjData *srcObj;

    obj = omAddObj(20, 4, 0, -1, NULL);
    chancetime_dancerWorkTbl[3].obj = obj;
    motObj = chancetime_hostWork.obj;
    srcObj = chancetime_dancerWorkTbl[0].obj;
    obj->model[1] = Hu3DModelLink(srcObj->model[1]);
    Hu3DModelPosSet(obj->model[1], chancetime_dancerPosTbl[2].x, chancetime_dancerPosTbl[2].y, chancetime_dancerPosTbl[2].z);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM1);
    obj->model[2] = Hu3DModelLink(srcObj->model[2]);
    Hu3DModelPosSet(obj->model[2], chancetime_dancerPosTbl[2].x, chancetime_dancerPosTbl[2].y, chancetime_dancerPosTbl[2].z);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM1);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[motObj->motion[0]].motId, 0, 10, 2);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    chancetime_dancerWorkTbl[3].func = chancetime_Dancer3Dance;
    while (TRUE) {
        chancetime_dancerWorkTbl[3].func(obj);
        HuPrcVSleep();
    }
}

void chancetime_Dancer3Dance(omObjData *object) {
    s16 model = object->model[1];
    omObjData *motObj = chancetime_hostWork.obj;
    f32 y;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(3);
    y = Hu3DData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            Hu3DData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    Hu3DData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(2);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            chancetime_MotionEndWait(model);
        }
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[10]].motId, 0, 10, 0);
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[1]].motId, 0, 10, 2);
    chancetime_ObjWalk(object, 200.0f, 0.0f, 300.0f, 10);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    chancetime_dancerWorkTbl[3].func = chancetime_ObjIdle;
}

void chancetime_Dancer4Proc(void) {
    omObjData *obj;
    omObjData *motObj;
    omObjData *srcObj;

    obj = omAddObj(20, 4, 0, -1, NULL);
    chancetime_dancerWorkTbl[4].obj = obj;
    motObj = chancetime_hostWork.obj;
    srcObj = chancetime_dancerWorkTbl[0].obj;
    obj->model[1] = Hu3DModelLink(srcObj->model[1]);
    Hu3DModelPosSet(obj->model[1], chancetime_dancerPosTbl[3].x, chancetime_dancerPosTbl[3].y, chancetime_dancerPosTbl[3].z);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM1);
    obj->model[2] = Hu3DModelLink(srcObj->model[2]);
    Hu3DModelPosSet(obj->model[2], chancetime_dancerPosTbl[3].x, chancetime_dancerPosTbl[3].y, chancetime_dancerPosTbl[3].z);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM1);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[motObj->motion[0]].motId, 0, 10, 2);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    chancetime_dancerWorkTbl[4].func = chancetime_Dancer4Dance;
    while (TRUE) {
        chancetime_dancerWorkTbl[4].func(obj);
        HuPrcVSleep();
    }
}

void chancetime_Dancer4Dance(omObjData *object) {
    s16 model = object->model[1];
    omObjData *motObj = chancetime_hostWork.obj;
    f32 y;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(4);
    y = Hu3DData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            Hu3DData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    Hu3DData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(1);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            chancetime_MotionEndWait(model);
        }
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[10]].motId, 0, 10, 0);
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[1]].motId, 0, 10, 2);
    chancetime_ObjWalk(object, 400.0f, 0.0f, 300.0f, 10);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    chancetime_dancerWorkTbl[4].func = chancetime_ObjIdle;
}

void chancetime_HostLJumpProc(void) {
    omObjData *parent = chancetime_hostWork.obj;
    omObjData *object = omAddObj(20, 4, 0, -1, NULL);

    chancetime_hostLWork.obj = object;
    object->model[1] = parent->model[1];
    object->model[2] = parent->model[2];
    Hu3DModelPosSet(object->model[1], chancetime_hostLJumpPos.x, chancetime_hostLJumpPos.y, chancetime_hostLJumpPos.z);
    Hu3DModelPosSet(object->model[2], chancetime_hostLJumpPos.x, chancetime_hostLJumpPos.y, chancetime_hostLJumpPos.z);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    chancetime_hostLWork.func = chancetime_HostLJump;
    while (TRUE) {
        chancetime_hostLWork.func(object);
        HuPrcVSleep();
    }
}

void chancetime_HostLJump(omObjData *object) {
    s16 model = chancetime_hostWork.obj->model[1];
    omObjData *motObj = chancetime_hostWork.obj;
    Vec unusedPos;
    f32 y;
    f32 speed;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(3);
    y = Hu3DData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            Hu3DData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    Hu3DData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(2);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            chancetime_MotionEndWait(model);
        }
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[9]].motId, 0, 10, 0);
    HuPrcSleep(42);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[12]].motId, 0, 10, 0);
    // Copied but never read in the original.
    unusedPos.x = Hu3DData[model].pos.x;
    unusedPos.y = Hu3DData[model].pos.y;
    unusedPos.z = Hu3DData[model].pos.z;
    (void)unusedPos;
    speed = 20.0f;
    while (TRUE) {
        Hu3DData[model].pos.y += speed;
        Hu3DData[model].pos.z += 10.0f;
        if (Hu3DData[model].pos.z >= -250.0f) {
            Hu3DData[object->model[2]].pos.x = Hu3DData[model].pos.x;
            Hu3DData[object->model[2]].pos.y = 0.0f;
            Hu3DData[object->model[2]].pos.z = Hu3DData[model].pos.z;
            Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        if (Hu3DData[model].pos.y <= 0.0f) {
            break;
        }
        speed -= 2.0f;
        HuPrcVSleep();
    }
    Hu3DData[model].pos.y = 0.0f;
    Hu3DData[object->model[2]].pos.x = Hu3DData[model].pos.x;
    Hu3DData[object->model[2]].pos.y = 0.0f;
    Hu3DData[object->model[2]].pos.z = Hu3DData[model].pos.z;
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[5]].motId, 0, 10, 2);
    chancetime_introEndF = 1;
    chancetime_hostLWork.func = chancetime_ObjIdle;
}

void chancetime_HostRJumpProc(void) {
    omObjData *parent = chancetime_hostWork.obj;
    omObjData *object = omAddObj(20, 4, 0, -1, NULL);

    chancetime_hostRWork.obj = object;
    object->model[1] = parent->model[3];
    object->model[2] = parent->model[4];
    Hu3DModelPosSet(object->model[1], chancetime_hostRJumpPos.x, chancetime_hostRJumpPos.y, chancetime_hostRJumpPos.z);
    Hu3DModelPosSet(object->model[2], chancetime_hostRJumpPos.x, chancetime_hostRJumpPos.y, chancetime_hostRJumpPos.z);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    chancetime_hostRWork.func = chancetime_HostRJump;
    while (TRUE) {
        chancetime_hostRWork.func(object);
        HuPrcVSleep();
    }
}

void chancetime_HostRJump(omObjData *object) {
    s16 model = chancetime_hostWork.obj->model[3];
    omObjData *motObj = chancetime_hostWork.obj;
    Vec unusedPos;
    f32 y;
    f32 speed;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    HuPrcSleep(4);
    y = Hu3DData[model].pos.y;
    for (i = 0; i < 3; i++) {
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[12]].motId, 0, 10, 0);
        for (j = 0; j < 9; j++) {
            Hu3DData[model].pos.y = y + sindf(j * 20.0f) * 50.0f;
            HuPrcVSleep();
        }
    }
    Hu3DData[model].pos.y = y;
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(1);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[5]].motId, 0, 10, 0);
            Hu3DMotionSpeedSet(model, 1.5f);
            chancetime_MotionEndWait(model);
        }
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[6]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
        Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[7]].motId, 0, 10, 0);
        Hu3DMotionSpeedSet(model, 1.5f);
        chancetime_MotionEndWait(model);
    }
    HuPrcSleep(1);
    Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[10]].motId, 0, 10, 0);
    HuPrcSleep(42);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[motObj->motion[12]].motId, 0, 10, 0);
    // Copied but never read in the original.
    unusedPos.x = Hu3DData[model].pos.x;
    unusedPos.y = Hu3DData[model].pos.y;
    unusedPos.z = Hu3DData[model].pos.z;
    (void)unusedPos;
    speed = 20.0f;
    while (TRUE) {
        Hu3DData[model].pos.y += speed;
        Hu3DData[model].pos.z += 10.0f;
        if (Hu3DData[model].pos.z >= -250.0f) {
            Hu3DData[object->model[2]].pos.x = Hu3DData[model].pos.x;
            Hu3DData[object->model[2]].pos.y = 0.0f;
            Hu3DData[object->model[2]].pos.z = Hu3DData[model].pos.z;
            Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        if (Hu3DData[model].pos.y <= 0.0f) {
            break;
        }
        speed -= 3.0f;
        HuPrcVSleep();
    }
    Hu3DData[model].pos.y = 0.0f;
    Hu3DData[object->model[2]].pos.x = Hu3DData[model].pos.x;
    Hu3DData[object->model[2]].pos.y = 0.0f;
    Hu3DData[object->model[2]].pos.z = Hu3DData[model].pos.z;
    Hu3DMotionShiftSet(model, Hu3DData[motObj->motion[1]].motId, 0, 10, 2);
    chancetime_ObjWalk(object, 400.0f, 0.0f, 300.0f, 10);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    chancetime_hostRWork.func = chancetime_ObjIdle;
}

s32 chancetime_MotionEndCheck(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && Hu3DMotion[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

void chancetime_MotionEndWait(s16 arg0) {
    HuPrcSleep(15);
    while (!chancetime_MotionEndCheck(arg0)) {
        HuPrcVSleep();
    }
}

void chancetime_ObjPosMove(omObjData *object, f32 x, f32 y, f32 z, s32 arg4) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    chancetime_ObjPosMoveV(object, &pos, arg4);
}

void chancetime_ObjPosMoveV(omObjData *object, Vec *pos, s32 arg2) {
    chancetime_ObjPosMoveEx(object, pos, arg2, 1);
}

void chancetime_ObjPosMoveEx(omObjData *object, Vec *pos, s32 time, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = object->model[1];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = pos->x - start.x;
    diff.y = pos->y - start.y;
    diff.z = pos->z - start.z;
    if (faceDir != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = time;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    for (i = 0.0f; i < (f32)time; i += 1.0f) {
        cur.x = i * step.x + start.x;
        cur.y = i * step.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        if (object->model[2] >= 0) {
            Hu3DModelPosSet(object->model[2], cur.x, 0.0f, cur.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    if (object->model[2] >= 0) {
        Hu3DModelPosSet(object->model[2], pos->x, 0.0f, pos->z);
    }
    HuPrcVSleep();
}

void chancetime_ObjRotMoveV(omObjData *object, Vec *rot, s32 time) {
    Vec start;
    Vec diff;
    Vec cur;
    s16 model = object->model[1];
    f32 i;
    f32 t;

    start.x = Hu3DData[model].rot.x;
    start.y = Hu3DData[model].rot.y;
    start.z = Hu3DData[model].rot.z;
    diff.x = rot->x - start.x;
    diff.y = rot->y - start.y;
    diff.z = rot->z - start.z;
    for (i = 0.0f; i < (f32)time; i += 1.0f) {
        t = 90.0f / time * i;
        cur.x = sindf(t) * diff.x + start.x;
        cur.y = sindf(t) * diff.y + start.y;
        cur.z = sindf(t) * diff.z + start.z;
        Hu3DModelRotSet(model, cur.x, cur.y, cur.z);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, rot->x, rot->y, rot->z);
    HuPrcVSleep();
}

void chancetime_ObjRotMove(omObjData *object, f32 x, f32 y, f32 z, s32 arg4) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    chancetime_ObjRotMoveV(object, &pos, arg4);
}

f32 chancetime_DirAngleGet(Vec *from, Vec *to) {
    Vec diff;

    diff.x = to->x - from->x;
    diff.z = to->z - from->z;
    return -(atan2df(diff.z, diff.x) - 90.0f);
}

void chancetime_ObjWalk(omObjData *object, f32 x, f32 y, f32 z, s32 arg4) {
    Vec from;
    Vec to;
    s16 modelId = object->model[1];

    from.x = Hu3DData[modelId].pos.x;
    from.y = Hu3DData[modelId].pos.y;
    from.z = Hu3DData[modelId].pos.z;
    to.x = x;
    to.y = y;
    to.z = z;
    chancetime_ObjRotMove(object, 0.0f, chancetime_DirAngleGet(&from, &to), 0.0f, 10);
    chancetime_ObjPosMoveV(object, &to, arg4);
}

void chancetime_TitleProc(void) {
    s16 anim;
    s16 sprite;
    f32 scale;
    s32 i;

    scale = 0.0f;
    anim = HuSprAnimDataRead(0x1C0006);
    sprite = espEntry(anim, 0, 0);
    espPosSet(sprite, 160, 120);
    espDispOff(sprite);
    espScaleSet(sprite, scale, scale);
    espDispOn(sprite);
    for (i = 0; i < 5; i++) {
        scale = sindf(i * 18.0f) * 1.2f;
        espScaleSet(sprite, scale, scale);
        HuPrcVSleep();
    }
    HuAudFXPlay(0x261);
    scale = 1.0f;
    espScaleSet(sprite, scale, scale);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        espScaleSet(sprite, scale, scale);
        scale = sindf(i * 4.5f);
        espTPLvlSet(sprite, 256.0f - scale * 256.0f);
        scale += 1.0f;
        HuPrcVSleep();
    }
    espDispOn(sprite);
    espKill(sprite);
    HuSprAnimKill(anim);
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 chancetime_IntroEndCheck(void) {
    return chancetime_introEndF;
}

void chancetime_HostTurn(void) {
    omObjData *object = chancetime_hostWork.obj;

    chancetime_ObjRotMove(object, 0.0f, 45.0f, 0.0f, 10);
}
