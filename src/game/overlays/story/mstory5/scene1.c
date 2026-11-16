#include "common.h"
#include "game/hmfmath.h"
#include "mstory5.h"

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern const Vec D_80114948_mstory5;
extern const Vec D_80114A88_mstory5;
extern const Vec D_80114C44_mstory5;
extern const Vec D_80114C84_mstory5;
extern const Vec D_80114C90_mstory5;
extern const Vec D_80114A0C_mstory5;
extern const Vec D_80114A18_mstory5;
extern void (*const D_801148A0_mstory5[])(void);
extern UnkStoryObj D_801151F0_mstory5[9];
extern UnkStoryObj D_801152C8_mstory5;
extern UnkStoryObj D_801152E0_mstory5;
extern Vec D_80115340_mstory5;
extern s16 D_80115364_mstory5;
extern Vec D_80115328_mstory5;
extern const Vec D_80114930_mstory5;
extern s16 D_80115368_mstory5;
extern s16 D_80115372_mstory5;
extern s32 D_80115370_mstory5[4];
extern Vec D_80115304_mstory5;
extern const Vec D_8011490C_mstory5;
extern s16 D_8011537A_mstory5;
extern s16 D_80115380_mstory5;
extern s16 D_80115384_mstory5;
extern s16 D_8011538A_mstory5[4];
extern s16 D_80115382_mstory5[4];
extern Vec D_8011531C_mstory5;
extern const Vec D_80114924_mstory5;
extern const Vec D_80114C9C_mstory5;
extern const Vec D_80114CA8_mstory5;
extern Vec D_80115358_mstory5;
extern const Vec D_80114960_mstory5;
extern const s32 D_80114C78_mstory5[];
extern s16 D_80115366_mstory5;
extern Vec D_80115310_mstory5;
extern const Vec D_80114918_mstory5;
extern Vec D_80115334_mstory5;
extern const Vec D_8011493C_mstory5;
extern const Vec D_80114AB8_mstory5;
extern const Vec D_80114AD0_mstory5;
extern const Vec D_80114ADC_mstory5;
extern const Vec D_80114AE8_mstory5;
extern const Vec D_80114AF4_mstory5;
extern const Vec D_80114B00_mstory5;
extern const Vec D_80114B0C_mstory5;
extern const Vec D_80114B18_mstory5;
extern const Vec D_80114B24_mstory5;
extern s16 D_80115376_mstory5;
extern const Vec D_80114AA0_mstory5;
extern const Vec D_80114B54_mstory5;
extern const Vec D_80114B60_mstory5;
extern const Vec D_80114B9C_mstory5;
extern const Vec D_80114BA8_mstory5;
extern const Vec D_80114BB4_mstory5;
extern const Vec D_80114BCC_mstory5;
extern const Vec D_80114BD8_mstory5;
extern const Vec D_80114BE4_mstory5;
extern const Vec D_80114BF0_mstory5;
extern s16 D_8011537E_mstory5;
extern s32 omCharModelNoTbl[][6];
extern Vec D_801152F8_mstory5;
extern Vec D_8011534C_mstory5;
extern const Vec D_80114954_mstory5;
extern const Vec D_80114900_mstory5;
extern const s32 D_8011496C_mstory5[];
extern const s32 D_8011498C_mstory5[];
extern const s32 D_801149AC_mstory5[];
extern const s32 D_801149CC_mstory5[];
extern const s32 D_801149EC_mstory5[];

s16 D_80114770_mstory5 = 0;
s32 D_80114774_mstory5 = 0;
Vec D_80114778_mstory5[4] = {
    { 0.0f, 200.0f, 100.0f },
    { -200.0f, 100.0f, -100.0f },
    { -100.0f, 300.0f, 300.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec D_801147A8_mstory5[6] = {
    { -100.0f, 300.0f, 300.0f },
    { -200.0f, 200.0f, 100.0f },
    { 0.0f, 300.0f, -100.0f },
    { 400.0f, 400.0f, 200.0f },
    { -50.0f, 120.0f, 450.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec D_801147F0_mstory5[4] = {
    { 100.0f, 200.0f, 100.0f },
    { -100.0f, 100.0f, -100.0f },
    { 0.0f, 300.0f, 300.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};

void func_80106B64_mstory5(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_80107080_mstory5(omObjData *obj, const Vec *pos, s32 frames);
void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80107254_mstory5(s16 model);
void func_801085D8_mstory5(omObjData *obj);
void func_80108A20_mstory5(void);
void func_8010D47C_mstory5(void);
void func_80109B30_mstory5(omObjData *obj);
void func_8010CFE4_mstory5(void);
void func_8010D230_mstory5(void);
void func_8010E3F0_mstory5(omObjData *obj, omObjData *target);
void func_8010734C_mstory5(omObjData *obj, f32 speed, s16 frames);
void func_8010E8C0_mstory5(omObjData *obj);
void func_8010F14C_mstory5(s32 index, s32 seNo);
void func_8010F240_mstory5(s32 index);
void func_8010F41C_mstory5(omObjData *obj);
void func_801074E8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir);
MstoryPath *func_80107850_mstory5(Vec *points, s32 flags);
void func_80107B54_mstory5(MstoryPath *path, f32 time, Vec *result);
void func_8010DE7C_mstory5(void);
void func_8010AE0C_mstory5(void);
void func_8010AE14_mstory5(omObjData *obj);
void func_801085E0_mstory5(void);
void func_801097B8_mstory5(void);
void func_8010B318_mstory5(void);
void func_80108A28_mstory5(omObjData *obj);
void func_80109790_mstory5(omObjData *obj);
void func_80109E70_mstory5(omObjData *obj);
void func_80109F48_mstory5(omObjData *obj);
void func_8010A0A8_mstory5(omObjData *obj);
void func_8010B320_mstory5(omObjData *obj);
void func_8010B5DC_mstory5(omObjData *obj);
void func_8010B9D4_mstory5(omObjData *obj);
void func_8010C6A4_mstory5(omObjData *obj);
void func_8010CA04_mstory5(omObjData *obj);
void func_8010E538_mstory5(omObjData *obj);
void func_8010EA34_mstory5(omObjData *obj);
void func_8010D484_mstory5(omObjData *arg0);
void func_8010D560_mstory5(omObjData *obj);
void func_8010DE84_mstory5(omObjData *obj);
void func_80109B28_mstory5(void);
void func_8010ABE4_mstory5(void);
void func_8010AF44_mstory5(void);
void func_8010B77C_mstory5(void);
void func_8010B9CC_mstory5(void);
void func_8010C4B8_mstory5(void);
void func_8010CBE8_mstory5(void);
void func_8010E558_mstory5(void);
void func_8010E5D0_mstory5(void);
void func_8010DC78_mstory5(void);
void func_8010DB30_mstory5(void);
void func_8010F2BC_mstory5(void);
void func_8010C85C_mstory5(void);
void func_8010CBE0_mstory5(void);
void func_8010E1A0_mstory5(omObjData *obj);
void func_8010E6B4_mstory5(omObjData *obj);
void func_8010E870_mstory5(omObjData *obj);
void func_8010ABC4_mstory5(omObjData *obj);
void func_8010EBCC_mstory5(omObjData *obj);
void func_8010EDFC_mstory5(omObjData *obj);
void func_8010F02C_mstory5(omObjData *obj);
void func_8010F0B8_mstory5(omObjData *obj);
void func_8010D214_mstory5(void);
void func_8010D594_mstory5(omObjData *obj);
void func_8010E648_mstory5(omObjData *obj);
void func_8010B6F8_mstory5(omObjData *obj);
void func_8010D7D8_mstory5(omObjData *obj);
void func_8010C69C_mstory5(void);
void func_80105D4C_mstory5(void);
void func_80105FDC_mstory5(void);
void func_80105FEC_mstory5(s32 arg0);
s32 func_801068C8_mstory5(void);
void func_801068E4_mstory5(s16 model, s16 animSlot, s16 anim);
void func_801069B8_mstory5(void);
void func_80106A20_mstory5(void);
void func_80106A50_mstory5(void);
void func_80106A74_mstory5(s32 mess);
void func_80106AC8_mstory5(s32 mess);
void func_80106AF4_mstory5(void);
s32 func_80106B30_mstory5(s32 character);
void func_80106B48_mstory5(omObjData *obj, const Vec *pos, s32 frames);
void func_80106FC8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80106FF4_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3);

MstoryPath *func_80107850_mstory5(Vec *points, s32 flags) {
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

void func_80107B54_mstory5(MstoryPath *path, f32 time, Vec *result) {
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

void func_801083FC_mstory5(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010842C_mstory5(void) {
    func_801069B8_mstory5();
    D_80115364_mstory5 = Hu3DModelRead(9, 0x2B9);
    D_80115368_mstory5 = Hu3DModelRead(0x83, 0x2B9);
    omAddPrcObj(func_801085E0_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_801097B8_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010ABE4_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010AF44_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010B77C_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010C4B8_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010C85C_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010CBE8_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010E558_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010E5D0_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010DC78_mstory5, 0x384, 0x800, 0);
    omAddPrcObj(func_8010DB30_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010F2BC_mstory5, 0x1001, 0x800, 0);
    HuPrcVSleep();
    Hu3DModelAttrSet(D_80115364_mstory5, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(D_80115368_mstory5, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_801085D8_mstory5(omObjData *obj) {
}

void func_801085E0_mstory5(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 16, -1, NULL);
    D_801151F0_mstory5[0].obj = obj;
    D_801151F0_mstory5[0].unk_08 = 0;
    D_801151F0_mstory5[0].unk_0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = Hu3DModelRead(0x1D000A, 0x2B9);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    obj->model[4] = Hu3DModelLink(D_80115368_mstory5);
    Hu3DModelAttrSet(obj->model[4], 4, 4);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x9C));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x21));
    omObjMotionRead(obj, 5, D_8011496C_mstory5[chr]);
    omObjMotionRead(obj, 6, D_8011498C_mstory5[chr]);
    omObjMotionRead(obj, 7, D_801149AC_mstory5[chr]);
    omObjMotionRead(obj, 8, CharMotionDataNumGet(chr, 0x33));
    omObjMotionRead(obj, 9, D_801149CC_mstory5[chr]);
    omObjMotionRead(obj, 10, D_801149EC_mstory5[chr]);
    omObjMotionRead(obj, 11, CharMotionDataNumGet(chr, 0x72));
    omObjMotionRead(obj, 12, CharMotionDataNumGet(chr, 0x9B));
    D_80115382_mstory5[0] = CharAnimCreate(obj->model[1], 2, chr, CharMotionDataNumGet(chr, 0xA4));
    D_80115382_mstory5[1] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xAA));
    D_80115382_mstory5[2] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA5));
    D_80115382_mstory5[3] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA9));
    Hu3DModelDynamicFree(obj->model[1]);
    CharAnimSet(obj->model[1], 2, GwStory.unk1, D_80115382_mstory5[0]);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_801152F8_mstory5 = D_80114900_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801152F8_mstory5.x, D_801152F8_mstory5.y, D_801152F8_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_801152F8_mstory5.x, -5.0f, D_801152F8_mstory5.z);
    Hu3DModelPosSet(obj->model[4], D_801152F8_mstory5.x, D_801152F8_mstory5.y, D_801152F8_mstory5.z);
    omPrcSetDestructor(0, func_80108A20_mstory5);
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
    while (TRUE) {
        D_801151F0_mstory5[0].func(obj);
        HuPrcVSleep();
    }
}

