#include "humath.h"

// Builds a fixed-point perspective matrix from field-of-view and clip parameters.
void HuPerspective(Mtx *m, u16 *perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale) {
    HuMtx4F temp;

    HuPerspectiveF(temp, perspNorm, fovy, aspect, near, far, scale);
    HuMtxF2L(temp, m);
}
