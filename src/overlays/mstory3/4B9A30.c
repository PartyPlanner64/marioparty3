#include "common.h"
#include "game/hmfmath.h"

typedef struct UnkMstory3Obj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} UnkMstory3Obj; // sizeof 0x14

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern Vec D_801158E0_mstory3;
extern Vec D_80115908_mstory3;
extern Vec D_80115914_mstory3;
extern Vec D_80115920_mstory3;
extern Vec D_8011598C_mstory3;
extern Vec D_80115998_mstory3;
extern Vec D_8011592C_mstory3;
extern Vec D_80115938_mstory3;
extern Vec D_80115944_mstory3;
extern Vec D_80115950_mstory3;
extern Vec D_8011595C_mstory3;
extern Vec D_801159BC_mstory3;
extern Vec D_801159C8_mstory3;
extern Vec D_801159D4_mstory3;
extern Vec D_801159E0_mstory3;
extern Vec D_801159F8_mstory3;
extern Vec D_80115A10_mstory3;
extern Vec D_80115A1C_mstory3;
extern Vec D_80115A28_mstory3;
extern Vec D_80115A34_mstory3;
extern Vec D_80115A40_mstory3;
extern Vec D_80115A4C_mstory3;
extern Vec D_80115A58_mstory3;
extern Vec D_80115A64_mstory3;
extern Vec D_80115A70_mstory3;
extern Vec D_80115A7C_mstory3;
extern Vec D_80115A88_mstory3;
extern Vec D_80115A94_mstory3;
extern Vec D_80115AA0_mstory3;
extern Vec D_80115B24_mstory3;
extern Vec D_80115B30_mstory3;
extern Vec D_80115B3C_mstory3;
extern Vec D_80115B48_mstory3;
extern Vec D_80115B54_mstory3;
extern Vec D_80115478_mstory3[];
extern Vec D_80115400_mstory3[];
extern Vec D_80115430_mstory3[];
extern Vec D_801154A8_mstory3[];
extern s16 D_80115C9C_mstory3[];
extern s16 D_80115CA2_mstory3[];
extern UnkMstory3Obj D_80115CB0_mstory3[11];
extern s16 D_80115D8C_mstory3;
extern s16 D_80115DA4_mstory3[4];
extern s16 D_80115DAE_mstory3;
extern const char D_8011588C_mstory3[];
extern s16 D_80115D9C_mstory3;
extern s16 D_80115DA0_mstory3;
extern s16 D_80115DA2_mstory3;
extern s16 D_80115D8E_mstory3;
extern s16 D_80115D90_mstory3[3];
extern s16 D_80115D96_mstory3;
extern s16 D_80115DB0_mstory3;
extern s16 D_80115D98_mstory3[5];
extern char *D_801153E0_mstory3[];
extern s32 D_800A178C_main[][6];

