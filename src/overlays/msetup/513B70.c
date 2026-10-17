#include "common.h"

extern s16 D_800D418E_main;

f32 func_80054B1C_main(s16, s16, s16, f32, f32, f32);

void func_80117910_msetup(s16 group, s16 member, s16 camera, f32 x, f32 y, f32 z, f32 scale) {
    HuSprite *sprite;
    HuCamera *cam;
    f32 depth;

    sprite = HuSprGrpData[group]->members[member];
    cam = &gCameraList[camera];
    depth = func_80054B1C_main(group, member, camera, x, y, z);
    if (depth != 0.0) {
        sprite->unk_60 = (cam->viewports[D_800D418E_main].vp.vscale[0] * scale) / 4.0 / depth / (f64)(4.0f / 3.0f);
        sprite->unk_64 = (cam->viewports[D_800D418E_main].vp.vscale[1] * scale) / 4.0 / depth;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/513B70", func_80117A3C_msetup);

INCLUDE_ASM("asm/nonmatchings/overlays/msetup/513B70", func_80118D48_msetup);
