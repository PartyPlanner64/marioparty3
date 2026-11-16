#include "common.h"
#include "game/input.h"
#include "game/malloc.h"
#include "game/mallocblock.h"
#include "math.h"
#include "mgmode.h"

extern u8 mgmode_cursorDisableTbl[0x20];
extern s16 mgmode_mgPicSpr;
extern s16 mgmode_mgPicBufNo;
extern u16 *mgmode_mgPicBufTbl[3];
extern void *mgmode_mgPicOrigData;
extern s16 mgmode_cursorX;
extern s16 mgmode_cursorY;
extern s16 mgmode_cursorMoveTime;
extern s16 mgmode_cursorSel;
extern s16 mgmode_cursorSpr;
extern s16 mgmode_cursorDispF;
extern MgmodeSpaceCoord *mgmode_cursorPosTbl;
extern s16 mgmode_confettiMdlTbl[4][4];
extern s16 mgmode_confettiCntTbl[4];
extern s16 mgmode_padNo;

void mgmode_CursorFadeProc(void);
void mgmode_ConfettiObjMain(omObjData *obj);
void mgmode_ConfettiParticleAdd(s16 model);
void mgmode_ConfettiHook(s16 model);

s16 mgmode_mgPicAnim = -1;
s32 mgmode_confettiMdlFileTbl[4] = {
    0xB002B, 0xB002C, 0xB002D, 0xB002E
};
s16 mgmode_confettiNum = 0;
s16 mgmode_confettiOnTbl[4] = { 0 };

s16 mgmode_MgPicCreate(void) {
    s16 sprGrp;
    s16 i;

    mgmode_mgPicAnim = HuSprAnimDataRead(0x12000E);
    sprGrp = espEntry(mgmode_mgPicAnim, 0, 1);
    mgmode_mgPicSpr = sprGrp;
    for (i = 0; i < ARRAY_COUNT(mgmode_mgPicBufTbl); i++) {
        mgmode_mgPicBufTbl[i] = HuMemAllocTag(0x6000, TAG_OVERLAY);
    }
    mgmode_mgPicOrigData = HuSprGet(esprite[sprGrp].unk04, 0)->data->pat->data;
    mgmode_mgPicBufNo = 0;
    espDispOff(sprGrp);
    return sprGrp;
}

void mgmode_MgPicLoad(s16 arg0) {
    HvqImageHeader *imageData;
    HvqFileHeader *decodeData;
    u8 *workBuffer;

    imageData = DataRead(arg0 | 0x170000);
    decodeData = DataRead((arg0 + 1) | 0x170000);
    hvqMpsInit1(0xFF);
    hvqMpsDecodeStart1(decodeData);
    workBuffer = HuMemMemoryAllocPerm(0xC00);
    hvqMpsDecode1(imageData, mgmode_mgPicBufTbl[mgmode_mgPicBufNo], 0x80, workBuffer);
    HuMemMemoryFreePerm(workBuffer);
    DataClose(imageData);
    DataClose(decodeData);
    HuSprGet(esprite[mgmode_mgPicSpr].unk04, 0)->data->pat->data =
        mgmode_mgPicBufTbl[mgmode_mgPicBufNo];
    mgmode_mgPicBufNo++;
    if (mgmode_mgPicBufNo >= ARRAY_COUNT(mgmode_mgPicBufTbl)) {
        mgmode_mgPicBufNo = 0;
    }
    espDispOn(mgmode_mgPicSpr);
}

void mgmode_MgPicKill(void) {
    s16 i;

    if (mgmode_mgPicAnim != -1) {
        HuSprGet(esprite[mgmode_mgPicSpr].unk04, 0)->data->pat->data =
            mgmode_mgPicOrigData;
        espKill(mgmode_mgPicSpr);
        HuSprAnimKill(mgmode_mgPicAnim);
        for (i = 0; i < ARRAY_COUNT(mgmode_mgPicBufTbl); i++) {
            HuMemFree(mgmode_mgPicBufTbl[i]);
        }
        mgmode_mgPicAnim = -1;
    }
}

extern f32 mgmode_cameraFov;
extern Vec mgmode_cameraRot;
extern ModeCameraPreset *mgmode_cameraPresetTbl;
extern s8 mgmode_cameraPresetNo;

void mgmode_CameraPresetSet(s16 arg0) {
    CRot = mgmode_cameraPresetTbl[arg0].rot;
    mgmode_cameraRot = CRot;

    Center = mgmode_cameraPresetTbl[arg0].center;
    CZoom = mgmode_cameraPresetTbl[arg0].zoom;

    mgmode_cameraFov = mgmode_cameraPresetTbl[arg0].fov;
    mgmode_cameraPresetNo = arg0;
}

