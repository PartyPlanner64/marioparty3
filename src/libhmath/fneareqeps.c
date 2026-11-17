#include "humath.h"

// Tests whether two values are approximately equal using global epsilon.
s32 HuNearEqEpsF(f32 a, f32 b) {
    return HuInRangeEpsF(a - b);
}
