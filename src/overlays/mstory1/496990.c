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

extern Vec D_80114BC4_mstory1[];
extern Vec D_80114BF4_mstory1[];
extern s32 D_80114BC0_mstory1;
extern const Vec D_8011550C_mstory1;
extern const Vec D_80115524_mstory1;
extern const s32 D_80115854_mstory1[];
extern Vec D_80115660_mstory1;
extern Vec D_8011566C_mstory1;
extern Vec D_80115714_mstory1;
extern Vec D_80115720_mstory1;
extern Vec D_8011572C_mstory1;
extern Vec D_80115738_mstory1;
extern Vec D_80115804_mstory1;
extern Vec D_8011581C_mstory1;
extern Vec D_80115828_mstory1;
extern Vec D_80115834_mstory1;
extern Vec D_80115840_mstory1;
extern UnkStoryObj D_80115B70_mstory1[8];
extern Vec D_80115C54_mstory1;
extern Vec D_80115C48_mstory1;
extern const Vec D_801154E8_mstory1;
extern const Vec D_801154F4_mstory1;
extern Vec D_80115C6C_mstory1;
extern Vec D_80115C84_mstory1;
extern s16 D_80115C90_mstory1;
extern s16 D_80115C92_mstory1;
extern s16 D_80115CA6_mstory1;
extern s16 D_80115CA8_mstory1;
extern Vec D_80115750_mstory1;
extern Vec D_8011575C_mstory1;
extern Vec D_80115768_mstory1;
extern Vec D_80115774_mstory1;
extern s16 D_80115CA2_mstory1;
extern Vec D_80115684_mstory1;
extern Vec D_8011569C_mstory1;
extern Vec D_801156B4_mstory1;
extern Vec D_801156C0_mstory1;
extern Vec D_801156CC_mstory1;
extern Vec D_801156D8_mstory1;
extern Vec D_801156E4_mstory1;
extern Vec D_801156F0_mstory1;
extern Vec D_801156FC_mstory1;
extern Vec D_80115708_mstory1;
extern Vec D_80115C3C_mstory1;
extern const Vec D_801154DC_mstory1;
extern s32 D_80115C9C_mstory1[3];
extern s16 D_80115C9E_mstory1;
extern Vec D_80115C60_mstory1;
extern const Vec D_80115500_mstory1;
extern Vec D_80115C78_mstory1;
extern const Vec D_80115518_mstory1;
extern const Vec D_8011578C_mstory1;
extern Vec D_801157A4_mstory1;
extern Vec D_801157B0_mstory1;
extern Vec D_801157BC_mstory1;
extern Vec D_801157E0_mstory1;
extern Vec D_801157EC_mstory1;
extern s32 D_800A178C_main[][6];
extern Vec D_80115C30_mstory1;
extern const Vec D_801154D0_mstory1;
extern const s32 D_80115530_mstory1[];
extern const s32 D_80115550_mstory1[];
extern const s32 D_80115570_mstory1[];
extern const s32 D_80115590_mstory1[];
extern s16 D_80115C94_mstory1[4];
extern const Vec D_801155B0_mstory1;
extern const Vec D_801155BC_mstory1;
extern const Vec D_801155C8_mstory1;
extern const Vec D_801155D4_mstory1;
extern const Vec D_801155E0_mstory1;
extern const Vec D_801155EC_mstory1;
extern const Vec D_801155F8_mstory1;

