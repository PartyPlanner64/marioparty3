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

extern Vec D_80111B04_mstory4[];
extern Vec D_80111B34_mstory4[];
extern const Vec D_80111DDC_mstory4;
extern const Vec D_80111DF4_mstory4;
extern const Vec D_80111E0C_mstory4;
extern const Vec D_80111E18_mstory4;
extern const Vec D_80111E24_mstory4;
extern const Vec D_80111E30_mstory4;
extern const Vec D_80111E3C_mstory4;
extern const Vec D_80111E48_mstory4;
extern const Vec D_80111E54_mstory4;
extern const Vec D_80111E60_mstory4;

extern s32 D_80111B00_mstory4;
extern Vec D_80111DB8_mstory4;
extern Vec D_80111DC4_mstory4;
extern Vec D_80111E78_mstory4;
extern Vec D_80111E84_mstory4;
extern Vec D_80111ECC_mstory4;
extern Vec D_80111EE4_mstory4;
extern void (*const D_80111C10_mstory4[])(void);
extern UnkStoryObj D_801121C0_mstory4[5];
extern s16 D_8011223A_mstory4;
extern s32 D_80112238_mstory4[4];
extern Vec D_8011225C_mstory4;
extern const Vec D_80111C7C_mstory4;
extern s16 D_8011223E_mstory4;
extern s16 D_80112242_mstory4;
extern s16 D_80112246_mstory4;
extern s16 D_80112248_mstory4;
extern s16 D_8011228C_mstory4;
extern s16 D_80112290_mstory4[4];
extern Vec D_80112250_mstory4;
extern const Vec D_80111C70_mstory4;
extern const s32 D_80111CAC_mstory4[];
extern const s32 D_80111CCC_mstory4[];
extern const s32 D_80111CEC_mstory4[];
extern const s32 D_80111D0C_mstory4[];
extern s32 D_800A178C_main[][6];
extern Vec D_80112274_mstory4;
extern const Vec D_80111C94_mstory4;
extern Vec D_80112268_mstory4;
extern const Vec D_80111C88_mstory4;
extern Vec D_80112280_mstory4;
extern const Vec D_80111CA0_mstory4;
extern s16 D_8011228E_mstory4;
extern const s32 D_80111F08_mstory4[];