void func_80108A20_mstory5(void) {
}

const Vec D_80114900_mstory5 = { -120.0f, 0.0f, 480.0f };

const Vec D_8011490C_mstory5 = { 38.0f, 100.0f, 214.0f };

const Vec D_80114918_mstory5 = { 150.0f, 0.0f, 384.0f };

const Vec D_80114924_mstory5 = { 608.1f, -85.8f, -1390.3f };

const Vec D_80114930_mstory5 = { 800.0f, 0.0f, 380.0f };

const Vec D_8011493C_mstory5 = { -700.0f, 0.0f, 300.0f };

const Vec D_80114948_mstory5 = { -900.0f, 0.0f, 300.0f };

const Vec D_80114954_mstory5 = { 0.0f, 200.0f, 150.0f };

const Vec D_80114960_mstory5 = { 0.0f, 200.0f, 100.0f };

const s32 D_8011496C_mstory5[8] = { 0x1D003E, 0x1D0048, 0x1D0052, 0x1D005B, 0x1D0065, 0x1D006E, 0x1D003E, 0x1D003E };

const s32 D_8011498C_mstory5[8] = { 0x1D0040, 0x1D004B, 0x1D0054, 0x1D005D, 0x1D0067, 0x1D0070, 0x1D0040, 0x1D0040 };

const s32 D_801149AC_mstory5[8] = { 0x1D0041, 0x1D004C, 0x1D0055, 0x1D005E, 0x1D0068, 0x1D0071, 0x1D0041, 0x1D0041 };

const s32 D_801149CC_mstory5[8] = { 0x1D0043, 0x1D004E, 0x1D0057, 0x1D0060, 0x1D006A, 0x1D0073, 0x1D0043, 0x1D0043 };

const s32 D_801149EC_mstory5[8] = { 0x1D003B, 0x1D0044, 0x1D004F, 0x1D0058, 0x1D0061, 0x1D006B, 0x1D003B, 0x1D003B };

const Vec D_80114A0C_mstory5 = { 0.0f, 0.0f, 0.0f };

const Vec D_80114A18_mstory5 = { 0.0f, 180.0f, 0.0f };

const Vec D_80114A24_mstory5 = { -100.0f, 0.0f, 350.0f };
const Vec D_80114A30_mstory5 = { -100.0f, 0.0f, 150.0f };
const Vec D_80114A3C_mstory5 = { 0.0f, 20.0f, 0.0f };
const Vec D_80114A48_mstory5 = { 0.0f, 0.0f, 0.0f };
const Vec D_80114A54_mstory5 = { 0.0f, -26.565f, 0.0f };
const Vec D_80114A60_mstory5 = { 0.0f, 45.0f, 0.0f };

const char D_80114A6C_mstory5[] = "item_hook";

