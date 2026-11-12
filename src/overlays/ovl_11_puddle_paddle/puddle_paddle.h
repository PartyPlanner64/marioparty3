#ifndef _PUDDLE_PADDLE_H
#define _PUDDLE_PADDLE_H

#include "common.h"

typedef struct PuddlePaddleSlot { // 0xC bytes
    /* 0x00 */ omObjData *unk_00;
    /* 0x04 */ s16 *unk_04; // model indices
    /* 0x08 */ s16 unk_08;
} PuddlePaddleSlot; // Size 0xC

typedef struct PuddlePaddleHandler {
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
} PuddlePaddleHandler; // Size 0x44

typedef struct PuddlePaddleOrder {
    /* 0x00 */ u32 priority;
    /* 0x04 */ s16 next;
    /* 0x06 */ s16 previous;
    /* 0x08 */ s16 handler;
    /* 0x0A */ char unk_0A[2];
} PuddlePaddleOrder; // Size 0xC

typedef struct UnkPuddlePaddleObj { // size = 0x14, eight entries
    /* 0x00 */ PuddlePaddleSlot *unk_00;
    /* 0x04 */ PuddlePaddleHandler *unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char pad0A[2];
    /* 0x0C */ PuddlePaddleOrder *unk_0C;
    /* 0x10 */ s8 unk_10;
    /* 0x11 */ char pad11[3];
} UnkPuddlePaddleObj;

typedef struct UnkPuddlePaddleSpr { // size = 0x8, twenty entries
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ char pad03[1];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} UnkPuddlePaddleSpr;

typedef struct UnkPuddlePaddleEntry { // size 0x24, sixteen entries
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
} UnkPuddlePaddleEntry; // size = 0x24

extern UnkPuddlePaddleSpr *D_80111664_puddle_paddle;
extern UnkPuddlePaddleEntry *D_80111668_puddle_paddle;

s16 func_8010C42C_puddle_paddle(s16 type);
s32 func_8010C4D0_puddle_paddle(s16 index, f32 x, f32 y, f32 z, f32 rx, f32 ry, f32 rz, f32 scale, f32 delay);
void func_80110BBC_puddle_paddle(f32 *angle, f32 *target);
void func_8010B820_puddle_paddle(void);
UnkPuddlePaddleObj *func_8010B8B4_puddle_paddle(omObjData *object, s8 index, s16 count, s16 handlers);
s16 func_8010BA04_puddle_paddle(s8 index, s32 priority, void *data, void (*callback)(), s8 tag);
void func_8010C16C_puddle_paddle(void);
s16 func_8010C98C_puddle_paddle(s16 type);
void func_8010CA30_puddle_paddle(s16 index, f32 x, f32 y, f32 z);
void func_8010C664_puddle_paddle(void);
void func_8010CCF0_puddle_paddle(void);
void func_8010BAA8_puddle_paddle(s8 arg0, PuddlePaddleHandler *arg1);
void func_8010C088_puddle_paddle(s16 index, s16 x, s16 y);
s16 func_8010BEE8_puddle_paddle(s16 priority, s32 directory, s32 file, u16 bank, s32 attr);
s16 func_8010C214_puddle_paddle(s32 directory, s32 file, f32 speed, s16 type, s32 flags, s32 attr);
s16 func_8010C804_puddle_paddle(s32 directory, s32 file, s16 interval, s16 type, s32 flags);
void func_8010C11C_puddle_paddle(s16 arg0);
void func_8010BC14_puddle_paddle(s8 index);
void func_80110714_puddle_paddle(omObjData *object);

#endif
