#ifndef _PARTY_COMMON_VEC_H
#define _PARTY_COMMON_VEC_H

#include "common_board.h"
#include "game/board.h"

f32 MBVecAngleGet(Vec *arg0);
void MBVecNormalize(Vec *vec);
void MBVecRotateX(Vec *arg0, f32 arg1);
void MBVecRotateY(Vec *arg0, f32 arg1);
void MBVecRotateZ(Vec *arg0, f32 arg1);
void MBVecAxisRotate(Vec* arg0, Vec* arg1, f32 arg2);
f32 MBVecBetweenAngleGet(Vec *vec_1, Vec *vec_2);

#endif //_PARTY_COMMON_VEC_H