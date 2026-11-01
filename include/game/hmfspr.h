#ifndef _GAME_HMFSPR_H
#define _GAME_HMFSPR_H

#include "ultra64.h"
#include "game/hu3d.h"
#include "types.h"

void func_800142A0_main(s32 count);
void func_800143F0_main(void);
u16 HmfSprModelCreate(void *data, u32 flags, u16 attr);
u16 func_80014618_main(s16 idx, u16 attr);
void func_800146DC_main(s16 arg0, u16 arg1, u16 arg2);
void func_80014714_main(s16 arg0, s16 arg1);
void func_8001473C_main(s16 arg0, s16 arg1);
u16 func_8001476C_main(s16 arg0);
void func_80014794_main(s16 arg0, s16 arg1);
void func_800147FC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3);
void func_80014850_main(s16 arg0);
void func_800148A8_main(s16 idx, u8 r0, u8 g0, u8 b0, u8 a0, u8 r1, u8 g1, u8 b1, u8 a1);
void func_800149D0_main(s16 arg0, HmfColorKey *arg1);
void func_80014A3C_main(s32 frames);
void func_80016638_main(s32 idx);
void func_800166D0_main(void);
HmfModelSet *func_80016784_main(s16 model, s16 step);
HmfModelSet *func_800168A8_main(s16 model, s16 step, char *name);
void func_800169E0_main(s16 model, s16 step, HmfModelSet *set, s16 target);
void func_80016B00_main(s16 model, s16 frame, char *name, HuMtx4F *out);
void func_80016C2C_main(HmfData *hmf, s16 nodeIdx, s16 target);
void func_80016FB4_main(s16 model, HmfModelSet *set, s16 frame);
void func_80017128_main(s16 model, HmfModelSet *set, HuMtx4F mtx, s16 frame);
void func_80017320_main(HmfModelSet *set);
void func_80017358_main(s16 srcModel, char *srcName, s16 dstModel, char *dstName);
void func_8001766C_main(void);
s16 func_80017790_main(s16 model, s16 slot, s16 chr, s32 dataNum);
void func_80017954_main(s16 model, s16 slot, s16 chr, s16 animIdx);
void func_80017A84_main(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
s16 func_80017AD8_main(s32 dataNum);
void func_80017B20_main(s16 arg0, s16 arg1, u8 arg2, u8 arg3);
s32 func_80017B6C_main(s16 chr, s16 arg1, s16 arg2);
s32 func_80017BB8_main(s16 chr, s16 animId);
void func_80017C10_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80017CD0_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80017D24_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80018044_main(HuMtx4F a, HuMtx4F b, HuMtx4F out);
s16 func_800183A0_main(HuMtx4F src, HuMtx4F dst);
s32 func_80018544_main(HuMtx4F src, HuMtx4F dst);
void func_800185A4_main(HuMtx4F mtx, f32 angle);
void func_8001866C_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80018978_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
f32 InterpolateBMLine(f32 *value, f32 *time, f32 x);
f32 func_80018D68_main(f32 mtx[3][3]);
void func_80018DD8_main(f32 arg0[4][4], s32 arg1, s32 arg2, f32 arg3[3][3]);
f32 func_80018E50_main(HuMtx4F mtx, s32 row, s32 col);
f32 func_80018E74_main(HuMtx4F mtx);
s32 func_80018F18_main(HuMtx4F src, HuMtx4F dst);

#endif
