#include "humath.h"

// Build a fixed-point look-at matrix.
void HuMtxLookAt(Mtx *mtx, Vec *camera) {
    HuMtx4F temp;
    Vec basis[3];

    HuMtxLookAtBasisF(temp, camera, basis);
    HuMtxF2L(temp, mtx);
}
