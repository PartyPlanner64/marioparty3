#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/camsetup.h"
#include "game/hmfcoll.h"
#include "game/camera.h"
#include "macros.h"

u8 camSetupNum = 0;
u8 camSetupHookNo = 0;
Vec camSetupViewportScale[] = {
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
};
Vec camSetupViewportPos[] = {
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
};
RectF camSetupScissor[] = {
    { 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT },
    { 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT },
    { 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT },
    { 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT },
};

void CamSetupInit(u8 arg0) {
    camSetupNum = arg0;
    Hu3DCamInit(camSetupNum);
    gCameraList[0].fov = 45.0f;
    camSetupHookNo = 0;
}

s32 CamSetupMapCullAdd(void) {
    s32 temp_s0;

    temp_s0 = camSetupHookNo;
    Hu3DCameraModelHookSet(camSetupHookNo, (void (*)(void *, struct HmfModel *))MapCullFan, &CFan);
    camSetupHookNo++;
    return temp_s0;
}

void CamSetupInitMulti(s32 arg0) {
    s32 i;

    camSetupNum = arg0;
    Hu3DCamInit(camSetupNum);

    for (i = 0; i < camSetupNum; i++) {
        gCameraList[i].fov = 45.0f;
    }

    camSetupHookNo = 0;
}

s32 CamSetupMapCullAddMulti(s32 arg0) {
    s32 i;

    for (i = 0; i < arg0; i++) {
        Hu3DCameraModelHookSet(i, (void (*)(void *, struct HmfModel *))MapCullFan, &CFanM[i]);
        camSetupHookNo++;
    }

    return camSetupHookNo;
}
