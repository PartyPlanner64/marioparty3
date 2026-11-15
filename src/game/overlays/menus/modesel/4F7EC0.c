#include "common.h"

extern u8 D_800D2132_main;

const Vec D_8010F3B0_modesel = { 0.0f, 0.0f, 100.0f };
const Vec D_8010F3BC_modesel = { 0.0f, 0.0f, 0.0f };
const Vec D_8010F3C8_modesel = { 0.0f, 1.0f, 0.0f };
const Vec D_8010F3D4_modesel = { 0.0f, 0.0f, 0.0f }; /* Unreferenced. */

void func_80107CB0_modesel(void);

void func_801059D0_modesel(void) {
    Vec position;
    Vec target;
    Vec up;

    omInitObjMan(0x40, 0x20);
    Hu3DSprModelInit(0x20);
    omGameSysInit();
    CamSetupInit(1);
    position = D_8010F3B0_modesel;
    target = D_8010F3BC_modesel;
    up = D_8010F3C8_modesel;
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
    D_800D2132_main = 0;
    _ClearFlag(0xD);
}

void func_80105BD8_modesel(void) {
    func_801059D0_modesel();
    func_80107CB0_modesel();
}

void func_80105BFC_modesel(void) {
    func_801059D0_modesel();
    func_80107CB0_modesel();
}

void func_80105C20_modesel(void) {
    func_801059D0_modesel();
    func_80107CB0_modesel();
}
