#include "common.h"

extern u8 D_800D2132_main;

void func_80107C84_filesel(void);

const Vec D_801129C0_filesel = { 0.0f, 0.0f, 100.0f };
const Vec D_801129CC_filesel = { 0.0f, 0.0f, 0.0f };
const Vec D_801129D8_filesel = { 0.0f, 1.0f, 0.0f };
const Vec D_801129E4_filesel = { 0.0f, 0.0f, 0.0f }; /* Unreferenced. */

s32 D_80112E90_filesel BSS;

void func_801059D0_filesel(void) {
    Vec position;
    Vec target;
    Vec up;

    omInitObjMan(0x40, 0x20);
    Hu3DSprModelInit(0x20);
    omGameSysInit();
    CamSetupInit(1);
    position = D_801129C0_filesel;
    target = D_801129CC_filesel;
    up = D_801129D8_filesel;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
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
    D_800D2132_main = 0;
}

void func_80105BC0_filesel(void) {
    D_80112E90_filesel = 0;
    func_801059D0_filesel();
    func_80107C84_filesel();
}
