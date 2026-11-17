#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "variables.h"
#include "macros.h"
#include "overlay.h"
#include "game/gamemes.h"
#include "game/hu3d.h"
#include "game/hmfcoll.h"
#include "game/esprite.h"
#include "game/hmfspr.h"
#include "game/audio.h"
#include "game/msm.h"
#include "game/graphics.h"
#include "game/hmfdraw.h"
#include "game/camera.h"
#include "game/pad.h"
#include "game/vibrator.h"
#include "game/util.h"
#include "game/hmflight.h"
#include "game/profiler.h"
#include "game/window.h"
#include "game/lightdebug.h"
#include "game/wipe.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/object.h"
#include "game/board.h"
#include "game/pause.h"
#include "game/printfunc.h"
#include "game/malloc.h"
#include "game/mallocblock.h"

typedef struct unkProcessStruct {
    u16 stat;
    s16 unk2;
    Process *processInstance;
    void (*destructor)();
} unkProcessStruct;

typedef union PauseObjWork {
    u32 words[4];
    u16 halfwords[8];
} PauseObjWork;

static u8 omMgAudParamTbl[][2] = {
    { 4, 20 }, { 4, 20 }, { 4, 20 }, { 1, 20 }, { 1, 20 }, { 4, 20 },
    { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 },
    { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 },
    { 1, 20 }, { 1, 20 }, { 4, 20 }, { 2, 20 }, { 1, 20 }, { 1, 20 },
    { 1, 20 }, { 1, 20 }, { 4, 20 }, { 1, 20 }, { 2, 20 }, { 1, 20 },
    { 1, 20 }, { 1, 20 }, { 1, 20 }, { 4, 20 }, { 4, 20 }, { 2, 20 },
    { 3, 20 }, { 4, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 },
    { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 },
    { 1, 20 }, { 1, 20 }, { 3, 20 }, { 4, 20 }, { 1, 20 }, { 1, 20 },
    { 4, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 },
    { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 4, 20 }, { 1, 20 },
    { 1, 20 }, { 4, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 },
};
static u8 omBoardAudParamTbl[][2] = {
    { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 }, { 1, 20 },
    { 1, 20 }, { 1, 20 }, { 1, 20 },
};
static u8 omDBGHu3DPauseFBak = 0;
static u8 omSysPauseCloseReq = 0;
static s16 omModeOvlPrev = -1;
static u16 omDBGPrevOvl = 999;
s32 omprevovl = 999;
s16 omprevovlPad = 0; // unreferenced
u8 omDBGPlayMode = 0;
u16 omdispinfo = 0;
static u8 omOvlKillWait = 0;
s16 omovlevtno = -1;
u16 omovlstat = 0;
s16 omovlhisidx = -1;
s16 omovlhisidxPad = 0; // unreferenced
static u8 omOvlChangeF = 1;
u8 omOvlSeKeepF = 0;
static omObjData *omobjall = NULL;
static s16 omPrcMax = 0;
static s16 omPrcNum = 0;
static s16 omPrcNextIdx = 0;
static unkProcessStruct *omPrcData = NULL;
static s16 omHu3DReinitF = 0;
static u8 omAudReinitF = 0;
static u8 omAudVolResetF = 1;
static s8 omSeFxMix = 0;
static s8 omPauseSubMusF = 0;
s16 omDBGInfoWin = -1;
omCharModelData omCharModelTbl[] = {
    { 0, 0x20000, { 0xA2, 0xA0, 0xA1 }, 1.0f },
    { 1, 0x30000, { 0xA2, 0xA0, 0xA1 }, 1.0f },
    { 2, 0x70000, { 0xA2, 0xA0, 0xA1 }, 1.0f },
    { 3, 0x40000, { 0xA2, 0xA0, 0xA1 }, 0.9f },
    { 4, 0x50000, { 0xA2, 0xA0, 0xA1 }, 0.8f },
    { 5, 0x60000, { 0xA2, 0xA0, 0xA1 }, 0.7f },
    { 6, 0x80000, { 0xA2, 0xA0, 0xA1 }, 1.0f },
    { 7, 0x90000, { 0x3, 0x0, 0x1 }, 1.0f },
};
static u8 omAudStopWait = 0;
static u8 omAudStopDoneF = 0;

extern s8 omHu3DBufNum;

extern s16 HuAudFxTypeNext;
extern s16 HuAudFxParamNext;
static u16 omMusFadeWait;
static u16 omPracticeSprAnim;
static u16 omPracticeSpr;
static s16 omPracticeSprAngle;
static s16 omPracticeSprPosNo;
static u8 omAudReinitWait;
static s16 omDBGPauseWin0;
static s16 omDBGPauseWin1;
extern u16 omMgActiveF;

extern f32 CFanOfs;
extern s16 omobjlast;
extern s16 ommaxobjs;
extern u8 HuGfxBufNum;
extern s16 omnumobjs;
extern f32 CFanLenM[];
extern omObjGroup omgroup[];
extern u16 omHu3DGfxNum;
extern s32 omovl;
extern u16 omovlLo;
extern u16 omHu3DReinitWait;
extern omObjData *omDBGSysKeyObj;
extern u16 omHu3DVtxNum;
extern f32 CFanOfsM[];
extern f32 CFanLen;
extern s16 omobjfirst;
extern s32 HuAudFadeObj;
extern u16 omHu3DMtxNum;
extern u8 omAllPauseF;
extern s16 omnextidx;

extern u16 omMusFadeTime;

typedef struct OverlayInfo {
    u8 *rom_start;
    u8 *rom_end;
    u8 *ram_start;
    u8 *code_start;
    u8 *code_end;
    u8 *data_start;
    u8 *data_end;
    u8 *bss_start;
    u8 *bss_end;
} OverlayInfo; // sizeof 0x24

