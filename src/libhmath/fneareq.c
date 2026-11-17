#include "humath.h"

// Tests whether two values are approximately equal.
s32 HuNearEqF(f32 a, f32 b, f32 threshold) {
    return HuInRangeF(a - b, threshold);
}
