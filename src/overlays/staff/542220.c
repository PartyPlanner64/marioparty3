#include "common.h"
#include "game/aura.h"
#include "game/gamemes.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "gcc/memory.h"
#include "overlays/msetup.h"
#include "../ovl_81_name/ovl_81.h"

typedef struct UnkStaff {
    char unk_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} UnkStaff;

typedef struct UnkStaff_1 {
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ char unk_20[8];
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ char unk_2A[2];
} UnkStaff_1;

typedef struct UnkStaff_2 { // sizeof 0x4C
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ char unk_24[0x28];
} UnkStaff_2;

typedef struct UnkStaff_8 { // sizeof 0x6
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
} UnkStaff_8;

typedef struct StaffModelEntry { // sizeof 0x18
    /* 0x00 */ f32 scale;
    /* 0x04 */ s32 dataId;
    /* 0x08 */ s32 motDataId;
    /* 0x0C */ UnkStaff_8 unk_0C;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 animNo;
} StaffModelEntry;

typedef struct StaffAnimEntry { // sizeof 0x8
    /* 0x00 */ s32 dataNum;
    /* 0x04 */ char *name;
} StaffAnimEntry;

typedef struct UnkStaff_3 { // sizeof 0x3C
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ char unk_0C[0x10];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ char unk_20[2];
    /* 0x22 */ UnkStaff_8 unk_22;
    /* 0x28 */ s16 unk_28[4];
    /* 0x30 */ char unk_30[2];
    /* 0x32 */ s16 unk_32;
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ char unk_38[2];
    /* 0x3A */ s16 unk_3A;
} UnkStaff_3;

typedef struct UnkStaff_4 {
    /* 0x00 */ UnkStaff_3 *unk_00;
    /* 0x04 */ char unk_04[4];
    /* 0x08 */ s16 unk_08;
} UnkStaff_4;

typedef struct UnkStaff_5 { // sizeof 0x4C
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ char unk_24[0xC];
    /* 0x30 */ Vec unk_30;
    /* 0x3C */ char unk_3C[0x10];
} UnkStaff_5;

typedef struct UnkStaff_6 { // sizeof 0x8
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk_02[4];
    /* 0x06 */ s16 unk_06;
} UnkStaff_6;

typedef struct StaffPathSeg { // sizeof 0x8
    /* 0x00 */ f32 start;
    /* 0x04 */ f32 end;
} StaffPathSeg;

typedef struct StaffPath { // sizeof 0x10
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 flags;
    /* 0x04 */ char unk_04[4];
    /* 0x08 */ Vec *points;
    /* 0x0C */ StaffPathSeg *segs;
} StaffPath;

typedef struct UnkStaff_7 { // sizeof 0x14
    /* 0x00 */ Vec2f *unk_00;
    /* 0x04 */ f32 *unk_04;
    /* 0x08 */ f32 *unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 count;
} UnkStaff_7;

void func_80105BD4_staff(omObjData *object);
void func_80105CB4_staff(omObjData *object);
void func_80105DB8_staff(MsetupModelEntry *entry, s16 model);
void func_80105E6C_staff(MsetupModelEntry *entry, MsetupModelHandle *handle, s32 count);
u32 func_80105F48_staff(u32 seed);
void func_8010615C_staff(void);
void func_80106720_staff(void);
void func_80106C50_staff(void);
void func_80106E20_staff(void);
void func_80107508_staff(void);
void func_80107EB8_staff(void);
void func_80109264_staff(void);
void func_801095E4_staff(void);
void func_801088F4_staff(StaffPath *path, f32 t, Vec *out);
void func_8010B514_staff(s16 arg0, s16 arg1);
void func_8010B794_staff(s16 arg0);
void func_8010BF84_staff(void);
void func_8010D1E8_staff(void);
void func_8010D998_staff(void);
void func_8010DEE4_staff(UnkStaff_2 *arg0, f32 x, f32 y, f32 z);
void func_8010DEF4_staff(UnkStaff_2 *arg0, f32 x, f32 y, f32 z);
void func_8010DF04_staff(UnkStaff_2 *arg0, s16 arg1);
void func_8010DF34_staff(void);
void func_8010C680_staff(s16 *, s32 *, f32 *, void *);
void func_8010C8F4_staff(UnkStaff_1 *);
void func_8010CD74_staff(UnkStaff_1 *);
void func_8010CFD4_staff(UnkStaff *);
void func_8010FB88_staff(void);
extern u16 D_80110530_staff;
extern f32 D_80110534_staff;
extern s8 D_80110538_staff;
extern u32 D_8011053C_staff;
extern MsetupCameraPreset D_80110560_staff;
extern s32 D_8011058C_staff[4];
extern s32 D_801105F0_staff[2];
extern Vec D_801105F8_staff[2];
extern f32 D_80110610_staff[2];
extern Vec D_80110618_staff[];
extern Vec D_80110648_staff[];
extern s16 D_8011066C_staff[4];
extern StaffAnimEntry D_80110674_staff[];
extern u8 D_8011059C_staff[4];
extern u16 D_801105A0_staff[4];
extern f32 D_801105A8_staff[4];
extern MsetupModelEntry D_80110FF4_staff[];
extern s16 D_80111510_staff;
extern s16 D_80111512_staff;
extern s16 D_80111514_staff;
extern s16 D_80111516_staff;
extern MsetupPlayerConfig D_80111518_staff;
extern s16 D_80111530_staff;
extern s16 D_80111532_staff;
extern s16 D_8011154C_staff;
extern Vec D_80111550_staff;
extern s16 D_8011155C_staff;
extern Vec D_80111534_staff;
extern Vec D_80111540_staff;
extern f32 D_80111560_staff;
extern f32 D_80111564_staff;
extern s16 D_80111490_staff[27];
extern UnkStaff_6 *D_801114C8_staff;
extern s16 D_801114D0_staff[28];
extern UnkStaff_6 *D_80111508_staff;
extern s16 D_8011150C_staff;
extern s16 D_8011150E_staff;
extern f32 D_800D5210_main;
extern f32 D_800CB890_main;

