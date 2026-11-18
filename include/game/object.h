#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "ultra64.h"
#include "humath.h"
#include "game/process.h"

#define OM_STAT_DELETED (1 << 0)
#define OM_STAT_DISABLED (1 << 1)
#define OM_STAT_ACTIVE (1 << 2)
#define OM_STAT_FUNCOFF (1 << 3) // object func is not called
#define OM_STAT_PAUSED (1 << 4)
#define OM_STAT_NOPAUSE (1 << 5)
#define OM_STAT_ALLPAUSED (1 << 6) // set by omAllPause
#define OM_STAT_NOALLPAUSE (1 << 7) // excluded from omAllPause
#define OM_STAT_MODELPAUSE (1 << 8)

// Overlay stat flags, passed to omOvlCallEx / omOvlGotoEx and stored in omovlstat.
#define OM_OVL_STAT_NONE 0
#define OM_OVL_STAT_MGLIB (1 << 0) // load the minigame common library
#define OM_OVL_STAT_BOARD (1 << 1) // party board: shared board library, board audio fx
#define OM_OVL_STAT_MG (1 << 2) // minigame: minigame library, minigame audio fx, practice exit, no system pause
#define OM_OVL_STAT_SYSKEY (1 << 4) // create the system key check (pause/reset) object
#define OM_OVL_STAT_TIMER (1 << 5) // create the system timer object
#define OM_OVL_STAT_GFXBUF2 (1 << 6) // use 2 graphics buffers
#define OM_OVL_STAT_GFXBUF3 (1 << 7) // use 3 graphics buffers
#define OM_OVL_STAT_AUDFX1 (1 << 8) // audio fx type override
#define OM_OVL_STAT_AUDFX2 (1 << 9)
#define OM_OVL_STAT_AUDFX3 (1 << 10)
#define OM_OVL_STAT_AUDFX4 (1 << 11)
#define OM_OVL_STAT_AUDFX5 (1 << 12)
#define OM_OVL_STAT_AUDFXKEEP (1 << 13) // leave the audio fx settings unchanged
#define OM_OVL_STAT_DUEL (1 << 14) // duel board: duel common library

#define OM_GET_WORK_PTR(object, type) ((type *)(&((object)->work[0])))
#define OM_GET_DATA_PTR(object, type) ((type *)(((object)->data)))

struct om_obj_data;
struct CameraViewData;
typedef void (*omObjFunc)(struct om_obj_data *);

typedef struct om_obj_data {
/* 0x00 */ u16 stat;
/* 0x02 */ s16 next_idx_alloc;
/* 0x04 */ s16 prio;
/* 0x06 */ s16 prev;
/* 0x08 */ s16 next;
/* 0x0A */ s16 next_idx;
/* 0x0C */ s16 group;
/* 0x0E */ u16 group_idx;
/* 0x10 */ u32 mode;
/* 0x14 */ omObjFunc func;
/* 0x18 */ Vec trans;
/* 0x24 */ Vec rot;
/* 0x30 */ Vec scale;
/* 0x3C */ u16 mdlcnt;
/* 0x40 */ s16* model;
/* 0x44 */ u16 mtncnt;
/* 0x48 */ s16* motion;
/* 0x4C */ u32 work[4];
/* 0x5C */ void* data;
} omObjData;

typedef struct {
    /* 0x00 */ s16 chr;
    /* 0x04 */ s32 model;
    /* 0x08 */ s32 motion[3];
    /* 0x14 */ f32 scale;
} omCharModelData; // Size 0x18

typedef struct {
    u16 next_idx;
    u16 max_objs;
    u16 num_objs;
    u16 *next;
    omObjData **objs;
} omObjGroup;

// Model object managed by the board (ovl_80) or duel (ovl_81) overlay. The two
// overlays have different layouts, so the definition comes from either
// common_board.h or common_duel.h.
typedef struct Object_s Object;

typedef struct omOvlHisData { //Object Manager History Data
/* 0x00 */ s32 overlayID;
/* 0x04 */ s16 event;
/* 0x06 */ s16 stat;
} omOvlHisData; //sizeof 0x08

typedef struct UnkomOvl {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06; // unused pad?
} UnkomOvl;

