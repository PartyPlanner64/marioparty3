#include "common.h"
#include "game/hmfmath.h"

typedef struct UnkStoryObj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} UnkStoryObj; // sizeof 0x18

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

typedef struct UnkMstory5Particle {
    /* 0x00 */ f32 time;
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec vel;
} UnkMstory5Particle; // sizeof 0x1C

extern Vec D_80114828_mstory5[];
extern Vec D_80114858_mstory5[];

extern s32 D_80114820_mstory5;
extern s32 D_80114824_mstory5;
extern const Vec D_80114D5C_mstory5;
extern Vec D_80114E00_mstory5;
extern Vec D_80114E0C_mstory5;
extern Vec D_80114E18_mstory5;
extern Vec D_80114E30_mstory5;
extern Vec D_80114EB8_mstory5;
extern Vec D_80114EC4_mstory5;
extern Vec D_80114F78_mstory5;
extern Vec D_80114F84_mstory5;
extern Vec D_80114F90_mstory5;
extern Vec D_80114F9C_mstory5;
extern Vec D_80115134_mstory5;
extern void (*const D_801148A0_mstory5[])(void);
extern UnkStoryObj D_801153A0_mstory5[8];
extern UnkStoryObj D_80115460_mstory5;
extern Vec D_8011549C_mstory5;
extern UnkMstory5Particle D_801154F8_mstory5[16];
extern const Vec D_80114D44_mstory5;
extern Vec D_801154A8_mstory5;
extern const Vec D_80114D50_mstory5;
extern Vec D_801154B4_mstory5;
extern Vec D_80115490_mstory5;
extern const Vec D_80114D38_mstory5;
extern s16 D_801154D8_mstory5;
extern s16 D_801154EE_mstory5;
extern s16 D_801154F0_mstory5;
extern s32 D_801154E4_mstory5[3];
extern s16 D_801154E6_mstory5;
extern Vec D_80115484_mstory5;
extern const Vec D_80114D2C_mstory5;
extern Vec D_801150E0_mstory5;
extern Vec D_801150EC_mstory5;
extern Vec D_801150F8_mstory5;
extern Vec D_80115110_mstory5;
extern Vec D_8011511C_mstory5;
extern Vec D_80115128_mstory5;
extern Vec D_801154CC_mstory5;
extern const Vec D_80114D74_mstory5;
extern s16 D_801154DA_mstory5;
extern const s32 D_8011514C_mstory5[];
extern Vec D_801154C0_mstory5;
extern const Vec D_80114D68_mstory5;
extern Vec D_80115038_mstory5;
extern Vec D_80115080_mstory5;
extern const Vec D_80114FC0_mstory5;
extern const Vec D_80114FD8_mstory5;
extern const Vec D_80114FE4_mstory5;
extern const Vec D_80114FF0_mstory5;
extern const Vec D_80115014_mstory5;
extern const Vec D_80115020_mstory5;
extern const Vec D_8011502C_mstory5;
extern Vec D_80115098_mstory5;
extern Vec D_801150B0_mstory5;
extern Vec D_801150BC_mstory5;
extern Vec D_80115050_mstory5;
extern Vec D_80115068_mstory5;
extern Vec D_80115074_mstory5;
extern Vec D_80114EDC_mstory5;
extern Vec D_80114EF4_mstory5;
extern Vec D_80114F0C_mstory5;
extern Vec D_80114F18_mstory5;
extern Vec D_80114F24_mstory5;
extern Vec D_80114F30_mstory5;
extern Vec D_80114F3C_mstory5;
extern Vec D_80114F48_mstory5;
extern Vec D_80114F60_mstory5;
extern Vec D_80114F6C_mstory5;
extern s16 D_801154EA_mstory5;
extern s32 D_800A178C_main[][6];
extern Vec D_80115478_mstory5;
extern const Vec D_80114D20_mstory5;
extern const s32 D_80114D80_mstory5[];
extern const s32 D_80114DA0_mstory5[];
extern const s32 D_80114DC0_mstory5[];
extern const s32 D_80114DE0_mstory5[];
extern s16 D_801154DC_mstory5[4];

