#include "game/camera.h"
#include "mallocblock.h"
#include "include_asm.h"
#include "macros.h"
#include "types.h"

// EXTERN
void func_8008A0D0_main(Mtx *);

extern HuCamera *gCameraList;
extern Vec D_800A0554_main;
extern Vec D_800A0590_main;
extern RectF D_800A05CC_main;
extern s16 D_800C9932_main;
extern HuCamMtxs *D_800D0444_main;
extern HuCamera *D_800D10F4_main;
extern u8 D_800D1FF0_main;
extern u8 D_800D2008_main;
extern s16 D_800D418E_main;

void Hu3DCamInit(u32 arg0) {
    s16 var_s3;
    s16 var_s2;

    D_800C9932_main = arg0;
    D_800D418E_main = 0;
    if (gCameraList != NULL) {
        HuMemFree(gCameraList);
    }
    gCameraList = HuMemAlloc(0xD20);
    for (var_s3 = 0; var_s3 < 6; var_s3++) {
        gCameraList[var_s3].fov = 45.0f;
        gCameraList[var_s3].near = 80.0f;
        gCameraList[var_s3].far = 8000.0f;
        gCameraList[var_s3].unk2 = 0;
        gCameraList[var_s3].unk4 = -1;
        Hu3DCameraViewportSet(var_s3, &D_800A0554_main, &D_800A0590_main);
        Hu3DCameraScissorSet(var_s3, &D_800A05CC_main);
        gCameraList[var_s3].unkA0 = NULL;
        gCameraList[var_s3].unkA8 = NULL;
        gCameraList[var_s3].unkAC = NULL;
        for (var_s2 = 0; var_s2 < D_800D1FF0_main; var_s2++) {
            func_8008A0D0_main(&gCameraList[var_s3].mtxs[var_s2].perspMtx);
            func_8008A0D0_main(&gCameraList[var_s3].mtxs[var_s2].lookAtMtx);
        }
    }
    D_800D10F4_main = gCameraList;
    D_800D0444_main = gCameraList->mtxs;
}

void func_800123F4_main(void) {
    D_800D418E_main = D_800D2008_main;
}

void Hu3DCameraPosSetV(s16 camIndex, Vec *pos, Vec *at, Vec *up) {
    HuCamera *camera = &gCameraList[camIndex];
    camera->pos = *pos;
    camera->at = *at;
    camera->up = *up;
}

void Hu3DCameraPerspectiveSet(s16 camIndex, f32 fov, f32 near, f32 far) {
    HuCamera *camera = &gCameraList[camIndex];
    camera->fov = fov;
    camera->near = near;
    camera->far = far;
    camera->perspNorm = 1;
}

void Hu3DCameraScissorSet(s16 camIndex, RectF *arg1) {
    HuCamera *camera = &gCameraList[camIndex];
    camera->screenLeft = arg1->x1;
    camera->screenTop = arg1->y1;
    camera->screenRight = arg1->x2;
    camera->screenBottom = arg1->y2;
}

void Hu3DCameraViewportSet(s16 camIndex, Vec *arg1, Vec *arg2) {
    HuCamera *camera = &gCameraList[camIndex];
    camera->screenScale = *arg1;
    camera->screenPos = *arg2;
}

void Hu3DCamUpdateMtx(s16 camIndex) {
    HuCamera *camera;
    HuCamMtxs *mtxs;

    camera = &gCameraList[camIndex];
    mtxs = &camera->mtxs[D_800D418E_main];

    guPerspective(&mtxs->perspMtx, &camera->perspNorm, camera->fov, (SCREEN_WIDTH / SCREEN_HEIGHT), camera->near, camera->far, 1.0f);
    guLookAt(&mtxs->lookAtMtx, camera->pos.x, camera->pos.y, camera->pos.z, camera->at.x, camera->at.y, camera->at.z, camera->up.x, camera->up.y, camera->up.z);
}

