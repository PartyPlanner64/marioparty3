#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/camsetup.h"
#include "game/hmfcoll.h"
#include "game/camera.h"

u8 D_80097660_main = 0;
u8 D_80097661_main = 0;
Vec D_80097664_main[] = {
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
};
Vec D_80097694_main[] = {
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
    { 640.0f, 480.0f, 511.0f },
};
RectF D_800976C4_main[] = {
    { 0.0f, 0.0f, 320.0f, 240.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f },
};
extern s32 D_800CE178_main; // TODO: type correctly

typedef struct UnkC1F0 {
    char unk_00[0x18];
} UnkC1F0;

extern UnkC1F0 D_800D04B8_main[];

void func_8000B5F0_main(u8 arg0) {
    D_80097660_main = arg0;
    Hu3DCamInit(D_80097660_main);
    gCameraList[0].fov = 45.0f;
    D_80097661_main = 0;
}

s32 func_8000B638_main(void) {
    s32 temp_s0;

    temp_s0 = D_80097661_main;
    func_80012888_main(D_80097661_main, (void (*)(void *, struct HmfModel *))func_80020E94_main, &D_800CE178_main);
    D_80097661_main++;
    return temp_s0;
}

void func_8000B690_main(s32 arg0) {
    s32 i;

    D_80097660_main = arg0;
    Hu3DCamInit(D_80097660_main);

    for (i = 0; i < D_80097660_main; i++) {
        gCameraList[i].fov = 45.0f;
    }

    D_80097661_main = 0;
}

s32 func_8000B710_main(s32 arg0) {
    s32 i;

    for (i = 0; i < arg0; i++) {
        func_80012888_main(i, (void (*)(void *, struct HmfModel *))func_80020E94_main, &D_800D04B8_main[i]);
        D_80097661_main++;
    }

    return D_80097661_main;
}
