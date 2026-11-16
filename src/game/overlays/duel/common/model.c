#include "common_duel.h"
#include "ovl_81.h"

typedef struct UnkObj {
    Object *unk_00;
    f32 unk_04;
} UnkObj;

typedef struct UnkTemp {
    s32 unk_00;
    s32 unk_04;
    f32 unk_08;
    f32 unk_0C;
} UnkTemp; //sizeof 0x10

typedef struct ModelSpinWork {
    /* 0x00 */ Object *obj;
    /* 0x04 */ f32 angle;
    /* 0x08 */ f32 speed;
    /* 0x0C */ s32 time;
} ModelSpinWork; //sizeof 0x10

extern u16 mbdModelNum;
extern s16 mbdModelDispFlag;
extern u8 omAllPauseF;

f32 mbdModelScaleMul = 1.0f;
f32 mbdShadowHeightMax = 100.0f;

const UnkTemp mbdModelDataTbl[] = {
    { 0x000200A2, 0x00000009, 1.0f, 0.9f },
    { 0x000300A2, 0x00000009, 1.0f, 0.9f },
    { 0x000700A2, 0x00000009, 1.0f, 1.2f },
    { 0x000400A2, 0x00000009, 1.0f, 1.1f },
    { 0x000500A2, 0x00000009, 1.0f, 1.1f },
    { 0x000600A2, 0x00000009, 0.9f, 1.0f },
    { 0x000800A2, 0x00000009, 1.0f, 0.9f },
    { 0x00090003, 0x00000009, 1.0f, 1.2f },
    { 0x000A002E, 0x00000009, 0.7f, 1.4f },
    { 0x000A0000, 0x00000009, 0.9f, 0.9f },
    { 0x000A00C5, 0x00000009, 0.6f, 1.2f },
    { 0x000A00CE, 0x0013025F, 0.4f, 0.0f },
    { 0x000A00A5, 0x00000009, 1.2f, 1.0f },
    { 0x000A00E7, 0x0013025F, 0.9f, 1.8f },
    { 0x0013014C, 0x00000009, 1.6666666f, 0.0f },
    { 0x000200A0, 0x00000009, 1.0f, 0.9f },
    { 0x000300A0, 0x00000009, 1.0f, 0.9f },
    { 0x000700A0, 0x00000009, 1.0f, 1.2f },
    { 0x000400A0, 0x00000009, 1.0f, 1.1f },
    { 0x000500A0, 0x00000009, 1.0f, 1.1f },
    { 0x000600A0, 0x00000009, 1.0f, 1.5f },
    { 0x000800A0, 0x00000009, 1.0f, 0.9f },
    { 0x00090000, 0x00000009, 1.0f, 1.2f },
    { 0x00130145, 0x00000009, 1.0f, 0.0f },
    { 0x00130146, 0x00000009, 1.0f, 0.0f },
    { 0x00130147, 0x00000009, 1.0f, 0.0f },
    { 0x001301CA, 0x00000009, 0.65f, 0.0f },
    { 0x000A0022, 0x00000009, 1.2f, 0.7f },
    { 0x000B0028, 0x00000009, 1.0f, 0.0f },
    { 0x001301CC, 0x00000009, 1.0f, 1.0f },
    { 0x000A0000, 0x00000009, 1.0f, 0.0f },
    { 0x000B000D, 0x00000009, 3.0f, 0.0f },
    { 0x000A00FF, 0x00000009, 1.2f, 0.7f },
    { 0x000B0026, 0x00000009, 1.0f, 0.0f },
    { 0x000B0027, 0x00000009, 1.0f, 0.0f },
    { 0x000A005B, 0x00000009, 1.0f, 1.0f },
    { 0x000A0136, 0x00000009, 1.0f, 0.8f },
    { 0x000A008E, 0x00000009, 1.0f, 1.0f },
    { 0x000A00C1, 0x00000009, 1.2f, 1.0f },
    { 0x000A00C3, 0x00000009, 1.2f, 1.0f },
    { 0x000A00C2, 0x00000009, 1.2f, 1.0f },
    { 0x000A0101, 0x00000009, 0.8f, 1.0f },
    { 0x000A00D9, 0x00000009, 0.6f, 1.0f },
    { 0x000A013F, 0x00000009, 2.0f, 1.0f },
    { 0x000A010D, 0x00000009, 0.6f, 1.0f },
    { 0x00130149, 0x00000009, 1.6666666f, 0.0f },
    { 0x0013014A, 0x00000009, 1.6666666f, 0.0f },
    { 0x00130150, 0x00000009, 1.6666666f, 0.0f },
    { 0x00130151, 0x00000009, 1.6666666f, 0.0f },
    { 0x00130152, 0x00000009, 1.6666666f, 0.0f },
    { 0x00130141, 0x00000009, 1.6666666f, 0.0f },
    { 0x00130142, 0x00000009, 1.6666666f, 0.0f },
    { 0x000A011B, 0x00000009, 1.6666666f, 3.3333333f },
    { 0x000B0006, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0007, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0008, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0009, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B000A, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B000B, 0x00000009, 1.6666666f, 0.0f },
    { 0x000A0122, 0x00000009, 1.6666666f, 2.0f },
    { 0x00130143, 0x00000009, 0.5f, 0.0f },
    { 0x000A0063, 0x00000009, 1.5f, 0.0f },
    { 0x000A0075, 0x00000009, 1.5f, 1.5f },
    { 0x00130144, 0x00000009, 1.0f, 0.0f },
    { 0x0013014C, 0x00000009, 1.6666666f, 0.0f },
    { 0x0013014D, 0x00000009, 1.6666666f, 0.0f },
    { 0x0013014E, 0x00000009, 1.6666666f, 0.0f },
    { 0x0013014F, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B001D, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B001E, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B001F, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0020, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0021, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0022, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0017, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0018, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0019, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B001A, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B001B, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0010, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0011, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0012, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0013, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B001C, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B000E, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B000F, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0016, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0015, 0x00000009, 1.0f, 0.5f },
    { 0x000B0014, 0x00000009, 1.6666666f, 0.0f },
    { 0x000B0029, 0x00000009, 1.6666666f, 0.0f },
    { 0x00330008, 0x00000009, 3.3333333f, 0.0f },
    { 0x000B002A, 0x00000009, 1.6666666f, 0.0f },
};

