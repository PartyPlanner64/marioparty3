#include "game/audio.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/camera.h"
#include "mallocblock.h"

typedef struct CameraViewData {
    s16 spriteGroup;
    Vec2f scale;
    Vec2f baseScale;
    f32 zoom;
    Vec2f offset;
    Vec origin;
    void (*draw)(struct CameraViewData *);
    HuCamera *camera;
} CameraViewData; // Size 0x34

extern Gfx *gMainGfxPos;
extern omObjData *D_800D6A40_main;
extern struct str800D5298 D_800D1398_main;
extern s16 D_800CDBC8_main;
extern u16 D_800D530C_main;
extern u16 D_800D13EE_main;
extern s16 D_800A1910_main;
extern u16 D_800A1906_main;
extern s16 D_800D037E_main;
extern Vec D_800CD2A8_main[4];
extern Vec D_800D6A78_main;
extern f32 D_800CB890_main;
extern f32 D_800CCF98_main[];
extern f32 D_800CE17C_main[];
extern f32 D_800D04B8_main[][6];
extern f32 D_800D4198_main[];
extern f32 D_800D5210_main;
extern omObjData *D_800CE194_main;
extern s32 D_800D6AB8_main;

s32 func_800078F8_main(s16 seNo);
void func_80007B28_main(s32 seNo, s32 volume);
void func_80007DD8_main(s16 seNo);
void func_80012B14_main(s16 camIndex, Vec *worldPos, Vec2f *outPos);
void func_80000EA8_main(struct str800D5298 *config);
void func_800036E8_main(s32 musNo, s32 volume);
void func_8004A72C_main(s16 arg0);
void func_8004B7B0_main(s32 priority, s16 spriteGroup, void (*draw)(CameraViewData *), f32 fov, Vec *pos, Vec *at);
void func_8004B984_main(u8 count, s32 priority, s16 *spriteGroups, void (*draw)(CameraViewData *), f32 fov, Vec *pos, Vec *at);
void func_8004C76C_main(omObjData *);
void func_8004C4C4_main(omObjData *);
void func_8004CB44_main(Vec *out, Vec *normal);
void func_8004CD04_main(Vec *pos, Vec *at, f32 *zoom, Vec *rot, Vec *center);
void func_8004CF00_main(omObjData *);
void func_8004D094_main(omObjData *);

void omOutView(omObjData *object) {
    Vec pos, at, up;
    f32 rot_x = CRot.x;
    f32 rot_y = CRot.y;

    pos.x = Center.x + sindf(rot_y) * cosdf(rot_x) * CZoom;
    pos.y = Center.y + -sindf(rot_x) * CZoom;
    pos.z = Center.z + cosdf(rot_y) * cosdf(rot_x) * CZoom;
    at.x = Center.x;
    at.y = Center.y;
    at.z = Center.z;
    up.x = sindf(rot_y) * sindf(rot_x);
    up.y = cosdf(rot_x);
    up.z = cosdf(rot_y) * sindf(rot_x);
    D_800CE17C_main[0] = pos.x;
    D_800CE17C_main[1] = pos.z;
    D_800CE17C_main[-1] = CRot.y; // actually D_800CE178_main?
    D_800CE17C_main[2] = gCameraList->fov;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &pos, &at, &up);
    Hu3DCamUpdateMtx(0);
}

void omOutViewMulti(omObjData *object) {
    u8 i;

    for (i = 0; i < object->work[0]; i++) {
        Vec pos, at, up;
        f32 rot_x = CRotM[i].x;
        f32 rot_y = CRotM[i].y;

        pos.x = CenterM[i].x + sindf(rot_y) * cosdf(rot_x) * CZoomM[i];
        pos.y = CenterM[i].y + -sindf(rot_x) * CZoomM[i];
        pos.z = CenterM[i].z + cosdf(rot_y) * cosdf(rot_x) * CZoomM[i];
        at.x = CenterM[i].x;
        at.y = CenterM[i].y;
        at.z = CenterM[i].z;
        up.x = sindf(rot_y) * sindf(rot_x);
        up.y = cosdf(rot_x);
        up.z = cosdf(rot_y) * sindf(rot_x);
        D_800D04B8_main[i][1] = pos.x;
        D_800D04B8_main[i][2] = pos.z;
        D_800D04B8_main[i][0] = CRotM[i].y;
        D_800D04B8_main[i][3] = gCameraList[i].fov;
        D_800D04B8_main[i][4] = D_800CCF98_main[i];
        D_800D04B8_main[i][5] = D_800D4198_main[i];
        Hu3DCamSetPositionOrientation(i, &pos, &at, &up);
        Hu3DCamUpdateMtx(i);
    }
}

