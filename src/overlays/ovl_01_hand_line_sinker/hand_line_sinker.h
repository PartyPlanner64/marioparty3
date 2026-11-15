#ifndef _HAND_LINE_SINKER_H
#define _HAND_LINE_SINKER_H

#include "common.h"
#include "overlays/mgcamera.h"

typedef struct FishingLine {
    /* 0x00 */ s16 model;
    /* 0x02 */ u8 r;
    /* 0x03 */ u8 g;
    /* 0x04 */ u8 b;
    /* 0x08 */ Vtx *vtx[8];
    /* 0x28 */ Gfx *gfx[8];
} FishingLine; // sizeof 0x48

FishingLine *func_8010BA80_hand_line_sinker(u8 r, u8 g, u8 b);
void func_8010BE6C_hand_line_sinker(FishingLine *line);
void func_8010B5EC_hand_line_sinker(MgCameraPreset *preset, MgCameraPreset *to, s16 duration);

#endif