void MBDModelObjMain(omObjData *playerObj);
void MBDShadowObjMain(omObjData *arg0);

void MBDMotionRefTblInit(void) {
    s32 i;
    for (i = 0; i < 128; i++) {
        mbdMotionRefTbl[i] = 0;
    }
}

s16 MBDMotionLock(s16 arg0) {
    mbdMotionRefTbl[arg0]++;
    return arg0;
}

s16 MBDMotionCreate(s32 arg0) {
    s16 res = Hu3DMotionCreate(DataRead(arg0), 8);
    mbdMotionRefTbl[res]++;
    return res;
}

void MBDMotionKill(s16 arg0) {
    if (mbdMotionRefTbl[arg0] != 0) {
        mbdMotionRefTbl[arg0]--;
        if (mbdMotionRefTbl[arg0] == 0) {
            Hu3DMotionKill(arg0);
        }
    }
}

s16 MBDMotionRefCopy(s16 arg0) {
    if (mbdMotionRefTbl[arg0] != 0) {
        mbdMotionRefTbl[arg0]++;
        return arg0;
    }
    return -1;
}

void MBDModelInit(void) {
    mbdModelListHead = NULL;
    mbdModelNum = 0;
    mbdModelDispFlag = 1;
    MBDMotionRefTblInit();
    MBDShadowHeightMaxSet(100.0f);
    MBDModelScaleMulSet(1.0f);
}

