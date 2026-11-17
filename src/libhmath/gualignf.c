#include "humath.h"

// Builds a floating-point matrix that aligns the negative Z axis to a direction.
void HuAlignF(HuMtx4F mtx, f32 angle, f32 x, f32 y, f32 z) {
    f32 sine, cosine;
    f32 len;
    f32 inv;
    f32 xz;

    len = HuSqrtf(x * x + y * y + z * z);
    if (len == 0.0f) {
        return;
    }
    len = 1.0f / len;
    x *= len;
    z *= len;
    y *= len;
    xz = HuSqrtf(x * x + z * z);
    sincosdf(angle, &sine, &cosine);
    if (xz != 0.0f) {
        inv = 1.0f / xz;
        mtx[0][0] = (-z * cosine - sine * y * x) * inv;
        mtx[1][0] = (z * sine - cosine * y * x) * inv;
        mtx[2][0] = -x;
        mtx[0][1] = sine * xz;
        mtx[1][1] = cosine * xz;
        mtx[2][1] = -y;
        mtx[0][2] = (cosine * x - sine * y * z) * inv;
        mtx[1][2] = (-sine * x - cosine * y * z) * inv;
        mtx[2][2] = -z;
    } else {
        mtx[0][0] = cosine;
        mtx[1][0] = -sine;
        mtx[2][0] = 0.0f;
        mtx[0][1] = 0.0f;
        mtx[1][1] = 0.0f;
        mtx[2][1] = -y;
        mtx[0][2] = sine * y;
        mtx[1][2] = cosine * y;
        mtx[2][2] = 0.0f;
    }
    mtx[3][0] = 0.0f;
    mtx[3][1] = 0.0f;
    mtx[3][2] = 0.0f;
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;
    mtx[3][3] = 1.0f;
}