void func_8004B760_main(s32 priority, s16 spriteGroup, void (*draw)(CameraViewData *), f32 fov, Vec *pos, Vec *at) {
    D_800D6A78_main.x = 0;
    D_800D6A78_main.y = 1.0f;
    D_800D6A78_main.z = 0;
    func_8004B7B0_main(priority, spriteGroup, draw, fov, pos, at);
}

void func_8004B7B0_main(s32 priority, s16 spriteGroup, void (*draw)(CameraViewData *), f32 fov, Vec *pos, Vec *at) {
    // Retained camera scratch vectors from the original setup routines.
    Vec unusedPos, unusedAt, unusedUp, unusedOrigin;
    omObjData *object;
    CameraViewData *data;
    HuCamera *camera;

    object = omAddObj(priority, 0, 0, -1, func_8004C4C4_main);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    data = HuMemAllocTag(sizeof(CameraViewData), TAG_OVERLAY);
    object->data = data;
    data->draw = draw;
    data->spriteGroup = spriteGroup;
    func_8004CD04_main(pos, at, &CZoom, &CRot, &Center);
    Hu3DCamSetPerspective(0, fov, 80.0f, 8000.0f);
    camera = gCameraList;
    func_8004CB44_main(&data->origin, &D_800D6A78_main);
    data->zoom = CZoom;
    data->baseScale.x = camera->screenScale.x / 640.0f;
    data->baseScale.y = camera->screenScale.y / 480.0f;
    data->scale.x = data->baseScale.x;
    data->scale.y = data->baseScale.y;
    data->camera = camera;
}

void func_8004B904_main(u8 count, s32 priority, s16 *spriteGroups, void (*draw)(CameraViewData *), f32 fov, Vec *pos, Vec *at) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_800CD2A8_main[i].x = 0;
        D_800CD2A8_main[i].y = 1.0f;
        D_800CD2A8_main[i].z = 0;
    }
    func_8004B984_main(count, priority, spriteGroups, draw, fov, pos, at);
}

void func_8004B984_main(u8 count, s32 priority, s16 *spriteGroups, void (*draw)(CameraViewData *), f32 fov, Vec *pos, Vec *at) {
    // Retained camera scratch vectors from the original setup routines.
    Vec unusedPos, unusedAt, unusedUp, unusedOrigin;
    omObjData *object;
    CameraViewData *data;
    HuCamera *camera;
    s32 i;
    f32 near;
    f32 far;

    object = omAddObj(priority, 0, 0, -1, func_8004C76C_main);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    object->data = HuMemAllocTag(count * sizeof(CameraViewData), TAG_OVERLAY);
    data = object->data;
    func_8004CD04_main(pos, at, &CZoom, &CRot, &Center);
    near = 80.0f;
    far = 8000.0f;
    object->work[0] = count;
    for (i = 0; i < count; i++, data++) {
        Hu3DCamSetPerspective(i, fov, near, far);
        data->draw = draw;
        data->spriteGroup = spriteGroups[i];
        CZoomM[i] = CZoom;
        CRotM[i] = CRot;
        CenterM[i] = Center;
        camera = &gCameraList[i];
        func_8004CB44_main(&data->origin, &D_800CD2A8_main[i]);
        data->zoom = CZoom;
        data->baseScale.x = camera->screenScale.x / 640.0f;
        data->baseScale.y = camera->screenScale.y / 480.0f;
        data->scale.x = data->baseScale.x;
        data->scale.y = data->baseScale.y;
        data->camera = camera;
    }
}

void func_8004BC00_main(void) {
    gDPPipeSync(gMainGfxPos++);
    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    gDPSetCombineLERP(gMainGfxPos++, TEXEL0, 0, TEXEL0_ALPHA, 0, TEXEL0, 0, 1, 0,
                      TEXEL0, 0, TEXEL0_ALPHA, 0, TEXEL0, 0, 1, 0);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);
    gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
}