void func_80108A28_mstory5(omObjData *obj) {
    omObjData *obj0;
    omObjData *obj7;
    omObjData *obj1;
    s16 model;
    HmfMotionNode *node;
    s32 fx;
    s32 i;
    f32 scale;
    f32 time;
    Vec pos;

    HuPrcSleep(20);
    // obj0 is unused, but reading it first makes D_801151F0_mstory5 itself
    // the shared base address for the following holder accesses.
    obj0 = D_801151F0_mstory5[0].obj;
    obj7 = D_801151F0_mstory5[7].obj;
    obj1 = D_801151F0_mstory5[1].obj;
    (void)obj0;
    model = obj->model[1];
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107228_mstory5(obj, 0.0f, 110.0f, 0.0f, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    HuPrcSleep(10);
    Hu3DModelAttrSet(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], model, D_80114A6C_mstory5);
    Hu3DModelAttrSet(obj->model[3], 4, 0);
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[5]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    while (!(D_801151F0_mstory5[8].unk_08 & 1)) {
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(D_801151F0_mstory5[8].obj->model[1], 4, 4);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, D_80114A6C_mstory5, 0x1B, 0x45);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, D_80114A6C_mstory5, 0x1B, 0x46);
    Hu3DMotionNoMotSet(model, Hu3DData[model].motId, D_80114A6C_mstory5, 0x1B, 0x47);
    node = Hu3DModelObjPtrGet(model, D_80114A6C_mstory5);
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
    Hu3DMotionNoMotReset(model, Hu3DData[model].motId, D_80114A6C_mstory5, 0x1B, 0x47);
    Hu3DMotionNoMotReset(model, Hu3DData[model].motId, D_80114A6C_mstory5, 0x1B, 0x46);
    Hu3DMotionNoMotReset(model, Hu3DData[model].motId, D_80114A6C_mstory5, 0x1B, 0x45);
    func_80105FEC_mstory5(4);
    while (func_801068C8_mstory5() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4B : 0x5B3F);
    func_80106A50_mstory5();
    Hu3DMotionModelSet(model, obj->motion[5]);
    Hu3DMotionAttrSet(model, 4, 4);
    Hu3DMotionSpeedSet(model, 2.0f);
    Hu3DMotionTimeSet(model, Hu3DMotion[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionModelSet(model, obj->motion[6]);
    Hu3DMotionAttrSet(model, 4, 4);
    Hu3DMotionTimeSet(model, Hu3DMotion[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionSpeedSet(model, 1.0f);
    Hu3DModelAttrSet(obj->model[3], 0x4000, 0);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    HuAudSeqFadeOut(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_80107080_mstory5(obj, &D_80114A0C_mstory5, 10);
    HuAudSeqPlay(0x72);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    CharAnimSet(model, 2, GwStory.unk1, D_80115382_mstory5[2]);
    func_80107254_mstory5(model);
    fx = CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    func_80107080_mstory5(obj7, &D_80114A54_mstory5, 3);
    func_80106B48_mstory5(obj7, &D_80114A24_mstory5, 5);
    func_80107080_mstory5(obj7, &D_80114A3C_mstory5, 3);
    D_801151F0_mstory5[1].func = func_80109F48_mstory5;
    HuAudFXPlay(0x219);
    HuAudFXStop(fx);
    Hu3DModelAttrSet(obj->model[4], 4, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    CharAnimSet(model, 2, GwStory.unk1, D_80115382_mstory5[3]);
    func_80107080_mstory5(obj7, &D_80114A48_mstory5, 3);
    func_80106B64_mstory5(obj7, &D_80114A30_mstory5, 10, 0);
    func_80107254_mstory5(model);
    func_80107080_mstory5(obj, &D_80114A18_mstory5, 10);
    HuAudSeqPlay(0x26);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    CharAnimSet(model, 2, GwStory.unk1, D_80115382_mstory5[0]);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(D_801151F0_mstory5[7].obj->model[1], Hu3DData[D_801151F0_mstory5[7].obj->motion[1]].motId, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4C : 0x5B40);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(D_801151F0_mstory5[7].obj->model[1], Hu3DData[D_801151F0_mstory5[7].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[8]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801151F0_mstory5[3].func = func_8010B320_mstory5;
    func_80107228_mstory5(D_801151F0_mstory5[7].obj, 0.0f, 158.46f, 0.0f, 5);
    D_801151F0_mstory5[1].func = func_8010EA34_mstory5;
    D_801151F0_mstory5[7].func = func_8010E538_mstory5;
    D_801152E0_mstory5.func = func_80109790_mstory5;
    func_80106FF4_mstory5(obj1, 238.0f, 100.0f, 214.0f, 10, 0);
    while (!(D_801151F0_mstory5[3].unk_08 & 8)) {
        HuPrcVSleep();
    }
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4D : 0x5B41);
    func_80106A50_mstory5();
    D_801151F0_mstory5[3].unk_08 |= 1;
    while (!(D_801151F0_mstory5[3].unk_08 & 4)) {
        HuPrcVSleep();
    }
    D_801152C8_mstory5.func = func_8010A0A8_mstory5;
    while (!(D_801151F0_mstory5[1].unk_08 & 1)) {
        HuPrcVSleep();
    }
    D_801151F0_mstory5[4].func = func_8010B9D4_mstory5;
    while (!(D_801151F0_mstory5[4].unk_08 & 2)) {
        HuPrcVSleep();
    }
    D_801152E0_mstory5.func = func_8010D484_mstory5;
    D_801151F0_mstory5[1].func = func_80109E70_mstory5;
    D_801151F0_mstory5[3].func = func_8010B5DC_mstory5;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_8010F14C_mstory5(0, 0x1F);
    func_80107228_mstory5(obj, 0.0f, 90.0f, 0.0f, 20);
    func_80106FC8_mstory5(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    func_8010F240_mstory5(0);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    D_801151F0_mstory5[5].func = func_8010C6A4_mstory5;
    D_801151F0_mstory5[6].func = func_8010CA04_mstory5;
    HuPrcSleep(30);
    HuPrcSleep(40);
    HuAudFXPlay(0x2A0);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A57 : 0x5B4B);
    func_80106A50_mstory5();
    HuPrcSleep(30);
    D_801151F0_mstory5[0].unk_08 |= 1;
    HuPrcSleep(50);
    func_80105FDC_mstory5();
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
}

void func_80109698_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
}

void func_8010975C_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80114A88_mstory5, 10);
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
}

void func_80109790_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(D_801151F0_mstory5[0].obj, D_801151F0_mstory5[3].obj);
}

const Vec D_80114A88_mstory5 = { 0.0f, 150.0f, 0.0f };

const char D_80114A94_mstory5[] = "c204n_0_DEF";

void func_801097B8_mstory5(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 4, 8, -1, NULL);
    D_801151F0_mstory5[1].obj = obj;
    D_801151F0_mstory5[1].unk_08 = 0;
    D_801151F0_mstory5[1].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    omObjMotionRead(obj, 0, 0xA0076);
    omObjMotionRead(obj, 1, 0x1D0029);
    omObjMotionRead(obj, 2, 0x1D002A);
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_80115304_mstory5 = D_8011490C_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115304_mstory5.x, D_80115304_mstory5.y, D_80115304_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115304_mstory5.x, -5.0f, D_80115304_mstory5.z);
    data = DataRead(0xA007E);
    D_80115370_mstory5[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_80114A94_mstory5);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    Hu3DAnimAttrSet(D_80115372_mstory5, 1, 0);
    Hu3DAnimBankSet(D_80115372_mstory5, 0);
    D_80115380_mstory5 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115372_mstory5, 0, D_80114A94_mstory5);
    D_80115370_mstory5[0] = Hu3DAnimData[D_80115370_mstory5[0]].animIdx;
    data = DataRead(0xA0080);
    D_80115370_mstory5[1] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80115370_mstory5[2] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0085);
    D_80115370_mstory5[3] = (s16)Hu3DAnimDataCreate(data);
    HuMemMemoryFreePerm(data);
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_80115372_mstory5);
    omPrcSetDestructor(0, func_80109B28_mstory5);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
    while (TRUE) {
        D_801151F0_mstory5[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80109B28_mstory5(void) {
}

const Vec D_80114AA0_mstory5 = { -5.0f, 300.0f, 0.0f };

const Vec D_80114AAC_mstory5 = { 10.0f, 378.9f, 0.0f };

void func_80109B30_mstory5(omObjData *obj) {
    HuPrcSleep(40);
    HuPrcSleep(20);
    D_801151F0_mstory5[0].func = func_80109698_mstory5;
    D_801151F0_mstory5[7].func = func_8010D560_mstory5;
    func_80107080_mstory5(obj, &D_80114AAC_mstory5, 30);
    func_80106B48_mstory5(obj, &D_80114B0C_mstory5, 20);
    HuPrcSleep(30);
    func_80107080_mstory5(obj, &D_80114ADC_mstory5, 10);
    func_80106B48_mstory5(obj, &D_80114B00_mstory5, 15);
    D_801151F0_mstory5[0].func = func_8010975C_mstory5;
    func_80107080_mstory5(obj, &D_80114AB8_mstory5, 10);
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_80115376_mstory5);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A49 : 0x5B3D);
    func_80106A50_mstory5();
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_80115372_mstory5);
    func_80107228_mstory5(D_801151F0_mstory5[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_80107080_mstory5(D_801151F0_mstory5[7].obj, &D_80114B18_mstory5, 10);
    func_80107080_mstory5(obj, &D_80114AD0_mstory5, 20);
    Hu3DMotionShiftSet(D_801151F0_mstory5[7].obj->model[1], Hu3DData[D_801151F0_mstory5[7].obj->motion[1]].motId, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4A : 0x5B3E);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(D_801151F0_mstory5[7].obj->model[1], Hu3DData[D_801151F0_mstory5[7].obj->motion[0]].motId, 0, 10, 2);
    func_80107080_mstory5(D_801151F0_mstory5[7].obj, &D_80114B24_mstory5, 10);
    D_801151F0_mstory5[8].func = func_8010DE84_mstory5;
    func_80107080_mstory5(obj, &D_80114AA0_mstory5, 20);
    Hu3DMotionShiftSet(D_801151F0_mstory5[0].obj->model[1], Hu3DData[D_801151F0_mstory5[0].obj->motion[12]].motId, 0, 10, 2);
    while (!(D_801151F0_mstory5[8].unk_08 & 2)) {
        HuPrcVSleep();
    }
    D_801151F0_mstory5[0].func = func_80108A28_mstory5;
    HuPrcSleep(40);
    func_80107080_mstory5(obj, &D_80114AF4_mstory5, 50);
    func_80107080_mstory5(obj, &D_80114AE8_mstory5, 40);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
}

void func_80109E70_mstory5(omObjData *obj) {
    Vec pos;
    s16 model = obj->model[1];

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80107228_mstory5(obj, 0.0f, 90.0f, 0.0f, 20);
    func_80106FC8_mstory5(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
}

void func_80109F48_mstory5(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec orig;
    s32 i;

    orig.x = Hu3DData[model].pos.x;
    orig.y = Hu3DData[model].pos.y;
    orig.z = Hu3DData[model].pos.z;
    pos.y = Hu3DData[model].pos.y;
    for (i = 0; i < 12; i++) {
        pos.x = Hu3DData[model].pos.x;
        pos.z = Hu3DData[model].pos.z;
        Hu3DModelPosSet(model, pos.x, sindf(i * 15.0f) * 80.0f + pos.y, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, orig.x, orig.y, orig.z);
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_8011537A_mstory5);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
}

void func_8010A0A8_mstory5(omObjData *obj) {
    omObjData *obj1 = D_801151F0_mstory5[1].obj;
    omObjData *obj3 = D_801151F0_mstory5[3].obj;
    omObjData *obj7 = D_801151F0_mstory5[7].obj;
    omObjData *obj0 = D_801151F0_mstory5[0].obj;

    while (!(D_801151F0_mstory5[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    func_80106B64_mstory5(D_801151F0_mstory5[1].obj, &D_80114BE4_mstory5, 15, 0);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
    func_80107080_mstory5(D_801151F0_mstory5[3].obj, &D_80114B9C_mstory5, 10);
    func_80106FF4_mstory5(obj7, 0.0f, 200.0f, 150.0f, 15, 0);
    Hu3DMotionShiftSet(D_801151F0_mstory5[0].obj->model[1], Hu3DData[D_801151F0_mstory5[0].obj->motion[0]].motId, 0, 30, 2);
    Hu3DMotionShiftSet(D_801151F0_mstory5[3].obj->model[1], Hu3DData[D_801151F0_mstory5[3].obj->motion[9]].motId, 0, 30, 0);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(D_801151F0_mstory5[1].obj->model[1], Hu3DData[D_801151F0_mstory5[1].obj->motion[2]].motId, 0, 30, 2);
    func_80107254_mstory5(D_801151F0_mstory5[3].obj->model[1]);
    Hu3DMotionShiftSet(D_801151F0_mstory5[3].obj->model[1], Hu3DData[D_801151F0_mstory5[3].obj->motion[9]].motId, 0, 30, 0);
    func_80107254_mstory5(D_801151F0_mstory5[3].obj->model[1]);
    Hu3DMotionShiftSet(D_801151F0_mstory5[3].obj->model[1], Hu3DData[D_801151F0_mstory5[3].obj->motion[0]].motId, 0, 30, 2);
    Hu3DMotionShiftSet(D_801151F0_mstory5[1].obj->model[1], Hu3DData[D_801151F0_mstory5[1].obj->motion[0]].motId, 0, 30, 2);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
    func_80106B48_mstory5(D_801151F0_mstory5[1].obj, &D_80114BF0_mstory5, 8);
    func_80107080_mstory5(D_801151F0_mstory5[1].obj, &D_80114B60_mstory5, 10);
    func_80107080_mstory5(D_801151F0_mstory5[3].obj, &D_80114B54_mstory5, 5);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
    func_80107080_mstory5(D_801151F0_mstory5[7].obj, &D_80114BA8_mstory5, 5);
    func_80107080_mstory5(D_801151F0_mstory5[0].obj, &D_80114BB4_mstory5, 5);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4E : 0x5B42);
    func_80106A50_mstory5();
    func_80106B48_mstory5(D_801151F0_mstory5[1].obj, &D_80114BE4_mstory5, 10);
    func_80107228_mstory5(D_801151F0_mstory5[7].obj, 15.0f, 20.0f, 0.0f, 5);
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[1]].motId, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4F : 0x5B43);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[0]].motId, 0, 10, 2);
    HuAudFXPlay(0x27C);
    func_80107228_mstory5(obj3, 0.0f, -110.0f, 0.0f, 5);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[4]].motId, 0, 10, 0);
    func_80107254_mstory5(obj3->model[1]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[5]].motId, 0, 10, 2);
    func_801068E4_mstory5(obj1->model[1], D_80115380_mstory5, D_8011537E_mstory5);
    func_8010CFE4_mstory5();
    HuAudFXPlay(0x21C);
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[4]].motId, 0, 10, 2);
    HuPrcSleep(20);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A50 : 0x5B44);
    func_80106A50_mstory5();
    func_80107228_mstory5(obj7, 0.0f, 0.0f, 0.0f, 5);
    D_801151F0_mstory5[8].func = func_8010E1A0_mstory5;
    HuPrcSleep(50);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[12]].motId, 0, 10, 0);
    func_80107254_mstory5(obj3->model[1]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    D_801152E0_mstory5.func = func_801085D8_mstory5;
    func_80107228_mstory5(obj0, 0.0f, 150.0f, 0.0f, 10);
    func_801068E4_mstory5(obj1->model[1], D_80115380_mstory5, D_80115372_mstory5);
    Hu3DMotionShiftSet(obj0->model[1], Hu3DData[obj0->motion[10]].motId, 0, 10, 2);
    HuPrcSleep(100);
    func_80106B48_mstory5(D_801151F0_mstory5[1].obj, &D_80114BF0_mstory5, 8);
    func_80107080_mstory5(D_801151F0_mstory5[1].obj, &D_80114B60_mstory5, 10);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A51 : 0x5B45);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(obj0->model[1], Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(D_801151F0_mstory5[3].obj->model[1], Hu3DData[D_801151F0_mstory5[3].obj->motion[1]].motId, 0, 30, 2);
    D_801151F0_mstory5[3].func = func_8010E6B4_mstory5;
    D_801151F0_mstory5[7].func = func_8010E870_mstory5;
    HuPrcSleep(70);
    func_801068E4_mstory5(obj1->model[1], D_80115380_mstory5, D_80115376_mstory5);
    Hu3DMotionShiftSet(obj1->model[1], Hu3DData[obj1->motion[1]].motId, 0, 10, 2);
    D_801151F0_mstory5[1].func = func_8010ABC4_mstory5;
    func_80106FF4_mstory5(obj1, 238.0f, 100.0f, 214.0f, 60, 0);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
    D_801151F0_mstory5[8].unk_08 |= 0x10;
    while (!(D_801151F0_mstory5[8].unk_08 & 8)) {
        HuPrcVSleep();
    }
    func_80107228_mstory5(obj1, 0.0f, -140.0f, 0.0f, 10);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A52 : 0x5B46);
    func_80106A50_mstory5();
    func_80107080_mstory5(D_801151F0_mstory5[1].obj, &D_80114B60_mstory5, 10);
    HuPrcSleep(20);
    func_8010D214_mstory5();
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[0]].motId, 0, 10, 2);
    D_80114770_mstory5 = 1;
    func_80106B48_mstory5(D_801151F0_mstory5[7].obj, &D_80114BCC_mstory5, 3);
    HuAudFXPlay(0x219);
    CharFXPlay(0x2AB, GwStory.unk1);
    _HuAudPlayerFXPlay(0x2B3, 1);
    D_801152E0_mstory5.func = func_8010EBCC_mstory5;
    D_801151F0_mstory5[3].func = func_8010EDFC_mstory5;
    D_80114770_mstory5 = 0;
    func_80106B64_mstory5(D_801151F0_mstory5[7].obj, &D_80114BD8_mstory5, 5, 0);
    D_801151F0_mstory5[1].func = func_80109F48_mstory5;
    HuPrcSleep(12);
    func_80107228_mstory5(D_801151F0_mstory5[1].obj, 0.0f, -135.0f, 0.0f, 10);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A53 : 0x5B47);
    func_80107080_mstory5(D_801151F0_mstory5[1].obj, &D_80114B60_mstory5, 10);
    func_8010CFE4_mstory5();
    HuAudFXPlay(0x21C);
    func_80107228_mstory5(obj7, 20.0f, 10.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[4]].motId, 0, 10, 2);
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A54 : 0x5B48);
    func_80106A50_mstory5();
    CharFXPlay(0x274, GwStory.unk1);
    _HuAudPlayerFXPlay(0x27C, 1);
    D_801152E0_mstory5.func = func_8010F02C_mstory5;
    D_801151F0_mstory5[3].func = func_8010F0B8_mstory5;
    HuPrcSleep(10);
    HuPrcSleep(40);
    D_801151F0_mstory5[1].unk_08 |= 1;
    D_801152C8_mstory5.func = func_801085D8_mstory5;
}

