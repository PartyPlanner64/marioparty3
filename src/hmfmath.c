#include "ultra64.h"
#include "humath.h"
#include "game/hmfmath.h"

void mtxTransCat(HuMtx4F mtx, f32 x, f32 y, f32 z) {
    mtx[3][0] += x * mtx[0][0] + y * mtx[1][0] + z * mtx[2][0];
    mtx[3][1] += x * mtx[0][1] + y * mtx[1][1] + z * mtx[2][1];
    mtx[3][2] += x * mtx[0][2] + y * mtx[1][2] + z * mtx[2][2];
    mtx[3][3] += x * mtx[0][3] + y * mtx[1][3] + z * mtx[2][3];
}

void mtxScaleCat(HuMtx4F mtx, f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 0; i < 3; i++) {
        mtx[0][i] *= x;
        mtx[1][i] *= y;
        mtx[2][i] *= z;
    }
}

void mtxRotCat(HuMtx4F mtx, f32 x, f32 y, f32 z) {
    f32 rot[3][3];
    f32 sx, cx;
    f32 sy, cy;
    f32 sz, cz;
    f32 m00, m01, m02;
    f32 m10, m11, m12;

    sincosdf(x, &sx, &cx);
    if (x == y) {
        sy = sx;
        cy = cx;
    } else {
        sincosdf(y, &sy, &cy);
    }
    if (x == z) {
        sz = sx;
        cz = cx;
    } else if (y == z) {
        sz = sy;
        cz = cy;
    } else {
        sincosdf(z, &sz, &cz);
    }
    rot[0][0] = cy * cz;
    rot[0][1] = cy * sz;
    rot[0][2] = -sy;
    rot[1][0] = sx * sy * cz - cx * sz;
    rot[1][1] = sx * sy * sz + cx * cz;
    rot[1][2] = sx * cy;
    rot[2][0] = cx * sy * cz + sx * sz;
    rot[2][1] = cx * sy * sz - sx * cz;
    rot[2][2] = cx * cy;
    m00 = rot[0][0] * mtx[0][0] + rot[0][1] * mtx[1][0] + rot[0][2] * mtx[2][0];
    m01 = rot[0][0] * mtx[0][1] + rot[0][1] * mtx[1][1] + rot[0][2] * mtx[2][1];
    m02 = rot[0][0] * mtx[0][2] + rot[0][1] * mtx[1][2] + rot[0][2] * mtx[2][2];
    m10 = rot[1][0] * mtx[0][0] + rot[1][1] * mtx[1][0] + rot[1][2] * mtx[2][0];
    m11 = rot[1][0] * mtx[0][1] + rot[1][1] * mtx[1][1] + rot[1][2] * mtx[2][1];
    m12 = rot[1][0] * mtx[0][2] + rot[1][1] * mtx[1][2] + rot[1][2] * mtx[2][2];
    mtx[2][0] = rot[2][0] * mtx[0][0] + rot[2][1] * mtx[1][0] + rot[2][2] * mtx[2][0];
    mtx[2][1] = rot[2][0] * mtx[0][1] + rot[2][1] * mtx[1][1] + rot[2][2] * mtx[2][1];
    mtx[2][2] = rot[2][0] * mtx[0][2] + rot[2][1] * mtx[1][2] + rot[2][2] * mtx[2][2];
    mtx[0][0] = m00;
    mtx[0][1] = m01;
    mtx[0][2] = m02;
    mtx[1][0] = m10;
    mtx[1][1] = m11;
    mtx[1][2] = m12;
}