void func_8004BCE4_main(CameraViewData *data) {
    HuSprite *sprite;
    s16 left, top, right, bottom;
    u16 width, height;
    f32 halfWidth, halfHeight;
    f32 x1, y1, x2, y2;
    f32 stripHeight;
    u16 rows;
    s32 row;

    sprite = HuSprGet(data->spriteGroup, 0);
    width = sprite->unk_84->unk14;
    height = sprite->unk_84->unk16;
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gMainGfxPos++, sprite->unk_84->unk0C);
    left = data->camera->screenLeft;
    top = data->camera->screenTop;
    right = data->camera->screenRight;
    bottom = data->camera->screenBottom;
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, left, top, right, bottom);
    halfWidth = width / 2.0f * data->scale.x;
    halfHeight = height / 2.0f * data->scale.y;
    x1 = (right - left) / 2.0f - halfWidth - data->offset.x + left;
    y1 = (bottom - top) / 2.0f - halfHeight - data->offset.y + top;
    x2 = (right - left) / 2.0f + halfWidth - data->offset.x + left;
    y2 = (bottom - top) / 2.0f + halfHeight - data->offset.y + top;
    rows = 2048 / width - 1;
    x2 -= 1.0f;
    y2 -= 1.0f;
    stripHeight = fabs((f64)y2 - (f64)y1);
    stripHeight /= (u16)(height / rows);
    for (row = 0; row < height - 1; row += rows) {
        if (row + rows >= height - 1) {
            rows = height - row - 1;
        }
        if (y1 + stripHeight >= top) {
            if (y1 + stripHeight > y2) {
                stripHeight = y2 - y1;
            }
            gDPLoadTextureTile(gMainGfxPos++, sprite->unk_84->unk08, G_IM_FMT_CI, G_IM_SIZ_8b,
                               width, height, 0, row, width, row + rows, 0,
                               G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPScisTextureRectangle(gMainGfxPos++, (s32)(x1 * 4.0f), (s32)(y1 * 4.0f),
                                    (s32)(x2 * 4.0f), (s32)((y1 + stripHeight) * 4.0f),
                                    G_TX_RENDERTILE, 0, row * 32,
                                    (s32)(1024.0f / data->scale.x), (s32)(1024.0f / data->scale.y));
        }
        y1 += stripHeight;
        if (y1 >= bottom) {
            break;
        }
    }
}

void func_8004C4C4_main(omObjData *object) {
    Vec pos, at, up, origin;
    Vec2f screenPos, screenOrigin;
    f32 length;
    CameraViewData *data = object->data;
    f32 rot_x = CRot.x;
    f32 rot_y = CRot.y;

    pos.x = Center.x + sindf(rot_y) * cosdf(rot_x) * CZoom;
    pos.y = Center.y + -sindf(rot_x) * CZoom;
    pos.z = Center.z + cosdf(rot_y) * cosdf(rot_x) * CZoom;
    at.x = Center.x;
    at.y = Center.y;
    at.z = Center.z;
    up.x = sindf(rot_y) * sindf(rot_x);
    up.y = cosdf(rot_x);
    up.z = cosdf(rot_y) * sindf(rot_x);
    D_800CE17C_main[0] = pos.x;
    D_800CE17C_main[1] = pos.z;
    D_800CE17C_main[-1] = CRot.y; // actually D_800CE178_main?
    D_800CE17C_main[2] = gCameraList->fov;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &pos, &at, &up);
    Hu3DCamUpdateMtx(0);

    length = HuSqrtf((Center.x - pos.x) * (Center.x - pos.x) +
                     (Center.y - pos.y) * (Center.y - pos.y) +
                     (Center.z - pos.z) * (Center.z - pos.z));
    data->scale.x = data->zoom / length * data->baseScale.x;
    data->scale.y = data->zoom / length * data->baseScale.y;
    func_8004CB44_main(&origin, &D_800D6A78_main);
    func_80012B14_main(0, &origin, &screenPos);
    func_80012B14_main(0, &data->origin, &screenOrigin);
    data->offset.x = (screenPos.x - screenOrigin.x) * data->baseScale.x;
    data->offset.y = (screenPos.y - screenOrigin.y) * data->baseScale.y;
    if (data->draw != NULL) {
        func_8004BC00_main();
        data->draw(data);
        gSPEndDisplayList(gMainGfxPos++);
    }
}