void func_8010ABC4_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(obj, D_801151F0_mstory5[0].obj);
}

void func_8010ABE4_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801151F0_mstory5[2].obj = obj;
    D_801151F0_mstory5[2].unk_08 = 0;
    D_801151F0_mstory5[2].unk_0C = 0;
    if (func_80106B30_mstory5(0) == 0) {
        obj->model[1] = Hu3DModelRead(0x200A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
        omObjMotionRead(obj, 0, 0x20000);
        omObjMotionRead(obj, 1, 0x1D003C);
        omObjMotionRead(obj, 2, 0x1D003D);
    } else {
        obj->model[1] = Hu3DModelRead(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
        omObjMotionRead(obj, 0, 0x30000);
        omObjMotionRead(obj, 1, 0x1D0046);
        omObjMotionRead(obj, 2, 0x1D0047);
    }
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    D_80115310_mstory5 = D_80114918_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115310_mstory5.x, D_80115310_mstory5.y, D_80115310_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115310_mstory5.x, -5.0f, D_80115310_mstory5.z);
    omPrcSetDestructor(0, func_8010AE0C_mstory5);
    D_801151F0_mstory5[2].func = func_8010AE14_mstory5;
    while (1) {
        D_801151F0_mstory5[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010AE0C_mstory5(void) {
}

const Vec D_80114AB8_mstory5 = { 20.0f, 320.0f, 0.0f };
const Vec D_80114AC4_mstory5 = { 0.0f, 450.0f, 0.0f }; /* Unreferenced. */

const Vec D_80114AD0_mstory5 = { 0.0f, 225.0f, 0.0f };

const Vec D_80114ADC_mstory5 = { 0.0f, 134.2f, 0.0f };

const Vec D_80114AE8_mstory5 = { 0.0f, 320.0f, 0.0f };

const Vec D_80114AF4_mstory5 = { -30.0f, 260.0f, 0.0f };

const Vec D_80114B00_mstory5 = { 238.0f, 100.0f, 214.0f };

const Vec D_80114B0C_mstory5 = { 88.0f, 100.0f, 360.0f };

const Vec D_80114B18_mstory5 = { 30.0f, -20.0f, 0.0f };

const Vec D_80114B24_mstory5 = { 0.0f, 0.0f, 0.0f };
const Vec D_80114B30_mstory5 = { 0.0f, 158.73f, 0.0f }; /* Unreferenced. */
const Vec D_80114B3C_mstory5 = { 0.0f, 167.01f, 0.0f }; /* Unreferenced. */
const Vec D_80114B48_mstory5 = { 0.0f, 158.46f, 0.0f }; /* Unreferenced. */

const Vec D_80114B54_mstory5 = { 0.0f, -70.43f, 0.0f };

const Vec D_80114B60_mstory5 = { 0.0f, -77.13f, 0.0f };
const Vec D_80114B6C_mstory5 = { 0.0f, -135.0f, 0.0f };  /* Unreferenced. */
const Vec D_80114B78_mstory5 = { 0.0f, 162.4f, 0.0f };   /* Unreferenced. */
const Vec D_80114B84_mstory5 = { 0.0f, -147.34f, 0.0f }; /* Unreferenced. */
const Vec D_80114B90_mstory5 = { 0.0f, 306.61f, 0.0f };  /* Unreferenced. */

const Vec D_80114B9C_mstory5 = { 0.0f, 90.0f, 0.0f };

const Vec D_80114BA8_mstory5 = { 0.0f, 50.19f, 0.0f };

const Vec D_80114BB4_mstory5 = { 0.0f, 100.78f, 0.0f };
const Vec D_80114BC0_mstory5 = { 150.0f, 0.0f, 384.0f }; /* Unreferenced. */

const Vec D_80114BCC_mstory5 = { 0.0f, 200.0f, 300.0f };

const Vec D_80114BD8_mstory5 = { 0.0f, 200.0f, 150.0f };

const Vec D_80114BE4_mstory5 = { 300.0f, 25.0f, 400.0f };

const Vec D_80114BF0_mstory5 = { 300.0f, 125.0f, 400.0f };
const Vec D_80114BFC_mstory5 = { 238.0f, 100.0f, 214.0f }; /* Unreferenced. */

const Vec D_80114C08_mstory5 = { 200.0f, 0.0f, 1200.0f };

void func_8010AE14_mstory5(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106B30_mstory5(0) == 0) {
        CharFXPlay(0x26B, 0);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    D_801151F0_mstory5[1].func = func_80109B30_mstory5;
    HuPrcSleep(70);
    if (func_80106B30_mstory5(0) == 0) {
        CharFXPlay(0x286, 0);
    } else {
        CharFXPlay(0x286, 1);
    }
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    func_8010F14C_mstory5(2, 40);
    func_80106B48_mstory5(obj, &D_80114C08_mstory5, 40);
    func_8010F240_mstory5(2);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801151F0_mstory5[2].func = func_801085D8_mstory5;
}

void func_8010AF44_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(20, 4, 16, -1, NULL);
    D_801151F0_mstory5[3].obj = obj;
    D_801151F0_mstory5[3].unk_08 = 0;
    D_801151F0_mstory5[3].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0x90000, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    obj->model[3] = Hu3DModelLink(D_80115368_mstory5);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    omObjMotionRead(obj, 0, 0x90004);
    omObjMotionRead(obj, 1, CharMotionDataNumGet(7, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(7, 2));
    omObjMotionRead(obj, 3, 0x9000C);
    omObjMotionRead(obj, 4, 0x1D0079);
    omObjMotionRead(obj, 5, 0x1D007B);
    omObjMotionRead(obj, 6, 0x1D007C);
    omObjMotionRead(obj, 7, CharMotionDataNumGet(7, 0x7A));
    omObjMotionRead(obj, 8, 0x70003);
    omObjMotionRead(obj, 9, 0x1D0078);
    omObjMotionRead(obj, 10, CharMotionDataNumGet(7, 0x13));
    omObjMotionRead(obj, 11, CharMotionDataNumGet(7, 0x72));
    omObjMotionRead(obj, 12, CharMotionDataNumGet(7, 0x32));
    omObjMotionRead(obj, 13, CharMotionDataNumGet(7, 0x33));
    omObjMotionRead(obj, 14, CharMotionDataNumGet(7, 0x21));
    D_8011538A_mstory5[0] = CharAnimCreate(obj->model[1], 2, 7, CharMotionDataNumGet(7, 0xA4));
    D_8011538A_mstory5[1] = Hu3DAnimDataRead(CharMotionDataNumGet(7, 0xAA));
    D_8011538A_mstory5[2] = Hu3DAnimDataRead(CharMotionDataNumGet(7, 0xA5));
    D_8011538A_mstory5[3] = Hu3DAnimDataRead(CharMotionDataNumGet(7, 0xA6));
    Hu3DModelDynamicFree(obj->model[1]);
    CharAnimSet(obj->model[1], 2, 7, D_8011538A_mstory5[0]);
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_8011531C_mstory5 = D_80114924_mstory5;
    Hu3DModelPosSet(obj->model[1], D_8011531C_mstory5.x, D_8011531C_mstory5.y, D_8011531C_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_8011531C_mstory5.x, -5.0f, D_8011531C_mstory5.z);
    omPrcSetDestructor(0, func_8010B318_mstory5);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
    while (TRUE) {
        D_801151F0_mstory5[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010B318_mstory5(void) {
}

void func_8010B320_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DModelAttrSet(model, 4, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
    func_80105D4C_mstory5();
    HuPrcSleep(15);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    while (!(D_801151F0_mstory5[1].unk_08 & 2)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    HuAudFXVolSet(HuAudFXPlay(0x297), 90);
    func_80107254_mstory5(model);
    D_801151F0_mstory5[3].unk_08 |= 8;
    while (!(D_801151F0_mstory5[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    func_8010F14C_mstory5(3, 40);
    HuAudFXVolSet((s16)D_801151F0_mstory5[3].unk_14, 64);
    D_801152E0_mstory5.func = func_8010F41C_mstory5;
    func_801074E8_mstory5(obj, 150.0f, 0.0f, 384.0f, 180, 1);
    func_8010F240_mstory5(3);
    func_801068E4_mstory5(D_801151F0_mstory5[1].obj->model[1], D_80115380_mstory5, D_80115372_mstory5);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[10]].motId, 0, 30, 2);
    D_801151F0_mstory5[3].unk_08 |= 4;
    HuPrcSleep(60);
    func_801068E4_mstory5(D_801151F0_mstory5[1].obj->model[1], D_80115380_mstory5, D_80115372_mstory5);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
    D_801151F0_mstory5[3].unk_08 |= 2;
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
}

void func_8010B5DC_mstory5(omObjData *obj) {
    Vec pos;
    s16 model = obj->model[1];

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_8010F14C_mstory5(3, 0x1F);
    func_80107228_mstory5(obj, 0.0f, 90.0f, 0.0f, 20);
    func_80106FC8_mstory5(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    func_8010F240_mstory5(3);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
}

void func_8010B6F8_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
}

void func_8010B77C_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 16, 8, -1, NULL);
    D_801151F0_mstory5[4].obj = obj;
    D_801151F0_mstory5[4].unk_08 = 0;
    D_801151F0_mstory5[4].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    obj->model[3] = Hu3DModelRead(0x1D0027, 0x2B9);
    omObjMotionRead(obj, 0, 0xA0030);
    omObjMotionRead(obj, 1, 0xA0035);
    omObjMotionRead(obj, 2, 0xA0032);
    omObjMotionRead(obj, 3, 0x1D0031);
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DMotionAttrSet(obj->model[3], 2, 2);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115328_mstory5 = D_80114930_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115328_mstory5.x, D_80115328_mstory5.y, D_80115328_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115328_mstory5.x, -5.0f, D_80115328_mstory5.z);
    omPrcSetDestructor(0, func_8010B9CC_mstory5);
    D_801151F0_mstory5[4].func = func_801085D8_mstory5;
    while (1) {
        D_801151F0_mstory5[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010B9CC_mstory5(void) {
}

void func_8010B9D4_mstory5(omObjData *obj) {
    s16 model = obj->model[1];
    omObjData *obj3 = D_801151F0_mstory5[3].obj;
    omObjData *obj7 = D_801151F0_mstory5[7].obj;
    omObjData *obj0 = D_801151F0_mstory5[0].obj;
    omObjData *obj1 = D_801151F0_mstory5[1].obj;
    Vec rot;
    Vec pos;
    Vec vel;
    f32 scale;
    f32 shadowScale;
    f32 t;

    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, 0);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, 0);
    func_8010D214_mstory5();
    HuAudSeqPlay(0x21);
    HuAudFXPlay(0x29D);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A55 : 0x5B49);
    func_80106A50_mstory5();
    D_801151F0_mstory5[7].func = func_8010D594_mstory5;
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(40);
    func_80107228_mstory5(obj3, 0.0f, -90.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[1]].motId, 0, 10, 2);
    func_8010F14C_mstory5(3, 31);
    func_80106FC8_mstory5(obj3, Hu3DData[obj3->model[1]].pos.x - 50.0f, Hu3DData[obj3->model[1]].pos.y, Hu3DData[obj3->model[1]].pos.z, 10);
    func_8010F240_mstory5(3);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    while (!(D_801151F0_mstory5[7].unk_08 & 1)) {
        HuPrcVSleep();
    }
    func_80106FC8_mstory5(obj, 300.0f, 0.0f, 380.0f, 30);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_8011537A_mstory5);
    func_80107228_mstory5(obj3, 0.0f, 90.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[7]].motId, 0, 10, 0);
    HuAudFXPlay(0x2B3);
    func_80107254_mstory5(obj3->model[1]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(3);
    Hu3DMotionAttrSet(obj3->model[1], 1, 1);
    HuPrcSleep(10);
    Hu3DMotionAttrSet(obj3->model[1], 1, 0);
    HuPrcSleep(6);
    HuAudFXPlay(0x21D);
    D_801152C8_mstory5.func = func_8010E648_mstory5;
    D_801151F0_mstory5[3].func = func_8010B6F8_mstory5;
    Hu3DMotionTimeSet(obj0->model[4], 0.0f);
    Hu3DModelPosSet(obj0->model[4], 180.0f, 0.0f, 480.0f);
    Hu3DModelAttrSet(obj0->model[4], HU3D_ATTR_DISPOFF, 0);
    D_801151F0_mstory5[1].func = func_80109F48_mstory5;
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[5]].motId, 0, 10, 2);
    D_801151F0_mstory5[7].func = func_8010D7D8_mstory5;
    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    rot.x = Hu3DData[model].rot.x;
    rot.y = Hu3DData[model].rot.y;
    rot.z = Hu3DData[model].rot.z;
    scale = 1.0f;
    shadowScale = 3.0f;
    vel.x = -111.666664f;
    vel.y = 66.666664f;
    vel.z = -100.0f;
    t = 0.0f;
    while (TRUE) {
        pos.x += vel.x;
        pos.y += vel.y;
        pos.z += vel.z;
        vel.x *= 0.85f;
        vel.y *= 0.85f;
        vel.z *= 0.85f;
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        Hu3DModelPosSet(obj->model[2], pos.x, 0.0f, pos.z);
        rot.z += 2.25f;
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        Hu3DModelScaleSet(model, scale, scale, scale);
        scale = vel.z / -100.0f;
        Hu3DModelScaleSet(obj->model[2], shadowScale, 1.0f, shadowScale);
        shadowScale -= 0.5f;
        if (shadowScale < 0.0f) {
            shadowScale = 0.0f;
        }
        if (t >= 20.0f) {
            break;
        }
        t += 1.0f;
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(obj->model[3], Hu3DData[model].pos.x, Hu3DData[model].pos.y, Hu3DData[model].pos.z);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    HuAudFXPlay(0x21E);
    while (!(D_801151F0_mstory5[4].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(35);
    D_801151F0_mstory5[7].unk_08 |= 2;
    HuPrcSleep(50);
    func_80107228_mstory5(obj3, 0.0f, 0.0f, 0.0f, 10);
    CharAnimSet(obj3->model[1], 2, 7, D_8011538A_mstory5[2]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[4]].motId, 0, 10, 0);
    func_80107254_mstory5(obj3->model[1]);
    HuAudFXPlay(0x27C);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[5]].motId, 0, 10, 2);
    HuPrcSleep(20);
    func_80107228_mstory5(obj3, 0.0f, -90.0f, 0.0f, 20);
    HuPrcSleep(10);
    func_80107228_mstory5(obj1, 0.0f, -30.0f, 0.0f, 10);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A58 : 0x5B4C);
    func_80106A50_mstory5();
    func_80107228_mstory5(obj1, 0.0f, 0.0f, 0.0f, 10);
    HuPrcSleep(60);
    func_80107228_mstory5(obj7, 0.0f, 20.0f, 0.0f, 10);
    Hu3DMotionShiftSet(D_801151F0_mstory5[7].obj->model[1], Hu3DData[D_801151F0_mstory5[7].obj->motion[2]].motId, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A59 : 0x5B4D);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[5]].motId, 0, 10, 2);
    CharAnimSet(obj3->model[1], 2, 7, D_8011538A_mstory5[0]);
    func_80107228_mstory5(obj3, 0.0f, 0.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[13]].motId, 0, 10, 0);
    func_80107254_mstory5(obj3->model[1]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    func_80107228_mstory5(obj3, 0.0f, 90.0f, 0.0f, 10);
    D_801151F0_mstory5[4].unk_08 |= 2;
    D_801151F0_mstory5[4].func = func_801085D8_mstory5;
}

