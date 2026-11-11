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

typedef struct UnkMstory4Work {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec pos;
} UnkMstory4Work; // sizeof 0x10

typedef struct UnkMstory4SprGroup {
    /* 0x00 */ s16 count;
    /* 0x04 */ s16 (*pos)[2];
} UnkMstory4SprGroup; // sizeof 0x8

extern Vec D_80111AD0_mstory4;
extern Vec D_80111ADC_mstory4;

extern s32 D_80111AC4_mstory4;
extern s32 D_80111B80_mstory4;
extern s32 D_80111B84_mstory4;
extern s32 D_80111B88_mstory4;
extern s32 D_80111B8C_mstory4;
extern f32 D_80111B90_mstory4;
extern char D_80111FF8_mstory4[];
extern s16 D_80112326_mstory4;
extern s16 D_80111BA4_mstory4[][2];
extern s16 D_80111BB4_mstory4[][2];
extern s16 D_80111BC8_mstory4[][2];
extern s16 D_80111BD8_mstory4[][2];
extern s16 D_80111BE4_mstory4[][2];
extern s16 D_80111BF0_mstory4[][2];
extern const UnkMstory4SprGroup D_80112088_mstory4[6];
extern const s32 D_801120B8_mstory4[];
extern s16 D_80112378_mstory4[];
extern s16 D_801123A4_mstory4;
extern u8 D_80111BFC_mstory4[];
extern Vec D_80111F1C_mstory4;
extern void (*const D_80111C10_mstory4[])(void);
extern s32 D_800A178C_main[][6];
extern u16 D_8011234A_mstory4[2][2];
extern s16 D_80112352_mstory4;
extern const s32 D_80112008_mstory4[8];
extern const s32 D_801120D4_mstory4[8];
extern const s16 D_801120F4_mstory4[8][2];
extern const s16 D_80112114_mstory4[2];
extern s16 D_80112358_mstory4[];
extern s16 D_80112366_mstory4;
extern s16 D_80112368_mstory4[];
extern u16 D_80112376_mstory4;
extern s16 D_801123A6_mstory4[2];
extern UnkStoryObj D_801122A0_mstory4[4];
extern s16 D_80112324_mstory4;
extern s16 D_80112328_mstory4[5];
extern Vec D_80112300_mstory4;
extern Vec D_8011230C_mstory4;
extern s32 D_80112338_mstory4[4];
extern s16 D_80112348_mstory4;
extern s16 D_80112346_mstory4;
extern const char *D_80111B94_mstory4[];
extern const Vec D_80111F10_mstory4;
extern const s32 D_80111F34_mstory4[];
extern const s32 D_80111F54_mstory4[];
extern Vec D_80112318_mstory4;
extern const Vec D_80111F28_mstory4;
extern const Vec D_80111F80_mstory4;
extern u8 D_80111C04_mstory4[];

void func_80107480_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_8010E7C0_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg5);
void func_8010BAF0_mstory4(omObjData *obj);
void func_8010BF3C_mstory4(void);
void func_8010C54C_mstory4(void);
void func_8010CAE8_mstory4(void);
void func_8010BAF8_mstory4(void);
void func_8010C0BC_mstory4(void);
void func_8010C8D0_mstory4(void);
void func_8010CE90_mstory4(void);
void func_8010CD40_mstory4(void);
void func_8010D128_mstory4(void);
void func_801119C0_mstory4(void);
void func_8010D1A0_mstory4(omObjData *obj);
void func_8010E5C4_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir);
void func_8010EC38_mstory4(void);
void func_8010EDA0_mstory4(void);
void func_8010EE3C_mstory4(void);
void func_8010F0E0_mstory4(void);
void func_8010F12C_mstory4(void);
void func_8010F178_mstory4(void);
void func_8010F588_mstory4(void);
void func_8010F660_mstory4(void);
void func_8010F910_mstory4(void);
void func_8010FC98_mstory4(void);
void func_80110BB4_mstory4(omObjData *obj);
void func_80110D5C_mstory4(omObjData *obj);
s16 func_80110394_mstory4(s32 file, s32 flags);
void func_801104D4_mstory4(s16 modelId, f32 value);
void func_80110888_mstory4(s16 modelId, f32 x, f32 y, f32 z);
void func_80110528_mstory4(omObjData *obj);
s32 func_80110724_mstory4(s16 model, f32 x, f32 y, f32 z);
s16 func_801108FC_mstory4(s32 file, s32 flags);
void func_801109EC_mstory4(s16 model);
s16 func_80110B4C_mstory4(s32 dataNum, s32 attr);
void func_80110E3C_mstory4(void);
void func_80111430_mstory4(s16 model, f32 x, f32 y, f32 z, s16 count, s32 randomAxis);
void func_80111740_mstory4(s16 model);
void func_801118F8_mstory4(s32 index, s32 seNo);
void func_8011196C_mstory4(s32 index);
void func_80106000_mstory4(void);
void func_80106034_mstory4(void);
void func_801060E8_mstory4(void);
void func_80106B3C_mstory4(s16 model, s16 animSlot, s16 anim);
void func_80106C10_mstory4(void);
void func_80106C78_mstory4(void);
void func_80106CA8_mstory4(void);
void func_80106CCC_mstory4(s32 mess);
void func_80107220_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_8010724C_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3);
void func_801074AC_mstory4(s16 model);

