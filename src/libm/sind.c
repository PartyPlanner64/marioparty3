#include "libm.h"

f64 __cosSign;

f64 sind(f64 angle) {
    f64 term = 1;
    f64 wholeAngle;
    s32 index;
    s32 sign;
    f64 fraction;
    f64 sinTbl;
    f64 cosTbl;
    f64 result;
    s32 toggle;
    s32 termIndex;
    s32 termsRemaining;

    toggle = 1;
    sign = 0;
    wholeAngle = angle * 0.00277777777777777788;
    index = (s32)wholeAngle;
    angle -= (f64)(index * 360);
    if (angle < 0.0) {
        angle += 360.0;
    }

    if (angle < 90.0 || 270.0 < angle) {
        __cosSign = 1.0;
    } else {
        __cosSign = -1.0;
    }

    if (180.0 < angle) {
        sign = 1;
        angle -= 180.0;
    }
    if (90.0 < angle) {
        angle = 180.0 - angle;
    }

    fraction = angle + 0.5;
    index = (s32)fraction;
    wholeAngle = (f64)index;
    index = (s32)wholeAngle;
    fraction = angle - wholeAngle;
    fraction *= M_DTOR;

    sinTbl = __sinTbl[index];
    result = sinTbl;
    cosTbl = __sinTbl[90 - index];

    termsRemaining = 8;
    termIndex = 0;
    do {
        term = __invFactTbl[9 - termsRemaining] * (term * fraction);
        if (-__libmPrecision <= term && term <= __libmPrecision) {
            break;
        }
        if (toggle) {
            wholeAngle = __sinCosSignTbl[termIndex] ? term * cosTbl : -term * cosTbl;
            result += wholeAngle;
            toggle = 0;
        } else {
            wholeAngle = __sinCosSignTbl[termIndex] ? term * sinTbl : -term * sinTbl;
            result += wholeAngle;
            toggle = 1;
        }
        termIndex++;
    } while (--termsRemaining > 0);

    if (sign) {
        wholeAngle = -result;
    } else {
        wholeAngle = result;
    }
    return wholeAngle;
}