MstoryPath *func_8010C9F0_mstory3(Vec *points, s32 flags);
void func_8010CCF4_mstory3(MstoryPath *path, f32 time, Vec *result);
void func_8010D59C_mstory3(MstoryPath *path);
void func_8010D774_mstory3(omObjData *obj);
void func_801110AC_mstory3(void);
void func_80114EF8_mstory3(omObjData *obj);
void func_80110978_mstory3(omObjData *obj);
void func_80114FA4_mstory3(omObjData *obj);
void func_801122BC_mstory3(void);
void func_80114AF8_mstory3(void);
void func_80105F54_mstory3(void);
void func_8010D77C_mstory3(void);
void func_8010D97C_mstory3(void);
void func_8010F660_mstory3(void);
void func_80110CB4_mstory3(void);
void func_801110B4_mstory3(void);
void func_80111764_mstory3(void);
void func_801122C4_mstory3(void);
void func_8011249C_mstory3(void);
void func_80112B88_mstory3(void);
void func_801134E0_mstory3(void);
void func_80113968_mstory3(void);
void func_80113BB0_mstory3(void);
void func_801149D0_mstory3(void);
void func_80114B00_mstory3(void);
void func_801061C4_mstory3(void);
void func_80106220_mstory3(void);
void func_80106DC4_mstory3(omObjData *obj, const Vec *pos, s32 frames);
void func_80106CF0_mstory3(s16 model, s16 arg1, s16 arg2);
void func_80106DE0_mstory3(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_80107070_mstory3(omObjData *obj, const Vec *pos, s32 frames);
void func_8010733C_mstory3(omObjData *obj, f32 speed, s16 frames);
void func_801074D8_mstory3(omObjData *obj, f32 speed, s16 frames);
void func_80107244_mstory3(s16 model);
void func_80107674_mstory3(omObjData *obj, omObjData *target);
void func_80107218_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80106400_mstory3(s32 arg0);
s32 func_80106CDC_mstory3(void);
void func_8010603C_mstory3(void);
void func_80106090_mstory3(s32 mess);
void func_8010606C_mstory3(void);
void func_8010DA00_mstory3(omObjData *obj);
void func_8010E170_mstory3(omObjData *obj);
void func_8010FDB0_mstory3(omObjData *obj);
void func_80110E30_mstory3(omObjData *obj);
void func_80111A58_mstory3(omObjData *obj);
void func_80111B34_mstory3(omObjData *obj);
void func_80113E68_mstory3(omObjData *obj);
void func_801142C0_mstory3(omObjData *obj);
void func_8011065C_mstory3(omObjData *obj);
void func_80110A84_mstory3(omObjData *obj);
void func_80111E2C_mstory3(omObjData *obj);
void func_80111F3C_mstory3(omObjData *obj);
void func_801125C4_mstory3(omObjData *obj);
void func_80112834_mstory3(omObjData *obj);
void func_8011270C_mstory3(omObjData *obj);
void func_8011268C_mstory3(omObjData *obj);
void func_80112EF0_mstory3(omObjData *obj);
void func_80112FB0_mstory3(omObjData *obj);
void func_8011322C_mstory3(omObjData *obj);
void func_80113874_mstory3(omObjData *obj);
void func_80114920_mstory3(omObjData *obj);
void func_8011522C_mstory3(omObjData *obj);

MstoryPath *func_8010C9F0_mstory3(Vec *points, s32 flags) {
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

void func_8010CCF4_mstory3(MstoryPath *path, f32 time, Vec *result) {
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

void func_8010D59C_mstory3(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010D5CC_mstory3(void) {
    D_80115DB0_mstory3 = GwStory.unk1;
    func_80105F54_mstory3();
    D_80115D8C_mstory3 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8010F660_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80110CB4_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_801110B4_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80111764_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_801122C4_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112B88_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_801134E0_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113968_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113BB0_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_80114B00_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010D97C_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_8011249C_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_801149D0_mstory3, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010D77C_mstory3, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115D8C_mstory3, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8010D774_mstory3(omObjData *obj) {
}

void func_8010D77C_mstory3(void) {
    s16 seNo;
    s8 vol;
    f32 z;

    while (TRUE) {
        if (D_80115CB0_mstory3[0].unk_0C == 1 && Hu3DData[D_80115CB0_mstory3[0].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)D_80115CB0_mstory3[0].unk_10, D_80115DB0_mstory3);
        }
        if (D_80115CB0_mstory3[2].unk_0C == 1 && Hu3DData[D_80115CB0_mstory3[2].obj->model[1]].motTime == 0.0f) {
            seNo = CharFXPlay((s16)D_80115CB0_mstory3[2].unk_10, 6);
            z = Hu3DData[D_80115CB0_mstory3[2].obj->model[1]].pos.z;
            if (z <= 0.0f) {
                vol = z / 15.0f + 127.0f;
            } else {
                vol = 127;
            }
            HuAudFXVolSet(seNo, vol);
        }
        if (D_80115CB0_mstory3[1].unk_0C == 1 && Hu3DData[D_80115CB0_mstory3[1].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)D_80115CB0_mstory3[1].unk_10, 7);
        }
        HuPrcVSleep();
    }
}

void func_8010D974_mstory3(void) {
}

void func_8010D97C_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0xA, 0, 0, -1, NULL);
    D_80115CB0_mstory3[10].obj = obj;
    D_80115CB0_mstory3[10].unk_08 = 0;
    D_80115CB0_mstory3[10].func = func_8010DA00_mstory3;
    omPrcSetDestructor(0, func_8010D974_mstory3);
    while (1) {
        D_80115CB0_mstory3[10].func(obj);
        HuPrcVSleep();
    }
}

const Vec D_80115740_mstory3 = { -100.0f, 0.0f, 350.0f };

const Vec D_8011574C_mstory3 = { -100.0f, 0.0f, 150.0f };

const Vec D_80115758_mstory3 = { 0.0f, 162.4f, 0.0f };

const Vec D_80115764_mstory3 = { 30.0f, -20.0f, 0.0f };

const Vec D_80115770_mstory3 = { 0.0f, 225.0f, 0.0f };

const Vec D_8011577C_mstory3 = { 0.0f, 0.0f, 0.0f };

const Vec D_80115788_mstory3 = { -5.0f, 300.0f, 0.0f };

const Vec D_80115794_mstory3 = { -30.0f, 260.0f, 0.0f };

const Vec D_801157A0_mstory3 = { 0.0f, 320.0f, 0.0f };

const Vec D_801157AC_mstory3 = { 0.0f, 0.0f, 0.0f };

const Vec D_801157B8_mstory3 = { 0.0f, -26.5f, 0.0f };

const Vec D_801157C4_mstory3 = { 0.0f, 0.0f, 0.0f };

const Vec D_801157D0_mstory3 = { 0.0f, 180.0f, 0.0f };

void func_8010DA00_mstory3(omObjData *obj) {
    s16 seNo;

    HuPrcSleep(30);
    CharFXPlay(0x26B, 7);
    D_80115CB0_mstory3[3].func = func_80111A58_mstory3;
    HuPrcSleep(70);
    D_80115CB0_mstory3[1].func = func_80110E30_mstory3;
    while (TRUE) {
        if (D_80115CB0_mstory3[3].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[3].unk_08 = 0;
    func_80106CF0_mstory3(D_80115CB0_mstory3[3].obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[1]);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A5A);
    func_8010606C_mstory3();
    func_80106CF0_mstory3(D_80115CB0_mstory3[3].obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[0]);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[1]].motId, 0, 10, 2);
    func_80107070_mstory3(D_80115CB0_mstory3[0].obj, &D_80115758_mstory3, 10);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[0]].motId, 0, 10, 0);
    func_80107070_mstory3(D_80115CB0_mstory3[4].obj, &D_80115764_mstory3, 10);
    func_80107070_mstory3(D_80115CB0_mstory3[3].obj, &D_80115770_mstory3, 10);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[4].obj->model[1], Hu3DData[D_80115CB0_mstory3[4].obj->motion[1]].motId, 0, 10, 2);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A5B);
    func_8010606C_mstory3();
    Hu3DMotionShiftSet(D_80115CB0_mstory3[4].obj->model[1], Hu3DData[D_80115CB0_mstory3[4].obj->motion[0]].motId, 0, 10, 2);
    func_80107070_mstory3(D_80115CB0_mstory3[4].obj, &D_8011577C_mstory3, 10);
    D_80115CB0_mstory3[8].func = func_80113E68_mstory3;
    func_80107070_mstory3(D_80115CB0_mstory3[3].obj, &D_80115788_mstory3, 10);
    while (TRUE) {
        if (D_80115CB0_mstory3[8].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[0].func = func_8010FDB0_mstory3;
    HuPrcSleep(40);
    func_80107070_mstory3(D_80115CB0_mstory3[3].obj, &D_80115794_mstory3, 50);
    func_80107070_mstory3(D_80115CB0_mstory3[3].obj, &D_801157A0_mstory3, 40);
    while (TRUE) {
        if (D_80115CB0_mstory3[0].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[0].unk_08 = 0;
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
    func_80107070_mstory3(D_80115CB0_mstory3[0].obj, &D_801157AC_mstory3, 10);
    HuAudSeqPlay(0x72);
    func_80106CF0_mstory3(D_80115CB0_mstory3[0].obj->model[1], D_80115DA2_mstory3, D_80115D98_mstory3[3]);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[7]].motId, 0, 10, 0);
    func_80107244_mstory3(D_80115CB0_mstory3[0].obj->model[1]);
    seNo = CharFXPlay(0x262, D_80115DB0_mstory3);
    HuPrcSleep(30);
    func_80107070_mstory3(D_80115CB0_mstory3[4].obj, &D_801157B8_mstory3, 3);
    func_80106DC4_mstory3(D_80115CB0_mstory3[4].obj, &D_80115740_mstory3, 5);
    HuAudFXPlay(0x219);
    HuAudFXStop(seNo);
    func_80106CF0_mstory3(D_80115CB0_mstory3[0].obj->model[1], D_80115DA2_mstory3, D_80115D98_mstory3[1]);
    func_8001C258_main(D_80115CB0_mstory3[0].obj->model[4], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[8]].motId, 0, 10, 0);
    func_80107070_mstory3(D_80115CB0_mstory3[4].obj, &D_801157C4_mstory3, 3);
    D_80115CB0_mstory3[4].unk_08 = 0;
    D_80115CB0_mstory3[3].func = func_80111B34_mstory3;
    func_80106DE0_mstory3(D_80115CB0_mstory3[4].obj, &D_8011574C_mstory3, 10, 0);
    func_80107244_mstory3(D_80115CB0_mstory3[0].obj->model[1]);
    HuAudSeqPlay(0x26);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[1]].motId, 0, 10, 2);
    func_80107070_mstory3(D_80115CB0_mstory3[0].obj, &D_801157D0_mstory3, 10);
    func_80106CF0_mstory3(D_80115CB0_mstory3[0].obj->model[1], D_80115DA2_mstory3, D_80115D98_mstory3[0]);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[8].func = func_801142C0_mstory3;
    Hu3DMotionShiftSet(D_80115CB0_mstory3[4].obj->model[1], Hu3DData[D_80115CB0_mstory3[4].obj->motion[1]].motId, 0, 10, 2);
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A5D);
    func_8010606C_mstory3();
    Hu3DMotionShiftSet(D_80115CB0_mstory3[4].obj->model[1], Hu3DData[D_80115CB0_mstory3[4].obj->motion[0]].motId, 0, 10, 2);
    while (TRUE) {
        if (D_80115CB0_mstory3[8].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[8].unk_08 = 0;
    Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[1]].motId, 0, 10, 2);
    func_80107070_mstory3(D_80115CB0_mstory3[0].obj, &D_8011577C_mstory3, 10);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[7]].motId, 0, 10, 0);
    func_80107244_mstory3(D_80115CB0_mstory3[0].obj->model[1]);
    D_80115CB0_mstory3[10].func = func_8010E170_mstory3;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010E170_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801157E8_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801157F4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B9A30", func_8010EBE4_mstory3);

void func_8010F658_mstory3(void) {
}