void MBDModelClose(void) {
    while (mbdModelListHead != NULL) {
        MBDModelKill(mbdModelListHead);
    }
}

Object *MBDModelAlloc(void) {
    Object *temp_v0;

    temp_v0 = HuMemMemoryAllocTemp(sizeof(Object));
    if (temp_v0 != NULL) {
        mbdModelNum++;
        temp_v0->prev = mbdModelListHead;
        temp_v0->next = NULL;
        if (mbdModelListHead != NULL) {
            mbdModelListHead->next = temp_v0;
        }
        mbdModelListHead = temp_v0;
        temp_v0->flags = 8;
        HuVecCopyXYZ(&temp_v0->coords, 0.0f, 0.0f, 0.0f);
        HuVecCopyXYZ(&temp_v0->rot, 0.0f, 0.0f, 1.0f);
        HuVecCopyXYZ(&temp_v0->scale, 1.0f, 1.0f, 1.0f);
        temp_v0->velocity.x = 0.0f;
        temp_v0->velocity.y = 0.0f;
        temp_v0->velocity.z = 0.0f;
        temp_v0->unk46 = -1;
        temp_v0->unk48 = -1;
    }
    return temp_v0;
}

Object *MBDModelCreate(u8 arg0, s32 *dataPtr) {
    Object *object;
    omObjData *objData;
    UnkObj *work;
    s16 mdlIdx;
    s16 motionCnt;
    s16 i;

    motionCnt = 0;

    object = MBDModelAlloc();
    if (object != NULL) {
        object->unk8 = arg0;

        if (dataPtr != NULL) {
            motionCnt = dataPtr[0];
            dataPtr++;
            object->mtncnt = motionCnt;
        } else {
            object->mtncnt = -1;
        }

        objData = object->omObj1 = omAddObj(0x4000, 1, motionCnt, -1, MBDModelObjMain);

        mdlIdx = Hu3DModelRead(mbdModelDataTbl[object->unk8].unk_00, 0x6A9);
        omSetStatBit(objData, OM_STAT_NOALLPAUSE);
        objData->model[0] = mdlIdx;
        omSetRot(objData, 0.0f, 0.0f, 0.0f);
        Hu3DMotionAttrSet(mdlIdx, 2, 2);
        Hu3DModelCameraSet(mdlIdx, HU3D_CAM0);
        Hu3DModelScaleSet(mdlIdx, 0.0f, 0.0f, 0.0f);
        if (Hu3DData[mdlIdx].motId != 0xFF) {
            object->unk46 = MBDMotionLock(Hu3DData[mdlIdx].motId);
        }

        work = HuMemMemoryAllocTemp(sizeof(UnkObj));
        objData->data = work;
        work->unk_00 = object;
        work->unk_04 = mbdModelDataTbl[object->unk8].unk_08 * 0.6f;

        for (i = 0; i < motionCnt; i++) {
            objData->motion[i] = MBDMotionCreate(*dataPtr++);
        }

        if (mbdModelDataTbl[object->unk8].unk_0C > 0.0f) {
            objData = object->omObj2 = omAddObj(0x4000, 1, 0, -1, MBDShadowObjMain);
            mdlIdx = Hu3DModelRead(mbdModelDataTbl[object->unk8].unk_04, 0x229);
            omSetStatBit(objData, OM_STAT_NOALLPAUSE);
            objData->model[0] = mdlIdx;
            omSetRot(objData, 0.0f, 0.0f, 0.0f);
            Hu3DModelCameraSet(mdlIdx, HU3D_CAM0);
            Hu3DModelScaleSet(mdlIdx, 0.0f, 0.0f, 0.0f);

            work = HuMemMemoryAllocTemp(sizeof(UnkObj));
            objData->data = work;
            work->unk_00 = object;
            work->unk_04 = mbdModelDataTbl[object->unk8].unk_0C * 0.6f;
        } else {
            object->omObj2 = NULL;
        }
    }
    return object;
}

