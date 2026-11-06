#include "common.h"

static u32 xseed = 174823885;

int guRandom(void) {
    u32 t0 = xseed * 4;
    u32 t1 = t0 + 2;
    t0 += 3;
    return xseed = (t1 * t0) >> 2;
}
