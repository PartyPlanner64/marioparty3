#include "common.h"

typedef union {
    f64 d;
    u64 u;
    u32 hi;
} f64bits;

double __fint(f64 x) {
    f64bits v;
    s32 e;

    v.d = x;
    e = (s32)((v.hi >> 20) & 0x7FF) - 0x3FF;
    if (e < 0) {
        return 0.0;
    }
    v.u &= (-1LL << 63) >> (e + 11);
    return v.d;
}

INCLUDE_ASM("asm/nonmatchings/libkmc/fmod", fmod);

INCLUDE_ASM("asm/nonmatchings/libkmc/fmod", ceil);

INCLUDE_ASM("asm/nonmatchings/libkmc/fmod", floor);
