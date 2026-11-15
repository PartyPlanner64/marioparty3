#ifndef _OVL_MGCAMERA_H
#define _OVL_MGCAMERA_H

#include "ultra64.h"
#include "humath.h"

// Camera types shared by minigame overlays. MgCameraKey is used by the camera
// interpolation helper that several minigame overlays link in their own copy of.

// Pass for any component of the camera-move helper to keep its current value.
#define CAMERA_KEEP 65535.0f

// Fixed camera view copied into Center/CRot/CZoom.
typedef struct MgCameraPreset {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} MgCameraPreset; // Size 0x1C

typedef struct MgCameraKey {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
} MgCameraKey; // Size 0x24

#endif
