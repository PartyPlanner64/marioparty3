#include "humath.h"

// Build a fixed-point perspective matrix.
void HuMtxPerspective(Mtx *mtx, u16 *perspNorm, PerspectiveParams *params) {
    HuMtx4F temp;

    HuMtxPerspectiveF(temp, perspNorm, params);
    HuMtxF2L(temp, mtx);
}