void func_8010F7D4_mstory5(MstoryPath *path, f32 time, Vec *result);
void func_80106B64_mstory5(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_80107080_mstory5(omObjData *obj, const Vec *pos, s32 frames);
void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80107254_mstory5(s16 model);
void func_80110200_mstory5(omObjData *obj);
void func_80113138_mstory5(omObjData *obj);
void func_80113618_mstory5(omObjData *obj);
void func_80112994_mstory5(void);
void func_80113130_mstory5(void);
void func_80111FE0_mstory5(void);
void func_80111FE8_mstory5(omObjData *obj);
void func_80111820_mstory5(omObjData *obj);
void func_80110208_mstory5(void);
void func_801114E8_mstory5(void);
void func_80111818_mstory5(void);
void func_80111DB8_mstory5(void);
void func_8011275C_mstory5(void);
void func_80112F38_mstory5(void);
void func_80113470_mstory5(void);
void func_80110620_mstory5(omObjData *obj);
void func_80111B60_mstory5(omObjData *obj);
void func_80111C48_mstory5(omObjData *obj);
void func_8011299C_mstory5(omObjData *obj);
void func_80113B6C_mstory5(omObjData *obj);
void func_8011447C_mstory5(s32 index, s32 seNo);
void func_80114560_mstory5(s32 index);
void func_80113CF8_mstory5(omObjData *obj);
void func_80114018_mstory5(omObjData *obj);
void func_8011396C_mstory5(void);
void func_80113974_mstory5(void);
void func_80113D2C_mstory5(void);
void func_80113E58_mstory5(void);
void func_80112104_mstory5(void);
void func_801145DC_mstory5(void);
void func_80113B64_mstory5(void);
void func_80114010_mstory5(void);
void func_80110618_mstory5(void);
void func_80105FDC_mstory5(void);
void func_80105FEC_mstory5(s32 arg0);
s32 func_801068C8_mstory5(void);
void func_801068E4_mstory5(s16 model, s16 animSlot, s16 anim);
void func_801069B8_mstory5(void);
void func_80106A20_mstory5(void);
void func_80106A50_mstory5(void);
void func_80106A74_mstory5(s32 mess);
s32 func_80106B30_mstory5(s32 character);
void func_80106B48_mstory5(omObjData *obj, const Vec *pos, s32 frames);

MstoryPath *func_8010F4D0_mstory5(Vec *points, s32 flags) {
    MstoryPath *path;
    Vec *current;
    Vec *next;
    f32(*interval)[2];
    f32 totalLength;
    f32 length;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 count;
    s16 i;

    path = HuMemAllocTag(sizeof(MstoryPath), TAG_OVERLAY);
    path->flags = flags;
    path->points = points;
    current = points;
    next = current + 1;
    totalLength = 0.0f;
    for (count = 0; next->x != 9999.0f || next->y != 9999.0f || next->z != 9999.0f; count++, next++, current++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    if (flags & 1) {
        dx = points->x - current->x;
        dy = points->y - current->y;
        dz = points->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    count++;
    path->count = count;
    interval = HuMemAllocTag(count * sizeof(*interval), TAG_OVERLAY);
    path->intervals = interval;
    current = points;
    next = current + 1;
    length = 0.0f;
    for (i = 0; i < count; i++, current++, next++, interval++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        if (flags & 1) {
            if (i == count - 1) {
                dx = points->x - current->x;
                dy = points->y - current->y;
                dz = points->z - current->z;
            }
        }
        dz = HuSqrtf(dx * dx + dy * dy + dz * dz);
        (*interval)[0] = length / totalLength;
        (*interval)[1] = (length + dz) / totalLength;
        if ((*interval)[1] > 1.0f) {
            (*interval)[1] = 1.0001f;
        }
        length += dz;
    }
    return path;
}

void func_8010F7D4_mstory5(MstoryPath *path, f32 time, Vec *result) {
    f32 values[4];
    f32 times[4];
    Vec *points;
    f32(*interval)[2];
    s16 i;

    if (time >= 1.0f) {
        result->x = path->points[path->count - 1].x;
        result->y = path->points[path->count - 1].y;
        result->z = path->points[path->count - 1].z;
        return;
    }
    interval = path->intervals;
    for (i = 0; i < path->count; i++, interval++) {
        if (time <= (*interval)[0]) {
            break;
        }
    }
    i--;
    if (i < 0) {
        i = 0;
    }
    if (i >= path->count - 1) {
        i--;
    }
    interval = path->intervals;
    if (path->flags & 1) {
        times[0] = i == 0 ? -(1.0f - interval[path->count - 1][0]) : interval[i - 1][0];
        times[1] = interval[i][0];
        times[2] = i >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 1][0];
        times[3] = i + 1 >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 2][0];
        points = path->points;
        if (i == 0) {
            values[0] = points[path->count - 1].x;
        } else {
            values[0] = points[i - 1].x;
        }
        values[1] = points[i].x;
        if (i >= path->count - 1) {
            values[2] = points[0].x;
        } else {
            values[2] = points[i + 1].x;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].x;
        } else {
            values[3] = points[i + 2].x;
        }
        result->x = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[path->count - 1].y;
        } else {
            values[0] = points[i - 1].y;
        }
        values[1] = points[i].y;
        if (i >= path->count - 1) {
            values[2] = points[0].y;
        } else {
            values[2] = points[i + 1].y;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].y;
        } else {
            values[3] = points[i + 2].y;
        }
        result->y = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[path->count - 1].z;
        } else {
            values[0] = points[i - 1].z;
        }
        values[1] = points[i].z;
        if (i >= path->count - 1) {
            values[2] = points[0].z;
        } else {
            values[2] = points[i + 1].z;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].z;
        } else {
            values[3] = points[i + 2].z;
        }
        result->z = InterpolateBMLine(values, times, time);
    } else {
        if (i == 0) {
            times[0] = -1.0f;
        } else {
            times[0] = interval[i - 1][0];
        }
        times[1] = interval[i][0];
        times[2] = i >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 1][0];
        times[3] = i + 1 >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 2][0];
        points = path->points;
        if (i == 0) {
            values[0] = points[0].x;
        } else {
            values[0] = points[i - 1].x;
        }
        values[1] = points[i].x;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].x;
        } else {
            values[2] = points[i + 1].x;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].x;
        } else {
            values[3] = points[i + 2].x;
        }
        result->x = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[0].y;
        } else {
            values[0] = points[i - 1].y;
        }
        values[1] = points[i].y;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].y;
        } else {
            values[2] = points[i + 1].y;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].y;
        } else {
            values[3] = points[i + 2].y;
        }
        result->y = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[0].z;
        } else {
            values[0] = points[i - 1].z;
        }
        values[1] = points[i].z;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].z;
        } else {
            values[2] = points[i + 1].z;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].z;
        } else {
            values[3] = points[i + 2].z;
        }
        result->z = InterpolateBMLine(values, times, time);
    }
}