void func_80110804_mstory1(MstoryPath *path, f32 time, Vec *result);
void func_80105FA8_mstory1(void);
void func_80106B14_mstory1(omObjData *obj, const Vec *pos, s32 frames);
void func_80106B30_mstory1(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
s32 func_80106AFC_mstory1(s32 character);
void func_8010704C_mstory1(omObjData *obj, const Vec *pos, s32 frames);
void func_801068B0_mstory1(s16 model, s16 animSlot, s16 anim);
void func_80107220_mstory1(s16 model);
void func_80111218_mstory1(omObjData *obj);
void func_80112644_mstory1(omObjData *obj);
void func_8011369C_mstory1(omObjData *obj);
void func_80113AAC_mstory1(omObjData *obj);
void func_801069EC_mstory1(void);
void func_80106A1C_mstory1(void);
void func_80106A40_mstory1(s32 mess);
void func_801071F4_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80111634_mstory1(omObjData *obj);
void func_80114050_mstory1(omObjData *obj);
void func_8011436C_mstory1(omObjData *obj);
void func_801147D0_mstory1(s32 index, s32 seNo);
void func_801148B4_mstory1(s32 index);
void func_80106984_mstory1(void);
void func_80111220_mstory1(void);
void func_80112310_mstory1(void);
void func_8011263C_mstory1(void);
void func_80112BD8_mstory1(void);
void func_80112E14_mstory1(void);
void func_80112E1C_mstory1(omObjData *obj);
void func_80112F4C_mstory1(void);
void func_801134B4_mstory1(void);
void func_80113144_mstory1(void);
void func_80113694_mstory1(void);
void func_80113908_mstory1(void);
void func_80113D2C_mstory1(void);
void func_80113D34_mstory1(void);
void func_80113F20_mstory1(void);
void func_80114084_mstory1(void);
void func_801141B0_mstory1(void);
void func_80114364_mstory1(void);
void func_80114930_mstory1(void);
void func_8011162C_mstory1(void);
void func_80105FB8_mstory1(s32 arg0);
s32 func_80106894_mstory1(void);
void func_80112984_mstory1(omObjData *obj);
void func_80112A68_mstory1(omObjData *obj);
void func_8011314C_mstory1(omObjData *obj);
void func_80113F28_mstory1(omObjData *obj);

MstoryPath *func_80110500_mstory1(Vec *points, s32 flags) {
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

void func_80110804_mstory1(MstoryPath *path, f32 time, Vec *result) {
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

void func_801110AC_mstory1(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_801110DC_mstory1(void) {
    func_80106984_mstory1();
    D_80115C90_mstory1 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80111220_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112310_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112BD8_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112F4C_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_801134B4_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113908_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113D34_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80114084_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_801141B0_mstory1, 0x384, 0x800, 0);
    omAddPrcObj(func_80114930_mstory1, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115C90_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_80111218_mstory1(omObjData *obj) {
}

void func_80111220_mstory1(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 16, -1, NULL);
    D_80115B70_mstory1[0].obj = obj;
    D_80115B70_mstory1[0].unk_08 = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
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
    func_8000B460_main(obj, 5, D_80115530_mstory1[chr]);
    func_8000B460_main(obj, 6, D_80115550_mstory1[chr]);
    func_8000B460_main(obj, 7, D_80115570_mstory1[chr]);
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 9, D_80115590_mstory1[chr]);
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x9B));
    D_80115C94_mstory1[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80115C94_mstory1[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80115C94_mstory1[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80115C94_mstory1[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115C94_mstory1[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_80115C30_mstory1 = D_801154D0_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C30_mstory1.x, D_80115C30_mstory1.y, D_80115C30_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_80115C30_mstory1.x, -5.0f, D_80115C30_mstory1.z);
    Hu3DModelPosSet(obj->model[4], D_80115C30_mstory1.x, D_80115C30_mstory1.y, D_80115C30_mstory1.z);
    omPrcSetDestructor(0, func_8011162C_mstory1);
    D_80115B70_mstory1[0].func = func_80111218_mstory1;
    while (TRUE) {
        D_80115B70_mstory1[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8011162C_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801154D0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801154DC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801154E8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801154F4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115500_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_8011550C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115518_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115524_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115530_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115550_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115570_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115590_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801155B0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801155BC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801155C8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801155D4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801155E0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801155EC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801155F8_mstory1);

const Vec D_80115604_mstory1 = { -100.0f, 0.0f, 350.0f };
const Vec D_80115610_mstory1 = { -100.0f, 0.0f, 150.0f };
const Vec D_8011561C_mstory1 = { 0.0f, 20.0f, 0.0f };
const Vec D_80115628_mstory1 = { 0.0f, 0.0f, 0.0f };
const Vec D_80115634_mstory1 = { 0.0f, -26.565f, 0.0f };

void func_80111634_mstory1(omObjData *obj) {
    s16 model;
    HmfMotionNode *node;
    omObjData *other;
    s32 i;
    f32 scale;
    f32 time;
    s32 fx;

    HuPrcSleep(20);
    model = obj->model[1];
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801071F4_mstory1(obj, 0.0f, 110.0f, 0.0f, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    HuPrcSleep(10);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], model, "item_hook");
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    func_80107220_mstory1(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[5]].motId, 0, 10, 0);
    func_80107220_mstory1(model);
    while (!(D_80115B70_mstory1[7].unk_08 & 1)) {
        HuPrcVSleep();
    }
    func_8001C258_main(D_80115B70_mstory1[7].obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(D_80115C92_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8002FD8C_main(model, Hu3DData[model].motId, "item_hook", 27, 69);
    func_8002FD8C_main(model, Hu3DData[model].motId, "item_hook", 27, 70);
    func_8002FD8C_main(model, Hu3DData[model].motId, "item_hook", 27, 71);
    node = func_8001D33C_main(model, "item_hook");
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
    func_8002FDCC_main(model, Hu3DData[model].motId, "item_hook", 27, 71);
    func_8002FDCC_main(model, Hu3DData[model].motId, "item_hook", 27, 70);
    func_8002FDCC_main(model, Hu3DData[model].motId, "item_hook", 27, 69);
    func_80105FB8_mstory1(2);
    while (TRUE) {
        if (func_80106894_mstory1() != 0) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A33 : 0x5B25);
    func_80106A1C_mstory1();
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
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    HuAudSeqFadeOut(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_8010704C_mstory1(obj, &D_801155B0_mstory1, 10);
    HuAudSeqPlay(0x72);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115C94_mstory1[2]);
    func_80107220_mstory1(model);
    fx = CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    other = D_80115B70_mstory1[6].obj;
    func_8010704C_mstory1(other, &D_80115634_mstory1, 3);
    func_80106B14_mstory1(other, &D_80115604_mstory1, 5);
    func_8010704C_mstory1(other, &D_8011561C_mstory1, 3);
    D_80115B70_mstory1[1].func = func_80112A68_mstory1;
    HuAudFXPlay(0x219);
    HuAudFXStop(fx);
    func_8001C258_main(obj->model[4], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115C94_mstory1[3]);
    func_8010704C_mstory1(other, &D_80115628_mstory1, 3);
    func_80106B30_mstory1(other, &D_80115610_mstory1, 10, 0);
    func_80107220_mstory1(model);
    HuAudSeqPlay(0x26);
    func_8010704C_mstory1(obj, &D_801155BC_mstory1, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115C94_mstory1[0]);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(D_80115B70_mstory1[6].obj->model[1], Hu3DData[D_80115B70_mstory1[6].obj->motion[1]].motId, 0, 10, 2);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A34 : 0x5B26);
    func_80106A1C_mstory1();
    Hu3DMotionShiftSet(D_80115B70_mstory1[6].obj->model[1], Hu3DData[D_80115B70_mstory1[6].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[8]].motId, 0, 10, 0);
    func_80107220_mstory1(model);
    D_80115B70_mstory1[6].func = func_80113F28_mstory1;
    D_80115B70_mstory1[1].func = func_80112984_mstory1;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    D_80115B70_mstory1[3].func = func_8011314C_mstory1;
    func_8010704C_mstory1(obj, &D_801155C8_mstory1, 20);
    func_801147D0_mstory1(0, 31);
    func_80106B14_mstory1(obj, &D_801155E0_mstory1, 20);
    func_801148B4_mstory1(0);
    func_8010704C_mstory1(obj, &D_801155D4_mstory1, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (!(D_80115B70_mstory1[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    func_801147D0_mstory1(0, 31);
    func_80106B30_mstory1(obj, &D_801155F8_mstory1, 10, 0);
    func_801148B4_mstory1(0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (!(D_80115B70_mstory1[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801155C8_mstory1, 10);
    func_801147D0_mstory1(0, 31);
    func_80106B14_mstory1(obj, &D_801155EC_mstory1, 30);
    func_801148B4_mstory1(0);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_80115B70_mstory1[0].func = func_80111218_mstory1;
}

void func_801121E4_mstory1(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 10, 0);
    func_80107220_mstory1(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115B70_mstory1[0].func = func_80111218_mstory1;
}

void func_801122A8_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115660_mstory1, 10);
    D_80115B70_mstory1[0].func = func_80111218_mstory1;
}

void func_801122DC_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_8011566C_mstory1, 10);
    D_80115B70_mstory1[0].func = func_80111218_mstory1;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115660_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_8011566C_mstory1);

const char D_80115678_mstory1[] = "c204n_0_DEF";

void func_80112310_mstory1(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 4, 8, -1, NULL);
    D_80115B70_mstory1[1].obj = obj;
    D_80115B70_mstory1[1].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_80115C3C_mstory1 = D_801154DC_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C3C_mstory1.x, D_80115C3C_mstory1.y, D_80115C3C_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_80115C3C_mstory1.x, -5.0f, D_80115C3C_mstory1.z);
    data = DataRead(0xA007E);
    D_80115C9C_mstory1[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_80115678_mstory1);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115C9E_mstory1, 1, 0);
    Hu3DAnimBankSet(D_80115C9E_mstory1, 0);
    D_80115CA8_mstory1 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115C9E_mstory1, 0, D_80115678_mstory1);
    D_80115C9C_mstory1[0] = D_800D1714_main[D_80115C9C_mstory1[0]].animIdx;
    data = DataRead(0xA0080);
    D_80115C9C_mstory1[1] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80115C9C_mstory1[2] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_801068B0_mstory1(obj->model[1], D_80115CA8_mstory1, D_80115C9E_mstory1);
    omPrcSetDestructor(0, func_8011263C_mstory1);
    D_80115B70_mstory1[1].func = func_80111218_mstory1;
    while (TRUE) {
        D_80115B70_mstory1[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8011263C_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115684_mstory1);

const Vec D_80115690_mstory1 = { 10.0f, 378.9f, 0.0f };

void func_80112644_mstory1(omObjData *obj) {
    HuPrcSleep(40);
    HuPrcSleep(20);
    D_80115B70_mstory1[0].func = func_801121E4_mstory1;
    D_80115B70_mstory1[6].func = func_80114050_mstory1;
    func_8010704C_mstory1(obj, &D_80115690_mstory1, 30);
    func_80106B14_mstory1(obj, &D_801156F0_mstory1, 20);
    HuPrcSleep(30);
    func_8010704C_mstory1(obj, &D_801156C0_mstory1, 10);
    func_80106B14_mstory1(obj, &D_801156E4_mstory1, 15);
    D_80115B70_mstory1[0].func = func_801122A8_mstory1;
    func_8010704C_mstory1(obj, &D_8011569C_mstory1, 10);
    func_801068B0_mstory1(obj->model[1], D_80115CA8_mstory1, D_80115CA2_mstory1);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A31 : 0x5B23);
    func_80106A1C_mstory1();
    func_801068B0_mstory1(obj->model[1], D_80115CA8_mstory1, D_80115C9E_mstory1);
    func_801071F4_mstory1(D_80115B70_mstory1[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_8010704C_mstory1(D_80115B70_mstory1[6].obj, &D_801156FC_mstory1, 10);
    func_8010704C_mstory1(obj, &D_801156B4_mstory1, 20);
    Hu3DMotionShiftSet(D_80115B70_mstory1[6].obj->model[1], Hu3DData[D_80115B70_mstory1[6].obj->motion[1]].motId, 0, 10, 2);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A32 : 0x5B24);
    func_80106A1C_mstory1();
    Hu3DMotionShiftSet(D_80115B70_mstory1[6].obj->model[1], Hu3DData[D_80115B70_mstory1[6].obj->motion[0]].motId, 0, 10, 2);
    func_8010704C_mstory1(D_80115B70_mstory1[6].obj, &D_80115708_mstory1, 10);
    D_80115B70_mstory1[7].func = func_8011436C_mstory1;
    func_8010704C_mstory1(obj, &D_80115684_mstory1, 20);
    Hu3DMotionShiftSet(D_80115B70_mstory1[0].obj->model[1], Hu3DData[D_80115B70_mstory1[0].obj->motion[10]].motId, 0, 10, 2);
    while (!(D_80115B70_mstory1[7].unk_08 & 2)) {
        HuPrcVSleep();
    }
    D_80115B70_mstory1[0].func = func_80111634_mstory1;
    HuPrcSleep(40);
    func_8010704C_mstory1(obj, &D_801156D8_mstory1, 50);
    func_8010704C_mstory1(obj, &D_801156CC_mstory1, 40);
    D_80115B70_mstory1[1].func = func_80111218_mstory1;
}

void func_80112984_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_8011572C_mstory1, 20);
    func_80106B14_mstory1(obj, &D_80115714_mstory1, 20);
    func_8010704C_mstory1(obj, &D_80115738_mstory1, 10);
    while (!(D_80115B70_mstory1[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_8010704C_mstory1(obj, &D_8011572C_mstory1, 10);
    func_80106B14_mstory1(obj, &D_80115720_mstory1, 30);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_80115B70_mstory1[1].func = func_80111218_mstory1;
}

void func_80112A68_mstory1(omObjData *obj) {
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
    func_801068B0_mstory1(obj->model[1], D_80115CA8_mstory1, D_80115CA6_mstory1);
    D_80115B70_mstory1[1].func = func_80111218_mstory1;
}

void func_80112BD8_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115B70_mstory1[2].obj = obj;
    D_80115B70_mstory1[2].unk_08 = 0;
    if (func_80106AFC_mstory1(5) == 0) {
        obj->model[1] = func_8000B108_main(0x600A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
        func_8000B460_main(obj, 0, 0x60000);
        func_8000B460_main(obj, 1, 0x1D006C);
        func_8000B460_main(obj, 2, 0x1D006D);
    } else {
        obj->model[1] = func_8000B108_main(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
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
    D_80115C48_mstory1 = D_801154E8_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C48_mstory1.x, D_80115C48_mstory1.y, D_80115C48_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_80115C48_mstory1.x, -5.0f, D_80115C48_mstory1.z);
    omPrcSetDestructor(0, func_80112E14_mstory1);
    D_80115B70_mstory1[2].func = func_80112E1C_mstory1;
    while (1) {
        D_80115B70_mstory1[2].func(obj);
        HuPrcVSleep();
    }
}

void func_80112E14_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_8011569C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801156B4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801156C0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801156CC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801156D8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801156E4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801156F0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801156FC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115708_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115714_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115720_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_8011572C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115738_mstory1);

const Vec D_80115744_mstory1 = { 200.0f, 0.0f, 1200.0f };

void func_80112E1C_mstory1(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106AFC_mstory1(5) == 0) {
        CharFXPlay(0x26B, 5);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    D_80115B70_mstory1[1].func = func_80112644_mstory1;
    HuPrcSleep(70);
    if (func_80106AFC_mstory1(5) == 0) {
        CharFXPlay(0x286, 5);
    } else {
        CharFXPlay(0x286, 1);
    }
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    func_801147D0_mstory1(2, 40);
    func_80106B14_mstory1(obj, &D_80115744_mstory1, 40);
    func_801148B4_mstory1(2);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_80115B70_mstory1[2].func = func_80111218_mstory1;
}

void func_80112F4C_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115B70_mstory1[3].obj = obj;
    D_80115B70_mstory1[3].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115C54_mstory1 = D_801154F4_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C54_mstory1.x, D_80115C54_mstory1.y, D_80115C54_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_80115C54_mstory1.x, -5.0f, D_80115C54_mstory1.z);
    omPrcSetDestructor(0, func_80113144_mstory1);
    D_80115B70_mstory1[3].func = func_80111218_mstory1;
    while (1) {
        D_80115B70_mstory1[3].func(obj);
        HuPrcVSleep();
    }
}

void func_80113144_mstory1(void) {
}

void func_8011314C_mstory1(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    HuAudSeqPlay(0x21);
    HuAudFXPlay(0x29D);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A35 : 0x5B27);
    func_80106A1C_mstory1();
    D_80115B70_mstory1[3].unk_08 |= 2;
    func_80106B14_mstory1(obj, &D_80115750_mstory1, 60);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuAudFXPlay(0x29C);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A36 : 0x5B28);
    func_80106A1C_mstory1();
    func_8010704C_mstory1(obj, &D_80115768_mstory1, 20);
    D_80115B70_mstory1[3].unk_08 |= 1;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    func_80107220_mstory1(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    func_80107220_mstory1(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_80115774_mstory1, 10);
    func_8010704C_mstory1(obj, &D_80115768_mstory1, 10);
    func_8010704C_mstory1(obj, &D_80115774_mstory1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuAudFXPlay(0x29D);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(5) == 0 ? 0x5A37 : 0x5B29);
    func_80106A1C_mstory1();
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106B14_mstory1(obj, &D_8011575C_mstory1, 50);
    D_80115B70_mstory1[4].func = func_8011369C_mstory1;
    D_80115B70_mstory1[5].func = func_80113AAC_mstory1;
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80115B70_mstory1[3].func = func_80111218_mstory1;
}

void func_801134B4_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115B70_mstory1[4].obj = obj;
    D_80115B70_mstory1[4].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F1);
    func_8000B460_main(obj, 2, 0xA00F0);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115C60_mstory1 = D_80115500_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C60_mstory1.x, D_80115C60_mstory1.y, D_80115C60_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_80115C60_mstory1.x, -5.0f, D_80115C60_mstory1.z);
    omPrcSetDestructor(0, func_80113694_mstory1);
    D_80115B70_mstory1[4].func = func_80111218_mstory1;
    while (1) {
        D_80115B70_mstory1[4].func(obj);
        HuPrcVSleep();
    }
}

void func_80113694_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115750_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_8011575C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115768_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115774_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_8011578C_mstory1);

const Vec D_80115798_mstory1 = { 900.0f, 0.0f, 300.0f };

void func_8011369C_mstory1(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    while (!(D_80115B70_mstory1[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    func_80106B14_mstory1(obj, &D_8011578C_mstory1, 30);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801157BC_mstory1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801157A4_mstory1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(30);
    model = obj->model[1];
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801157B0_mstory1, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106B14_mstory1(obj, &D_80115798_mstory1, 20);
    func_80105FA8_mstory1();
    D_80115B70_mstory1[4].func = func_80111218_mstory1;
}

void func_80113908_mstory1(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115B70_mstory1[5].obj = obj;
    D_80115B70_mstory1[5].unk_08 = 0;
    src = D_80115B70_mstory1[4].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
    func_8001C5B4_main(obj->model[1], src->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115C6C_mstory1 = D_8011550C_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C6C_mstory1.x, D_80115C6C_mstory1.y, D_80115C6C_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_80115C6C_mstory1.x, -5.0f, D_80115C6C_mstory1.z);
    omPrcSetDestructor(0, func_80113D2C_mstory1);
    D_80115B70_mstory1[5].func = func_80111218_mstory1;
    while (1) {
        D_80115B70_mstory1[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801157A4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801157B0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801157BC_mstory1);

const Vec D_801157C8_mstory1 = { -100.0f, 0.0f, 300.0f };

const Vec D_801157D4_mstory1 = { 700.0f, 0.0f, 300.0f };

void func_80113AAC_mstory1(omObjData *obj) {
    omObjData *other = D_80115B70_mstory1[4].obj;
    s16 model = obj->model[1];

    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    while (!(D_80115B70_mstory1[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    func_80106B14_mstory1(obj, &D_801157C8_mstory1, 30);
    Hu3DMotionShiftSet(model, Hu3DData[other->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801157EC_mstory1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[other->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(20);
    Hu3DMotionShiftSet(model, Hu3DData[other->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801157E0_mstory1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[other->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(30);
    model = obj->model[1];
    Hu3DMotionShiftSet(model, Hu3DData[other->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_801157EC_mstory1, 10);
    Hu3DMotionShiftSet(model, Hu3DData[other->motion[1]].motId, 0, 10, 2);
    func_80106B14_mstory1(obj, &D_801157D4_mstory1, 20);
    D_80115B70_mstory1[5].func = func_80111218_mstory1;
}

void func_80113D2C_mstory1(void) {
}

void func_80113D34_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_80115B70_mstory1[6].obj = obj;
    D_80115B70_mstory1[6].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_80115C90_mstory1);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_80115C78_mstory1 = D_80115518_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C78_mstory1.x, D_80115C78_mstory1.y, D_80115C78_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_80115C78_mstory1.x, -5.0f, D_80115C78_mstory1.z);
    omPrcSetDestructor(0, func_80113F20_mstory1);
    D_80115B70_mstory1[6].func = func_80111218_mstory1;
    D_80114BC0_mstory1 = 1;
    while (1) {
        D_80115B70_mstory1[6].func(obj);
        HuPrcVSleep();
    }
}

void func_80113F20_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801157E0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_801157EC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115804_mstory1);

const Vec D_80115810_mstory1 = { 700.0f, 0.0f, 150.0f };

void func_80113F28_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115828_mstory1, 20);
    func_80106B14_mstory1(obj, &D_80115804_mstory1, 20);
    func_8010704C_mstory1(obj, &D_80115834_mstory1, 10);
    while (!(D_80115B70_mstory1[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    func_80106B30_mstory1(obj, &D_8011581C_mstory1, 10, 0);
    while (!(D_80115B70_mstory1[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_8010704C_mstory1(obj, &D_80115828_mstory1, 10);
    func_80106B14_mstory1(obj, &D_80115810_mstory1, 30);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_80115B70_mstory1[6].func = func_80111218_mstory1;
}

void func_80114050_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115840_mstory1, 20);
    D_80115B70_mstory1[6].func = func_80111218_mstory1;
}

void func_80114084_mstory1(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80114BC0_mstory1 != 0) {
        model = D_80115B70_mstory1[6].obj->model[1];
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

void func_801141B0_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_80115B70_mstory1[7].obj = obj;
    D_80115B70_mstory1[7].unk_08 = 0;
    obj->model[1] = func_8000B108_main(D_80115854_mstory1[0], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80115C84_mstory1 = D_80115524_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115C84_mstory1.x, D_80115C84_mstory1.y, D_80115C84_mstory1.z);
    D_80115C92_mstory1 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80115C92_mstory1, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_80115C92_mstory1, 60.0f);
    func_800138EC_main(D_80115C92_mstory1, 1, 0);
    func_8001C258_main(D_80115C92_mstory1, 4, 4);
    omPrcSetDestructor(0, func_80114364_mstory1);
    D_80115B70_mstory1[7].func = func_80111218_mstory1;
    while (1) {
        D_80115B70_mstory1[7].func(obj);
        HuPrcVSleep();
    }
}

void func_80114364_mstory1(void) {
}

void func_8011436C_mstory1(omObjData *obj) {
    Vec pos;
    MstoryPath *paths[2];
    omObjData *target;
    f32 rotY;
    s32 i;

    paths[0] = func_80110500_mstory1(D_80114BC4_mstory1, 0);
    paths[1] = func_80110500_mstory1(D_80114BF4_mstory1, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_80115C92_mstory1, 4, 0);
    func_800138EC_main(D_80115C92_mstory1, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        func_80110804_mstory1(paths[0], (i * 0.02f) * (i * 0.02f), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115C92_mstory1, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    target = D_80115B70_mstory1[6].obj;
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(20);
    D_80115B70_mstory1[7].unk_08 |= 2;
    HuAudFXPlay(0x218);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[0]].motId, 0, 10, 2);
    rotY = 0.0f;
    for (i = 0; i < 120; i++) {
        func_80110804_mstory1(paths[1], (i * 0.008333334f) * (i * 0.008333334f), &pos);
        rotY -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        Hu3DModelRotSet(obj->model[1], 0.0f, rotY, 0.0f);
        func_8000CFA4_main(D_80115C92_mstory1, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(D_80115C92_mstory1, 4, 4);
    HuAudFXPlay(0x21A);
    func_801110AC_mstory1(paths[0]);
    func_801110AC_mstory1(paths[1]);
    D_80115B70_mstory1[7].unk_08 = 1;
    D_80115B70_mstory1[7].func = func_80111218_mstory1;
}

void func_80114688_mstory1(omObjData *obj, omObjData *target) {
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

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_8011581C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115828_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115834_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115840_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/496990", D_80115854_mstory1);

void func_801147D0_mstory1(s32 index, s32 seNo) {
    if (D_80115B70_mstory1[index].unk_0C == 0) {
        D_80115B70_mstory1[index].unk_0C = 1;
        D_80115B70_mstory1[index].unk_10 = seNo;
        switch (index) {
            case 0:
                D_80115B70_mstory1[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                if (func_80106AFC_mstory1(5) == 0) {
                    D_80115B70_mstory1[index].unk_14 = CharFXPlay(seNo, 5);
                } else {
                    D_80115B70_mstory1[index].unk_14 = CharFXPlay(seNo, 1);
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

void func_801148B4_mstory1(s32 index) {
    if (D_80115B70_mstory1[index].unk_0C == 1) {
        D_80115B70_mstory1[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop((s16)D_80115B70_mstory1[index].unk_14);
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

void func_80114930_mstory1(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 8; i++) {
            if (D_80115B70_mstory1[i].unk_0C == 1 && Hu3DData[D_80115B70_mstory1[i].obj->model[1]].motTime == 0.0f) {
                seNo = D_80115B70_mstory1[i].unk_10;
                switch (i) {
                    case 0:
                        D_80115B70_mstory1[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                        break;
                    case 2:
                        if (func_80106AFC_mstory1(5) == 0) {
                            D_80115B70_mstory1[i].unk_14 = CharFXPlay(seNo, 5);
                        } else {
                            D_80115B70_mstory1[i].unk_14 = CharFXPlay(seNo, 1);
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