void omInitObjMan(s16 numOfObjs, s32 numOfPrcs) {
    s16 prcCount;
    s32 i;
    omObjData *obj;
    unkProcessStruct *prcInfo;

    ommaxobjs = numOfObjs + 1;
    omnumobjs = 0;
    omnextidx = 0;
    omobjlast = -1;
    omobjfirst = -1;
    omDBGSysKeyObj = NULL;
    omSysExitReq = 0;
    omAllPauseF = 0;

    if (omobjall != NULL) {
        HuMemMemoryFreeTemp((void *)omobjall);
    }

    omobjall = (omObjData *)HuMemMemoryAllocTemp(ommaxobjs * sizeof(omObjData));

    for (i = 0; i < ommaxobjs; ++i) {
        obj = &omobjall[i];
        obj->stat = OM_STAT_DELETED;
        obj->next = -1;
        obj->prev = -1;
        obj->prio = -1;
        obj->mode = 0;
        obj->rot.x =
            obj->rot.y =
                obj->rot.z = 0.0f;
        obj->trans.x =
            obj->trans.y =
                obj->trans.z = 0.0f;
        obj->scale.x =
            obj->scale.y =
                obj->scale.z = 1.0f;
        obj->motion = NULL;
        obj->model = NULL;
        obj->data = NULL;
        obj->func = NULL;
        obj->next_idx = i + 1;
        obj->mtncnt = 0;
        obj->motion = NULL;
    }

    for (i = 0; i < 10; ++i) {
        omgroup[i].max_objs = 0;
        omgroup[i].num_objs = 0;
        omgroup[i].next_idx = 0;
        omgroup[i].objs = NULL;
        omgroup[i].next = 0;
    }

    prcCount = numOfPrcs + 2;
    omPrcMax = prcCount;
    omPrcNum = 0;
    omPrcNextIdx = 0;
    omPrcData = (unkProcessStruct *)HuMemMemoryAllocTemp(prcCount * sizeof(unkProcessStruct));

    for (i = 0; i < omPrcMax; ++i) {
        prcInfo = &omPrcData[i];
        prcInfo->stat = OM_STAT_DELETED;
        prcInfo->unk2 = i + 1;
        prcInfo->processInstance = NULL;
        prcInfo->destructor = NULL;
    }

    CFanLen = 20000.0f;
    CFanOfs = 10000.0f;

    for (i = 0; i < 4; ++i) {
        CFanLenM[i] = 20000.0f;
        CFanOfsM[i] = 10000.0f;
    }

    HuAudFadeObj = 0;
    omMusFadeTime = 0x5A;
}

void omDestroyObjMan(void) {
    omObjData *obj;
    omObjGroup *group;
    unkProcessStruct *prcInfo;
    s32 i;

    omobjlast = -1;

    for (i = 0; i < ommaxobjs; i++) {
        obj = &omobjall[i];
        if (obj->stat == OM_STAT_DELETED) {
            continue;
        }
        if (obj->model != NULL) {
            HuMemMemoryFreeTemp(obj->model);
        }
        if (obj->motion != NULL) {
            HuMemMemoryFreeTemp(obj->motion);
        }
        if (obj->data != NULL) {
            HuMemFree(obj->data);
        }
    }

    HuMemMemoryFreeTemp(omobjall);
    omobjall = NULL;
    ommaxobjs = 0;

    for (i = 0; i < 10; i++) {
        if (omgroup[i].max_objs != 0) {
            if (omgroup[i].objs != NULL) {
                HuMemMemoryFreeTemp(omgroup[i].objs);
                omgroup[i].objs = NULL;
            }
            if (omgroup[i].next != NULL) {
                HuMemMemoryFreeTemp(omgroup[i].next);
                omgroup[i].next = NULL;
            }
            omgroup[i].max_objs = 0;
        }
    }

    for (i = 0; i < omPrcMax; i++) {
        prcInfo = &omPrcData[i];
        if (prcInfo->stat != OM_STAT_DELETED) {
            HuPrcDestructorSet2(prcInfo->processInstance, prcInfo->destructor);
            HuPrcKill(prcInfo->processInstance);
        }
    }

    omPrcMax = 0;
    omPrcNum = 0;
    HuMemMemoryFreeTemp(omPrcData);
    omPrcData = NULL;
    HuMemFreeAllWithTag(TAG_OVERLAY);
    HuAudFadeObj = 0;
}

omObjData *omAddObj(s16 prio, u16 mdlcnt, u16 mtncnt, s16 group, omObjFunc func) {
    omObjData *object;
    s32 i;

    if (omnumobjs == ommaxobjs) {
        return NULL;
    }

    object = &omobjall[omnextidx];
    object->next_idx_alloc = omnextidx;
    object->prio = prio;

    omInsertObj(object);

    if (mdlcnt != 0) {
        object->model = HuMemMemoryAllocTemp(mdlcnt * sizeof(s16));
        object->mdlcnt = mdlcnt;
        for (i = 0; i < mdlcnt; ++i) {
            object->model[i] = -1;
        }
    } else {
        object->model = NULL;
        object->mdlcnt = 0;
    }

    if (mtncnt != 0) {
        object->motion = HuMemMemoryAllocTemp(mtncnt * sizeof(s16));
        object->mtncnt = mtncnt;
    } else {
        object->motion = NULL;
        object->mtncnt = 0;
    }

    if (group >= 0) {
        omAddMember(group, object);
    } else {
        object->group = group;
        object->group_idx = 0;
    }

    object->stat = OM_STAT_ACTIVE;
    object->mode = 0;
    object->func = func;
    object->work[0] = object->work[1] = object->work[2] = object->work[3] = 0;
    omnextidx = object->next_idx;
    ++omnumobjs;

    return object;
}

void omSetObjPrio(omObjData *obj, s16 prio) {
    obj->prio = prio;

    if (omobjlast != omobjfirst) {
        if (obj->next >= 0) {
            omobjall[obj->next].prev = obj->prev;
        }
        if (obj->prev >= 0) {
            omobjall[obj->prev].next = obj->next;
        }

        if (obj->prev < 0) {
            omobjfirst = omobjall[obj->next].next_idx_alloc;
        }
        if (obj->next < 0) {
            omobjlast = omobjall[obj->prev].next_idx_alloc;
        }

        omInsertObj(obj);
    }
}

// register object into linked list, sort based on priority
void omInsertObj(omObjData *obj) {
    s16 next_idx_alloc;
    s16 prio;
    s16 obj_idx;
    omObjData *obj_new;
    s16 prev_idx;

    next_idx_alloc = obj->next_idx_alloc;
    prio = obj->prio;

    if (omobjfirst == -1) {
        obj->prev = -1;
        obj->next = -1;
        omobjfirst = next_idx_alloc;
        omobjlast = next_idx_alloc;
        return;
    }
    for (obj_idx = omobjfirst; obj_idx != -1; obj_idx = obj_new->next) {
        obj_new = &omobjall[obj_idx];
        if (obj_new->prio <= prio) {
            break;
        }
        prev_idx = obj_idx;
    }
    if (obj_idx != -1) {
        obj->prev = obj_new->prev;
        obj->next = obj_idx;
        if (obj_new->prev != -1) {
            omobjall[obj_new->prev].next = next_idx_alloc;
        } else {
            omobjfirst = next_idx_alloc;
        }
        obj_new->prev = next_idx_alloc;
    } else {
        obj->next = -1;
        obj->prev = prev_idx;
        obj_new->next = next_idx_alloc;
        omobjlast = next_idx_alloc;
    }
}

