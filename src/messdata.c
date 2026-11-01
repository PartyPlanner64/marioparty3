#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/messdata.h"
#include "game/malloc.h"
#include "game/rom.h"
#include "game/decode.h"

// string table parsing code.

static u32 D_800B1A40_main;  // strings ROM pointer
static s32 D_800B1A44_main;  // string directory count
static u32 *D_800B1A48_main; // string directory table
static s32 D_800B1A4C_main;  // string directory table size

void func_80036380_main(u32 stringsRomPtr) {
    s32 stringDirTableSize;
    u32 *stringDirTable;
    u32 *stringsHeader;

    D_800B1A40_main = stringsRomPtr;
    stringsHeader = HuMemMemoryAllocPerm(16);
    dmaRead(stringsRomPtr, (u8 *)stringsHeader, 16);
    D_800B1A44_main = *stringsHeader;
    HuMemMemoryFreePerm(stringsHeader);
    stringDirTableSize = D_800B1A44_main * 4;
    D_800B1A4C_main = stringDirTableSize;
    stringDirTable = HuMemMemoryAllocPerm(stringDirTableSize);
    D_800B1A48_main = stringDirTable;
    dmaRead(stringsRomPtr + 4, (u8 *)stringDirTable, D_800B1A4C_main);
}

void func_80036414_main(u32 ptr) {
    D_800B1A40_main = ptr;
    dmaRead(ptr + 4, (u8 *)D_800B1A48_main, D_800B1A4C_main);
}

struct str80036448 {
    u32 unk0;
    s32 unk4; // decompressed size
    s32 unk8; // compression type
};

struct string_dir_header {
    s32 decompressedSize;
    s32 compressionType;
};

struct string_entry {
    s16 length;
    u8 text[1];
};

void func_80036448_main(s32 arg0, struct str80036448 *arg1) {
    u32 temp_a0;
    struct string_dir_header *dirHeader;

    dirHeader = HuMemMemoryAllocPerm(16);
    temp_a0 = D_800B1A40_main + D_800B1A48_main[arg0];
    arg1->unk0 = temp_a0;
    dmaRead(temp_a0, (u8 *)dirHeader, 16);
    arg1->unk0 = arg1->unk0 + 8;
    arg1->unk4 = dirHeader->decompressedSize;
    arg1->unk8 = dirHeader->compressionType;
    HuMemMemoryFreePerm(dirHeader);
}

// Reads a message by id. The upper bits select the string directory,
// and the low byte is the index of the message within that directory.
// TODO: the message id is passed as a pointer to match the existing prototype.
void *func_800364DC_main(void *arg0) {
    s32 messageId = (s32)arg0;
    struct str80036448 dirInfo;
    u8 *dirData;
    s32 *offsets;
    struct string_entry *entry;
    u8 *text;
    s16 length;
    s32 i;

    func_80036448_main(messageId >> 8, &dirInfo);
    text = NULL;
    dirData = HuMemMemoryAllocPerm((dirInfo.unk4 + 1) & ~1);
    if (dirData != NULL) {
        DecodeData(dirInfo.unk0, dirData, dirInfo.unk4, dirInfo.unk8);
        entry = (struct string_entry *)(dirData + 4);
        for (i = 0; i < (messageId & 0xFF); i++) {
            entry = (struct string_entry *)((s32 *)entry + 1);
        }
        entry = (struct string_entry *)(dirData + *(s32 *)entry);
        length = entry->length;
        text = HuMemMemoryAllocPerm(length);
        if (text != NULL) {
            for (i = 0; i < length; i++) {
                text[i] = entry->text[i];
            }
        }
        HuMemMemoryFreePerm(dirData);
    }
    return text;
}

void func_800365E8_main(void *ptr) {
    if (ptr != NULL) {
        HuMemMemoryFreePerm(ptr);
    }
}
