#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/saveEncode.h"
#include "macros.h"
#include "gcc/memory.h"

// Total number of bytes needed to hold the bits described by an encoding scheme.
#define SAVE_SCHEME_BYTE_SIZE(dest, scheme)              \
    {                                                    \
        u8 *_entry = (scheme);                           \
        s16 _bits = 0;                                   \
        s32 _bytes;                                      \
                                                         \
        while (*_entry != 0) {                           \
            _bits += _entry[0] * _entry[1];              \
            _entry += 3;                                 \
        }                                                \
        _bytes = _bits / 8;                              \
        (dest) = (_bits % 8 != 0) ? _bytes + 1 : _bytes; \
    }


extern u8 gEncodedSaveBuffer[220];

// Encoding schemes: { bit width, count, byte offset } tuples, terminated by a zero width.
static u8 D_800A1D70_main[] = {
    2, 1, 0x9F,
    2, 1, 0xA2,
    2, 1, 0x9E,
    2, 1, 0xA0,
    2, 1, 0xA1,
    8, 1, 0x00,
    3, 1, 0x01,
    8, 10, 0x94,
    8, 9, 0x16,
    8, 9, 0x8B,
    16, 10, 0x02,
    72, 6, 0x1F,
    72, 6, 0x55,
    0, 0, 0x00,
};

static u8 D_800A1D9C_main[] = {
    2, 1, 0x0F,
    2, 1, 0x04,
    3, 1, 0x00,
    3, 1, 0x01,
    3, 1, 0x05,
    3, 8, 0x06,
    7, 1, 0x02,
    7, 1, 0x03,
    8, 1, 0x10,
    8, 1, 0x11,
    8, 3, 0x5E,
    8, 1, 0x0E,
    16, 16, 0x3E,
    0, 0, 0x00,
};

static u8 D_800A1DC8_main[] = {
    2, 19, 0x2A,
    2, 1, 0x04,
    2, 1, 0x0F,
    3, 1, 0x00,
    3, 1, 0x01,
    3, 1, 0x05,
    3, 8, 0x06,
    7, 1, 0x02,
    7, 1, 0x03,
    8, 1, 0x10,
    8, 1, 0x11,
    6, 19, 0x17,
    8, 3, 0x5E,
    8, 1, 0x0E,
    16, 16, 0x3E,
    0, 0, 0x00,
};

static u8 D_800A1DF8_main[] = {
    2, 1, 0x02,
    2, 1, 0x1D,
    2, 1, 0x01,
    3, 1, 0x03,
    8, 1, 0x17,
    5, 1, 0x0F,
    5, 1, 0x10,
    5, 1, 0x11,
    5, 1, 0x12,
    8, 1, 0x13,
    8, 1, 0x14,
    5, 1, 0x15,
    5, 1, 0x16,
    7, 1, 0x0E,
    8, 1, 0x04,
    8, 1, 0x1B,
    8, 1, 0x1C,
    8, 3, 0x18,
    8, 1, 0x2C,
    8, 1, 0x2D,
    8, 1, 0x2E,
    8, 1, 0x2F,
    8, 1, 0x30,
    8, 1, 0x31,
    8, 1, 0x32,
    8, 1, 0x33,
    8, 1, 0x34,
    8, 1, 0x35,
    10, 1, 0x0A,
    16, 1, 0x2A,
    16, 1, 0x28,
    0, 0, 0x00,
};

static u8 D_800A1E58_main[] = {
    2, 1, 0x66,
    2, 6, 0x5E,
    3, 1, 0x65,
    3, 12, 0x67,
    3, 72, 0x10,
    4, 1, 0x73,
    4, 6, 0x58,
    4, 1, 0x64,
    0, 0, 0x00,
};

static s32 D_800BBAA0_main;
static s32 D_800BBAA4_main;
extern u16 D_800D04B0_main;
extern u16 D_800CBB64_main;
extern u16 D_800C9944_main;
extern u16 D_800CCF54_main;
extern u16 D_800CD6A4_main;
extern u16 D_800CE2C0_main;


