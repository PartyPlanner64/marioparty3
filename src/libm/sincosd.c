#include "libm.h"

void sincosd(f64 angle, f64 *sine, f64 *cosine) {
    *sine = sind(angle);
    *cosine = HuSqrt(1.0 - *sine * *sine) * __cosSign;
}
