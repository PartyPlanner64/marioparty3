#include "common.h"

extern u8 omSysPauseReadyF;

void filesel_MainInit(void);

const Vec filesel_cameraInitPos = { 0.0f, 0.0f, 100.0f };
const Vec filesel_cameraInitTarget = { 0.0f, 0.0f, 0.0f };
const Vec filesel_cameraInitUp = { 0.0f, 1.0f, 0.0f };
const Vec filesel_unusedVec = { 0.0f, 0.0f, 0.0f }; /* Unreferenced. */

s32 filesel_unusedF BSS;

void filesel_ObjectInit(void) {
    Vec position;
    Vec target;
    Vec up;

    omInitObjMan(0x40, 0x20);
    Hu3DSprModelInit(0x20);
    omGameSysInit();
    CamSetupInit(1);
    position = filesel_cameraInitPos;
    target = filesel_cameraInitTarget;
    up = filesel_cameraInitUp;
    ScissorSet(0, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 41.0f, 80.0f, 8000.0f);
    Hu3DCameraPosSetV(0, &position, &target, &up);
    Hu3DMotionGlobalSpeedSet(1.0f);
    HuAudSeqStop();
    pfInit();
    HuWinInit();
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x80);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(1, 0.0f, 64.0f, 192.0f);
    omSysPauseReadyF = 0;
}

void filesel_ObjectSetup(void) {
    filesel_unusedF = 0;
    filesel_ObjectInit();
    filesel_MainInit();
}
