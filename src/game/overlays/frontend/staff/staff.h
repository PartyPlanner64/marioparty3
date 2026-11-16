#ifndef _STAFF_H
#define _STAFF_H

#include "common.h"
#include "game/aura.h"
#include "game/gamemes.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "gcc/memory.h"
#include "game/overlays/msetup.h"
#include "game/overlays/duel/common/ovl_81.h"

typedef struct UnkStaff { // sizeof 0x20
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec rot;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} UnkStaff;

typedef struct StaffDecoEntry { // sizeof 0x28
    /* 0x00 */ s32 dataId;
    /* 0x04 */ s32 subDataId;
    /* 0x08 */ s32 animDataId;
    /* 0x0C */ char *animName;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec rot;
} StaffDecoEntry;

typedef struct UnkStaff_9 { // sizeof 0x28
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x14];
    /* 0x20 */ s16 anims[3];
} UnkStaff_9;

typedef struct UnkStaff_1 { // sizeof 0x2C
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec rot;
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ s16 unk_2A;
} UnkStaff_1;

typedef struct UnkStaff_2 { // sizeof 0x4C
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ Vec unk_24;
    /* 0x30 */ Vec center;
    /* 0x3C */ Vec unk_3C;
    /* 0x48 */ f32 unk_48;
} UnkStaff_2;

typedef struct UnkStaff_8 { // sizeof 0x6
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
} UnkStaff_8;

typedef struct StaffModelEntry { // sizeof 0x18
    /* 0x00 */ f32 scale;
    /* 0x04 */ s32 dataId;
    /* 0x08 */ s32 motDataId;
    /* 0x0C */ UnkStaff_8 unk_0C;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 animNo;
} StaffModelEntry;

typedef struct StaffAnimEntry { // sizeof 0x8
    /* 0x00 */ s32 dataNum;
    /* 0x04 */ char *name;
} StaffAnimEntry;

typedef struct UnkStaff_3 { // sizeof 0x3C
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ UnkStaff_8 unk_22;
    /* 0x28 */ s16 unk_28[4];
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ s16 unk_32;
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ s16 unk_3A;
} UnkStaff_3;

typedef struct UnkStaff_4 { // sizeof 0xC
    /* 0x00 */ UnkStaff_3 *unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ char unk_06[2];
    /* 0x08 */ s16 unk_08;
} UnkStaff_4;

typedef struct UnkStaff_5 { // sizeof 0x4C
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ char unk_24[0xC];
    /* 0x30 */ Vec unk_30;
    /* 0x3C */ char unk_3C[0x10];
} UnkStaff_5;

typedef struct UnkStaff_6 { // sizeof 0x8
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} UnkStaff_6;

typedef struct StaffPathSeg { // sizeof 0x8
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
} StaffPathSeg;

typedef struct StaffPath { // sizeof 0x10
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 flags;
    /* 0x04 */ char unk_04[4];
    /* 0x08 */ Vec *points;
    /* 0x0C */ StaffPathSeg *segs;
} StaffPath;

typedef struct StaffPos2s { // sizeof 0x4
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} StaffPos2s;

typedef struct UnkStaff_7 { // sizeof 0x14
    /* 0x00 */ Vec2f *unk_00;
    /* 0x04 */ f32 *unk_04;
    /* 0x08 */ f32 *unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 count;
} UnkStaff_7;

