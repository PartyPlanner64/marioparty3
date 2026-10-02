#include "common.h"

u16 __osContAddressCrc(u16 address) {
    u32 crc;
    u32 bitmask;

    crc = 0;
    for (bitmask = 0x400; bitmask != 0; bitmask >>= 1) {
        if (address & bitmask) {
            crc <<= 1;
            if (crc & 0x20) {
                crc ^= 0x14;
            } else {
                crc += 1;
            }
        } else {
            crc <<= 1;
            if (crc & 0x20) {
                crc ^= 0x15;
            }
        }
    }

    for (bitmask = 5; bitmask != 0; bitmask--) {
        crc <<= 1;
        if (crc & 0x20) {
            crc ^= 0x15;
        }
    }

    return crc & 0x1F;
}

INCLUDE_ASM("asm/nonmatchings/2.0L/io/crc", __osContDataCrc);
