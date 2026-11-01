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

#define OM_GET_WORK_PTR(object, type) ((type *)(&((object)->work[0])))
#define OM_GET_DATA_PTR(object, type) ((type *)(((object)->data)))

struct om_obj_data;
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

typedef struct Object_s {
/* 0x00 */ struct Object_s *prev;
/* 0x04 */ struct Object_s *next;
/* 0x08 */ u8 unk8;
/* 0x09 */ s8 unk9;
/* 0x0A */ u16 flags;
/* 0x0C */ Vec coords;
// Three Vec groups (Scale?, Rotation?, Position?)
/* 0x18 */ Vec rot;
/* 0x24 */ Vec scale;
/* 0x30 */ Vec velocity;
/* 0x3C */ omObjData* omObj1;
/* 0x40 */ omObjData* omObj2;
/* 0x44 */ s16 unk44;
/* 0x46 */ s16 unk46;
} Object; //sizeof 0x48

typedef struct omOvlHisData { //Object Manager History Data
/* 0x00 */ s32 overlayID;
/* 0x04 */ s16 event;
/* 0x06 */ s16 stat;
} omOvlHisData; //sizeof 0x08

extern s16 omovlevtno;
extern s16 omovlhisidx;
extern omOvlHisData omovlhis[12];
extern u16 omdispinfo;
extern s16 D_800A1786_main;
extern f32 D_800CE17C_main[];
extern omObjData *D_800CE194_main;

void omInitObjMan(s16 numOfObjs, s32 numOfPrcs);
void omSetStatBit(omObjData *obj, u16 stat);
s32 omOvlReturnEx(s16 level);
omObjData* omAddObj(s16 prio, u16 mdlcnt, u16 mtncnt, s16 group, omObjFunc func);
Process* omAddPrcObj(process_func func, u16 priority, s32 stackSize, s32 extDataSize);
s32 omDelPrcObj(Process*);
s32 omOvlCallEx(s32 ovlID, s16 event, u16 stat);
void omMain(void);
u16 omPauseChk(void);
void func_8004A208_main(void);
void omPrcSetStatBit(Process* prc, s32 stat);
void omOvlGotoEx(s32 ovlID, s16 event, u16 stat);
void omOvlHisChg(s16 level, s32 overlay, s16 event, s16 stat);
void omOvlKill(void);
void omDestroyObjMan(void);
void omPrcSetDestructor(s32, void*);
void omPrcResetStatBit(Process* prc, s32 stat);
void omSetTra(omObjData* obj, f32 x, f32 y, f32 z);
void omSetRot(omObjData* obj, f32 x, f32 y, f32 z);
void omSetSca(omObjData* obj, f32 x, f32 y, f32 z);
void omDelObj(omObjData*);

void omOutView(omObjData* object);
void omOutViewMulti(omObjData* object);

extern f32 CZoomM[];
extern f32 CZoom;
extern Vec CRot;
extern Vec CenterM[];
extern Vec Center;
extern Vec CRotM[];

void omSetObjPrio(omObjData *obj, s16 prio);
void omInsertObj(omObjData *obj);
void omSetStat(omObjData *obj, u16 stat);
void omResetStatBit(omObjData *obj, u16 stat);
void omPrcSetStat(Process *prc, s32 stat);
void omMakeGroup(u16 group, u16 max_objs);
void omAddMember(u16 group, omObjData *obj);
void omDelMember(omObjData *obj);
omObjData **omGetGroupMemberList(s16 arg0);
omObjData *func_80047DD4_main(s16 arg0, u16 arg1);
void func_80047DFC_main(s16 group, u32 stat);
void func_80047E5C_main(s16 group, u16 idx, s32 flags);
void func_80047E90_main(omObjData *obj, s32 arg1);
Process *func_80047F50_main(process_func func, s32 priority, s32 stack_size, s32 extra_data_size, Process *parent);
void omDestroyPrcObj(void);
void omSystemKeyCheckSetup(void);
void func_80048EE8_main(omObjData *object);
void omSystemKeyCheck(omObjData *object);
s32 omAllPause(void);
void omAllUPause(void);
void func_8004A354_main(omObjData *arg0);
void func_8004A444_main(s32 arg0);
void func_8004A468_main(u16 arg0, u16 arg1, u16 arg2);
void func_8004A49C_main(void);
void func_8004BC00_main(void);
void func_8004C4C4_main(omObjData *object);
void func_8004C76C_main(omObjData *object);
void func_8004CB44_main(Vec *out, Vec *normal);
void func_8004CD04_main(Vec *pos, Vec *at, f32 *zoom, Vec *rot, Vec *center);
void func_8004CEA4_main(void);
void func_8004CF00_main(omObjData *object);
void func_8004CF30_main(void);
void func_8004D094_main(omObjData *object);

#endif //_GAME_OBJECT_H
