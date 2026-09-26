#include "common.h"

extern u32 D_800A2D60_main;

u32 func_8007B1E0_main(void) {
    u32 t0 = D_800A2D60_main * 4;
    u32 t1 = t0 + 2;
    t0 += 3;
    return D_800A2D60_main = (t1 * t0) >> 2;
}