void omDelObj(omObjData *obj) {
    u16 idx = obj->next_idx_alloc;

    if (omnumobjs != 0 && obj->stat != OM_STAT_DELETED) {
        omnumobjs--;

        if (obj->group >= 0) {
            omDelMember(obj);
        }

        if (obj->motion != NULL) {
            HuMemMemoryFreeTemp(obj->motion);
            obj->motion = NULL;
        }

        if (obj->model != NULL) {
            HuMemMemoryFreeTemp(obj->model);
            obj->model = NULL;
        }

        if (obj->data != NULL) {
            HuMemFree(obj->data);
            obj->data = NULL;
        }

        obj->stat = OM_STAT_DELETED;

        if (obj->next >= 0) {
            omobjall[obj->next].prev = obj->prev;
        }

        if (obj->prev < 0 || (omobjall[obj->prev].next = obj->next, obj->prev < 0)) {
            omobjfirst = omobjall[obj->next].next_idx_alloc;
        }

        if (obj->next < 0) {
            omobjlast = omobjall[obj->prev].next_idx_alloc;
        }

        obj->next_idx = omnextidx;
        omnextidx = idx;
    }
}

void omSetStat(omObjData *obj, u16 stat) {
    obj->stat = stat;
}

void omSetStatBit(omObjData *obj, u16 stat) {
    obj->stat |= stat;
}

void omResetStatBit(omObjData *obj, u16 stat) {
    obj->stat &= ~stat;
}

void omPrcSetStat(Process *prc, s32 stat) {
    omPrcData[prc->dtor_idx].stat = stat;
}

void omPrcSetStatBit(Process *prc, s32 stat) {
    omPrcData[prc->dtor_idx].stat |= stat;
}

void omPrcResetStatBit(Process *prc, s32 stat) {
    omPrcData[prc->dtor_idx].stat &= ~stat;
}

void omSetTra(omObjData *obj, f32 x, f32 y, f32 z) {
    obj->trans.x = x;
    obj->trans.y = y;
    obj->trans.z = z;
}

void omSetRot(omObjData *obj, f32 x, f32 y, f32 z) {
    obj->rot.x = x;
    obj->rot.y = y;
    obj->rot.z = z;
}

void omSetSca(omObjData *obj, f32 x, f32 y, f32 z) {
    obj->scale.x = x;
    obj->scale.y = y;
    obj->scale.z = z;
}

void omMakeGroup(u16 group, u16 max_objs) {
    omObjGroup *grp = &omgroup[group];
    s32 i;

    if (grp->objs != NULL) {
        HuMemMemoryFreeTemp(grp->objs);
    }
    if (grp->next != NULL) {
        HuMemMemoryFreeTemp(grp->next);
    }

    grp->next_idx = 0;
    grp->max_objs = max_objs;
    grp->num_objs = 0;
    grp->objs = HuMemMemoryAllocTemp(max_objs * sizeof(omObjData *));
    grp->next = HuMemMemoryAllocTemp(max_objs * sizeof(u16));

    for (i = 0; i < max_objs; i++) {
        grp->objs[i] = NULL;
        grp->next[i] = i + 1;
    }
}

void omAddMember(u16 group, omObjData *obj) {
    omObjGroup *group_ptr = &omgroup[group];

    if (group_ptr->num_objs != group_ptr->max_objs) {
        obj->group = group;
        obj->group_idx = group_ptr->next_idx;
        group_ptr->objs[group_ptr->next_idx] = obj;
        group_ptr->next_idx = group_ptr->next[group_ptr->next_idx];
        ++group_ptr->num_objs;
    }
}

void omDelMember(omObjData *obj) {
    omObjGroup *grp;

    if (obj->group != -1) {
        grp = &omgroup[obj->group];
        grp->objs[obj->group_idx] = NULL;
        grp->next[obj->group_idx] = grp->next_idx;
        grp->next_idx = obj->group_idx;
        obj->group = -1;
        grp->num_objs--;
    }
}

omObjData **omGetGroupMemberList(s16 arg0) {
    return omgroup[arg0].objs;
}

omObjData *omGetGroupMember(s16 arg0, u16 arg1) {
    return omgroup[arg0].objs[arg1];
}

void omGroupModeSet(s16 group, u32 stat) {
    omObjGroup *grp = &omgroup[group];
    s32 i;

    for (i = 0; i < grp->max_objs; i++) {
        if (grp->objs[i] != NULL) {
            grp->objs[i]->mode |= stat;
        }
    }
}

void omGroupMemberModeSet(s16 group, u16 idx, s32 flags) {
    omgroup[group].objs[idx]->mode |= flags;
}

void omObjModeSet(omObjData *obj, s32 arg1) {
    obj->mode |= arg1;
}

Process *omAddPrcObj(process_func func, u16 priority, s32 stackSize, s32 extDataSize) {
    s16 prevIdx;
    Process *newPrc;
    unkProcessStruct *temp_s0;

    if (omPrcNum == omPrcMax) {
        return NULL;
    }

    prevIdx = omPrcNextIdx;
    temp_s0 = &omPrcData[omPrcNextIdx];
    temp_s0->stat = OM_STAT_ACTIVE;
    omPrcNextIdx = temp_s0->unk2;

    newPrc = HuPrcCreate(func, priority, stackSize, extDataSize);

    temp_s0->processInstance = newPrc;
    newPrc->dtor_idx = prevIdx;
    HuPrcDestructorSet2(temp_s0->processInstance, omDestroyPrcObj);

    temp_s0->destructor = NULL;
    ++omPrcNum;

    return temp_s0->processInstance;
}

Process *omAddChildPrcObj(process_func func, s32 priority, s32 stack_size, s32 extra_data_size, Process *parent) {
    unkProcessStruct *prcInfo;
    Process *process;
    s16 prevIdx;

    if (omPrcNum == omPrcMax) {
        return NULL;
    }

    prevIdx = omPrcNextIdx;
    prcInfo = &omPrcData[omPrcNextIdx];
    prcInfo->stat = OM_STAT_ACTIVE;
    omPrcNextIdx = prcInfo->unk2;
    process = HuPrcChildCreate(func, priority, stack_size, extra_data_size, parent);
    prcInfo->processInstance = process;
    process->dtor_idx = prevIdx;
    HuPrcDestructorSet2(prcInfo->processInstance, omDestroyPrcObj);
    prcInfo->destructor = NULL;
    omPrcNum++;
    return prcInfo->processInstance;
}

s32 omDelPrcObj(Process *arg0) {
    if (arg0 != NULL) {
        return HuPrcKill(arg0);
    } else if (HuPrcKill(HuPrcCurrentGet()) == 0) {
        HuPrcVSleep();
    }
    return -1;
}

void omDestroyPrcObj(void) {
    Process *currPrc;
    unkProcessStruct *temp_s0;

    currPrc = HuPrcCurrentGet();
    temp_s0 = &omPrcData[currPrc->dtor_idx];
    if (temp_s0->destructor != NULL) {
        temp_s0->destructor();
    }
    temp_s0->stat = OM_STAT_DELETED;
    temp_s0->unk2 = omPrcNextIdx;
    omPrcNextIdx = currPrc->dtor_idx;
    --omPrcNum;
}