Object *MBDModelFileCreate(s32 arg0, s32 arg1, f32 arg2, f32 arg3, u32 *arg4) {
    Object *object;
    omObjData *objData;
    UnkObj *work;
    u32 *dataPtr;
    s16 mdlIdx;
    s16 motionCnt;
    s16 i;

    dataPtr = arg4;
    motionCnt = 0;

    object = MBDModelAlloc();
    if (object != NULL) {
        object->unk8 = 0xFF;

        if (dataPtr != NULL) {
            motionCnt = dataPtr[0];
            dataPtr++;
        }

        objData = object->omObj1 = omAddObj(0x4000, 1, motionCnt, -1, MBDModelObjMain);

        mdlIdx = Hu3DModelRead(arg0, 0x6A9);
        omSetStatBit(objData, OM_STAT_NOALLPAUSE);
        objData->model[0] = mdlIdx;
        omSetRot(objData, 0.0f, 0.0f, 0.0f);
        Hu3DMotionAttrSet(mdlIdx, 2, 2);
        Hu3DModelCameraSet(mdlIdx, HU3D_CAM0);
        Hu3DModelScaleSet(mdlIdx, 0.0f, 0.0f, 0.0f);
        if (Hu3DData[mdlIdx].motId != 0xFF) {
            object->unk46 = MBDMotionLock(Hu3DData[mdlIdx].motId);
        }

        work = HuMemMemoryAllocTemp(sizeof(UnkObj));
        objData->data = work;
        work->unk_00 = object;
        work->unk_04 = arg2;

        for (i = 0; i < motionCnt; i++) {
            objData->motion[i] = MBDMotionCreate(*dataPtr++);
        }

        if ((arg1 >= 0) && (arg3 > 0.0f)) {
            objData = object->omObj2 = omAddObj(0x4000, 1, 0, -1, MBDShadowObjMain);
            mdlIdx = Hu3DModelRead(arg1, 0x229);
            omSetStatBit(objData, OM_STAT_NOALLPAUSE);
            objData->model[0] = mdlIdx;
            omSetRot(objData, 0.0f, 0.0f, 0.0f);
            Hu3DModelCameraSet(mdlIdx, HU3D_CAM0);
            Hu3DModelScaleSet(mdlIdx, 0.0f, 0.0f, 0.0f);

            work = HuMemMemoryAllocTemp(sizeof(UnkObj));
            objData->data = work;
            work->unk_00 = object;
            work->unk_04 = arg3;
        } else {
            object->omObj2 = NULL;
        }
    }
    return object;
}

void MBDModelScaleMulSet(f32 arg0) {
    mbdModelScaleMul = arg0;
}

void MBDModelObjMain(omObjData *playerObj) {
    Vec2f sp10;
    Object *temp_s0;
    UnkObj *temp_s2;

    temp_s2 = playerObj->data;
    temp_s0 = temp_s2->unk_00;

    if ((omAllPauseF == 0) || (temp_s0->flags & 0x10)) {
        if (temp_s0->velocity.z != 0.0f) {
            temp_s0->velocity.y += temp_s0->velocity.z;
            temp_s0->velocity.x = temp_s0->velocity.x + temp_s0->velocity.y;
            if (temp_s0->velocity.x < 0.0f) {
                temp_s0->velocity.x = 0.0f;
                temp_s0->velocity.y = 0.0f;
                temp_s0->velocity.z = 0.0f;
            }
        }
    }

    if (!(mbdModelDispFlag & 1)) {
        MBDModelAttrSetDispOff(temp_s0);
        return;
    }

    if (!(temp_s0->flags & 8)) {
        MBDModelAttrSetDispOff(temp_s0);
        return;
    }

    if (temp_s0->flags & 2) {
        MBDCamera3Dto2D(&temp_s0->coords, &sp10);
        if ((sp10.x > 370.0f) ||
            (sp10.x < -50.0f) ||
            (sp10.y > 290.0f) ||
            (sp10.y < -20.0f)) {
            MBDModelAttrSetDispOff(temp_s0);
            return;
        }
    }
    MBDModelAttrSetDispOn(temp_s0);

    if (!(temp_s0->flags & 4)) {
        playerObj->rot.y = MBDVecAngleGet(&temp_s0->rot);
    }

    playerObj->trans.x = temp_s0->coords.x;
    playerObj->trans.y = temp_s0->coords.y + temp_s0->velocity.x;
    playerObj->trans.z = temp_s0->coords.z;
    playerObj->scale.x = temp_s0->scale.x * temp_s2->unk_04 * MBDBackMdlScaleGet() * mbdModelScaleMul;
    playerObj->scale.y = temp_s0->scale.y * temp_s2->unk_04 * MBDBackMdlScaleGet() * mbdModelScaleMul;
    playerObj->scale.z = temp_s0->scale.z * temp_s2->unk_04 * MBDBackMdlScaleGet() * mbdModelScaleMul;
}

