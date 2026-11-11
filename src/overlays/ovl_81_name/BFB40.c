#include "common_duel.h"
#include "ovl_81.h"

typedef struct UnkObj {
    Object *unk_00;
    f32 unk_04;
} UnkObj;

extern u16 D_801029C4_name_81;
extern s16 D_80105624_name_81;
extern f32 D_80100E10_name_81;
extern f32 D_80100E14_name_81;

void func_800D85B4_name_81(omObjData *playerObj);
void func_800D87E8_name_81(omObjData *arg0);

void func_800D7D70_name_81(void) {
    s32 i;
    for (i = 0; i < 128; i++) {
        D_801029C8_name_81[i] = 0;
    }
}

s16 MBDMotionLock(s16 arg0) {
    D_801029C8_name_81[arg0]++;
    return arg0;
}

s16 func_800D7DC8_name_81(s32 arg0) {
    s16 res = Hu3DMotionCreate(DataRead(arg0), 8);
    D_801029C8_name_81[res]++;
    return res;
}

void MBDMotionKill(s16 arg0) {
    if (D_801029C8_name_81[arg0] != 0) {
        D_801029C8_name_81[arg0]--;
        if (D_801029C8_name_81[arg0] == 0) {
            Hu3DMotionKill(arg0);
        }
    }
}

s16 func_800D7E68_name_81(s16 arg0) {
    if (D_801029C8_name_81[arg0] != 0) {
        D_801029C8_name_81[arg0]++;
        return arg0;
    }
    return -1;
}

void MBDModelInit(void) {
    D_801029C0_name_81 = NULL;
    D_801029C4_name_81 = 0;
    D_80105624_name_81 = 1;
    func_800D7D70_name_81();
    func_800D87DC_name_81(100.0f);
    func_800D85A8_name_81(1.0f);
}

void MBDModelClose(void) {
    while (D_801029C0_name_81 != NULL) {
        MBDModelKill(D_801029C0_name_81);
    }
}

Object *func_800D7F4C_name_81(void) {
    Object *temp_v0;

    temp_v0 = HuMemMemoryAllocTemp(sizeof(Object));
    if (temp_v0 != NULL) {
        D_801029C4_name_81++;
        temp_v0->prev = D_801029C0_name_81;
        temp_v0->next = NULL;
        if (D_801029C0_name_81 != NULL) {
            D_801029C0_name_81->next = temp_v0;
        }
        D_801029C0_name_81 = temp_v0;
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D8010_name_81);

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

    object = func_800D7F4C_name_81();
    if (object != NULL) {
        object->unk8 = 0xFF;

        if (dataPtr != NULL) {
            motionCnt = dataPtr[0];
            dataPtr++;
        }

        objData = object->omObj1 = omAddObj(0x4000, 1, motionCnt, -1, func_800D85B4_name_81);

        mdlIdx = func_8000B108_main(arg0, 0x6A9);
        omSetStatBit(objData, OM_STAT_NOALLPAUSE);
        objData->model[0] = mdlIdx;
        omSetRot(objData, 0.0f, 0.0f, 0.0f);
        func_8001C814_main(mdlIdx, 2, 2);
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
            objData->motion[i] = func_800D7DC8_name_81(*dataPtr++);
        }

        if ((arg1 >= 0) && (arg3 > 0.0f)) {
            objData = object->omObj2 = omAddObj(0x4000, 1, 0, -1, func_800D87E8_name_81);
            mdlIdx = func_8000B108_main(arg1, 0x229);
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

void func_800D85A8_name_81(f32 arg0) {
    D_80100E10_name_81 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D85B4_name_81);

void func_800D87DC_name_81(f32 arg0) {
    D_80100E14_name_81 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D87E8_name_81);

void MBDModelTempAllocFree(Object* arg0) {
    func_8001C514_main(arg0->omObj1->model[0]);

    if (arg0->omObj2 != NULL) {
        func_8001C514_main(arg0->omObj2->model[0]);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D898C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D8B18_name_81);

void MBDModelAttrSetDispOn(Object* arg0) {
    Object* temp_s0 = arg0;

    func_8001C258_main(temp_s0->omObj1->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    if (temp_s0->omObj2 != NULL) {
        func_8001C258_main(temp_s0->omObj2->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
}

void MBDModelDispOn(Object* arg0) {
    MBDModelAttrSetDispOn(arg0);
    arg0->flags |= 8;
}

void MBDModelAttrSetDispOff(Object* arg0) {
    Object* temp_s0 = arg0;

    func_8001C258_main(temp_s0->omObj1->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (temp_s0->omObj2 != NULL) {
        func_8001C258_main(temp_s0->omObj2->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
}

void MBDModelDispOff(Object* arg0) {
    MBDModelAttrSetDispOff(arg0);
    arg0->flags &= ~8;
}

void MBDModelKill(Object* arg0) {
    s32 i;

    if (D_801029C0_name_81 != NULL) {
        if (arg0->prev != NULL) {
            arg0->prev->next = arg0->next;
        }
        if (arg0->next != NULL) {
            arg0->next->prev = arg0->prev;
        } else {
            D_801029C0_name_81 = arg0->prev;
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
        D_801029C4_name_81 -= 1;
    }
}

s32 func_800D9098_name_81(Object *arg0) {
    Object *node;

    for (node = D_801029C0_name_81; node != NULL; node = node->prev) {
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
    func_8001C814_main(arg0->omObj1->model[0], -1, arg2);
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
    if (Hu3DData[arg0->omObj1->model[0]].motTime == D_800CCF58_main[Hu3DData[arg0->omObj1->model[0]].motId].unk02) {
        ret = 1;
    }
    return ret;
}

u16 func_800D92A8_name_81(Object *arg0) {
    u16 ret;

    ret = 0;
    if (Hu3DData[arg0->omObj1->model[0]].motTime == 0.0f) {
        ret = 1;
    }
    return ret;
}

void func_800D92F8_name_81(omObjData* arg0) {
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

omObjData* func_800D9384_name_81(Object* arg0, Vec* arg1, s32 arg2) {
    Vec sp18;
    f32 var_f20;
    f32 var_f4;
    omObjData* temp_v0;

    MBDVecDirGet(&arg0->coords, arg1, &sp18);
    temp_v0 = omAddObj(0x1000, 0, 0, -1, func_800D92F8_name_81);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D94C4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/BFB40", func_800D9668_name_81);

void func_800D96F4_name_81(void) {
    Object **work = HuPrcCurrentGet()->user_data;
    Object *obj = *work;

    func_8001C814_main(obj->omObj1->model[0], 3, 0);
    func_800EFABC_name_81(obj);
    MBDModelKill(obj);
    omDelPrcObj(NULL);
}

void func_800D974C_name_81(Object* arg0) {
    Process* proc;
    Object** work;

    proc = omAddPrcObj(func_800D96F4_name_81, 0, 0, 0x40);
    work = HuMemMemoryAlloc(proc->heap, 0x10);
    proc->user_data = work;
    *work = arg0;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/BFB40", D_80101C48_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/BFB40", D_80101C4C_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/BFB40", D_80101C50_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/BFB40", D_80101C54_name_81);