void omPrcSetDestructor(Process *prc, void *destructor) {
    unkProcessStruct *unk = &omPrcData[HuPrcCurrentGet()->dtor_idx];
    unk->destructor = destructor;
}

s32 omOvlCallEx(s32 ovlID, s16 event, u16 stat) {
    omOvlHisData *history;

    // history is full, cannot call overlay
    if (omovlhisidx >= ARRAY_COUNT(omovlhis)) {
        return FALSE;
    }

    history = &omovlhis[++omovlhisidx];
    history->overlayID = ovlID;
    history->event = event;
    history->stat = stat;
    omOvlGotoEx(ovlID, event, stat);
    return TRUE;
}

s32 omOvlReturnEx(s16 level) {
    omovlhisidx -= level;

    if (omovlhisidx < 0) {
        omovlhisidx = 0;
        omOvlGotoEx(omovlhis[0].overlayID, omovlhis[0].event, omovlhis[0].stat);
        return 0;
    }
    omOvlGotoEx(omovlhis[omovlhisidx].overlayID, omovlhis[omovlhisidx].event, omovlhis[omovlhisidx].stat);
    return 1;
}

void omOvlGotoEx(s32 ovlID, s16 event, u16 stat) {
    u8 var_a0_2;
    u8 var_v1;

    if (omovl != selmenu && omovl != selmenu2) {
        omprevovl = omovl;
        omDBGPrevOvl = omovlLo;
    }

    omOvlChangeF = 1;
    omovl = ovlID;
    omovlevtno = event;
    omovlstat = stat;
    omHu3DReinitWait = 0;

    if (stat & OM_OVL_STAT_GFXBUF2 && HuGfxBufNum != 2) {
        omHu3DLayerNumSet(2);
    } else if (stat & OM_OVL_STAT_GFXBUF3 && (HuGfxBufNum != 3)) {
        omHu3DLayerNumSet(3);
    }

    if ((omHu3DVtxNum != omOvlHu3DParamTbl[ovlID].unk_00) || (omHu3DGfxNum != omOvlHu3DParamTbl[ovlID].unk_02) || (omHu3DMtxNum != omOvlHu3DParamTbl[ovlID].unk_04)) {
        omHu3DParamSet(omOvlHu3DParamTbl[ovlID].unk_00, omOvlHu3DParamTbl[ovlID].unk_02, omOvlHu3DParamTbl[ovlID].unk_04);
    }

    if (!(stat & OM_OVL_STAT_AUDFXKEEP)) {
        if (stat & OM_OVL_STAT_BOARD) {
            var_a0_2 = omBoardAudParamTbl[GwSystem.current_board_index][0];
            var_v1 = omBoardAudParamTbl[GwSystem.current_board_index][1];
        } else if (stat & OM_OVL_STAT_MG) {
            var_a0_2 = omMgAudParamTbl[GwSystem.minigame_index - 1][0];
            var_v1 = omMgAudParamTbl[GwSystem.minigame_index - 1][1];
        } else {
            var_a0_2 = 1;
            var_v1 = 20;
        }

        if (stat & OM_OVL_STAT_AUDFX1) {
            var_a0_2 = 1;
            var_v1 = 20;
        } else if (stat & OM_OVL_STAT_AUDFX2) {
            var_a0_2 = 2;
            var_v1 = 20;
        } else if (stat & OM_OVL_STAT_AUDFX3) {
            var_a0_2 = 3;
            var_v1 = 20;
        } else if (stat & OM_OVL_STAT_AUDFX4) {
            var_a0_2 = 4;
            var_v1 = 20;
        } else if (stat & OM_OVL_STAT_AUDFX5) {
            var_a0_2 = 5;
            var_v1 = 20;
        }

        omSeFxMix = var_v1;
        HuAudFxTypeNext = var_a0_2;
    }
    HuAudFxParamNext = 0;
}

void omOvlHisChg(s16 level, s32 overlay, s16 event, u16 stat) {
    s32 ovlhisIndex = omovlhisidx - level;
    omOvlHisData *history;

    if (ovlhisIndex >= 0) {
        history = &omovlhis[ovlhisIndex];
        history->overlayID = overlay;
        history->event = event;
        history->stat = stat;
    }
}

void omOvlKill(void) {
    omOvlKillWait = 4;
    omMusFadeWait = omMusFadeTime;
    GMesClose();
    Hu3DAllKill();
    MapCollAllKill();
    omDestroyObjMan();
    espClose();
    Hu3DSprModelAllKill();
    Hu3DScreenClearF = 1;
}

extern s32 omovl;
extern u8 omHu3DReinitSkipF;
extern void *HuGfxFBPool[3];
extern u16 HuAudFxType;
extern u16 HuAudFxParam;
extern f32 Hu3DMatColScale;
extern f32 Hu3DMatAmbScale;
extern s32 omObjExecCnt;
extern omObjData *omCurObj;
extern s16 omExecStep;
extern void (*omCurObjFunc)(omObjData *);

extern u16 omHu3DReinitWait;

void omOvlEntry(void);

