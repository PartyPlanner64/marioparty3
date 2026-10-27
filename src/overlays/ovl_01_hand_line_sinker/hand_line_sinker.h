#ifndef _HAND_LINE_SINKER_H
#define _HAND_LINE_SINKER_H

#include "common.h"

typedef struct CameraPreset {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} CameraPreset;

void func_8010B5EC_hand_line_sinker(CameraPreset *preset, CameraPreset *to, s16 duration);

#endif
