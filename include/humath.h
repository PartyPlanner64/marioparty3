#ifndef _HUMATH_H
#define _HUMATH_H

#include "PR/ultratypes.h"
#include "PR/mbi.h"
#include "math.h"
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} HuVec3I;

typedef struct {
    f32 fov;
    f32 aspect;
    f32 near;
    f32 far;
    f32 scale;
} PerspectiveParams;

typedef struct Vec2f {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
} Vec2f;

/* Application-owned default tolerance used by libhmath's epsilon helpers. */
extern f32 D_800A12A4_main;

f64 HuSqrt(f64 x);
s32 func_80089820_main(f32 value, f32 threshold);
s32 func_80089860_main(f32 value);
s32 func_800898A0_main(f32 a, f32 b, f32 threshold);
s32 func_800898D0_main(f32 a, f32 b);
s32 func_80089750_main(f32 value);
s32 func_80089790_main(f32 value, f32 threshold);
s32 func_800897D0_main(f32 value);
void func_800884B0_main(Mtx *m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void HuLookAtF(HuMtx4F mf, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void func_80088520_main(Mtx *m, u16 *perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);
void func_80088CB0_main(HuMtx4F mtx, f32 r, f32 p, f32 h, f32 s, f32 x, f32 y, f32 z);
void func_80088E50_main(Mtx *m, f32 r, f32 p, f32 h, f32 s, f32 x, f32 y, f32 z);
void func_80089190_main(HuMtx4F mtx, f32 angle, f32 x, f32 y, f32 z);
void func_80088570_main(HuMtx4F mtx, f32 angle, f32 x, f32 y, f32 z);
void func_80088700_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80088750_main(Mtx *mtx, f32 x, f32 y, f32 z);
void func_80088800_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80088850_main(Mtx *mtx, const f32 x, const f32 y, const f32 z);
void func_80088910_main(HuMtx4F mtx, f32 r, f32 p, f32 h);
void func_80088A70_main(Mtx *mtx, f32 r, f32 p, f32 h);
void func_8008D450_main(HuMtx4F mtx, Vec *camera, Vec *basis);
void func_80089FF0_main(Mtx *mtx, Vec *camera);
void func_8008CCC0_main(const HuMtx4F a, const HuMtx4F b, HuMtx4F result);
void func_8008CD90_main(Mtx *a, Mtx *b, Mtx *result);
void func_8008CE00_main(const HuMtx4F a, const HuMtx4F b, HuMtx4F result);
void func_8008CEE0_main(Mtx *a, const Mtx *b, Mtx *result);
void func_8008CFA0_main(const HuMtx4F a, const HuMtx4F b, HuMtx4F result);
void func_8008D070_main(Mtx *a, const Mtx *b, Mtx *result);
void func_8008D130_main(const HuMtx4F a, const HuMtx4F b, HuMtx4F result);
void func_8008D1F0_main(Mtx *a, Mtx *b, Mtx *result);
void func_8008CB90_main(Mtx *src, f32 *scale, Mtx *dst);
void func_8008CB30_main(HuMtx4F src, f32 *scale, HuMtx4F dst);
void func_8008CC60_main(Mtx *src, f32 *translation, Mtx *dst);
void func_8008CBF0_main(const HuMtx4F src, f32 *translation, HuMtx4F dst);
void func_8008A7F0_main(HuMtx4F mtx, const f32 *rot);
void func_8008AD60_main(Mtx *m, const f32 *rot, const f32 *scale, const f32 *translation);
void func_8008B0E0_main(HuMtx4F mtx, f32 angle, const f32 *axis);
void func_8008A960_main(Mtx *mtx, const f32 *rot);
void func_8008ABA0_main(HuMtx4F mtx, const f32 *rot, const f32 *scale, const f32 *translation);
void func_800898F0_main(HuMtx4F mf, Mtx *m);
void func_8008A0D0_main(Mtx *mtx);
void func_8008A070_main(HuMtx4F mtx);
void func_80089980_main(HuMtx4F mf, Mtx *m);
void func_800893B0_main(Mtx *m, f32 angle, f32 x, f32 y, f32 z);
void func_8008B300_main(Mtx *m, f32 angle, const f32 *axis);
void func_8008A1B0_main(Mtx *mtx, f32 angle);
void func_8008B6B0_main(const HuMtx4F src, f32 angle, HuMtx4F dst);
void func_8008C5E0_main(Mtx *src, f32 angle, Mtx *dst);
void func_8008A120_main(HuMtx4F mtx, f32 angle);
void func_8008A330_main(Mtx *mtx, f32 angle);
void func_8008B840_main(Mtx *src, f32 angle, Mtx *dst);
void func_8008BD90_main(const HuMtx4F src, f32 angle, HuMtx4F dst);
void func_8008A2A0_main(HuMtx4F mtx, f32 angle);
void func_8008A4C0_main(Mtx *mtx, f32 angle);
void func_8008BF20_main(Mtx *src, f32 angle, Mtx *dst);
void func_8008C450_main(const HuMtx4F src, f32 angle, HuMtx4F dst);
void func_8008A430_main(HuMtx4F mtx, f32 angle);
void func_8008A5C0_main(HuMtx4F mtx, f32 *scale);
void func_8008A620_main(Mtx *mtx, f32 *scale);
void func_8008A6D0_main(HuMtx4F mtx, f32 *translation);
void func_8008A730_main(Mtx *mtx, const f32 *translation);
void func_8008D2C0_main(HuMtx4F mtx, u16 *perspNorm, f32 fov, f32 aspect, f32 near, f32 far, f32 scale);
void func_8008A030_main(Mtx *mtx, u16 *perspNorm, PerspectiveParams *params);
void func_8008D5D0_main(HuMtx4F mtx, u16 *perspNorm, const PerspectiveParams *params);
f32 HuSqrtf(f32 x);
void HuVecAdd(Vec *out, Vec *a, Vec *b);
void HuVecAddScaled(Vec *out, Vec *a, f32 scalar, Vec *b);
void HuVecCopyXYZ(Vec *out, f32 x, f32 y, f32 z);
void HuVecCopy3F(Vec *out, Vec *a);
void HuVecCross(Vec *out, Vec *a, Vec *b);
f32 HuVecDistance(const Vec *a, const Vec *b);
f32 HuVecDistanceSqr(const Vec *a, const Vec *b);
f32 HuVecDot3F(Vec *a, Vec *b);
f32 HuVecDotProduct(f32 aX, f32 aY, f32 aZ, f32 bX, f32 bY, f32 bZ);
s32 HuVecIsEqual(Vec *a, Vec *b);
void HuVecLinearComb(Vec *out, f32 scaleA, Vec *a, f32 scaleB, Vec *b);
void HuVecLinearComb2D(Vec *out, Vec *scale, Vec *a, Vec *b);
f32 HuVecGetLength3F(Vec *vec);
f32 HuVecGetLengthSqr(f32 x, f32 y, f32 z);
f32 mulHuVecGetLength(f32 x, f32 y, f32 z);
f32 HuVecGetLengthSqr3F(Vec *vec);
void HuVecMulScalar(Vec *out, f32 scalar, Vec *a);
s32 func_80089E90_main(Vec *a, Vec *b, f32 epsilon);
s32 func_80089F30_main(Vec *a, Vec *b);
void func_80089FD0_main(HuMtx4F mtx, Vec *camera);
void HuVecNeg(Vec *out, Vec *a);
void HuVecNormalize3F(Vec *const vec);
void HuVecNormalize(f32 *x, f32 *y, f32 *z);
void HuVecSubtract(Vec *out, Vec *a, Vec *b);

#endif