void MBDShadowHeightMaxSet(f32 arg0) {
    mbdShadowHeightMax = arg0;
}

void MBDShadowObjMain(omObjData *arg0) {
    f32 var_f20;
    Object *temp_s0;
    UnkObj *temp_s2;

    temp_s2 = arg0->data;
    temp_s0 = temp_s2->unk_00;
    var_f20 = 1.0f;
    arg0->rot.y = MBDVecAngleGet(&temp_s0->rot);
    if (temp_s0->flags & 1) {
        var_f20 = 0.0f;
    } else {
        if (temp_s0->velocity.x != 0.0f) {
            var_f20 = 1.0f - (temp_s0->velocity.x / mbdShadowHeightMax);
            if (var_f20 <= 0.0f) {
                var_f20 = 0.0f;
            }
            if (var_f20 >= 1.0f) {
                var_f20 = 1.0f;
            }
        }
    }
    arg0->scale.x = var_f20 * temp_s0->scale.x * temp_s2->unk_04 * MBDBackMdlScaleGet() * mbdModelScaleMul;
    arg0->scale.y = MBDBackMdlScaleGet();
    arg0->scale.z = var_f20 * temp_s0->scale.z * temp_s2->unk_04 * MBDBackMdlScaleGet() * mbdModelScaleMul;
    arg0->trans.x = temp_s0->coords.x;
    arg0->trans.y = temp_s0->coords.y;
    arg0->trans.z = temp_s0->coords.z;
}

void MBDModelTempAllocFree(Object* arg0) {
    Hu3DModelDynamicFree(arg0->omObj1->model[0]);

    if (arg0->omObj2 != NULL) {
        Hu3DModelDynamicFree(arg0->omObj2->model[0]);
    }
}

void MBDModelChange(Object *arg0, u8 arg1) {
    u16 temp;
    s16 mdlIdx;

    arg0->unk8 = arg1;
    Hu3DMotionSet(arg0->omObj1->model[0], -1);
    Hu3DModelKill(arg0->omObj1->model[0]);
    if (arg0->unk46 != -1) {
        MBDMotionKill(arg0->unk46);
    }

    temp = Hu3DModelRead(mbdModelDataTbl[arg0->unk8].unk_00, 0x6A9);
    arg0->omObj1->model[0] = temp;
    mdlIdx = temp;
    Hu3DMotionAttrSet(mdlIdx, 2, 2);
    Hu3DModelCameraSet(mdlIdx, HU3D_CAM0);
    ((UnkObj *)arg0->omObj1->data)->unk_04 = mbdModelDataTbl[arg0->unk8].unk_08;
    if (Hu3DData[mdlIdx].motId != 0xFF) {
        arg0->unk46 = MBDMotionLock(Hu3DData[mdlIdx].motId);
    } else {
        arg0->unk46 = -1;
    }

    if (arg0->omObj2 != NULL) {
        Hu3DModelKill(arg0->omObj2->model[0]);
        temp = Hu3DModelRead(mbdModelDataTbl[arg0->unk8].unk_04, 0x229);
        arg0->omObj2->model[0] = temp;
        mdlIdx = temp;
        Hu3DModelCameraSet(mdlIdx, HU3D_CAM0);
        ((UnkObj *)arg0->omObj2->data)->unk_04 = mbdModelDataTbl[arg0->unk8].unk_0C;
    }
}

