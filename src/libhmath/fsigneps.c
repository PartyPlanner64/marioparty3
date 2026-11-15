#include "humath.h"

// Returns the sign of a value using the global epsilon threshold.
s32 func_800897D0_main(f32 value) {
    if (value < -mainUnkF32) {
        return -1;
    }
    if (mainUnkF32 < value) {
        return 1;
    }
    return 0;
}