void func_8010F660_mstory3(void) {
    s32 motIds[8][4] = {
        { 0x3E, 0x40, 0x41, 0x43 },
        { 0x48, 0x4B, 0x4C, 0x4E },
        { 0x52, 0x54, 0x55, 0x57 },
        { 0x5B, 0x5D, 0x5E, 0x60 },
        { 0x65, 0x67, 0x68, 0x6A },
        { 0x6E, 0x70, 0x71, 0x73 },
        { 0x48, 0x4B, 0x4C, 0x4E },
        { 0x52, 0x54, 0x55, 0x57 },
    };
    omObjData *obj;
    s32 chr;
    void *data;

    obj = omAddObj(20, 20, 20, -1, NULL);
    D_80115CB0_mstory3[0].obj = obj;
    D_80115CB0_mstory3[0].unk_08 = 0;
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
    D_80115CB0_mstory3[0].unk_0C = 0;
    D_80115CB0_mstory3[0].unk_10 = 31;
    chr = D_80115DB0_mstory3;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 2));
    func_8000B460_main(obj, 3, motIds[chr][1] | 0x1D0000);
    func_8000B460_main(obj, 4, motIds[chr][0] | 0x1D0000);
    func_8000B460_main(obj, 5, motIds[chr][2] | 0x1D0000);
    func_8000B460_main(obj, 6, motIds[chr][3] | 0x1D0000);
    func_8000B460_main(obj, 7, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x21));
    func_8000B460_main(obj, 9, func_80017BB8_main(chr, 0x72));
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x6C));
    func_8000B460_main(obj, 11, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 12, func_80017BB8_main(chr, 0x9B));
    func_8000B460_main(obj, 13, func_80017BB8_main(chr, 0x9C));
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    if (D_80115DB0_mstory3 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    Hu3DModelPosSet(obj->model[1], -120.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -120.0f, -5.0f, 480.0f);
    Hu3DModelPosSet(obj->model[4], -120.0f, 0.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    data = DataRead(func_80017BB8_main(chr, 0xA4));
    D_80115D98_mstory3[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_801153E0_mstory3[chr]);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115D98_mstory3[0], 1, 0);
    Hu3DAnimBankSet(D_80115D98_mstory3[0], 0);
    D_80115DA2_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115D98_mstory3[0], 0, D_801153E0_mstory3[chr]);
    data = DataRead(func_80017BB8_main(chr, 0xA9));
    D_80115D98_mstory3[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115DA2_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115D98_mstory3[0], 0, D_801153E0_mstory3[chr]);
    data = DataRead(func_80017BB8_main(chr, 0xAA));
    D_80115D98_mstory3[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115DA2_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115D98_mstory3[0], 0, D_801153E0_mstory3[chr]);
    data = DataRead(func_80017BB8_main(chr, 0xA5));
    D_80115D98_mstory3[3] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115DA2_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115D98_mstory3[0], 0, D_801153E0_mstory3[chr]);
    data = DataRead(func_80017BB8_main(chr, 0xA6));
    D_80115D98_mstory3[4] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106CF0_mstory3(obj->model[1], D_80115DA2_mstory3, D_80115D98_mstory3[0]);
    omPrcSetDestructor(0, func_8010F658_mstory3);
    while (TRUE) {
        D_80115CB0_mstory3[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8010FCA4_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

void func_8010FD64_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_80107070_mstory3(obj, &D_801158E0_mstory3, 10);
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115880_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011588C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115898_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158A4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158B0_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158BC_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158C8_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158D4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801158E0_mstory3);

void func_8010FDB0_mstory3(omObjData *obj) {
    HmfMotionNode *node;
    s32 i;
    f32 scale;
    f32 time;

    HuPrcSleep(70);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[13]].motId, 0, 10, 2);
    func_80107218_mstory3(obj, 0.0f, 110.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    HuPrcSleep(10);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], obj->model[1], "item_hook");
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    func_80107244_mstory3(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    while (TRUE) {
        if (D_80115CB0_mstory3[8].unk_08 == 2) {
            break;
        }
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[8].unk_08 = 0;
    func_8001C258_main(D_80115CB0_mstory3[8].obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(D_80115CB0_mstory3[8].obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8002FD8C_main(obj->model[1], Hu3DData[obj->model[1]].motId, "item_hook", 27, 69);
    func_8002FD8C_main(obj->model[1], Hu3DData[obj->model[1]].motId, "item_hook", 27, 70);
    func_8002FD8C_main(obj->model[1], Hu3DData[obj->model[1]].motId, "item_hook", 27, 71);
    node = func_8001D33C_main(obj->model[1], "item_hook");
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
    func_8002FDCC_main(obj->model[1], Hu3DData[obj->model[1]].motId, "item_hook", 27, 71);
    func_8002FDCC_main(obj->model[1], Hu3DData[obj->model[1]].motId, "item_hook", 27, 70);
    func_8002FDCC_main(obj->model[1], Hu3DData[obj->model[1]].motId, "item_hook", 27, 69);
    func_80106400_mstory3(5);
    while (func_80106CDC_mstory3() != 1) {
        HuPrcVSleep();
    }
    func_8010603C_mstory3();
    func_80106090_mstory3(0x5A5C);
    func_8010606C_mstory3();
    func_8001C5B4_main(obj->model[1], obj->motion[4]);
    func_8001C814_main(obj->model[1], 4, 4);
    Hu3DMotionSpeedSet(obj->model[1], 2.0f);
    Hu3DMotionTimeSet(obj->model[1], D_800CCF58_main[Hu3DData[obj->model[1]].motId].unk02);
    do {
        time = Hu3DData[obj->model[1]].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    func_8001C5B4_main(obj->model[1], obj->motion[3]);
    func_8001C814_main(obj->model[1], 4, 4);
    Hu3DMotionTimeSet(obj->model[1], D_800CCF58_main[Hu3DData[obj->model[1]].motId].unk02);
    do {
        time = Hu3DData[obj->model[1]].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionSpeedSet(obj->model[1], 1.0f);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    HuAudSeqFadeOut(20);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    D_80115CB0_mstory3[0].unk_08 = 1;
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

void func_801103E8_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80107070_mstory3(obj, &D_80115908_mstory3, 5);
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

void func_80110474_mstory3(omObjData *obj) {
    D_80115CB0_mstory3[0].unk_0C = 1;
    D_80115CB0_mstory3[0].unk_10 = 31;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801074D8_mstory3(obj, 1.5f, 60);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[0].unk_0C = 0;
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

void func_80110558_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107070_mstory3(obj, &D_80115914_mstory3, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

void func_80110628_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, &D_80115920_mstory3, 5);
    D_80115CB0_mstory3[0].func = func_8011065C_mstory3;
}

void func_8011065C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_8011067C_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107070_mstory3(obj, &D_8011592C_mstory3, 10);
    D_80115CB0_mstory3[0].unk_0C = 1;
    D_80115CB0_mstory3[0].unk_10 = 31;
    func_801074D8_mstory3(obj, 6.0f, 30);
    D_80115CB0_mstory3[0].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[0].func = func_80110A84_mstory3;
}

void func_80110774_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[0].unk_08 == 1) {
        func_80106CF0_mstory3(obj->model[1], D_80115DA2_mstory3, D_80115DA0_mstory3);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        func_80107070_mstory3(obj, &D_80115944_mstory3, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        D_80115CB0_mstory3[0].unk_08 = 2;
        D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[0].unk_08 == 2) {
        func_80106CF0_mstory3(obj->model[1], D_80115DA2_mstory3, D_80115D9C_mstory3);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        func_80107070_mstory3(obj, &D_80115938_mstory3, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        D_80115CB0_mstory3[0].unk_08 = 3;
        D_80115CB0_mstory3[0].func = func_80110978_mstory3;
    } else if (D_80115CB0_mstory3[0].unk_08 == 3) {
        func_80107070_mstory3(obj, &D_80115944_mstory3, 10);
        D_80115CB0_mstory3[0].func = func_80110978_mstory3;
    }
}

void func_80110978_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80110998_mstory3(omObjData *obj) {
    HuPrcSleep(5);
    D_80115CB0_mstory3[0].unk_0C = 1;
    D_80115CB0_mstory3[0].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    func_8010733C_mstory3(obj, 20.0f, 15);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[0].unk_0C = 0;
    D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
}

void func_80110A84_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[0].unk_08 == 0) {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        func_80107070_mstory3(obj, &D_80115950_mstory3, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        D_80115CB0_mstory3[0].unk_08 = 1;
        D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[0].unk_08 == 1) {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        func_80107070_mstory3(obj, &D_8011595C_mstory3, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        D_80115CB0_mstory3[0].unk_08 = 2;
        D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[0].unk_08 == 2) {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
        func_80107070_mstory3(obj, &D_80115950_mstory3, 10);
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        D_80115CB0_mstory3[0].unk_08 = 0;
        D_80115CB0_mstory3[0].func = func_8010D774_mstory3;
    }
}

void func_80110CAC_mstory3(void) {
}

void func_80110CB4_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[1].obj = obj;
    D_80115CB0_mstory3[1].unk_08 = 0;
    D_80115CB0_mstory3[1].func = func_8010D774_mstory3;
    D_80115CB0_mstory3[1].unk_0C = 0;
    D_80115CB0_mstory3[1].unk_10 = 31;
    obj->model[1] = func_8000B108_main(0x90000, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8000B460_main(obj, 0, 0x90004);
    func_8000B460_main(obj, 1, 0x1D007A);
    func_8000B460_main(obj, 2, 0x1D0051);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 30, 2);
    Hu3DModelPosSet(obj->model[1], 150.0f, 0.0f, 384.0f);
    Hu3DModelPosSet(obj->model[2], 150.0f, -5.0f, 384.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    omPrcSetDestructor(0, func_80110CAC_mstory3);
    while (1) {
        D_80115CB0_mstory3[1].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115908_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115914_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115920_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011592C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115938_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115944_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115950_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011595C_mstory3);

const Vec D_80115974_mstory3 = { 200.0f, 0.0f, 1200.0f };

void func_80110E30_mstory3(omObjData *obj) {
    HuAudFXPlay(0x28E);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    D_80115CB0_mstory3[1].unk_0C = 1;
    D_80115CB0_mstory3[1].unk_10 = 40;
    func_80106DC4_mstory3(obj, &D_80115974_mstory3, 40);
    D_80115CB0_mstory3[1].unk_0C = 0;
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_80115CB0_mstory3[1].func = func_8010D774_mstory3;
}

void func_80110F04_mstory3(omObjData *obj) {
    Vec pos;

    pos.x = Hu3DData[D_80115CB0_mstory3[8].obj->model[2]].pos.x;
    pos.y = Hu3DData[D_80115CB0_mstory3[8].obj->model[2]].pos.y;
    pos.z = Hu3DData[D_80115CB0_mstory3[8].obj->model[2]].pos.z;
    pos.x += 0.5f;
    Hu3DModelPosSet(D_80115CB0_mstory3[8].obj->model[2], pos.x, pos.y, pos.z);
    func_8000CFA4_main(D_80115CB0_mstory3[8].obj->model[5], pos.x, pos.y - 40.0f, pos.z);
}

void func_80110FE8_mstory3(omObjData *obj) {
    omObjData *target = D_80115CB0_mstory3[2].obj;

    func_8001C258_main(target->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(target->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_801061C4_mstory3();
    HuPrcSleep(3);
    func_80106220_mstory3();
    D_80115CB0_mstory3[1].func = func_8010D774_mstory3;
}

const Vec D_80115980_mstory3 = { 138.0f, 100.0f, 214.0f };

void func_80111064_mstory3(void) {
    func_80106DE0_mstory3(D_80115CB0_mstory3[3].obj, &D_80115980_mstory3, 180, 0);
    D_80115CB0_mstory3[1].func = func_8010D774_mstory3;
}

void func_801110AC_mstory3(void) {
}

void func_801110B4_mstory3(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 20, 20, -1, NULL);
    D_80115CB0_mstory3[2].obj = obj;
    D_80115CB0_mstory3[2].unk_08 = 0;
    D_80115CB0_mstory3[2].func = func_8010D774_mstory3;
    D_80115CB0_mstory3[2].unk_0C = 0;
    D_80115CB0_mstory3[2].unk_10 = 31;
    obj->model[1] = func_8000B108_main(0x800A0, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8000B460_main(obj, 0, 0x80000);
    func_8000B460_main(obj, 1, 0x80001);
    func_8000B460_main(obj, 2, 0x80002);
    func_8000B460_main(obj, 3, 0x80005);
    func_8000B460_main(obj, 4, 0x8002F);
    func_8000B460_main(obj, 5, 0x80072);
    func_8000B460_main(obj, 6, 0x1D0075);
    func_8000B460_main(obj, 7, 0x80033);
    func_8000B460_main(obj, 8, 0x80003);
    func_8000B460_main(obj, 9, 0x80005);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 608.1f, -85.8f, -1390.3f);
    Hu3DModelPosSet(obj->model[2], 608.1f, -85.8f, -1390.3f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    data = DataRead(func_80017BB8_main(6, 0xA4));
    D_80115DA4_mstory3[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_8011588C_mstory3);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115DA4_mstory3[0], 1, 0);
    Hu3DAnimBankSet(D_80115DA4_mstory3[0], 0);
    D_80115DAE_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115DA4_mstory3[0], 0, D_8011588C_mstory3);
    data = DataRead(func_80017BB8_main(6, 0xA9));
    D_80115DA4_mstory3[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115DAE_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115DA4_mstory3[0], 0, D_8011588C_mstory3);
    data = DataRead(func_80017BB8_main(6, 0xAA));
    D_80115DA4_mstory3[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115DAE_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115DA4_mstory3[0], 0, D_8011588C_mstory3);
    data = DataRead(func_80017BB8_main(6, 0xA5));
    D_80115DA4_mstory3[3] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106CF0_mstory3(obj->model[1], D_80115DAE_mstory3, D_80115DA4_mstory3[0]);
    omPrcSetDestructor(0, func_801110AC_mstory3);
    while (TRUE) {
        D_80115CB0_mstory3[2].func(obj);
        HuPrcVSleep();
    }
}

void func_80111500_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(D_80115CB0_mstory3[2].obj->model[1], Hu3DData[D_80115CB0_mstory3[2].obj->motion[1]].motId, 0, 10,
                       2);
    func_80107070_mstory3(obj, &D_8011598C_mstory3, 10);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[2].obj->model[1], Hu3DData[D_80115CB0_mstory3[2].obj->motion[0]].motId, 0, 10,
                       2);
    D_80115CB0_mstory3[2].func = func_8010D774_mstory3;
}

void func_801115D8_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    D_80115CB0_mstory3[8].func = func_80114920_mstory3;
    Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[13]].motId, 0, 10, 2);
    Hu3DMotionSpeedSet(D_80115CB0_mstory3[0].obj->model[1], 0.5f);
    D_80115CB0_mstory3[2].unk_0C = 1;
    D_80115CB0_mstory3[2].unk_10 = 40;
    func_80106DC4_mstory3(obj, &D_80115998_mstory3, 60);
    D_80115CB0_mstory3[2].unk_0C = 0;
    Hu3DMotionSpeedSet(D_80115CB0_mstory3[0].obj->model[1], 1.0f);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[2].unk_08 = 1;
    D_80115CB0_mstory3[2].func = func_8010D774_mstory3;
}

void func_8011175C_mstory3(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_8011598C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115998_mstory3);

const char D_801159A4_mstory3[] = "c204n_0_DEF";

void func_80111764_mstory3(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    D_80115CB0_mstory3[3].obj = obj;
    D_80115CB0_mstory3[3].unk_08 = 0;
    D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 38.0f, 100.0f, 214.0f);
    Hu3DModelPosSet(obj->model[2], 38.0f, -5.0f, 214.0f);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    data = DataRead(0xA007E);
    D_80115D90_mstory3[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_801159A4_mstory3);
    HuMemMemoryFreePerm(data);
    D_80115D8E_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115D90_mstory3[0], 0, D_801159A4_mstory3);
    data = DataRead(0xA0080);
    D_80115D90_mstory3[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_80115D8E_mstory3 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115D90_mstory3[0], 0, D_801159A4_mstory3);
    data = DataRead(0xA0083);
    D_80115D90_mstory3[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115D90_mstory3[0], 1, 0);
    Hu3DAnimBankSet(D_80115D90_mstory3[0], 0);
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[0]);
    omPrcSetDestructor(0, func_8011175C_mstory3);
    while (TRUE) {
        D_80115CB0_mstory3[3].func(obj);
        HuPrcVSleep();
    }
}