void func_8010C4B8_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801151F0_mstory5[5].obj = obj;
    D_801151F0_mstory5[5].unk_08 = 0;
    D_801151F0_mstory5[5].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    omObjMotionRead(obj, 0, 0xA00EF);
    omObjMotionRead(obj, 1, 0xA00F1);
    omObjMotionRead(obj, 2, 0xA00F0);
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115334_mstory5 = D_8011493C_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115334_mstory5.x, D_80115334_mstory5.y, D_80115334_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115334_mstory5.x, -5.0f, D_80115334_mstory5.z);
    omPrcSetDestructor(0, func_8010C69C_mstory5);
    D_801151F0_mstory5[5].func = func_801085D8_mstory5;
    while (1) {
        D_801151F0_mstory5[5].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C69C_mstory5(void) {
}

void func_8010C6A4_mstory5(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    Hu3DModelAttrSet(model, 4, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106FC8_mstory5(obj, 100.0f, pos.y, pos.z, 30);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80107228_mstory5(obj, 0.0f, 210.0f, 0.0f, 10);
    while (!(D_801151F0_mstory5[0].unk_08 & 1)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 2);
        func_80107254_mstory5(model);
    }
}

void func_8010C85C_mstory5(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801151F0_mstory5[6].obj = obj;
    D_801151F0_mstory5[6].unk_08 = 0;
    D_801151F0_mstory5[6].unk_0C = 0;
    src = D_801151F0_mstory5[5].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    Hu3DMotionModelSet(obj->model[1], src->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115340_mstory5 = D_80114948_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115340_mstory5.x, D_80115340_mstory5.y, D_80115340_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115340_mstory5.x, -5.0f, D_80115340_mstory5.z);
    omPrcSetDestructor(0, func_8010CBE0_mstory5);
    D_801151F0_mstory5[6].func = func_801085D8_mstory5;
    while (1) {
        D_801151F0_mstory5[6].func(obj);
        HuPrcVSleep();
    }
}

void func_8010CA04_mstory5(omObjData *obj) {
    s16 model = obj->model[1];
    omObjData *src = D_801151F0_mstory5[5].obj;
    Vec pos;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    Hu3DModelAttrSet(model, 4, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    func_80106FC8_mstory5(obj, -100.0f, pos.y, pos.z, 30);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    func_80107228_mstory5(obj, 0.0f, 200.0f, 0.0f, 10);
    while (!(D_801151F0_mstory5[0].unk_08 & 1)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[src->motion[2]].motId, 0, 10, 2);
        func_80107254_mstory5(model);
    }
}

void func_8010CBE0_mstory5(void) {
}

const char D_80114C14_mstory5[] = "c208nk0-r_eye";
const char D_80114C24_mstory5[] = "r_eye";
const char D_80114C2C_mstory5[] = "l_eye";
const char D_80114C34_mstory5[] = "c208nk1-r_eye";

void func_8010CBE8_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(20, 10, 8, -1, NULL);
    D_801151F0_mstory5[7].obj = obj;
    D_801151F0_mstory5[7].unk_08 = 0;
    D_801151F0_mstory5[7].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    AuraCreate(obj->model[1]);
    omObjMotionRead(obj, 0, 0xA0123);
    omObjMotionRead(obj, 1, 0xA0125);
    omObjMotionRead(obj, 2, 0xA012E);
    omObjMotionRead(obj, 3, 0xA0127);
    omObjMotionRead(obj, 4, 0xA0126);
    omObjMotionRead(obj, 5, 0xA012A);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    obj->model[3] = Hu3DModelRead(0x1D002E, 0x6B9);
    obj->model[4] = Hu3DModelRead(0x1D002E, 0x6B9);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    Hu3DModelAttrSet(obj->model[4], 4, 4);
    obj->model[5] = Hu3DModelRead(0xA0122, 0x2A9);
    Hu3DModelAttrSet(obj->model[5], 4, 4);
    Hu3DModelScaleSet(obj->model[5], 2.0f, 2.0f, 2.0f);
    AuraCreate(obj->model[5]);
    Hu3DModelObjCopy(obj->model[3], D_80114C14_mstory5, obj->model[5], D_80114C24_mstory5);
    Hu3DModelObjCopy(obj->model[4], D_80114C14_mstory5, obj->model[5], D_80114C2C_mstory5);
    obj->model[6] = Hu3DModelRead(0x1D002F, 0x6B9);
    obj->model[7] = Hu3DModelRead(0x1D002F, 0x6B9);
    Hu3DModelAttrSet(obj->model[6], 4, 4);
    Hu3DModelAttrSet(obj->model[7], 4, 4);
    obj->model[8] = Hu3DModelRead(0xA0122, 0x2A9);
    Hu3DModelAttrSet(obj->model[8], 4, 4);
    Hu3DModelScaleSet(obj->model[8], 2.0f, 2.0f, 2.0f);
    AuraCreate(obj->model[8]);
    Hu3DModelObjCopy(obj->model[6], D_80114C34_mstory5, obj->model[8], D_80114C24_mstory5);
    Hu3DModelObjCopy(obj->model[7], D_80114C34_mstory5, obj->model[8], D_80114C2C_mstory5);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_8011534C_mstory5 = D_80114954_mstory5;
    Hu3DModelPosSet(obj->model[1], D_8011534C_mstory5.x, D_8011534C_mstory5.y, D_8011534C_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_8011534C_mstory5.x, -5.0f, D_8011534C_mstory5.z);
    omPrcSetDestructor(0, func_8010D47C_mstory5);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
    D_80114774_mstory5 = 1;
    while (TRUE) {
        D_801151F0_mstory5[7].func(obj);
        HuPrcVSleep();
    }
}

