#include "guint.h"
#include "math.h"

/* The static `dtor` of guRotateRPYF; the .data of this file is not split out yet. */
extern float D_800A2D70_main;

/* guRotateRPYF */
void func_8007B210_main(float mf[4][4], float r, float p, float h) {
    float sinr, sinp, sinh;
    float cosr, cosp, cosh;

    r *= D_800A2D70_main;
    p *= D_800A2D70_main;
    h *= D_800A2D70_main;
    sinr = sinf(r);
    cosr = cosf(r);
    sinp = sinf(p);
    cosp = cosf(p);
    sinh = sinf(h);
    cosh = cosf(h);

    guMtxIdentF(mf);

    mf[0][0] = cosp * cosh;
    mf[0][1] = cosp * sinh;
    mf[0][2] = -sinp;

    mf[1][0] = sinr * sinp * cosh - cosr * sinh;
    mf[1][1] = sinr * sinp * sinh + cosr * cosh;
    mf[1][2] = sinr * cosp;

    mf[2][0] = cosr * sinp * cosh + sinr * sinh;
    mf[2][1] = cosr * sinp * sinh - sinr * cosh;
    mf[2][2] = cosr * cosp;
}

/* guRotateRPY */
void func_8007B398_main(Mtx *m, float r, float p, float h) {
    Matrix mf;

    func_8007B210_main(mf, r, p, h);

    guMtxF2L(mf, m);
}
