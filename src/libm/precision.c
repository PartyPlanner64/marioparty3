#include "libm.h"

void __libmSetPrecision(s32 precision) {
    f64 tolerance = 1.0;
    s32 i;

    if (precision < 1) {
        precision = 1;
    }
    if (precision > 15) {
        precision = 15;
    }
    for (i = 0; i < precision; i++) {
        tolerance /= 10.0;
    }
    __libmPrecision = tolerance;
}