void func_80018044_main(HuMtx4F a, HuMtx4F b, HuMtx4F out) {
    s32 i;

    if (a[0][3] != 0.0f || a[1][3] != 0.0f || a[2][3] != 0.0f || a[3][3] != 1.0f) {
        f32 b00, b01, b02, b03;
        f32 b10, b11, b12, b13;
        f32 b20, b21, b22, b23;
        f32 b30, b31, b32, b33;
        f32 r0, r1, r2, r3;

        i = 0;
        b00 = b[0][0];
        b10 = b[1][0];
        b20 = b[2][0];
        b30 = b[3][0];
        b01 = b[0][1];
        b11 = b[1][1];
        b21 = b[2][1];
        b31 = b[3][1];
        b02 = b[0][2];
        b12 = b[1][2];
        b22 = b[2][2];
        b32 = b[3][2];
        b03 = b[0][3];
        b13 = b[1][3];
        b23 = b[2][3];
        b33 = b[3][3];
        for (; i < 4; i++) {
            out[i][0] = (r0 = a[i][0]) * b00 + (r1 = a[i][1]) * b10 + (r2 = a[i][2]) * b20 + (r3 = a[i][3]) * b30;
            out[i][1] = r0 * b01 + r1 * b11 + r2 * b21 + r3 * b31;
            out[i][2] = r0 * b02 + r1 * b12 + r2 * b22 + r3 * b32;
            out[i][3] = r0 * b03 + r1 * b13 + r2 * b23 + r3 * b33;
        }
    } else {
        f32 b00, b01, b02, b03;
        f32 b10, b11, b12, b13;
        f32 b20, b21, b22, b23;
        f32 r0, r1, r2;
        f32 c0, c1, c2;

        i = 0;
        b00 = b[0][0];
        b10 = b[1][0];
        b20 = b[2][0];
        b01 = b[0][1];
        b11 = b[1][1];
        b21 = b[2][1];
        b02 = b[0][2];
        b12 = b[1][2];
        b22 = b[2][2];
        b03 = b[0][3];
        b13 = b[1][3];
        b23 = b[2][3];
        for (; i < 3; i++) {
            out[i][0] = (r0 = a[i][0]) * b00 + (r1 = a[i][1]) * b10 + (r2 = a[i][2]) * b20;
            out[i][1] = r0 * b01 + r1 * b11 + r2 * b21;
            out[i][2] = r0 * b02 + r1 * b12 + r2 * b22;
            out[i][3] = r0 * b03 + r1 * b13 + r2 * b23;
        }
        out[3][0] = (c0 = a[3][0]) * b[0][0] + (c1 = a[3][1]) * b[1][0] + (c2 = a[3][2]) * b[2][0] + b[3][0];
        out[3][1] = c0 * b[0][1] + c1 * b[1][1] + c2 * b[2][1] + b[3][1];
        out[3][2] = c0 * b[0][2] + c1 * b[1][2] + c2 * b[2][2] + b[3][2];
        out[3][3] = c0 * b[0][3] + c1 * b[1][3] + c2 * b[2][3] + b[3][3];
    }
}

s16 HmfInverseMtxF3X3(HuMtx4F src, HuMtx4F dst) {
    f32 c00 = src[1][1] * src[2][2] - src[1][2] * src[2][1];
    f32 c10 = src[1][2] * src[2][0] - src[1][0] * src[2][2];
    f32 c20 = src[1][0] * src[2][1] - src[1][1] * src[2][0];
    f32 det = c00 * src[0][0] + c10 * src[0][1] + c20 * src[0][2];

    if (det == 0.0f) {
        return 0;
    }
    det = 1.0f / det;
    dst[0][0] = c00 * det;
    dst[1][0] = c10 * det;
    dst[2][0] = c20 * det;
    dst[0][1] = (src[0][2] * src[2][1] - src[0][1] * src[2][2]) * det;
    dst[0][2] = (src[0][1] * src[1][2] - src[0][2] * src[1][1]) * det;
    dst[1][1] = (src[0][0] * src[2][2] - src[0][2] * src[2][0]) * det;
    dst[1][2] = (src[0][2] * src[1][0] - src[0][0] * src[1][2]) * det;
    dst[2][1] = (src[0][1] * src[2][0] - src[0][0] * src[2][1]) * det;
    dst[2][2] = (src[0][0] * src[1][1] - src[0][1] * src[1][0]) * det;
    dst[0][3] = dst[1][3] = dst[2][3] = dst[3][0] = dst[3][1] = dst[3][2] = 0.0f;
    dst[3][3] = 1.0f;
    return 1;
}

s32 func_80018544_main(HuMtx4F src, HuMtx4F dst) {
    HuMtx4F inv;

    if (!HmfInverseMtxF3X3(src, inv)) {
        guMtxIdentF(dst);
        return 0;
    }
    guMtxCatF(inv, src, dst);
    return 1;
}