void func_8004C76C_main(omObjData *object) {
    Vec pos, at, up, origin;
    Vec2f screenPos, screenOrigin;
    f32 length;
    f32 rot_x, rot_y;
    CameraViewData *data = object->data;
    u32 i;

    func_8004BC00_main();
    for (i = 0; i < object->work[0]; i++, data++) {
        rot_x = CRotM[i].x;
        rot_y = CRotM[i].y;
        pos.x = CenterM[i].x + sindf(rot_y) * cosdf(rot_x) * CZoomM[i];
        pos.y = CenterM[i].y + -sindf(rot_x) * CZoomM[i];
        pos.z = CenterM[i].z + cosdf(rot_y) * cosdf(rot_x) * CZoomM[i];
        at.x = CenterM[i].x;
        at.y = CenterM[i].y;
        at.z = CenterM[i].z;
        up.x = sindf(rot_y) * sindf(rot_x);
        up.y = cosdf(rot_x);
        up.z = cosdf(rot_y) * sindf(rot_x);
        D_800D04B8_main[i][1] = pos.x;
        D_800D04B8_main[i][2] = pos.z;
        D_800D04B8_main[i][0] = CRotM[i].y; // actually D_800CE178_main?
        D_800D04B8_main[i][3] = gCameraList[i].fov;
        D_800D04B8_main[i][4] = D_800CCF98_main[i];
        D_800D04B8_main[i][5] = D_800D4198_main[i];
        Hu3DCamSetPositionOrientation(i, &pos, &at, &up);
        Hu3DCamUpdateMtx(i);

        length = HuSqrtf((CenterM[i].x - pos.x) * (CenterM[i].x - pos.x) +
                         (CenterM[i].y - pos.y) * (CenterM[i].y - pos.y) +
                         (CenterM[i].z - pos.z) * (CenterM[i].z - pos.z));
        data->scale.x = data->zoom / length * data->baseScale.x;
        data->scale.y = data->zoom / length * data->baseScale.y;
        func_8004CB44_main(&origin, &D_800CD2A8_main[i]);
        func_80012B14_main(0, &origin, &screenPos);
        func_80012B14_main(0, &data->origin, &screenOrigin);
        data->offset.x = (screenPos.x - screenOrigin.x) * data->baseScale.x;
        data->offset.y = (screenPos.y - screenOrigin.y) * data->baseScale.y;
        if (data->draw != NULL) {
            data->draw(data);
            if (i != object->work[0] - 1) {
                gDPPipeSync(gMainGfxPos++);
            }
        }
    }
    gSPEndDisplayList(gMainGfxPos++);
}

void func_8004CB44_main(Vec *out, Vec *normal) {
    Vec pos;
    f32 rot_x = CRot.x;
    f32 rot_y = CRot.y;
    f32 length;
    f32 x, y, z;
    f32 distance;

    pos.x = Center.x + sindf(rot_y) * cosdf(rot_x) * CZoom;
    pos.y = Center.y + -sindf(rot_x) * CZoom;
    pos.z = Center.z + cosdf(rot_y) * cosdf(rot_x) * CZoom;
    length = HuSqrtf((Center.x - pos.x) * (Center.x - pos.x) + (Center.y - pos.y) * (Center.y - pos.y) + (Center.z - pos.z) * (Center.z - pos.z));
    x = (pos.x - Center.x) / length;
    y = (pos.y - Center.y) / length;
    z = (pos.z - Center.z) / length;
    length = x * normal->x + y * normal->y + z * normal->z;
    distance = (-pos.x * normal->x + -pos.y * normal->y + -pos.z * normal->z) / length;
    out->x = x * distance + pos.x;
    out->y = y * distance + pos.y;
    out->z = z * distance + pos.z;
}

void func_8004CD04_main(Vec *pos, Vec *at, f32 *zoom, Vec *rot, Vec *center) {
    HuMtx4F matrix;
    f32 x = pos->x - at->x;
    f32 y = pos->y - at->y;
    f32 z = pos->z - at->z;
    f32 angle;
    f32 rotatedX, rotatedY;

    *zoom = HuSqrtf(x * x + y * y + z * z);
    angle = atan2df(z, x);
    rot->y = -(angle - 90.0f);
    angle = -angle;
    matrix[0][0] = matrix[2][2] = cosdf(angle);
    matrix[2][0] = -sindf(angle);
    matrix[0][2] = sindf(angle);
    matrix[1][1] = matrix[3][3] = 1.0f;
    matrix[1][0] = matrix[3][0] = matrix[0][1] = matrix[2][1] = matrix[3][1] = matrix[1][2] =
        matrix[3][2] = matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    rotatedX = x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0];
    rotatedY = x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1];
    rot->x = -atan2df(rotatedY, rotatedX);
    rot->z = 0;
    center->x = at->x;
    center->y = at->y;
    center->z = at->z;
}

