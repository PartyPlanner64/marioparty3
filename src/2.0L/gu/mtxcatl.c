#include "common.h"

void func_8007E040_main(Mtx *m, Mtx *n, Mtx *res) {
    float lm[4][4];
    float ln[4][4];
    float lres[4][4];

    guMtxL2F(lm, m);
    guMtxL2F(ln, n);
    guMtxCatF(lm, ln, lres);
    guMtxF2L(lres, res);
}