void func_800185A4_main(HuMtx4F mtx, f32 angle) {
    f32 s = sindf(angle);
    f32 c = cosdf(angle);
    f32 row0[3];
    s32 i;

    for (i = 0; i < 3; i++) {
        row0[i] = mtx[0][i];
    }
    for (i = 0; i < 3; i++) {
        mtx[0][i] = c * row0[i] - s * mtx[2][i];
        mtx[2][i] = s * row0[i] + c * mtx[2][i];
    }
}

void func_8001866C_main(HuMtx4F mtx, f32 x, f32 y, f32 z) {
    HuMtx4F tmp;
    f32 sx, cx;
    f32 sy, cy;
    f32 sz, cz;
    f32 a, b, c;

    sincosdf(x, &sx, &cx);
    sincosdf(y, &sy, &cy);
    sincosdf(z, &sz, &cz);
    tmp[0][0] = mtx[0][0];
    tmp[0][1] = mtx[0][1];
    tmp[0][2] = mtx[0][2];
    tmp[0][3] = mtx[0][3];
    tmp[1][0] = mtx[1][0];
    tmp[1][1] = mtx[1][1];
    tmp[1][2] = mtx[1][2];
    tmp[1][3] = mtx[1][3];
    tmp[2][0] = mtx[2][0];
    tmp[2][1] = mtx[2][1];
    tmp[2][2] = mtx[2][2];
    tmp[2][3] = mtx[2][3];
    a = cx * sz;
    b = -cz * sy + cy * sx * sz;
    c = cy * cz + sx * sy * sz;
    mtx[0][0] = a * tmp[1][0] + b * tmp[2][0] + c * tmp[0][0];
    mtx[0][1] = a * tmp[1][1] + b * tmp[2][1] + c * tmp[0][1];
    mtx[0][2] = a * tmp[1][2] + b * tmp[2][2] + c * tmp[0][2];
    mtx[0][3] = a * tmp[1][3] + b * tmp[2][3] + c * tmp[0][3];
    a = cx * cz;
    b = cz * sx * sy - cy * sz;
    c = cy * cz * sx + sy * sz;
    mtx[1][0] = a * tmp[1][0] + b * tmp[0][0] + c * tmp[2][0];
    mtx[1][1] = a * tmp[1][1] + b * tmp[0][1] + c * tmp[2][1];
    mtx[1][2] = a * tmp[1][2] + b * tmp[0][2] + c * tmp[2][2];
    mtx[1][3] = a * tmp[1][3] + b * tmp[0][3] + c * tmp[2][3];
    a = cx * cy;
    b = cx * sy;
    mtx[2][0] = a * tmp[2][0] - tmp[1][0] * sx + b * tmp[0][0];
    mtx[2][1] = a * tmp[2][1] - tmp[1][1] * sx + b * tmp[0][1];
    mtx[2][2] = a * tmp[2][2] - tmp[1][2] * sx + b * tmp[0][2];
    mtx[2][3] = a * tmp[2][3] - tmp[1][3] * sx + b * tmp[0][3];
}

void func_80018978_main(HuMtx4F mtx, f32 x, f32 y, f32 z) {
    f32 sx, cx;
    f32 sy, cy;
    f32 sz, cz;

    sincosdf(x, &sx, &cx);
    sincosdf(y, &sy, &cy);
    sincosdf(z, &sz, &cz);
    mtx[0][0] = cy * cz + sx * sy * sz;
    mtx[1][0] = -cx * sz;
    mtx[2][0] = cz * sy + cy * sx * sz;
    mtx[0][1] = cz * sx * sy + cy * sz;
    mtx[1][1] = cx * cz;
    mtx[2][1] = -cy * cz * sx + sy * sz;
    mtx[0][2] = -cx * sy;
    mtx[1][2] = sx;
    mtx[2][2] = cx * cy;
    mtx[3][0] = mtx[3][1] = mtx[3][2] = mtx[0][3] = mtx[1][3] = mtx[2][3] = 0.0f;
    mtx[3][3] = 1.0f;
}

