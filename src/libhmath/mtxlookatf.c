#include "humath.h"

// Look-at convenience wrapper using a stack scratch buffer.
void HuMtxLookAtF(HuMtx4F mtx, Vec *camera) {
    Vec basis[3];

    HuMtxLookAtBasisF(mtx, camera, basis);
}
