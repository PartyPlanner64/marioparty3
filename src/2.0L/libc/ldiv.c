#include "common.h"
#include "stdlib.h"

ldiv_t ldiv(long num, long den) {
    ldiv_t rval;

    rval.quot = num / den;
    rval.rem = num - den * rval.quot;
    if (rval.quot < 0 && rval.rem > 0) {
        rval.quot++;
        rval.rem -= den;
    }
    return rval;
}

lldiv_t lldiv(long long num, long long den) {
    lldiv_t rval;

    rval.quot = num / den;
    rval.rem = num - den * rval.quot;
    if (rval.quot < 0 && rval.rem > 0) {
        rval.quot++;
        rval.rem -= den;
    }
    return rval;
}