void func_801078B4_mstory4(MstoryPath *path, f32 time, Vec *result);
void func_80106DA0_mstory4(omObjData *obj, const Vec *pos, s32 frames);
void func_80106DBC_mstory4(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_801072D8_mstory4(omObjData *obj, const Vec *pos, s32 frames);
void func_80108280_mstory4(omObjData *obj);
void func_801086EC_mstory4(void);
void func_801086F4_mstory4(omObjData *obj);
void func_801093B0_mstory4(omObjData *obj);
void func_8010A44C_mstory4(omObjData *obj);
void func_8010A76C_mstory4(omObjData *obj);
void func_80107480_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_8010A3C8_mstory4(void);
void func_80109840_mstory4(omObjData *obj);
void func_8010ABD0_mstory4(s32 index, s32 seNo);
void func_8010AC84_mstory4(s32 index);
void func_80109B5C_mstory4(omObjData *object);
void func_80109CCC_mstory4(omObjData *obj);
void func_80109E3C_mstory4(omObjData *obj);
void func_80109E68_mstory4(omObjData *obj);
void func_80108288_mstory4(void);
void func_801094DC_mstory4(void);
void func_80109838_mstory4(void);
void func_80109EA4_mstory4(void);
void func_8010A1C4_mstory4(void);
void func_8010A480_mstory4(void);
void func_8010A05C_mstory4(void);
void func_8010A064_mstory4(omObjData *obj);
void func_8010A5AC_mstory4(void);
void func_8010A764_mstory4(void);
void func_8010ACF4_mstory4(void);
void func_801060E8_mstory4(void);
void func_801060F8_mstory4(s32 arg0);
s32 func_80106B20_mstory4(void);
void func_80106B3C_mstory4(s16 model, s16 animSlot, s16 anim);
void func_80106C10_mstory4(void);
void func_80106C78_mstory4(void);
void func_80106CA8_mstory4(void);
void func_80106CCC_mstory4(s32 mess);
void func_801074AC_mstory4(s16 model);

MstoryPath *func_801075B0_mstory4(Vec *points, s32 flags) {
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

void func_801078B4_mstory4(MstoryPath *path, f32 time, Vec *result) {
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

void func_8010815C_mstory4(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010818C_mstory4(void) {
    func_80106C10_mstory4();
    D_8011228C_mstory4 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80108288_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_801094DC_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_80109EA4_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A1C4_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A480_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A5AC_mstory4, 900, 0x800, 0);
    omAddPrcObj(func_8010ACF4_mstory4, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_8011228C_mstory4, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_80108280_mstory4(omObjData *obj) {
}

void func_80108288_mstory4(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 16, -1, NULL);
    D_801121C0_mstory4[0].obj = obj;
    D_801121C0_mstory4[0].unk_08 = 0;
    D_801121C0_mstory4[0].unk_0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
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
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x30));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 0x21));
    func_8000B460_main(obj, 6, D_80111CAC_mstory4[chr]);
    func_8000B460_main(obj, 7, D_80111CCC_mstory4[chr]);
    func_8000B460_main(obj, 8, D_80111CEC_mstory4[chr]);
    func_8000B460_main(obj, 9, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 10, D_80111D0C_mstory4[chr]);
    func_8000B460_main(obj, 11, func_80017BB8_main(chr, 0x2C));
    func_8000B460_main(obj, 12, func_80017BB8_main(chr, 0x7A));
    func_8000B460_main(obj, 13, func_80017BB8_main(chr, 0x9B));
    D_80112290_mstory4[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80112290_mstory4[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80112290_mstory4[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80112290_mstory4[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112290_mstory4[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_80112250_mstory4 = D_80111C70_mstory4;
    Hu3DModelPosSet(obj->model[1], D_80112250_mstory4.x, D_80112250_mstory4.y, D_80112250_mstory4.z);
    Hu3DModelPosSet(obj->model[2], D_80112250_mstory4.x, -5.0f, D_80112250_mstory4.z);
    Hu3DModelPosSet(obj->model[4], D_80112250_mstory4.x, D_80112250_mstory4.y, D_80112250_mstory4.z);
    omPrcSetDestructor(0, func_801086EC_mstory4);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
    while (TRUE) {
        D_801121C0_mstory4[0].func(obj);
        HuPrcVSleep();
    }
}

void func_801086EC_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111C70_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111C7C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111C88_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111C94_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111CA0_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111CAC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111CCC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111CEC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111D0C_mstory4);

const Vec D_80111D2C_mstory4 = { 0.0f, 0.0f, 0.0f };

const Vec D_80111D38_mstory4 = { 0.0f, 180.0f, 0.0f };

const Vec D_80111D44_mstory4 = { 0.0f, 90.0f, 0.0f };

const Vec D_80111D50_mstory4 = { 0.0f, -90.0f, 0.0f };

const Vec D_80111D5C_mstory4 = { -100.0f, 0.0f, 350.0f };

const Vec D_80111D68_mstory4 = { -100.0f, 0.0f, 150.0f };

const Vec D_80111D74_mstory4 = { 0.0f, 20.0f, 0.0f };

const Vec D_80111D80_mstory4 = { 0.0f, 0.0f, 0.0f };

const Vec D_80111D8C_mstory4 = { 0.0f, -26.565f, 0.0f };

const char D_80111D98_mstory4[] = "item_hook";

const char D_80111DA4_mstory4[] = "";

void func_801086F4_mstory4(omObjData *obj) {
    omObjData *obj1;
    omObjData *obj3;
    s16 model;
    HmfMotionNode *node;
    s32 i;
    f32 scale;
    f32 time;

    HuPrcSleep(20);
    obj1 = D_801121C0_mstory4[1].obj;
    obj3 = D_801121C0_mstory4[3].obj;
    model = obj->model[1];
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107480_mstory4(obj, 0.0f, 110.0f, 0.0f, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    HuPrcSleep(10);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], model, D_80111D98_mstory4);
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    func_801074AC_mstory4(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_801074AC_mstory4(model);
    while (!(D_801121C0_mstory4[4].unk_08 & 1)) {
        HuPrcVSleep();
    }
    func_8001C258_main(D_801121C0_mstory4[4].obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(D_8011228E_mstory4, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8002FD8C_main(model, Hu3DData[model].motId, D_80111D98_mstory4, 27, 69);
    func_8002FD8C_main(model, Hu3DData[model].motId, D_80111D98_mstory4, 27, 70);
    func_8002FD8C_main(model, Hu3DData[model].motId, D_80111D98_mstory4, 27, 71);
    node = func_8001D33C_main(model, D_80111D98_mstory4);
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
    func_8002FDCC_main(model, Hu3DData[model].motId, D_80111D98_mstory4, 27, 71);
    func_8002FDCC_main(model, Hu3DData[model].motId, D_80111D98_mstory4, 27, 70);
    func_8002FDCC_main(model, Hu3DData[model].motId, D_80111D98_mstory4, 27, 69);
    func_801060F8_mstory4(6);
    while (TRUE) {
        if (func_80106B20_mstory4() != 0) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A72);
    func_80106CA8_mstory4();
    func_80106B3C_mstory4(obj1->model[1], D_80112248_mstory4, D_80112246_mstory4);
    D_801121C0_mstory4[1].func = func_80109CCC_mstory4;
    HuPrcSleep(12);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A73);
    func_80106CA8_mstory4();
    func_8001C5B4_main(model, obj->motion[6]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionSpeedSet(model, 2.0f);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    func_8001C5B4_main(model, obj->motion[7]);
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
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_801072D8_mstory4(obj, &D_80111D2C_mstory4, 10);
    HuAudSeqPlay(0x72);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112290_mstory4[2]);
    func_801074AC_mstory4(model);
    CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    HuPrcSleep(60);
    func_801072D8_mstory4(obj3, &D_80111D8C_mstory4, 3);
    func_80106DA0_mstory4(obj3, &D_80111D5C_mstory4, 5);
    func_801072D8_mstory4(obj3, &D_80111D74_mstory4, 3);
    D_801121C0_mstory4[1].func = func_80109B5C_mstory4;
    HuAudFXPlay(0x219);
    func_8001C258_main(obj->model[4], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[5]].motId, 0, 10, 0);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112290_mstory4[3]);
    func_801072D8_mstory4(obj3, &D_80111D80_mstory4, 3);
    func_80106DBC_mstory4(obj3, &D_80111D68_mstory4, 10, 0);
    func_80107480_mstory4(obj1, 0.0f, 225.0f, 0.0f, 10);
    func_801074AC_mstory4(model);
    HuAudSeqPlay(0x26);
    func_801072D8_mstory4(obj, &D_80111D38_mstory4, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[2]].motId, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A74);
    func_80106CA8_mstory4();
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[11]].motId, 0, 10, 2);
    func_80106B3C_mstory4(obj1->model[1], D_80112248_mstory4, D_8011223A_mstory4);
    func_80107480_mstory4(obj1, 0.0f, 225.0f, 0.0f, 10);
    HuPrcSleep(50);
    func_80107480_mstory4(obj3, 30.0f, -20.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[1]].motId, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A76);
    func_80106CA8_mstory4();
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    func_80107480_mstory4(obj3, 0.0f, 0.0f, 0.0f, 5);
    HuPrcSleep(50);
    HuAudSeqPlay(0x29);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[3]].motId, 0, 10, 0);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A77);
    func_80106CA8_mstory4();
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    D_801121C0_mstory4[1].func = func_80109E3C_mstory4;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[12]].motId, 0, 10, 0);
    func_801074AC_mstory4(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[2]].motId, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A78);
    func_80106CA8_mstory4();
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[3]].motId, 0, 10, 0);
    func_80107480_mstory4(obj3, 0.0f, 0.0f, 0.0f, 10);
    func_80106B3C_mstory4(obj1->model[1], D_80112248_mstory4, D_80112246_mstory4);
    D_801121C0_mstory4[1].func = func_80109E68_mstory4;
    func_80107480_mstory4(obj, 0.0f, 0.0f, 0.0f, 10);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80112290_mstory4[1]);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_801074AC_mstory4(model);
    HuPrcSleep(30);
    func_801060E8_mstory4();
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_801093B0_mstory4(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[10]].motId, 0, 10, 0);
    func_801074AC_mstory4(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_80109474_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111DB8_mstory4, 10);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_801094A8_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111DC4_mstory4, 10);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111DB8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111DC4_mstory4);