void mgmode_CameraPresetMove(s16 presetIdx, s16 duration, s16 easeType, void (*callback)(s16 *)) {
    Vec rotDelta;
    Vec centerDelta;
    Vec rotStart;
    Vec centerStart;
    Vec rot;
    Vec center;
    s16 cbArg[24];
    Vec eye;
    void (*cb)(s16 *);
    f32 zoom;
    f32 zoomDelta;
    f32 zoomStart;
    f32 unkDelta;
    f32 unkStart;
    f64 t;
    s16 i;

    cb = callback;
    rot = mgmode_cameraPresetTbl[presetIdx].rot;
    center = mgmode_cameraPresetTbl[presetIdx].center;
    zoom = mgmode_cameraPresetTbl[presetIdx].zoom;

    eye.x = sindf(rot.y) * cosdf(rot.x) * zoom + center.x;
    eye.y = -sindf(rot.x) * zoom + center.y;
    eye.z = cosdf(rot.y) * cosdf(rot.x) * zoom + center.z;
    t = 100.0f / zoom;
    center.x = eye.x + (center.x - eye.x) * t;
    center.y = eye.y + (center.y - eye.y) * t;
    center.z = eye.z + (center.z - eye.z) * t;
    zoom = 100.0f;

    t = rot.x - CRot.x;
    if ((t < 0.0 ? -t : t) > 180.0) {
        if (rot.x < CRot.x) {
            rotDelta.x = t + 360.0;
        } else {
            rotDelta.x = t - 360.0;
        }
    } else {
        rotDelta.x = t;
    }
    t = rot.y - CRot.y;
    if ((t < 0.0 ? -t : t) > 180.0) {
        if (rot.y < CRot.y) {
            rotDelta.y = t + 360.0;
        } else {
            rotDelta.y = t - 360.0;
        }
    } else {
        rotDelta.y = t;
    }
    t = rot.z - CRot.z;
    if ((t < 0.0 ? -t : t) > 180.0) {
        if (rot.z < CRot.z) {
            rotDelta.z = t + 360.0;
        } else {
            rotDelta.z = t - 360.0;
        }
    } else {
        rotDelta.z = t;
    }

    centerDelta.x = center.x - Center.x;
    centerDelta.y = center.y - Center.y;
    centerDelta.z = center.z - Center.z;
    zoomDelta = zoom - CZoom;
    unkDelta = mgmode_cameraPresetTbl[presetIdx].fov - mgmode_cameraFov;
    cbArg[1] = duration;
    unkStart = mgmode_cameraFov;
    centerStart = Center;
    rotStart = CRot;
    zoomStart = CZoom;

    if (easeType == 1 || easeType == 2) {
        for (i = 0; i < duration; i++) {
            if (easeType != 2) {
                t = sindf(i * 90.0f / duration);
            } else if (i <= duration / 2) {
                t = (1.0f - cosdf(i * 180.0f / duration)) * 0.5f;
            } else {
                t = -cosdf(i * 180.0f / duration) * 0.5f + 0.5f;
            }
            mgmode_cameraRot.x = CRot.x = t * rotDelta.x + rotStart.x;
            mgmode_cameraRot.y = CRot.y = t * rotDelta.y + rotStart.y;
            mgmode_cameraRot.z = CRot.z = t * rotDelta.z + rotStart.z;
            Center.x = t * centerDelta.x + centerStart.x;
            Center.y = t * centerDelta.y + centerStart.y;
            Center.z = t * centerDelta.z + centerStart.z;
            CZoom = t * zoomDelta + zoomStart;
            mgmode_cameraFov = t * unkDelta + unkStart;
            if (callback != (void (*)(s16 *))-1) {
                cbArg[0] = i;
                cb(cbArg);
            }
            HuPrcVSleep();
        }
    } else {
        for (i = 0; i <= duration; i++) {
            t = (1.0f / duration) * i;
            mgmode_cameraRot.x = CRot.x = t * rotDelta.x + rotStart.x;
            mgmode_cameraRot.y = CRot.y = t * rotDelta.y + rotStart.y;
            mgmode_cameraRot.z = CRot.z = t * rotDelta.z + rotStart.z;
            Center.x = t * centerDelta.x + centerStart.x;
            Center.y = t * centerDelta.y + centerStart.y;
            Center.z = t * centerDelta.z + centerStart.z;
            CZoom = t * zoomDelta + zoomStart;
            if (callback != (void (*)(s16 *))-1) {
                cbArg[0] = i;
                cb(cbArg);
            }
            HuPrcVSleep();
        }
    }
    mgmode_CameraPresetSet(presetIdx);
}