const Vec D_801159B0_mstory3 = { 10.0f, 378.9f, 0.0f };

void func_80111A58_mstory3(omObjData *obj) {
    HuPrcSleep(60);
    D_80115CB0_mstory3[0].func = func_8010FCA4_mstory3;
    D_80115CB0_mstory3[4].func = func_801125C4_mstory3;
    func_80107070_mstory3(obj, &D_801159B0_mstory3, 30);
    func_80106DC4_mstory3(obj, &D_801159D4_mstory3, 20);
    HuPrcSleep(30);
    func_80107070_mstory3(obj, &D_801159BC_mstory3, 10);
    func_80106DC4_mstory3(obj, &D_801159E0_mstory3, 15);
    D_80115CB0_mstory3[0].func = func_8010FD64_mstory3;
    func_80107070_mstory3(obj, &D_801159C8_mstory3, 10);
    D_80115CB0_mstory3[3].unk_08 = 1;
    D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159BC_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159C8_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159D4_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159E0_mstory3);

void func_80111B34_mstory3(omObjData *obj) {
    f32 baseY = Hu3DData[obj->model[1]].pos.y;
    f32 ofs;
    s16 i;

    for (i = 0; i < 12; i++) {
        ofs = sindf(i * 15.0) * 80.0f;
        Hu3DData[obj->model[1]].pos.y = baseY + ofs;
        HuPrcVSleep();
    }
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[2]);
    D_80115CB0_mstory3[3].unk_08 = 1;
    D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
}