void staff_ObjectSetup(void);
void staff_ExitCheckObjMain(omObjData *object);
void staff_ExitObjMain(omObjData *object);
void staff_ModelEntryPosSet(MsetupModelEntry *entry, s16 model);
void staff_ModelEntryReadAll(MsetupModelEntry *entry, MsetupModelHandle *handle, s32 count);
u32 staff_RandSeedCalc(u32 seed);
u32 staff_Rand(void);
s32 staff_RandMod(u32 limit);
void staff_CameraPresetSet(ModeCameraPreset *preset);
void staff_CameraUpdate(void);
void staff_CameraProc(void);
void staff_CameraKeyframeExec(MsetupCameraKeyframe *keys, f32 speed, void (*callback)(s16, s16, s16));
void staff_PlayerConfigInit(void);
void staff_MainProc(void);
void staff_FireworkRandSet(UnkStaff_2 *arg0, s32 arg1);
void staff_FireworkShowProc(void);
UnkStaff_7 *staff_BackStarCreate(void);
void staff_BackStarKill(UnkStaff_7 *arg0);
void staff_BackStarSpeedSet(UnkStaff_7 *arg0, f32 arg1);
void staff_BackStarMove(UnkStaff_7 *arg0);
void staff_BackStarTwinkle(UnkStaff_7 *arg0);
void staff_BackProc(void);
StaffPath *staff_PathCreate(Vec *points, s32 flags);
void staff_PathPosGet(StaffPath *path, f32 t, Vec *out);
void staff_PathKill(StaffPath *path);
void staff_HostOrbitPosGet(Vec *out, Vec *center, f32 angle);
void staff_HostProc(void);
void staff_StarProc(void);
void staff_CastKillReq(Process *prc, s16 modelId);
s16 staff_CastShow(Process *prc, s16 *model, s16 *motion, Vec *pos);
void staff_CastPosSet(Process *prc, s16 modelId, Vec *pos);
StaffModelEntry *staff_CastCreateAll(UnkStaff_3 *work, StaffModelEntry *entry);
StaffModelEntry *staff_CastNextLoad(UnkStaff_3 *work, StaffModelEntry *entry);
void staff_CastMoveProc(void);
void staff_CastProc(void);
void staff_SprPosAdd(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void staff_SprPosYSet(s16 arg0, s16 arg1, s16 arg2);
void staff_TextLineInit(s16 arg0, s16 arg1);
void staff_TextLineClose(s16 arg0);
void staff_TextLineDispSet(s16 arg0, s16 arg1, s16 visible);
void staff_TextLinePosSet(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void staff_TextLineStrSet(s16 arg0, s16 arg1, u32 arg2, s16 arg3, s16 arg4);
void staff_WinCreateAll(s16 *windows, s16 count);
void staff_CreditRollProc(void);
void staff_FinaleWalkUpdate(s16 *state, f32 *angle, f32 *rotY, UnkStaff *work);
void staff_FinaleStarUpdate(UnkStaff_1 *);
void staff_FinaleStarCreate(UnkStaff_1 *);
void staff_FinaleChrCreate(UnkStaff *);
void staff_FinaleProc(void);
void staff_EndShadowUpdate(s16 model, Vec *pos);
void staff_EndTumbleDropExec(s16 model, s16 shadow, Vec *start);
void staff_EndProc(void);
UnkStaff_2 *staff_FireworkCreate(s32 arg0);
void staff_FireworkSprSet(s32 *arg0, s32 arg1);
void staff_FireworkEndPosSet(UnkStaff_2 *arg0, f32 x, f32 y, f32 z);
void staff_FireworkStartPosSet(UnkStaff_2 *arg0, f32 x, f32 y, f32 z);
void staff_FireworkTimeSet(UnkStaff_2 *arg0, s16 arg1);
void staff_FireworkFlagSet(UnkStaff_2 *arg0, s32 mask, s32 value);
s16 staff_FireworkFlagGet(UnkStaff_2 *arg0);
void staff_FireworkBurstTimeSet(UnkStaff_2 *arg0, s16 arg1);
void staff_FireworkProc(void);
void staff_FireworkShapeSet(s16 model, s32 dataNum);
HmfModelData_UnkBC_Unk58_Struct *staff_ParticleAdd(s16 model, f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz, u8 r, u8 g, u8 b);
void staff_FireworkBurstHook(s16 model);
void staff_FireworkTrailHook(s16 model);
void staff_SpiralCreate(void);
void staff_SpiralProc(void);

extern u16 staff_exitCnt;
extern f32 staff_cameraFov;
extern s8 staff_cameraLookF;

#ifndef NO_EXTERN_VARIABLES
extern s16 staff_padNo;
extern s16 staff_storyF;
extern s16 staff_chrNo;
extern s16 staff_exitOvlNo;
extern MsetupPlayerConfig staff_playerConfig;
extern s16 staff_wipeType;
extern s16 staff_exitEvtNo;
extern s16 staff_wipeTime;
extern Vec staff_cameraRot;
extern s16 staff_exitMode;
extern Vec staff_cameraTarget;
extern Vec staff_cameraPos;
extern f32 staff_cameraFar;
extern f32 staff_cameraNear;
extern s16 staff_roleFontAnimTbl[27];
extern UnkStaff_6 *staff_roleLineTbl;
extern s16 staff_nameFontAnimTbl[28];
extern UnkStaff_6 *staff_nameLineTbl;
extern s16 staff_roleLineNum;
extern s16 staff_nameLineNum;
#endif

extern f32 CFanLen;
extern f32 CFanOfs;

#endif
