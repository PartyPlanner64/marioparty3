#include "humath.h"

// Keep separate negated comparisons to reject NaNs and preserve the matching branches.
// Vec3 near-equal test with an explicit epsilon.
s32 HuVecNearEq(Vec *a, Vec *b, f32 epsilon) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 negEpsilon;

    negEpsilon = -epsilon;
    dx = a->x - b->x;
    if (!(negEpsilon <= dx)) {
        return FALSE;
    }
    if (!(dx <= epsilon)) {
        return FALSE;
    }
    dy = a->y - b->y;
    if (!(negEpsilon <= dy)) {
        return FALSE;
    }
    if (!(dy <= epsilon)) {
        return FALSE;
    }
    dz = a->z - b->z;
    if (!(negEpsilon <= dz)) {
        return FALSE;
    }
    if (!(dz <= epsilon)) {
        return FALSE;
    }
    return TRUE;
}

// Vec3 near-equal test using the default epsilon.
s32 HuVecNearEqEps(Vec *a, Vec *b) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 epsilon;
    f32 negEpsilon;

    epsilon = HuMathEpsilon;
    negEpsilon = -epsilon;
    dx = a->x - b->x;
    if (!(negEpsilon <= dx)) {
        return FALSE;
    }
    if (!(dx <= epsilon)) {
        return FALSE;
    }
    dy = a->y - b->y;
    if (!(negEpsilon <= dy)) {
        return FALSE;
    }
    if (!(dy <= epsilon)) {
        return FALSE;
    }
    dz = a->z - b->z;
    if (!(negEpsilon <= dz)) {
        return FALSE;
    }
    if (!(dz <= epsilon)) {
        return FALSE;
    }
    return TRUE;
}

// Look-at convenience wrapper using a stack scratch buffer.
void HuMtxLookAtF(HuMtx4F mtx, Vec *camera) {
    Vec basis[3];

    HuMtxLookAtBasisF(mtx, camera, basis);
}