void omMain(void) {
    omObjData *obj;
    void (*func)(omObjData *);
    s16 temp_s3;
    s16 var_v1;
    s16 *model;
    s16 model_id;
    s32 i;
    s32 var_s0;
    s32 var_a0;
    s16 var_s1;
    u32 permSize;
    u32 permUsed;
    u32 tempSize;
    u8 temp_v0;
    u8 temp_v0_2;

    fontcolor = FONT_COLOR_YELLOW;
    permSize = HuMemHeapAllocPermSizeGet();
    permUsed = HuMemUsedMemoryBlockGetPerm();
    if (omdispinfo != 0) {
        sprintf(omDBGStrBuf, "%8lX(%ld)", permSize, permUsed);
        print8(0x10, 0x18, omDBGStrBuf);
        tempSize = HuMemHeapAllocTempSizeGet();
        sprintf(omDBGStrBuf, "%8lX(%ld)", tempSize, HuMemUsedMemoryBlockGetTemp());
        print8(0x10, 0x20, omDBGStrBuf);
        sprintf(omDBGStrBuf, "OVL:%d(%ld<%ld)", omovlhisidx, omovl, (s32)(s16)omDBGPrevOvl);
        print8(0x18, 0x28, omDBGStrBuf);
        sprintf(omDBGStrBuf, "OBJ:%d/%d", omnumobjs, ommaxobjs);
        print8(0x18, 0x30, omDBGStrBuf);
        sprintf(omDBGStrBuf, "PRC:%d/%d", omPrcNum, omPrcMax);
        print8(0x18, 0x38, omDBGStrBuf);
        sprintf(omDBGStrBuf, "%02X", HuAudStat);
        print8(0x70, 0x38, omDBGStrBuf);
        i = msmSysDummy(6);
        sprintf(omDBGStrBuf, "C:%04X D:%02X", i, msmSysDummy(5));
        print8(0x28, 0x40, omDBGStrBuf);
        if (omDBGInfoWin == -1) {
            omDBGInfoWin = printWin(0xE, 0x16, 0x82, 0x4A, 0xFF70);
        }
    }
    HuAudPlayerParamCopy();
    HuAudStatUpdate();
    if (omOvlChangeF != 0) {
        if (HuAudStat & 8) {
            omAudVolResetF = 1;
            if (!(HuAudStat & 1) && (omMusFadeWait != 0)) {
                omMusFadeWait--;
                if (omOvlKillWait != 0) {
                    omOvlKillWait--;
                }
                return;
            }
            HuAudSeqStop();
        }
        if (omOvlKillWait == 0) {
            if (omHu3DReinitSkipF != 1) {
                if (omHu3DReinitF == 1) {
                    if (omHu3DReinitWait == 4) {
                        Hu3DModelAllReset();
                    }
                    if (omHu3DReinitWait != 0) {
                        omHu3DReinitWait--;
                        return;
                    }
                    HuGfxBufNum = omHu3DBufNum;
                    HuGfxFBPoolSet(HuGfxFBPool, (u8)omHu3DBufNum, 2);
                    Hu3DInit(HuMemMemoryAllocPerm, HuMemMemoryFreePerm, omHu3DVtxNum, omHu3DGfxNum, (u16)(s32)omHu3DMtxNum, (u8)(s32)(u8)omHu3DBufNum);
                    Hu3DPreProc();
                    Hu3DScreenClear(0x02000000, 0x3D0800);
                    Hu3DCamInit(1);
                }
                omHu3DReinitF = 0;
                if (omAudReinitF == 0) {
                    if (omAudStopWait != 0) {
                        if (!(--omAudStopWait & 0xFF)) {
                            omAudStopDoneF = 1;
                        }
                        return;
                    } else {
                        omAudReinitWait = 0;
                        if ((HuAudDummy()) == 1) {
                            HuAudSeqStop();
                            msmMusStop(0);
                            msmMusStop(1);
                            HuAudFXAllStop();
                            if (omAudStopDoneF == 0) {
                                omAudStopWait = 5;
                                return;
                            } else if (omAudStopDoneF != 1) {
                                return;
                            } else if (msmSysIsPlay() != 0) {
                                return;
                            }
                            omAudReinitWait = 1;
                            omAudReinitF = 1;
                            return;
                        }
                    }
                } else {
                    if (!(--omAudReinitWait)) {
                        HuAudInit();
                        HuAudFxType = HuAudFxTypeNext;
                        HuAudFxParam = HuAudFxParamNext;
                        omAudReinitF = 0;
                        omAudStopDoneF = 0;
                    } else {
                        return;
                    }
                }
            }
            HuMemHeapInitTemp((void *)0x80128000, 0x18000);
            for (i = 0; i < 4; i++) {
                if (CheckControllerRead(i) != 0) {
                    ResetVibrator(i);
                }
            }
            omSysPauseDisableF = 0;
            espInit();
            CharAnimInit();
            omOvlChangeF = 0;
            omModeOvlLoad();
            OvlLoad(omovl);
            Hu3DLighInit();
            Hu3DMatColScale = 1.0f;
            Hu3DMatAmbScale = 1.0f;
            Hu3DGLightMaxSet(3);
            Hu3DGLightColorSet(0, 0x40, 0x40, 0x40);
            Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
            Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
            Hu3DGLightColorSet(2, 0, 0, 0);
            Hu3DGLightDirSet(2, 100.0f, 100.0f, 100.0f);
            Hu3DGLightColorSet(3, 0, 0, 0);
            Hu3DGLightDirSet(3, 100.0f, 100.0f, 100.0f);
            Hu3DGLightStatSet(0, 0, 0);
            Hu3DGLightStatSet(1, 0, 0);
            Hu3DGLightStatSet(2, 0, 0);
            Hu3DGLightStatSet(3, 0, 0);
            Hu3DBGColorSet(0, 0, 0);
            Hu3DScreenClearF = 1;
            Hu3DDrawModeSet(1);
            HuAudCharVoiceInit();
            if (omOvlSeKeepF == 0) {
                HuAudFXAllStop();
                if (omAudVolResetF == 1) {
                    HuAudFXMasterVolSet(0x7F);
                }
                HuAudFXAllPanning(0x40);
                msmSeSetFxMix(-1, omSeFxMix);
            }
            if (omAudVolResetF == 1) {
                HuAudSeqMasterVolSet(0x7F);
            }
            omAudVolResetF = 0;
            omHu3DReinitSkipF = 0;
            omMgActiveF = 0;
            omOvlEntry();
            for (i = 0; i < 4; i++) {
                if (CheckControllerRead(i) != 0) {
                    HuPadBtnDown[i] = 0;
                }
            }
            if (omOvlChangeF != 0) {
                omOvlKill();
                omOvlKillWait = 0;
                return;
            }
        } else {
            omOvlKillWait--;
            return;
        }
    }
    temp_s3 = HuProfCpuBegin(0, 0, 0xFF);
    omObjExecCnt = 0;
    omCurObj = NULL;
    for (var_s1 = omobjlast; var_s1 != -1;) {
        obj = &omobjall[var_s1];
        omExecStep = 0;
        omObjExecCnt++;
        omCurObj = obj;
        var_s1 = obj->prev;
        if (!(obj->stat & (OM_STAT_DELETED | OM_STAT_DISABLED))) {
            omCurObjFunc = obj->func;
            func = obj->func;
            if (func != NULL && !(obj->stat & (OM_STAT_ALLPAUSED | OM_STAT_PAUSED | OM_STAT_FUNCOFF))) {
                func(obj);
            }
            omExecStep = 1;
            if (omobjlast != -1 && omOvlChangeF == 0) {
                if (!(obj->stat & (OM_STAT_DELETED | OM_STAT_DISABLED))) {
                    if (omobjall[var_s1].stat & (OM_STAT_DELETED | OM_STAT_DISABLED)) {
                        var_s1 = obj->prev;
                    }
                    model = obj->model;
                    if (model != NULL) {
                        model_id = *model;
                        if (model_id != -1 && !(obj->stat & OM_STAT_MODELPAUSE)) {
                            Hu3DModelPosSet(model_id, obj->trans.x, obj->trans.y, obj->trans.z);
                            Hu3DModelRotSet(*obj->model, obj->rot.x, obj->rot.y, obj->rot.z);
                            Hu3DModelScaleSet(*obj->model, obj->scale.x, obj->scale.y, obj->scale.z);
                        }
                    }
                    omExecStep = 2;
                }
            } else {
                break;
            }
        }
    }
    omExecStep = 4;
    HuProfCpuEnd(temp_s3);
    omExecStep = 5;
    if (omOvlChangeF != 0) {
        omExecStep = 6;
        omOvlKill();
        omExecStep = 7;
    }
    omExecStep = 8;
}

