#ifndef OPENING_H
#define OPENING_H

#include "common.h"

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

extern u8 D_800D20B8_main[16][3];
extern u8 D_800D5570_main[16][3];
extern Gfx D_80114BE8_opening[];
extern u32 D_80114BE0_opening;
extern Vec D_80117378_opening;
extern s32 D_80117384_opening;
extern Vec D_80114BB8_opening;
extern Vec D_80114BC4_opening;
extern RectF D_80114BD0_opening;
extern Process *D_80114EA0_opening;
extern s32 D_80114EA4_opening;
extern OpModel D_80115630_opening[0xA0];
extern OpCamVecs D_80117350_opening;
extern OpShake D_80117338_opening;
extern OpObj D_80117388_opening[0x10];
extern s16 D_801171B0_opening;
extern u16 D_801171B2_opening;
extern OpSlot D_801171B8_opening[0x20];
extern OpSpr D_80114EB0_opening[0x40];
extern OpAnimSlot D_801155B0_opening[0x40];
extern OpContError D_80117750_opening;
extern s32 D_8011738C_opening[0x10][15];
extern s32 D_80117390_opening[0x10][15];
extern OpWork D_80117394_opening[0x10];
extern OpObjPos D_80117398_opening[0x10][5];
extern OpObjPos D_8011739C_opening[0x10][5];
extern f32 D_801173A4_opening[0x10][15];
extern f32 D_801173A8_opening[0x10][15];
extern OpObjPos D_801173B0_opening[0x10][5];
extern f32 D_801173B4_opening[0x10][15];
extern f32 D_801173B8_opening[0x10][15];

extern HmfMotionNode *D_801173BC_opening[0x10][15];
extern HmfMotionNode *D_801173C0_opening[0x10][15];

s16 func_801117D4_opening(s32 arg0, s32 arg1);
s32 func_80111984_opening(s32 resourceId, s32 arg1);
s32 func_80111DDC_opening(s16 modelId, f32 x, f32 y, f32 z, f32 size);
void opDemoOutEffMain(omObjData *obj);
void opDemoGuideInEffMain(omObjData *obj);
void opDemoEndReset(void);
void func_80107140_opening(s32 slot, u32 event, s16 x, s16 y, s16 width, s16 height, s16 style);
void opObjectInit(void);
void opTitleCreate(void);
void opDemoCreate(void);
void func_80110B9C_opening(void);
void opDemoModelKill(void);
void opDemoSprKill(void);
void func_80107A90_opening(s32 index);
void func_80112A74_opening(omObjData *obj);
void opDemoStarWaitMain(omObjData *obj);
void func_80050064_main(s32 arg0);
void opDemoEventSetup(void);
void opDemoEventKill(void);
void opTitleSetup(void);
void opTitleKill(void);
s32 opBtnStartCheck(void);
s32 opDemoEndGet(void);

void opTitleMain(void);
void opDemoMain(void);
void opTitleSprMain(void);
void opDemoEvent(void);
void func_801061F0_opening(void);
void func_8010621C_opening(void);
void func_801067D4_opening(void);
void func_80107A4C_opening(void);
void opSprPosSet(s32 slot, s32 x, s32 y);
void opModelRotSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void opMotionSet(s32 modelId, s32 motionId, s16 arg2);
void func_80110B90_opening(void);
void func_80110C04_opening(omObjData *);
void func_80110F48_opening(void);
void func_80111028_opening(void);
void func_80111090_opening(omObjData *);
void func_80112944_opening(void);
void opContErrorCreate(void);
void MBCameraOffsetSet(s16 arg0, s16 arg1);
void func_8000BBFC_main(u16 arg0, s16 arg1);
void func_8000BC48_main(u16 arg0, u16 arg1);
void func_8000BC88_main(u16 arg0, u16 arg1);
void func_8000BE5C_main(u16 arg0, f32 arg1, f32 arg2);
void func_8000BBD4_main(u16 arg0, s16 arg1, s16 arg2);
void func_8000BD94_main(u16 arg0, s32 arg1, s32 arg2);
void func_80113E8C_opening(omObjData *);
void func_80113AE8_opening(omObjData *);
void func_8011373C_opening(omObjData *);
void opDemoObjKill(s32 index);
void opDemoObjKillAll(void);
void opContErrorKill(void);
void opContErrorDispOn(void);
void opContErrorDispOff(void);
void opWipeKill(s32 index);
void func_80111F58_opening(s16 modelId);
void func_80112120_opening(s16 modelId);
void func_80013390_main(s16 model, s32 arg1, s32 arg2, void (*callback)(s16));

#endif