void mgmode_CameraLookAtSet(Vec *eye, Vec *center) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 angle;

    dx = eye->x - center->x;
    dy = eye->y - center->y;
    dz = eye->z - center->z;
    CZoom = HuSqrtf((dx * dx) + (dy * dy) + (dz * dz));
    angle = atan2df(dz, dx);
    CRot.y = -(angle - 90.0f);
    angle = -angle;
    dx = dx * cosdf(angle) + dz * -sindf(angle);
    CRot.x = -atan2df(dy, dx);
    CRot.z = 0.0f;
    Center = *center;
}

void mgmode_CameraRotPosCalc(Vec *center, Vec *rot, f32 zoom, Vec *pos, Vec *at, Vec *up) {
    f32 rotX, rotY, rotZ;
    f32 upX, upY, upZ;
    f32 dx, dy, dz;
    f32 length;

    rotX = rot->x;
    rotY = rot->y;
    rotZ = rot->z;
    pos->x = sindf(rotY) * cosdf(rotX) * zoom + center->x;
    pos->y = -sindf(rotX) * zoom + center->y;
    pos->z = cosdf(rotY) * cosdf(rotX) * zoom + center->z;
    *at = *center;
    upX = sindf(rotY) * sindf(rotX);
    upY = cosdf(rotX);
    upZ = cosdf(rotY) * sindf(rotX);
    dx = at->x - pos->x;
    dy = at->y - pos->y;
    dz = at->z - pos->z;
    length = dx * dx + dy * dy + dz * dz;
    length = HuSqrtf(length);
    dx /= length;
    dy /= length;
    dz /= length;
    up->x = upX * (dx * dx + (1.0f - dx * dx) * cosdf(rotZ)) +
            upY * (dx * dy * (1.0f - cosdf(rotZ)) - dz * sindf(rotZ)) +
            upZ * (dx * dz * (1.0f - cosdf(rotZ)) + dy * sindf(rotZ));
    up->y = upX * (dx * dy * (1.0f - cosdf(rotZ)) + dz * sindf(rotZ)) +
            upY * (dy * dy + (1.0f - dy * dy) * cosdf(rotZ)) +
            upZ * (dy * dz * (1.0f - cosdf(rotZ)) - dx * sindf(rotZ));
    up->z = upX * (dx * dz * (1.0f - cosdf(rotZ)) - dy * sindf(rotZ)) +
            upY * (dy * dz * (1.0f - cosdf(rotZ)) + dx * sindf(rotZ)) +
            upZ * (dz * dz + (1.0f - dz * dz) * cosdf(rotZ));
}

void mgmode_CursorProc(void) {
    s16 prev = -1;
    s16 startX;
    s16 startY;
    s16 dx;
    s16 dy;
    f32 t;

    mgmode_cursorDispF = 0;
    mgmode_cursorSpr = espEntry(HuSprAnimDataRead(0x11000E), 0, 1);
    espPriSet(mgmode_cursorSpr, 1);
    espPosSet(mgmode_cursorSpr, 160, 120);
    espDispOff(mgmode_cursorSpr);
    mgmode_cursorX = 160;
    mgmode_cursorY = 120;
    mgmode_cursorMoveTime = 10;
    omAddPrcObj(mgmode_CursorFadeProc, 0x3F00, 0x800, 0);
    while (TRUE) {
        HuPrcVSleep();
        if (mgmode_cursorDispF == 0) {
            prev = mgmode_cursorSel;
        } else if (prev != mgmode_cursorSel && mgmode_cursorSel != -1) {
            if (mgmode_cursorPosTbl[mgmode_cursorSel].x != mgmode_cursorX ||
                mgmode_cursorPosTbl[mgmode_cursorSel].y != mgmode_cursorY) {
                startX = mgmode_cursorX;
                startY = mgmode_cursorY;
                dx = mgmode_cursorPosTbl[mgmode_cursorSel].x - startX;
                dy = mgmode_cursorPosTbl[mgmode_cursorSel].y - startY;
                for (prev = 1; prev <= mgmode_cursorMoveTime; prev++) {
                    t = sindf(90.0f / mgmode_cursorMoveTime * prev);
                    mgmode_cursorX = startX + dx * t;
                    mgmode_cursorY = startY + dy * t;
                    espPosSet(mgmode_cursorSpr, mgmode_cursorX, mgmode_cursorY);
                    HuPrcVSleep();
                }
            }
            prev = mgmode_cursorSel;
        }
        espPosSet(mgmode_cursorSpr, mgmode_cursorX, mgmode_cursorY);
    }
}

