#include "humath.h"

// Builds a fixed-point look-at matrix using the floating-point implementation.
void HuLookAt(Mtx *m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp) {
    HuMtx4F temp;

    HuLookAtF(temp, xEye, yEye, zEye, xAt, yAt, zAt, xUp, yUp, zUp);
    HuMtxF2L(temp, m);
}
