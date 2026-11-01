#ifndef _GAME_HVQ_H
#define _GAME_HVQ_H

#include "ultra64.h"

#define ASCII_HVQS 0x48565153

typedef struct HvqFileHeader {
    char signature[20];
    u16 width;
    u16 height;
    u8 horizontalSampling;
    u8 verticalSampling;
    u8 shifts;
    u8 componentOrder;
    u32 treeOffsets[4];
} HvqFileHeader;

typedef struct HvqImageHeader {
    u32 size;
    u32 modeOffsets[2];
    u32 meanOffsets[3];
    u32 amplitudeOffsets[3];
    u32 rawOffsets[3];
} HvqImageHeader;

void hvqMpsInit1(u8 alpha);
void hvqMpsDecodeStart1(void *data);
/* output contains RGBA5551 pixels; stride is measured in pixels. */
void hvqMpsDecode1(void *data, u16 *output, s32 stride, u8 *work);

void func_800677B8_main(u16 *output, s16 *luma, s16 *cb, s16 *cr);
void func_80067D50_main(u16 *output, s16 *luma, s16 *cb, s16 *cr);
void func_80068ECC_main(u16 *output);
void func_800694D0_main(u16 *output);

#endif