f32 InterpolateBMLine(f32 *value, f32 *time, f32 x) {
    f32 slope[2];
    f32 midTime, midValue, midSlope;
    f32 crossTime;
    f32 dx, b;
    f32 t0, t1, v0, v1, s0, s1;
    s32 crosses;
    s32 i;

    if (value[0] == value[1] && value[0] == value[2] && value[0] == value[3]) {
        return value[0];
    }
    for (i = 1; i < 3; i++) {
        slope[i - 1] = ((value[i] - value[i - 1]) / (time[i] - time[i - 1]) +
                        (value[i + 1] - value[i]) / (time[i + 1] - time[i])) *
                       0.5f;
    }
    midTime = (time[2] + time[1]) * 0.5f;
    crosses = FALSE;
    if (slope[1] - slope[0] != 0.0f) {
        crossTime = (slope[1] * time[2] - slope[0] * time[1] - (value[2] - value[1])) / (slope[1] - slope[0]);
        if (time[1] <= crossTime && crossTime <= time[2]) {
            crosses = TRUE;
        }
    }
    if (crosses == TRUE) {
        dx = midTime - time[1];
        b = (value[2] - value[1]) / (time[2] - time[1]) - (slope[1] - slope[0]) / 2.0f;
        midValue = (slope[1] - slope[0]) / ((time[2] - time[1]) * 2) * dx * dx + b * dx + value[1];
        midSlope = (slope[1] - slope[0]) / (time[2] - time[1]) * dx + b;
    } else {
        dx = midTime - time[1];
        midValue = (value[2] + value[1]) * (dx / (time[2] - time[1]));
        midSlope = (value[2] - value[1]) * 2 / (time[2] - time[1]) - (slope[1] + slope[0]) * (dx / (time[2] - time[1]));
    }
    if (x < midTime) {
        t0 = time[1];
        v0 = value[1];
        s0 = slope[0];
        t1 = midTime;
        v1 = midValue;
        s1 = midSlope;
    } else {
        t0 = midTime;
        v0 = midValue;
        s0 = midSlope;
        t1 = time[2];
        v1 = value[2];
        s1 = slope[1];
    }
    return (s1 - s0) / ((t1 - t0) * 2) * (x - t0) * (x - t0) + ((v1 - v0) / (t1 - t0) - (s1 - s0) / 2.0f) * (x - t0) + v0;
}

f32 func_80018D68_main(f32 mtx[3][3]) {
    f32 m10 = mtx[1][0], m11 = mtx[1][1], m12 = mtx[1][2];
    f32 m20 = mtx[2][0], m21 = mtx[2][1], m22 = mtx[2][2];

    return mtx[0][0] * (m11 * m22 - m12 * m21) +
           mtx[0][1] * (m12 * m20 - m10 * m22) +
           mtx[0][2] * (m10 * m21 - m11 * m20);
}

void func_80018DD8_main(f32 arg0[4][4], s32 arg1, s32 arg2, f32 arg3[3][3]) {
    s32 i, j, k, l;

    k = 0;
    for (i = 0; i < 4; i++) {
        if (i != arg1) {
            l = 0;
            for (j = 0; j < 4; j++) {
                if (j != arg2) {
                    arg3[k][l] = arg0[i][j];
                    l++;
                }
            }
            k++;
        }
    }
}

f32 func_80018E50_main(HuMtx4F mtx, s32 row, s32 col) {
    f32 minor[3][3];

    func_80018DD8_main(mtx, row, col, minor);
    return func_80018D68_main(minor);
}

f32 func_80018E74_main(HuMtx4F mtx) {
    f32 det = 0.0f;
    s32 i;

    for (i = 0; i < 4; i++) {
        s32 sign = (i != i / 2 * 2) ? -1 : 1;

        det += func_80018E50_main(mtx, 0, i) * mtx[0][i] * sign;
    }
    return det;
}

s32 func_80018F18_main(HuMtx4F src, HuMtx4F dst) {
    f32 det = func_80018E74_main(src);
    s32 i, j;

    if (det == 0.0f) {
        return 0;
    }
    det = 1.0f / det;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            s32 sign = i + j;

            sign = (sign != sign / 2 * 2) ? -1 : 1;

            dst[j][i] = func_80018E50_main(src, i, j) * det * sign;
        }
    }
    return 1;
}
