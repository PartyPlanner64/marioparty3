#include "common.h"
#include "game/overlays/minigame.h"

u32 mgRandSeed = 0;

u32 MgRandSeedCalc(u32 seed) {
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

u32 MgRand(void) {
    mgRandSeed = MgRandSeedCalc(mgRandSeed);
    return mgRandSeed;
}

u32 MgRandMod(u32 max) {
    u32 value;

    value = MgRandSeedCalc(mgRandSeed);
    mgRandSeed = value;
    return (value & 0x7FFFFFFF) % max;
}
