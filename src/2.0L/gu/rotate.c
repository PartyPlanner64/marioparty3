#include "guint.h"
#include "math.h"

/* The static `dtor` of guRotateF; the .data of this file is not split out yet. */
extern float D_800A3F80_main;

/* guRotateF */
void func_8007E0C0_main(float mf[4][4], float a, float x, float y, float z) {
    float sine;
    float cosine;
    float ab, bc, ca, t;
    float xs, ys, zs;

    guNormalize(&x, &y, &z);
    a *= D_800A3F80_main;
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

/* guRotate */
void func_8007E220_main(Mtx *m, float a, float x, float y, float z) {
    Matrix mf;

    func_8007E0C0_main(mf, a, x, y, z);

    guMtxF2L(mf, m);
}