MstoryPath *func_8010AE20_mstory4(Vec *points, s32 flags) {
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

void func_8010B124_mstory4(MstoryPath *path, f32 time, Vec *result) {
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

void func_8010B9CC_mstory4(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010B9FC_mstory4(void) {
    func_80106C10_mstory4();
    D_80112324_mstory4 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8010BAF8_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010C0BC_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010C8D0_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010CE90_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010CD40_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010D128_mstory4, 0x1002, 0x800, 0);
    omAddPrcObj(func_801119C0_mstory4, 0x1002, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80112324_mstory4, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8010BAF0_mstory4(omObjData *obj) {
}

void func_8010BAF8_mstory4(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 16, -1, NULL);
    D_801122A0_mstory4[0].obj = obj;
    D_801122A0_mstory4[0].unk_08 = 0;
    D_801122A0_mstory4[0].unk_0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80112324_mstory4);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x34));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x8F));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x32));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x36));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 7, D_80111F34_mstory4[chr]);
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x9B));
    func_8000B460_main(obj, 9, func_80017BB8_main(chr, 0x7A));
    func_8000B460_main(obj, 10, D_80111F54_mstory4[chr]);
    func_8000B460_main(obj, 11, func_80017BB8_main(chr, 2));
    func_8000B460_main(obj, 12, func_80017BB8_main(chr, 0x72));
    func_8000B460_main(obj, 13, func_80017BB8_main(chr, 0x6C));
    D_80112328_mstory4[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80112328_mstory4[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80112328_mstory4[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80112328_mstory4[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    D_80112328_mstory4[4] = func_80017AD8_main(func_80017BB8_main(chr, 0xAB));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112328_mstory4[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80112300_mstory4 = D_80111F10_mstory4;
    Hu3DModelPosSet(obj->model[1], D_80112300_mstory4.x, D_80112300_mstory4.y, D_80112300_mstory4.z);
    Hu3DModelPosSet(obj->model[2], D_80112300_mstory4.x, -5.0f, D_80112300_mstory4.z);
    omPrcSetDestructor(0, func_8010BF3C_mstory4);
    D_801122A0_mstory4[0].func = func_8010BAF0_mstory4;
    while (TRUE) {
        D_801122A0_mstory4[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8010BF3C_mstory4(void) {
}

void func_8010BF44_mstory4(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    HuPrcSleep(30);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[6]].motId, 0, 10, 2);
    func_801118F8_mstory4(0, 0x1F);
    func_8010724C_mstory4(obj, pos.x, pos.y, pos.z + 50.0f, 15, 0);
    func_8011196C_mstory4(0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801122A0_mstory4[0].func = func_8010BAF0_mstory4;
}

void func_8010C080_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 180.0f, 0.0f, 40);
    D_801122A0_mstory4[0].func = func_8010BAF0_mstory4;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F10_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F1C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F28_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F34_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F54_mstory4);

const char D_80111F74_mstory4[] = "c204n_0_DEF";

void func_8010C0BC_mstory4(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 8, 8, -1, NULL);
    D_801122A0_mstory4[1].obj = obj;
    D_801122A0_mstory4[1].unk_08 = 0;
    D_801122A0_mstory4[1].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80112324_mstory4);
    obj->model[3] = func_8000B108_main(0x1D002B, 0x2B9);
    obj->model[4] = func_8000B108_main(0x1D002C, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    obj->model[5] = func_8000B108_main(0x1D002D, 0x299);
    func_8001C258_main(obj->model[5], 4, 4);
    Hu3DModelScaleSet(obj->model[5], 2.0f, 2.0f, 2.0f);
    func_8001C814_main(obj->model[5], 2, 2);
    Hu3DMotionSpeedSet(obj->model[5], 0.5f);
    obj->model[6] = func_8000B108_main(0xA015F, 0x2A9);
    func_8001C258_main(obj->model[6], 4, 4);
    func_8001C814_main(obj->model[6], 2, 2);
    D_80111B88_mstory4 = 1;
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D0083);
    func_8000B460_main(obj, 3, 0x1D0084);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 10.0f, 330.0f, 0.0f);
    D_8011230C_mstory4 = D_80111F1C_mstory4;
    Hu3DModelPosSet(obj->model[1], D_8011230C_mstory4.x, D_8011230C_mstory4.y, D_8011230C_mstory4.z);
    Hu3DModelPosSet(obj->model[2], D_8011230C_mstory4.x, -5.0f, D_8011230C_mstory4.z);
    data = DataRead(0xA007E);
    D_80112338_mstory4[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_80111F74_mstory4);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80112338_mstory4[0], 1, 0);
    Hu3DAnimBankSet(D_80112338_mstory4[0], 0);
    D_80112348_mstory4 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80112338_mstory4[0], 0, D_80111F74_mstory4);
    D_80112338_mstory4[0] = D_800D1714_main[D_80112338_mstory4[0]].animIdx;
    data = DataRead(0xA0080);
    D_80112338_mstory4[1] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80112338_mstory4[2] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0081);
    D_80112338_mstory4[3] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106B3C_mstory4(obj->model[1], D_80112348_mstory4, D_80112338_mstory4[0]);
    omPrcSetDestructor(0, func_8010C54C_mstory4);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
    while (TRUE) {
        D_801122A0_mstory4[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C54C_mstory4(void) {
}

void func_8010C554_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 230.0f, 0.0f, 30);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_8010C590_mstory4(omObjData *obj) {
    Vec pos;
    f32 scale;
    s32 i;

    func_80107480_mstory4(obj, 0.0f, 360.0f, 0.0f, 10);
    Hu3DData[obj->model[1]].rot.y = 0.0f;
    pos.x = Hu3DData[obj->model[1]].pos.x;
    pos.y = Hu3DData[obj->model[1]].pos.y;
    pos.z = Hu3DData[obj->model[1]].pos.z;
    func_8010724C_mstory4(obj, pos.x, pos.y - 50.0f, pos.z, 20, 0);
    pos.x = Hu3DData[obj->model[1]].pos.x;
    pos.y = Hu3DData[obj->model[1]].pos.y + 80.0f;
    pos.z = Hu3DData[obj->model[1]].pos.z;
    func_8001C258_main(obj->model[5], 4, 0);
    Hu3DModelPosSet(obj->model[5], pos.x, pos.y, pos.z);
    Hu3DModelPosSet(obj->model[6], pos.x, pos.y, pos.z);
    HuAudFXPlay(0x222);
    for (i = 0; i < 10; i++) {
        Hu3DModelPosSet(obj->model[5], pos.x, pos.y, pos.z);
        Hu3DModelPosSet(obj->model[6], pos.x, pos.y, pos.z);
        scale = sindf(i * 9.0f) * 2.0f;
        Hu3DModelScaleSet(obj->model[5], scale, scale, 1.0f);
        HuPrcVSleep();
    }
    Hu3DModelScaleSet(obj->model[5], 2.0f, 2.0f, 2.0f);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_8010C7F8_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 10.0f, -30.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    HuPrcSleep(30);
    func_8010724C_mstory4(obj, D_80111F1C_mstory4.x + 300.0f, D_80111F1C_mstory4.y + 100.0f, D_80111F1C_mstory4.z, 20,
                          0);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_8010C8D0_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801122A0_mstory4[2].obj = obj;
    D_801122A0_mstory4[2].unk_08 = 0;
    D_801122A0_mstory4[2].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0129);
    func_8000B460_main(obj, 3, 0xA0127);
    func_8000B460_main(obj, 4, 0xA012D);
    obj->model[2] = Hu3DModelLink(D_80112324_mstory4);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80112318_mstory4 = D_80111F28_mstory4;
    Hu3DModelPosSet(obj->model[1], D_80112318_mstory4.x, D_80112318_mstory4.y, D_80112318_mstory4.z);
    Hu3DModelPosSet(obj->model[2], D_80112318_mstory4.x, -5.0f, D_80112318_mstory4.z);
    omPrcSetDestructor(0, func_8010CAE8_mstory4);
    D_801122A0_mstory4[2].func = func_8010BAF0_mstory4;
    D_80111B80_mstory4 = 1;
    while (1) {
        D_801122A0_mstory4[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010CAE8_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F80_mstory4);

void func_8010CAF0_mstory4(omObjData *obj) {
    s16 models[2];
    Vec pos;
    Vec ofs;
    f32 rot;
    f32 scale;
    f32 t;
    f32 s;
    f32 c;
    s32 i;

    models[0] = obj->model[1];
    models[1] = obj->model[2];
    pos.x = Hu3DData[models[0]].pos.x;
    pos.y = Hu3DData[models[0]].pos.y;
    pos.z = Hu3DData[models[0]].pos.z;
    ofs.x = 0.0f;
    ofs.y = 0.0f;
    ofs.z = 0.0f;
    rot = ofs.x;
    scale = rot;
    D_80111B84_mstory4 = 1;
    for (i = 0; i < 20; i++) {
        t = i * 4.5f;
        s = sindf(t);
        ofs.x = s * D_80111F80_mstory4.x;
        ofs.y = s * D_80111F80_mstory4.y;
        ofs.z = s * D_80111F80_mstory4.z;
        Hu3DModelPosSet(models[0], pos.x + ofs.x, pos.y + ofs.y, pos.z + ofs.z);
        Hu3DModelPosSet(models[1], pos.x + ofs.x, 0.0f, pos.z + ofs.z);
        c = cosdf(t) * 2.0f;
        Hu3DModelScaleSet(models[0], c, c, c);
        scale -= 0.2;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        Hu3DModelScaleSet(models[1], scale, scale, scale);
        rot += 0.5f;
        Hu3DModelRotSet(models[0], 0.0f, 0.0f, rot);
        HuPrcVSleep();
    }
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801122A0_mstory4[2].func = func_8010BAF0_mstory4;
}

void func_8010CD40_mstory4(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80111B80_mstory4 != 0) {
        model = D_801122A0_mstory4[2].obj->model[1];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            pos.x = Hu3DData[model].pos.x;
            pos.z = Hu3DData[model].pos.z;
            ofs = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            if (D_80111B84_mstory4 == 1) {
                break;
            }
            HuPrcVSleep();
        }
        while (TRUE) {
            HuPrcVSleep();
        }
    }
}

