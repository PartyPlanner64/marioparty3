#ifndef _HAND_LINE_SINKER_H
#define _HAND_LINE_SINKER_H

#include "common.h"

typedef struct CameraPreset {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} CameraPreset;

typedef struct FishingLine {
    /* 0x00 */ s16 model;
    /* 0x02 */ u8 r;
    /* 0x03 */ u8 g;
    /* 0x04 */ u8 b;
    /* 0x08 */ Vtx *vtx[8];
    /* 0x28 */ Gfx *gfx[8];
} FishingLine; // sizeof 0x48

void func_8010BE6C_hand_line_sinker(FishingLine *line);
void func_8010B5EC_hand_line_sinker(CameraPreset *preset, CameraPreset *to, s16 duration);

#endif
