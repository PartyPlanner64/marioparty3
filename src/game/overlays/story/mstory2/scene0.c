#include "common.h"
#include "game/hmfmath.h"
#include "game/overlays/minigame.h"
#include "mstory2.h"

extern void (*const mstory2_sceneCreateTbl[])(void);
extern Mstory2ObjWork mstory2_scene0WorkTbl[3];
extern s16 mstory2_scene0TumbleFaceAnimTbl[3];
extern Vec mstory2_scene0TumblePos;
extern const Vec mstory2_scene0TumbleStartPos;
extern s16 mstory2_scene0TumbleFaceSlot;
extern s16 mstory2_scene0ShadowMdl;
extern Vec mstory2_scene0StarPos;
extern const Vec mstory2_scene0StarStartPos;
extern f32 mstory2_scene0StarY;

void mstory2_WinCreate(void);
void mstory2_HmfAnimSet(s16 model, s16 arg1, s16 arg2);
void mstory2_Scene0EventProc(void);
void mstory2_Scene0EventDestroy(void);
void mstory2_Scene0EventExec(omObjData *);
void mstory2_Scene0EventStartExec(omObjData *);
void mstory2_Scene0EventCancelExec(omObjData *);
void mstory2_Scene0TumbleProc(void);
void mstory2_Scene0ObjIdle(omObjData *obj);
void mstory2_Scene0TumbleDestroy(void);
void mstory2_Scene0TumbleHop(omObjData *obj);
void mstory2_Scene0StarProc(void);
void mstory2_Scene0StarDestroy(void);
void mstory2_Scene0StarFloat(omObjData *obj);
void mstory2_SceneEnd(void);
void mstory2_SceneStageGoto(void);
void mstory2_WinOpen(void);
void mstory2_WinClose(void);
void mstory2_WinMesExec(s32 mess);
s16 mstory2_WinChoiceGet(void);

f32 mstory2_scene0TumbleHopT = -1.5f;
f32 mstory2_scene0StarFloatAngle = 0.0f;
f32 mstory2_scene0StarFloatOfs = 0.0f;