void func_8010CE90_mstory4(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80111B88_mstory4 != 0) {
        model = D_801122A0_mstory4[1].obj->model[6];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            if (D_80111B8C_mstory4 == 0) {
                pos.x = Hu3DData[model].pos.x;
                pos.z = Hu3DData[model].pos.z;
                ofs = sindf(angle) * 40.0f;
                angle += 2.0f;
                angle = (angle >= 360.0f) ? angle - 360.0f : angle;
                Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            } else {
                pos.y = Hu3DData[model].pos.y;
                angle = 0.0f;
            }
            HuPrcVSleep();
        }
    }
}

void func_8010CFE0_mstory4(omObjData *obj, omObjData *target) {
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

void func_8010D128_mstory4(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_801122A0_mstory4[3].obj = obj;
    D_801122A0_mstory4[3].unk_08 = 0;
    D_801122A0_mstory4[3].unk_0C = 0;
    D_801122A0_mstory4[3].func = func_8010D1A0_mstory4;

    for (;;) {
        D_801122A0_mstory4[3].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111F98_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111FA8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111FB8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111FC8_mstory4);

// Code matches instruction-for-instruction, but the target's stack frame is
// 0x40 bytes larger (0xD0 vs 0x90). The extra space is unreferenced and lies
// after the `model` spill slot, so it comes from additional reload stack slots
// (e.g. constant locals folded away by combine), not from a local array.
#ifdef NON_MATCHING
void func_8010D1A0_mstory4(omObjData *obj) {
    omObjData *obj0;
    omObjData *obj1;
    omObjData *obj2;
    Vec pos;
    HmfMotionNode *nodes[4];
    s16 model;
    s32 i;
    f32 ofs;
    f32 time;
    f32 dist;
    f32 scale;

    HuPrcVSleep();
    obj0 = D_801122A0_mstory4[0].obj;
    obj1 = D_801122A0_mstory4[1].obj;
    obj2 = D_801122A0_mstory4[2].obj;
    model = obj0->model[1];
    HuPrcSleep(10);
    CharFXPlay(0x262, GwStory.unk1);
    func_80017954_main(obj0->model[1], 2, GwStory.unk1, D_80112328_mstory4[2]);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[1]].motId, 0, 20, 0);
    func_801074AC_mstory4(model);
    HuPrcSleep(30);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(20);
    func_80017954_main(obj0->model[1], 2, GwStory.unk1, D_80112328_mstory4[0]);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[10]].motId, 0, 10, 2);
    func_80107480_mstory4(obj0, 0.0f, 180.0f, 0.0f, 20);
    HuPrcSleep(30);
    func_80107480_mstory4(obj1, 0.0f, 210.0f, 0.0f, 10);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A79);
    func_80106CA8_mstory4();
    HuPrcSleep(40);
    func_8010724C_mstory4(obj2, 0.0f, 200.0f, -150.0f, 40, 0);
    HuPrcSleep(50);
    HuAudFXPlay(0x15C);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(D_801122A0_mstory4[2].obj->model[1], Hu3DData[D_801122A0_mstory4[2].obj->motion[2]].motId, 0, 10, 2);
    D_801122A0_mstory4[0].func = func_8010BF44_mstory4;
    func_80107480_mstory4(obj2, 0.0f, -10.0f, 0.0f, 10);
    func_8010724C_mstory4(obj2, -120.0f, 200.0f, 400.0f, 20, 0);
    func_80107480_mstory4(obj2, 0.0f, 0.0f, 0.0f, 10);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7A);
    func_80106CA8_mstory4();
    Hu3DMotionShiftSet(D_801122A0_mstory4[2].obj->model[1], Hu3DData[D_801122A0_mstory4[2].obj->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(30);
    func_8010724C_mstory4(obj2, 0.0f, 200.0f, -150.0f, 5, 0);
    func_80107480_mstory4(obj2, 0.0f, 0.0f, 0.0f, 5);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(D_801122A0_mstory4[2].obj->model[1], Hu3DData[D_801122A0_mstory4[2].obj->motion[4]].motId, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7B);
    func_80106CA8_mstory4();
    D_801122A0_mstory4[2].func = func_8010CAF0_mstory4;
    HuAudFXPlay(0x224);
    HuAudSeqFadeOut(120);
    HuPrcSleep(10);
    D_801122A0_mstory4[1].func = func_80110BB4_mstory4;
    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[6]].motId, 0, 10, 2);
    func_801118F8_mstory4(0, 0x1F);
    func_80107220_mstory4(obj0, pos.x - 80.0f, pos.y, pos.z - 200.0f, 20);
    func_8011196C_mstory4(0);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(50);
    func_80107480_mstory4(obj0, 0.0f, 0.0f, 0.0f, 10);
    CharFXPlay(0x286, GwStory.unk1);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[5]].motId, 0, 10, 0);
    func_801074AC_mstory4(model);
    HuPrcSleep(40);
    D_801122A0_mstory4[1].func = func_8010C590_mstory4;
    HuPrcSleep(40);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[0]].motId, 0, 30, 0);
    HuPrcSleep(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[9]].motId, 0, 10, 0);
    func_80107480_mstory4(obj0, 0.0f, 110.0f, 0.0f, 20);
    func_801074AC_mstory4(model);
    HuPrcSleep(25);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[6]].motId, 0, 10, 2);
    Hu3DMotionSpeedSet(model, 1.0f);
    func_801118F8_mstory4(0, 0x1F);
    func_80107220_mstory4(obj0, -100.0f, 0.0f, 300.0f, 35);
    func_8011196C_mstory4(0);
    Hu3DMotionSpeedSet(model, 1.0f);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(20);
    func_80106000_mstory4();
    func_8010EC38_mstory4();
    D_80111ADC_mstory4.x = Hu3DData[obj1->model[1]].pos.x;
    D_80111ADC_mstory4.y = Hu3DData[obj1->model[1]].pos.y + 90.0f;
    D_80111ADC_mstory4.z = Hu3DData[obj1->model[1]].pos.z;
    D_80111AD0_mstory4.x = Hu3DData[obj1->model[1]].pos.x;
    D_80111AD0_mstory4.y = Hu3DData[obj1->model[1]].pos.y + 90.0f;
    D_80111AD0_mstory4.z = Hu3DData[obj1->model[1]].pos.z + 400.0f;
    func_8010F0E0_mstory4();
    pos.x = Hu3DData[obj1->model[1]].pos.x;
    pos.y = Hu3DData[obj1->model[1]].pos.y + 90.0f;
    pos.z = Hu3DData[obj1->model[1]].pos.z - 5.0f;
    Hu3DModelPosSet(obj1->model[6], pos.x, pos.y, pos.z);
    Hu3DModelPosSet(obj1->model[5], pos.x, pos.y, pos.z - 80.0f);
    func_8001C5B4_main(obj1->model[1], obj1->motion[2]);
    func_8001C814_main(obj1->model[1], 2, 0);
    func_8001C814_main(obj1->model[1], 1, 1);
    func_80017358_main(obj1->model[3], "saikoro", obj1->model[1], "saikoro");
    func_80017358_main(obj1->model[4], "c204nj1-futa", obj1->model[1], "futa");
    ofs = 0.0f;
    scale = 0.0f;
    for (i = 0; i < 4; i++) {
        func_8002FD8C_main(obj1->model[6], Hu3DData[obj1->model[6]].motId, D_80111B94_mstory4[i], 27, 69);
        func_8002FD8C_main(obj1->model[6], Hu3DData[obj1->model[6]].motId, D_80111B94_mstory4[i], 27, 70);
        func_8002FD8C_main(obj1->model[6], Hu3DData[obj1->model[6]].motId, D_80111B94_mstory4[i], 27, 71);
        nodes[i] = func_8001D33C_main(obj1->model[6], D_80111B94_mstory4[i]);
        nodes[i]->baseScale.z = nodes[i]->baseScale.y = nodes[i]->baseScale.x = scale;
        nodes[i]->scale.z = nodes[i]->scale.y = nodes[i]->scale.x = scale;
    }
    HuPrcVSleep();
    HuPrcSleep(10);
    func_8001C814_main(obj1->model[1], 1, 0);
    HuPrcSleep(30);
    func_8001C258_main(obj1->model[6], 4, 0);
    HuAudFXPlay(0x223);
    HuPrcSleep(60);
    time = 60.0f;
    dist = 250.0f;
    ofs = 0.0f;
    for (i = 0; i <= time; i++) {
        D_80111ADC_mstory4.y += dist / time;
        D_80111AD0_mstory4.y += dist / time;
        ofs += dist / time;
        HuPrcVSleep();
        Hu3DModelPosSet(obj1->model[6], pos.x, ofs + pos.y, pos.z);
        Hu3DModelPosSet(obj1->model[5], pos.x, ofs + pos.y, pos.z - 80.0f);
    }
    HuPrcSleep(50);
    D_80111ADC_mstory4.x = -25.0f;
    D_80111ADC_mstory4.y = 0.0f;
    D_80111ADC_mstory4.z = -650.0f;
    D_80111AD0_mstory4.x = 14.0f;
    D_80111AD0_mstory4.y = 193.0f;
    D_80111AD0_mstory4.z = 1400.0f;
    HuPrcVSleep();
    Hu3DModelPosSet(obj1->model[6], D_80111F1C_mstory4.x, D_80111F1C_mstory4.y + 150.0f, D_80111F1C_mstory4.z);
    func_8001C258_main(obj1->model[5], 4, 4);
    for (i = 0; i < 4; i++) {
        func_8002FDCC_main(obj1->model[6], Hu3DData[obj1->model[6]].motId, D_80111B94_mstory4[i], 27, 69);
        func_8002FDCC_main(obj1->model[6], Hu3DData[obj1->model[6]].motId, D_80111B94_mstory4[i], 27, 70);
        func_8002FDCC_main(obj1->model[6], Hu3DData[obj1->model[6]].motId, D_80111B94_mstory4[i], 27, 71);
    }
    func_8010EDA0_mstory4();
    func_80106034_mstory4();
    func_8010F12C_mstory4();
    Hu3DModelPosSet(obj0->model[1], 0.0f, 0.0f, 300.0f);
    Hu3DModelPosSet(obj0->model[2], 0.0f, 0.0f, 300.0f);
    HuPrcVSleep();
    D_80111B8C_mstory4 = 0;
    func_8001C5B4_main(obj1->model[1], obj1->motion[2]);
    func_8001C814_main(obj1->model[1], 2, 0);
    func_8001C814_main(obj1->model[1], 4, 4);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[9]].motId, 0, 10, 0);
    Hu3DMotionTimeSet(obj1->model[1], D_800CCF58_main[Hu3DData[obj1->model[1]].motId].unk02);
    do {
        time = Hu3DData[obj1->model[1]].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    func_8001C814_main(obj1->model[1], 4, 0);
    func_8001C5B4_main(obj1->model[1], obj1->motion[0]);
    func_8001C814_main(obj1->model[1], 2, 2);
    Hu3DMotionShiftSet(model, Hu3DData[obj0->motion[8]].motId, 0, 30, 2);
    D_80111B8C_mstory4 = 1;
    D_801122A0_mstory4[0].func = func_8010C080_mstory4;
    func_8010E5C4_mstory4(obj1, 0.0f, 300.0f, 300.0f, 40, 0);
    D_80111B8C_mstory4 = 0;
    pos.x = Hu3DData[obj1->model[1]].pos.x;
    pos.y = Hu3DData[obj1->model[1]].pos.y + 100.0f;
    pos.z = Hu3DData[obj1->model[1]].pos.z;
    func_8010724C_mstory4(obj1, pos.x, pos.y, pos.z, 15, 0);
    HuPrcSleep(20);
    HuAudSeqPlay(0x2A);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7C);
    func_80106CA8_mstory4();
    func_8002FD8C_main(obj1->model[6], Hu3DData[obj1->model[6]].motId, D_80111FF8_mstory4, 76, 69);
    func_8002FD8C_main(obj1->model[6], Hu3DData[obj1->model[6]].motId, D_80111FF8_mstory4, 76, 70);
    nodes[0] = func_8001D33C_main(obj1->model[6], D_80111FF8_mstory4);
    nodes[0]->baseRot.y = 0.0f;
    nodes[0]->rot.z = 0.0f;
    for (i = 0; i < 10; i++) {
        nodes[0]->baseRot.y += 4.5f;
        nodes[0]->rot.z += 4.5f;
        nodes[0]->baseRot.x += 0.5f;
        nodes[0]->rot.x += 0.5f;
        HuPrcVSleep();
    }
    func_80107480_mstory4(obj1, 0.0f, -45.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj1->model[1], Hu3DData[obj1->motion[3]].motId, 0, 10, 2);
    func_80106B3C_mstory4(obj1->model[1], D_80112348_mstory4, D_80112346_mstory4);
    HuPrcSleep(40);
    Hu3DMotionShiftSet(obj1->model[1], Hu3DData[obj1->motion[0]].motId, 0, 10, 2);
    func_80107480_mstory4(obj1, 10.0f, -20.0f, 0.0f, 10);
    for (i = 0; i < 10; i++) {
        nodes[0]->baseRot.y -= 4.5f;
        nodes[0]->rot.z -= 4.5f;
        nodes[0]->baseRot.x -= 0.5f;
        nodes[0]->rot.x -= 0.5f;
        HuPrcVSleep();
    }
    func_8002FDCC_main(obj1->model[6], Hu3DData[obj1->model[6]].motId, D_80111FF8_mstory4, 76, 69);
    func_8002FDCC_main(obj1->model[6], Hu3DData[obj1->model[6]].motId, D_80111FF8_mstory4, 76, 70);
    HuPrcSleep(40);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7D);
    func_80106CA8_mstory4();
    HuPrcSleep(30);
    D_80111B8C_mstory4 = 1;
    D_801122A0_mstory4[1].func = func_80110D5C_mstory4;
    func_8010E5C4_mstory4(obj1, 0.0f, 230.0f, 300.0f, 30, 0);
    HuAudFXPlay(0x225);
    func_8010E5C4_mstory4(obj1, 0.0f, 700.0f, 300.0f, 30, 0);
    HuPrcSleep(30);
    func_8010F0E0_mstory4();
    func_8010F178_mstory4();
    func_80046558_main(D_801122A0_mstory4[2].obj->model[1]);
    Hu3DModelKill(D_801122A0_mstory4[2].obj->model[1]);
    func_80106000_mstory4();
    func_8010EE3C_mstory4();
    D_80111B8C_mstory4 = 1;
    func_8010F588_mstory4();
    func_8010F660_mstory4();
    func_8010F910_mstory4();
    func_8010FC98_mstory4();
    HuPrcSleep(150);
    while (D_800D5558_main[0] == 0) {
        HuPrcVSleep();
    }
    func_801060E8_mstory4();
    D_801122A0_mstory4[3].func = func_8010BAF0_mstory4;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C8050", func_8010D1A0_mstory4);