typedef struct DebugMenuItem {
    /* 0x00 */ u8 disabled;
    /* 0x01 */ u8 x;
    /* 0x02 */ u8 y;
    /* 0x03 */ u8 color;
    /* 0x04 */ u8 selectedColor;
    /* 0x08 */ const char *label;
} DebugMenuItem; // Size 0xC

extern u16 HuAudMusEnableF;
extern u16 omPadBtn[];
extern u16 omPadBtnDown[];
extern u8 omSysPauseReadyF;
extern u16 omPauseWinInitF;

static DebugMenuItem omDBGMenuItemTbl[] = {
    { 0, 132, 112, 6, 14, " CANCEL" },
    { 0, 132, 120, 6, 14, " RESET " },
    { 0, 132, 128, 6, 14, " LIGHT " },
    { 0, 132, 136, 6, 14, " INFO  " },
    { 0, 132, 144, 6, 14, " MUSSTP" },
    { 0, 132, 152, 6, 14, " SE STP" },
};

static s16 omPracticeGroupTbl[] = { 5, 5, 5, 5, 2, 1, 1, 1, 1 };

static s16 omPracticeSprPosTbl[][2] = {
    { 160, 216 }, { 264, 216 }, { 160, 120 }, { 160, 24 },
};

static u8 omPracticeSprPosIdx[] = {
    1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 1,
};

