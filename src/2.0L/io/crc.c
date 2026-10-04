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

u8 __osContDataCrc(u8 *dataptr, u32 size) {
    u32 crc;
    u32 bitmask;
    u32 count;
    u32 byte;

    crc = 0;
    for (count = 0x20; count != 0; count--) {
        bitmask = 0x80;
        byte = *dataptr;
        do {
            crc <<= 1;
            if (byte & bitmask) {
                if (crc & 0x100) {
                    crc ^= 0x84;
                } else {
                    crc += 1;
                }
            } else if (crc & 0x100) {
                crc ^= 0x85;
            }
        } while (bitmask >>= 1);
        dataptr++;
    }

    do {
        crc <<= 1;
        if (crc & 0x100) {
            crc ^= 0x85;
        }
        count++;
    } while (count < 8);

    return crc & 0xFF;
}