#endif

void func_8010E5C4_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[6];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = x - start.x;
    diff.y = y - start.y;
    diff.z = z - start.z;
    if (faceDir != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = frames;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    for (i = 0.0f; i < (f32)frames; i += 1.0f) {
        cur.x = i * step.x + start.x;
        cur.y = i * step.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, x, y, z);
    HuPrcVSleep();
}

void func_8010E7C0_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg5) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[6];
    f32 i;
    f32 angle;
    f32 scale;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = x - start.x;
    diff.y = y - start.y;
    diff.z = z - start.z;
    if (arg5 != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = frames;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    scale = 1.0f;
    for (i = 0.0f; i < (f32)frames; i += 1.0f) {
        cur.x = i * step.x + start.x;
        angle = i / frames * 90.0f;
        cur.y = sindf(angle) * diff.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        Hu3DModelScaleSet(model, scale, scale, scale);
        scale = sindf(angle) * 5.0f;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, x, y, z);
    HuPrcVSleep();
}

f32 func_8010EA34_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[6];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = x - start.x;
    diff.y = y - start.y;
    diff.z = z - start.z;
    if (faceDir != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = frames;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    D_80111B90_mstory4 = 0.0f;
    for (i = 0.0f; i < (f32)frames; i += 1.0f) {
        cur.x = i * step.x + start.x;
        cur.y = i * step.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, x, y, z);
    return 20.0f;
}

