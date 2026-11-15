#ifndef _OVL_MODECAMERA_H
#define _OVL_MODECAMERA_H

#include "ultra64.h"
#include "humath.h"

// Camera view used by the menu and mode overlays (msetup, mgmode, staff,
// storyresult). The view is copied into CRot/Center/CZoom and the fov is
// passed to Hu3DCameraPerspectiveSet.
typedef struct ModeCameraPreset {
    /* 0x00 */ Vec rot;
    /* 0x0C */ Vec center;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 fov;
} ModeCameraPreset; // Size 0x20

#endif
