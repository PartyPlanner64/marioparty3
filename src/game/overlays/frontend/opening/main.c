#include "common.h"
#include "game/overlays/party/common/back.h"
#include "game/mallocblock.h"
#include "game/overlays/opening.h"

extern s8 omSysPauseReadyF;


void op_ObjectInit(void) {
    omInitObjMan(32, 8);
    Hu3DSprModelInit(8);
    omGameSysInit();
    CamSetupInit(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    {
        Vec pos = { 0.0f, 0.0f, 100.0f };
        Vec at = { 0.0f, 0.0f, 0.0f };
        Vec up = { 0.0f, 1.0f, 0.0f };

        ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
        ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        Hu3DCameraPerspectiveSet(0, 41.0f, 80.0f, 8000.0f);
        Hu3DCameraPosSetV(0, &pos, &at, &up);
    }
    Hu3DMotionGlobalSpeedSet(1.0f);
    HuAudSeqStop();
    pfInit();
    HuWinInit();
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 128, 128, 128);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightDirSet(1, 0.0f, 64.0f, 192.0f);
    omSysPauseReadyF = 0;
}

void op_TitleObjectSetup(void) {
    op_ObjectInit();
    op_TitleCreate();
}

void op_DemoReturnObjectSetup(void) {
    op_ObjectInit();
    op_DemoCreate();
}

void op_DemoObjectSetup(void) {
    op_ObjectInit();
    op_DemoCreate();
}
