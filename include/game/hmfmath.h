#ifndef _GAME_HMFMATH_H
#define _GAME_HMFMATH_H

#include "ultra64.h"
#include "humath.h"

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