#ifndef NO_EXTERN_VARIABLES
extern UnkomOvl omOvlHu3DParamTbl[128]; // per-overlay arguments for omHu3DParamSet

extern s16 omovlevtno;
extern s32 omprevovl;
extern u8 omDBGPlayMode;
extern u16 omovlstat;
extern s16 omovlhisidx;
extern omOvlHisData omovlhis[12];
extern u16 omdispinfo;
extern s16 omDBGInfoWin;
extern omObjData *omSysTimerObj;
#endif

void omInitObjMan(s16 numOfObjs, s32 numOfPrcs);
void omSetStatBit(omObjData *obj, u16 stat);
s32 omOvlReturnEx(s16 level);
omObjData* omAddObj(s16 prio, u16 mdlcnt, u16 mtncnt, s16 group, omObjFunc func);
Process* omAddPrcObj(process_func func, u16 priority, s32 stackSize, s32 extDataSize);
s32 omDelPrcObj(Process*);
s32 omOvlCallEx(s32 ovlID, s16 event, u16 stat);
void omMain(void);
u16 omPauseChk(void);
void omGameSysInit(void);
void omPrcSetStatBit(Process* prc, s32 stat);
void omOvlGotoEx(s32 ovlID, s16 event, u16 stat);
void omOvlHisChg(s16 level, s32 overlay, s16 event, u16 stat);
void omOvlKill(void);
void omDestroyObjMan(void);
void omPrcSetDestructor(Process* prc, void* destructor);
void omPrcResetStatBit(Process* prc, s32 stat);
void omSetTra(omObjData* obj, f32 x, f32 y, f32 z);
void omSetRot(omObjData* obj, f32 x, f32 y, f32 z);
void omSetSca(omObjData* obj, f32 x, f32 y, f32 z);
void omDelObj(omObjData*);

void omOutView(omObjData* object);
void omOutViewMulti(omObjData* object);
void omCameraViewCreate(s32 priority, s16 spriteGroup, void (*draw)(struct CameraViewData *), f32 fov, Vec *pos, Vec *at);

#ifndef NO_EXTERN_VARIABLES
extern f32 CZoomM[];
extern f32 CZoom;
extern Vec CRot;
extern Vec CenterM[];
extern Vec Center;
extern Vec CRotM[];
extern omCharModelData omCharModelTbl[];
#endif

void omSetObjPrio(omObjData *obj, s16 prio);
void omInsertObj(omObjData *obj);
void omSetStat(omObjData *obj, u16 stat);
void omResetStatBit(omObjData *obj, u16 stat);
void omPrcSetStat(Process *prc, s32 stat);
void omMakeGroup(u16 group, u16 max_objs);
void omAddMember(u16 group, omObjData *obj);
void omDelMember(omObjData *obj);
omObjData **omGetGroupMemberList(s16 arg0);
omObjData *omGetGroupMember(s16 arg0, u16 arg1);
void omGroupModeSet(s16 group, u32 stat);
void omGroupMemberModeSet(s16 group, u16 idx, s32 flags);
void omObjModeSet(omObjData *obj, s32 arg1);
Process *omAddChildPrcObj(process_func func, s32 priority, s32 stack_size, s32 extra_data_size, Process *parent);
void omDestroyPrcObj(void);
void omSystemKeyCheckSetup(void);
void omDBGSystemKeyCheck(omObjData *object);
void omSystemKeyCheck(omObjData *object);
s32 omAllPause(void);
void omAllUPause(void);
void omPracticeSprExec(omObjData *arg0);
void omHu3DLayerNumSet(s32 arg0);
void omHu3DParamSet(u16 arg0, u16 arg1, u16 arg2);
void omModeOvlLoad(void);
void omCameraViewGfxSetup(void);
void omCameraViewExec(omObjData *object);
void omCameraViewMultiExec(omObjData *object);
void omCameraPosGet(Vec *out, Vec *normal);
void omCameraLookAtToRot(Vec *pos, Vec *at, f32 *zoom, Vec *rot, Vec *center);
void omSysTimerCreate(void);
void omSysTimerExec(omObjData *object);
void HuAudFadeObjCreate(void);
void HuAudFadeObjExec(omObjData *object);

#endif //_GAME_OBJECT_H