void func_8004CEA4_main() {
    D_800CE194_main = omAddObj(0x7FD8, 0, 0, -1, func_8004CF00_main);
    omSetStatBit(D_800CE194_main, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_800CE194_main->work[0] = D_800D6AB8_main;
}

void func_8004CF00_main(omObjData *object) {
    u32 *counter = object->work;

    if (*counter == 0) {
        D_800D530C_main = 1;
    } else {
        *counter -= 1;
    }
}

void func_8004CF30_main(void) {
    UnkAudioObjData *data;
    s32 i;

    D_800D6A40_main = omAddObj(0x7FD8, 0, 0, -1, func_8004D094_main);
    data = D_800D6A40_main->data = HuMemAllocTag(sizeof(UnkAudioObjData), TAG_OVERLAY);
    func_80000EA8_main(&D_800D1398_main);
    D_800A1910_main = D_800D13EE_main;
    data->unk00 = HuMemAllocTag(D_800A1910_main * sizeof(f32), TAG_OVERLAY);
    data->unk04 = HuMemAllocTag(D_800A1910_main * sizeof(f32), TAG_OVERLAY);
    data->unk08 = HuMemAllocTag(D_800A1910_main * sizeof(f32), TAG_OVERLAY);
    data->unk0C = HuMemAllocTag(D_800A1910_main * sizeof(f32), TAG_OVERLAY);
    data->unk10 = HuMemAllocTag(D_800A1910_main, TAG_OVERLAY);
    omSetStatBit(D_800D6A40_main, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    for (i = 0; i < D_800A1910_main; i++) {
        data->unk10[i] = 0;
    }
    data->unk14 = 0;
    data->unk24 = -1.0f;
    data->unk1C = 0;
    data->unk18 = 0;
    data->unk16 = 0;
    data->unk28 = -1.0f;
    data->unk20 = 0;
    data->unk1A = 0;
    data->unk34 = -1;
}

void func_8004D094_main(omObjData *object) {
    UnkAudioObjData *data = D_800D6A40_main->data;
    s16 i;
    u8 flags;
    s32 active;
    f32 volume;

    for (i = 0; i < D_800A1910_main; i++) {
        flags = data->unk10[i];
        active = func_800078F8_main(i);
        if (flags & 2) {
            if (active == 0) {
                data->unk10[i] &= ~1;
                data->unk10[i] &= ~4;
            } else if (flags & 4) {
                data->unk08[i] -= data->unk0C[i];
                if (data->unk08[i] <= 0.0f) {
                    data->unk08[i] = 0.0f;
                    func_80007B28_main(i, 0);
                    data->unk10[i] &= ~4;
                } else {
                    func_80007B28_main(i, (s16)data->unk08[i]);
                }
            }
        } else if (data->unk10[i] & 1) {
            if (active == 0) {
                data->unk10[i] &= ~1;
            } else {
                data->unk00[i] -= data->unk04[i];
                if (data->unk00[i] <= 0.0f) {
                    data->unk00[i] = 0.0f;
                    func_80007B28_main(i, 0);
                    func_80007DD8_main(i);
                    data->unk10[i] &= ~1;
                } else {
                    func_80007B28_main(i, (s16)data->unk00[i]);
                }
            }
        }
    }
    if ((D_800A1906_main & 0x10) && data->unk34 >= 0) {
        func_8004A72C_main(data->unk34);
        data->unk34 = -1;
    }
    if (data->unk14 == 1) {
        volume = data->unk2C += data->unk1C;
        if (data->unk1C < 0.0f) {
            if (volume < 0.0f) {
                volume = data->unk2C = 0.0f;
                data->unk14 = 0;
            }
        } else if (volume > data->unk24) {
            volume = data->unk2C = data->unk24;
            data->unk14 = 0;
        }
        func_800036E8_main(D_800CDBC8_main, volume);
    }
    if (data->unk16 == 1) {
        volume = data->unk30 += data->unk20;
        if (data->unk20 < 0.0f) {
            if (volume < 0.0f) {
                volume = data->unk30 = 0.0f;
                data->unk16 = 0;
            }
        } else if (volume > data->unk28) {
            volume = data->unk30 = data->unk28;
            data->unk16 = 0;
        }
        func_800036E8_main(D_800D037E_main, volume);
    }
}
