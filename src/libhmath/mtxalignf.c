#include "humath.h"

// Build a floating-point matrix that aligns the negative Z axis to a direction.
void HuMtxAlignF(HuMtx4F mtx, f32 angle, const f32 *axis) {
    f32 sine, cosine;
    f32 len;
    f32 xz;
    f32 x, y, z;
    f32 xn, yn, zn;
    f32 inv;

    x = axis[0];
    y = axis[1];
    z = axis[2];
    len = HuSqrtf(x * x + y * y + z * z);
    if (len == 0.0f) {
        return;
    }
    len = 1.0f / len;
    xn = x * len;
    yn = y * len;
    zn = z * len;
    xz = HuSqrtf(xn * xn + zn * zn);
    sincosdf(angle, &sine, &cosine);
    if (xz != 0.0f) {
        inv = 1.0f / xz;
        mtx[0][0] = (-zn * cosine - sine * yn * xn) * inv;
        mtx[1][0] = (zn * sine - cosine * yn * xn) * inv;
        mtx[2][0] = -xn;
        mtx[0][1] = sine * xz;
        mtx[1][1] = cosine * xz;
        mtx[2][1] = -yn;
        mtx[0][2] = (cosine * xn - sine * yn * zn) * inv;
        mtx[1][2] = (-sine * xn - cosine * yn * zn) * inv;
        mtx[2][2] = -zn;
    } else {
        mtx[0][0] = cosine;
        mtx[1][0] = -sine;
        mtx[2][0] = 0.0f;
        mtx[0][1] = 0.0f;
        mtx[1][1] = 0.0f;
        mtx[2][1] = -yn;
        mtx[0][2] = sine * yn;
        mtx[1][2] = cosine * yn;
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
