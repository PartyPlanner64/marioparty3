#ifndef _PUDDLE_PADDLE_H
#define _PUDDLE_PADDLE_H

#include "common.h"

typedef struct PuddlePaddleSlot { // 0xC bytes
    /* 0x00 */ omObjData *unk_00;
    /* 0x04 */ s16 *unk_04; // model indices
    /* 0x08 */ s16 unk_08;
} PuddlePaddleSlot; // Size 0xC

typedef struct PuddlePaddleFunc {
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ char unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s8 unk_04;
    /* 0x05 */ s8 unk_05;
    /* 0x06 */ char unk_06[2];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s8 unk_0C[16];
    /* 0x1C */ s16 unk_1C[8];
    /* 0x2C */ f32 unk_2C[4];
    /* 0x3C */ void *unk_3C;
    /* 0x40 */ void (*unk_40)();
} PuddlePaddleFunc; // Size 0x44

typedef struct PuddlePaddleOrder {
    /* 0x00 */ u32 priority;
    /* 0x04 */ s16 next;
    /* 0x06 */ s16 previous;
    /* 0x08 */ s16 handler;
    /* 0x0A */ char unk_0A[2];
} PuddlePaddleOrder; // Size 0xC

typedef struct PuddlePaddleFuncGroup { // size = 0x14, eight entries
    /* 0x00 */ PuddlePaddleSlot *unk_00;
    /* 0x04 */ PuddlePaddleFunc *unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char pad0A[2];
    /* 0x0C */ PuddlePaddleOrder *unk_0C;
    /* 0x10 */ s8 unk_10;
    /* 0x11 */ char pad11[3];
} PuddlePaddleFuncGroup;

typedef struct PuddlePaddleSprite { // size = 0x8, twenty entries
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ char pad03[1];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} PuddlePaddleSprite;

typedef struct PuddlePaddleBillboard { // size 0x24, sixteen entries
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ char pad01[3];
    /* 0x04 */ s32 unk_04; // flags
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ char pad0B[1];
    /* 0x0C */ s16 unk_0C; // hmf model index
    /* 0x0E */ s16 unk_0E; // frame count
    /* 0x10 */ s16 unk_10; // current frame
    /* 0x12 */ s16 unk_12; // frame tick
    /* 0x14 */ s16 unk_14; // ticks per frame
    /* 0x16 */ char pad16[2];
    /* 0x18 */ f32 *unk_18;
    /* 0x1C */ f32 *unk_1C;
    /* 0x20 */ f32 *unk_20;
} PuddlePaddleBillboard; // size = 0x24

s16 m217_AnimMdlFreeGet(s16 type);
s32 m217_AnimMdlDispOn(s16 index, f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale, f32 delay);
void m217_AngleDiffMinimize(f32 *angle, f32 *target);
void m217_SystemCreate(void);
PuddlePaddleFuncGroup *m217_FuncGroupCreate(omObjData *object, s8 index, s16 count, s16 handlers);
s16 m217_FuncSet(s8 index, s32 priority, void *data, void (*callback)(), s8 tag);
void m217_SprUpdate(void);
s16 m217_BillboardFreeGet(s16 type);
void m217_BillboardDispOn(s16 index, f32 x, f32 y, f32 z);
void m217_AnimMdlUpdate(void);
void m217_BillboardUpdate(void);
void m217_FuncReset(s8 arg0, PuddlePaddleFunc *arg1);
void m217_SprDispOn(s16 index, s16 x, s16 y);
s16 m217_SprCreate(s16 priority, s32 directory, s32 file, u16 bank, s32 attr);
s16 m217_AnimMdlCreate(s32 directory, s32 file, f32 speed, s16 type, s32 flags, s32 attr);
s16 m217_BillboardCreate(s32 directory, s32 file, s16 interval, s16 type, s32 flags);
void m217_SprDispOff(s16 arg0);
void m217_FuncGroupUpdate(s8 index);
void m217_MdlSync(omObjData *object);

#endif