void func_8011007C_mstory5(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_801100AC_mstory5(void) {
    func_801069B8_mstory5();
    D_801154D8_mstory5 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80110208_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_801114E8_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80111DB8_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_8011275C_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112F38_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113470_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113974_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113D2C_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113E58_mstory5, 0x384, 0x800, 0);
    omAddPrcObj(func_80112104_mstory5, 0x384, 0x800, 0);
    omAddPrcObj(func_801145DC_mstory5, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_801154D8_mstory5, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_80110200_mstory5(omObjData *obj) {
}

void func_80110208_mstory5(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 16, -1, NULL);
    D_801153A0_mstory5[0].obj = obj;
    D_801153A0_mstory5[0].unk_08 = 0;
    D_801153A0_mstory5[0].unk_0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x9C));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x21));
    func_8000B460_main(obj, 5, D_80114D80_mstory5[chr]);
    func_8000B460_main(obj, 6, D_80114DA0_mstory5[chr]);
    func_8000B460_main(obj, 7, D_80114DC0_mstory5[chr]);
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 9, D_80114DE0_mstory5[chr]);
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x9B));
    D_801154DC_mstory5[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_801154DC_mstory5[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_801154DC_mstory5[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_801154DC_mstory5[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_801154DC_mstory5[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_80115478_mstory5 = D_80114D20_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115478_mstory5.x, D_80115478_mstory5.y, D_80115478_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115478_mstory5.x, -5.0f, D_80115478_mstory5.z);
    Hu3DModelPosSet(obj->model[4], D_80115478_mstory5.x, D_80115478_mstory5.y, D_80115478_mstory5.z);
    omPrcSetDestructor(0, func_80110618_mstory5);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[0].func(obj);
        HuPrcVSleep();
    }
}

void func_80110618_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D20_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D2C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D38_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D44_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D50_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D5C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D68_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D74_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114D80_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114DA0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114DC0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114DE0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E00_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114E30_mstory5);

const Vec D_80114E3C_mstory5 = { 230.0f, 0.0f, 480.0f };
const Vec D_80114E48_mstory5 = { 680.0f, 0.0f, 480.0f };
const Vec D_80114E54_mstory5 = { -70.0f, 0.0f, 480.0f };
const Vec D_80114E60_mstory5 = { -100.0f, 0.0f, 350.0f };
const Vec D_80114E6C_mstory5 = { -100.0f, 0.0f, 150.0f };
const Vec D_80114E78_mstory5 = { 0.0f, 20.0f, 0.0f };
const Vec D_80114E84_mstory5 = { 0.0f, 0.0f, 0.0f };
const Vec D_80114E90_mstory5 = { 0.0f, -26.565f, 0.0f };

const char D_80114E9C_mstory5[] = "item_hook";

void func_80110620_mstory5(omObjData *obj) {
    s16 model;
    HmfMotionNode *node;
    omObjData *obj6;
    s32 fx;
    s32 i;
    f32 scale;
    f32 time;

    HuPrcSleep(20);
    model = obj->model[1];
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107228_mstory5(obj, 0.0f, 110.0f, 0.0f, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    HuPrcSleep(10);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], model, D_80114E9C_mstory5);
    func_8001C258_main(obj->model[3], 4, 0);
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[5]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    while (!(D_801153A0_mstory5[7].unk_08 & 1)) {
        HuPrcVSleep();
    }
    func_8001C258_main(D_801153A0_mstory5[7].obj->model[1], 4, 4);
    func_8001C258_main(D_801154DA_mstory5, 4, 4);
    func_8002FD8C_main(model, Hu3DData[model].motId, D_80114E9C_mstory5, 0x1B, 0x45);
    func_8002FD8C_main(model, Hu3DData[model].motId, D_80114E9C_mstory5, 0x1B, 0x46);
    func_8002FD8C_main(model, Hu3DData[model].motId, D_80114E9C_mstory5, 0x1B, 0x47);
    node = func_8001D33C_main(model, D_80114E9C_mstory5);
    for (i = 0; i < 10; i++) {
        scale = sindf(i * 18.0f) * 0.8 + 1.0;
        node->baseScale.x = scale;
        node->baseScale.y = scale;
        node->baseScale.z = scale;
        node->scale.x = scale;
        node->scale.y = scale;
        node->scale.z = scale;
        HuPrcVSleep();
    }
    func_8002FDCC_main(model, Hu3DData[model].motId, D_80114E9C_mstory5, 0x1B, 0x47);
    func_8002FDCC_main(model, Hu3DData[model].motId, D_80114E9C_mstory5, 0x1B, 0x46);
    func_8002FDCC_main(model, Hu3DData[model].motId, D_80114E9C_mstory5, 0x1B, 0x45);
    func_80105FEC_mstory5(3);
    while (func_801068C8_mstory5() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A3E : 0x5B31);
    func_80106A50_mstory5();
    func_8001C5B4_main(model, obj->motion[5]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionSpeedSet(model, 2.0f);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    func_8001C5B4_main(model, obj->motion[6]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionSpeedSet(model, 1.0f);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    HuAudSeqFadeOut(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_80107080_mstory5(obj, &D_80114E00_mstory5, 10);
    HuAudSeqPlay(0x72);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_801154DC_mstory5[2]);
    func_80107254_mstory5(model);
    fx = CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    obj6 = D_801153A0_mstory5[6].obj;
    func_80107080_mstory5(obj6, &D_80114E90_mstory5, 3);
    func_80106B48_mstory5(obj6, &D_80114E60_mstory5, 5);
    func_80107080_mstory5(obj6, &D_80114E78_mstory5, 3);
    D_801153A0_mstory5[1].func = func_80111C48_mstory5;
    HuAudFXPlay(0x219);
    HuAudFXStop(fx);
    func_8001C258_main(obj->model[4], 4, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_801154DC_mstory5[3]);
    func_80107080_mstory5(obj6, &D_80114E84_mstory5, 3);
    func_80106B64_mstory5(obj6, &D_80114E6C_mstory5, 10, 0);
    func_80107254_mstory5(model);
    HuAudSeqPlay(0x26);
    func_80107080_mstory5(obj, &D_80114E0C_mstory5, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_801154DC_mstory5[0]);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(D_801153A0_mstory5[6].obj->model[1], Hu3DData[D_801153A0_mstory5[6].obj->motion[1]].motId, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A3F : 0x5B32);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(D_801153A0_mstory5[6].obj->model[1], Hu3DData[D_801153A0_mstory5[6].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[8]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    D_801153A0_mstory5[3].func = func_8011299C_mstory5;
    D_801153A0_mstory5[6].func = func_80113B6C_mstory5;
    D_801153A0_mstory5[1].func = func_80111B60_mstory5;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    func_8011447C_mstory5(0, 0x1F);
    func_80107080_mstory5(obj, &D_80114E18_mstory5, 20);
    func_80106B48_mstory5(obj, &D_80114E3C_mstory5, 20);
    func_80114560_mstory5(0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    func_8011447C_mstory5(0, 0x1F);
    func_80106B64_mstory5(obj, &D_80114E54_mstory5, 30, 0);
    func_80114560_mstory5(0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    for (i = 0; i < 2; i++) {
        Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 5, 0);
        Hu3DMotionSpeedSet(model, 5.0f);
        func_80107254_mstory5(model);
        func_8001C5B4_main(model, obj->motion[9]);
        func_8001C814_main(model, 4, 4);
        func_8001C814_main(model, 2, 0);
        Hu3DMotionSpeedSet(model, 5.0f);
        Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
        while (Hu3DData[model].motTime > 0.0f) {
            HuPrcVSleep();
        }
        func_8001C814_main(model, 4, 0);
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionSpeedSet(model, 1.0f);
    while (!(D_801153A0_mstory5[3].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &D_80114E30_mstory5, 40);
    while (!(D_801153A0_mstory5[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &D_80114E18_mstory5, 15);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    func_8011447C_mstory5(0, 0x1F);
    func_80106B48_mstory5(obj, &D_80114E48_mstory5, 30);
    func_80114560_mstory5(0);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
}

void func_801113BC_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
}

void func_80111480_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80114EB8_mstory5, 10);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
}

void func_801114B4_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80114EC4_mstory5, 10);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114EB8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114EC4_mstory5);

const char D_80114ED0_mstory5[] = "c204n_0_DEF";

void func_801114E8_mstory5(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 4, 8, -1, NULL);
    D_801153A0_mstory5[1].obj = obj;
    D_801153A0_mstory5[1].unk_08 = 0;
    D_801153A0_mstory5[1].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_80115484_mstory5 = D_80114D2C_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115484_mstory5.x, D_80115484_mstory5.y, D_80115484_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115484_mstory5.x, -5.0f, D_80115484_mstory5.z);
    data = DataRead(0xA007E);
    D_801154E4_mstory5[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_80114ED0_mstory5);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_801154E6_mstory5, 1, 0);
    Hu3DAnimBankSet(D_801154E6_mstory5, 0);
    D_801154F0_mstory5 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_801154E6_mstory5, 0, D_80114ED0_mstory5);
    D_801154E4_mstory5[0] = D_800D1714_main[D_801154E4_mstory5[0]].animIdx;
    data = DataRead(0xA0080);
    D_801154E4_mstory5[1] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_801154E4_mstory5[2] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, D_801154E6_mstory5);
    omPrcSetDestructor(0, func_80111818_mstory5);
    D_801153A0_mstory5[1].func = func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80111818_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114EDC_mstory5);

