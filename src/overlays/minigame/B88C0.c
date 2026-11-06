#include "common.h"

extern u32 D_800EB900_minigame;

u32 func_800E5D40_minigame(u32 seed) {
    u32 quotient;
    u32 remainder;

    if (seed == 0) {
        seed = rand8();
        seed ^= osGetCount();
        seed ^= 0xD826BC89;
    }
    quotient = seed / 127773;
    remainder = seed - quotient * 127773;
    seed = quotient * 2836;
    return seed - remainder * 16807;
}

u32 func_800E5E14_minigame(void) {
    D_800EB900_minigame = func_800E5D40_minigame(D_800EB900_minigame);
    return D_800EB900_minigame;
}

u32 func_800E5E3C_minigame(u32 max) {
    u32 value;

    value = func_800E5D40_minigame(D_800EB900_minigame);
    D_800EB900_minigame = value;
    return (value & 0x7FFFFFFF) % max;
}
