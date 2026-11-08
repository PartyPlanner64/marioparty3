#include "common.h"
#include "game/input.h"
#include "game/malloc.h"
#include "game/mallocblock.h"
#include "math.h"
#include "overlays/mgmode.h"

extern u8 D_8011B630_mgmode[0x20];
extern s16 D_8011B650_mgmode;
extern s16 D_8011B652_mgmode;
extern u16 *D_8011B654_mgmode[3];
extern void *D_8011B660_mgmode;
extern s16 D_8011A3E0_mgmode;
extern s16 D_8011B664_mgmode;
extern s16 D_8011B666_mgmode;
extern s16 D_8011B668_mgmode;
extern s16 D_8011B66A_mgmode;
extern s16 D_8011B66C_mgmode;
extern s16 D_8011B66E_mgmode;
extern s32 D_8011A3E4_mgmode[4];
extern s16 D_8011A3F4_mgmode;
extern s16 D_8011A3F8_mgmode[];
extern MgmodeSpaceCoord *D_8011B670_mgmode;
extern s16 D_8011B678_mgmode[4][4];
extern s16 D_8011B698_mgmode[4];
extern s16 D_8011B808_mgmode;

void func_801180A4_mgmode(void);
void func_801188BC_mgmode(omObjData *obj);
void func_801189C4_mgmode(s16 model);
void func_80118B8C_mgmode(s16 model);

s16 func_80116B20_mgmode(void) {
    s16 sprGrp;
    s16 i;

    D_8011A3E0_mgmode = func_8000B838_main(0x12000E);
    sprGrp = espEntry(D_8011A3E0_mgmode, 0, 1);
    D_8011B650_mgmode = sprGrp;
    for (i = 0; i < ARRAY_COUNT(D_8011B654_mgmode); i++) {
        D_8011B654_mgmode[i] = HuMemAllocTag(0x6000, TAG_OVERLAY);
    }
    D_8011B660_mgmode = HuSprGet(D_800CD1DC_main[sprGrp].unk04, 0)->unk_84->unk00->unk00;
    D_8011B652_mgmode = 0;
    espDispOff(sprGrp);
    return sprGrp;
}

void func_80116C18_mgmode(s16 arg0) {
    HvqImageHeader *imageData;
    HvqFileHeader *decodeData;
    u8 *workBuffer;

    imageData = DataRead(arg0 | 0x170000);
    decodeData = DataRead((arg0 + 1) | 0x170000);
    hvqMpsInit1(0xFF);
    hvqMpsDecodeStart1(decodeData);
    workBuffer = HuMemMemoryAllocPerm(0xC00);
    hvqMpsDecode1(imageData, D_8011B654_mgmode[D_8011B652_mgmode], 0x80, workBuffer);
    HuMemMemoryFreePerm(workBuffer);
    DataClose(imageData);
    DataClose(decodeData);
    HuSprGet(D_800CD1DC_main[D_8011B650_mgmode].unk04, 0)->unk_84->unk00->unk00 =
        D_8011B654_mgmode[D_8011B652_mgmode];
    D_8011B652_mgmode++;
    if (D_8011B652_mgmode >= ARRAY_COUNT(D_8011B654_mgmode)) {
        D_8011B652_mgmode = 0;
    }
    espDispOn(D_8011B650_mgmode);
}

void func_80116D4C_mgmode(void) {
    s16 i;

    if (D_8011A3E0_mgmode != -1) {
        HuSprGet(D_800CD1DC_main[D_8011B650_mgmode].unk04, 0)->unk_84->unk00->unk00 =
            D_8011B660_mgmode;
        espKill(D_8011B650_mgmode);
        HuSprAnimKill(D_8011A3E0_mgmode);
        for (i = 0; i < ARRAY_COUNT(D_8011B654_mgmode); i++) {
            HuMemFree(D_8011B654_mgmode[i]);
        }
        D_8011A3E0_mgmode = -1;
    }
}

