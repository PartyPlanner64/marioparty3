#include "humath.h"

// Apply scale to a fixed-point matrix.
void HuMtxScaleCat(Mtx *src, f32 *scale, Mtx *dst) {
    HuMtx4F temp;

    HuMtxL2F(temp, src);
    HuMtxScaleCatF(temp, scale, temp);
    HuMtxF2L(temp, dst);
}
