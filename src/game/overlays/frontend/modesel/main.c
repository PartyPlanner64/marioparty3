#include "common.h"

extern u8 omSysPauseReadyF;

const Vec modesel_cameraPos = { 0.0f, 0.0f, 100.0f };
const Vec modesel_cameraAt = { 0.0f, 0.0f, 0.0f };
const Vec modesel_cameraUp = { 0.0f, 1.0f, 0.0f };
const Vec modesel_cameraUnusedVec = { 0.0f, 0.0f, 0.0f }; /* Unreferenced. */

void modesel_MainCreate(void);

void modesel_ObjectInit(void) {
    Vec position;
    Vec target;
    Vec up;

    omInitObjMan(0x40, 0x20);
    Hu3DSprModelInit(0x20);
    omGameSysInit();
    CamSetupInit(1);
    position = modesel_cameraPos;
    target = modesel_cameraAt;
    up = modesel_cameraUp;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 41.0f, 80.0f, 8000.0f);
    Hu3DCameraPosSetV(0, &position, &target, &up);
    Hu3DMotionGlobalSpeedSet(1.0f);
    if (FileSelEnteredGet()) {
        HuAudSeqStop();
    }
    pfInit();
    HuWinInit();
    Hu3DGLightMaxSet(1);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x80);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(1, 0.0f, 64.0f, 192.0f);
    omSysPauseReadyF = 0;
    _ClearFlag(0xD);
}

void modesel_ObjectSetup(void) {
    modesel_ObjectInit();
    modesel_MainCreate();
}

void modesel_ReturnObjectSetup(void) {
    modesel_ObjectInit();
    modesel_MainCreate();
}

void modesel_FadeWhiteObjectSetup(void) {
    modesel_ObjectInit();
    modesel_MainCreate();
}
