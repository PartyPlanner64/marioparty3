#include "humath.h"

// Tests whether a value lies within plus or minus a threshold.
s32 HuInRangeF(f32 value, f32 threshold) {
    return (-threshold <= value) & (value <= threshold);
}