typedef struct CamData {
    Vec rot;
    Vec center;
    f32 zoom;
    f32 unk_1C;
} CamData;

extern f32 D_8011B6A4_mgmode;
extern Vec D_8011B898_mgmode;
extern CamData *D_8011B954_mgmode;
extern s8 D_8011B958_mgmode;

void func_80116E24_mgmode(s16 arg0) {
    CRot = D_8011B954_mgmode[arg0].rot;
    D_8011B898_mgmode = CRot;

    Center = D_8011B954_mgmode[arg0].center;
    CZoom = D_8011B954_mgmode[arg0].zoom;

    D_8011B6A4_mgmode = D_8011B954_mgmode[arg0].unk_1C;
    D_8011B958_mgmode = arg0;
}

void func_80116ED4_mgmode(s16 presetIdx, s16 duration, s16 easeType, void (*callback)(s16 *)) {
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
    rot = D_8011B954_mgmode[presetIdx].rot;
    center = D_8011B954_mgmode[presetIdx].center;
    zoom = D_8011B954_mgmode[presetIdx].zoom;

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
    unkDelta = D_8011B954_mgmode[presetIdx].unk_1C - D_8011B6A4_mgmode;
    cbArg[1] = duration;
    unkStart = D_8011B6A4_mgmode;
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
            D_8011B898_mgmode.x = CRot.x = t * rotDelta.x + rotStart.x;
            D_8011B898_mgmode.y = CRot.y = t * rotDelta.y + rotStart.y;
            D_8011B898_mgmode.z = CRot.z = t * rotDelta.z + rotStart.z;
            Center.x = t * centerDelta.x + centerStart.x;
            Center.y = t * centerDelta.y + centerStart.y;
            Center.z = t * centerDelta.z + centerStart.z;
            CZoom = t * zoomDelta + zoomStart;
            D_8011B6A4_mgmode = t * unkDelta + unkStart;
            if (callback != (void (*)(s16 *))-1) {
                cbArg[0] = i;
                cb(cbArg);
            }
            HuPrcVSleep();
        }
    } else {
        for (i = 0; i <= duration; i++) {
            t = (1.0f / duration) * i;
            D_8011B898_mgmode.x = CRot.x = t * rotDelta.x + rotStart.x;
            D_8011B898_mgmode.y = CRot.y = t * rotDelta.y + rotStart.y;
            D_8011B898_mgmode.z = CRot.z = t * rotDelta.z + rotStart.z;
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
    func_80116E24_mgmode(presetIdx);
}

void func_801177BC_mgmode(Vec *eye, Vec *center) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47DD90", func_801178E0_mgmode);

void func_80117DD0_mgmode(void) {
    s16 prev = -1;
    s16 startX;
    s16 startY;
    s16 dx;
    s16 dy;
    f32 t;

    D_8011B66E_mgmode = 0;
    D_8011B66C_mgmode = espEntry(func_8000B838_main(0x11000E), 0, 1);
    espPriSet(D_8011B66C_mgmode, 1);
    espPosSet(D_8011B66C_mgmode, 160, 120);
    espDispOff(D_8011B66C_mgmode);
    D_8011B664_mgmode = 160;
    D_8011B666_mgmode = 120;
    D_8011B668_mgmode = 10;
    omAddPrcObj(func_801180A4_mgmode, 0x3F00, 0x800, 0);
    while (TRUE) {
        HuPrcVSleep();
        if (D_8011B66E_mgmode == 0) {
            prev = D_8011B66A_mgmode;
        } else if (prev != D_8011B66A_mgmode && D_8011B66A_mgmode != -1) {
            if (D_8011B670_mgmode[D_8011B66A_mgmode].x != D_8011B664_mgmode ||
                D_8011B670_mgmode[D_8011B66A_mgmode].y != D_8011B666_mgmode) {
                startX = D_8011B664_mgmode;
                startY = D_8011B666_mgmode;
                dx = D_8011B670_mgmode[D_8011B66A_mgmode].x - startX;
                dy = D_8011B670_mgmode[D_8011B66A_mgmode].y - startY;
                for (prev = 1; prev <= D_8011B668_mgmode; prev++) {
                    t = sindf(90.0f / D_8011B668_mgmode * prev);
                    D_8011B664_mgmode = startX + dx * t;
                    D_8011B666_mgmode = startY + dy * t;
                    espPosSet(D_8011B66C_mgmode, D_8011B664_mgmode, D_8011B666_mgmode);
                    HuPrcVSleep();
                }
            }
            prev = D_8011B66A_mgmode;
        }
        espPosSet(D_8011B66C_mgmode, D_8011B664_mgmode, D_8011B666_mgmode);
    }
}

void func_801180A4_mgmode(void) {
    s16 prev = 0;
    s16 i;

    while (TRUE) {
        HuPrcVSleep();
        if (prev == D_8011B66E_mgmode) {
            continue;
        }
        if (D_8011B66E_mgmode != 0) {
            espDispOn(D_8011B66C_mgmode);
            for (i = 0; i < 5; i++) {
                espTPLvlSet(D_8011B66C_mgmode, i * 63.75f);
                HuPrcVSleep();
            }
        } else {
            for (i = 0; i < 5; i++) {
                espTPLvlSet(D_8011B66C_mgmode, 255.0f - i * 63.75f);
                HuPrcVSleep();
            }
            espDispOff(D_8011B66C_mgmode);
        }
        prev = D_8011B66E_mgmode;
    }
}

void func_801181F4_mgmode(s16 index) {
    D_8011B664_mgmode = D_8011B670_mgmode[index].x;
    D_8011B666_mgmode = D_8011B670_mgmode[index].y;
    D_8011B66A_mgmode = index;
}

void func_8011822C_mgmode(MgmodeSpaceCoord *arg0) {
    s16 i;
    MgmodeSpaceCoord *p;

    D_8011B670_mgmode = arg0;
    for (i = 0; ((p = (MgmodeSpaceCoord *)(i * sizeof(MgmodeSpaceCoord) + (u32)arg0))->x != -1) ||
                p->y != p->x;
         i++) {
        D_8011B630_mgmode[i] = 0;
    }
}

void func_8011829C_mgmode(s16 arg0) {
    D_8011B668_mgmode = arg0;
}

void func_801182A8_mgmode(s16 arg0) {
    D_8011B66A_mgmode = arg0;
}

void func_801182B4_mgmode(s16 arg0) {
    D_8011B66E_mgmode = arg0;
}

void func_801182C0_mgmode(s16 index) {
    D_8011B630_mgmode[index] = 1;
}

s16 func_801182DC_mgmode(s16 stickX, s16 stickY) {
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

    for (i = 0; D_8011B670_mgmode[i].x != -1 || D_8011B670_mgmode[i].y != D_8011B670_mgmode[i].x; i++) {
        if (i == D_8011B66A_mgmode || D_8011B630_mgmode[i] != 0) {
            dist[i] = -1.0f;
        } else {
            dx = D_8011B670_mgmode[D_8011B66A_mgmode].x - D_8011B670_mgmode[i].x;
            dy = D_8011B670_mgmode[D_8011B66A_mgmode].y - D_8011B670_mgmode[i].y;
            dist[i] = HuSqrtf(dx * dx + dy * dy);
            len = dist[i];
            dir[i][0] = dx / len;
            dir[i][1] = dy / len;
        }
    }
    len = HuSqrtf(stickX * stickX + stickY * stickY);
    nx = stickX / len;
    ny = stickY / len;
    for (i = 0; D_8011B670_mgmode[i].x != -1 || D_8011B670_mgmode[i].y != D_8011B670_mgmode[i].x; i++) {
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
    for (i = 0; D_8011B670_mgmode[i].x != -1 || D_8011B670_mgmode[i].y != D_8011B670_mgmode[i].x; i++) {
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

void func_80118624_mgmode(s16 dstModel, s16 srcModel) {
    HmfModelData[dstModel].pos.x = HmfModelData[srcModel].pos.x;
    HmfModelData[dstModel].pos.y = HmfModelData[srcModel].pos.y;
    HmfModelData[dstModel].pos.z = HmfModelData[srcModel].pos.z;
}

s16 func_80118678_mgmode(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    omObjData *obj;
    HmfModelData_UnkBC_Struct *bc;
    s16 model;
    s16 anim;
    s16 i;

    for (i = 0; i < 4; i++) {
        model = func_8000B108_main(D_8011A3E4_mgmode[i], 0x2A9);
        D_8011B678_mgmode[D_8011A3F4_mgmode][i] = model;
        anim = HmfAnimRead(HmfModelData[model].hmf, 0xB0048, "e268p01_I8");
        Hu3DModelCameraSet(model, 2);
        func_8003302C_main(anim, i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        func_8001C2FC_main(model, 0x20000, 0x20000);
        Hu3DModelRemakeStatic(model);
        func_8001C954_main(model);
        func_8001C514_main(model);
        func_80013390_main(model, -1, 0, func_80118B8C_mgmode);
        bc = HmfModelData[model].unkBC;
        bc->unk1C.f = arg0;
        bc->unk20.f = arg1;
        bc->unk24.f = arg2;
        bc->unk08.f = arg3;
        func_8001C258_main(model, 4, 4);
    }
    obj = omAddObj(10, 10, 10, -1, func_801188BC_mgmode);
    obj->work[0] = D_8011A3F4_mgmode;
    D_8011A3F4_mgmode++;
    return obj->work[0];
}

void func_80118888_mgmode(s16 index) {
    D_8011A3F8_mgmode[index] = 1;
}

void func_801188A4_mgmode(s16 index) {
    D_8011A3F8_mgmode[index] = 0;
}

void func_801188BC_mgmode(omObjData *obj) {
    s16 index = obj->work[0];
    s16 i;

    if (D_8011A3F8_mgmode[index] != 0) {
        for (i = 0; i < 4; i++) {
            func_8001C258_main(D_8011B678_mgmode[index][i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            if (((D_8011B698_mgmode[index] + i) & 3) == 0) {
                func_801189C4_mgmode(D_8011B678_mgmode[index][i]);
            }
        }
        D_8011B698_mgmode[index]++;
    }
}

void func_801189C4_mgmode(s16 model) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = HmfModelData[model].unkBC;
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

void func_80118B8C_mgmode(s16 model) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = HmfModelData[model].unkBC;
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

void func_80118CD8_mgmode(void) {
    _ClearFlag(0x1C);
    SLCommonSet(1);
    _ClearFlag(0xD);
    _SetFlag(0x1C);
}

void func_80118D0C_mgmode(void) {
    f32 x;
    f32 y;
    f32 dist;

    y = 0.0f;
    x = y;
    if (D_800CDA7C_main[D_8011B808_mgmode] & 0x200) {
        x = -1.0f;
    }
    if (D_800CDA7C_main[D_8011B808_mgmode] & 0x100) {
        x += 1.0f;
    }
    if (D_800CDA7C_main[D_8011B808_mgmode] & 0x800) {
        y += 1.0f;
    }
    if (D_800CDA7C_main[D_8011B808_mgmode] & 0x400) {
        y += -1.0f;
    }
    if (x == 0.0f && y == 0.0f) {
        return;
    }
    dist = HuSqrtf(x * x + y * y);
    D_800CBB6E_main[D_8011B808_mgmode] = x / dist * 50.0f;
    D_800D20A1_main[D_8011B808_mgmode] = y / dist * 50.0f;
}