const char D_80111DD0_mstory4[] = "c204n_0_DEF";

void func_801094DC_mstory4(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 4, 8, -1, NULL);
    D_801121C0_mstory4[1].obj = obj;
    D_801121C0_mstory4[1].unk_08 = 0;
    D_801121C0_mstory4[1].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_8011225C_mstory4 = D_80111C7C_mstory4;
    Hu3DModelPosSet(obj->model[1], D_8011225C_mstory4.x, D_8011225C_mstory4.y, D_8011225C_mstory4.z);
    Hu3DModelPosSet(obj->model[2], D_8011225C_mstory4.x, -5.0f, D_8011225C_mstory4.z);
    data = DataRead(0xA007E);
    D_80112238_mstory4[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_80111DD0_mstory4);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011223A_mstory4, 1, 0);
    Hu3DAnimBankSet(D_8011223A_mstory4, 0);
    D_80112248_mstory4 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011223A_mstory4, 0, D_80111DD0_mstory4);
    D_80112238_mstory4[0] = D_800D1714_main[D_80112238_mstory4[0]].animIdx;
    data = DataRead(0xA0080);
    D_80112238_mstory4[1] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80112238_mstory4[2] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0084);
    D_80112238_mstory4[3] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106B3C_mstory4(obj->model[1], D_80112248_mstory4, D_8011223A_mstory4);
    omPrcSetDestructor(0, func_80109838_mstory4);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
    while (TRUE) {
        D_801121C0_mstory4[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80109838_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111DDC_mstory4);

const Vec D_80111DE8_mstory4 = { 10.0f, 378.9f, 0.0f };

void func_80109840_mstory4(omObjData *obj) {
    D_801121C0_mstory4[0].func = func_801093B0_mstory4;
    D_801121C0_mstory4[3].func = func_8010A44C_mstory4;
    func_801072D8_mstory4(obj, &D_80111DE8_mstory4, 30);
    func_80106DA0_mstory4(obj, &D_80111E48_mstory4, 20);
    HuPrcSleep(30);
    func_801072D8_mstory4(obj, &D_80111E18_mstory4, 10);
    func_80106DA0_mstory4(obj, &D_80111E3C_mstory4, 15);
    func_80107480_mstory4(D_801121C0_mstory4[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_801072D8_mstory4(obj, &D_80111DF4_mstory4, 15);
    HuPrcSleep(20);
    func_801072D8_mstory4(obj, &D_80111E0C_mstory4, 10);
    func_801072D8_mstory4(D_801121C0_mstory4[3].obj, &D_80111E54_mstory4, 10);
    Hu3DMotionShiftSet(D_801121C0_mstory4[3].obj->model[1], Hu3DData[D_801121C0_mstory4[3].obj->motion[1]].motId, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A71);
    func_80106CA8_mstory4();
    Hu3DMotionShiftSet(D_801121C0_mstory4[3].obj->model[1], Hu3DData[D_801121C0_mstory4[3].obj->motion[0]].motId, 0, 10, 2);
    func_801072D8_mstory4(D_801121C0_mstory4[3].obj, &D_80111E60_mstory4, 10);
    D_801121C0_mstory4[4].func = func_8010A76C_mstory4;
    func_801072D8_mstory4(obj, &D_80111DDC_mstory4, 20);
    Hu3DMotionShiftSet(D_801121C0_mstory4[0].obj->model[1], Hu3DData[D_801121C0_mstory4[0].obj->motion[13]].motId, 0, 10, 2);
    while (!(D_801121C0_mstory4[4].unk_08 & 2)) {
        HuPrcVSleep();
    }
    D_801121C0_mstory4[0].func = func_801086F4_mstory4;
    HuPrcSleep(40);
    func_801072D8_mstory4(obj, &D_80111E30_mstory4, 50);
    func_801072D8_mstory4(obj, &D_80111E24_mstory4, 40);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109AE0_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111E84_mstory4, 10);
    func_80106DA0_mstory4(obj, &D_80111E78_mstory4, 50);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109B5C_mstory4(omObjData *obj) {
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
    func_80106B3C_mstory4(obj->model[1], D_80112248_mstory4, D_80112242_mstory4);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109CCC_mstory4(omObjData *obj) {
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
    func_80106B3C_mstory4(obj->model[1], D_80112248_mstory4, D_80112246_mstory4);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109E3C_mstory4(omObjData *obj) {
    HuPrcSleep(5);
    D_801121C0_mstory4[1].func = func_80109B5C_mstory4;
}

void func_80109E68_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 0.0f, 0.0f, 10);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109EA4_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801121C0_mstory4[2].obj = obj;
    D_801121C0_mstory4[2].unk_08 = 0;
    D_801121C0_mstory4[2].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0x800A0, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
    func_8000B460_main(obj, 0, 0x80000);
    func_8000B460_main(obj, 1, 0x1D0076);
    func_8000B460_main(obj, 2, 0x1D0077);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    D_80112268_mstory4 = D_80111C88_mstory4;
    Hu3DModelPosSet(obj->model[1], D_80112268_mstory4.x, D_80112268_mstory4.y, D_80112268_mstory4.z);
    Hu3DModelPosSet(obj->model[2], D_80112268_mstory4.x, -5.0f, D_80112268_mstory4.z);
    omPrcSetDestructor(0, func_8010A05C_mstory4);
    D_801121C0_mstory4[2].func = func_8010A064_mstory4;
    while (1) {
        D_801121C0_mstory4[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A05C_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111DF4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E0C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E18_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E24_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E30_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E3C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E48_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E54_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E60_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E78_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111E84_mstory4);

const Vec D_80111E9C_mstory4 = { 200.0f, 0.0f, 1200.0f };
const Vec D_80111EA8_mstory4 = { 166.66666f, 0.0f, 150.0f };

void func_8010A064_mstory4(omObjData *obj) {
    HuPrcSleep(10);
    CharFXPlay(0x26B, 6);
    HuPrcSleep(30);
    func_80106B3C_mstory4(D_801121C0_mstory4[1].obj->model[1], D_80112248_mstory4, D_8011223E_mstory4);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A70);
    func_80106CA8_mstory4();
    func_80106B3C_mstory4(D_801121C0_mstory4[1].obj->model[1], D_80112248_mstory4, D_8011223A_mstory4);
    D_801121C0_mstory4[1].func = func_80109840_mstory4;
    CharFXPlay(0x286, 6);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    func_8010ABD0_mstory4(2, 40);
    func_80106DA0_mstory4(obj, &D_80111E9C_mstory4, 40);
    func_8010AC84_mstory4(2);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801121C0_mstory4[2].func = func_80108280_mstory4;
}

void func_8010A1C4_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801121C0_mstory4[3].obj = obj;
    D_801121C0_mstory4[3].unk_08 = 0;
    D_801121C0_mstory4[3].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0129);
    func_8000B460_main(obj, 3, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_80112274_mstory4 = D_80111C94_mstory4;
    Hu3DModelPosSet(obj->model[1], D_80112274_mstory4.x, D_80112274_mstory4.y, D_80112274_mstory4.z);
    Hu3DModelPosSet(obj->model[2], D_80112274_mstory4.x, -5.0f, D_80112274_mstory4.z);
    omPrcSetDestructor(0, func_8010A3C8_mstory4);
    D_801121C0_mstory4[3].func = func_80108280_mstory4;
    D_80111B00_mstory4 = 1;
    while (1) {
        D_801121C0_mstory4[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A3C8_mstory4(void) {
}

const Vec D_80111EB4_mstory4 = { 700.0f, 0.0f, 150.0f };
const Vec D_80111EC0_mstory4 = { 216.66666f, 0.0f, 150.0f };

void func_8010A3D0_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111ECC_mstory4, 10);
    func_80106DA0_mstory4(obj, &D_80111EB4_mstory4, 50);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801121C0_mstory4[3].func = func_80108280_mstory4;
}

void func_8010A44C_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111EE4_mstory4, 20);
    D_801121C0_mstory4[3].func = func_80108280_mstory4;
}

void func_8010A480_mstory4(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80111B00_mstory4 != 0) {
        model = D_801121C0_mstory4[3].obj->model[1];
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

void func_8010A5AC_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_801121C0_mstory4[4].obj = obj;
    D_801121C0_mstory4[4].unk_08 = 0;
    D_801121C0_mstory4[4].unk_0C = 0;
    obj->model[1] = func_8000B108_main(D_80111F08_mstory4[0], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80112280_mstory4 = D_80111CA0_mstory4;
    Hu3DModelPosSet(obj->model[1], D_80112280_mstory4.x, D_80112280_mstory4.y, D_80112280_mstory4.z);
    D_8011228E_mstory4 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_8011228E_mstory4, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_8011228E_mstory4, 60.0f);
    func_800138EC_main(D_8011228E_mstory4, 1, 0);
    func_8001C258_main(D_8011228E_mstory4, 4, 4);
    omPrcSetDestructor(0, func_8010A764_mstory4);
    D_801121C0_mstory4[4].func = func_80108280_mstory4;
    while (1) {
        D_801121C0_mstory4[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A764_mstory4(void) {
}

void func_8010A76C_mstory4(omObjData *obj) {
    Vec pos;
    MstoryPath *paths[2];
    omObjData *target;
    f32 rotY;
    s32 i;

    paths[0] = func_801075B0_mstory4(D_80111B04_mstory4, 0);
    paths[1] = func_801075B0_mstory4(D_80111B34_mstory4, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_8011228E_mstory4, 4, 0);
    func_800138EC_main(D_8011228E_mstory4, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        func_801078B4_mstory4(paths[0], (i * 0.02f) * (i * 0.02f), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_8011228E_mstory4, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    target = D_801121C0_mstory4[3].obj;
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[3]].motId, 0, 10, 0);
    HuPrcSleep(20);
    D_801121C0_mstory4[4].unk_08 |= 2;
    HuAudFXPlay(0x218);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[0]].motId, 0, 10, 2);
    rotY = 0.0f;
    for (i = 0; i < 120; i++) {
        func_801078B4_mstory4(paths[1], (i * 0.008333334f) * (i * 0.008333334f), &pos);
        rotY -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        Hu3DModelRotSet(obj->model[1], 0.0f, rotY, 0.0f);
        func_8000CFA4_main(D_8011228E_mstory4, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(D_8011228E_mstory4, 4, 4);
    HuAudFXPlay(0x21A);
    func_8010815C_mstory4(paths[0]);
    func_8010815C_mstory4(paths[1]);
    D_801121C0_mstory4[4].unk_08 = 1;
    D_801121C0_mstory4[4].func = func_80108280_mstory4;
}

void func_8010AA88_mstory4(omObjData *obj, omObjData *target) {
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

void func_8010ABD0_mstory4(s32 index, s32 seNo) {
    if (D_801121C0_mstory4[index].unk_0C == 0) {
        D_801121C0_mstory4[index].unk_0C = 1;
        D_801121C0_mstory4[index].unk_10 = seNo;
        switch (index) {
            case 0:
                D_801121C0_mstory4[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                D_801121C0_mstory4[index].unk_14 = CharFXPlay(seNo, 6);
                break;
        }
    }
}

void func_8010AC84_mstory4(s32 index) {
    if (D_801121C0_mstory4[index].unk_0C == 1) {
        D_801121C0_mstory4[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop((s16)D_801121C0_mstory4[index].unk_14);
        }
    }
}

void func_8010ACF4_mstory4(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 5; i++) {
            if (D_801121C0_mstory4[i].unk_0C == 1 && Hu3DData[D_801121C0_mstory4[i].obj->model[1]].motTime == 0.0f) {
                seNo = D_801121C0_mstory4[i].unk_10;
                switch (i) {
                    case 0:
                        D_801121C0_mstory4[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                        break;
                    case 2:
                        D_801121C0_mstory4[i].unk_14 = CharFXPlay(seNo, 6);
                        break;
                }
            }
        }
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111ECC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111EE4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C47E0", D_80111F08_mstory4);