void func_80111C50_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[0]);
    func_80107070_mstory3(obj, &D_801159F8_mstory3, 5);
    D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_801159F8_mstory3);

void func_80111CB8_mstory3(omObjData *obj) {
    f32 baseY = Hu3DData[obj->model[1]].pos.y;
    f32 ofs;
    s16 i;

    for (i = 0; i < 10; i++) {
        ofs = sindf(i * 15.0) * 100.0f;
        Hu3DData[obj->model[1]].pos.y = baseY + ofs;
        HuPrcVSleep();
    }
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[2]);
    D_80115CB0_mstory3[0].func = func_80110558_mstory3;
    D_80115CB0_mstory3[4].func = func_8011268C_mstory3;
    D_80115CB0_mstory3[5].func = func_80112EF0_mstory3;
    D_80115CB0_mstory3[3].unk_08 = 1;
    D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
}

void func_80111DF8_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, &D_80115A10_mstory3, 5);
    D_80115CB0_mstory3[3].func = func_80111E2C_mstory3;
}

void func_80111E2C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80111E4C_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[3].unk_08 == 1) {
        func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[0]);
        func_80107070_mstory3(obj, &D_80115A1C_mstory3, 10);
        D_80115CB0_mstory3[3].unk_08 = 2;
        D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[3].unk_08 == 2) {
        func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[1]);
        func_80107070_mstory3(obj, &D_80115A28_mstory3, 10);
        D_80115CB0_mstory3[3].unk_08 = 3;
        D_80115CB0_mstory3[3].func = func_80111F3C_mstory3;
    } else if (D_80115CB0_mstory3[3].unk_08 == 3) {
        func_80107070_mstory3(obj, &D_80115A1C_mstory3, 10);
        D_80115CB0_mstory3[3].func = func_80111F3C_mstory3;
    }
}

void func_80111F3C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80111F5C_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_8010733C_mstory3(obj, 20.0f, 60);
    D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
}

void func_80111FA4_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[3].unk_08 == 0) {
        func_80107070_mstory3(obj, &D_80115A34_mstory3, 10);
        D_80115CB0_mstory3[3].unk_08 = 1;
        D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[3].unk_08 == 1) {
        func_80107070_mstory3(obj, &D_80115A40_mstory3, 10);
        D_80115CB0_mstory3[3].unk_08 = 2;
        D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[3].unk_08 == 2) {
        func_80107070_mstory3(obj, &D_80115A34_mstory3, 10);
        D_80115CB0_mstory3[3].unk_08 = 0;
        D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
    }
}

void func_8011204C_mstory3(omObjData *obj) {
    f32 rotY;
    f32 ofs;
    s16 i;

    if (D_80115CB0_mstory3[3].unk_08 == 0) {
        HuPrcSleep(30);
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 10; i++) {
        ofs = sindf(i * 9.0f) * 120.0f;
        Hu3DData[obj->model[1]].rot.y = rotY + ofs;
        HuPrcVSleep();
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 15; i++) {
        ofs = sindf(i * 4.5f) * 240.0f;
        Hu3DData[obj->model[1]].rot.y = rotY - ofs;
        HuPrcVSleep();
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 10; i++) {
        ofs = sindf(i * 9.0f) * 120.0f;
        Hu3DData[obj->model[1]].rot.y = rotY + ofs;
        HuPrcVSleep();
    }
    if (D_80115CB0_mstory3[3].unk_08 == 0) {
        D_80115CB0_mstory3[3].unk_08 = 0;
        D_80115CB0_mstory3[3].func = func_80111CB8_mstory3;
    } else {
        D_80115CB0_mstory3[3].unk_08 = 0;
        D_80115CB0_mstory3[3].func = func_8010D774_mstory3;
    }
}

void func_801122BC_mstory3(void) {
}

void func_801122C4_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[4].obj = obj;
    D_80115CB0_mstory3[4].unk_08 = 0;
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    func_8000B460_main(obj, 3, 0xA0129);
    func_8000B460_main(obj, 4, 0xA012A);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 0.0f, 200.0f, 150.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, -5.0f, 150.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    omPrcSetDestructor(0, func_801122BC_mstory3);
    while (1) {
        D_80115CB0_mstory3[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8011249C_mstory3(void) {
    f32 angle = 0.0f;
    omObjData *obj = D_80115CB0_mstory3[4].obj;
    Vec pos;
    f32 ofs;

    pos.y = Hu3DData[obj->model[1]].pos.y;
    while (TRUE) {
        pos.x = Hu3DData[obj->model[1]].pos.x;
        pos.z = Hu3DData[obj->model[1]].pos.z;
        ofs = sindf(angle) * 25.0f + 25.0f;
        angle += 2.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        Hu3DModelPosSet(obj->model[1], pos.x, ofs + pos.y, pos.z);
        HuPrcVSleep();
    }
}

void func_801125C4_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, &D_80115A4C_mstory3, 20);
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
}

void func_801125F8_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_80107070_mstory3(obj, &D_80115A58_mstory3, 5);
    D_80115CB0_mstory3[8].unk_08 = 2;
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
}

void func_80112650_mstory3(omObjData *obj) {
    func_801074D8_mstory3(obj, 2.0f, 60);
    D_80115CB0_mstory3[4].unk_08 = 1;
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
}

void func_8011268C_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_80107070_mstory3(obj, &D_80115A64_mstory3, 10);
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
}

void func_801126D8_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, &D_80115A70_mstory3, 5);
    D_80115CB0_mstory3[4].func = func_8011270C_mstory3;
}