void func_8010EC38_mstory4(void) {
    s32 i;
    s32 j;

    D_80112352_mstory4 = func_8000B838_main(0x1D0028);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            D_8011234A_mstory4[i][j] = espEntry(D_80112352_mstory4, 0, 0);
            espPosSet(D_8011234A_mstory4[i][j], j * 160 + 80, i * 120 + 60);
            espAttrSet(D_8011234A_mstory4[i][j], 0x4000);
        }
    }
    espAttrSet(D_8011234A_mstory4[0][1], 1);
    espAttrSet(D_8011234A_mstory4[1][0], 2);
    espAttrSet(D_8011234A_mstory4[1][1], 3);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            espDispOn(D_8011234A_mstory4[i][j]);
        }
    }
}

void func_8010EDA0_mstory4(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            espDispOff(D_8011234A_mstory4[i][j]);
            espKill(D_8011234A_mstory4[i][j]);
        }
    }
    HuSprAnimKill(D_80112352_mstory4);
}

void func_8010EE3C_mstory4(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_80112358_mstory4[i] = func_8000B838_main(D_80112008_mstory4[i]);
        D_80112368_mstory4[i] = espEntry(D_80112358_mstory4[i], 0, 0);
        espPosSet(D_80112368_mstory4[i], 160, 120);
        espAttrSet(D_80112368_mstory4[i], 0x4000);
        espDispOff(D_80112368_mstory4[i]);
    }
}

void func_8010EF00_mstory4(s32 index) {
    espDispOn(D_80112368_mstory4[index]);
}

void func_8010EF28_mstory4(s32 index) {
    espDispOff(D_80112368_mstory4[index]);
}

void func_8010EF50_mstory4(s32 index, s16 level) {
    espTPLvlSet(D_80112368_mstory4[index], level);
}

void func_8010EF80_mstory4(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        espDispOff(D_80112368_mstory4[i]);
        espKill(D_80112368_mstory4[i]);
        HuSprAnimKill(D_80112358_mstory4[i]);
    }
    HuPrcSleep(3);
}

void func_8010F010_mstory4(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        espDispOff(D_80112368_mstory4[i]);
        espKill(D_80112368_mstory4[i]);
        HuSprAnimKill(D_80112358_mstory4[i]);
        HuPrcSleep(3);
    }
}

void func_8010F0A0_mstory4(void) {
    u16 *espriteSlot = &D_80112376_mstory4;
    s16 *sprite = &D_80112366_mstory4;

    espDispOff(*espriteSlot);
    espKill(*espriteSlot);
    HuSprAnimKill(*sprite);
}

void func_8010F0E0_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[0].obj;

    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8010F12C_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[0].obj;

    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void func_8010F178_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[1].obj;

    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelKill(obj->model[1]);
    Hu3DModelKill(obj->model[3]);
    Hu3DModelKill(obj->model[4]);
    Hu3DModelKill(obj->model[5]);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80111FF8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80112008_mstory4);

void func_8010F1F4_mstory4(void) {
    while (TRUE) {
        if (D_800CDA7C_main[0] & 0x2000) {
            if (D_800CDA7C_main[0] & 0x100) {
                D_80111AD0_mstory4.x -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 0x200) {
                D_80111AD0_mstory4.x += 10.0f;
            }
        } else {
            if (D_800CDA7C_main[0] & 0x800) {
                D_80111AD0_mstory4.z -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 0x400) {
                D_80111AD0_mstory4.z += 10.0f;
            }
            if (D_800CDA7C_main[0] & 0x100) {
                D_80111AD0_mstory4.y -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 0x200) {
                D_80111AD0_mstory4.y += 10.0f;
            }
        }
        if (D_800CDA7C_main[0] & 0x2000) {
            if (D_800CDA7C_main[0] & 1) {
                D_80111ADC_mstory4.x -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 2) {
                D_80111ADC_mstory4.x += 10.0f;
            }
        } else {
            if (D_800CDA7C_main[0] & 8) {
                D_80111ADC_mstory4.z -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 4) {
                D_80111ADC_mstory4.z += 10.0f;
            }
            if (D_800CDA7C_main[0] & 1) {
                D_80111ADC_mstory4.y -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 2) {
                D_80111ADC_mstory4.y += 10.0f;
            }
        }
        sprintf(D_800D5218_main, "POSX   :[%f]", D_80111AD0_mstory4.x);
        print8(24, 128, D_800D5218_main);
        sprintf(D_800D5218_main, "POSY   :[%f]", D_80111AD0_mstory4.y);
        print8(24, 136, D_800D5218_main);
        sprintf(D_800D5218_main, "POSZ   :[%f]", D_80111AD0_mstory4.z);
        print8(24, 144, D_800D5218_main);
        sprintf(D_800D5218_main, "INTERX :[%f]", D_80111ADC_mstory4.x);
        print8(24, 160, D_800D5218_main);
        sprintf(D_800D5218_main, "INTERY :[%f]", D_80111ADC_mstory4.y);
        print8(24, 168, D_800D5218_main);
        sprintf(D_800D5218_main, "INTERZ :[%f]", D_80111ADC_mstory4.z);
        print8(24, 176, D_800D5218_main);
        HuPrcVSleep();
    }
}

void func_8010F588_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[1].obj;

    func_8010EF00_mstory4(1);
    D_80111AD0_mstory4.x = 1720.0f;
    D_80111AD0_mstory4.y = 4000.0f;
    D_80111AD0_mstory4.z = 4000.0f;
    D_80111ADC_mstory4.x = 140.0f;
    D_80111ADC_mstory4.y = 1000.0f;
    D_80111ADC_mstory4.z = 500.0f;
    HuPrcVSleep();
    Hu3DModelPosSet(obj->model[6], 0.0f, 0.0f, 0.0f);
    HuAudFXPlay(0x225);
    func_8010E7C0_mstory4(obj, 0.0f, 3000.0f, 0.0f, 100, 0);
}

void func_8010F660_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[1].obj;
    HmfMotionNode *node;
    f32 speed;
    s32 i;

    D_80112326_mstory4 = func_80110394_mstory4(0xB0004, 0x689);
    func_80110888_mstory4(D_80112326_mstory4, 7.0f, 50.0f, 12.0f);
    func_801104D4_mstory4(D_80112326_mstory4, 120.0f);
    func_800138EC_main(D_80112326_mstory4, 1, 0);
    func_8001C258_main(D_80112326_mstory4, 4, 4);
    func_8010EF28_mstory4(1);
    func_8010EF00_mstory4(0);
    D_80111AD0_mstory4.x = 0.0f;
    D_80111AD0_mstory4.y = 0.0f;
    D_80111AD0_mstory4.z = 500.0f;
    D_80111ADC_mstory4.x = 0.0f;
    D_80111ADC_mstory4.y = 0.0f;
    D_80111ADC_mstory4.z = 0.0f;
    HuPrcVSleep();
    Hu3DModelPosSet(obj->model[6], 0.0f, -100.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[6], 1.0f, 1.0f, 1.0f);
    func_8002FD8C_main(obj->model[6], Hu3DData[obj->model[6]].motId, D_80111FF8_mstory4, 76, 70);
    func_8010EA34_mstory4(obj, 0.0f, 50.0f, 0.0f, 40, 0);
    speed = 0.0f;
    HuPrcSleep(20);
    node = func_8001D33C_main(obj->model[6], D_80111FF8_mstory4);
    node->rot.z = node->baseRot.y = D_80111B90_mstory4;
    HuAudFXPlay(0x226);
    for (i = 0; i < 80; i++) {
        if (i == 30) {
            func_800138EC_main(D_80112326_mstory4, 1, 1);
            func_8001C258_main(D_80112326_mstory4, 4, 0);
        }
        D_80111B90_mstory4 += speed;
        speed += 1.0f;
        if (speed > 30.0f) {
            speed = 40.0f;
        }
        node->rot.z = node->baseRot.y = D_80111B90_mstory4;
        HuPrcVSleep();
    }
    func_8002FDCC_main(obj->model[6], Hu3DData[obj->model[6]].motId, D_80111FF8_mstory4, 76, 70);
    D_80111B90_mstory4 = 0.0f;
}