const Vec D_80114EE8_mstory5 = { 10.0f, 378.9f, 0.0f };

void func_80111820_mstory5(omObjData *obj) {
    HuPrcSleep(40);
    HuPrcSleep(20);
    D_801153A0_mstory5[0].func = func_801113BC_mstory5;
    D_801153A0_mstory5[6].func = func_80113CF8_mstory5;
    func_80107080_mstory5(obj, &D_80114EE8_mstory5, 30);
    func_80106B48_mstory5(obj, &D_80114F48_mstory5, 20);
    HuPrcSleep(30);
    func_80107080_mstory5(obj, &D_80114F18_mstory5, 10);
    func_80106B48_mstory5(obj, &D_80114F3C_mstory5, 15);
    D_801153A0_mstory5[0].func = func_80111480_mstory5;
    func_80107080_mstory5(obj, &D_80114EF4_mstory5, 10);
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, D_801154EA_mstory5);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A3C : 0x5B2F);
    func_80106A50_mstory5();
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, D_801154E6_mstory5);
    func_80107228_mstory5(D_801153A0_mstory5[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_80107080_mstory5(D_801153A0_mstory5[6].obj, &D_80114F60_mstory5, 10);
    func_80107080_mstory5(obj, &D_80114F0C_mstory5, 20);
    Hu3DMotionShiftSet(D_801153A0_mstory5[6].obj->model[1], Hu3DData[D_801153A0_mstory5[6].obj->motion[1]].motId, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A3D : 0x5B30);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(D_801153A0_mstory5[6].obj->model[1], Hu3DData[D_801153A0_mstory5[6].obj->motion[0]].motId, 0, 10, 2);
    func_80107080_mstory5(D_801153A0_mstory5[6].obj, &D_80114F6C_mstory5, 10);
    D_801153A0_mstory5[7].func = func_80114018_mstory5;
    func_80107080_mstory5(obj, &D_80114EDC_mstory5, 20);
    Hu3DMotionShiftSet(D_801153A0_mstory5[0].obj->model[1], Hu3DData[D_801153A0_mstory5[0].obj->motion[10]].motId, 0, 10, 2);
    while (!(D_801153A0_mstory5[7].unk_08 & 2)) {
        HuPrcVSleep();
    }
    D_801153A0_mstory5[0].func = func_80110620_mstory5;
    HuPrcSleep(40);
    func_80107080_mstory5(obj, &D_80114F30_mstory5, 50);
    func_80107080_mstory5(obj, &D_80114F24_mstory5, 40);
    D_801153A0_mstory5[1].func = func_80110200_mstory5;
}

void func_80111B60_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80114F9C_mstory5, 20);
    func_80106B48_mstory5(obj, &D_80114F78_mstory5, 20);
    while (!(D_801153A0_mstory5[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    func_80106B64_mstory5(obj, &D_80114F90_mstory5, 30, 0);
    while (!(D_801153A0_mstory5[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    func_80106B48_mstory5(obj, &D_80114F84_mstory5, 30);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801153A0_mstory5[1].func = func_80110200_mstory5;
}

void func_80111C48_mstory5(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec orig;
    f32 y;
    s32 i;

    orig.x = Hu3DData[model].pos.x;
    orig.y = Hu3DData[model].pos.y;
    orig.z = Hu3DData[model].pos.z;
    pos.y = Hu3DData[model].pos.y;
    for (i = 0; i < 12; i++) {
        pos.x = Hu3DData[model].pos.x;
        pos.z = Hu3DData[model].pos.z;
        y = sindf(i * 15.0f) * 80.0f;
        Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, orig.x, y + orig.y, orig.z);
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, D_801154EE_mstory5);
    D_801153A0_mstory5[1].func = func_80110200_mstory5;
}

void func_80111DB8_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[2].obj = obj;
    D_801153A0_mstory5[2].unk_08 = 0;
    D_801153A0_mstory5[2].unk_0C = 0;
    if (func_80106B30_mstory5(2) == 0) {
        obj->model[1] = func_8000B108_main(0x700A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
        func_8000B460_main(obj, 0, 0x70000);
        func_8000B460_main(obj, 1, 0x1D0050);
        func_8000B460_main(obj, 2, 0x1D0051);
    } else {
        obj->model[1] = func_8000B108_main(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
        func_8000B460_main(obj, 0, 0x30000);
        func_8000B460_main(obj, 1, 0x1D0046);
        func_8000B460_main(obj, 2, 0x1D0047);
    }
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    D_80115490_mstory5 = D_80114D38_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115490_mstory5.x, D_80115490_mstory5.y, D_80115490_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115490_mstory5.x, -5.0f, D_80115490_mstory5.z);
    omPrcSetDestructor(0, func_80111FE0_mstory5);
    D_801153A0_mstory5[2].func = func_80111FE8_mstory5;
    while (1) {
        D_801153A0_mstory5[2].func(obj);
        HuPrcVSleep();
    }
}

void func_80111FE0_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114EF4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F24_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F30_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F3C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F48_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F60_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F6C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114F9C_mstory5);

const Vec D_80114FB4_mstory5 = { 200.0f, 0.0f, 1200.0f };

void func_80111FE8_mstory5(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106B30_mstory5(2) == 0) {
        CharFXPlay(0x26B, 2);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    D_801153A0_mstory5[1].func = func_80111820_mstory5;
    HuPrcSleep(70);
    if (func_80106B30_mstory5(2) == 0) {
        CharFXPlay(0x286, 2);
    } else {
        CharFXPlay(0x286, 1);
    }
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    func_80106B48_mstory5(obj, &D_80114FB4_mstory5, 40);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801153A0_mstory5[2].func = func_80110200_mstory5;
}

void func_80112104_mstory5(void) {
    omObjData *obj;
    void *data;
    s16 first;
    s16 spr;
    s16 model;
    f32 scale;
    s32 i;

    obj = omAddObj(20, 20, 1, -1, NULL);
    D_80115460_mstory5.obj = obj;
    for (i = 0; i < 16; i++) {
        if (i == 0) {
            data = DataRead(0x1D0036);
            first = spr = Hu3DSprModelCreate(data, 0xA89, 8);
            DataClose(data);
        } else {
            spr = func_80014618_main(first, 8);
        }
        func_800147FC_main(spr, 0xF0, 0x40, 8);
        func_80014794_main(spr, 0x80);
        model = D_800CBB60_main[spr].modelId;
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(model, 0.0f, 0.0f, 0.0f);
        func_8001C2FC_main(model, 0x70000000, 0x70000000);
        func_8001C814_main(model, 2, 2);
        func_8001C258_main(model, 4, 4);
        obj->model[i + 1] = model;
        D_801154F8_mstory5[i].time = -10.0f;
        D_801154F8_mstory5[i].pos.x = 0.0f;
        D_801154F8_mstory5[i].pos.y = 0.0f;
        D_801154F8_mstory5[i].pos.z = 0.0f;
        D_801154F8_mstory5[i].vel.x = 0.0f;
        D_801154F8_mstory5[i].vel.y = 0.0f;
        D_801154F8_mstory5[i].vel.z = 0.0f;
    }
    D_80115460_mstory5.func = func_80110200_mstory5;
    while (TRUE) {
        D_80115460_mstory5.func(obj);
        for (i = 0; i < 16; i++) {
            if (D_801154F8_mstory5[i].time < 0.0f) {
                continue;
            }
            func_8001C258_main(obj->model[i + 1], 4, 0);
            scale = D_801154F8_mstory5[i].time / 40.0f * 3.0f + 1.0f;
            Hu3DModelScaleSet(obj->model[i + 1], scale, scale, scale);
            Hu3DModelPosSet(obj->model[i + 1], D_801154F8_mstory5[i].pos.x, D_801154F8_mstory5[i].pos.y, D_801154F8_mstory5[i].pos.z);
            D_801154F8_mstory5[i].pos.x += D_801154F8_mstory5[i].vel.x;
            D_801154F8_mstory5[i].pos.y += D_801154F8_mstory5[i].vel.y;
            D_801154F8_mstory5[i].pos.z += D_801154F8_mstory5[i].vel.z;
            D_801154F8_mstory5[i].time++;
            if (D_801154F8_mstory5[i].time >= 40.0f) {
                func_8001C258_main(obj->model[i + 1], 4, 4);
                D_801154F8_mstory5[i].time = -10.0f;
            }
        }
        HuPrcVSleep();
    }
}

void func_80112514_mstory5(omObjData *obj) {
    Vec pos;
    Vec rot;
    Vec ofs;
    omObjData *boat;
    s16 model;
    s32 i;

    if (D_80114820_mstory5 >= 3) {
        D_80114820_mstory5 = 0;
        boat = D_801153A0_mstory5[3].obj;
        model = boat->model[1];
        pos.x = Hu3DData[model].pos.x;
        pos.y = Hu3DData[model].pos.y;
        pos.z = Hu3DData[model].pos.z;
        rot.x = Hu3DData[model].rot.x;
        rot.y = Hu3DData[model].rot.y;
        rot.z = Hu3DData[model].rot.z;
        for (i = 0; i < 16; i++) {
            if (D_801154F8_mstory5[i].time < 0.0f) {
                ofs.x = 0.0f;
                ofs.y = 150.0f;
                ofs.z = 300.0f;
                D_801154F8_mstory5[i].pos.x = cosdf(rot.y) * ofs.x + pos.x - sindf(rot.y) * ofs.z;
                D_801154F8_mstory5[i].pos.y = pos.y + ofs.y;
                D_801154F8_mstory5[i].pos.z = sindf(rot.y) * ofs.x + pos.z + cosdf(rot.y) * ofs.z;
                D_801154F8_mstory5[i].vel.x = sindf(rot.y) * 5.0f;
                D_801154F8_mstory5[i].vel.y = cosdf(120.0f) * 5.0f;
                D_801154F8_mstory5[i].vel.z = cosdf(rot.y) * 5.0f;
                D_801154F8_mstory5[i].time = 0.0f;
                func_8001C258_main(boat->model[i + 1], 4, 0);
                break;
            }
        }
    }
    D_80114820_mstory5++;
}

void func_8011275C_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 16, 8, -1, NULL);
    D_801153A0_mstory5[3].obj = obj;
    D_801153A0_mstory5[3].unk_08 = 0;
    D_801153A0_mstory5[3].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8000B460_main(obj, 3, 0xA003A);
    func_8000B460_main(obj, 4, 0xA003B);
    func_8000B460_main(obj, 5, 0x1D0031);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_8011549C_mstory5 = D_80114D44_mstory5;
    Hu3DModelPosSet(obj->model[1], D_8011549C_mstory5.x, D_8011549C_mstory5.y, D_8011549C_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_8011549C_mstory5.x, -5.0f, D_8011549C_mstory5.z);
    omPrcSetDestructor(0, func_80112994_mstory5);
    D_801153A0_mstory5[3].func = func_80110200_mstory5;
    while (1) {
        D_801153A0_mstory5[3].func(obj);
        HuPrcVSleep();
    }
}

void func_80112994_mstory5(void) {
}

void func_8011299C_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    HuAudSeqPlay(0x21);
    HuAudFXPlay(0x29D);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A40 : 0x5B33);
    func_80106A50_mstory5();
    D_801153A0_mstory5[4].func = func_80113138_mstory5;
    D_801153A0_mstory5[5].func = func_80113618_mstory5;
    D_801153A0_mstory5[3].unk_08 |= 2;
    func_80106B48_mstory5(obj, &D_80114FC0_mstory5, 40);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuAudFXPlay(0x29C);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A41 : 0x5B34);
    func_80106A50_mstory5();
    D_801153A0_mstory5[3].unk_08 |= 8;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106B48_mstory5(D_801153A0_mstory5[1].obj, &D_8011502C_mstory5, 10);
    HuAudFXPlay(0x2A8);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A42 : 0x5B35);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[5]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801153A0_mstory5[3].unk_08 |= 0x10;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107080_mstory5(obj, &D_80114FF0_mstory5, 10);
    func_80106B64_mstory5(obj, &D_80114FD8_mstory5, 40, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801153A0_mstory5[3].unk_08 |= 1;
    func_80107080_mstory5(obj, &D_80115020_mstory5, 90);
    HuPrcSleep(60);
    func_80107080_mstory5(obj, &D_80115014_mstory5, 20);
    D_801153A0_mstory5[3].unk_08 |= 4;
    HuPrcSleep(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106B48_mstory5(obj, &D_80114FE4_mstory5, 30);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80107080_mstory5(obj, &D_80114FF0_mstory5, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    HuPrcSleep(30);
    HuAudFXPlay(0x21B);
    D_80115460_mstory5.func = func_80112514_mstory5;
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    HuPrcSleep(20);
    D_80115460_mstory5.func = func_80110200_mstory5;
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(40);
    HuAudFXPlay(0x29E);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(2) == 0 ? 0x5A44 : 0x5B37);
    func_80106A50_mstory5();
    D_801153A0_mstory5[3].unk_08 |= 0x20;
    HuPrcSleep(50);
    func_80105FDC_mstory5();
    D_801153A0_mstory5[3].func = func_80110200_mstory5;
}

void func_80112F38_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[4].obj = obj;
    D_801153A0_mstory5[4].unk_08 = 0;
    D_801153A0_mstory5[4].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F1);
    func_8000B460_main(obj, 2, 0xA00F0);
    func_8000B460_main(obj, 3, 0x1D0037);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_801154A8_mstory5 = D_80114D50_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801154A8_mstory5.x, D_801154A8_mstory5.y, D_801154A8_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_801154A8_mstory5.x, -5.0f, D_801154A8_mstory5.z);
    omPrcSetDestructor(0, func_80113130_mstory5);
    D_801153A0_mstory5[4].func = func_80110200_mstory5;
    while (1) {
        D_801153A0_mstory5[4].func(obj);
        HuPrcVSleep();
    }
}

