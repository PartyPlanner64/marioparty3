#include "guint.h"
#include "math.h"

void guRotateF(float mf[4][4], float a, float x, float y, float z) {
    float sine;
    float cosine;
    float ab, bc, ca, t;
    float xs, ys, zs;
    static float dtor = 3.1415926 / 180.0;

    guNormalize(&x, &y, &z);
    a *= dtor;
    sine = sinf(a);
    cosine = cosf(a);
    t = (1 - cosine);
    ab = x * y * t;
    bc = y * z * t;
    ca = z * x * t;

    guMtxIdentF(mf);

    xs = x * sine;
    ys = y * sine;
    zs = z * sine;

    t = x * x;
    mf[0][0] = t + cosine * (1 - t);
    mf[2][1] = bc - xs;
    mf[1][2] = bc + xs;

    t = y * y;
    mf[1][1] = t + cosine * (1 - t);
    mf[2][0] = ca + ys;
    mf[0][2] = ca - ys;

    t = z * z;
    mf[2][2] = t + cosine * (1 - t);
    mf[1][0] = ab - zs;
    mf[0][1] = ab + zs;
}

void guRotate(Mtx *m, float a, float x, float y, float z) {
    Matrix mf;

    guRotateF(mf, a, x, y, z);

    guMtxF2L(mf, m);
}