void mgmode_CursorFadeProc(void) {
    s16 prev = 0;
    s16 i;

    while (TRUE) {
        HuPrcVSleep();
        if (prev == mgmode_cursorDispF) {
            continue;
        }
        if (mgmode_cursorDispF != 0) {
            espDispOn(mgmode_cursorSpr);
            for (i = 0; i < 5; i++) {
                espTPLvlSet(mgmode_cursorSpr, i * 63.75f);
                HuPrcVSleep();
            }
        } else {
            for (i = 0; i < 5; i++) {
                espTPLvlSet(mgmode_cursorSpr, 255.0f - i * 63.75f);
                HuPrcVSleep();
            }
            espDispOff(mgmode_cursorSpr);
        }
        prev = mgmode_cursorDispF;
    }
}

void mgmode_CursorSelSet(s16 index) {
    mgmode_cursorX = mgmode_cursorPosTbl[index].x;
    mgmode_cursorY = mgmode_cursorPosTbl[index].y;
    mgmode_cursorSel = index;
}

void mgmode_CursorPosTblSet(MgmodeSpaceCoord *arg0) {
    s16 i;
    MgmodeSpaceCoord *p;

    mgmode_cursorPosTbl = arg0;
    for (i = 0; ((p = (MgmodeSpaceCoord *)(i * sizeof(MgmodeSpaceCoord) + (u32)arg0))->x != -1) ||
                p->y != p->x;
         i++) {
        mgmode_cursorDisableTbl[i] = 0;
    }
}

void mgmode_CursorMoveTimeSet(s16 arg0) {
    mgmode_cursorMoveTime = arg0;
}

void mgmode_CursorSelMove(s16 arg0) {
    mgmode_cursorSel = arg0;
}

void mgmode_CursorDispSet(s16 arg0) {
    mgmode_cursorDispF = arg0;
}

void mgmode_CursorDisableSet(s16 index) {
    mgmode_cursorDisableTbl[index] = 1;
}

s16 mgmode_CursorPadNextGet(s16 stickX, s16 stickY) {
    f32 dir[32][2];
    f32 dist[32];
    f32 dx;
    f32 dy;
    f32 len;
    f32 nx;
    f32 ny;
    f32 minDist;
    s16 best;
    s16 i;

    for (i = 0; mgmode_cursorPosTbl[i].x != -1 || mgmode_cursorPosTbl[i].y != mgmode_cursorPosTbl[i].x; i++) {
        if (i == mgmode_cursorSel || mgmode_cursorDisableTbl[i] != 0) {
            dist[i] = -1.0f;
        } else {
            dx = mgmode_cursorPosTbl[mgmode_cursorSel].x - mgmode_cursorPosTbl[i].x;
            dy = mgmode_cursorPosTbl[mgmode_cursorSel].y - mgmode_cursorPosTbl[i].y;
            dist[i] = HuSqrtf(dx * dx + dy * dy);
            len = dist[i];
            dir[i][0] = dx / len;
            dir[i][1] = dy / len;
        }
    }
    len = HuSqrtf(stickX * stickX + stickY * stickY);
    nx = stickX / len;
    ny = stickY / len;
    for (i = 0; mgmode_cursorPosTbl[i].x != -1 || mgmode_cursorPosTbl[i].y != mgmode_cursorPosTbl[i].x; i++) {
        if (dist[i] < 0.0f) {
            continue;
        }
        dx = nx - dir[i][0];
        dy = ny - dir[i][1];
        if (HuSqrtf(dx * dx + dy * dy) > 0.5f) {
            dist[i] = -1.0f;
        }
    }
    minDist = 100000.0f;
    best = -1;
    for (i = 0; mgmode_cursorPosTbl[i].x != -1 || mgmode_cursorPosTbl[i].y != mgmode_cursorPosTbl[i].x; i++) {
        if (dist[i] < 0.0f) {
            continue;
        }
        if (dist[i] < minDist) {
            minDist = dist[i];
            best = i;
        }
    }
    return best;
}

void mgmode_MdlPosCopy(s16 dstModel, s16 srcModel) {
    Hu3DData[dstModel].pos.x = Hu3DData[srcModel].pos.x;
    Hu3DData[dstModel].pos.y = Hu3DData[srcModel].pos.y;
    Hu3DData[dstModel].pos.z = Hu3DData[srcModel].pos.z;
}

