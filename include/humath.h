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
extern f32 HuMathEpsilon;

f64 HuSqrt(f64 x);
s32 HuInRangeF(f32 value, f32 threshold);
s32 HuInRangeEpsF(f32 value);
s32 HuNearEqF(f32 a, f32 b, f32 threshold);
s32 HuNearEqEpsF(f32 a, f32 b);
s32 HuSignF(f32 value);
s32 HuSignThreshF(f32 value, f32 threshold);
s32 HuSignEpsF(f32 value);
void HuLookAt(Mtx *m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void HuLookAtF(HuMtx4F mf, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void HuPerspective(Mtx *m, u16 *perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);
void HuPositionF(HuMtx4F mtx, f32 r, f32 p, f32 h, f32 s, f32 x, f32 y, f32 z);
void HuPosition(Mtx *m, f32 r, f32 p, f32 h, f32 s, f32 x, f32 y, f32 z);
void HuAlignF(HuMtx4F mtx, f32 angle, f32 x, f32 y, f32 z);
void HuRotateF(HuMtx4F mtx, f32 angle, f32 x, f32 y, f32 z);
void HuScaleF(HuMtx4F mtx, f32 x, f32 y, f32 z);
void HuScale(Mtx *mtx, f32 x, f32 y, f32 z);
void HuTranslateF(HuMtx4F mtx, f32 x, f32 y, f32 z);
void HuTranslate(Mtx *mtx, const f32 x, const f32 y, const f32 z);
void HuRotateRPYF(HuMtx4F mtx, f32 r, f32 p, f32 h);
void HuRotateRPY(Mtx *mtx, f32 r, f32 p, f32 h);
void HuMtxLookAtBasisF(HuMtx4F mtx, Vec *camera, Vec *basis);
void HuMtxLookAt(Mtx *mtx, Vec *camera);
void HuMtxCatF(const HuMtx4F a, const HuMtx4F b, HuMtx4F result);
void HuMtxCat(Mtx *a, Mtx *b, Mtx *result);
void HuMtxCatAffineF(const HuMtx4F a, const HuMtx4F b, HuMtx4F result);
void HuMtxCatAffine(Mtx *a, const Mtx *b, Mtx *result);
void HuMtxCatRotF(const HuMtx4F a, const HuMtx4F b, HuMtx4F result);
void HuMtxCatRot(Mtx *a, const Mtx *b, Mtx *result);
void HuMtxCatTransF(const HuMtx4F a, const HuMtx4F b, HuMtx4F result);
void HuMtxCatTrans(Mtx *a, Mtx *b, Mtx *result);
void HuMtxScaleCat(Mtx *src, f32 *scale, Mtx *dst);
void HuMtxScaleCatF(HuMtx4F src, f32 *scale, HuMtx4F dst);
void HuMtxTransCat(Mtx *src, f32 *translation, Mtx *dst);
void HuMtxTransCatF(const HuMtx4F src, f32 *translation, HuMtx4F dst);
void HuMtxRotF(HuMtx4F mtx, const f32 *rot);
void HuMtxSRT(Mtx *m, const f32 *rot, const f32 *scale, const f32 *translation);
void HuMtxAlignF(HuMtx4F mtx, f32 angle, const f32 *axis);
void HuMtxRot(Mtx *mtx, const f32 *rot);
void HuMtxSRTF(HuMtx4F mtx, const f32 *rot, const f32 *scale, const f32 *translation);
void HuMtxF2L(HuMtx4F mf, Mtx *m);
void HuMtxIdent(Mtx *mtx);
void HuMtxIdentF(HuMtx4F mtx);
void HuMtxL2F(HuMtx4F mf, Mtx *m);
void HuAlign(Mtx *m, f32 angle, f32 x, f32 y, f32 z);
void HuMtxAlign(Mtx *m, f32 angle, const f32 *axis);
void HuMtxRotX(Mtx *mtx, f32 angle);
void HuMtxRotXCatF(const HuMtx4F src, f32 angle, HuMtx4F dst);
void HuMtxRotZCat(Mtx *src, f32 angle, Mtx *dst);
void HuMtxRotXF(HuMtx4F mtx, f32 angle);
void HuMtxRotY(Mtx *mtx, f32 angle);
void HuMtxRotXCat(Mtx *src, f32 angle, Mtx *dst);
void HuMtxRotYCatF(const HuMtx4F src, f32 angle, HuMtx4F dst);
void HuMtxRotYF(HuMtx4F mtx, f32 angle);
void HuMtxRotZ(Mtx *mtx, f32 angle);
void HuMtxRotYCat(Mtx *src, f32 angle, Mtx *dst);
void HuMtxRotZCatF(const HuMtx4F src, f32 angle, HuMtx4F dst);
void HuMtxRotZF(HuMtx4F mtx, f32 angle);
void HuMtxScaleF(HuMtx4F mtx, f32 *scale);
void HuMtxScale(Mtx *mtx, f32 *scale);
void HuMtxTransF(HuMtx4F mtx, f32 *translation);
void HuMtxTrans(Mtx *mtx, const f32 *translation);
void HuPerspectiveF(HuMtx4F mtx, u16 *perspNorm, f32 fov, f32 aspect, f32 near, f32 far, f32 scale);
void HuMtxPerspective(Mtx *mtx, u16 *perspNorm, PerspectiveParams *params);
void HuMtxPerspectiveF(HuMtx4F mtx, u16 *perspNorm, const PerspectiveParams *params);
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
s32 HuVecNearEq(Vec *a, Vec *b, f32 epsilon);
s32 HuVecNearEqEps(Vec *a, Vec *b);
void HuMtxLookAtF(HuMtx4F mtx, Vec *camera);
void HuVecNeg(Vec *out, Vec *a);
void HuVecNormalize3F(Vec *const vec);
void HuVecNormalize(f32 *x, f32 *y, f32 *z);
void HuVecSubtract(Vec *out, Vec *a, Vec *b);

#endif