void Hu3DCameraSet(s16 camIndex, Gfx **dispList) {
    HuCamMtxs *camMtx;
    HuCamera *camera;

    camera = &gCameraList[camIndex];
    camMtx = &camera->mtxs[D_800D418E_main];
    camera->viewports[D_800D418E_main].vp.vscale[0] = (s16)camera->screenScale.x;
    camera->viewports[D_800D418E_main].vp.vscale[1] = (s16)camera->screenScale.y;
    camera->viewports[D_800D418E_main].vp.vscale[2] = (s16)camera->screenScale.z;
    camera->viewports[D_800D418E_main].vp.vtrans[0] = (s16)camera->screenPos.x;
    camera->viewports[D_800D418E_main].vp.vtrans[1] = (s16)camera->screenPos.y;
    camera->viewports[D_800D418E_main].vp.vtrans[2] = (s16)camera->screenPos.z;

    gSPViewport((*dispList)++, &camera->viewports[D_800D418E_main].vp);
    gSPPerspNormalize((*dispList)++, camera->perspNorm);
    gSPMatrix((*dispList)++, osVirtualToPhysical(&camMtx->perspMtx), G_MTX_PROJECTION | G_MTX_LOAD);
    gSPMatrix((*dispList)++, OS_PHYSICAL_TO_K0(&camMtx->lookAtMtx), G_MTX_LOAD);
}

void func_800127C4_main(s16 camIndex, Gfx **dispList) {
    HuCamera *camera = &gCameraList[camIndex];
    gDPSetScissor((*dispList)++, G_SC_NON_INTERLACE, camera->screenLeft, camera->screenTop, camera->screenRight, camera->screenBottom);
}

void func_80012888_main(s16 camIndex, void (*arg1)(void *, struct HmfModel *), void *arg2) {
    HuCamera *camera = &gCameraList[camIndex];
    camera->unkA0 = arg1;
    camera->unkA4 = arg2;
}

void func_800128BC_main(s16 camIndex, void (*arg1)(s16)) {
    gCameraList[camIndex].unkA8 = arg1;
}

void func_800128EC_main(s16 camIndex, void (*arg1)(s16)) {
    gCameraList[camIndex].unkAC = arg1;
}

void Hu3D3Dto2D(s16 camIndex, Vec *worldPos, Vec2f *outPos) {
    f32 x;
    f32 y;
    f32 z;
    f32 projectedX;
    f32 projectedY;
    f32 projectedZ;
    HuCamera *camera;
    HuMtx4F viewMtx;

    camera = &gCameraList[camIndex];
    HuLookAtF(
        viewMtx,
        camera->pos.x,
        camera->pos.y,
        camera->pos.z,
        camera->at.x,
        camera->at.y,
        camera->at.z,
        camera->up.x,
        camera->up.y,
        camera->up.z);

    x = worldPos->x;
    y = worldPos->y;
    z = worldPos->z;
    x -= camera->pos.x;
    y -= camera->pos.y;
    z -= camera->pos.z;
    projectedX = ((x * viewMtx[0][0]) + (y * viewMtx[1][0])) + (z * viewMtx[2][0]);
    projectedY = ((x * viewMtx[0][1]) + (y * viewMtx[1][1])) + (z * viewMtx[2][1]);
    projectedZ = ((x * viewMtx[0][2]) + (y * viewMtx[1][2])) + (z * viewMtx[2][2]);
    x = sindf(camera->fov / 2.0f) / cosdf(camera->fov / 2.0f) * projectedZ * ASPECT_RATIO;
    y = (sindf(camera->fov / 2.0f) / cosdf(camera->fov / 2.0f)) * projectedZ;
    outPos->x = (projectedX * (SCREEN_WIDTH_CENTER / (-x))) + SCREEN_WIDTH_CENTER;
    outPos->y = ((projectedY * (SCREEN_HEIGHT_CENTER / y)) + SCREEN_HEIGHT_CENTER);
}