void func_8011270C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_8011272C_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[4].unk_08 == 1) {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
        func_80107070_mstory3(obj, &D_80115A7C_mstory3, 10);
        D_80115CB0_mstory3[4].unk_08 = 2;
        D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[4].unk_08 == 2) {
        func_80107070_mstory3(obj, &D_80115A88_mstory3, 10);
        D_80115CB0_mstory3[4].unk_08 = 3;
        D_80115CB0_mstory3[4].func = func_80112834_mstory3;
    } else if (D_80115CB0_mstory3[4].unk_08 == 3) {
        func_80107070_mstory3(obj, &D_80115A7C_mstory3, 10);
        D_80115CB0_mstory3[4].func = func_80112834_mstory3;
    }
}

void func_80112834_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80112854_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    func_8010733C_mstory3(obj, 20.0f, 60);
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
}

void func_8011289C_mstory3(omObjData *obj) {
    if (D_80115CB0_mstory3[4].unk_08 == 0) {
        func_80107070_mstory3(obj, &D_80115A94_mstory3, 10);
        D_80115CB0_mstory3[4].unk_08 = 1;
        D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[4].unk_08 == 1) {
        func_80107070_mstory3(obj, &D_80115AA0_mstory3, 10);
        D_80115CB0_mstory3[4].unk_08 = 2;
        D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
    } else if (D_80115CB0_mstory3[4].unk_08 == 2) {
        func_80107070_mstory3(obj, &D_80115A94_mstory3, 10);
        D_80115CB0_mstory3[4].unk_08 = 0;
        D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
    }
}

void func_80112944_mstory3(omObjData *obj) {
    f32 rotY;
    f32 ofs;
    s16 i;

    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 15; i++) {
        ofs = sindf(i * 6.0f) * 30.0f;
        Hu3DData[obj->model[1]].rot.y = rotY + ofs;
        HuPrcVSleep();
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 30; i++) {
        ofs = sindf(i * 3.0f) * 60.0f;
        Hu3DData[obj->model[1]].rot.y = rotY - ofs;
        HuPrcVSleep();
    }
    rotY = Hu3DData[obj->model[1]].rot.y;
    for (i = 0; i < 15; i++) {
        ofs = sindf(i * 6.0f) * 30.0f;
        Hu3DData[obj->model[1]].rot.y = rotY + ofs;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[4].func = func_8010D774_mstory3;
}

void func_80112B80_mstory3(void) {
}

void func_80112B88_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    D_80115CB0_mstory3[5].obj = obj;
    D_80115CB0_mstory3[5].unk_08 = 0;
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8000B460_main(obj, 3, 0x1D0032);
    func_8000B460_main(obj, 4, 0x1D0034);
    func_8000B460_main(obj, 5, 0x1D0033);
    func_8000B460_main(obj, 6, 0x1D0035);
    func_8000B460_main(obj, 7, 0xA0038);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], -700.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -700.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 270.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    omPrcSetDestructor(0, func_80112B80_mstory3);
    while (1) {
        D_80115CB0_mstory3[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A10_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A1C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A28_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A34_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A40_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A4C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A58_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A64_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A70_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A7C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A88_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115A94_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115AA0_mstory3);

const Vec D_80115AAC_mstory3 = { -350.0f, 0.0f, 480.0f };
// Unreferenced zero-filled rodata.
const Vec D_80115AB8_mstory3[9] = { 0 };

void func_80112DA0_mstory3(omObjData *obj) {
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    D_80115CB0_mstory3[0].func = func_80110474_mstory3;
    D_80115CB0_mstory3[4].func = func_80112650_mstory3;
    D_80115CB0_mstory3[1].func = func_80110F04_mstory3;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106DC4_mstory3(obj, &D_80115AAC_mstory3, 60);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (TRUE) {
        if (D_80115CB0_mstory3[4].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[4].unk_08 = 0;
    D_80115CB0_mstory3[1].func = func_8010D774_mstory3;
    D_80115CB0_mstory3[5].unk_08 = 1;
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
}

void func_80112EF0_mstory3(omObjData *obj) {
    HuPrcSleep(10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80107070_mstory3(obj, &D_80115B24_mstory3, 10);
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
}

void func_80112F7C_mstory3(omObjData *obj) {
    func_80107070_mstory3(obj, &D_80115B30_mstory3, 5);
    D_80115CB0_mstory3[5].func = func_80112FB0_mstory3;
}

void func_80112FB0_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115CB0_mstory3[2].obj);
}

void func_80112FD0_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106DC4_mstory3(obj, &D_80115B3C_mstory3, 60);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[5].unk_08 = 1;
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
}

void func_801130A4_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_80107244_mstory3(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
}

void func_8011315C_mstory3(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106DC4_mstory3(obj, &D_80115B48_mstory3, 30);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[5].obj->model[1], Hu3DData[D_80115CB0_mstory3[5].obj->motion[2]].motId, 0, 10,
                       2);
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
}

void func_8011322C_mstory3(omObjData *obj) {
    f32 t;
    s16 i;

    D_80115CB0_mstory3[9].func = func_8010D774_mstory3;
    Hu3DData[D_80115CB0_mstory3[5].obj->model[2]].pos.x = Hu3DData[D_80115CB0_mstory3[5].obj->model[1]].pos.x = -380.0f;
    Hu3DMotionShiftSet(D_80115CB0_mstory3[5].obj->model[1], Hu3DData[D_80115CB0_mstory3[5].obj->motion[5]].motId, 0, 10, 2);
    Hu3DData[D_80115CB0_mstory3[2].obj->model[1]].pos.x = Hu3DData[D_80115CB0_mstory3[2].obj->model[2]].pos.x = 100.0f;
    func_8001C5B4_main(D_80115CB0_mstory3[2].obj->model[1], D_80115CB0_mstory3[2].obj->motion[3]);
    Hu3DMotionSpeedSet(D_80115CB0_mstory3[2].obj->model[1], 0.0f);
    Hu3DMotionTimeSet(D_80115CB0_mstory3[2].obj->model[1], 19.0f);
    HuAudFXPlay(0x29D);
    for (i = 0; i < 30; i++) {
        t = i * 3.0f;
        Hu3DData[D_80115CB0_mstory3[5].obj->model[1]].pos.x = sindf(t) * -300.0f + -80.0f;
        Hu3DData[D_80115CB0_mstory3[5].obj->model[2]].pos.x = sindf(t) * -175.0f + -80.0f;
        Hu3DData[D_80115CB0_mstory3[5].obj->model[2]].scale.x = Hu3DData[D_80115CB0_mstory3[5].obj->model[2]].scale.z = 5.0f;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[9].func = func_80114EF8_mstory3;
    D_80115CB0_mstory3[5].func = func_8010D774_mstory3;
}

void func_801134D8_mstory3(void) {
}

void func_801134E0_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[6].obj = obj;
    D_80115CB0_mstory3[6].unk_08 = 0;
    D_80115CB0_mstory3[6].func = func_8010D774_mstory3;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F1);
    func_8000B460_main(obj, 2, 0x1D0039);
    func_8000B460_main(obj, 3, 0x1D003A);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], 500.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], 500.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 270.0f, 0.0f);
    omPrcSetDestructor(0, func_801134D8_mstory3);
    while (1) {
        D_80115CB0_mstory3[6].func(obj);
        HuPrcVSleep();
    }
}

void func_80113668_mstory3(omObjData *obj) {
    func_80106DC4_mstory3(obj, &D_80115B54_mstory3, 60);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[6].func = func_8010D774_mstory3;
}

