#ifndef _STAFF_H
#define _STAFF_H

#include "common.h"
#include "game/aura.h"
#include "game/gamemes.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "gcc/memory.h"
#include "overlays/msetup.h"
#include "../ovl_81_name/ovl_81.h"

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

void func_801059A0_staff(void);
void func_80105BD4_staff(omObjData *object);
void func_80105CB4_staff(omObjData *object);
void func_80105DB8_staff(MsetupModelEntry *entry, s16 model);
void func_80105E6C_staff(MsetupModelEntry *entry, MsetupModelHandle *handle, s32 count);
u32 func_80105F48_staff(u32 seed);
u32 func_8010601C_staff(void);
s32 func_80106044_staff(u32 limit);
void func_8010609C_staff(MsetupCameraPreset *preset);
void func_8010615C_staff(void);
void func_80106720_staff(void);
void func_8010674C_staff(MsetupCameraKeyframe *keys, f32 speed, void (*callback)(s16, s16, s16));
void func_80106C50_staff(void);
void func_80106E20_staff(void);
void func_801073EC_staff(UnkStaff_2 *arg0, s32 arg1);
void func_80107508_staff(void);
UnkStaff_7 *func_80107740_staff(void);
void func_80107A9C_staff(UnkStaff_7 *arg0);
void func_80107B1C_staff(UnkStaff_7 *arg0, f32 arg1);
void func_80107BA0_staff(UnkStaff_7 *arg0);
void func_80107DBC_staff(UnkStaff_7 *arg0);
void func_80107EB8_staff(void);
StaffPath *func_801085F0_staff(Vec *points, s32 flags);
void func_801088F4_staff(StaffPath *path, f32 t, Vec *out);
void func_8010919C_staff(StaffPath *path);
void func_801091CC_staff(Vec *out, Vec *center, f32 angle);
void func_80109264_staff(void);
void func_801095E4_staff(void);
void func_8010992C_staff(Process *prc, s16 modelId);
s16 func_8010998C_staff(Process *prc, s16 *model, s16 *motion, Vec *pos);
void func_80109D08_staff(Process *prc, s16 modelId, Vec *pos);
StaffModelEntry *func_80109D74_staff(UnkStaff_3 *work, StaffModelEntry *entry);
StaffModelEntry *func_80109F34_staff(UnkStaff_3 *work, StaffModelEntry *entry);
void func_8010A848_staff(void);
void func_8010B1E0_staff(void);
void func_8010B430_staff(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_8010B4B4_staff(s16 arg0, s16 arg1, s16 arg2);
void func_8010B514_staff(s16 arg0, s16 arg1);
void func_8010B794_staff(s16 arg0);
void func_8010B8C0_staff(s16 arg0, s16 arg1, s16 visible);
void func_8010B9BC_staff(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_8010BA30_staff(s16 arg0, s16 arg1, u32 arg2, s16 arg3, s16 arg4);
void func_8010BE20_staff(s16 *windows, s16 count);
void func_8010BF84_staff(void);
void func_8010C680_staff(s16 *state, f32 *angle, f32 *rotY, UnkStaff *work);
void func_8010C8F4_staff(UnkStaff_1 *);
void func_8010CD74_staff(UnkStaff_1 *);
void func_8010CFD4_staff(UnkStaff *);
void func_8010D1E8_staff(void);
void func_8010D450_staff(s16 model, Vec *pos);
void func_8010D580_staff(s16 model, s16 shadow, Vec *start);
void func_8010D998_staff(void);
UnkStaff_2 *func_8010DE50_staff(s32 arg0);
void func_8010DEDC_staff(s32 *arg0, s32 arg1);
void func_8010DEE4_staff(UnkStaff_2 *arg0, f32 x, f32 y, f32 z);
void func_8010DEF4_staff(UnkStaff_2 *arg0, f32 x, f32 y, f32 z);
void func_8010DF04_staff(UnkStaff_2 *arg0, s16 arg1);
void func_8010DF0C_staff(UnkStaff_2 *arg0, s32 mask, s32 value);
s16 func_8010DF24_staff(UnkStaff_2 *arg0);
void func_8010DF2C_staff(UnkStaff_2 *arg0, s16 arg1);
void func_8010DF34_staff(void);
void func_8010F04C_staff(s16 model, s32 dataNum);
HmfModelData_UnkBC_Unk58_Struct *func_8010F3E4_staff(s16 model, f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz, u8 r, u8 g, u8 b);
void func_8010F4C4_staff(s16 model);
void func_8010F9D4_staff(s16 model);
void func_8010FB28_staff(void);
void func_8010FB88_staff(void);

extern u16 D_80110530_staff;
extern f32 D_80110534_staff;
extern s8 D_80110538_staff;
extern u32 D_8011053C_staff;
extern s32 D_80110540_staff[6];
extern MsetupCameraPreset D_80110560_staff;
extern s32 D_8011058C_staff[4];
extern s16 D_801105B8_staff[4];
extern u16 D_801105C0_staff[4];
extern StaffPos2s D_801105C8_staff[3];
extern s32 D_801105D4_staff[3];
extern s32 D_801105E0_staff[4];
extern s32 D_801105F0_staff[2];
extern Vec D_801105F8_staff[2];
extern f32 D_80110610_staff[2];
extern Vec D_80110618_staff[];
extern Vec D_80110648_staff[];
extern s16 D_8011066C_staff[4];
extern StaffAnimEntry D_80110674_staff[];
extern StaffModelEntry D_80110704_staff[];
extern u8 D_8011059C_staff[4];
extern u16 D_801105A0_staff[4];
extern f32 D_801105A8_staff[4];
extern MsetupModelEntry D_80110FF4_staff[];
extern Vec D_80110FA0_staff[3];
extern Vec D_80110FDC_staff;
extern s32 D_80110FE8_staff[3];
extern StaffDecoEntry D_80111094_staff[];
extern s16 D_80111510_staff;
extern s16 D_80111512_staff;
extern s16 D_80111514_staff;
extern s16 D_80111516_staff;
extern MsetupPlayerConfig D_80111518_staff;
extern s16 D_80111530_staff;
extern s16 D_80111532_staff;
extern s16 D_8011154C_staff;
extern Vec D_80111550_staff;
extern s16 D_8011155C_staff;
extern Vec D_80111534_staff;
extern Vec D_80111540_staff;
extern f32 D_80111560_staff;
extern f32 D_80111564_staff;
extern s16 D_80111490_staff[27];
extern UnkStaff_6 *D_801114C8_staff;
extern s16 D_801114D0_staff[28];
extern UnkStaff_6 *D_80111508_staff;
extern s16 D_8011150C_staff;
extern s16 D_8011150E_staff;
extern f32 D_800D5210_main;
extern f32 D_800CB890_main;

#endif