void func_8010CFE4_mstory5(void) {
    omObjData *obj = D_801151F0_mstory5[7].obj;
    s16 models[2];

    models[0] = obj->model[1];
    models[1] = obj->model[5];
    Hu3DModelAttrSet(models[0], 4, 4);
    Hu3DModelAttrSet(models[1], 4, 0);
    Hu3DData[models[1]].pos.x = Hu3DData[models[0]].pos.x;
    Hu3DData[models[1]].pos.y = Hu3DData[models[0]].pos.y;
    Hu3DData[models[1]].pos.z = Hu3DData[models[0]].pos.z;
    Hu3DData[models[1]].rot.x = Hu3DData[models[0]].rot.x;
    Hu3DData[models[1]].rot.y = Hu3DData[models[0]].rot.y;
    Hu3DData[models[1]].rot.z = Hu3DData[models[0]].rot.z;
    Hu3DData[models[1]].scale.x = Hu3DData[models[0]].scale.x;
    Hu3DData[models[1]].scale.y = Hu3DData[models[0]].scale.y;
    Hu3DData[models[1]].scale.z = Hu3DData[models[0]].scale.z;
    obj->model[1] = models[1];
    obj->model[5] = models[0];
}

void func_8010D214_mstory5(void) {
    func_8010CFE4_mstory5();
}