void func_801136E8_mstory3(omObjData *obj) {
    s16 i;
    f32 y;

    Hu3DMotionShiftSet(obj->model[1], Hu3DData[D_80115CB0_mstory3[6].obj->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(10);
    for (i = 0; i < 10; i++) {
        y = sindf(i * 9.0f) * 100.0f;
        Hu3DData[D_80115CB0_mstory3[5].obj->model[1]].pos.y = y;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[6].unk_08 = 1;
    D_80115CB0_mstory3[6].func = func_8010D774_mstory3;
}

void func_80113800_mstory3(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[D_80115CB0_mstory3[6].obj->motion[3]].motId, 0, 0xA, 2);
    HuPrcSleep(0xA);
    D_80115CB0_mstory3[6].func = func_80113874_mstory3;
}

void func_80113874_mstory3(omObjData *obj) {
    omObjData *obj6 = D_80115CB0_mstory3[6].obj;
    omObjData *obj7 = D_80115CB0_mstory3[7].obj;
    omObjData *obj5 = D_80115CB0_mstory3[5].obj;

    Hu3DData[obj6->model[2]].pos.x = Hu3DData[obj6->model[1]].pos.x += 10.0f;
    Hu3DData[obj7->model[2]].pos.x = Hu3DData[obj7->model[1]].pos.x += 10.0f;
    Hu3DData[obj5->model[1]].pos.x += 10.0f;
    Hu3DData[obj5->model[2]].pos.x += 10.0f;
}

void func_80113960_mstory3(void) {
}

void func_80113968_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[7].obj = obj;
    D_80115CB0_mstory3[7].unk_08 = 0;
    D_80115CB0_mstory3[7].func = func_8010D774_mstory3;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115D8C_mstory3);
    Hu3DModelPosSet(obj->model[1], 500.0f, 0.0f, 700.0f);
    Hu3DModelPosSet(obj->model[2], 500.0f, -5.0f, 700.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 270.0f, 0.0f);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[D_80115CB0_mstory3[6].obj->motion[1]].motId, 0, 10, 2);
    omPrcSetDestructor(0, func_80113960_mstory3);
    while (1) {
        D_80115CB0_mstory3[7].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B24_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B30_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B3C_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B48_mstory3);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory3/4B9A30", D_80115B54_mstory3);

const Vec D_80115B60_mstory3 = { -400.0f, 0.0f, 700.0f };

