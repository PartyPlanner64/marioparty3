#include "common.h"
#include "game/camera.h"
#include "game/object.h"
#include "mallocblock.h"

typedef struct CameraPreset {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} CameraPreset;

typedef struct CameraMotionData {
    /* 0x00 */ CameraPreset *from;
    /* 0x04 */ CameraPreset *to;
    /* 0x08 */ u16 duration;
    /* 0x0A */ u16 remaining;
    /* 0x0C */ f32 t;
} CameraMotionData; // sizeof 0x10

extern omObjData *D_8010C190_hand_line_sinker;

s32 func_8000B638_main(void);
void func_8010B750_hand_line_sinker(omObjData *obj);

void func_8010B5B0_hand_line_sinker(void) {
    func_8000B5F0_main(1);
    func_8000B638_main();
    gCameraList->fov[0] = 40.0f;
}

void func_8010B5EC_hand_line_sinker(CameraPreset *preset, CameraPreset *to, s16 duration) {
    CameraMotionData *data;

    Center = preset->center;
    CRot = preset->rot;
    CZoom = preset->zoom;
    D_8010C190_hand_line_sinker = omAddObj(40, 0, 0, -1, func_8010B750_hand_line_sinker);
    data = HuMemAllocTag(sizeof(CameraMotionData), 0x7918);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/120090", func_8010BA80_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/120090", func_8010BB58_hand_line_sinker);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_01_hand_line_sinker/120090", func_8010BE6C_hand_line_sinker);
