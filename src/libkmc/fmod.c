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

double fmod(f64 x, f64 y) {
    if (y == 0.0) {
        return 0.0;
    }
    return x - __fint(x / y) * y;
}

double ceil(f64 x) {
    f64 t = __fint(x);

    if ((x >= 0.0) & (t != x)) {
        return t + 1.0;
    }
    return t;
}

INCLUDE_ASM("asm/nonmatchings/libkmc/fmod", floor);