void func_801059A0_staff(void) {
    Hu3DCamInit(1);
    func_8001FE20_main(1);
    func_800142A0_main(25);
    omInitObjMan(51, 25);
    HuWinInit();
    func_8004A208_main();
    D_800CD280_main = 0;
    D_80111564_staff = 80.0f;
    D_80111560_staff = 6000.0f;
    D_80110534_staff = 58.0f;
    Hu3DCameraPerspectiveSet(0, D_80110534_staff, D_80111564_staff, D_80111560_staff);
    D_80111550_staff.x = 0;
    D_80111550_staff.y = 0;
    D_80111550_staff.z = 0;
    CRot.x = 0;
    CRot.y = 0;
    CRot.z = 0;
    func_8010615C_staff();
    omAddObj(10000, 0, 0, -1, func_80105BD4_staff);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightDirSet(2, 0.0f, 0.0f, 100.0f);
    Hu3DGLightColorSet(3, 240, 240, 240);
    Hu3DGLightDirSet(3, 0.0f, 100.0f, 0.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DBGColorSet(0, 0, 0);
    omPrcSetStatBit(omAddPrcObj(func_80106720_staff, 0x1100, 0x400, 0), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_8011155C_staff = 0;
    func_80106C50_staff();
    D_80111514_staff = 0;
    D_80111512_staff = 0;
    if (omovlevtno >= 0 && omovlevtno < 6) {
        D_80111514_staff = omovlevtno;
    } else if (omovlevtno >= 6) {
        D_80111514_staff = GwStory.unk1;
        D_80111512_staff = 1;
    }
    omAddPrcObj(func_80106E20_staff, 0x3F00, 0x1000, 0);
    WipeColorSet(0, 0, 0);
    D_80111530_staff = 11;
    D_8011154C_staff = 20;
}

void func_80105BD4_staff(omObjData *object) {
    if (D_80111512_staff == 0 && (D_800D5558_main[D_80111510_staff] & 0x1000)) {
        D_8011155C_staff = 0;
        D_80110530_staff = 1;
    }
    if (D_80110530_staff == 0) {
        if (D_800D530C_main != 0) {
            goto createWipe;
        }
    } else if (D_80110530_staff == 1) {
        goto createWipe;
    } else {
        D_80110530_staff--;
    }
    return;

createWipe:
    if (D_80111530_staff >= 0) {
        WipeCreateOut(D_80111530_staff, D_8011154C_staff);
    }
    HuAudSeqFadeOut(15);
    object->func = func_80105CB4_staff;
}

void func_80105CB4_staff(omObjData *object) {
    u16 flags;

    if (WipeStatGet() == 0) {
        HuWinAllKill();
        flags = 0x14;
        switch (D_8011155C_staff) {
            case 0:
            default:
                if (D_80111512_staff != 0) {
                    omovlhisidx = -1;
                    omOvlCallEx(0x58, 0, 0x84);
                } else {
                    omOvlReturnEx(1);
                }
                break;
            case 2:
                omOvlCallEx(D_80111516_staff, D_80111532_staff, flags);
                break;
            case 1:
                omOvlGotoEx(D_80111516_staff, D_80111532_staff, flags);
                break;
            case 3:
                omOvlGotoEx(D_80111516_staff, D_80111532_staff, 0x4090);
                break;
            case 4:
                omOvlGotoEx(D_80111516_staff, D_80111532_staff, 0x92);
                break;
        }
    }
}

void func_80105DB8_staff(MsetupModelEntry *entry, s16 model) {
    switch (entry->positionMode) {
        case 0:
            break;
        case 1:
            Hu3DModelPosSet(model, entry->pos.x, entry->pos.y, entry->pos.z);
            Hu3DModelRotSet(model, entry->rot.x, entry->rot.y, entry->rot.z);
            break;
        case 2:
            Hu3DModelPosSet(model, entry->pos.x * 5.0f, entry->pos.y * 5.0f, entry->pos.z * 5.0f);
            Hu3DModelRotSet(model, entry->rot.x, entry->rot.y, entry->rot.z);
            break;
    }
}

void func_80105E6C_staff(MsetupModelEntry *entry, MsetupModelHandle *handle, s32 count) {
    s16 i;
    s16 model;
    s32 motion;

    if (entry == NULL || handle == NULL) {
        return;
    }
    for (i = 0; i < count; entry++, i++, handle++) {
        model = handle->model = func_8000B108_main(entry->dataId, entry->flags);
        func_80105DB8_staff(entry, model);
        motion = handle->motion = Hu3DData[model].motId;
        if (motion >= 0) {
            func_8001C814_main(model, -1, entry->motion);
        }
    }
}

u32 func_80105F48_staff(u32 seed) {
    u32 quotient;
    u32 remainder;

    if (seed == 0) {
        seed = rand8();
        seed ^= osGetCount();
        seed ^= 0xD826BC89;
    }
    quotient = seed / 127773;
    remainder = seed % 127773;
    seed = quotient * 2836;
    return seed - remainder * 16807;
}

u32 func_8010601C_staff(void) {
    return D_8011053C_staff = func_80105F48_staff(D_8011053C_staff);
}

s32 func_80106044_staff(u32 limit) {
    u32 random;

    random = D_8011053C_staff = func_80105F48_staff(D_8011053C_staff);
    return (random & 0x7FFFFFFF) % limit;
}

void func_8010609C_staff(MsetupCameraPreset *preset) {
    CRot = preset->rot;
    D_80111550_staff = CRot;
    Center = preset->center;
    CZoom = preset->zoom;
    if (preset->fov != D_80110534_staff) {
        D_80110534_staff = preset->fov;
        Hu3DCameraPerspectiveSet(0, D_80110534_staff, D_80111564_staff, D_80111560_staff);
    }
}

#ifdef NON_MATCHING
// Instruction scheduling differs around the Center address load.
void func_8010615C_staff(void) {
    Vec pos, at, up;
    f32 rotX, rotY, rotZ;
    f32 upX, upY, upZ;
    f32 dx, dy, dz;
    f32 length;

    if (D_80110538_staff == 0) {
        rotX = CRot.x;
        rotY = CRot.y;
        rotZ = CRot.z;
        pos.x = sindf(rotY) * cosdf(rotX) * CZoom + Center.x;
        pos.y = -sindf(rotX) * CZoom + Center.y;
        pos.z = cosdf(rotY) * cosdf(rotX) * CZoom + Center.z;
        at.x = Center.x;
        at.y = Center.y;
        at.z = Center.z;
        upX = sindf(rotY) * sindf(rotX);
        upY = cosdf(rotX);
        upZ = cosdf(rotY) * sindf(rotX);
        dx = at.x - pos.x;
        dy = at.y - pos.y;
        dz = at.z - pos.z;
        length = dx * dx + dy * dy + dz * dz;
        length = HuSqrtf(length);
        dx /= length;
        dy /= length;
        dz /= length;
        up.x = upX * (dx * dx + (1.0f - dx * dx) * cosdf(rotZ)) +
               upY * (dx * dy * (1.0f - cosdf(rotZ)) - dz * sindf(rotZ)) +
               upZ * (dx * dz * (1.0f - cosdf(rotZ)) + dy * sindf(rotZ));
        up.y = upX * (dx * dy * (1.0f - cosdf(rotZ)) + dz * sindf(rotZ)) +
               upY * (dy * dy + (1.0f - dy * dy) * cosdf(rotZ)) +
               upZ * (dy * dz * (1.0f - cosdf(rotZ)) - dx * sindf(rotZ));
        up.z = upX * (dx * dz * (1.0f - cosdf(rotZ)) - dy * sindf(rotZ)) +
               upY * (dy * dz * (1.0f - cosdf(rotZ)) + dx * sindf(rotZ)) +
               upZ * (dz * dz + (1.0f - dz * dz) * cosdf(rotZ));
    } else {
        pos = D_80111540_staff;
        at = D_80111534_staff;
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
    }
    D_800CE17C_main[0] = pos.x;
    D_800CE17C_main[1] = pos.z;
    D_800CE17C_main[-1] = CRot.y;
    D_800CE17C_main[2] = gCameraList->fov;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &pos, &at, &up);
    Hu3DCamUpdateMtx(0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010615C_staff);
#endif

void func_80106720_staff(void) {
    while (1) {
        func_8010615C_staff();
        HuPrcVSleep();
    }
}

void func_8010674C_staff(MsetupCameraKeyframe *keys, f32 speed, void (*callback)(s16, s16, s16)) {
    MsetupCameraKeyframe interpolated;
    f32 values[4];
    f32 times[4];
    MsetupCameraKeyframe *key;
    f32 *p0;
    f32 *p1;
    f32 *p2;
    f32 *p3;
    f32 *out;
    f32 oldX;
    f32 oldY;
    f32 oldZ;
    f32 x;
    f32 y;
    f32 z;
    f32 duration;
    f32 distance;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 i;
    s16 component;
    s16 segment;
    void (*onFrame)(s16, s16, s16) = callback;

    duration = oldX = oldY = oldZ = 0.0f;
    for (i = 0, key = keys; key->values.preset.zoom != 0.0f; i++, key = &keys[i]) {
        if (speed != 0.0f) {
            x = sindf(key->values.preset.rot.y) * cosdf(key->values.preset.rot.x) * key->values.preset.zoom + key->values.preset.center.x;
            y = -sindf(key->values.preset.rot.x) * key->values.preset.zoom + key->values.preset.center.y;
            z = cosdf(key->values.preset.rot.y) * cosdf(key->values.preset.rot.x) * key->values.preset.zoom + key->values.preset.center.z;
            if (i > 0) {
                dx = oldX - x;
                dy = oldY - y;
                dz = oldZ - z;
                dx = dx * dx + dy * dy;
                dz *= dz;
                distance = dx + dz;
                distance = HuSqrtf(distance);
                if (distance == 0.0f) {
                    distance = speed * 10.0f;
                }
                duration += distance / speed;
                key->time = duration;
            }
            oldX = x;
            oldY = y;
            oldZ = z;
        } else {
            duration = key->time;
        }
    }
    duration -= 10.0f;
    for (i = 10, segment = 1; i < duration; i++) {
        if (i > keys[segment + 1].time) {
            segment++;
        }
        times[0] = keys[segment - 1].time;
        times[1] = keys[segment].time;
        times[2] = keys[segment + 1].time;
        times[3] = keys[segment + 2].time;
        p0 = keys[segment - 1].values.components;
        p1 = keys[segment].values.components;
        p2 = keys[segment + 1].values.components;
        p3 = keys[segment + 2].values.components;
        out = interpolated.values.components;
        for (component = 0; component < 8; component++) {
            values[0] = *p0++;
            values[1] = *p1++;
            values[2] = *p2++;
            values[3] = *p3++;
            *out++ = InterpolateBMLine(values, times, i);
        }
        Center.x = interpolated.values.preset.center.x;
        Center.y = interpolated.values.preset.center.y;
        Center.z = interpolated.values.preset.center.z;
        D_80111550_staff.x = CRot.x = interpolated.values.preset.rot.x;
        D_80111550_staff.y = CRot.y = interpolated.values.preset.rot.y;
        D_80111550_staff.z = CRot.z = interpolated.values.preset.rot.z;
        CZoom = interpolated.values.preset.zoom;
        gCameraList->fov = D_80110534_staff = interpolated.values.preset.fov;
        if (callback != NULL) {
            onFrame((s16)duration, segment, i);
        }
        HuPrcVSleep();
    }
    segment++;
    D_80111550_staff.x = CRot.x = keys[segment].values.preset.rot.x;
    D_80111550_staff.y = CRot.y = keys[segment].values.preset.rot.y;
    D_80111550_staff.z = CRot.z = keys[segment].values.preset.rot.z;
    CZoom = keys[segment].values.preset.zoom;
    Center.x = keys[segment].values.preset.center.x;
    Center.y = keys[segment].values.preset.center.y;
    Center.z = keys[segment].values.preset.center.z;
    gCameraList->fov = D_80110534_staff = keys[segment].values.preset.fov;
    D_800CB99C_main = 0;
}

// This function matches, but the original has alignment padding after it
// (a new source file likely begins at func_80106E20_staff), so it remains
// assembly until the segment is split.
#ifdef NON_MATCHING
void func_80106C50_staff(void) {
    s16 i;
    s16 connectedCount;
    s16 port;
    s16 j;

    for (i = 0; i < 4; i++) {
        D_80111518_staff.controllerPorts[i] = 0xFF;
        D_80111518_staff.characters[i] = i;
        D_80111518_staff.cpuDifficulty[i] = 0xFF;
        D_80111518_staff.stars[i] = 0;
    }
    for (i = 0, connectedCount = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            D_80111518_staff.controllerPorts[connectedCount] = i;
            connectedCount++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (D_80111518_staff.controllerPorts[i] == 0xFF) {
            for (port = 0; port < 4; port++) {
                for (j = 0; j < 4; j++) {
                    if (D_80111518_staff.controllerPorts[j] == port) {
                        break;
                    }
                }
                if (j == 4) {
                    break;
                }
            }
            D_80111518_staff.controllerPorts[i] = port;
        }
    }
    D_80111518_staff.totalTurns = 0;
    D_80111518_staff.unk16 = 0;
    D_80111518_staff.unk13 = 0;
    D_80111518_staff.connectedCount = connectedCount;
    D_80111518_staff.humanCount = 0;
    D_80111518_staff.cpuCount = 4;
    D_80111518_staff.boardIndex = 0;
    D_80111510_staff = D_80111518_staff.controllerPorts[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80106C50_staff);
#endif

const char D_80111204_staff[] = "";

const char D_80111208_staff[] = "MARIO PARTY 3 STAFF";

void func_80106E20_staff(void) {
    GAMEMES gMes;
    s16 stat0;
    s16 stat1;
    s16 stat2;
    s16 stat3;
    s16 stat4;
    s16 stat5;
    s16 stat6;
    s16 strId;
    s16 grpId;
    s16 tpLvl;
    s16 time;
    s32 i;

    D_800CD280_main = 1;
    func_8010609C_staff(&D_80110560_staff);
    func_8010B514_staff(0, 6);
    func_8010B514_staff(1, 12);
    stat0 = 0;
    omAddPrcObj(func_80107EB8_staff, 0x4200, 0x800, 0)->user_data = &stat0;
    stat1 = 0;
    omAddPrcObj(func_801095E4_staff, 0x4000, 0, 0)->user_data = &stat1;
    stat2 = 0;
    omAddPrcObj(func_8010BF84_staff, 0x4000, 0, 0)->user_data = &stat2;
    stat3 = 0;
    omAddPrcObj(func_80109264_staff, 0x4000, 0, 0)->user_data = &stat3;
    stat4 = 0;
    omAddPrcObj(func_80107508_staff, 0x1000, 0, 0)->user_data = &stat4;
    strId = func_8003A308_main(&gMes, (char *)D_80111208_staff, 0, -1, -1);
    grpId = gMes.strGId[strId];
    HuSprPosSet(grpId, 0, 160, 120);
    for (i = 1; i < 20; i++) {
        HuSprTPLvlSet(grpId, i, 0);
        HuSprDispOff(grpId, i);
    }
    WipeCreateIn(D_80111530_staff, 16);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    HuAudSeqPlay(6);
    stat4 = 1;
    for (time = 30; time != 0; time--) {
        HuPrcVSleep();
    }
    for (i = 1; i < 20; i++) {
        HuSprDispOn(grpId, i);
    }
    for (tpLvl = 64; tpLvl <= 256; tpLvl += 64) {
        for (i = 1; i < 20; i++) {
            HuSprTPLvlSet(grpId, i, tpLvl);
        }
        HuPrcVSleep();
    }
    stat4 = 2;
    for (time = 180; time != 0; time--) {
        HuPrcVSleep();
    }
    for (tpLvl = 240; tpLvl >= 0; tpLvl -= 16) {
        for (i = 1; i < 20; i++) {
            HuSprTPLvlSet(grpId, i, tpLvl);
        }
        HuPrcVSleep();
    }
    func_8003B128_main(&gMes);
    stat0 = 2;
    HuPrcVSleep();
    stat3 = 1;
    do {
        HuPrcVSleep();
    } while (stat3 >= 0);
    stat0 = stat1 = 1;
    for (time = 120; time != 0; time--) {
        HuPrcVSleep();
    }
    stat2 = 1;
    do {
        HuPrcVSleep();
    } while (stat2 != 0);
    stat1 = 2;
    HuAudFXPlay(0x229);
    HuAudSeqFadeOut(240);
    for (time = 75; time != 0; time--) {
        HuPrcVSleep();
    }
    WipeColorSet(0, 0, 0);
    WipeCreateOut(11, 4);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    func_8010B794_staff(0);
    func_8010B794_staff(1);
    stat0 = stat1 = -1;
    HuPrcSleep(2);
    stat5 = 1;
    omAddPrcObj(func_8010D1E8_staff, 0x4000, 0x1800, 0)->user_data = &stat5;
    while (stat5 != 0) {
        HuPrcVSleep();
    }
    HuAudSeqPlay(0x4E);
    WipeCreateIn(11, 4);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    for (time = 180; time != 0; time--) {
        HuPrcVSleep();
    }
    HuAudSeqFadeOut(0x4A);
    WipeCreateOut(11, 24);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    stat5 = -1;
    stat6 = 1;
    omAddPrcObj(func_8010D998_staff, 0x4000, 0x1000, 0)->user_data = &stat6;
    while (stat6 != 0) {
        HuPrcVSleep();
    }
    WipeCreateIn(11, 24);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    stat6 = 1;
    HuAudFXPlay(0x22A);
    while (stat6 != 0) {
        HuPrcVSleep();
    }
    while (TRUE) {
        if ((D_800D5558_main[0] & 0xD000) || (D_800D5558_main[1] & 0xD000) || (D_800D5558_main[2] & 0xD000) ||
            (D_800D5558_main[3] & 0xD000)) {
            break;
        }
        HuPrcVSleep();
    }
    D_80110530_staff = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_801073EC_staff(UnkStaff_2 *arg0, s32 arg1) {
    u32 random;
    s32 x;
    s32 y;

    random = func_8010601C_staff();
    x = (random & 0xFF) - 128;
    y = -500 - ((random >> 8) & 0xFF);
    func_8010DEF4_staff(arg0, x, y, 0.0f);
    x = func_80106044_staff(100) + arg1 * 500 - 550;
    y = (func_8010601C_staff() & 0x3F) + 218;
    func_8010DEE4_staff(arg0, x, y, func_80106044_staff(500) - 800);
    func_8010DF04_staff(arg0, func_80106044_staff(60) + 30);
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107508_staff);

UnkStaff_7 *func_80107740_staff(void) {
    UnkStaff_7 *work;
    UnkStaff_7 *ptr;
    Vec2f *pos;
    f32 *vel;
    f32 *speed;
    f32 baseSpeed;
    f32 spread;
    u32 random;
    s32 x;
    s32 y;
    s16 i;
    s16 j;
    s16 grpId;
    s16 animId;
    u16 pri;
    s16 count;
    u8 red;
    u8 green;
    u8 blue;

    work = HuMemAllocTag(sizeof(UnkStaff_7) * 4, TAG_OVERLAY);
    memset(work, 0, sizeof(UnkStaff_7) * 4);
    for (i = 0, ptr = work; i < 4; i++, ptr++) {
        count = D_8011059C_staff[i];
        pos = HuMemAllocTag(count * sizeof(Vec2f), TAG_OVERLAY);
        vel = HuMemAllocTag(count * sizeof(f32), TAG_OVERLAY);
        speed = HuMemAllocTag(count * sizeof(f32), TAG_OVERLAY);
        grpId = HuSprGrpCreate(count, 0);
        animId = func_8000B838_main(D_8011058C_staff[i]);
        pri = D_801105A0_staff[i];
        ptr->unk_00 = pos;
        ptr->unk_0C = grpId;
        ptr->unk_0E = animId;
        ptr->unk_04 = vel;
        ptr->unk_08 = speed;
        ptr->count = count;
        baseSpeed = D_801105A8_staff[i];
        for (j = 0; j < count; j++, pos++, vel++, speed++) {
            HuSprTPLvlSet(grpId, j, 0x100);
            HuSprAttrReset(grpId, j, 0xFFFF);
            HuSprAttrSet(grpId, j, 0x5000);
            HuSprScaleSet(grpId, j, 1.0f, 1.0f);
            func_800550F4_main(grpId, j, 0);
            HuSprGrpMemberSet(grpId, j, animId, 0);
            HuSprPriSet(grpId, j, pri);
            random = func_8010601C_staff();
            red = random | 0xC0;
            random >>= 7;
            green = random | 0xC0;
            random >>= 7;
            blue = random | 0xC0;
            HuSprColorSet(grpId, j, red, green, blue);
            random = func_8010601C_staff() & 0x7FFFFFFF;
            x = random % 320;
            random >>= 6;
            y = random % 304 - 64;
            pos->x = x;
            pos->y = y;
            HuSprPosSet(grpId, j, x, y);
            *vel = 0;
            spread = baseSpeed / 16.0f;
            random >>= 6;
            x = (random & 3) - 1;
            *speed = baseSpeed + spread * x;
        }
    }
    return work;
}

void func_80107A9C_staff(UnkStaff_7 *arg0) {
    s32 i;
    UnkStaff_7 *ptr;

    for (i = 0, ptr = arg0; i < 4; i++, ptr++) {
        HuSprGrpKill(ptr->unk_0C);
        HuSprAnimKill(ptr->unk_0E);
        HuMemFree(ptr->unk_00);
        HuMemFree(ptr->unk_04);
        HuMemFree(ptr->unk_08);
    }
    HuMemFree(arg0);
}

void func_80107B1C_staff(UnkStaff_7 *arg0, f32 arg1) {
    s16 i;
    s16 j;
    s16 count;
    f32 *dest;
    f32 *src;
    UnkStaff_7 *ptr;

    for (i = 0, ptr = arg0; i < 4; i++, ptr++) {
        dest = ptr->unk_04;
        src = ptr->unk_08;
        count = ptr->count;
        for (j = 0; j < count; j++, dest++, src++) {
            *dest = arg1 * *src;
        }
    }
}

void func_80107BA0_staff(UnkStaff_7 *arg0) {
    UnkStaff_7 *ptr;
    Vec2f *pos;
    f32 *vel;
    u32 random;
    s16 x;
    s16 i;
    s16 j;
    s16 grpId;
    s16 count;

    for (i = 0, ptr = arg0; i < 4; i++, ptr++) {
        vel = ptr->unk_04;
        grpId = ptr->unk_0C;
        pos = ptr->unk_00;
        count = ptr->count;
        for (j = 0; j < count; j++, pos++, vel++) {
            pos->y += *vel;
            if (pos->y >= 240.0f) {
                random = func_8010601C_staff() & 0x7FFFFFFF;
                if (i == 0) {
                    x = random % 160;
                    random >>= 5;
                    x += random % 160;
                    pos->x = x;
                } else {
                    pos->x = random % 320;
                }
                random >>= 6;
                pos->y = -(s32)(random & 0x1F);
            }
            HuSprPosSet(grpId, j, pos->x, pos->y);
        }
    }
}

const char D_80111228_staff[] = "";

void func_80107DBC_staff(UnkStaff_7 *arg0) {
    UnkStaff_7 *ptr;
    u32 random;
    s16 counter;
    s16 i;
    s16 j;
    s16 grpId;
    s16 count;
    s32 tpLvl;
    u32 bits;

    random = 0;
    counter = 0;
    for (i = 0, ptr = arg0; i < 4; i++, ptr++) {
        grpId = ptr->unk_0C;
        count = ptr->count;
        for (j = 0; j < count; j++) {
            counter -= 4;
            if (counter < 0) {
                counter = 31;
                random = func_8010601C_staff();
            }
            bits = random & 0xF;
            random >>= 4;
            tpLvl = 0x100;
            if (bits == 0) {
                tpLvl = 0xB4;
            }
            HuSprTPLvlSet(grpId, j, tpLvl);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80107EB8_staff);

StaffPath *func_801085F0_staff(Vec *points, s32 flags) {
    StaffPath *path;
    StaffPathSeg *seg;
    Vec *prev;
    Vec *cur;
    f32 total;
    f32 accum;
    f32 dist;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 count;
    s16 i;

    path = HuMemAllocTag(sizeof(StaffPath), TAG_OVERLAY);
    path->flags = flags;
    path->points = points;
    prev = points;
    cur = prev + 1;
    total = 0.0f;
    for (count = 0; cur->x != 9999.0f || cur->y != 9999.0f || cur->z != 9999.0f;
         count++, prev++, cur++) {
        dx = cur->x - prev->x;
        dy = cur->y - prev->y;
        dz = cur->z - prev->z;
        total += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    if (flags & 1) {
        dx = points->x - prev->x;
        dy = points->y - prev->y;
        dz = points->z - prev->z;
        total += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    count++;
    path->count = count;
    seg = HuMemAllocTag(count * sizeof(StaffPathSeg), TAG_OVERLAY);
    path->segs = seg;
    prev = points;
    cur = prev + 1;
    accum = 0.0f;
    for (i = 0; i < count; i++, prev++, cur++, seg++) {
        dx = cur->x - prev->x;
        dy = cur->y - prev->y;
        dz = cur->z - prev->z;
        if ((flags & 1) && i == count - 1) {
            dx = points->x - prev->x;
            dy = points->y - prev->y;
            dz = points->z - prev->z;
        }
        dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
        seg->start = accum / total;
        seg->end = (accum + dist) / total;
        if (seg->end > 1.0f) {
            seg->end = 1.0001f;
        }
        accum += dist;
    }
    return path;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801088F4_staff);

void func_8010919C_staff(StaffPath *path) {
    HuMemFree(path->segs);
    HuMemFree(path);
}

void func_801091CC_staff(Vec *out, Vec *center, f32 angle) {
    f32 x = cosdf(angle) * 1235.0f;
    f32 y = sindf(angle) * 880.0f;

    x += center->x;
    y += center->y;
    out->x = x;
    out->y = y;
    out->z = center->z;
}

void func_80109264_staff(void) {
    f32 angle[2];
    f32 speed[2];
    Vec pos;
    s16 model[2];
    s16 *stat;
    f32 rotZ;
    s32 i;
    s16 state;
    s16 modelId;

    rotZ = 0.0f;
    stat = HuPrcCurrentGet()->user_data;
    for (i = 0; i < 2; i++) {
        modelId = func_8000B108_main(D_801105F0_staff[i], 0x2A9);
        model[i] = modelId;
        func_8001C814_main(modelId, -1, 2);
        angle[i] = 270.0f;
        func_801091CC_staff(&pos, &D_801105F8_staff[i], 270.0f);
        Hu3DModelPosSet(modelId, pos.x, pos.y, pos.z);
    }
    func_800461B4_main(modelId);
    state = 0;
    speed[0] = speed[1] = 0.0f;
    while (state >= 0) {
        if (state != *stat) {
            switch (*stat) {
                case 0:
                    break;
                case 1:
                    speed[1] = -3.0f;
                    break;
                case 2:
                    speed[0] = 3.0f;
                    break;
                case 3:
                    state = -1;
                    continue;
            }
            state = *stat;
        }
        for (i = 0; i < 2; i++) {
            if (speed[i] == 0.0f) {
                continue;
            }
            angle[i] += speed[i];
            modelId = 0; // reused as an arrival flag
            if (speed[i] < 0.0f) {
                if (angle[i] <= D_80110610_staff[i]) {
                    modelId = 1;
                }
            } else {
                if (angle[i] >= D_80110610_staff[i]) {
                    modelId++;
                }
            }
            if (modelId) {
                angle[i] = D_80110610_staff[i];
                speed[i] = 0.0f;
                (*stat)++;
            }
            func_801091CC_staff(&pos, &D_801105F8_staff[i], angle[i]);
            Hu3DModelPosSet(model[i], pos.x, pos.y, pos.z);
            switch (i) {
                case 0:
                    rotZ = angle[i];
                    break;
                case 1:
                    rotZ = angle[i] - 180.0f;
                    break;
            }
            Hu3DModelRotSet(model[i], 0.0f, 0.0f, rotZ);
        }
        HuPrcVSleep();
    }
    func_80046558_main(model[1]);
    Hu3DModelKill(model[0]);
    Hu3DModelKill(model[1]);
    HuPrcVSleep();
    *stat = -1;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
// Register allocation differs: state/path use swapped saved registers, and the
// path interpolation factor uses swapped FPU temporaries.
void func_801095E4_staff(void) {
    Vec pos;
    StaffPath *path;
    s16 state;
    s16 *stat;
    StaffPath *nextPath;
    f32 rot;
    f32 angle;
    f32 rotSpeed;
    f32 rotTarget;
    f32 angleSpeed;
    s16 model;
    s32 done;

    state = 0;
    stat = HuPrcCurrentGet()->user_data;
    model = func_8000B108_main(0xA015F, 0x2A9);
    func_8001C814_main(model, -1, 2);
    path = func_801085F0_staff(D_80110618_staff, 0);
    nextPath = func_801085F0_staff(D_80110648_staff, 0);
    func_801088F4_staff(path, 0.0f, &pos);
    Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
    angle = 0.0f;
    angleSpeed = angle;
    rotTarget = angle;
    rotSpeed = rotTarget;
    rot = rotTarget;
    while (state >= 0) {
        if (state != *stat) {
            switch (*stat) {
                case 0:
                    break;
                case -1:
                    state = -1;
                    continue;
                case 1:
                    if (path != NULL) {
                        angle = 180.0f;
                        angleSpeed = 0.75f;
                        rotTarget = 8.0f;
                        rot = 0.0f;
                        rotSpeed = 8.0f / 240.0f;
                    }
                    break;
                case 2:
                    if (path == NULL && nextPath != NULL) {
                        path = nextPath;
                        angle = 180.0f;
                        angleSpeed = 2.0f;
                        rotTarget = 0.0f;
                        rot = 8.0f;
                        rotSpeed = -8.0f / 90.0f;
                        nextPath = NULL;
                    }
                    break;
            }
            state = *stat;
        }
        if (angleSpeed != 0.0f) {
            angle += angleSpeed;
            done = 0;
            if (angle >= 360.0f) {
                angle = 0.0f;
                angleSpeed = angle;
                done = 1;
            }
            func_801088F4_staff(path, (cosdf(angle) + 1.0f) * 0.5f, &pos);
            Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
            if (done) {
                func_8010919C_staff(path);
                path = NULL;
                *stat = 0;
            }
        }
        if (rotSpeed != 0.0f) {
            rot += rotSpeed;
            done = 0;
            if (rotSpeed < 0.0f) {
                if (rot <= rotTarget) {
                    done = 1;
                }
            } else {
                if (rot >= rotTarget) {
                    done++;
                }
            }
            if (done) {
                rotSpeed = 0.0f;
                rot = rotTarget;
            }
            Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
        }
        HuPrcVSleep();
    }
    Hu3DModelKill(model);
    *stat = 0;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_801095E4_staff);
#endif

void func_8010992C_staff(Process *prc, s16 modelId) {
    UnkStaff_4 *staff = prc->user_data;
    UnkStaff_3 *ptr = staff->unk_00;
    s32 i;

    for (i = 0; i < 3; i++, ptr++) {
        if (ptr->unk_3A != 3) {
            continue;
        }
        if (ptr->unk_1C == modelId) {
            break;
        }
    }
    if (i < 3) {
        ptr->unk_3A |= 4;
    }
}

s16 func_8010998C_staff(Process *prc, s16 *model, s16 *motion, Vec *pos) {
    UnkStaff_4 *staff = prc->user_data;
    s16 index = staff->unk_08;
    UnkStaff_3 *work = &staff->unk_00[index];
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s16 member;

    if (work->unk_3A == 0) {
        *model = -1;
        *motion = -1;
        return -1;
    }
    work->unk_3A |= 2;
    *model = work->unk_1C;
    *motion = work->unk_1E;
    work->unk_00 = *pos;
    x = pos->x + work->unk_22.unk_00;
    y = pos->y + work->unk_22.unk_02;
    z = pos->z + work->unk_22.unk_04;
    switch (work->unk_34) {
        case 4:
            Hu3DModelPosSet(work->unk_1C, x - work->unk_36, y, z);
            func_8001C258_main(work->unk_1C, 4, 0);
            Hu3DModelPosSet(work->unk_28[0], x + work->unk_36, y, z);
            func_8001C258_main(work->unk_28[0], 4, 0);
            break;
        case 7:
            Hu3DModelPosSet(work->unk_1C, x, y, z);
            func_8001C258_main(work->unk_1C, 4, 0);
            for (i = 0; i < 4; i++) {
                member = work->unk_28[i];
                Hu3DModelPosSet(member, x + D_8011066C_staff[i], y, z);
                func_8001C258_main(member, 4, 0);
            }
            break;
        case 8:
            Hu3DModelPosSet(work->unk_1C, x - work->unk_36, y, z);
            func_8001C258_main(work->unk_1C, 4, 0);
            Hu3DModelPosSet(work->unk_28[0], x + work->unk_36, y, z);
            func_8001C258_main(work->unk_28[0], 4, 0);
            break;
        case 10:
            Hu3DModelPosSet(work->unk_1C, x - work->unk_36, y, z);
            func_8001C258_main(work->unk_1C, 4, 0);
            Hu3DModelPosSet(work->unk_28[0], x + work->unk_36, y, z);
            func_8001C258_main(work->unk_28[0], 4, 0);
            break;
        case 0:
        default:
            Hu3DModelPosSet(work->unk_1C, x, y, z);
            func_8001C258_main(work->unk_1C, 4, 0);
            break;
    }
    if (++staff->unk_08 >= 3) {
        staff->unk_08 = 0;
    }
    return index;
}

void func_80109D08_staff(Process *prc, s16 modelId, Vec *pos) {
    UnkStaff_4 *staff = prc->user_data;
    UnkStaff_3 *ptr = staff->unk_00;
    s32 i;

    for (i = 0; i < 3; i++, ptr++) {
        if (ptr->unk_3A != 3) {
            continue;
        }
        if (ptr->unk_1C == modelId) {
            break;
        }
    }
    if (i < 3) {
        ptr->unk_00 = *pos;
    }
}

StaffModelEntry *func_80109D74_staff(UnkStaff_3 *work, StaffModelEntry *entry) {
    void *data;
    s32 i;
    s16 hasAnim;
    s16 model;
    s16 motion;

    for (i = 0; i < 3; i++, work++, entry++) {
        hasAnim = FALSE;
        work->unk_3A = 1;
        work->unk_34 = entry->unk_12;
        work->unk_22 = entry->unk_0C;
        model = func_8000B108_main(entry->dataId, 0x2AD);
        func_8001C814_main(model, -1, 2);
        Hu3DModelScaleSet(model, entry->scale, entry->scale, entry->scale);
        work->unk_32 = -1;
        if (entry->animNo != 0) {
            i = entry->animNo - 1;
            hasAnim = TRUE;
            data = DataRead(D_80110674_staff[i].dataNum);
            work->unk_32 = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, D_80110674_staff[i].name);
            HuMemMemoryFreePerm(data);
        }
        if (entry->motDataId != 0) {
            motion = func_8000B13C_main(entry->motDataId);
            func_8001C5B4_main(model, motion);
            func_8001C814_main(model, -1, 2);
        } else {
            motion = -1;
        }
        work->unk_1C = model;
        work->unk_1E = motion;
        if (hasAnim) {
            Hu3DModelRemakeStatic(model);
        }
        func_8001C514_main(model);
    }
    return entry;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_80109F34_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010A848_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B1E0_staff);

void func_8010B430_staff(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    HuSprGrp *grp = HuSprGrpData[arg0];
    HuSprite *sprite = grp->members[arg1];

    if ((u32)arg2 || (u32)arg3) {
        grp->dirty = 1;
        sprite->pos.x += arg2;
        sprite->pos.y += arg3;
    }
}

void func_8010B4B4_staff(s16 arg0, s16 arg1, s16 arg2) {
    f32 value = arg2;
    HuSprGrp *grp = HuSprGrpData[arg0];
    HuSprite *sprite = grp->members[arg1];

    if (sprite->pos.y == value) {
        return;
    }
    grp->dirty = 1;
    sprite->pos.y = value;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010B514_staff);

void func_8010B794_staff(s16 arg0) {
    UnkStaff_6 *recs;
    UnkStaff_6 *rec;
    s16 *anims;
    s8 animCount;
    s32 i;
    s16 count;

    switch (arg0) {
        case 0:
        default:
            recs = D_801114C8_staff;
            anims = D_80111490_staff;
            count = D_8011150C_staff;
            animCount = ARRAY_COUNT(D_80111490_staff);
            break;
        case 1:
            recs = D_80111508_staff;
            anims = D_801114D0_staff;
            count = D_8011150E_staff;
            animCount = ARRAY_COUNT(D_801114D0_staff);
            break;
    }

    if (recs != NULL) {
        for (i = 0, rec = recs; i < count; i++, rec++) {
            HuSprGrpKill(rec->unk_00);
        }
        HuMemFree(recs);
        for (i = 0; i < animCount; i++, anims++) {
            HuSprAnimKill(*anims);
        }
        switch (arg0) {
            case 0:
            default:
                D_801114C8_staff = NULL;
                break;
            case 1:
                D_80111508_staff = NULL;
                break;
        }
    }
}

void func_8010B8C0_staff(s16 arg0, s16 arg1, s16 visible) {
    UnkStaff_6 *rec;
    s32 i;
    s16 count;
    s16 grpId;

    switch (arg0) {
        case 0:
        default:
            rec = &D_801114C8_staff[arg1];
            break;
        case 1:
            rec = &D_80111508_staff[arg1];
            break;
    }

    count = rec->unk_06;
    if (count != 0) {
        grpId = rec->unk_00;
        if (visible) {
            for (i = 0; i < count; i++) {
                HuSprDispOn(grpId, i);
            }
        } else {
            for (i = 0; i < count; i++) {
                HuSprDispOff(grpId, i);
            }
        }
    }
}

void func_8010B9BC_staff(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    UnkStaff_6 *rec;

    switch (arg0) {
        case 0:
        default:
            rec = &D_801114C8_staff[arg1];
            break;
        case 1:
            rec = &D_80111508_staff[arg1];
            break;
    }

    if (rec->unk_06 != 0) {
        HuSprPosSet(rec->unk_00, 0, arg2, arg3);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BA30_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BE20_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011133C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111348_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111354_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111360_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011136C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111378_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111384_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111390_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011139C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113A8_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113B4_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113C0_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113CC_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113D8_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113E4_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_801113F0_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010BF84_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010C680_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010C8F4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010CD74_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010CFD4_staff);

void func_8010D1E8_staff(void) {
    MsetupModelHandle sp10[3];
    UnkStaff sp20[8];
    UnkStaff_1 sp120[3];
    s16 sp1A8;
    s32 sp1AC;
    f32 sp1B0;
    s16 var_v0;
    s16 *temp_s2;
    s16 var_s0;
    s32 i;
    UnkStaff_1 *temp;
    UnkStaff *temp2;
    MsetupModelHandle *temp3;

    temp_s2 = HuPrcCurrentGet()->user_data;
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackLoad(0x20);
    func_800E8180_name_81(1000.0f, 10000.0f);
    func_800E8110_name_81();
    D_80110538_staff = 1;
    D_80111540_staff.x = 350.0f;
    D_80111540_staff.y = 190.0f;
    D_80111540_staff.z = 3770.0f;
    D_80111534_staff.x = -1000.0f;
    D_80111534_staff.y = 130.0f;
    D_80111534_staff.z = 450.0f;
    D_80110534_staff = 40.0f;
    Hu3DCameraPerspectiveSet(0, 40.0f, D_80111564_staff, D_80111560_staff);
    func_80105E6C_staff(D_80110FF4_staff, sp10, 3);
    func_8010CFD4_staff(sp20);
    func_8010CD74_staff(sp120);
    *temp_s2 = 0;
    sp1A8 = 0;
    sp1B0 = 90.0f;
    sp1AC = 0;
    for (var_s0 = 0; var_s0 >= 0;) {
        if (var_s0 != *temp_s2) {
            if (*temp_s2 == -1) {
                var_s0 = -1;
            } else {
                var_s0 = *temp_s2;
                func_8010C8F4_staff(sp120);
                func_8010C680_staff(&sp1A8, &sp1AC, &sp1B0, &sp20[3]);
                HuPrcVSleep();
            }
        } else {
            func_8010C8F4_staff(sp120);
            func_8010C680_staff(&sp1A8, &sp1AC, &sp1B0, &sp20[3]);
            HuPrcVSleep();
        }
    }

    for (temp3 = sp10, i = 0; i < 3; i++, temp3++) {
        Hu3DModelKill(temp3->model);
    }
    for (temp2 = sp20, i = 0; i < 8; i++, temp2++) {
        Hu3DModelKill(temp2->unk_18);
        Hu3DModelKill(temp2->unk_1A);
        Hu3DAnimKill(temp2->unk_1C);
        if (temp2->unk_1E >= 0) {
            Hu3DModelKill(temp2->unk_1E);
        }
    }

    for (temp = sp120, i = 0; i < 3; i++, temp++) {
        Hu3DModelKill(temp->unk_28);
    }

    MBDBackKill();
    MBDBackClose();
    *temp_s2 = 0;
    while (1) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D450_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D580_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010D998_staff);

UnkStaff_2 *func_8010DE50_staff(s32 arg0) {
    Process *prc = omAddPrcObj(func_8010DF34_staff, 0x3F00, 0x2000, 0);
    UnkStaff_2 *data = HuMemAllocTag(sizeof(UnkStaff_2), TAG_OVERLAY);

    prc->user_data = data;
    data->unk_0A = data->unk_06 = 60;
    data->unk_0C.x = 0.0f;
    data->unk_0C.y = 500.0f;
    data->unk_0C.z = 0.0f;
    data->unk_18.x = 0.0f;
    data->unk_18.y = 0.0f;
    data->unk_18.z = 0.0f;
    data->unk_00 = arg0;
    data->unk_04 = 0;
    return data;
}

void func_8010DEDC_staff(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

void func_8010DEE4_staff(UnkStaff_2 *arg0, f32 x, f32 y, f32 z) {
    arg0->unk_0C.x = x;
    arg0->unk_0C.y = y;
    arg0->unk_0C.z = z;
}

void func_8010DEF4_staff(UnkStaff_2 *arg0, f32 x, f32 y, f32 z) {
    arg0->unk_18.x = x;
    arg0->unk_18.y = y;
    arg0->unk_18.z = z;
}

void func_8010DF04_staff(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_0A = arg1;
}

void func_8010DF0C_staff(UnkStaff_2 *arg0, s32 mask, s32 value) {
    arg0->unk_04 = value | (arg0->unk_04 & ~mask);
}

s16 func_8010DF24_staff(UnkStaff_2 *arg0) {
    return arg0->unk_04;
}

void func_8010DF2C_staff(UnkStaff_2 *arg0, s16 arg1) {
    arg0->unk_06 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010DF34_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F04C_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F3E4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F4C4_staff);

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010F9D4_staff);

void func_8010FB28_staff(void) {
    Process *prc = omAddPrcObj(func_8010FB88_staff, 0x3F00, 0x2000, 0);
    UnkStaff_5 *data = HuMemAllocTag(sizeof(UnkStaff_5), TAG_OVERLAY);

    prc->user_data = data;
    data->unk_18.x = 0.0f;
    data->unk_18.y = 100.0f;
    data->unk_18.z = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/staff/542220", func_8010FB88_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111430_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011143C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111448_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111454_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111460_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_8011146C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111478_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/542220", D_80111484_staff);