s16 mgmode_ConfettiCreate(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    omObjData *obj;
    HmfModelData_UnkBC_Struct *bc;
    s16 model;
    s16 anim;
    s16 i;

    for (i = 0; i < 4; i++) {
        model = Hu3DModelRead(mgmode_confettiMdlFileTbl[i], 0x2A9);
        mgmode_confettiMdlTbl[mgmode_confettiNum][i] = model;
        anim = Hu3DAnimRead(Hu3DData[model].hmf, 0xB0048, "e268p01_I8");
        Hu3DModelCameraSet(model, 2);
        Hu3DAnmNoSet(anim, i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
        Hu3DModelRemakeStatic(model);
        Hu3DModelVtxBufMake(model);
        Hu3DModelDynamicFree(model);
        Hu3DParticleCreate(model, -1, 0, mgmode_ConfettiHook);
        bc = Hu3DData[model].unkBC;
        bc->unk1C.f = arg0;
        bc->unk20.f = arg1;
        bc->unk24.f = arg2;
        bc->unk08.f = arg3;
        Hu3DModelAttrSet(model, 4, 4);
    }
    obj = omAddObj(10, 10, 10, -1, mgmode_ConfettiObjMain);
    obj->work[0] = mgmode_confettiNum;
    mgmode_confettiNum++;
    return obj->work[0];
}

void mgmode_ConfettiOn(s16 index) {
    mgmode_confettiOnTbl[index] = 1;
}

void mgmode_ConfettiOff(s16 index) {
    mgmode_confettiOnTbl[index] = 0;
}

void mgmode_ConfettiObjMain(omObjData *obj) {
    s16 index = obj->work[0];
    s16 i;

    if (mgmode_confettiOnTbl[index] != 0) {
        for (i = 0; i < 4; i++) {
            Hu3DModelAttrSet(mgmode_confettiMdlTbl[index][i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            if (((mgmode_confettiCntTbl[index] + i) & 3) == 0) {
                mgmode_ConfettiParticleAdd(mgmode_confettiMdlTbl[index][i]);
            }
        }
        mgmode_confettiCntTbl[index]++;
    }
}

void mgmode_ConfettiParticleAdd(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = bc->unk58;
    s16 spread = bc->unk08.f;
    s16 count = hmf->unk1A;
    s16 i;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 <= 0.0f) {
            particle->unk0C = (((rand8() << 1) * spread) >> 8) + bc->unk1C.f - spread;
            particle->unk10 = bc->unk20.f;
            particle->unk14 = (((rand8() << 1) * spread) >> 8) + bc->unk24.f - spread;
            particle->unk18 = ((s32)((rand8() * 5U) >> 7) - 5) / 2;
            particle->unk1C = 0.0f;
            particle->unk20 = ((s32)((rand8() * 5U) >> 7) - 5) / 2;
            particle->unk08 = 2.0f;
            break;
        }
    }
}

void mgmode_ConfettiHook(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count = hmf->unk1A;
    s16 i;

    if (bc->unk02 == 0) {
        bc->unk04 &= ~4;
        particle = bc->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
            particle->unk08 = 0.0f;
            particle->unk04 = 1.0f;
        }
        bc->unk02++;
    }
    particle = bc->unk58;
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 > 0.0f) {
            particle->unk0C += particle->unk18;
            particle->unk10 += particle->unk1C - 8.0f;
            particle->unk14 += particle->unk20;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}

void mgmode_RecordSave(void) {
    _ClearFlag(0x1C);
    SLCommonSet(1);
    _ClearFlag(0xD);
    _SetFlag(0x1C);
}

void mgmode_DpadStickSet(void) {
    f32 x;
    f32 y;
    f32 dist;

    y = 0.0f;
    x = y;
    if (HuPadBtn[mgmode_padNo] & 0x200) {
        x = -1.0f;
    }
    if (HuPadBtn[mgmode_padNo] & 0x100) {
        x += 1.0f;
    }
    if (HuPadBtn[mgmode_padNo] & 0x800) {
        y += 1.0f;
    }
    if (HuPadBtn[mgmode_padNo] & 0x400) {
        y += -1.0f;
    }
    if (x == 0.0f && y == 0.0f) {
        return;
    }
    dist = HuSqrtf(x * x + y * y);
    HuPadStkX[mgmode_padNo] = x / dist * 50.0f;
    HuPadStkY[mgmode_padNo] = y / dist * 50.0f;
}