void mstory2_Scene0Create(void) {
    mstory2_WinCreate();
    mstory2_scene0ShadowMdl = Hu3DModelRead(9, 0x2B9);
    omAddPrcObj(mstory2_Scene0TumbleProc, 0x1001, 0x1000, 0);
    omAddPrcObj(mstory2_Scene0StarProc, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(mstory2_Scene0EventProc, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    Hu3DModelAttrSet(mstory2_scene0ShadowMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void mstory2_Scene0ObjIdle(omObjData *obj) {
}

void mstory2_Scene0EventProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    mstory2_scene0WorkTbl[2].obj = obj;
    mstory2_scene0WorkTbl[2].unk_08 = 0;
    mstory2_scene0WorkTbl[2].func = mstory2_Scene0EventExec;
    omPrcSetDestructor(0, mstory2_Scene0EventDestroy);
    while (1) {
        mstory2_scene0WorkTbl[2].func(obj);
        HuPrcVSleep();
    }
}

void mstory2_Scene0EventDestroy(void) {
}

void mstory2_Scene0EventExec(omObjData *obj) {
    s16 choice;

    HuPrcSleep(40);
    HuAudFXPlay(0x159);
    mstory2_WinOpen();
    mstory2_WinMesExec(0x5A7F);
    mstory2_WinClose();
    Hu3DMotionShiftSet(mstory2_scene0WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene0WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(20);
    Hu3DMotionShiftSet(mstory2_scene0WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene0WorkTbl[1].obj->motion[1]].motId, 0, 10, 2);
    mstory2_WinOpen();
    mstory2_WinMesExec(0x5A80);
    choice = mstory2_WinChoiceGet();
    mstory2_WinClose();
    Hu3DMotionShiftSet(mstory2_scene0WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene0WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
    switch (choice) {
        case 0:
            mstory2_scene0WorkTbl[2].func = mstory2_Scene0EventStartExec;
            break;
        case 1:
            mstory2_scene0WorkTbl[2].func = mstory2_Scene0EventCancelExec;
            break;
    }
}

void mstory2_Scene0EventStartExec(omObjData *obj) {
    Hu3DMotionShiftSet(mstory2_scene0WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene0WorkTbl[1].obj->motion[3]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(mstory2_scene0WorkTbl[0].obj->model[1], Hu3DData[mstory2_scene0WorkTbl[0].obj->motion[0]].motId, 0, 10, 0);
    mstory2_HmfAnimSet(mstory2_scene0WorkTbl[0].obj->model[1], mstory2_scene0TumbleFaceSlot, mstory2_scene0TumbleFaceAnimTbl[1]);
    mstory2_scene0WorkTbl[0].func = mstory2_Scene0TumbleHop;
    mstory2_scene0WorkTbl[0].unk_08 = 1;
    mstory2_WinOpen();
    mstory2_WinMesExec(0x5A81);
    mstory2_WinClose();
    Hu3DMotionShiftSet(mstory2_scene0WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene0WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
    mstory2_scene0WorkTbl[1].unk_08 = 1;
    mstory2_scene0WorkTbl[0].unk_08 = 2;
    HuPrcSleep(20);
    while (TRUE) {
        if (mstory2_scene0WorkTbl[0].unk_08 == 3) {
            break;
        }
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DData[mstory2_scene0WorkTbl[0].obj->model[1]].pos.y += 30.0f;
        Hu3DData[mstory2_scene0WorkTbl[1].obj->model[1]].pos.y += 60.0f;
        Hu3DData[mstory2_scene0WorkTbl[0].obj->model[2]].scale.x = Hu3DData[mstory2_scene0WorkTbl[0].obj->model[2]].scale.z -= 0.075f;
        Hu3DData[mstory2_scene0WorkTbl[1].obj->model[2]].scale.x = Hu3DData[mstory2_scene0WorkTbl[1].obj->model[2]].scale.z -= 0.075f;
        if (Hu3DData[mstory2_scene0WorkTbl[0].obj->model[1]].pos.y >= 500.0f) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcVSleep();
    mstory2_SceneStageGoto();
    mstory2_scene0WorkTbl[1].func = mstory2_Scene0ObjIdle;
    mstory2_scene0WorkTbl[0].func = mstory2_Scene0ObjIdle;
    mstory2_scene0WorkTbl[2].func = mstory2_Scene0ObjIdle;
}

void mstory2_Scene0EventCancelExec(omObjData *obj) {
    mstory2_HmfAnimSet(mstory2_scene0WorkTbl[0].obj->model[1], mstory2_scene0TumbleFaceSlot, mstory2_scene0TumbleFaceAnimTbl[2]);
    HuPrcSleep(20);
    Hu3DMotionShiftSet(mstory2_scene0WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene0WorkTbl[1].obj->motion[2]].motId, 0, 10, 2);
    mstory2_WinOpen();
    mstory2_WinMesExec(0x5A82);
    mstory2_WinClose();
    Hu3DMotionShiftSet(mstory2_scene0WorkTbl[1].obj->model[1], Hu3DData[mstory2_scene0WorkTbl[1].obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(30);
    mstory2_SceneEnd();
    mstory2_scene0WorkTbl[1].func = mstory2_Scene0ObjIdle;
    mstory2_scene0WorkTbl[0].func = mstory2_Scene0ObjIdle;
    mstory2_scene0WorkTbl[2].func = mstory2_Scene0ObjIdle;
}

const Vec mstory2_scene0TumbleStartPos = { 138.0f, 100.0f, 514.0f };

const Vec mstory2_scene0StarStartPos = { 0.0f, 225.0f, 400.0f };
const Vec mstory2_scene0UnusedPos0 = { 0.0f, 0.0f, 0.0f }; /* Unreferenced. */

const char mstory2_scene0TumbleAnimName[] = "c204n_0_DEF";

void mstory2_Scene0TumbleProc(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    mstory2_scene0WorkTbl[0].obj = obj;
    mstory2_scene0WorkTbl[0].unk_08 = 0;
    mstory2_scene0WorkTbl[0].func = mstory2_Scene0ObjIdle;
    obj->model[1] = Hu3DModelRead(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory2_scene0ShadowMdl);
    omObjMotionRead(obj, 0, 0xA0076);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    mstory2_scene0TumblePos = mstory2_scene0TumbleStartPos;
    Hu3DModelPosSet(obj->model[1], mstory2_scene0TumblePos.x, mstory2_scene0TumblePos.y, mstory2_scene0TumblePos.z);
    Hu3DModelPosSet(obj->model[2], mstory2_scene0TumblePos.x, -5.0f, mstory2_scene0TumblePos.z);
    data = DataRead(0xA0082);
    mstory2_scene0TumbleFaceAnimTbl[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, mstory2_scene0TumbleAnimName);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(mstory2_scene0TumbleFaceAnimTbl[0], 1, 0);
    Hu3DAnimBankSet(mstory2_scene0TumbleFaceAnimTbl[0], 0);
    mstory2_scene0TumbleFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory2_scene0TumbleFaceAnimTbl[0], 0, mstory2_scene0TumbleAnimName);
    data = DataRead(0xA0084);
    mstory2_scene0TumbleFaceAnimTbl[1] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory2_scene0TumbleFaceSlot = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, mstory2_scene0TumbleFaceAnimTbl[0], 0, mstory2_scene0TumbleAnimName);
    data = DataRead(0xA0080);
    mstory2_scene0TumbleFaceAnimTbl[2] = Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    mstory2_HmfAnimSet(obj->model[1], mstory2_scene0TumbleFaceSlot, mstory2_scene0TumbleFaceAnimTbl[0]);
    omPrcSetDestructor(0, mstory2_Scene0TumbleDestroy);
    while (TRUE) {
        mstory2_scene0WorkTbl[0].func(obj);
        HuPrcVSleep();
    }
}

void mstory2_Scene0TumbleDestroy(void) {
}

void mstory2_Scene0TumbleHop(omObjData *obj) {
    if (mstory2_scene0WorkTbl[0].unk_08 == 1) {
        Hu3DData[obj->model[1]].pos.y += mstory2_scene0TumbleHopT * mstory2_scene0TumbleHopT * (mstory2_scene0TumbleHopT >= 0.0f ? -8.75f : 8.75f);
        if (mstory2_scene0TumbleHopT > 1.5f) {
            mstory2_scene0TumbleHopT = -1.5f;
        } else {
            mstory2_scene0TumbleHopT += 0.2f;
        }
    } else if (mstory2_scene0WorkTbl[0].unk_08 == 2) {
        Hu3DData[obj->model[1]].pos.y += mstory2_scene0TumbleHopT * mstory2_scene0TumbleHopT * (mstory2_scene0TumbleHopT >= 0.0f ? -8.75f : 8.75f);
        if (mstory2_scene0TumbleHopT > 1.5f) {
            mstory2_scene0TumbleHopT = 0.0f;
            Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
            mstory2_scene0WorkTbl[0].func = mstory2_Scene0ObjIdle;
            mstory2_scene0WorkTbl[0].unk_08 = 3;
        } else {
            mstory2_scene0TumbleHopT += 0.2f;
        }
    }
}

void mstory2_Scene0StarProc(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    mstory2_scene0WorkTbl[1].obj = obj;
    mstory2_scene0WorkTbl[1].unk_08 = 0;
    obj->model[1] = Hu3DModelRead(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(mstory2_scene0ShadowMdl);
    AuraCreate(obj->model[1]);
    omObjMotionRead(obj, 0, 0xA0123);
    omObjMotionRead(obj, 1, 0xA0129);
    omObjMotionRead(obj, 2, 0xA0125);
    omObjMotionRead(obj, 3, 0xA0128);
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    mstory2_scene0StarPos = mstory2_scene0StarStartPos;
    Hu3DModelPosSet(obj->model[1], mstory2_scene0StarPos.x, mstory2_scene0StarPos.y, mstory2_scene0StarPos.z);
    Hu3DModelPosSet(obj->model[2], mstory2_scene0StarPos.x, -5.0f, mstory2_scene0StarPos.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, mstory2_Scene0StarDestroy);
    mstory2_scene0WorkTbl[1].func = mstory2_Scene0StarFloat;
    while (1) {
        mstory2_scene0WorkTbl[1].func(obj);
        HuPrcVSleep();
    }
}

void mstory2_Scene0StarDestroy(void) {
}

void mstory2_Scene0StarFloat(omObjData *obj) {
    mstory2_scene0StarY = Hu3DData[obj->model[1]].pos.y;
    mstory2_scene0StarFloatOfs = sindf(mstory2_scene0StarFloatAngle) * 15.0f + 15.0f;
    mstory2_scene0StarFloatAngle += 2.0f;
    if (mstory2_scene0StarFloatAngle >= 360.0f) {
        mstory2_scene0StarFloatAngle -= 360.0f;
    }
    if (mstory2_scene0WorkTbl[1].unk_08 != 1) {
        Hu3DModelPosSet(obj->model[1], 0.0f, mstory2_scene0StarFloatOfs + 225.0f, 400.0f);
    }
}
