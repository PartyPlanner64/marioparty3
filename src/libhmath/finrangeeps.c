#include "humath.h"

// Tests whether a value lies within the global epsilon threshold.
s32 HuInRangeEpsF(f32 value) {
    return (-HuMathEpsilon <= value) && (value <= HuMathEpsilon);
}