// extern char D_800A7B40_main[];

void func_8004F290_main(void) {
    SAVE_SCHEME_BYTE_SIZE(D_800D04B0_main, D_800A1D70_main);
    SAVE_SCHEME_BYTE_SIZE(D_800CBB64_main, D_800A1D9C_main);
    SAVE_SCHEME_BYTE_SIZE(D_800C9944_main, D_800A1DC8_main);
    SAVE_SCHEME_BYTE_SIZE(D_800CCF54_main, D_800A1DF8_main);
    SAVE_SCHEME_BYTE_SIZE(D_800CD6A4_main, D_800A1E58_main);

    D_800CE2C0_main = D_800D04B0_main + (D_800CBB64_main + D_800CCF54_main * 4) +
                      (D_800C9944_main + D_800CCF54_main * 2) +
                      (D_800CD6A4_main + D_800C9944_main + D_800CCF54_main * 4);
}

s32 func_8004F504_main(GW_SYSTEM *system) {
    return SaveFileEncode((u8 *)system, D_800A1D9C_main);
}

s32 func_8004F524_main(GW_SYSTEM *system) {
    return SaveFileEncode((u8 *)system, D_800A1DC8_main);
}

s32 SavePlayerStruct(GW_PLAYER *player) {
    return SaveFileEncode((u8 *)player, D_800A1DF8_main);
}

s32 func_8004F564_main(GW_COMMON *common) {
    return SaveFileEncode((u8 *)common, D_800A1D70_main);
}

s32 func_8004F584_main(GW_STORY *story) {
    return SaveFileEncode((u8 *)story, D_800A1E58_main);
}

s32 SaveFileEncode(u8 *sourceData, u8 *encodingScheme) {
    s32 phi_s0;
    s16 phi_v1_2;
    u8 *currentDataPtr;
    s16 fieldIndex, byteIndex, bitIndex, schemeIndex;

    for (schemeIndex = 0; schemeIndex < ARRAY_COUNT(gEncodedSaveBuffer); schemeIndex++) {
        gEncodedSaveBuffer[schemeIndex] = 0;
    }

    D_800BBAA4_main = 0;
    D_800BBAA0_main = 0;

    while (*encodingScheme != 0) {
        currentDataPtr = (sourceData + encodingScheme[2]);
        for (fieldIndex = 0; fieldIndex < encodingScheme[1]; fieldIndex++) {
            if (encodingScheme[0] > 16) {
                for (byteIndex = 0; byteIndex < (encodingScheme[0] >> 3); byteIndex++, currentDataPtr++) {
                    phi_s0 = *currentDataPtr;
                    for (bitIndex = 0; bitIndex < 8; bitIndex++, phi_s0 *= 2) {
                        func_8004F83C_main(phi_s0 & 0x80);
                    }
                }
                continue;
            } else {
                if (encodingScheme[0] > 8) {
                    phi_s0 = *currentDataPtr << (16 - encodingScheme[0]);
                    phi_v1_2 = encodingScheme[0] - 8;
                    for (bitIndex = 0; bitIndex < phi_v1_2; bitIndex++, phi_s0 *= 2) {
                        func_8004F83C_main(phi_s0 & 0x80);
                    }
                    currentDataPtr++;
                    phi_s0 = *currentDataPtr;
                    phi_v1_2 = 8;
                } else {
                    phi_s0 = *currentDataPtr << (8 - encodingScheme[0]);
                    phi_v1_2 = encodingScheme[0];
                }
                for (bitIndex = 0; bitIndex < phi_v1_2; bitIndex++, phi_s0 *= 2) {
                    func_8004F83C_main(phi_s0 & 0x80);
                }
            }
            currentDataPtr++;
        }
        encodingScheme += 3; // advance to next encoding tuplet
    }

    gEncodedSaveBuffer[D_800BBAA0_main] <<= 8 - D_800BBAA4_main;
    if (D_800BBAA4_main == 0) {
        D_800BBAA0_main--;
    }
    if (D_800BBAA0_main > ARRAY_COUNT(gEncodedSaveBuffer)) {
        osSyncPrintf("SaveCompBuffer Max Over!\n");
    }
    return D_800BBAA0_main + 1;
}