void omSystemKeyCheckSetup(void) {
    omObjData *temp_v0;

    temp_v0 = omAddObj(0x7FD9, 0, 0, -1, omSystemKeyCheck);
    omDBGSysKeyObj = temp_v0;
    omSetStatBit(temp_v0, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    temp_v0->work[0] = 0;
    temp_v0->work[1] = 0;
    temp_v0->work[2] = 0;
}

// Debug pause menu.
void omDBGSystemKeyCheck(omObjData *object) {
    char *buf;
    s32 port;
    s32 i;
    u8 close = 0;

    if (object->work[0] & 1) {
        port = OM_GET_WORK_PTR(object, PauseObjWork)->halfwords[3];
        if (!(object->work[0] & 4)) {
            sprintf(omDBGStrBuf, "- PAUSE -");
            fontcolor = FONT_COLOR_DARK_GREEN;
            print8(125, 97, omDBGStrBuf);
            fontcolor = FONT_COLOR_GREEN;
            print8(124, 96, omDBGStrBuf);
            buf = omDBGStrBuf;
            for (i = 0; i < 6; i++) {
                sprintf(buf, omDBGMenuItemTbl[i].label);
                if (i == object->work[2]) {
                    fontcolor = omDBGMenuItemTbl[i].color;
                    print8(omDBGMenuItemTbl[i].x + 1, omDBGMenuItemTbl[i].y + 1, buf);
                    fontcolor = omDBGMenuItemTbl[i].selectedColor;
                    print8(omDBGMenuItemTbl[i].x, omDBGMenuItemTbl[i].y, buf);
                } else {
                    fontcolor = FONT_COLOR_BLACK;
                    print8(omDBGMenuItemTbl[i].x + 1, omDBGMenuItemTbl[i].y + 1, buf);
                    fontcolor = omDBGMenuItemTbl[i].color;
                    print8(omDBGMenuItemTbl[i].x, omDBGMenuItemTbl[i].y, buf);
                }
            }
            sprintf(omDBGStrBuf, ">");
            fontcolor = FONT_COLOR_TRANSLUCENT_GRAY;
            print8(omDBGMenuItemTbl[object->work[2]].x + 1, omDBGMenuItemTbl[object->work[2]].y + 1, omDBGStrBuf);
            fontcolor = FONT_COLOR_WHITE;
            print8(omDBGMenuItemTbl[object->work[2]].x, omDBGMenuItemTbl[object->work[2]].y, omDBGStrBuf);

            if (omPadBtnDown[port] & D_JPAD) {
                HuAudFXPlay(0);
                do {
                    if (++object->work[2] >= 6) {
                        object->work[2] = 0;
                    }
                } while (omDBGMenuItemTbl[object->work[2]].disabled == 1);
            } else if (omPadBtnDown[port] & U_JPAD) {
                HuAudFXPlay(0);
                do {
                    if ((s8)--object->work[2] < 0) {
                        object->work[2] = 5;
                    }
                } while (omDBGMenuItemTbl[object->work[2]].disabled == 1);
            } else if (omPadBtnDown[port] & U_CBUTTONS) {
                object->work[0] ^= 8;
                if (object->work[0] & 8) {
                    saftyFrameFlashSet(1, 1, -1, 0x60, 0x80, 0xFF, 0, 0, 100);
                } else {
                    saftyFrameFlashReset();
                    saftyFrameData.unk_00 = saftyFrameData.unk_01 = 0;
                    saftyFrameData.unk_02 = 0x90;
                }
            } else if (omPadBtnDown[port] & D_CBUTTONS) {
                object->work[0] ^= 0x20;
                if (object->work[0] & 0x20) {
                    saftyFrameData.unk_01 = 0xFF;
                } else {
                    saftyFrameData.unk_01 = 0;
                }
            } else if (omPadBtnDown[port] & L_CBUTTONS) {
                object->work[0] ^= 0x10;
                if (object->work[0] & 0x10) {
                    saftyFrameData.unk_00 = 0xFF;
                } else {
                    saftyFrameData.unk_00 = 0;
                }
            } else if (omPadBtnDown[port] & R_CBUTTONS) {
                object->work[0] ^= 0x40;
                if (object->work[0] & 0x40) {
                    saftyFrameData.unk_02 = 0xFF;
                } else {
                    saftyFrameData.unk_02 = 0;
                }
            } else if (omPadBtnDown[port] & A_BUTTON) {
                omPadBtnDown[port] = 0;
                HuAudFXPlay(0);
                switch (object->work[2]) {
                    case 0: // CANCEL
                        omPadBtnDown[port] |= L_TRIG;
                        break;
                    case 1: // RESET
                        omSysExitReq = 1;
                        omPadBtnDown[port] |= L_TRIG;
                        if (omDBGSysKeyObj->work[0] & 1) {
                            omDBGSysKeyObj->work[0] &= ~1;
                            if (omPauseWinInitF == 1) {
                                HuWinAllKill();
                            }
                        }
                        break;
                    case 2: // LIGHT
                        pfWinClose();
                        omdispinfo = 0;
                        omDBGInfoWin = -1;
                        saftyFrameReset();
                        object->work[0] |= 4;
                        LightDebugCreate();
                        break;
                    case 3: // INFO
                        if ((omdispinfo ^= 1) == 0) {
                            pfWinKill(omDBGInfoWin);
                            omDBGInfoWin = -1;
                        }
                        break;
                    case 4: // MUSSTP
                        if ((HuAudMusEnableF ^= 1) == 0) {
                            HuAudSeqStop();
                        }
                        break;
                    case 5: // SE STP
                        if ((HuAudSeEnableF ^= 1) == 0) {
                            HuAudFXAllStop();
                        }
                        break;
                }
            }
        }

        if (omPadBtnDown[port] & L_TRIG) {
            close = 1;
        }
        if (omOvlChangeF == 1) {
            close = 1;
        }
        if (close == 1) {
            object->work[0] &= ~1;
            if (!(omDBGSysKeyObj->work[0] & 1)) {
                Hu3DPauseF = omDBGHu3DPauseFBak;
                for (i = 0; i < ommaxobjs; i++) {
                    if (!(omobjall[i].stat & (OM_STAT_DELETED | OM_STAT_NOPAUSE))) {
                        omResetStatBit(&omobjall[i], OM_STAT_PAUSED);
                    }
                }
                for (i = 0; i < omPrcMax; i++) {
                    if (!(omPrcData[i].stat & (OM_STAT_DELETED | OM_STAT_NOPAUSE))) {
                        omPrcResetStatBit(omPrcData[i].processInstance, OM_STAT_PAUSED);
                        if (!(omPrcData[i].stat & OM_STAT_ALLPAUSED)) {
                            omPrcData[i].processInstance->stat &= ~PROCESS_STAT_PAUSE;
                        }
                    }
                }
                msmMusResume(HuAudMusNo, 0);
                if (omPauseSubMusF == 1) {
                    msmMusResume(1, 0);
                    omPauseSubMusF = 0;
                }
                HuAudFXAllVolRestore();
                if (HuAudStat & 8) {
                    HuAudStat &= ~8;
                }
                for (i = 0; i < 4; i++) {
                    if (CheckControllerRead(i)) {
                        ResetVibrator(i);
                    }
                }
            }
            if (!(object->work[0] & 4)) {
                pfWinKill(omDBGPauseWin0);
                pfWinKill(omDBGPauseWin1);
            }
            object->work[0] &= ~4;
            saftyFrameReset();
            LightDebugKill();
        }
        return;
    }

    if (WipeStatGet() == 1 || omOvlChangeF == 1) {
        return;
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        if (!(omPadBtnDown[i] & L_TRIG)) {
            continue;
        }
        if ((omPadBtn[i] | omPadBtnDown[i]) & R_TRIG) {
            continue;
        }
        omDBGHu3DPauseFBak = Hu3DPauseF;
        Hu3DPauseF = 1;
        object->work[0] = 1;
        object->work[1] = i;
        for (i = 0; i < ommaxobjs; i++) {
            if (!(omobjall[i].stat & (OM_STAT_DELETED | OM_STAT_NOPAUSE))) {
                omSetStatBit(&omobjall[i], OM_STAT_PAUSED);
            }
        }
        for (i = 0; i < omPrcMax; i++) {
            if (!(omPrcData[i].stat & (OM_STAT_DELETED | OM_STAT_NOPAUSE))) {
                omPrcSetStatBit(omPrcData[i].processInstance, OM_STAT_PAUSED);
                omPrcData[i].processInstance->stat |= PROCESS_STAT_PAUSE;
            }
        }
        omDBGPauseWin0 = printWin(120, 96, 208, 168, 0x40FF);
        omDBGPauseWin1 = printWin(116, 92, 204, 164, 0x90FF);
        saftyFrameSet(0, 0, 0x90);
        msmMusPause(HuAudMusNo);
        if (msmMusGetStatus(1) == 4) {
            msmMusPause(1);
            omPauseSubMusF = 1;
        }
        HuAudFXAllVolFadeDown(4);
        for (i = 0; i < 4; i++) {
            if (CheckControllerRead(i)) {
                ResetVibrator(i);
            }
        }
        return;
    }
}

// Watches for the pause button and pauses/resumes the game.
void omSystemKeyCheck(omObjData *object) {
    s32 i;
    s32 j;
    u8 minigameType;

    if (omSysPauseDisableF != 0) {
        return;
    }

    if (object->work[0] & 1) {
        if (omSysPauseReadyF == 0) {
            return;
        }
        if ((omPadBtnDown[OM_GET_WORK_PTR(object, PauseObjWork)->halfwords[3]] & START_BUTTON) ||
            omOvlChangeF == 1 || omSysPauseCloseReq == 1) {
            omSysPauseCloseReq = 0;
            Hu3DPauseF = 0;
            object->work[0] &= ~1;
            for (i = 0; i < ommaxobjs; i++) {
                if (!(omobjall[i].stat & (OM_STAT_DELETED | OM_STAT_NOPAUSE))) {
                    omResetStatBit(&omobjall[i], OM_STAT_PAUSED);
                }
            }
            for (i = 0; i < omPrcMax; i++) {
                if (!(omPrcData[i].stat & (OM_STAT_DELETED | OM_STAT_NOPAUSE))) {
                    omPrcResetStatBit(omPrcData[i].processInstance, OM_STAT_PAUSED);
                    if (!(omPrcData[i].stat & OM_STAT_ALLPAUSED)) {
                        omPrcData[i].processInstance->stat &= ~PROCESS_STAT_PAUSE;
                    }
                }
            }
            if (_CheckFlag(FLAG_MG_PRACTICE)) {
                espDispOn(omPracticeSpr);
            }
            for (i = 0; i < 4; i++) {
                if (CheckControllerRead(i)) {
                    ResetVibrator(i);
                }
            }
            if (omPauseWinInitF == 1) {
                HuWinAllKill();
            }
            GamePauseEnd();
            msmMusResume(HuAudMusNo, 0);
            if (omPauseSubMusF == 1) {
                msmMusResume(1, 0);
                omPauseSubMusF = 0;
            }
            HuAudFXAllVolRestore();
            if (HuAudStat & 8) {
                HuAudStat &= ~8;
            }
        }
        return;
    }

    for (j = 0; j < 4; j++) {
        if (CheckControllerRead(GwPlayer[j].pad) && _CheckFlag(FLAG_MG_PRACTICE) && omMgActiveF == 1 &&
            (omPadBtnDown[GwPlayer[j].pad] & R_TRIG)) {
            omSysExitReq = 1;
            return;
        }
    }

    if (WipeStatGet() == 1 || omSysExitReq == 1 || omOvlChangeF == 1 || !(omovlstat & OM_OVL_STAT_MG)) {
        return;
    }

    for (j = 0; j < 4; j++) {
        if (!CheckControllerRead(GwPlayer[j].pad)) {
            continue;
        }
        minigameType = mgDataTbl[GwSystem.minigame_index - 1].minigameType;
        if (minigameType == 7) {
            if (j != 0) {
                continue;
            }
        } else if (GwPlayer[j].group >= omPracticeGroupTbl[minigameType]) {
            continue;
        }
        if (!(omPadBtnDown[GwPlayer[j].pad] & START_BUTTON)) {
            continue;
        }
        omSysPauseReadyF = 0;
        omSysPauseCloseReq = 0;
        Hu3DPauseF = 1;
        object->work[0] = 1;
        object->work[1] = GwPlayer[j].pad;
        for (i = 0; i < ommaxobjs; i++) {
            if (!(omobjall[i].stat & (OM_STAT_DELETED | OM_STAT_NOPAUSE))) {
                omSetStatBit(&omobjall[i], OM_STAT_PAUSED);
            }
        }
        for (i = 0; i < omPrcMax; i++) {
            if (!(omPrcData[i].stat & (OM_STAT_DELETED | OM_STAT_NOPAUSE))) {
                omPrcSetStatBit(omPrcData[i].processInstance, OM_STAT_PAUSED);
                omPrcData[i].processInstance->stat |= PROCESS_STAT_PAUSE;
            }
        }
        if (winInitF != 1) {
            HuWinInit();
            omPauseWinInitF = 1;
        } else {
            omPauseWinInitF = 0;
        }
        GameMesPauseCreate();
        if (_CheckFlag(FLAG_MG_PRACTICE)) {
            espDispOff(omPracticeSpr);
        }
        msmMusPause(HuAudMusNo);
        if (msmMusGetStatus(1) == 4) {
            msmMusPause(1);
            omPauseSubMusF = 1;
        }
        HuAudFXAllVolFadeDown(4);
        for (i = 0; i < 4; i++) {
            if (CheckControllerRead(i)) {
                ResetVibrator(i);
            }
        }
        return;
    }
}

u16 omPauseChk(void) {
    return omDBGSysKeyObj != NULL ? (OM_GET_WORK_PTR(omDBGSysKeyObj, PauseObjWork)->halfwords[1] & 1) : 0;
}

// Pauses all objects and processes.
s32 omAllPause(void) {
    s32 i;

    if (WipeStatGet() == 1 || omOvlChangeF == 1) {
        return 0;
    }
    omAllPauseF = 1;
    for (i = 0; i < ommaxobjs; i++) {
        if (!(omobjall[i].stat & (OM_STAT_DELETED | OM_STAT_NOALLPAUSE))) {
            omSetStatBit(&omobjall[i], OM_STAT_ALLPAUSED);
        }
    }
    for (i = 0; i < omPrcMax; i++) {
        if (!(omPrcData[i].stat & (OM_STAT_DELETED | OM_STAT_NOALLPAUSE))) {
            omPrcSetStatBit(omPrcData[i].processInstance, OM_STAT_ALLPAUSED);
            omPrcData[i].processInstance->stat |= PROCESS_STAT_PAUSE;
        }
    }
    return 1;
}

// Resumes all objects and processes.
void omAllUPause(void) {
    s32 i;

    omAllPauseF = 0;
    for (i = 0; i < ommaxobjs; i++) {
        if (!(omobjall[i].stat & (OM_STAT_DELETED | OM_STAT_NOALLPAUSE))) {
            omResetStatBit(&omobjall[i], OM_STAT_ALLPAUSED);
        }
    }
    for (i = 0; i < omPrcMax; i++) {
        if (!(omPrcData[i].stat & (OM_STAT_DELETED | OM_STAT_NOALLPAUSE))) {
            omPrcResetStatBit(omPrcData[i].processInstance, OM_STAT_ALLPAUSED);
            if (!(omPrcData[i].stat & OM_STAT_PAUSED)) {
                omPrcData[i].processInstance->stat &= ~PROCESS_STAT_PAUSE;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        ResetVibrator(i);
    }
}

void omGameSysInit(void) {
    MgCoinReset();
    if (omovlstat & OM_OVL_STAT_SYSKEY) {
        omSystemKeyCheckSetup();
        if (omovlstat & OM_OVL_STAT_MG) {
            omSysPauseDisableF = 1;
        }
    }
    if (omovlstat & OM_OVL_STAT_TIMER) {
        omSysTimerCreate();
    }
    HuAudFadeObjCreate();
    if (_CheckFlag(FLAG_MG_PRACTICE) != 0) {
        omPracticeSprAnim = HuSprAnimDataRead(0x94);
        omPracticeSpr = espEntry(omPracticeSprAnim, 0, 1);
        espTPLvlSet(omPracticeSpr, 0x100);
        espPriSet(omPracticeSpr, 1);
        omPracticeSprPosNo = omPracticeSprPosIdx[GwSystem.minigame_index - 1];
        espPosSet(omPracticeSpr, omPracticeSprPosTbl[omPracticeSprPosNo][0], omPracticeSprPosTbl[omPracticeSprPosNo][1]);
        omPracticeSprAngle = 0;
        omSetStatBit(omAddObj(10, 0, 0, -1, omPracticeSprExec), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    }
}

void omPracticeSprExec(omObjData *arg0) {
    omPracticeSprAngle += 10;
    if (omPracticeSprAngle > 180) {
        omPracticeSprAngle -= 180;
    }
    espTPLvlSet(omPracticeSpr, sindf(omPracticeSprAngle) * 255.0f);
    espPosSet(omPracticeSpr, omPracticeSprPosTbl[omPracticeSprPosNo][0], omPracticeSprPosTbl[omPracticeSprPosNo][1]);
    if (omMgActiveF == 1) {
        espDispOn(omPracticeSpr);
    } else {
        espDispOff(omPracticeSpr);
    }
}

void omHu3DLayerNumSet(s32 arg0) {
    omHu3DReinitF = 1;
    omHu3DReinitWait = 4;
    omHu3DBufNum = arg0;
}

void omHu3DParamSet(u16 arg0, u16 arg1, u16 arg2) {
    omHu3DVtxNum = arg0;
    omHu3DGfxNum = arg1;
    omHu3DMtxNum = arg2;
    omHu3DReinitF = 1;
    omHu3DReinitWait = 4;
}

void omModeOvlLoad(void) {
    s16 ovlIndex;

    if (omovlstat & (OM_OVL_STAT_MGLIB | OM_OVL_STAT_MG)) {
        ovlIndex = minigame;
    } else if (omovlstat & OM_OVL_STAT_BOARD) {
        ovlIndex = shared_board;
    } else if (omovlstat & OM_OVL_STAT_DUEL) {
        ovlIndex = name_81;
    } else {
        return;
    }
    if (ovlIndex == omModeOvlPrev) {
        OvlModeLoad(ovlIndex, 6);
    } else {
        OvlModeLoad(ovlIndex, 7);
    }
    omModeOvlPrev = ovlIndex;
}
