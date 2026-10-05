#include "common.h"
#include "stdlib.h"

ldiv_t ldiv(long num, long denom) {
    ldiv_t res;

    res.quot = num / denom;
    res.rem = num - res.quot * denom;

    if (res.quot < 0 && res.rem > 0) {
        res.quot += 1;
        res.rem -= denom;
    }

    return res;
}

INCLUDE_ASM("asm/nonmatchings/2.0L/libc/ldiv", lldiv);
