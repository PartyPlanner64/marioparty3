#include "common.h"
#include "../ovl_80_shared_board/FA250.h"
#include "game/mallocblock.h"
#include "overlays/opening.h"

extern s8 D_800D2132_main;


void opObjectInit(void) {
    omInitObjMan(32, 8);
    func_800142A0_main(8);
    func_8004A208_main();
    func_8000B5F0_main(1);
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
    func_80030030_main(1.0f);
    HuAudSeqStop();
    pfInit();
    HuWinInit();
    HmfLightMaxSet(2);
    HmfLightColorSet(0, 128, 128, 128);
    HmfLightColorSet(1, 255, 255, 255);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightDirSet(1, 0.0f, 64.0f, 192.0f);
    D_800D2132_main = 0;
}

void opTitleObjectSetup(void) {
    opObjectInit();
    opTitleCreate();
}

void func_80105C2C_opening(void) {
    opObjectInit();
    opDemoCreate();
}

void opDemoObjectSetup(void) {
    opObjectInit();
    opDemoCreate();
}
