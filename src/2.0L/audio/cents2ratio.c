#include "common.h"

/* Returns the pitch ratio for a shift of `cents`, i.e. 2^(cents/1200). The
 * factor for a single cent is applied by squaring it once per bit of the
 * shift count, so only the low bits of the count need to be looked at. */
f32 alCents2Ratio(s32 cents) {
    f32 step;
    f32 ratio = 1.0f;

    if (cents >= 0) {
        step = 1.00057779f; /* 2^(1/1200) */
    } else {
        step = 0.9994225441f; /* 2^(-1/1200) */
        cents = -cents;
    }

    while (cents) {
        if (cents & 1) {
            ratio *= step;
        }
        step *= step;
        cents >>= 1;
    }

    return ratio;
}
