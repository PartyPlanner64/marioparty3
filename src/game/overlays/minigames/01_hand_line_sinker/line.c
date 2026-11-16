#include "common.h"
#include "game/camera.h"
#include "game/hu3d.h"
#include "game/object.h"
#include "game/mallocblock.h"
#include "hand_line_sinker.h"

typedef struct CameraMotionData {
    /* 0x00 */ MgCameraPreset *from;
    /* 0x04 */ MgCameraPreset *to;
    /* 0x08 */ u16 duration;
    /* 0x0A */ u16 remaining;
    /* 0x0C */ f32 t;
} CameraMotionData; // sizeof 0x10

FishingLine *m201_lineCur BSS;
Gfx *m201_lineGfx BSS;
HmfData **m201_lineHmf BSS;
HmfModel *m201_lineMdlData BSS;
omObjData *m201_cameraMoveObj BSS;
extern u8 Hu3DBufNo;
extern Gfx *gMainGfxPos;

void m201_CameraMoveObjMain(omObjData *obj);

void m201_CameraInit(void) {
    CamSetupInit(1);
    CamSetupMapCullAdd();
    gCameraList->fov = 40.0f;
}

void m201_CameraMoveStart(MgCameraPreset *preset, MgCameraPreset *to, s16 duration) {
    CameraMotionData *data;

    Center = preset->center;
    CRot = preset->rot;
    CZoom = preset->zoom;
    m201_cameraMoveObj = omAddObj(40, 0, 0, -1, m201_CameraMoveObjMain);
    data = HuMemAllocTag(sizeof(CameraMotionData), TAG_OVERLAY);
    m201_cameraMoveObj->data = data;
    data->from = preset;
    data->to = to;
    data->duration = data->remaining = duration;
    data->t = 0.0f;
    Center = preset->center;
    CRot = preset->rot;
    CZoom = preset->zoom;
    m201_cameraMoveObj->work[0] = 1;
    m201_cameraMoveObj->work[1] = 0;
    m201_cameraMoveObj->work[2] = 0;
    if (duration >= 0) {
        m201_cameraMoveObj->work[3] = 1;
    } else {
        m201_cameraMoveObj->work[3] = 0;
    }
}

void m201_CameraMoveObjMain(omObjData *obj) {
    CameraMotionData *data = obj->data;
    MgCameraPreset *from;
    MgCameraPreset *to;

    if (m201_cameraMoveObj->work[1] == 0) {
        return;
    }
    from = data->from;
    to = data->to;
    if (m201_cameraMoveObj->work[3] == 1) {
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
                m201_cameraMoveObj = NULL;
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
                m201_cameraMoveObj = NULL;
                omDelObj(obj);
            } else {
                obj->func = NULL;
            }
        }
    }
}

void m201_CameraMoveTimeSet(f32 arg0) {
    OM_GET_DATA_PTR(m201_cameraMoveObj, CameraMotionData)->t = arg0;
}

void m201_OvlReturn(void) {
    omOvlReturnEx(1);
}

FishingLine *m201_LineCreate(u8 r, u8 g, u8 b) {
    FishingLine *line;
    s16 i;

    line = HuMemAlloc(sizeof(FishingLine));
    line->model = Hu3DModelDLCreate(0x1080, NULL, 4);
    for (i = 0; i < Hu3DBufNum; i++) {
        line->vtx[i] = HuMemAlloc(32 * sizeof(Vtx));
        line->gfx[i] = HuMemAlloc(128 * sizeof(Gfx));
    }
    line->r = r;
    line->g = g;
    line->b = b;
    return line;
}

void m201_LineDraw(FishingLine *line, Vec *points, u16 count) {
    Gfx *gfx;
    Vtx *vtx;
    s16 i;

    if (line == NULL) {
        return;
    }
    vtx = line->vtx[Hu3DBufNo];
    gfx = line->gfx[Hu3DBufNo];
    if (count < 2) {
        osSyncPrintf("Line Count err %d\n", count);
    }
    m201_lineCur = line;
    m201_lineMdlData = &Hu3DData[line->model];
    m201_lineHmf = &Hu3DData[line->model].hmf;
    m201_lineGfx = gfx;
    Hu3DData[line->model].hmf->unk3C->unk00[0] = gfx;
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

void m201_LineKill(FishingLine *line) {
    s16 i;

    Hu3DModelKill(line->model);
    for (i = 0; i < Hu3DBufNum; i++) {
        HuMemDelayFree(line->vtx[i]);
        HuMemDelayFree(line->gfx[i]);
    }
    HuMemDelayFree(line);
}
