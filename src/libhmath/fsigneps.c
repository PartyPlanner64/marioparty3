#include "humath.h"

// Returns the sign of a value using the global epsilon threshold.
s32 HuSignEpsF(f32 value) {
    if (value < -HuMathEpsilon) {
        return -1;
    }
    if (HuMathEpsilon < value) {
        return 1;
    }
    return 0;
}
