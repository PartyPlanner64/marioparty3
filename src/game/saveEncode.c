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
static u8 saveCommonScheme[] = {
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

static u8 saveBoardSystemScheme[] = {
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

static u8 saveStorySystemScheme[] = {
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

static u8 savePlayerScheme[] = {
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

static u8 saveStoryScheme[] = {
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

static s32 saveBitByte;
static s32 saveBitPos;
extern u16 saveCommonSize;
extern u16 saveBoardSystemSize;
extern u16 saveStorySystemSize;
extern u16 savePlayerSize;
extern u16 saveStorySize;
extern u16 saveChecksumOfs;


// extern char D_800A7B40_main[];

void SaveSchemeInit(void) {
    SAVE_SCHEME_BYTE_SIZE(saveCommonSize, saveCommonScheme);
    SAVE_SCHEME_BYTE_SIZE(saveBoardSystemSize, saveBoardSystemScheme);
    SAVE_SCHEME_BYTE_SIZE(saveStorySystemSize, saveStorySystemScheme);
    SAVE_SCHEME_BYTE_SIZE(savePlayerSize, savePlayerScheme);
    SAVE_SCHEME_BYTE_SIZE(saveStorySize, saveStoryScheme);

    saveChecksumOfs = saveCommonSize + (saveBoardSystemSize + savePlayerSize * 4) +
                      (saveStorySystemSize + savePlayerSize * 2) +
                      (saveStorySize + saveStorySystemSize + savePlayerSize * 4);
}

s32 SaveBoardSystemEncode(GW_SYSTEM *system) {
    return SaveFileEncode((u8 *)system, saveBoardSystemScheme);
}

s32 SaveStorySystemEncode(GW_SYSTEM *system) {
    return SaveFileEncode((u8 *)system, saveStorySystemScheme);
}

s32 SavePlayerStruct(GW_PLAYER *player) {
    return SaveFileEncode((u8 *)player, savePlayerScheme);
}

s32 SaveCommonEncode(GW_COMMON *common) {
    return SaveFileEncode((u8 *)common, saveCommonScheme);
}

s32 SaveStoryEncode(GW_STORY *story) {
    return SaveFileEncode((u8 *)story, saveStoryScheme);
}

s32 SaveFileEncode(u8 *sourceData, u8 *encodingScheme) {
    s32 phi_s0;
    s16 phi_v1_2;
    u8 *currentDataPtr;
    s16 fieldIndex, byteIndex, bitIndex, schemeIndex;

    for (schemeIndex = 0; schemeIndex < ARRAY_COUNT(gEncodedSaveBuffer); schemeIndex++) {
        gEncodedSaveBuffer[schemeIndex] = 0;
    }

    saveBitPos = 0;
    saveBitByte = 0;

    while (*encodingScheme != 0) {
        currentDataPtr = (sourceData + encodingScheme[2]);
        for (fieldIndex = 0; fieldIndex < encodingScheme[1]; fieldIndex++) {
            if (encodingScheme[0] > 16) {
                for (byteIndex = 0; byteIndex < (encodingScheme[0] >> 3); byteIndex++, currentDataPtr++) {
                    phi_s0 = *currentDataPtr;
                    for (bitIndex = 0; bitIndex < 8; bitIndex++, phi_s0 *= 2) {
                        SaveBitWrite(phi_s0 & 0x80);
                    }
                }
                continue;
            } else {
                if (encodingScheme[0] > 8) {
                    phi_s0 = *currentDataPtr << (16 - encodingScheme[0]);
                    phi_v1_2 = encodingScheme[0] - 8;
                    for (bitIndex = 0; bitIndex < phi_v1_2; bitIndex++, phi_s0 *= 2) {
                        SaveBitWrite(phi_s0 & 0x80);
                    }
                    currentDataPtr++;
                    phi_s0 = *currentDataPtr;
                    phi_v1_2 = 8;
                } else {
                    phi_s0 = *currentDataPtr << (8 - encodingScheme[0]);
                    phi_v1_2 = encodingScheme[0];
                }
                for (bitIndex = 0; bitIndex < phi_v1_2; bitIndex++, phi_s0 *= 2) {
                    SaveBitWrite(phi_s0 & 0x80);
                }
            }
            currentDataPtr++;
        }
        encodingScheme += 3; // advance to next encoding tuplet
    }

    gEncodedSaveBuffer[saveBitByte] <<= 8 - saveBitPos;
    if (saveBitPos == 0) {
        saveBitByte--;
    }
    if (saveBitByte > ARRAY_COUNT(gEncodedSaveBuffer)) {
        osSyncPrintf("SaveCompBuffer Max Over!\n");
    }
    return saveBitByte + 1;
}

void SaveBitWrite(s32 arg0) {
    gEncodedSaveBuffer[saveBitByte] *= 2;
    gEncodedSaveBuffer[saveBitByte] |= arg0 ? 1 : 0;

    if (++saveBitPos >= 8) {
        saveBitByte++;
        saveBitPos = 0;
    }
}

// Only the first 0x62 bytes of GwSystem are saved.
void SaveBoardSystemDecode(u8 *src, GW_SYSTEM *system) {
    memset(system, 0, 0x62);
    SaveFileDecode(src, (u8 *)system, saveBoardSystemScheme);
}

void SaveStorySystemDecode(u8 *src, GW_SYSTEM *system) {
    memset(system, 0, 0x62);
    SaveFileDecode(src, (u8 *)system, saveStorySystemScheme);
}

void SavePlayerDecode(u8 *src, GW_PLAYER *player) {
    memset(player, 0, sizeof(GW_PLAYER));
    SaveFileDecode(src, (u8 *)player, savePlayerScheme);
}

void SaveCommonDecode(u8 *src, GW_COMMON *common) {
    memset(common, 0, sizeof(GW_COMMON));
    SaveFileDecode(src, (u8 *)common, saveCommonScheme);
}

void SaveStoryDecode(u8 *src, GW_STORY *story) {
    memset(story, 0, sizeof(GW_STORY));
    SaveFileDecode(src, (u8 *)story, saveStoryScheme);
}

void SaveFileDecode(u8 *src, u8 *destData, u8 *encodingScheme) {
    u8 *currentDataPtr;
    u8 value;
    s16 bitCount;
    s16 fieldIndex, byteIndex, bitIndex, i;

    for (i = 0; i < ARRAY_COUNT(gEncodedSaveBuffer); i++) {
        gEncodedSaveBuffer[i] = *src++;
    }

    saveBitPos = 0;
    saveBitByte = 0;

    while (*encodingScheme != 0) {
        currentDataPtr = destData + encodingScheme[2];
        for (fieldIndex = 0; fieldIndex < encodingScheme[1]; fieldIndex++) {
            if (encodingScheme[0] > 16) {
                for (byteIndex = 0; byteIndex < (encodingScheme[0] >> 3); byteIndex++) {
                    value = 0;
                    for (bitIndex = 0; bitIndex < 8; bitIndex++) {
                        value = (value << 1) | (SaveBitRead() ? 1 : 0);
                    }
                    *currentDataPtr++ = value;
                }
            } else {
                if (encodingScheme[0] > 8) {
                    value = 0;
                    bitCount = encodingScheme[0] - 8;
                    for (bitIndex = 0; bitIndex < bitCount; bitIndex++) {
                        value = (value << 1) | (SaveBitRead() ? 1 : 0);
                    }
                    *currentDataPtr++ = value;
                    bitCount = 8;
                } else {
                    bitCount = encodingScheme[0];
                }
                value = 0;
                for (bitIndex = 0; bitIndex < bitCount; bitIndex++) {
                    value = (value << 1) | (SaveBitRead() ? 1 : 0);
                }
                *currentDataPtr++ = value;
            }
        }
        encodingScheme += 3;
    }
}

s32 SaveBitRead(void) {
    s32 topBit = gEncodedSaveBuffer[saveBitByte] & 0x80;

    gEncodedSaveBuffer[saveBitByte] <<= 1;
    if (++saveBitPos >= 8) {
        saveBitByte++;
        saveBitPos = 0;
    }
    return topBit;
}
