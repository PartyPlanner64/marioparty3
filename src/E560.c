#include "common.h"

f32 HuVecDot3F(Vec *a, Vec *b);

s32 PrecalcPntToTriangle(Vec *origin, Vec *u, Vec *v, Vec *normal, Vec *point, Vec *out);

void func_8000D960_main(HuMtx4F in, HuMtx4F out) {
    f32 m00m11 = in[0][0] * in[1][1];
    f32 m00m12 = in[0][0] * in[1][2];
    f32 m00m21 = in[0][0] * in[2][1];
    f32 m00m22 = in[0][0] * in[2][2];
    f32 m01m10 = in[0][1] * in[1][0];
    f32 m01m12 = in[0][1] * in[1][2];
    f32 m01m20 = in[0][1] * in[2][0];
    f32 m01m22 = in[0][1] * in[2][2];
    f32 m02m10 = in[0][2] * in[1][0];
    f32 m02m11 = in[0][2] * in[1][1];
    f32 m02m20 = in[0][2] * in[2][0];
    f32 m02m21 = in[0][2] * in[2][1];
    f32 m10m21 = in[1][0] * in[2][1];
    f32 m10m22 = in[1][0] * in[2][2];
    f32 m11m20 = in[1][1] * in[2][0];
    f32 m11m22 = in[1][1] * in[2][2];
    f32 m12m20 = in[1][2] * in[2][0];
    f32 m12m21 = in[1][2] * in[2][1];
    f32 invDet;

    invDet = 1.0f / ((m01m12 - m02m11) * in[2][0] + (m02m10 - m00m12) * in[2][1] + (m00m11 - m01m10) * in[2][2]);
    out[0][0] = (-m12m21 + m11m22) * invDet;
    out[0][1] = (m02m21 - m01m22) * invDet;
    out[0][2] = (-m02m11 + m01m12) * invDet;
    out[1][0] = (m12m20 - m10m22) * invDet;
    out[1][1] = (-m02m20 + m00m22) * invDet;
    out[1][2] = (m02m10 - m00m12) * invDet;
    out[2][0] = (-m11m20 + m10m21) * invDet;
    out[2][1] = (m01m20 - m00m21) * invDet;
    out[2][2] = (-m01m10 + m00m11) * invDet;
    out[3][0] = ((m10m22 - m12m20) * in[3][1] + (m11m20 - m10m21) * in[3][2] + (m12m21 - m11m22) * in[3][0]) * invDet;
    out[3][1] = ((m01m22 - m02m21) * in[3][0] + (m02m20 - m00m22) * in[3][1] + (m00m21 - m01m20) * in[3][2]) * invDet;
    out[3][2] = ((m02m11 - m01m12) * in[3][0] + (m00m12 - m02m10) * in[3][1] + (m01m10 - m00m11) * in[3][2]) * invDet;
    out[0][3] = out[1][3] = out[2][3] = 0.0f;
    out[3][3] = 1.0f;
}

s32 Hitcheck_Triangle_with_Sphere(Vec *triangle, Vec *sphereOrigin, f32 sphereRadius, Vec *closestPoint) {
    Vec triPoint;
    Vec u;
    Vec v;
    Vec normal;
    Vec toSphere;
    Vec offset;

    HuVecCopy3F(&triPoint, &triangle[0]);
    HuVecSubtract(&u, &triangle[1], &triangle[0]);
    HuVecSubtract(&v, &triangle[2], &triangle[0]);
    HuVecCross(&normal, &u, &v);
    HuVecSubtract(&toSphere, sphereOrigin, &triangle[0]);
    PrecalcPntToTriangle(&triPoint, &u, &v, &normal, &toSphere, &offset);
    HuVecAdd(closestPoint, &offset, &triPoint);
    if (HuVecDistance(closestPoint, sphereOrigin) > sphereRadius) {
        return FALSE;
    } else {
        return TRUE;
    }
}