void func_8010F910_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[1].obj;
    void *data;
    s32 n;
    s32 i;
    s32 j;

    data = DataRead(0x1D001D);
    n = 0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < D_80112088_mstory4[i].count; j++) {
            D_801123A4_mstory4 = HuSprAnimRead(data);
            D_80112378_mstory4[n] = espEntry(D_801123A4_mstory4, 0, 1);
            espPosSet(D_80112378_mstory4[n], D_80112088_mstory4[i].pos[j][0], D_80112088_mstory4[i].pos[j][1]);
            espAttrSet(D_80112378_mstory4[n], 0x1000);
            espColorSet(D_80112378_mstory4[n], 0xFF, 0xFF, 0xDC);
            espAttrSet(D_80112378_mstory4[n], 8);
            espTPLvlSet(D_80112378_mstory4[n], 0xFF);
            espDispOff(D_80112378_mstory4[n]);
            n++;
        }
    }
    HuMemMemoryFreePerm(data);
    func_8001C258_main(obj->model[6], 4, 4);
    func_8010EF28_mstory4(0);
    func_8010EF00_mstory4(1);
    D_80111AD0_mstory4.x = 0.0f;
    D_80111AD0_mstory4.y = 40.0f;
    D_80111AD0_mstory4.z = 310.0f;
    D_80111ADC_mstory4.x = 0.0f;
    D_80111ADC_mstory4.y = -270.0f;
    D_80111ADC_mstory4.z = -180.0f;
    HuPrcVSleep();
    HuPrcSleep(90);
    func_800138EC_main(D_80112326_mstory4, 1, 0);
    HuPrcSleep(10);
    HuAudFXPlay(0x24E);
    for (j = 1; j < 7; j++) {
        func_8010EF00_mstory4(j + 1);
        func_8010EF50_mstory4(j + 1, 0);
        for (i = 0; i < D_801120B8_mstory4[j]; i++) {
            func_8010EF50_mstory4(j + 1, 256.0f / D_801120B8_mstory4[j] * i);
            HuPrcVSleep();
        }
        func_8010EF28_mstory4(j);
        func_8010EF50_mstory4(j + 1, 0x100);
    }
    HuAudFXPlay(0x227);
    n = 0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < D_80112088_mstory4[i].count; j++) {
            espBankSet(D_80112378_mstory4[n], 0, 0);
            func_8000BDDC_main(D_80112378_mstory4[n], 1);
            espDispOn(D_80112378_mstory4[n]);
            n++;
            HuPrcSleep(1);
        }
    }
    func_8010F010_mstory4();
    HuPrcSleep(129);
}

void func_800E4F50_name_81(u8 *);
void MBDBackCreate(s32, s32);                   /* extern */
void func_8010EF28_mstory4(s32);                /* extern */
void func_8010F0A0_mstory4(void);               /* extern */
void func_8010F12C_mstory4(void);               /* extern */
void func_80110270_mstory4(void);               /* extern */
void func_80110DB0_mstory4(f32, f32, f32, s16); /* extern */

extern s16 D_80112330_mstory4;
extern s16 D_80111C00_mstory4;

void func_8010FC98_mstory4(void) {
    omObjData *temp_s5;
    omObjData *temp_s7;
    s32 var_s3;
    u16 temp_fp;
    s32 i, j;

    temp_s5 = D_801122A0_mstory4[0].obj;
    temp_s7 = D_801122A0_mstory4[1].obj;
    temp_fp = temp_s5->model[1];
    Hu3DCameraPerspectiveSet(0, 40.0f, 80.0f, 8000.0f);

    D_80111AD0_mstory4.x = 0.0f;
    D_80111AD0_mstory4.y = 190.0f;
    D_80111AD0_mstory4.z = 3770.0f;

    D_80111ADC_mstory4.x = 0.0f;
    D_80111ADC_mstory4.y = 130.0f;
    D_80111ADC_mstory4.z = 450.0f;

    D_80111AC4_mstory4 = 1;
    var_s3 = 0;
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackCreate(0x20, 0);
    func_8010EF28_mstory4(7);
    for (i = 0; i < 6; i++) {
        for (j = 0; j < D_80112088_mstory4[i].count; var_s3++, j++) {
            espBankSet(D_80112378_mstory4[var_s3], 0, 0);
            func_8000BDDC_main(D_80112378_mstory4[var_s3], 1);
            espDispOff(D_80112378_mstory4[var_s3]);
            espKill(D_80112378_mstory4[var_s3]);
        }
    }

    HuSprAnimKill(D_801123A4_mstory4);
    func_8010F12C_mstory4();
    func_8001C5B4_main(temp_s5->model[1], temp_s5->motion[13]);
    func_8001C814_main(temp_s5->model[1], 2, 2);
    Hu3DModelPosSet(temp_s5->model[1], 0.0f, 0.0f, 2220.0f);
    Hu3DModelPosSet(temp_s5->model[2], 0.0f, -5.0f, 2220.0f);
    Hu3DModelRotSet(temp_s5->model[1], 0, 0, 0);
    Hu3DModelScaleSet(temp_s5->model[1], 1.5f, 1.5f, 1.5f);
    Hu3DModelScaleSet(temp_s5->model[2], 1.5f, 1.5f, 1.5f);
    HuPrcVSleep();
    func_8010F0A0_mstory4();
    HuPrcSleep(30);
    func_8001C258_main(temp_s7->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(temp_s7->model[6], 0.0f, 1000.0f, 2120.0f);
    Hu3DModelRotSet(temp_s7->model[6], 0, 0, 0);
    Hu3DModelScaleSet(temp_s7->model[6], 1.5f, 1.5f, 1.5f);
    func_8010E5C4_mstory4(temp_s7, 0.0f, 400.0f, 2120.0f, 0x3C, 0);
    D_80111B8C_mstory4 = 0;
    HuPrcSleep(20);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[0]].motId, 0, 0xA, 2);
    func_80107480_mstory4(temp_s5, 0.0f, 180.0f, 0.0f, 8);
    HuPrcSleep(20);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7E);
    func_80106CA8_mstory4();
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[4]].motId, 0, 0xA, 0);
    func_801074AC_mstory4(temp_fp);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[0]].motId, 0, 0xA, 2);
    func_80107480_mstory4(temp_s5, 0.0f, 0.0f, 0.0f, 0xA);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[11]].motId, 0, 0xA, 2);
    func_801118F8_mstory4(0, 0x1F);
    func_8010724C_mstory4(temp_s5, 0.0f, 0.0f, 2930.0f, 0x28, 0);
    func_8011196C_mstory4(0);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[0]].motId, 0, 0xA, 2);
    HuPrcSleep(20);
    CharFXPlay(0x2C6, GwStory.unk1);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[2]].motId, 0, 0xA, 0);
    func_80017954_main(temp_fp, 2, GwStory.unk1, D_80112330_mstory4);
    func_8010E5C4_mstory4(temp_s7, 0.0f, 400.0f, 2500.0f, 0x14, 0);
    func_801074AC_mstory4(temp_fp);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[3]].motId, 0, 0xA, 2);
    func_80110270_mstory4();
    HuPrcVSleep();
    for (i = 0; i < 4; i++) {
        func_80110DB0_mstory4(0.0f, 400.0f, 2500.0f, i << 3);
        HuPrcSleep(2);
    }
}