Object *MBDModelLinkCreate(Object *src) {
    Object *object;
    omObjData *objData;
    UnkObj *work;
    s16 mdlIdx;
    s16 i;

    object = MBDModelAlloc();
    if (object != NULL) {
        object->unk8 = src->unk8;

        objData = object->omObj1 = omAddObj(0x4000, 1, src->omObj1->mtncnt, -1, MBDModelObjMain);

        mdlIdx = Hu3DModelLink(src->omObj1->model[0]);
        omSetStatBit(objData, OM_STAT_NOALLPAUSE);
        objData->model[0] = mdlIdx;
        omSetRot(objData, 0.0f, 0.0f, 0.0f);
        Hu3DMotionAttrSet(mdlIdx, 2, 2);
        Hu3DModelCameraSet(mdlIdx, HU3D_CAM0);
        Hu3DModelScaleSet(mdlIdx, 0.0f, 0.0f, 0.0f);

        if (Hu3DData[mdlIdx].motId != 0xFF) {
            object->unk46 = MBDMotionRefCopy(Hu3DData[mdlIdx].motId);
        } else {
            object->unk46 = src->unk46;
        }

        work = HuMemMemoryAllocTemp(sizeof(UnkObj));
        objData->data = work;
        work->unk_00 = object;
        if (object->unk8 != 0xFF) {
            work->unk_04 = mbdModelDataTbl[object->unk8].unk_08 * 0.6f;
        } else {
            work->unk_04 = 1.0f;
        }

        for (i = 0; i < src->omObj1->mtncnt; i++) {
            objData->motion[i] = MBDMotionRefCopy(src->omObj1->motion[i]);
        }
        object->mtncnt = src->mtncnt;

        if ((src->omObj2 != NULL) && (object->unk8 != 0xFF) &&
            (mbdModelDataTbl[object->unk8].unk_0C > 0.0f)) {
            objData = object->omObj2 = omAddObj(0x4000, 1, 0, -1, MBDShadowObjMain);

            mdlIdx = Hu3DModelLink(src->omObj2->model[0]);
            omSetStatBit(objData, OM_STAT_NOALLPAUSE);
            objData->model[0] = mdlIdx;
            omSetRot(objData, 0.0f, 0.0f, 0.0f);
            Hu3DModelCameraSet(mdlIdx, HU3D_CAM0);
            Hu3DModelScaleSet(mdlIdx, 0.0f, 0.0f, 0.0f);

            work = HuMemMemoryAllocTemp(sizeof(UnkObj));
            objData->data = work;
            work->unk_00 = object;
            work->unk_04 = mbdModelDataTbl[object->unk8].unk_0C * 0.6f;
        } else {
            object->omObj2 = NULL;
        }
    }
    return object;
}

