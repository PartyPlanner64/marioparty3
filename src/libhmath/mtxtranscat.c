#include "humath.h"

// Apply translation to a fixed-point matrix.
void HuMtxTransCat(Mtx *src, f32 *translation, Mtx *dst) {
    HuMtx4F temp;

    HuMtxL2F(temp, src);
    HuMtxTransCatF(temp, translation, temp);
    HuMtxF2L(temp, dst);
}
