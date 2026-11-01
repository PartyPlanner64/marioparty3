#include "common.h"
#include "game/camera.h"
#include "game/hu3d.h"
#include "game/object.h"
#include "game/mallocblock.h"
#include "hand_line_sinker.h"

typedef struct CameraMotionData {
    /* 0x00 */ CameraPreset *from;
    /* 0x04 */ CameraPreset *to;
    /* 0x08 */ u16 duration;
    /* 0x0A */ u16 remaining;
    /* 0x0C */ f32 t;
} CameraMotionData; // sizeof 0x10

extern omObjData *D_8010C190_hand_line_sinker;
extern FishingLine *D_8010C180_hand_line_sinker;
extern Gfx *D_8010C184_hand_line_sinker;
extern HmfData **D_8010C188_hand_line_sinker;
extern HmfModel *D_8010C18C_hand_line_sinker;
extern u8 D_800D2008_main;
extern Gfx *gMainGfxPos;

void func_8010B750_hand_line_sinker(omObjData *obj);

void func_8010B5B0_hand_line_sinker(void) {
    func_8000B5F0_main(1);
    func_8000B638_main();
    gCameraList->fov = 40.0f;
}

void func_8010B5EC_hand_line_sinker(CameraPreset *preset, CameraPreset *to, s16 duration) {
    CameraMotionData *data;

    Center = preset->center;
    CRot = preset->rot;
    CZoom = preset->zoom;
    D_8010C190_hand_line_sinker = omAddObj(40, 0, 0, -1, func_8010B750_hand_line_sinker);
    data = HuMemAllocTag(sizeof(CameraMotionData), TAG_OVERLAY);
    D_8010C190_hand_line_sinker->data = data;
    data->from = preset;
    data->to = to;
    data->duration = data->remaining = duration;
    data->t = 0.0f;
    Center = preset->center;
    CRot = preset->rot;
    CZoom = preset->zoom;
    D_8010C190_hand_line_sinker->work[0] = 1;
    D_8010C190_hand_line_sinker->work[1] = 0;
    D_8010C190_hand_line_sinker->work[2] = 0;
    if (duration >= 0) {
        D_8010C190_hand_line_sinker->work[3] = 1;
    } else {
        D_8010C190_hand_line_sinker->work[3] = 0;
    }
}

void func_8010B750_hand_line_sinker(omObjData *obj) {
    CameraMotionData *data = obj->data;
    CameraPreset *from;
    CameraPreset *to;

    if (D_8010C190_hand_line_sinker->work[1] == 0) {
        return;
    }
    from = data->from;
    to = data->to;
    if (D_8010C190_hand_line_sinker->work[3] == 1) {
        Center.x += (to->center.x - from->center.x) / data->duration;
        Center.y += (to->center.y - from->center.y) / data->duration;
        Center.z += (to->center.z - from->center.z) / data->duration;
        CRot.x += (to->rot.x - from->rot.x) / data->duration;
        CRot.y += (to->rot.y - from->rot.y) / data->duration;
        CRot.z += (to->rot.z - from->rot.z) / data->duration;
        CZoom += (to->zoom - from->zoom) / data->duration;
        if (--data->remaining == 0) {
            Center.x = to->center.x;
            Center.y = to->center.y;
            Center.z = to->center.z;
            CRot.x = to->rot.x;
            CRot.y = to->rot.y;
            CRot.z = to->rot.z;
            CZoom = to->zoom;
            obj->work[0] = 0;
            if (obj->work[2] == 1) {
                omDelObj(obj);
                D_8010C190_hand_line_sinker = NULL;
            } else {
                obj->func = NULL;
            }
        }
    } else {
        Center.x = from->center.x + (to->center.x - from->center.x) * data->t;
        Center.y = from->center.y + (to->center.y - from->center.y) * data->t;
        Center.z = from->center.z + (to->center.z - from->center.z) * data->t;
        CRot.x = from->rot.x + (to->rot.x - from->rot.x) * data->t;
        CRot.y = from->rot.y + (to->rot.y - from->rot.y) * data->t;
        CRot.z = from->rot.z + (to->rot.z - from->rot.z) * data->t;
        CZoom = from->zoom + (to->zoom - from->zoom) * data->t;
        if (obj->work[0] == 0) {
            if (obj->work[2] == 1) {
                D_8010C190_hand_line_sinker = NULL;
                omDelObj(obj);
            } else {
                obj->func = NULL;
            }
        }
    }
}

void func_8010BA50_hand_line_sinker(f32 arg0) {
    OM_GET_DATA_PTR(D_8010C190_hand_line_sinker, CameraMotionData)->t = arg0;
}

void func_8010BA64_hand_line_sinker(void) {
    omOvlReturnEx(1);
}

FishingLine *func_8010BA80_hand_line_sinker(u8 r, u8 g, u8 b) {
    FishingLine *line;
    s16 i;

    line = HuMemAlloc(sizeof(FishingLine));
    line->model = func_8001A894_main(0x1080, NULL, 4);
    for (i = 0; i < D_800D1FF0_main; i++) {
        line->vtx[i] = HuMemAlloc(32 * sizeof(Vtx));
        line->gfx[i] = HuMemAlloc(128 * sizeof(Gfx));
    }
    line->r = r;
    line->g = g;
    line->b = b;
    return line;
}

void func_8010BB58_hand_line_sinker(FishingLine *line, Vec *points, u16 count) {
    Gfx *gfx;
    Vtx *vtx;
    s16 i;

    if (line == NULL) {
        return;
    }
    vtx = line->vtx[D_800D2008_main];
    gfx = line->gfx[D_800D2008_main];
    if (count < 2) {
        osSyncPrintf("Line Count err %d\n", count);
    }
    D_8010C180_hand_line_sinker = line;
    D_8010C18C_hand_line_sinker = &HmfModelData[line->model];
    D_8010C188_hand_line_sinker = &HmfModelData[line->model].hmf;
    D_8010C184_hand_line_sinker = gfx;
    HmfModelData[line->model].hmf->unk3C->unk00[0] = gfx;
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(gfx++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPVertex(gfx++, osVirtualToPhysical(vtx), count + 1, 0);
    vtx->v.ob[0] = points->x;
    vtx->v.ob[1] = points->y;
    vtx->v.ob[2] = points->z;
    vtx->v.cn[0] = line->r;
    vtx->v.cn[1] = line->g;
    vtx->v.cn[2] = line->b;
    vtx->v.tc[1] = 0;
    vtx->v.tc[0] = 0;
    vtx->v.cn[3] = 255;
    vtx++;
    points++;
    for (i = 1; i < count; i++) {
        gSPLine3D(gfx++, i - 1, i, 0);
        vtx->v.ob[0] = points->x;
        vtx->v.ob[1] = points->y;
        vtx->v.ob[2] = points->z;
        vtx->v.cn[0] = line->r;
        vtx->v.cn[1] = line->g;
        vtx->v.cn[2] = line->b;
        vtx->v.tc[1] = 0;
        vtx->v.tc[0] = 0;
        vtx->v.cn[3] = 255;
        vtx++;
        points++;
    }
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gSPEndDisplayList(gfx++);
}

void func_8010BE6C_hand_line_sinker(FishingLine *line) {
    s16 i;

    Hu3DModelKill(line->model);
    for (i = 0; i < D_800D1FF0_main; i++) {
        func_80019C00_main(line->vtx[i]);
        func_80019C00_main(line->gfx[i]);
    }
    func_80019C00_main(line);
}