void func_80113130_mstory5(void) {
}

void func_80113138_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80106B48_mstory5(obj, &D_80115038_mstory5, 40);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].unk_08 & 8)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &D_80115074_mstory5, 40);
    while (!(D_801153A0_mstory5[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    func_80107080_mstory5(obj, &D_80115068_mstory5, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106B48_mstory5(obj, &D_80115050_mstory5, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(40);
    func_80107080_mstory5(obj, &D_80115074_mstory5, 10);
    while (!(D_801153A0_mstory5[3].unk_08 & 4)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80107080_mstory5(obj, &D_80115068_mstory5, 30);
    while (!(D_801153A0_mstory5[3].unk_08 & 0x20)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
        func_80107254_mstory5(model);
    }
}

void func_80113470_mstory5(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[5].obj = obj;
    D_801153A0_mstory5[5].unk_08 = 0;
    D_801153A0_mstory5[5].unk_0C = 0;
    src = D_801153A0_mstory5[4].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    func_8001C5B4_main(obj->model[1], src->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_801154B4_mstory5 = D_80114D5C_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801154B4_mstory5.x, D_801154B4_mstory5.y, D_801154B4_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_801154B4_mstory5.x, -5.0f, D_801154B4_mstory5.z);
    omPrcSetDestructor(0, func_8011396C_mstory5);
    D_801153A0_mstory5[5].func = func_80110200_mstory5;
    while (1) {
        D_801153A0_mstory5[5].func(obj);
        HuPrcVSleep();
    }
}

void func_80113618_mstory5(omObjData *obj) {
    omObjData *src = D_801153A0_mstory5[4].obj;
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80106B48_mstory5(obj, &D_80115080_mstory5, 40);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].unk_08 & 8)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[3]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &D_801150BC_mstory5, 40);
    while (!(D_801153A0_mstory5[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    func_80107080_mstory5(obj, &D_801150B0_mstory5, 10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    func_80106B48_mstory5(obj, &D_80115098_mstory5, 10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(40);
    func_80107080_mstory5(obj, &D_801150BC_mstory5, 10);
    while (!(D_801153A0_mstory5[3].unk_08 & 4)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80107080_mstory5(obj, &D_801150B0_mstory5, 30);
    while (!(D_801153A0_mstory5[3].unk_08 & 0x20)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[src->motion[2]].motId, 0, 10, 0);
        func_80107254_mstory5(model);
    }
}

void func_8011396C_mstory5(void) {
}

void func_80113974_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[6].obj = obj;
    D_801153A0_mstory5[6].unk_08 = 0;
    D_801153A0_mstory5[6].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_801154C0_mstory5 = D_80114D68_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801154C0_mstory5.x, D_801154C0_mstory5.y, D_801154C0_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_801154C0_mstory5.x, -5.0f, D_801154C0_mstory5.z);
    omPrcSetDestructor(0, func_80113B64_mstory5);
    D_801153A0_mstory5[6].func = func_80110200_mstory5;
    D_80114824_mstory5 = 1;
    while (1) {
        D_801153A0_mstory5[6].func(obj);
        HuPrcVSleep();
    }
}

void func_80113B64_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114FC0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114FD8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114FE4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80114FF0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115014_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115020_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_8011502C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115038_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115050_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115068_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115074_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115080_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115098_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_801150B0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_801150BC_mstory5);

const Vec D_801150C8_mstory5 = { 250.0f, 0.0f, 150.0f };
const Vec D_801150D4_mstory5 = { 800.0f, 0.0f, 350.0f };

void func_80113B6C_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_801150F8_mstory5, 20);
    func_80106B48_mstory5(obj, &D_801150C8_mstory5, 20);
    while (!(D_801153A0_mstory5[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    func_80106B64_mstory5(obj, &D_801150E0_mstory5, 30, 0);
    while (!(D_801153A0_mstory5[3].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &D_80115128_mstory5, 40);
    while (!(D_801153A0_mstory5[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80107080_mstory5(obj, &D_801150F8_mstory5, 15);
    func_80106B64_mstory5(obj, &D_801150EC_mstory5, 5, 0);
    func_80107080_mstory5(obj, &D_80115110_mstory5, 10);
    func_80107080_mstory5(obj, &D_8011511C_mstory5, 10);
    func_80106B64_mstory5(obj, &D_801150D4_mstory5, 20, 0);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801153A0_mstory5[6].func = func_80110200_mstory5;
}

void func_80113CF8_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80115134_mstory5, 20);
    D_801153A0_mstory5[6].func = func_80110200_mstory5;
}

void func_80113D2C_mstory5(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80114824_mstory5 != 0) {
        model = D_801153A0_mstory5[6].obj->model[1];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            pos.x = Hu3DData[model].pos.x;
            pos.z = Hu3DData[model].pos.z;
            ofs = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            HuPrcVSleep();
        }
    }
}

void func_80113E58_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_801153A0_mstory5[7].obj = obj;
    D_801153A0_mstory5[7].unk_08 = 0;
    D_801153A0_mstory5[7].unk_0C = 0;
    obj->model[1] = func_8000B108_main(D_8011514C_mstory5[0], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_801154CC_mstory5 = D_80114D74_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801154CC_mstory5.x, D_801154CC_mstory5.y, D_801154CC_mstory5.z);
    D_801154DA_mstory5 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_801154DA_mstory5, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_801154DA_mstory5, 60.0f);
    func_800138EC_main(D_801154DA_mstory5, 1, 0);
    func_8001C258_main(D_801154DA_mstory5, 4, 4);
    omPrcSetDestructor(0, func_80114010_mstory5);
    D_801153A0_mstory5[7].func = func_80110200_mstory5;
    while (1) {
        D_801153A0_mstory5[7].func(obj);
        HuPrcVSleep();
    }
}

void func_80114010_mstory5(void) {
}

void func_80114018_mstory5(omObjData *obj) {
    Vec pos;
    MstoryPath *paths[2];
    omObjData *target;
    f32 rotY;
    s32 i;

    paths[0] = func_8010F4D0_mstory5(D_80114828_mstory5, 0);
    paths[1] = func_8010F4D0_mstory5(D_80114858_mstory5, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_801154DA_mstory5, 4, 0);
    func_800138EC_main(D_801154DA_mstory5, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        func_8010F7D4_mstory5(paths[0], (i * 0.02f) * (i * 0.02f), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_801154DA_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    target = D_801153A0_mstory5[6].obj;
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(20);
    D_801153A0_mstory5[7].unk_08 |= 2;
    HuAudFXPlay(0x218);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[0]].motId, 0, 10, 2);
    rotY = 0.0f;
    for (i = 0; i < 120; i++) {
        func_8010F7D4_mstory5(paths[1], (i * 0.008333334f) * (i * 0.008333334f), &pos);
        rotY -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        Hu3DModelRotSet(obj->model[1], 0.0f, rotY, 0.0f);
        func_8000CFA4_main(D_801154DA_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(D_801154DA_mstory5, 4, 4);
    HuAudFXPlay(0x21A);
    func_8011007C_mstory5(paths[0]);
    func_8011007C_mstory5(paths[1]);
    D_801153A0_mstory5[7].unk_08 = 1;
    D_801153A0_mstory5[7].func = func_80110200_mstory5;
}

void func_80114334_mstory5(omObjData *obj, omObjData *target) {
    s16 model[2];
    Vec pos[2];
    Vec rot;
    Vec diff;
    s32 i;

    model[0] = obj->model[1];
    model[1] = target->model[1];
    for (i = 0; i < 2; i++) {
        pos[i].x = Hu3DData[model[i]].pos.x;
        pos[i].y = Hu3DData[model[i]].pos.y;
        pos[i].z = Hu3DData[model[i]].pos.z;
    }
    rot.x = Hu3DData[model[0]].rot.x;
    rot.y = Hu3DData[model[0]].rot.y;
    rot.z = Hu3DData[model[0]].rot.z;
    diff.x = pos[1].x - pos[0].x;
    diff.y = pos[1].y - pos[0].y;
    diff.z = pos[1].z - pos[0].z;
    rot.y = -(atan2df(diff.z, diff.x) - 90.0f);
    Hu3DModelRotSet(model[0], rot.x, rot.y, rot.z);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_801150E0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_801150EC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_801150F8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115110_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_8011511C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115128_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_80115134_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4D8E80", D_8011514C_mstory5);

void func_8011447C_mstory5(s32 index, s32 seNo) {
    if (D_801153A0_mstory5[index].unk_0C == 0) {
        D_801153A0_mstory5[index].unk_0C = 1;
        D_801153A0_mstory5[index].unk_10 = seNo;
        switch (index) {
            case 0:
                D_801153A0_mstory5[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                if (func_80106B30_mstory5(2) == 0) {
                    D_801153A0_mstory5[index].unk_14 = CharFXPlay(seNo, 2);
                } else {
                    D_801153A0_mstory5[index].unk_14 = CharFXPlay(seNo, 1);
                }
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

void func_80114560_mstory5(s32 index) {
    if (D_801153A0_mstory5[index].unk_0C == 1) {
        D_801153A0_mstory5[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop((s16)D_801153A0_mstory5[index].unk_14);
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

void func_801145DC_mstory5(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 8; i++) {
            if (D_801153A0_mstory5[i].unk_0C == 1 && Hu3DData[D_801153A0_mstory5[i].obj->model[1]].motTime == 0.0f) {
                seNo = D_801153A0_mstory5[i].unk_10;
                switch (i) {
                    case 0:
                        D_801153A0_mstory5[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                        break;
                    case 2:
                        if (func_80106B30_mstory5(2) == 0) {
                            D_801153A0_mstory5[i].unk_14 = CharFXPlay(seNo, 2);
                        } else {
                            D_801153A0_mstory5[i].unk_14 = CharFXPlay(seNo, 1);
                        }
                        break;
                    case 1:
                    case 3:
                    case 4:
                    case 5:
                        break;
                }
            }
        }
        HuPrcVSleep();
    }
}