void func_80012B14_main(s16 camIndex, Vec *worldPos, Vec2f *outPos) {
    f32 x;
    f32 y;
    f32 z;
    f32 projectedX;
    f32 projectedY;
    f32 projectedZ;
    HuCamera *camera;
    HuMtx4F viewMtx;
    f32 f2;
    f32 f4;

    camera = &gCameraList[camIndex];
    HuLookAtF(
        viewMtx,
        camera->pos.x,
        camera->pos.y,
        camera->pos.z,
        camera->at.x,
        camera->at.y,
        camera->at.z,
        camera->up.x,
        camera->up.y,
        camera->up.z);

    x = worldPos->x;
    y = worldPos->y;
    z = worldPos->z;
    x -= camera->pos.x;
    y -= camera->pos.y;
    z -= camera->pos.z;
    projectedX = ((x * viewMtx[0][0]) + (y * viewMtx[1][0])) + (z * viewMtx[2][0]);
    projectedY = ((x * viewMtx[0][1]) + (y * viewMtx[1][1])) + (z * viewMtx[2][1]);
    projectedZ = ((x * viewMtx[0][2]) + (y * viewMtx[1][2])) + (z * viewMtx[2][2]);
    x = sindf(camera->fov / 2.0f) / cosdf(camera->fov / 2.0f) * projectedZ * (camera->screenScale.x / camera->screenScale.y);
    y = (sindf(camera->fov / 2.0f) / cosdf(camera->fov / 2.0f)) * projectedZ;
    f2 = camera->screenPos.x / 4.0f;
    outPos->x = (projectedX * (f2 / (-x))) + f2;
    f4 = camera->screenPos.y / 4.0f;
    outPos->y = ((projectedY * (f4 / y)) + f4);
}

void Hu3D2Dto3D(s16 camIndex, f32 depth, Vec2f *screenPos, Vec2f *outPos) {
    HuCamera *camera;
    HuMtx4F viewMtx;
    f32 x;
    f32 y;
    f32 screenX;
    f32 screenY;

    camera = &gCameraList[camIndex];
    HuLookAtF(
        viewMtx,
        camera->pos.x,
        camera->pos.y,
        camera->pos.z,
        camera->at.x,
        camera->at.y,
        camera->at.z,
        camera->up.x,
        camera->up.y,
        camera->up.z);

    y = sindf(camera->fov / 2.0f) / cosdf(camera->fov / 2.0f) * depth;
    x = y * ASPECT_RATIO;
    screenX = screenPos->x / SCREEN_WIDTH;
    screenY = (SCREEN_HEIGHT - screenPos->y) / SCREEN_HEIGHT;
    outPos->x = (x + x) * screenX - x;
    outPos->y = (y + y) * screenY - y;
}

// Rotates the camera up vector to be perpendicular to the view direction.
void func_80012E54_main(s16 camIndex) {
    HuCamera *camera;
    HmfData *hmf;
    HmfData_UnkBC *env;
    f32 angle;
    f32 dx, dy, dz;
    f32 len;
    f32 ux, uy, uz;

    camera = &gCameraList[camIndex];
    hmf = HmfModelData[camera->unk4].hmf;
    if (hmf == NULL) {
        return;
    }
    env = hmf->unkBC;
    if (env == NULL) {
        return;
    }
    angle = -90.0f;
    dx = env->unk14 - env->unk08;
    dy = env->unk18 - env->unk0C;
    dz = env->unk1C - env->unk10;
    len = dx * dx + dy * dy + dz * dz;
    len = HuSqrtf(len);
    dx /= len;
    dy /= len;
    dz /= len;
    ux = dy * dz - dz * (dy + 1.0f);
    uy = dz * dx - dx * dz;
    uz = dx * (dy + 1.0f) - dy * dx;
    env->unk20 = ux * (dx * dx + (1.0f - dx * dx) * cosdf(angle)) + uy * (dy * dx * (1.0f - cosdf(angle)) - dz * sindf(angle)) + uz * (dz * dx * (1.0f - cosdf(angle)) + dy * sindf(angle));
    env->unk24 = ux * (dy * dx * (1.0f - cosdf(angle)) + dz * sindf(angle)) + uy * (dy * dy + (1.0f - dy * dy) * cosdf(angle)) + uz * (dy * dz * (1.0f - cosdf(angle)) - dx * sindf(angle));
    env->unk28 = ux * (dz * dx * (1.0f - cosdf(angle)) - dy * sindf(angle)) + uy * (dy * dz * (1.0f - cosdf(angle)) + dx * sindf(angle)) + uz * (dz * dz + (1.0f - dz * dz) * cosdf(angle));
    Hu3DCameraPosSetV(camIndex, (Vec *)&env->unk08, (Vec *)&env->unk14, (Vec *)&env->unk20);
    Hu3DCamUpdateMtx(camIndex);
}

void func_80013320_main(s16 value, s16 camIndex) {
    gCameraList[camIndex].unk4 = value;
}

void func_80013350_main(s16 camIndex) {
    gCameraList[camIndex].unk4 = -1;
}