void func_80113AA8_mstory3(omObjData *obj) {
    func_80106DC4_mstory3(obj, &D_80115B60_mstory3, 60);
    Hu3DModelPosSet(obj->model[1], -500.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -500.0f, 0.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115CB0_mstory3[7].unk_08 = 1;
    D_80115CB0_mstory3[7].func = func_8010D774_mstory3;
}

void func_80113B3C_mstory3(omObjData *arg0) {
    Hu3DMotionShiftSet(arg0->model[1], Hu3DData[D_80115CB0_mstory3[6].obj->motion[3]].motId, 0, 0xA, 2);
    D_80115CB0_mstory3[7].func = func_8010D774_mstory3;
}

void func_80113BA8_mstory3(void) {
}

void func_80113BB0_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    D_80115CB0_mstory3[8].obj = obj;
    D_80115CB0_mstory3[8].unk_08 = 0;
    D_80115CB0_mstory3[8].func = func_8010D774_mstory3;
    obj->model[1] = func_8000B108_main(0x1D0008, 0x20299);
    obj->model[2] = func_8000B108_main(0x1D0009, 0x20299);
    obj->model[4] = func_8000B108_main(0x1D0013, 0x2B9);
    obj->model[6] = func_8000B108_main(0x83, 0x2B9);
    obj->model[7] = Hu3DModelLink(D_80115D8C_mstory3);
    func_8001C258_main(obj->model[6], 4, 4);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C814_main(obj->model[2], 2, 2);
    Hu3DModelPosSet(obj->model[1], 0.0f, 200.0f, 100.0f);
    Hu3DModelPosSet(obj->model[2], 0.0f, 200.0f, 100.0f);
    Hu3DModelPosSet(obj->model[4], 750.0f, 100.0f, -1500.3f);
    Hu3DModelPosSet(obj->model[6], -150.0f, 270.0f, 300.0f);
    Hu3DModelPosSet(obj->model[7], 750.0f, 0.0f, -1500.3f);
    obj->model[3] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(obj->model[3], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[3], 60.0f);
    func_800138EC_main(obj->model[3], 1, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    obj->model[5] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(obj->model[5], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[5], 60.0f);
    func_800138EC_main(obj->model[5], 1, 0);
    func_8001C258_main(obj->model[5], 4, 4);
    omPrcSetDestructor(0, func_80113BA8_mstory3);
    while (TRUE) {
        D_80115CB0_mstory3[8].func(obj);
        HuPrcVSleep();
    }
}

void func_80113E68_mstory3(omObjData *obj) {
    Vec pos;
    MstoryPath *path[2];
    s16 i;

    path[0] = func_8010C9F0_mstory3(D_80115400_mstory3, 0);
    path[1] = func_8010C9F0_mstory3(D_80115430_mstory3, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[3], 4, 0);
    func_800138EC_main(obj->model[3], 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        if (i == 20) {
            Hu3DMotionShiftSet(D_80115CB0_mstory3[0].obj->model[1], Hu3DData[D_80115CB0_mstory3[0].obj->motion[12]].motId, 0, 10, 2);
        }
        func_8010CCF4_mstory3(path[0], (i * (1.0f / 50.0f)) * (i * (1.0f / 50.0f)), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115CB0_mstory3[8].obj->model[3], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[4].obj->model[1], Hu3DData[D_80115CB0_mstory3[4].obj->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(20);
    D_80115CB0_mstory3[8].unk_08 = 1;
    Hu3DMotionShiftSet(D_80115CB0_mstory3[4].obj->model[1], Hu3DData[D_80115CB0_mstory3[4].obj->motion[0]].motId, 0, 10, 0);
    HuAudFXPlay(0x218);
    for (i = 0; i < 120; i++) {
        func_8010CCF4_mstory3(path[1], (i * (1.0f / 120.0f)) * (i * (1.0f / 120.0f)), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115CB0_mstory3[8].obj->model[3], pos.x, pos.y - 40.0f, pos.z);
        Hu3DData[obj->model[1]].rot.y += 24.0f;
        if (Hu3DData[obj->model[1]].rot.y >= 360.0f) {
            Hu3DData[obj->model[1]].rot.y -= 360.0f;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(0x21A);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    func_800138EC_main(obj->model[3], 1, 0);
    func_8010D59C_mstory3(path[0]);
    func_8010D59C_mstory3(path[1]);
    D_80115CB0_mstory3[8].unk_08 = 2;
    D_80115CB0_mstory3[8].func = func_8010D774_mstory3;
}

void func_80114260_mstory3(void) {
    func_80107674_mstory3(D_80115CB0_mstory3[5].obj, D_80115CB0_mstory3[0].obj);
    func_80107674_mstory3(D_80115CB0_mstory3[0].obj, D_80115CB0_mstory3[5].obj);
    func_80107674_mstory3(D_80115CB0_mstory3[4].obj, D_80115CB0_mstory3[5].obj);
    func_80107674_mstory3(D_80115CB0_mstory3[3].obj, D_80115CB0_mstory3[5].obj);
}

void func_801142C0_mstory3(omObjData *obj) {
    MstoryPath *path;
    Vec pos;
    s16 i;

    path = func_8010C9F0_mstory3(D_80115478_mstory3, 0);
    Hu3DModelPosSet(obj->model[2], -100.0f, 200.0f, 100.0f);
    func_8000CFA4_main(obj->model[5], -100.0f, 200.0f, 100.0f);
    func_8001C258_main(obj->model[2], 4, 0);
    func_8001C258_main(obj->model[5], 4, 0);
    func_800138EC_main(obj->model[5], 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 30; i++) {
        func_8010CCF4_mstory3(path, (i * (1.0f / 30.0f)) * (i * (1.0f / 30.0f)), &pos);
        pos.x -= 100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115CB0_mstory3[8].obj->model[5], pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8010D59C_mstory3(path);
    D_80115CB0_mstory3[8].unk_08 = 1;
    D_80115CB0_mstory3[8].func = func_8010D774_mstory3;
}

void func_80114474_mstory3(omObjData *obj) {
    omObjData *other = D_80115CB0_mstory3[2].obj;
    MstoryPath *path;
    Vec pos;
    s16 i;

    path = func_8010C9F0_mstory3(D_801154A8_mstory3, 0);
    func_8001C258_main(obj->model[6], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_8001C258_main(obj->model[5], 4, 0);
    func_800138EC_main(obj->model[5], 1, 1);
    HuAudFXPlay(0x21F);
    for (i = 0; i < 30; i++) {
        func_8010CCF4_mstory3(path, i * (1.0f / 30.0f), &pos);
        pos.x -= 100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115CB0_mstory3[8].obj->model[5], pos.x, pos.y - 40.0f, pos.z);
        if (i == 25) {
            D_80115CB0_mstory3[1].func = func_80110FE8_mstory3;
        }
        HuPrcVSleep();
    }
    func_8010D59C_mstory3(path);
    func_8001C258_main(obj->model[5], 4, 4);
    func_800138EC_main(obj->model[3], 1, 0);
    Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[4]].pos.x;
    Hu3DData[obj->model[2]].pos.y = Hu3DData[obj->model[4]].pos.y;
    Hu3DData[obj->model[2]].pos.z = Hu3DData[obj->model[4]].pos.z;
    Hu3DData[obj->model[2]].rot.y = 0.0f;
    D_80115D96_mstory3 = 1;
    func_8001C258_main(other->model[1], 4, 4);
    func_8001C258_main(other->model[2], 4, 4);
    D_80115CB0_mstory3[8].func = func_8010D774_mstory3;
}

void func_8011475C_mstory3(omObjData *obj) {
    Vec pos;
    s16 i;

    pos.x = Hu3DData[obj->model[4]].pos.x;
    pos.y = Hu3DData[obj->model[4]].pos.y;
    pos.z = Hu3DData[obj->model[4]].pos.z;
    for (i = 0; i < 50; i++) {
        pos.x -= 3.5;
        pos.y += 1.75;
        pos.z += 19.25;
        Hu3DData[obj->model[2]].pos.z = Hu3DData[obj->model[4]].pos.z = pos.z;
        Hu3DData[obj->model[2]].pos.y = Hu3DData[obj->model[4]].pos.y = pos.y;
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[4]].pos.x = pos.x;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[8].func = func_8010D774_mstory3;
}

void func_80114920_mstory3(omObjData *obj) {
    s16 i;

    for (i = 0; i < 60; i++) {
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[4]].pos.x += 15.0f;
        HuPrcVSleep();
    }
    D_80115CB0_mstory3[8].func = func_8010D774_mstory3;
}

void func_801149D0_mstory3(void) {
    while (TRUE) {
        if (D_80115D96_mstory3 == 1) {
            Hu3DData[D_80115CB0_mstory3[8].obj->model[2]].rot.y += 12.0f;
            Hu3DData[D_80115CB0_mstory3[8].obj->model[7]].pos.x = Hu3DData[D_80115CB0_mstory3[8].obj->model[4]].pos.x;
            Hu3DData[D_80115CB0_mstory3[8].obj->model[7]].pos.y = -85.8f;
            Hu3DData[D_80115CB0_mstory3[8].obj->model[7]].pos.z = Hu3DData[D_80115CB0_mstory3[8].obj->model[4]].pos.z;
        }
        HuPrcVSleep();
    }
}

void func_80114AF8_mstory3(void) {
}

void func_80114B00_mstory3(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0x14, 0x14, -1, NULL);
    D_80115CB0_mstory3[9].obj = obj;
    D_80115CB0_mstory3[9].unk_08 = 0;
    D_80115CB0_mstory3[9].func = func_8010D774_mstory3;
    obj->model[1] = func_8000B108_main(0x1D0030, 0x2A8);
    obj->model[2] = func_8000B108_main(0x83, 0x2B9);
    obj->model[3] = func_8000B108_main(0x83, 0x2B9);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8001FA68_main(obj->model[1]);
    func_8001F9E4_main(obj->model[1], 255);
    Hu3DModelPosSet(obj->model[1], 0.0f, -25.0f, 800.0f);
    Hu3DModelScaleSet(obj->model[1], 0.0f, 0.0f, 1.0f);
    func_8000B460_main(obj, 0, 0x1D0030);
    func_8000B460_main(obj, 1, 0x83);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    omPrcSetDestructor(0, func_80114AF8_mstory3);
    while (1) {
        D_80115CB0_mstory3[9].func(obj);
        HuPrcVSleep();
    }
}

void func_80114CD8_mstory3(omObjData *obj) {
    s16 i;
    f32 scale;

    HuPrcSleep(10);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_8001C258_main(obj->model[3], 4, 0);
    func_8001C258_main(obj->model[4], 4, 0);
    HuAudFXPlay(0x220);
    for (i = 0; i < 10; i++) {
        scale = sindf(i * 9.0f) * 2.0f;
        Hu3DModelScaleSet(obj->model[1], scale, scale, 1.0f);
        HuPrcVSleep();
    }
    Hu3DData[D_80115CB0_mstory3[2].obj->model[1]].pos.x = Hu3DData[D_80115CB0_mstory3[2].obj->model[2]].pos.x = 100.0f;
    Hu3DData[D_80115CB0_mstory3[3].obj->model[1]].rot.y = 0.0f;
    Hu3DData[D_80115CB0_mstory3[4].obj->model[1]].rot.y = 0.0f;
    Hu3DData[D_80115CB0_mstory3[0].obj->model[1]].rot.y = 0.0f;
    Hu3DMotionShiftSet(D_80115CB0_mstory3[4].obj->model[1], Hu3DData[D_80115CB0_mstory3[4].obj->motion[4]].motId, 0, 10, 2);
    func_80106CF0_mstory3(obj->model[1], D_80115D8E_mstory3, D_80115D90_mstory3[2]);
    D_80115CB0_mstory3[9].func = func_80114FA4_mstory3;
}

void func_80114EF8_mstory3(omObjData *obj) {
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    HuPrcSleep(30);
    Hu3DMotionSpeedSet(D_80115CB0_mstory3[2].obj->model[1], 1.0f);
    Hu3DMotionShiftSet(D_80115CB0_mstory3[2].obj->model[1], Hu3DData[D_80115CB0_mstory3[2].obj->motion[0]].motId, 0, 10, 2);
    D_80115CB0_mstory3[9].unk_08 = 1;
    D_80115CB0_mstory3[9].func = func_8010D774_mstory3;
}

void func_80114FA4_mstory3(omObjData *obj) {
    f32 angle;
    s16 i;

    for (i = 2; i < 5; i++) {
        if (D_80115C9C_mstory3[i] == 0) {
            if ((u8)(rand8() % 7) == 0) {
                angle = (u8)(rand8() % 200) - 10.0f;
                Hu3DModelPosSet(obj->model[i], cosdf(angle) * 175.0f, sindf(angle) * 175.0f, 500.0f);
                func_8001C5B4_main(obj->model[i], obj->motion[1]);
                D_80115C9C_mstory3[i] = 1;
                D_80115CA2_mstory3[i] = 10;
            }
        } else if (--D_80115CA2_mstory3[i] <= 0) {
            D_80115C9C_mstory3[i] = 0;
        }
    }
}

void func_8011517C_mstory3(omObjData *obj) {
    do {
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[8 + (rand8() & 1)]].motId, 0, 10, 0);
        func_80107244_mstory3(obj->model[1]);
        HuPrcVSleep();
    } while (D_80115CB0_mstory3[2].unk_08 != 1);
    D_80115CB0_mstory3[2].func = func_8011522C_mstory3;
}

void func_8011522C_mstory3(omObjData *obj) {
    D_80115CB0_mstory3[5].func = func_8011322C_mstory3;
    D_80115CB0_mstory3[2].func = func_8010D774_mstory3;
    D_80115CB0_mstory3[2].unk_08 = 0;
}
