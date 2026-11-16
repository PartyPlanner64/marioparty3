#ifndef OPENING_H
#define OPENING_H

#include "ultra64.h"
#include "humath.h"
#include "game/object.h"
#include "game/camera.h"
#include "game/hu3d.h"

typedef struct {
    /* 0x00 */ s16 modelId;
    /* 0x02 */ s16 motionId;
    /* 0x04 */ s32 posX;
    /* 0x08 */ s32 posY;
    /* 0x0C */ s32 posZ;
    /* 0x10 */ f32 scaleX;
    /* 0x14 */ f32 scaleY;
    /* 0x18 */ f32 scaleZ;
    /* 0x1C */ f32 rotX;
    /* 0x20 */ f32 rotY;
    /* 0x24 */ f32 rotZ;
    /* 0x28 */ s32 unk_28;
} OpModel;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ RGBA color;
    /* 0x10 */ s16 effectId;
    /* 0x12 */ char unk_12[0x1A];
    /* 0x2C */ Vec unk_2C;
    /* 0x38 */ s32 unk_38;
} OpObj; // sizeof 0x3C

typedef struct {
    /* 0x00 */ s16 espriteSlot;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19[3];
} OpSpr; // sizeof 0x1C

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec at;
    /* 0x18 */ Vec up;
    /* 0x24 */ omObjData *obj;
} OpCamVecs; // sizeof 0x28

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ f32 magnitude;
    /* 0x08 */ s32 frame;
    /* 0x0C */ s32 totalFrames;
    /* 0x10 */ s32 active;
} OpShake; // sizeof 0x14

typedef struct {
    /* 0x00 */ s16 animId;
    /* 0x02 */ u16 espriteSlot;
} OpContError; // sizeof 0x4

typedef struct {
    /* 0x00 */ s16 animId;
} OpAnimSlot; // sizeof 0x2

// View of an OpObj slot from offset 0x0C, as used by the demo model objects.
// The word at 0x0C doubles as OpObj's color for the wipe effects.
typedef struct {
    /* 0x00 */ s32 modelId;
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec unk_1C;
    /* 0x1C */ Vec unk_28;
    /* 0x28 */ char unk_34[0x14];
} OpWork; // sizeof 0x3C

typedef union {
    s16 effectId;
    Vec pos;
    s32 motion[3];
} OpObjPos;

typedef struct {
    /* 0x00 */ s16 espriteSlot;
    /* 0x04 */ void *event;
    /* 0x08 */ s32 unk_08;
} OpSlot; // sizeof 0xC

#ifndef NO_EXTERN_VARIABLES
extern Vec op_effPos;
extern s32 op_effNum;
extern Process *op_mainProc;
extern s32 op_demoEndF;
extern OpModel op_modelTbl[0xA0];
extern OpCamVecs op_cameraWork;
extern OpShake op_cameraShake;
extern OpObj op_demoObjTbl[0x10];
extern s16 op_bgAnim;
extern u16 op_bgSpr;
extern OpSlot op_winTbl[0x20];
extern OpSpr op_sprTbl[0x40];
extern OpAnimSlot op_animTbl[0x40];
extern OpContError op_contError;
extern s32 op_demoObjTime[0x10][15];
extern s32 op_demoObjMaxTime[0x10][15];
extern OpWork op_demoObjWork[0x10];
extern OpObjPos op_demoObjParamA[0x10][5];
extern OpObjPos op_demoObjParamB[0x10][5];
extern f32 op_demoObjEndX[0x10][15];
extern f32 op_demoObjEndY[0x10][15];
extern OpObjPos op_demoObjAngleX[0x10][5];
extern f32 op_demoObjAngleY[0x10][15];
extern f32 op_demoObjAngleZ[0x10][15];

extern HmfMotionNode *op_demoObjBodyNode[0x10][15];
extern HmfMotionNode *op_demoObjShadowNode[0x10][15];
#endif

s16 op_SpiralEffCreate(s32 arg0, s32 arg1);
s32 op_SparkEffCreate(s32 resourceId, s32 arg1);
s32 op_SparkEffAdd(s16 modelId, f32 x, f32 y, f32 z, f32 size);
void op_DemoOutEffMain(omObjData *obj);
void op_DemoGuideInEffMain(omObjData *obj);
void op_DemoEndReset(void);
void op_WinCreate(s32 slot, u32 event, s16 x, s16 y, s16 width, s16 height, s16 style);
void op_ObjectInit(void);
void op_TitleCreate(void);
void op_DemoCreate(void);
void op_CameraShakeKill(void);
void op_DemoModelKill(void);
void op_DemoSprKill(void);
void op_WinKill(s32 index);
void op_DemoMotIntervalMain(omObjData *obj);
void op_DemoStarWaitMain(omObjData *obj);
void op_DemoEventSetup(void);
void op_DemoEventKill(void);
void op_TitleSetup(void);
void op_TitleKill(void);
s32 op_BtnStartCheck(void);
s32 op_DemoEndGet(void);

void op_TitleMain(void);
void op_DemoMain(void);
void op_TitleSprMain(void);
void op_DemoEvent(void);
void op_UtilInit(void);
void op_SprInit(void);
void op_ModelInit(void);
void op_WinInit(void);
void op_SprPosSet(s32 slot, s32 x, s32 y);
void op_ModelRotSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void op_MotionSet(s32 modelId, s32 motionId, s16 arg2);
void op_CameraShakeInit(void);
void op_CameraShakeObjMain(omObjData *);
void op_CameraInit(void);
void op_CameraObjKill(void);
void op_CameraObjMain(omObjData *);
void op_DemoObjInit(void);
void op_ContErrorCreate(void);
void MBCameraOffsetSet(s16 arg0, s16 arg1);
void op_DemoFlyAwayMain(omObjData *);
void op_DemoFlyMain(omObjData *);
void op_DemoJumpMain(omObjData *);
void op_DemoObjKill(s32 index);
void op_DemoObjKillAll(void);
void op_ContErrorKill(void);
void op_ContErrorDispOn(void);
void op_ContErrorDispOff(void);
void op_WipeKill(s32 index);
void op_SpiralEffHook(s16 modelId);
void op_SparkEffHook(s16 modelId);

#endif