void func_8010D230_mstory5(void) {
    omObjData *obj = D_801151F0_mstory5[7].obj;
    s16 models[2];

    models[0] = obj->model[1];
    models[1] = obj->model[8];
    Hu3DModelAttrSet(models[0], 4, 4);
    Hu3DModelAttrSet(models[1], 4, 0);
    Hu3DData[models[1]].pos.x = Hu3DData[models[0]].pos.x;
    Hu3DData[models[1]].pos.y = Hu3DData[models[0]].pos.y;
    Hu3DData[models[1]].pos.z = Hu3DData[models[0]].pos.z;
    Hu3DData[models[1]].rot.x = Hu3DData[models[0]].rot.x;
    Hu3DData[models[1]].rot.y = Hu3DData[models[0]].rot.y;
    Hu3DData[models[1]].rot.z = Hu3DData[models[0]].rot.z;
    Hu3DData[models[1]].scale.x = Hu3DData[models[0]].scale.x;
    Hu3DData[models[1]].scale.y = Hu3DData[models[0]].scale.y;
    Hu3DData[models[1]].scale.z = Hu3DData[models[0]].scale.z;
    obj->model[1] = models[1];
    obj->model[8] = models[0];
}

void func_8010D460_mstory5(void) {
    func_8010D230_mstory5();
}

void func_8010D47C_mstory5(void) {
}

void func_8010D484_mstory5(omObjData *arg0) {
    omObjData *obj = D_801151F0_mstory5[7].obj;
    Vec pos;
    s16 model = obj->model[1];

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80107228_mstory5(obj, 0.0f, 90.0f, 0.0f, 20);
    func_80106FC8_mstory5(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801152E0_mstory5.func = func_801085D8_mstory5;
}

void func_8010D560_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80114C44_mstory5, 20);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
}

void func_8010D594_mstory5(omObjData *obj) {
    s32 frames = 20;
    omObjData *objs[4];
    Vec dist;
    f32 speed[3];
    s32 i;
    s32 j;

    dist.x = 150.0f;
    dist.y = 350.0f;
    dist.z = 400.0f;
    speed[0] = dist.x / frames;
    speed[1] = dist.y / frames;
    speed[2] = dist.z / frames;

    objs[0] = D_801151F0_mstory5[0].obj;
    objs[1] = D_801151F0_mstory5[1].obj;
    objs[2] = D_801151F0_mstory5[7].obj;
    objs[3] = D_801151F0_mstory5[3].obj;
    func_80107228_mstory5(objs[0], 0.0f, 90.0f, 0.0f, 10);
    func_80107228_mstory5(objs[1], 0.0f, 90.0f, 0.0f, 10);
    func_80107228_mstory5(objs[2], 0.0f, 90.0f, 0.0f, 10);
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[3]].motId, 0, 10, 2);
    for (i = 0; i < frames; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DData[objs[j]->model[1]].pos.x -= speed[j];
            Hu3DData[objs[j]->model[2]].pos.x -= speed[j];
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[0]].motId, 0, 10, 2);
    D_801151F0_mstory5[7].unk_08 |= 1;
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
}

const Vec D_80114C44_mstory5 = { 0.0f, 10.0f, 0.0f };

void func_8010D7D8_mstory5(omObjData *obj) {
    omObjData *objs[3];
    f32 rotY[3] = { 90.0f, 135.0f, 135.0f };
    f32 rotX[3] = { 0.0f, 10.0f, 20.0f };
    s32 frames;
    s32 i;
    s32 j;

    frames = 20;
    objs[0] = D_801151F0_mstory5[0].obj;
    objs[1] = D_801151F0_mstory5[7].obj;
    objs[2] = D_801151F0_mstory5[1].obj;
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[3]].motId, 0, 10, 2);
    for (i = 0; i < frames; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DData[objs[j]->model[1]].rot.y += 90.0f / frames;
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[0]].motId, 0, 10, 2);
    while (!(D_801151F0_mstory5[7].unk_08 & 2)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[3]].motId, 0, 10, 2);
    frames = 20;
    for (i = 0; i < frames; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DData[objs[j]->model[1]].rot.y -= rotY[j] / frames;
            Hu3DData[objs[j]->model[1]].rot.x += rotX[j] / frames;
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[0]].motId, 0, 10, 2);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
}

const s32 D_80114C68_mstory5[] = { 0x1D0003, 0x1D0004, 0x1D0005, 0x1D0006 };

void func_8010DADC_mstory5(omObjData *obj) {
    HuPrcSleep(60);
    func_80107228_mstory5(obj, 0.0f, 30.0f, 0.0f, 50);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
}

void func_8010DB30_mstory5(void) {
    f32 angle = 0.0f;
    omObjData *obj;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80114774_mstory5 != 0) {
        obj = D_801151F0_mstory5[7].obj;
        model = obj->model[1];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            model = obj->model[1];
            pos.x = Hu3DData[model].pos.x;
            pos.z = Hu3DData[model].pos.z;
            ofs = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            if (D_80114770_mstory5 != 1) {
                Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            }
            HuPrcVSleep();
        }
    }
}

void func_8010DC78_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_801151F0_mstory5[8].obj = obj;
    D_801151F0_mstory5[8].unk_08 = 0;
    D_801151F0_mstory5[8].unk_0C = 0;
    obj->model[1] = Hu3DModelRead(D_80114C78_mstory5[0], 0x20299);
    obj->model[2] = Hu3DModelRead(D_80114C78_mstory5[1], 0x20299);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DMotionAttrSet(obj->model[2], 2, 2);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80115358_mstory5 = D_80114960_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115358_mstory5.x, D_80115358_mstory5.y, D_80115358_mstory5.z);
    D_80115366_mstory5 = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(D_80115366_mstory5, 4.0f, 20.0f, 4.0f);
    EffectRangeSet(D_80115366_mstory5, 60.0f);
    Hu3DParticleAttrSet(D_80115366_mstory5, 1, 0);
    Hu3DModelAttrSet(D_80115366_mstory5, 4, 4);
    omPrcSetDestructor(0, func_8010DE7C_mstory5);
    D_801151F0_mstory5[8].func = func_801085D8_mstory5;
    while (1) {
        D_801151F0_mstory5[8].func(obj);
        HuPrcVSleep();
    }
}

void func_8010DE7C_mstory5(void) {
}