s32 PrecalcPntToTriangle(Vec *origin, Vec *u, Vec *v, Vec *normal, Vec *point, Vec *out) {
    Vec sp10;
    Vec sp20;
    Vec unused; // Unreferenced, but present in the original stack frame
    f32 invDet;
    f32 s;
    f32 t;
    f32 scale;

    HuVecCopyXYZ(&sp10, -point->x, -point->y, -point->z);
    invDet = 1.0f / (-(u->z * v->y * normal->x) + u->y * v->z * normal->x + u->z * v->x * normal->y -
                     u->x * v->z * normal->y - u->y * v->x * normal->z + u->x * v->y * normal->z);
    s = (v->z * (normal->y * sp10.x - normal->x * sp10.y) + v->y * (normal->x * sp10.z - normal->z * sp10.x) +
         v->x * (normal->z * sp10.y - normal->y * sp10.z)) *
        invDet;
    t = (u->z * (normal->x * sp10.y - normal->y * sp10.x) + u->y * (normal->z * sp10.x - normal->x * sp10.z) +
         u->x * (normal->y * sp10.z - normal->z * sp10.y)) *
        invDet;
    if (s > 0.0f && t > 0.0f && s + t > 1.0f) {
        HuVecSubtract(&sp10, v, u);
        HuVecSubtract(&sp20, point, u);
        scale = HuVecDot3F(&sp10, &sp20) / HuVecDot3F(&sp10, &sp10);
        if (scale <= 0.0f) {
            HuVecCopy3F(out, u);
        } else if (scale >= 1.0f) {
            HuVecCopy3F(out, v);
        } else {
            HuVecMulScalar(&sp20, scale, &sp10);
            HuVecAdd(out, u, &sp20);
        }
    } else if (t < 0.0f) {
        scale = HuVecDot3F(u, point) / HuVecDot3F(u, u);
        if (scale <= 0.0f) {
            HuVecCopyXYZ(out, 0.0f, 0.0f, 0.0f);
        } else if (scale >= 1.0f) {
            HuVecCopy3F(out, u);
        } else {
            HuVecMulScalar(out, scale, u);
        }
    } else if (s < 0.0f) {
        scale = HuVecDot3F(v, point) / HuVecDot3F(v, v);
        if (scale <= 0.0f) {
            HuVecCopyXYZ(out, 0.0f, 0.0f, 0.0f);
        } else if (scale >= 1.0f) {
            HuVecCopy3F(out, v);
        } else {
            HuVecMulScalar(out, scale, v);
        }
    } else {
        HuVecCopyXYZ(out, s * u->x + t * v->x, s * u->y + t * v->y, s * u->z + t * v->z);
    }
    return TRUE;
}

s32 Hitcheck_Quadrangle_with_Sphere(Vec *quad, Vec *sphereOrigin, f32 sphereRadius, Vec *closestPoint) {
    Vec quadPoint;
    Vec u;
    Vec v;
    Vec w;
    Vec normal;
    Vec toSphere;
    Vec offset;
    Vec closest1;
    Vec closest2;
    f32 dist1;
    f32 dist2;

    HuVecCopy3F(&quadPoint, &quad[0]);
    HuVecSubtract(&u, &quad[1], &quad[0]);
    HuVecSubtract(&v, &quad[2], &quad[0]);
    HuVecSubtract(&w, &quad[3], &quad[0]);
    HuVecCross(&normal, &u, &v);
    HuVecSubtract(&toSphere, sphereOrigin, &quad[0]);
    PrecalcPntToTriangle(&quadPoint, &u, &v, &normal, &toSphere, &offset);
    HuVecAdd(&closest1, &offset, &quadPoint);
    PrecalcPntToTriangle(&quadPoint, &v, &w, &normal, &toSphere, &offset);
    HuVecAdd(&closest2, &offset, &quadPoint);
    dist1 = HuVecDistance(&closest1, sphereOrigin);
    dist2 = HuVecDistance(&closest2, sphereOrigin);
    if (dist2 > dist1) {
        HuVecCopy3F(closestPoint, &closest1);
    } else {
        dist1 = dist2;
        HuVecCopy3F(closestPoint, &closest2);
    }
    if (dist1 > sphereRadius) {
        return FALSE;
    } else {
        return TRUE;
    }
}

void func_8000E344_main(Vec *a, Vec *b, Vec *out) {
    HuVecMulScalar(out, HuVecDot3F(a, b) / HuVecDot3F(a, a), a);
}