void MBDModelAttrSetDispOn(Object* arg0) {
    Object* temp_s0 = arg0;

    Hu3DModelAttrSet(temp_s0->omObj1->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    if (temp_s0->omObj2 != NULL) {
        Hu3DModelAttrSet(temp_s0->omObj2->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
}

void MBDModelDispOn(Object* arg0) {
    MBDModelAttrSetDispOn(arg0);
    arg0->flags |= 8;
}

void MBDModelAttrSetDispOff(Object* arg0) {
    Object* temp_s0 = arg0;

    Hu3DModelAttrSet(temp_s0->omObj1->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (temp_s0->omObj2 != NULL) {
        Hu3DModelAttrSet(temp_s0->omObj2->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
}

void MBDModelDispOff(Object* arg0) {
    MBDModelAttrSetDispOff(arg0);
    arg0->flags &= ~8;
}

void MBDModelKill(Object* arg0) {
    s32 i;

    if (mbdModelListHead != NULL) {
        if (arg0->prev != NULL) {
            arg0->prev->next = arg0->next;
        }
        if (arg0->next != NULL) {
            arg0->next->prev = arg0->prev;
        } else {
            mbdModelListHead = arg0->prev;
        }
        Hu3DMotionSet(arg0->omObj1->model[0], -1);
        Hu3DModelKill(arg0->omObj1->model[0]);
        if (arg0->omObj2 != NULL) {
            Hu3DModelKill(arg0->omObj2->model[0]);
        }

        for (i = 0; i < arg0->omObj1->mtncnt; i++) {
            MBDMotionKill(arg0->omObj1->motion[i]);
        }

        if (arg0->unk46 != -1) {
            MBDMotionKill(arg0->unk46);
        }

        HuMemMemoryFreeTemp(arg0->omObj1->data);

        arg0->omObj1->data = NULL;
        omDelObj(arg0->omObj1);

        if (arg0->omObj2 != NULL) {
            HuMemMemoryFreeTemp(arg0->omObj2->data);
            arg0->omObj2->data = NULL;
            omDelObj(arg0->omObj2);
        }
        HuMemMemoryFreeTemp(arg0);
        mbdModelNum -= 1;
    }
}

s32 MBDModelExistCheck(Object *arg0) {
    Object *node;

    for (node = mbdModelListHead; node != NULL; node = node->prev) {
        if (node == arg0) {
            return 1;
        }
    }
    return 0;
}

void MBDMotionSet(Object *arg0, s16 arg1, u16 arg2) {
    u16 var_v1;
    s16 mtncnt;

    if (arg0->mtncnt == -1) {
        return;
    }

    if (arg1 == -1) {
        var_v1 = arg0->unk46;
        arg0->unk48 = arg1;
    } else {
        mtncnt = arg0->mtncnt;
        if (arg1 > mtncnt - 1) {
            return;
        }
        var_v1 = arg0->omObj1->motion[arg1];
        arg0->unk48 = arg1;
    }
    Hu3DMotionSet(arg0->omObj1->model[0], var_v1);
    Hu3DMotionAttrSet(arg0->omObj1->model[0], -1, arg2);
}

void MBDMotionShiftSet(Object* arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    s16 var;

    if (arg0->mtncnt == -1) {
        return;
    }

    if (arg1 == -1) {
        var = arg0->unk46;
        arg0->unk48 = arg1;
    } else {
        if (arg1 > arg0->mtncnt - 1) {
            return;
        }
        var = arg0->omObj1->motion[arg1];
        arg0->unk48 = arg1;
    }
    Hu3DMotionShiftSet(arg0->omObj1->model[0], var, arg2, arg3, arg4);
}

u16 MBDMotionCheck(Object *arg0) {
    u16 ret;

    ret = 0;
    if (Hu3DData[arg0->omObj1->model[0]].motTime == Hu3DMotion[Hu3DData[arg0->omObj1->model[0]].motId].unk02) {
        ret = 1;
    }
    return ret;
}

u16 MBDMotionStartCheck(Object *arg0) {
    u16 ret;

    ret = 0;
    if (Hu3DData[arg0->omObj1->model[0]].motTime == 0.0f) {
        ret = 1;
    }
    return ret;
}

void MBDModelTurnObjMain(omObjData* arg0) {
    Object* temp_s1;

    temp_s1 = arg0->data;

    if (--arg0->work[1] == 0) {
        temp_s1->rot.x = arg0->rot.x;
        temp_s1->rot.y = arg0->rot.y;
        temp_s1->rot.z = arg0->rot.z;
        arg0->data = NULL;
        omDelObj(arg0);
        return;
    }

    arg0->scale.y += arg0->scale.x;
    temp_s1->rot.x = sindf(arg0->scale.y);
    temp_s1->rot.y = 0.0f;
    temp_s1->rot.z = cosdf(arg0->scale.y);
}

omObjData* MBDModelTurnCreate(Object* arg0, Vec* arg1, s32 arg2) {
    Vec sp18;
    f32 var_f20;
    f32 var_f4;
    omObjData* temp_v0;

    MBDVecDirGet(&arg0->coords, arg1, &sp18);
    temp_v0 = omAddObj(0x1000, 0, 0, -1, MBDModelTurnObjMain);
    temp_v0->work[1] = arg2;
    temp_v0->rot.x = sp18.x;
    temp_v0->rot.y = sp18.y;
    temp_v0->rot.z = sp18.z;
    var_f20 = MBDVecAngleGet(&arg0->rot);
    var_f4 = MBDVecAngleGet(&sp18);
    if (var_f4 < var_f20) {
        if ((var_f20 - var_f4) >= 180.0f) {
            var_f4 += 360.0f;
        }
    } else if ((var_f4 - var_f20) >= 180.0f) {
        var_f20 += 360.0f;
    }
    temp_v0->scale.y = var_f20;
    temp_v0->scale.x = (var_f4 - var_f20) / (f32) arg2;
    temp_v0->data = arg0;
    return temp_v0;
}

void MBDModelSpinProc(void) {
    ModelSpinWork *work = HuPrcCurrentGet()->user_data;
    Object *obj = work->obj;
    f32 angle = work->angle;
    f32 speed = work->speed;
    s32 time = work->time;
    HmfModel *model;
    f32 zero;

    while (time != 0) {
        sincosdf(angle, &Hu3DData[obj->omObj1->model[0]].mtx[2][0], &Hu3DData[obj->omObj1->model[0]].mtx[2][2]);
        Hu3DData[obj->omObj1->model[0]].mtx[0][2] = -Hu3DData[obj->omObj1->model[0]].mtx[2][0];

        model = &Hu3DData[obj->omObj1->model[0]];
        model->mtx[0][0] = model->mtx[2][2];

        model = &Hu3DData[obj->omObj1->model[0]];
        zero = 0.0f;
        model->mtx[3][2] = zero;
        model->mtx[3][1] = zero;
        model->mtx[3][0] = zero;
        model->mtx[2][3] = zero;
        model->mtx[2][1] = zero;
        model->mtx[1][3] = zero;
        model->mtx[1][2] = zero;
        model->mtx[1][0] = zero;
        model->mtx[0][3] = zero;
        model->mtx[0][1] = zero;

        model = &Hu3DData[obj->omObj1->model[0]];
        model->mtx[3][3] = 1.0f;
        model->mtx[1][1] = 1.0f;

        angle += speed;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (time > 0) {
            time--;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

Process *MBDModelSpinCreate(Object *obj, f32 angle, f32 speed, s32 time) {
    Process *proc;
    ModelSpinWork *work;

    proc = omAddPrcObj(MBDModelSpinProc, 0, 0, 0x40);
    work = HuMemMemoryAlloc(proc->heap, sizeof(ModelSpinWork));
    proc->user_data = work;
    work->obj = obj;
    work->angle = angle;
    work->speed = speed;
    work->time = time;
    return proc;
}

void MBDModelMotionKillProc(void) {
    Object **work = HuPrcCurrentGet()->user_data;
    Object *obj = *work;

    Hu3DMotionAttrSet(obj->omObj1->model[0], 3, 0);
    MBDModelMotionWait(obj);
    MBDModelKill(obj);
    omDelPrcObj(NULL);
}

void MBDModelMotionKillCreate(Object* arg0) {
    Process* proc;
    Object** work;

    proc = omAddPrcObj(MBDModelMotionKillProc, 0, 0, 0x40);
    work = HuMemMemoryAlloc(proc->heap, 0x10);
    proc->user_data = work;
    *work = arg0;
}