void func_8010DE84_mstory5(omObjData *obj) {
    Vec pos;
    MstoryPath *paths[2];
    omObjData *target;
    f32 rotY;
    s32 i;

    paths[0] = func_80107850_mstory5(D_80114778_mstory5, 0);
    paths[1] = func_80107850_mstory5(D_801147A8_mstory5, 0);
    Hu3DModelAttrSet(obj->model[1], 4, 0);
    Hu3DModelAttrSet(D_80115366_mstory5, 4, 0);
    Hu3DParticleAttrSet(D_80115366_mstory5, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        func_80107B54_mstory5(paths[0], (i * 0.02f) * (i * 0.02f), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        EffectPosSet(D_80115366_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    target = D_801151F0_mstory5[7].obj;
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[3]].motId, 0, 10, 0);
    HuPrcSleep(20);
    D_801151F0_mstory5[8].unk_08 |= 2;
    HuAudFXPlay(0x218);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[0]].motId, 0, 10, 2);
    rotY = 0.0f;
    for (i = 0; i < 120; i++) {
        func_80107B54_mstory5(paths[1], (i * 0.008333334f) * (i * 0.008333334f), &pos);
        rotY -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        Hu3DModelRotSet(obj->model[1], 0.0f, rotY, 0.0f);
        EffectPosSet(D_80115366_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DParticleAttrSet(D_80115366_mstory5, 1, 0);
    HuAudFXPlay(0x21A);
    func_801083FC_mstory5(paths[0]);
    func_801083FC_mstory5(paths[1]);
    D_801151F0_mstory5[8].unk_08 = 1;
    D_801151F0_mstory5[8].func = func_801085D8_mstory5;
}

void func_8010E1A0_mstory5(omObjData *obj) {
    Vec pos;
    MstoryPath *path;
    s32 i;

    path = func_80107850_mstory5(D_801147F0_mstory5, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
    Hu3DParticleAttrSet(D_80115366_mstory5, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        func_80107B54_mstory5(path, (i * 0.02f) * (i * 0.02f), &pos);
        pos.x += -100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        EffectPosSet(D_80115366_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    while (!(D_801151F0_mstory5[8].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    for (i = 0; i < 50; i++) {
        func_80107B54_mstory5(path, (1.0f - i * 0.02f) * (1.0f - i * 0.02f), &pos);
        pos.x += -100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        EffectPosSet(D_80115366_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    Hu3DParticleAttrSet(D_80115366_mstory5, 1, 0);
    func_801083FC_mstory5(path);
    D_801151F0_mstory5[8].unk_08 = 8;
    D_801151F0_mstory5[8].func = func_801085D8_mstory5;
}

void func_8010E3F0_mstory5(omObjData *obj, omObjData *target) {
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

void func_8010E538_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(obj, D_801151F0_mstory5[3].obj);
}

void func_8010E558_mstory5(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_801152C8_mstory5.obj = obj;
    D_801152C8_mstory5.unk_08 = 0;
    D_801152C8_mstory5.unk_0C = 0;
    D_801152C8_mstory5.func = func_801085D8_mstory5;

    for (;;) {
        D_801152C8_mstory5.func(obj);
        HuPrcVSleep();
    }
}

void func_8010E5D0_mstory5(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_801152E0_mstory5.obj = obj;
    D_801152E0_mstory5.unk_08 = 0;
    D_801152E0_mstory5.unk_0C = 0;
    D_801152E0_mstory5.func = func_801085D8_mstory5;

    for (;;) {
        D_801152E0_mstory5.func(obj);
        HuPrcVSleep();
    }
}

void func_8010E648_mstory5(omObjData *obj) {
    func_80106A20_mstory5();
    func_80106AC8_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A56 : 0x5B4A);
    func_80106AF4_mstory5();
    func_80106A50_mstory5();
    D_801151F0_mstory5[4].unk_08 |= 0x10;
    D_801152C8_mstory5.func = func_801085D8_mstory5;
}

void func_8010E6B4_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(obj, D_801151F0_mstory5[0].obj);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 30, 2);
    func_8010F14C_mstory5(3, 31);
    func_8010734C_mstory5(obj, 4.5f, 15);
    func_8010F240_mstory5(3);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
    D_801152E0_mstory5.func = func_8010E8C0_mstory5;
}

void func_8010E7B0_mstory5(omObjData *obj) {
    while (TRUE) {
        if (Hu3DData[obj->model[1]].pos.y > 100.0f) {
            Hu3DData[obj->model[1]].pos.y -= 2.0f;
            HuPrcVSleep();
        } else {
            break;
        }
    }
    Hu3DData[obj->model[1]].pos.y = 100.0f;
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
}

void func_8010E870_mstory5(omObjData *obj) {
    Vec pos = D_80114C84_mstory5;

    func_80107080_mstory5(obj, &pos, 10);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
}

void func_8010E8C0_mstory5(omObjData *obj) {
    omObjData *player = D_801151F0_mstory5[0].obj;

    func_8010E3F0_mstory5(player, D_801151F0_mstory5[3].obj);
    Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[3]].motId, 0, 30, 2);
    func_8010F14C_mstory5(0, 31);
    func_8010734C_mstory5(player, 3.5f, 15);
    func_8010F240_mstory5(0);
    CharAnimSet(player->model[1], 2, GwStory.unk1, D_80115384_mstory5);
    Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[11]].motId, 0, 30, 2);
    CharAnimSet(D_801151F0_mstory5[3].obj->model[1], 2, 7, D_8011538A_mstory5[0]);
    Hu3DMotionShiftSet(D_801151F0_mstory5[3].obj->model[1], Hu3DData[D_801151F0_mstory5[3].obj->motion[11]].motId, 0, 30, 2);
    D_801152E0_mstory5.func = func_801085D8_mstory5;
}

void func_8010EA34_mstory5(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_80114C90_mstory5;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_801068E4_mstory5(model, D_80115380_mstory5, D_8011537A_mstory5);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &target, 5);
    func_801068E4_mstory5(model, D_80115380_mstory5, D_80115372_mstory5);
    D_801151F0_mstory5[1].unk_08 |= 2;
    D_801151F0_mstory5[1].func = func_8010E538_mstory5;
}

void func_8010EBCC_mstory5(omObjData *obj) {
    Vec pos = D_80114C9C_mstory5;
    Vec target;
    omObjData *player = D_801151F0_mstory5[0].obj;

    target.x = Hu3DData[player->model[1]].pos.x - 5.0f;
    target.y = Hu3DData[player->model[1]].pos.y;
    target.z = 500.0f;
    Hu3DModelRotSet(player->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(player->model[4], Hu3DData[player->model[1]].pos.x, Hu3DData[player->model[1]].pos.y, Hu3DData[player->model[1]].pos.z);
    Hu3DMotionTimeSet(player->model[4], 0.0f);
    Hu3DModelAttrSet(player->model[4], 4, 0);
    CharAnimSet(player->model[1], 2, GwStory.unk1, D_80115382_mstory5[3]);
    Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[4]].motId, 0, 30, 0);
    func_80106B48_mstory5(player, &target, 10);
    func_80107254_mstory5(player->model[1]);
    CharAnimSet(player->model[1], 2, GwStory.unk1, D_80115382_mstory5[0]);
    Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[0]].motId, 0, 30, 2);
    func_80107080_mstory5(player, &pos, 10);
    D_801152E0_mstory5.func = func_801085D8_mstory5;
}

void func_8010EDFC_mstory5(omObjData *obj) {
    Vec pos = D_80114CA8_mstory5;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x + 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    Hu3DModelAttrSet(obj->model[3], 4, 0);
    CharAnimSet(obj->model[1], 2, 7, D_8011538A_mstory5[3]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[14]].motId, 0, 30, 0);
    func_80106B48_mstory5(obj, &target, 10);
    func_80107254_mstory5(obj->model[1]);
    CharAnimSet(obj->model[1], 2, 7, D_8011538A_mstory5[0]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
    func_80107080_mstory5(obj, &pos, 10);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
}

void func_8010F02C_mstory5(omObjData *obj) {
    omObjData *target = D_801151F0_mstory5[0].obj;

    func_80107228_mstory5(target, 0.0f, 0.0f, 0.0f, 10);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[8]].motId, 0, 10, 0);
    D_801152E0_mstory5.func = func_801085D8_mstory5;
}

void func_8010F0B8_mstory5(omObjData *obj) {
    omObjData *target = D_801151F0_mstory5[3].obj;

    func_80107228_mstory5(target, 0.0f, 0.0f, 0.0f, 10);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[13]].motId, 0, 10, 0);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
}

const s32 D_80114C78_mstory5[3] = { 0x1D0007, 0x1D0008, 0x1D0009 };

const Vec D_80114C84_mstory5 = { 0.0f, 0.0f, 0.0f };

const Vec D_80114C90_mstory5 = { 0.0f, 167.0f, 0.0f };

const Vec D_80114C9C_mstory5 = { 0.0f, 180.0f, 0.0f };

const Vec D_80114CA8_mstory5 = { 0.0f, -180.0f, 0.0f };

void func_8010F14C_mstory5(s32 index, s32 seNo) {
    if (D_801151F0_mstory5[index].unk_0C == 0) {
        D_801151F0_mstory5[index].unk_0C = 1;
        D_801151F0_mstory5[index].unk_10 = seNo;
        switch (index) {
            case 0:
                D_801151F0_mstory5[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                if (func_80106B30_mstory5(0) == 0) {
                    D_801151F0_mstory5[index].unk_14 = CharFXPlay(seNo, 0);
                } else {
                    D_801151F0_mstory5[index].unk_14 = CharFXPlay(seNo, 1);
                }
                break;
            case 3:
                D_801151F0_mstory5[index].unk_14 = CharFXPlay(seNo, 7);
                break;
            case 1:
            case 4:
            case 5:
            case 6:
                break;
        }
    }
}

void func_8010F240_mstory5(s32 index) {
    if (D_801151F0_mstory5[index].unk_0C == 1) {
        D_801151F0_mstory5[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
            case 3:
                HuAudFXStop((s16)D_801151F0_mstory5[index].unk_14);
            case 1:
            case 4:
            case 5:
            case 6:
                break;
        }
    }
}

void func_8010F2BC_mstory5(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 9; i++) {
            if (D_801151F0_mstory5[i].unk_0C == 1 && Hu3DData[D_801151F0_mstory5[i].obj->model[1]].motTime == 0.0f) {
                seNo = D_801151F0_mstory5[i].unk_10;
                switch (i) {
                    case 0:
                        D_801151F0_mstory5[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                        break;
                    case 2:
                        if (func_80106B30_mstory5(0) == 0) {
                            D_801151F0_mstory5[i].unk_14 = CharFXPlay(seNo, 0);
                        } else {
                            D_801151F0_mstory5[i].unk_14 = CharFXPlay(seNo, 1);
                        }
                        break;
                    case 3:
                        D_801151F0_mstory5[i].unk_14 = CharFXPlay(seNo, 7);
                        break;
                    case 1:
                    case 4:
                    case 5:
                    case 6:
                        break;
                }
            }
        }
        HuPrcVSleep();
    }
}

void func_8010F41C_mstory5(omObjData *obj) {
    f32 step = 0.35f;
    f32 vol = 0.0f;
    s32 i;

    if (D_801151F0_mstory5[3].unk_0C == 1) {
        for (i = 0; i < 180; i++) {
            HuAudFXVolSet((s16)D_801151F0_mstory5[3].unk_14, (s32)vol + 64);
            vol += step;
            HuPrcVSleep();
        }
        HuAudFXVolSet((s16)D_801151F0_mstory5[3].unk_14, 127);
    }
    D_801152E0_mstory5.func = func_801085D8_mstory5;
}