void func_80110270_mstory4(void) {
    s8 chr = GwStory.unk1;
    s8 i;

    D_801123A6_mstory4[0] = espEntry(func_8000B838_main(D_801120D4_mstory4[chr]), 0, 0);
    D_801123A6_mstory4[1] = espEntry(func_8000B838_main(0x1D001E), 0, 0);
    for (i = 0; i < 2; i++) {
        espPosSet(D_801123A6_mstory4[i], D_801120F4_mstory4[chr][i] + D_80112114_mstory4[i] / 2, 194);
    }
}

s16 func_80110394_mstory4(s32 file, s32 flags) {
    omObjData *obj;
    HmfModelData_UnkBC_Struct *effect;
    s16 model;

    obj = omAddObj(1000, 0, 0, -1, func_80110528_mstory4);
    obj->work[0] = model = func_801108FC_mstory4(file, flags);
    effect = Hu3DData[model].unkBC;
    effect->unk1C.f = effect->unk20.f = effect->unk24.f = 0.0f;
    effect->unk04 |= 1;
    effect->unk10.f = 100.0f;
    effect->unk14 = -1.0f;
    return model;
}

void func_80110460_mstory4(s16 modelId, s32 x, s32 y, s32 z) {
    HmfModelData_UnkBC_Struct *model = Hu3DData[modelId].unkBC;
    model->unk1C.i = x;
    model->unk20.i = y;
    model->unk24.i = z;
}

void func_80110494_mstory4(s16 modelId, s16 value) {
    Hu3DData[modelId].unkBC->unk14 = value;
}

void func_801104D4_mstory4(s16 modelId, f32 value) {
    Hu3DData[modelId].unkBC->unk10.f = value;
}

void func_80110500_mstory4(s16 model) {
    func_800138EC_main(model, 5, 4);
}

void func_80110528_mstory4(omObjData *obj) {
    s16 model = obj->work[0];
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;
    f32 x;
    f32 z;

    if (bc->unk04 & 4) {
        particle = bc->unk58;
        for (i = 0; i < hmf->unk1A; i++, particle++) {
            if (particle->unk04 > 0.0f) {
                break;
            }
        }
        if (i == hmf->unk1A) {
            Hu3DModelKill(model);
            omDelObj(obj);
            return;
        }
        bc->unk04 &= ~1;
    }
    if (bc->unk14 >= 0.0f) {
        if ((bc->unk14 -= 1.0f) <= 0.0f) {
            bc->unk04 &= ~1;
        }
    }
    if (bc->unk04 & 1) {
        x = rand8() * bc->unk10.f / 256.0f - bc->unk10.f / 2.0f;
        z = rand8() * bc->unk10.f / 256.0f - bc->unk10.f / 2.0f;
        func_80110724_mstory4(model, x + bc->unk1C.f, bc->unk20.f, z + bc->unk24.f);
    }
}

s32 func_80110724_mstory4(s16 model, f32 x, f32 y, f32 z) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = bc->unk58;
    s16 i;

    for (i = 0; i < hmf->unk1A; i++, particle++) {
        if (particle->unk04 <= 0.0f) {
            particle->unk0C = x;
            particle->unk10 = y;
            particle->unk14 = z;
            particle->unk04 = particle->unk08 =
                bc->unk08.f * 0.7f + bc->unk08.f * 0.3f * ((rand8() % 10 + 1) * 0.1f);
            return 1;
        }
    }
    return 0;
}

void func_80110888_mstory4(s16 modelId, f32 x, f32 y, f32 z) {
    HmfData *hmf = Hu3DData[modelId].hmf;
    HmfModelData_UnkBC_Struct *unkBC = Hu3DData[modelId].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *entry = unkBC->unk58;
    s16 i;

    unkBC->unk08.f = x;
    unkBC->unk0C.f = y;
    for (i = 0; i < hmf->unk1A; i++) {
        entry->unk1C = -z;
        entry++;
    }
}

s16 func_801108FC_mstory4(s32 file, s32 flags) {
    s16 model = func_80110B4C_mstory4(file, flags);
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *unkBC;
    HmfModelData_UnkBC_Unk58_Struct *entry;
    s16 i;

    func_80013390_main(model, -1, 0, func_801109EC_mstory4);
    hmf = Hu3DData[model].hmf;
    unkBC = Hu3DData[model].unkBC;
    entry = unkBC->unk58;
    unkBC->unk08.f = 5.0f;
    unkBC->unk0C.f = 20.0f;
    for (i = 0; i < hmf->unk1A; i++, entry++) {
        entry->unk0C = entry->unk10 = entry->unk14 = 0.0f;
        entry->unk18 = entry->unk20 = 0.0f;
        entry->unk1C = -10.0f;
        entry->unk04 = entry->unk08 = 0.0f;
    }
    return model;
}

void func_801109EC_mstory4(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = bc->unk58;
    s16 i;
    s16 count;

    for (i = 0, count = hmf->unk1A; i < count; i++, particle++) {
        if (particle->unk04 > 0.0f) {
            particle->unk0C = particle->unk0C * 0.04f + particle->unk18 + particle->unk0C;
            particle->unk10 += particle->unk1C;
            particle->unk14 = particle->unk14 * 0.04f + particle->unk20 + particle->unk14;
            particle->unk04 -= bc->unk08.f / bc->unk0C.f;
            if (particle->unk04 <= 0.0f) {
                particle->unk04 = 0.0f;
            }
            particle->unk08 = (D_80111BFC_mstory4[(bc->unk02 + i) & 3] * 0.15f + 1.0f) * particle->unk04;
        }
    }
    bc->unk02++;
}

