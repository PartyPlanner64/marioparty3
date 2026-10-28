#include "common.h"

extern s32 D_800A3FA8_main; // osViClock

s32 osAiSetFrequency(u32 frequency) {
    register unsigned int dacRate;
    register u8 bitRate;
    register float f;

    f = D_800A3FA8_main / (float)frequency + .5f;
    dacRate = f;
    if (dacRate < AI_MIN_DAC_RATE) {
        return -1;
    }

    bitRate = dacRate / 66;
    if (bitRate > AI_MAX_BIT_RATE) {
        bitRate = AI_MAX_BIT_RATE;
    }

    IO_WRITE(AI_DACRATE_REG, dacRate - 1);
    IO_WRITE(AI_BITRATE_REG, bitRate - 1);
    return D_800A3FA8_main / (s32)dacRate;
}
