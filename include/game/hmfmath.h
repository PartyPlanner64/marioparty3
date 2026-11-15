#ifndef _GAME_HMFMATH_H
#define _GAME_HMFMATH_H

#include "ultra64.h"
#include "humath.h"

void mtxTransCat(HuMtx4F mtx, f32 x, f32 y, f32 z);
void mtxScaleCat(HuMtx4F mtx, f32 x, f32 y, f32 z);
void mtxRotCat(HuMtx4F mtx, f32 x, f32 y, f32 z);
void mtxCat(HuMtx4F a, HuMtx4F b, HuMtx4F out);
s16 HmfInverseMtxF3X3(HuMtx4F src, HuMtx4F dst);
s32 HmfInverseMtxF3X3Cat(HuMtx4F src, HuMtx4F dst);
void mtxRotYCat(HuMtx4F mtx, f32 angle);
void mtxRotCatZXY(HuMtx4F mtx, f32 x, f32 y, f32 z);
void mtxRotZXY(HuMtx4F mtx, f32 x, f32 y, f32 z);
f32 InterpolateBMLine(f32 *value, const f32 *time, f32 x);
f32 mtxDet3x3(f32 mtx[3][3]);
void mtxMinorGet(f32 arg0[4][4], s32 arg1, s32 arg2, f32 arg3[3][3]);
f32 mtxMinorDet(HuMtx4F mtx, s32 row, s32 col);
f32 mtxDet(HuMtx4F mtx);
s32 mtxInverse(HuMtx4F src, HuMtx4F dst);

#endif