s16 func_80110B4C_mstory4(s32 dataNum, s32 attr) {
    s16 model = func_8000B108_main(dataNum, attr);

    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    Hu3DModelRemakeStatic(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    return model;
}

void func_80110BB4_mstory4(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec orig;
    Vec rot;
    f32 step;
    f32 y;
    s32 i;

    orig.x = Hu3DData[model].pos.x;
    orig.y = Hu3DData[model].pos.y;
    orig.z = Hu3DData[model].pos.z;
    pos.y = Hu3DData[model].pos.y;
    rot.x = Hu3DData[model].rot.x;
    rot.y = Hu3DData[model].rot.y;
    rot.z = Hu3DData[model].rot.z;
    step = (230.0f - rot.y) / 12.0f;
    for (i = 0; i < 12; i++) {
        pos.x = Hu3DData[model].pos.x;
        pos.z = Hu3DData[model].pos.z;
        y = sindf(i * 15.0f) * 80.0f;
        rot.y += step;
        Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
        Hu3DModelRotSet(model, rot.x, y + rot.y, rot.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, orig.x, orig.y, orig.z);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_80110D5C_mstory4(omObjData *obj) {
    HuPrcSleep(30);
    func_80107480_mstory4(obj, -30.0f, -45.0f, 0.0f, 30);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_80110DB0_mstory4(f32 x, f32 y, f32 z, s16 arg3) {
    Process *process = omAddPrcObj(func_80110E3C_mstory4, 0x3F00, 0x2000, 0);
    UnkMstory4Work *work = HuMemAllocTag(sizeof(UnkMstory4Work), 0x7918);

    process->user_data = work;
    work->pos.x = x;
    work->pos.y = y;
    work->pos.z = z;
    work->unk_02 = arg3;
    work->unk_00 = 0;
}

// Only difference: the first rand8() term is converted in $f2 instead of
// directly in rx's register ($f28). Writing it as two statements to rx gets
// that, but swaps the $f26/$f28 allocation of rx and rz.
#ifdef NON_MATCHING
void func_80110E3C_mstory4(void) {
    UnkMstory4Work *work = HuPrcCurrentGet()->user_data;
    HmfData *hmf;
    HmfModelData_Unk64_Unk60_Unk54_Struct *face;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 model;
    s16 models[3];
    s16 total;
    s16 count;
    s16 i;
    s16 j;
    f32 rx;
    f32 ry;
    f32 rz;
    f32 x;
    f32 y;
    f32 z;

    models[0] = model = func_8000B108_main(0xB0034, 0x28C);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    hmf = Hu3DData[model].hmf;
    for (j = 0; j < hmf->unk10; j++) {
        count = hmf->unk60[j].unk22;
        face = hmf->unk60[j].unk54;
        for (i = 0; i < count; i++, face++) {
            face->unk00 |= 0x80;
        }
    }
    HuPrcVSleep();
    Hu3DModelRemakeStatic(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_80111740_mstory4);
    func_800138EC_main(model, 8, 8);
    func_80013954_main(model, 0);
    particle = Hu3DData[model].unkBC->unk58;
    total = hmf->unk1A;
    for (i = 0; i < total; i++, particle++) {
        particle->unk08 = particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
    }
    HuPrcVSleep();
    models[1] = func_8000B108_main(0xB004B, 0x29D);
    func_8001C814_main(models[1], 2, 2);
    Hu3DModelScaleSet(models[1], 0.2f, 0.2f, 0.2f);
    models[2] = func_8000B108_main(0xB004C, 0x29D);
    Hu3DModelScaleSet(models[2], 0.4f, 0.4f, 0.4f);
    HuPrcSleep(work->unk_02);
    func_8001C258_main(model, 4, 0);
    while (TRUE) {
        HuPrcVSleep();
        rx = ((s32)(rand8() * 25U >> 7) + 100.0f) * D_80111C00_mstory4;
        ry = (rand8() * 75 >> 7) + 50;
        rz = rand8() * 75 >> 7;
        rx *= 2.0f;
        ry *= 2.0f;
        rz *= 2.0f;
        D_80111C00_mstory4 *= -1;
        func_8001C258_main(models[1], 4, 0);
        for (i = 0; i <= 20; i++) {
            x = rx * sindf(i / 20.0f * 90.0f) + work->pos.x;
            y = ry * sindf(i / 20.0f * 135.0f + 45.0f) - ry * sindf(45.0f) + work->pos.y;
            z = rz * sindf(i / 20.0f * 90.0f) + work->pos.z;
            Hu3DModelPosSet(models[1], x, y, z);
            HuPrcVSleep();
        }
        func_8001C258_main(models[1], 4, 4);
        HuPrcSleep(5);
        if (rand8() & 3) {
            func_8001C258_main(models[2], 4, 0);
            Hu3DMotionTimeSet(models[2], 0.0f);
            Hu3DMotionSpeedSet(models[2], 3.0f);
            Hu3DModelPosSet(models[2], x, y, z);
            for (i = 0; i < 8; i++) {
                func_80111430_mstory4(model, x, y, z, total / 8, i & 3);
                HuPrcVSleep();
            }
            func_8001C258_main(models[2], 4, 4);
        } else {
            for (i = 0; i < 8; i++) {
                func_80111430_mstory4(model, x, y, z, total / 8, i & 3);
                HuPrcVSleep();
            }
        }
        HuPrcSleep(25);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C8050", func_80110E3C_mstory4);
#endif

void func_80111430_mstory4(s16 model, f32 x, f32 y, f32 z, s16 count, s32 randomAxis) {
    f32 step = 360.0f / count;
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Unk58_Struct *particle = Hu3DData[model].unkBC->unk58;
    s16 total = hmf->unk1A;
    f32 ax;
    f32 ay;
    f32 az;
    f32 len;
    f32 angle;
    s16 type;
    s16 i;
    s16 j;

    if (randomAxis) {
        while (TRUE) {
            ax = rand8() - 128;
            ay = rand8() - 128;
            az = rand8() - 128;
            len = ax * ax + ay * ay + az * az;
            if (len != 0.0f) {
                break;
            }
        }
    } else {
        ax = 0.0f;
        ay = 0.0f;
        az = 1.0f;
        len = ax * ax + ay * ay + az * az;
    }
    len = HuSqrtf(len);
    ax /= len;
    ay /= len;
    az /= len;
    type = rand8() & 3;
    for (i = 0, j = 0; j < total; j++, particle++) {
        if (particle->unk08 <= 0.0f) {
            particle->unk0C = x;
            particle->unk10 = y;
            particle->unk14 = z;
            angle = step * i;
            particle->unk18 = ax * ay * (1.0f - cosdf(angle)) - az * sindf(angle);
            particle->unk1C = ay * ay + (1.0f - ay * ay) * cosdf(angle);
            particle->unk20 = ay * az * (1.0f - cosdf(angle)) + ax * sindf(angle);
            particle->unk24 = type;
            particle->unk28 = 0.0f;
            particle->unk08 = 1.0f;
            particle->unk04 = 20.0f;
            if (++i >= count) {
                break;
            }
        }
    }
}

void func_80111740_mstory4(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count;
    s16 i;
    s16 color;
    f32 dx;
    f32 dy;
    f32 dz;

    if (bc->unk00 == -1) {
        count = hmf->unk1A;
    } else {
        count = hmf->unk60[bc->unk00].unk2E;
    }
    particle = bc->unk58;
    if (bc->unk02 >= 50) {
        if (!(bc->unk04 & 1)) {
            return;
        }
        bc->unk02 = 0;
    }
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 > 0.0f) {
            color = particle->unk24;
            particle->unk28 += 1.0f;
            particle->unk00[0] = D_80111C04_mstory4[color * 3 + 0];
            particle->unk00[1] = D_80111C04_mstory4[color * 3 + 1];
            particle->unk00[2] = D_80111C04_mstory4[color * 3 + 2];
            dx = particle->unk18 * particle->unk04;
            dy = particle->unk1C * particle->unk04;
            dz = particle->unk20 * particle->unk04;
            particle->unk0C += dx;
            particle->unk10 += dy;
            particle->unk14 += dz;
            particle->unk04 *= 0.9f;
            particle->unk08 -= 0.05f;
        }
    }
}

void func_801118F8_mstory4(s32 index, s32 seNo) {
    if (D_801122A0_mstory4[index].unk_0C == 0) {
        D_801122A0_mstory4[index].unk_0C = 1;
        D_801122A0_mstory4[index].unk_10 = seNo;
        if (index == 0) {
            D_801122A0_mstory4[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
        }
    }
}

void func_8011196C_mstory4(s32 index) {
    if (D_801122A0_mstory4[index].unk_0C == 1) {
        D_801122A0_mstory4[index].unk_0C = 0;
        if (index == 0) {
            HuAudFXStop((s16)D_801122A0_mstory4[0].unk_14);
        }
    }
}

void func_801119C0_mstory4(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 3; i++) {
            if (D_801122A0_mstory4[i].unk_0C == 1 && Hu3DData[D_801122A0_mstory4[i].obj->model[1]].motTime == 0.0f) {
                seNo = D_801122A0_mstory4[i].unk_10;
                if (i == 0) {
                    D_801122A0_mstory4[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                }
            }
        }
        HuPrcVSleep();
    }
}

const UnkMstory4SprGroup D_80112088_mstory4[6] = {
    { 4, D_80111BA4_mstory4 },
    { 5, D_80111BB4_mstory4 },
    { 4, D_80111BC8_mstory4 },
    { 3, D_80111BD8_mstory4 },
    { 3, D_80111BE4_mstory4 },
    { 3, D_80111BF0_mstory4 },
};

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_801120B8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_801120D4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_801120F4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C8050", D_80112114_mstory4);