void func_8004F83C_main(s32 arg0) {
    gEncodedSaveBuffer[D_800BBAA0_main] *= 2;
    gEncodedSaveBuffer[D_800BBAA0_main] |= arg0 ? 1 : 0;

    if (++D_800BBAA4_main >= 8) {
        D_800BBAA0_main++;
        D_800BBAA4_main = 0;
    }
}

// Only the first 0x62 bytes of GwSystem are saved.
void func_8004F8BC_main(u8 *src, GW_SYSTEM *system) {
    memset(system, 0, 0x62);
    func_8004FA4C_main(src, (u8 *)system, D_800A1D9C_main);
}

void func_8004F90C_main(u8 *src, GW_SYSTEM *system) {
    memset(system, 0, 0x62);
    func_8004FA4C_main(src, (u8 *)system, D_800A1DC8_main);
}

void func_8004F95C_main(u8 *src, GW_PLAYER *player) {
    memset(player, 0, sizeof(GW_PLAYER));
    func_8004FA4C_main(src, (u8 *)player, D_800A1DF8_main);
}

void func_8004F9AC_main(u8 *src, GW_COMMON *common) {
    memset(common, 0, sizeof(GW_COMMON));
    func_8004FA4C_main(src, (u8 *)common, D_800A1D70_main);
}

void func_8004F9FC_main(u8 *src, GW_STORY *story) {
    memset(story, 0, sizeof(GW_STORY));
    func_8004FA4C_main(src, (u8 *)story, D_800A1E58_main);
}

void func_8004FA4C_main(u8 *src, u8 *destData, u8 *encodingScheme) {
    u8 *currentDataPtr;
    u8 value;
    s16 bitCount;
    s16 fieldIndex, byteIndex, bitIndex, i;

    for (i = 0; i < ARRAY_COUNT(gEncodedSaveBuffer); i++) {
        gEncodedSaveBuffer[i] = *src++;
    }

    D_800BBAA4_main = 0;
    D_800BBAA0_main = 0;

    while (*encodingScheme != 0) {
        currentDataPtr = destData + encodingScheme[2];
        for (fieldIndex = 0; fieldIndex < encodingScheme[1]; fieldIndex++) {
            if (encodingScheme[0] > 16) {
                for (byteIndex = 0; byteIndex < (encodingScheme[0] >> 3); byteIndex++) {
                    value = 0;
                    for (bitIndex = 0; bitIndex < 8; bitIndex++) {
                        value = (value << 1) | (func_8004FC84_main() ? 1 : 0);
                    }
                    *currentDataPtr++ = value;
                }
            } else {
                if (encodingScheme[0] > 8) {
                    value = 0;
                    bitCount = encodingScheme[0] - 8;
                    for (bitIndex = 0; bitIndex < bitCount; bitIndex++) {
                        value = (value << 1) | (func_8004FC84_main() ? 1 : 0);
                    }
                    *currentDataPtr++ = value;
                    bitCount = 8;
                } else {
                    bitCount = encodingScheme[0];
                }
                value = 0;
                for (bitIndex = 0; bitIndex < bitCount; bitIndex++) {
                    value = (value << 1) | (func_8004FC84_main() ? 1 : 0);
                }
                *currentDataPtr++ = value;
            }
        }
        encodingScheme += 3;
    }
}

s32 func_8004FC84_main(void) {
    s32 topBit = gEncodedSaveBuffer[D_800BBAA0_main] & 0x80;

    gEncodedSaveBuffer[D_800BBAA0_main] <<= 1;
    if (++D_800BBAA4_main >= 8) {
        D_800BBAA0_main++;
        D_800BBAA4_main = 0;
    }
    return topBit;
}
