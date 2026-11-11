#include "common.h"
#include "game/hmfmath.h"
#include "overlays/minigame.h"

typedef struct UnkMstory2Obj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} UnkMstory2Obj; // sizeof 0x14

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern s32 D_800A178C_main[][6];

extern char *D_8011BA40_mstory2[];
extern char *D_8011BA60_mstory2[];

extern void (*const D_8011BDE0_mstory2[])(void);
extern const Vec D_8011BE74_mstory2;
extern const Vec D_8011BE80_mstory2;
extern const Vec D_8011BE8C_mstory2;
extern const Vec D_8011BE98_mstory2;
extern const Vec D_8011C000_mstory2;
extern const Vec D_8011C024_mstory2;
extern const Vec D_8011C03C_mstory2;
extern UnkMstory2Obj D_8011C680_mstory2[6];
extern Vec D_8011C704_mstory2;
extern Vec D_8011C710_mstory2;
extern Vec D_8011C71C_mstory2;
extern Vec D_8011C728_mstory2;
extern s16 D_8011C740_mstory2[3];
extern s16 D_8011C746_mstory2;
extern const Vec D_8011C030_mstory2;
extern s16 D_8011C748_mstory2;
extern s16 D_8011C75A_mstory2;
extern s16 D_8011C75C_mstory2;
extern s16 D_8011C75E_mstory2;
extern Vec D_8011B950_mstory2[];
extern Vec D_8011B980_mstory2[];
extern Vec D_8011B9C8_mstory2;
extern Vec D_8011B9D4_mstory2;
extern Vec D_8011B9E0_mstory2;
extern Vec D_8011BA1C_mstory2;
extern Vec D_8011BA28_mstory2;
extern Vec D_8011BA34_mstory2;
extern s16 D_8011C74E_mstory2;
extern s16 D_8011C750_mstory2;
extern s16 D_8011C74A_mstory2[3];
extern const Vec D_8011BFF4_mstory2;
extern s16 D_8011C752_mstory2[3];
extern const Vec D_8011C00C_mstory2;
extern s16 D_8011C756_mstory2;
extern s16 D_8011C758_mstory2;

void func_80105FBC_mstory2(void);
void func_80106D58_mstory2(s16 model, s16 arg1, s16 arg2);
void func_80106E48_mstory2(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_801070D8_mstory2(omObjData *obj, Vec *pos, s32 frames);
void func_801073A4_mstory2(omObjData *obj, f32 speed, s16 frames);
void func_801076DC_mstory2(omObjData *obj, omObjData *target);
void func_8010889C_mstory2(omObjData *);
void func_8010A290_mstory2(void);
void func_8010B108_mstory2(void);
void func_8010A61C_mstory2(omObjData *);
void func_8010BCE4_mstory2(omObjData *obj);
void func_8010A5FC_mstory2(omObjData *obj);
void func_8010BF7C_mstory2(omObjData *obj);
void func_80108AB0_mstory2(omObjData *);
void func_80108C40_mstory2(omObjData *);
void func_80107824_mstory2(omObjData *obj, Vec *target, s32 frames, s32 faceDir);
void func_8010A298_mstory2(omObjData *obj);
void func_8010A3B4_mstory2(omObjData *obj);
void func_8010A784_mstory2(omObjData *obj);
void func_8010A9F0_mstory2(omObjData *obj);
void func_8010B110_mstory2(omObjData *obj);
void func_8010B200_mstory2(omObjData *obj);
void func_8010B46C_mstory2(omObjData *obj);
void func_8010B688_mstory2(omObjData *obj);
void func_8010B738_mstory2(omObjData *obj);
void func_8010BACC_mstory2(omObjData *obj);
void func_8010BD04_mstory2(omObjData *obj);
void func_8010BDC4_mstory2(omObjData *obj);
void func_8010C018_mstory2(omObjData *obj);
void func_8010C328_mstory2(omObjData *obj);
void func_8010C348_mstory2(omObjData *obj);
void func_80109D04_mstory2(void);
void func_8010AC1C_mstory2(void);
void func_8010B7B8_mstory2(void);
void func_8010BAC4_mstory2(void);
void func_8010C038_mstory2(void);
void func_8010C398_mstory2(void);
void func_80108A3C_mstory2(void);
void func_8010C1E4_mstory2(void);
void func_801088A4_mstory2(void);
void func_8010C1DC_mstory2(void);
void func_8010C508_mstory2(void);
void func_80105EA4_mstory2(void);
void func_801060A4_mstory2(void);
void func_801060D4_mstory2(void);
void func_801060F8_mstory2(s32 mess);
void func_8010614C_mstory2(s32 mess);
void func_8010622C_mstory2(void);
void func_80106E2C_mstory2(omObjData *obj, Vec *pos, s32 frames);
void func_801072AC_mstory2(s16 model);

const Vec D_8011BE68_mstory2 = { -120.0f, 0.0f, 480.0f };

MstoryPath *func_80107B90_mstory2(Vec *points, s32 flags) {
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

void func_80107E94_mstory2(MstoryPath *path, f32 time, Vec *result) {
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

void func_8010873C_mstory2(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010876C_mstory2(void) {
    D_8011C75C_mstory2 = GwStory.unk1;
    if (D_8011C75C_mstory2 == 4) {
        D_8011C75E_mstory2 = 1;
    } else {
        D_8011C75E_mstory2 = 4;
    }
    func_80105FBC_mstory2();
    D_8011C75A_mstory2 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80109D04_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010AC1C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010B7B8_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C038_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C398_mstory2, 0x1001, 0x1000, 0);
    HuPrcVSleep();
    omAddPrcObj(func_80108A3C_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010C1E4_mstory2, 0x1001, 0x1000, 0);
    omAddPrcObj(func_801088A4_mstory2, 0x1001, 0x1000, 0);
    func_8001C258_main(D_8011C75A_mstory2, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8010889C_mstory2(omObjData *obj) {
}

void func_801088A4_mstory2(void) {
    s16 seNo;
    s8 vol;
    f32 z;

    while (TRUE) {
        if (D_8011C680_mstory2[0].unk_0C == 1 && Hu3DData[D_8011C680_mstory2[0].obj->model[1]].motTime == 0.0f) {
            CharFXPlay((s16)D_8011C680_mstory2[0].unk_10, D_8011C75C_mstory2);
        }
        if (D_8011C680_mstory2[1].unk_0C == 1 && Hu3DData[D_8011C680_mstory2[1].obj->model[1]].motTime == 0.0f) {
            seNo = CharFXPlay((s16)D_8011C680_mstory2[1].unk_10, D_8011C75E_mstory2);
            z = Hu3DData[D_8011C680_mstory2[1].obj->model[1]].pos.z;
            if (z <= 0.0f) {
                vol = z / 15.0f + 127.0f;
            } else {
                vol = 127;
            }
            HuAudFXVolSet(seNo, vol);
        }
        HuPrcVSleep();
    }
}

void func_80108A3C_mstory2(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_8011C680_mstory2[5].obj = obj;
    D_8011C680_mstory2[5].unk_08 = 0;
    D_8011C680_mstory2[5].func = func_80108AB0_mstory2;

    for (;;) {
        D_8011C680_mstory2[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BE74_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BE80_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BE8C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BE98_mstory2);

void func_80108AB0_mstory2(omObjData *obj) {
    Vec pos[4] = {
        { 20.0f, -20.0f, 0.0f },
        { 0.0f, 225.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 300.0f, 0.0f },
    };

    HuPrcSleep(40);
    func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &pos[0], 10);
    func_801070D8_mstory2(D_8011C680_mstory2[2].obj, &pos[1], 10);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(D_8011C680_mstory2[3].obj->model[1], Hu3DData[D_8011C680_mstory2[3].obj->motion[1]].motId, 0, 10, 2);
    func_801060A4_mstory2();
    if (D_8011C75C_mstory2 != 4) {
        func_8010614C_mstory2(0x5A0F);
    } else {
        func_801060F8_mstory2(0x5B00);
    }
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011C680_mstory2[3].obj->model[1], Hu3DData[D_8011C680_mstory2[3].obj->motion[0]].motId, 0, 10, 2);
    func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &pos[2], 10);
    func_801070D8_mstory2(D_8011C680_mstory2[2].obj, &pos[3], 10);
    D_8011C680_mstory2[5].func = func_80108C40_mstory2;
}

void func_80108C40_mstory2(omObjData *obj) {
    Vec cur;
    MstoryPath *paths[2];
    s16 j = 0;
    Vec pos[6] = {
        { 150.0f, 0.0f, 384.0f },
        { 0.0f, 200.0f, 300.0f },
        { 0.0f, 200.0f, 150.0f },
        { 300.0f, 25.0f, 400.0f },
        { 300.0f, 125.0f, 400.0f },
        { 238.0f, 100.0f, 214.0f },
    };
    s16 i;
    f32 t;
    s32 frames;

    func_8001C258_main(D_8011C680_mstory2[4].obj->model[1], 4, 0);
    func_8001C258_main(D_8011C680_mstory2[4].obj->model[2], 4, 0);
    func_800138EC_main(D_8011C680_mstory2[4].obj->model[2], 1, 1);
    HuAudFXPlay(0x215);
    paths[0] = func_80107B90_mstory2(D_8011B950_mstory2, 0);
    for (i = 0; i < 40.0f; i++) {
        if (i == 30) {
            Hu3DMotionShiftSet(D_8011C680_mstory2[0].obj->model[1], Hu3DData[D_8011C680_mstory2[0].obj->motion[9]].motId, 0, 10, 2);
        }
        t = i * 0.025f;
        func_80107E94_mstory2(paths[0], t * t, &cur);
        Hu3DModelPosSet(D_8011C680_mstory2[4].obj->model[1], cur.x, cur.y, cur.z);
        func_8000CFA4_main(D_8011C680_mstory2[4].obj->model[2], cur.x, cur.y - 40.0f, cur.z);
        HuPrcVSleep();
    }
    func_8010873C_mstory2(paths[0]);
    D_8011C680_mstory2[0].func = func_8010A298_mstory2;
    while (TRUE) {
        if (D_8011C680_mstory2[0].unk_08 == 1) {
            cur.x -= 0.19999999f;
            cur.y -= 2.0f;
            cur.z += 1.0f;
            Hu3DModelPosSet(D_8011C680_mstory2[4].obj->model[1], cur.x, cur.y, cur.z);
            func_8000CFA4_main(D_8011C680_mstory2[4].obj->model[2], cur.x, cur.y - 40.0f, cur.z);
            if (j++ == 30.0f) {
                j = 0;
                break;
            }
        }
        HuPrcVSleep();
    }
    HuAudFXVolSet(CharFXPlay(0x2BD, D_8011C75E_mstory2), 80);
    if (D_8011C75C_mstory2 != 4) {
        func_801060A4_mstory2();
        func_801060F8_mstory2(0x5A11);
        func_801060D4_mstory2();
    } else {
        HuPrcSleep(30);
    }
    func_8001C258_main(D_8011C680_mstory2[1].obj->model[1], 4, 0);
    func_8001C258_main(D_8011C680_mstory2[1].obj->model[2], 4, 0);
    func_8010622C_mstory2();
    HuPrcSleep(10);
    D_8011C680_mstory2[0].func = func_8010A3B4_mstory2;
    D_8011C680_mstory2[2].func = func_8010BACC_mstory2;
    while (TRUE) {
        cur.x += 1.0f;
        cur.y += 10.0f;
        cur.z -= 5.0f;
        Hu3DModelPosSet(D_8011C680_mstory2[4].obj->model[1], cur.x, cur.y, cur.z);
        func_8000CFA4_main(D_8011C680_mstory2[4].obj->model[2], cur.x, cur.y - 40.0f, cur.z);
        if (j++ == 6.0f) {
            break;
        }
        HuPrcVSleep();
    }
    D_8011B980_mstory2[0].x = cur.x;
    D_8011B980_mstory2[0].y = cur.y;
    D_8011B980_mstory2[0].z = cur.z;
    func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &D_8011B9C8_mstory2, 5);
    D_8011C680_mstory2[3].func = func_8010C328_mstory2;
    while (TRUE) {
        if (D_8011C680_mstory2[2].unk_08 == 5) {
            break;
        }
        HuPrcVSleep();
    }
    func_801072AC_mstory2(D_8011C680_mstory2[1].obj->model[1]);
    HuPrcSleep(30);
    D_8011C680_mstory2[1].unk_0C = 1;
    D_8011C680_mstory2[1].unk_10 = 40;
    Hu3DMotionSpeedSet(D_8011C680_mstory2[0].obj->model[1], 0.25f);
    Hu3DMotionShiftSet(D_8011C680_mstory2[0].obj->model[1], Hu3DData[D_8011C680_mstory2[0].obj->motion[10]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[2]].motId, 0, 10, 2);
    func_80107824_mstory2(D_8011C680_mstory2[1].obj, &pos[0], 180, 1);
    D_8011C680_mstory2[1].unk_0C = 0;
    Hu3DMotionShiftSet(D_8011C680_mstory2[0].obj->model[1], Hu3DData[D_8011C680_mstory2[0].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionSpeedSet(D_8011C680_mstory2[0].obj->model[1], 1.0f);
    func_80106D58_mstory2(D_8011C680_mstory2[2].obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[3]].motId, 0, 10, 2);
    HuPrcSleep(60);
    func_80106D58_mstory2(D_8011C680_mstory2[2].obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[0]].motId, 0, 10, 2);
    func_801070D8_mstory2(D_8011C680_mstory2[1].obj, &D_8011B9D4_mstory2, 5);
    if (D_8011C75C_mstory2 != 4) {
        D_8011C680_mstory2[1].func = func_8010B688_mstory2;
        func_801060A4_mstory2();
        func_801060F8_mstory2(0x5A12);
        func_801060D4_mstory2();
        func_80106D58_mstory2(D_8011C680_mstory2[2].obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
        D_8011C680_mstory2[1].func = func_8010889C_mstory2;
    } else {
        for (i = 0; i < 2; i++) {
            func_80106E48_mstory2(D_8011C680_mstory2[2].obj, &pos[3], 15, 0);
            Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[1]].motId, 0, 10, 2);
            func_801070D8_mstory2(D_8011C680_mstory2[1].obj, &D_8011BA1C_mstory2, 10);
            Hu3DMotionShiftSet(D_8011C680_mstory2[0].obj->model[1], Hu3DData[D_8011C680_mstory2[0].obj->motion[0]].motId, 0, 10, 2);
            Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[5]].motId, 0, 10, 0);
            HuPrcSleep(10);
            Hu3DMotionShiftSet(D_8011C680_mstory2[2].obj->model[1], Hu3DData[D_8011C680_mstory2[2].obj->motion[2]].motId, 0, 10, 2);
            func_801072AC_mstory2(D_8011C680_mstory2[1].obj->model[1]);
            if (i == 0) {
                Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[5]].motId, 0, 10, 0);
                func_801072AC_mstory2(D_8011C680_mstory2[1].obj->model[1]);
            }
            Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[0]].motId, 0, 10, 2);
            Hu3DMotionShiftSet(D_8011C680_mstory2[2].obj->model[1], Hu3DData[D_8011C680_mstory2[2].obj->motion[0]].motId, 0, 10, 2);
            D_8011C680_mstory2[2].func = func_8010889C_mstory2;
            func_80106E2C_mstory2(D_8011C680_mstory2[2].obj, &pos[4], 8);
            func_801070D8_mstory2(D_8011C680_mstory2[2].obj, &D_8011B9E0_mstory2, 10);
            Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[1]].motId, 0, 10, 2);
            func_801070D8_mstory2(D_8011C680_mstory2[1].obj, &D_8011B9D4_mstory2, 5);
            Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[0]].motId, 0, 10, 2);
            D_8011C680_mstory2[3].func = func_8010889C_mstory2;
            D_8011C680_mstory2[0].func = func_8010889C_mstory2;
            func_801070D8_mstory2(D_8011C680_mstory2[3].obj, &D_8011BA28_mstory2, 5);
            func_801070D8_mstory2(D_8011C680_mstory2[0].obj, &D_8011BA34_mstory2, 5);
            func_801060A4_mstory2();
            D_8011C680_mstory2[1].func = func_8010B738_mstory2;
            func_801060F8_mstory2(i + 0x5B01);
            func_801060D4_mstory2();
            Hu3DMotionShiftSet(D_8011C680_mstory2[0].obj->model[1], Hu3DData[D_8011C680_mstory2[0].obj->motion[8]].motId, 0, 10, 0);
            func_801072AC_mstory2(D_8011C680_mstory2[0].obj->model[1]);
        }
    }
    func_801072AC_mstory2(D_8011C680_mstory2[1].obj->model[1]);
    Hu3DMotionShiftSet(D_8011C680_mstory2[0].obj->model[1], Hu3DData[D_8011C680_mstory2[0].obj->motion[0]].motId, 0, 10, 2);
    D_8011C680_mstory2[1].func = func_8010B110_mstory2;
    D_8011C680_mstory2[2].func = func_8010BD04_mstory2;
    D_8011C680_mstory2[3].func = func_8010C348_mstory2;
    paths[1] = func_80107B90_mstory2(D_8011B980_mstory2, 0);
    for (i = 0; i < 50.0f; i++) {
        t = i * 0.02f;
        func_80107E94_mstory2(paths[1], t * t, &cur);
        Hu3DModelPosSet(D_8011C680_mstory2[4].obj->model[1], cur.x, cur.y, cur.z);
        func_8000CFA4_main(D_8011C680_mstory2[4].obj->model[2], cur.x, cur.y - 40.0f, cur.z);
        HuPrcVSleep();
    }
    func_8010873C_mstory2(paths[1]);
    func_8001C258_main(D_8011C680_mstory2[4].obj->model[1], 4, 4);
    func_8001C258_main(D_8011C680_mstory2[4].obj->model[2], 4, 4);
    func_800138EC_main(D_8011C680_mstory2[4].obj->model[2], 1, 0);
    HuPrcSleep(5);
    func_80106D58_mstory2(D_8011C680_mstory2[2].obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[2]);
    Hu3DMotionShiftSet(D_8011C680_mstory2[2].obj->model[1], Hu3DData[D_8011C680_mstory2[2].obj->motion[1]].motId, 0, 10, 2);
    if (D_8011C75C_mstory2 == 4) {
        D_8011C680_mstory2[2].func = func_8010C018_mstory2;
        HuPrcSleep(10);
        func_80106E2C_mstory2(D_8011C680_mstory2[2].obj, &pos[5], 60);
        frames = 30;
    } else {
        frames = 60;
    }
    HuPrcSleep(frames);
    D_8011C748_mstory2 = 1;
    pos[2].y = pos[1].y = Hu3DData[D_8011C680_mstory2[3].obj->model[1]].pos.y;
    func_80106E2C_mstory2(D_8011C680_mstory2[3].obj, &pos[1], 3);
    HuAudFXPlay(0x217);
    D_8011C680_mstory2[2].func = func_8010BDC4_mstory2;
    D_8011C680_mstory2[0].func = func_8010A784_mstory2;
    D_8011C680_mstory2[1].func = func_8010B200_mstory2;
    func_8004AC98_main(D_8011C75C_mstory2 + 0x2AC, 0);
    func_8004AC98_main(D_8011C75E_mstory2 + 0x2AC, 1);
    D_8011C748_mstory2 = 0;
    func_80106E48_mstory2(D_8011C680_mstory2[3].obj, &pos[2], 5, 0);
    while (TRUE) {
        if (D_8011C680_mstory2[2].unk_08 == 1) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    Hu3DMotionShiftSet(D_8011C680_mstory2[3].obj->model[1], Hu3DData[D_8011C680_mstory2[3].obj->motion[1]].motId, 0, 10, 2);
    func_801060A4_mstory2();
    func_801060F8_mstory2(D_8011C75C_mstory2 != 4 ? 0x5A13 : 0x5B03);
    func_801060D4_mstory2();
    Hu3DMotionShiftSet(D_8011C680_mstory2[3].obj->model[1], Hu3DData[D_8011C680_mstory2[3].obj->motion[0]].motId, 0, 10, 2);
    D_8011C680_mstory2[0].func = func_8010A9F0_mstory2;
    D_8011C680_mstory2[1].func = func_8010B46C_mstory2;
    while (TRUE) {
        if (D_8011C680_mstory2[0].unk_08 == 10 && D_8011C680_mstory2[1].unk_08 == 10) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    func_80105EA4_mstory2();
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
    D_8011C680_mstory2[3].func = func_8010889C_mstory2;
    D_8011C680_mstory2[2].func = func_8010889C_mstory2;
    D_8011C680_mstory2[4].func = func_8010889C_mstory2;
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
    D_8011C680_mstory2[5].func = func_8010889C_mstory2;
}

void func_80109D04_mstory2(void) {
    s32 motIds[8][3] = {
        { 0x40, 0x3E, 0x42 },
        { 0x4B, 0x48, 0x4D },
        { 0x54, 0x52, 0x56 },
        { 0x5D, 0x5B, 0x5F },
        { 0x67, 0x65, 0x69 },
        { 0x70, 0x6E, 0x72 },
        { 0x4B, 0x48, 0x4D },
        { 0x54, 0x52, 0x56 },
    };
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 20, 20, -1, NULL);
    D_8011C680_mstory2[0].obj = obj;
    D_8011C680_mstory2[0].unk_08 = 0;
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
    D_8011C680_mstory2[0].unk_0C = 0;
    D_8011C680_mstory2[0].unk_10 = 31;
    obj->model[1] = func_8000B108_main(D_800A178C_main[D_8011C75C_mstory2][0] | D_800A178C_main[D_8011C75C_mstory2][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    obj->model[4] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(D_8011C75C_mstory2, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(D_8011C75C_mstory2, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(D_8011C75C_mstory2, 2));
    func_8000B460_main(obj, 3, motIds[D_8011C75C_mstory2][0] | 0x1D0000);
    func_8000B460_main(obj, 4, motIds[D_8011C75C_mstory2][1] | 0x1D0000);
    func_8000B460_main(obj, 5, func_80017BB8_main(D_8011C75C_mstory2, 0x72));
    func_8000B460_main(obj, 6, func_80017BB8_main(D_8011C75C_mstory2, 0x21));
    func_8000B460_main(obj, 7, func_80017BB8_main(D_8011C75C_mstory2, 0x33));
    func_8000B460_main(obj, 8, motIds[D_8011C75C_mstory2][2] | 0x1D0000);
    func_8000B460_main(obj, 9, func_80017BB8_main(D_8011C75C_mstory2, 0x9B));
    func_8000B460_main(obj, 10, func_80017BB8_main(D_8011C75C_mstory2, 0x9C));
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    Hu3DModelPosSet(obj->model[1], -120.0f, 0.0f, 480.0f);
    Hu3DModelPosSet(obj->model[2], -120.0f, -5.0f, 480.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, 162.4f, 0.0f);
    if (D_8011C75C_mstory2 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    data = DataRead(func_80017BB8_main(D_8011C75C_mstory2, 0xA4));
    D_8011C74A_mstory2[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_8011BA40_mstory2[D_8011C75C_mstory2]);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C74A_mstory2[0], 1, 0);
    Hu3DAnimBankSet(D_8011C74A_mstory2[0], 0);
    D_8011C750_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C74A_mstory2[0], 0, D_8011BA40_mstory2[D_8011C75C_mstory2]);
    data = DataRead(func_80017BB8_main(D_8011C75C_mstory2, 0xA9));
    D_8011C74A_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C750_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C74A_mstory2[0], 0, D_8011BA40_mstory2[D_8011C75C_mstory2]);
    data = DataRead(func_80017BB8_main(D_8011C75C_mstory2, 0xAA));
    D_8011C74A_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[0]);
    omPrcSetDestructor(0, func_8010A290_mstory2);
    while (TRUE) {
        D_8011C680_mstory2[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A290_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BF88_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BF94_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFA0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFAC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFB8_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFC4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFD0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFDC_mstory2);

const char D_8011BFE8_mstory2[] = "item_hook";

void func_8010A298_mstory2(omObjData *obj) {
    s16 model = obj->model[1];

    HuPrcSleep(20);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], obj->model[1], D_8011BFE8_mstory2);
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_801072AC_mstory2(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_801072AC_mstory2(model);
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
    D_8011C680_mstory2[0].unk_08 = 1;
}

void func_8010A3B4_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    f32 time;

    func_8001C5B4_main(model, obj->motion[4]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionSpeedSet(model, 2.0f);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    func_8001C5B4_main(model, obj->motion[3]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionSpeedSet(model, 1.0f);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    D_8011C680_mstory2[0].func = func_8010A5FC_mstory2;
}

void func_8010A5FC_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

void func_8010A61C_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    D_8011C680_mstory2[0].unk_0C = 1;
    D_8011C680_mstory2[0].unk_10 = 31;
    func_801073A4_mstory2(obj, 3.5f, 15);
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74E_mstory2);
    func_80106D58_mstory2(D_8011C680_mstory2[1].obj->model[1], D_8011C758_mstory2, D_8011C756_mstory2);
    D_8011C680_mstory2[0].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[4]].motId, 0, 10, 2);
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

void func_8010A784_mstory2(omObjData *obj) {
    Vec pos = D_8011BFF4_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x - 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[4], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[4], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80106E2C_mstory2(obj, &target, 10);
    func_801072AC_mstory2(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C750_mstory2, D_8011C74A_mstory2[0]);
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

void func_8010A9F0_mstory2(omObjData *obj) {
    Vec pos = D_8011C000_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C680_mstory2[2].func = func_8010BF7C_mstory2;
    func_8004AC98_main(D_8011C75C_mstory2 + 0x275, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C680_mstory2[0].unk_08 = 10;
    while (TRUE) {
        if (D_8011C680_mstory2[1].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    D_8011C680_mstory2[0].unk_0C = 1;
    D_8011C680_mstory2[0].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &target, 60);
    D_8011C680_mstory2[0].unk_0C = 0;
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

void func_8010AC1C_mstory2(void) {
    s16 chrs[2] = { 4, 1 };
    s32 motIds[2] = { 0x61, 0x44 };
    omObjData *obj;
    s16 idx;
    void *data;

    idx = D_8011C75C_mstory2 == 4;
    obj = omAddObj(20, 20, 20, -1, NULL);
    D_8011C680_mstory2[1].obj = obj;
    D_8011C680_mstory2[1].unk_08 = 0;
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
    D_8011C680_mstory2[1].unk_0C = 0;
    D_8011C680_mstory2[1].unk_10 = 31;
    obj->model[1] = func_8000B108_main(idx == 0 ? 0x500A0 : 0x300A0, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    obj->model[3] = func_8000B108_main(0x83, 0x2B9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chrs[idx], 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chrs[idx], 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(chrs[idx], 2));
    func_8000B460_main(obj, 3, func_80017BB8_main(chrs[idx], 0x13));
    func_8000B460_main(obj, 4, func_80017BB8_main(chrs[idx], 0x72));
    func_8000B460_main(obj, 5, motIds[idx] | 0x1D0000);
    func_8000B460_main(obj, 6, func_80017BB8_main(chrs[idx], 0x21));
    func_8000B460_main(obj, 7, func_80017BB8_main(chrs[idx], 0x33));
    func_8000B460_main(obj, 8, func_80017BB8_main(chrs[idx], 0x2F));
    if (D_8011C75C_mstory2 == 4) {
        func_8000B460_main(obj, 9, 0x1D0045);
    }
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C704_mstory2 = D_8011BE74_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C704_mstory2.x, D_8011C704_mstory2.y, D_8011C704_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C704_mstory2.x, D_8011C704_mstory2.y - -5.0f, D_8011C704_mstory2.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, -14.48f, 0.0f);
    data = DataRead(func_80017BB8_main(chrs[idx], 0xA4));
    D_8011C752_mstory2[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_8011BA60_mstory2[idx]);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C752_mstory2[0], 1, 0);
    Hu3DAnimBankSet(D_8011C752_mstory2[0], 0);
    D_8011C758_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C752_mstory2[0], 0, D_8011BA60_mstory2[idx]);
    data = DataRead(func_80017BB8_main(chrs[idx], 0xA9));
    D_8011C752_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C758_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C752_mstory2[0], 0, D_8011BA60_mstory2[idx]);
    data = DataRead(func_80017BB8_main(chrs[idx], 0xAA));
    D_8011C752_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C758_mstory2, D_8011C752_mstory2[0]);
    omPrcSetDestructor(0, func_8010B108_mstory2);
    while (TRUE) {
        D_8011C680_mstory2[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8010B108_mstory2(void) {
}

void func_8010B110_mstory2(omObjData *obj) {
    D_8011C680_mstory2[1].unk_0C = 1;
    D_8011C680_mstory2[1].unk_10 = 31;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801073A4_mstory2(obj, 4.5f, 15);
    D_8011C680_mstory2[1].unk_0C = 0;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
    D_8011C680_mstory2[0].func = func_8010A61C_mstory2;
}

void func_8010B200_mstory2(omObjData *obj) {
    Vec pos = D_8011C00C_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x + 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    func_80106D58_mstory2(obj->model[1], D_8011C758_mstory2, D_8011C752_mstory2[1]);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[3], 4, 0);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    func_80106E2C_mstory2(obj, &target, 10);
    func_801072AC_mstory2(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80106D58_mstory2(obj->model[1], D_8011C758_mstory2, D_8011C752_mstory2[0]);
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
}

void func_8010B46C_mstory2(omObjData *obj) {
    Vec pos = D_8011C000_mstory2;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 1200.0f;
    target = tmp;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_801070D8_mstory2(obj, &pos, 10);
    func_8004AC98_main(D_8011C75E_mstory2 + 0x275, 1);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[7]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C680_mstory2[1].unk_08 = 10;
    while (TRUE) {
        if (D_8011C680_mstory2[0].unk_08 != 10) {
            HuPrcVSleep();
        } else {
            break;
        }
    }
    D_8011C680_mstory2[1].unk_0C = 1;
    D_8011C680_mstory2[1].unk_10 = 40;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    HuPrcSleep(10);
    func_80106E2C_mstory2(obj, &target, 60);
    D_8011C680_mstory2[1].unk_0C = 0;
    D_8011C680_mstory2[0].func = func_8010889C_mstory2;
}

void func_8010B688_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[5]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
}

void func_8010B738_mstory2(omObjData *obj) {
    Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[9]].motId, 0, 10, 0);
    func_801072AC_mstory2(obj->model[1]);
    D_8011C680_mstory2[1].func = func_8010889C_mstory2;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011BFF4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011C000_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011C00C_mstory2);

const char D_8011C018_mstory2[] = "c204n_0_DEF";

void func_8010B7B8_mstory2(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    D_8011C680_mstory2[2].obj = obj;
    D_8011C680_mstory2[2].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C710_mstory2 = D_8011BE80_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C710_mstory2.x, D_8011C710_mstory2.y, D_8011C710_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C710_mstory2.x, -5.0f, D_8011C710_mstory2.z);
    Hu3DModelRotSet(obj->model[1], 20.0f, 320.0f, 0.0f);
    data = DataRead(0xA007E);
    D_8011C740_mstory2[0] = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_8011C018_mstory2);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011C740_mstory2[0], 1, 0);
    Hu3DAnimBankSet(D_8011C740_mstory2[0], 0);
    D_8011C746_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C740_mstory2[0], 0, D_8011C018_mstory2);
    data = DataRead(0xA0083);
    D_8011C740_mstory2[1] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    D_8011C746_mstory2 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011C740_mstory2[0], 0, D_8011C018_mstory2);
    data = DataRead(0xA0080);
    D_8011C740_mstory2[2] = func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106D58_mstory2(obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    omPrcSetDestructor(0, func_8010BAC4_mstory2);
    D_8011C680_mstory2[2].func = func_8010889C_mstory2;
    while (TRUE) {
        D_8011C680_mstory2[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010BAC4_mstory2(void) {
}

void func_8010BACC_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_8011C024_mstory2;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C746_mstory2, D_8011C740_mstory2[1]);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_801070D8_mstory2(obj, &target, 5);
    func_80106D58_mstory2(model, D_8011C746_mstory2, D_8011C740_mstory2[0]);
    Hu3DMotionShiftSet(D_8011C680_mstory2[1].obj->model[1], Hu3DData[D_8011C680_mstory2[1].obj->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(D_8011C75C_mstory2 != 4 ? 30 : 35);
    HuAudFXVolSet(CharFXPlay(0x28F, D_8011C75E_mstory2), 0x60);
    D_8011C680_mstory2[2].func = func_8010BCE4_mstory2;
    D_8011C680_mstory2[2].unk_08 = 5;
}

void func_8010BCE4_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

void func_8010BD04_mstory2(omObjData *obj) {
    while (TRUE) {
        if (Hu3DData[obj->model[1]].pos.y > 100.0f) {
            Hu3DData[obj->model[1]].pos.y -= 2.0f;
            HuPrcVSleep();
        } else {
            break;
        }
    }
    Hu3DData[obj->model[1]].pos.y = 100.0f;
    D_8011C680_mstory2[2].func = func_8010889C_mstory2;
}

void func_8010BDC4_mstory2(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_8011C030_mstory2;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80106D58_mstory2(model, D_8011C746_mstory2, D_8011C740_mstory2[1]);
    Hu3DMotionShiftSet(D_8011C680_mstory2[2].obj->model[1], Hu3DData[D_8011C680_mstory2[2].obj->motion[0]].motId, 0, 10, 2);
    for (i = 0; i < 15; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    func_801070D8_mstory2(obj, &target, 10);
    D_8011C680_mstory2[2].func = func_8010889C_mstory2;
    D_8011C680_mstory2[2].unk_08 = 1;
}

void func_8010BF7C_mstory2(omObjData *obj) {
    Vec pos = D_8011C03C_mstory2;

    func_80106D58_mstory2(obj->model[1], D_8011C746_mstory2, D_8011C740_mstory2[0]);
    func_801070D8_mstory2(obj, &pos, 10);
    while (TRUE) {
        func_801076DC_mstory2(D_8011C680_mstory2[2].obj, D_8011C680_mstory2[0].obj);
        HuPrcVSleep();
    }
}

void func_8010C018_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[0].obj);
}

void func_8010C038_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    D_8011C680_mstory2[3].obj = obj;
    D_8011C680_mstory2[3].unk_08 = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011C75A_mstory2);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C71C_mstory2 = D_8011BE8C_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C71C_mstory2.x, D_8011C71C_mstory2.y, D_8011C71C_mstory2.z);
    Hu3DModelPosSet(obj->model[2], D_8011C71C_mstory2.x, -5.0f, D_8011C71C_mstory2.z);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    omPrcSetDestructor(0, func_8010C1DC_mstory2);
    D_8011C680_mstory2[3].func = func_8010889C_mstory2;
    while (1) {
        D_8011C680_mstory2[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C1DC_mstory2(void) {
}

void func_8010C1E4_mstory2(void) {
    f32 angle = 0.0f;
    omObjData *obj = D_8011C680_mstory2[3].obj;
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
        if (D_8011C748_mstory2 != 1) {
            Hu3DModelPosSet(obj->model[1], pos.x, ofs + pos.y, pos.z);
        }
        HuPrcVSleep();
    }
}

void func_8010C328_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

void func_8010C348_mstory2(omObjData *obj) {
    Vec pos = D_8011C000_mstory2;

    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C680_mstory2[3].func = func_8010889C_mstory2;
}

void func_8010C398_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 20, 20, -1, NULL);
    D_8011C680_mstory2[4].obj = obj;
    D_8011C680_mstory2[4].unk_08 = 0;
    D_8011C680_mstory2[4].func = func_8010889C_mstory2;
    obj->model[1] = func_8000B108_main(0x1D0003, 0x20299);
    obj->model[2] = func_8000CED8_main(0xB0004, 0x6A9);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C814_main(obj->model[1], 2, 2);
    D_8011C728_mstory2 = D_8011BE98_mstory2;
    Hu3DModelPosSet(obj->model[1], D_8011C728_mstory2.x, D_8011C728_mstory2.y, D_8011C728_mstory2.z);
    func_8000CD00_main(obj->model[2], 4.0f, 20.0f, 4.0f);
    func_8000D018_main(obj->model[2], 60.0f);
    func_800138EC_main(obj->model[2], 1, 0);
    func_8001C258_main(obj->model[2], 4, 4);
    omPrcSetDestructor(0, func_8010C508_mstory2);
    while (1) {
        D_8011C680_mstory2[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C508_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011C024_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011C030_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49DF30", D_8011C03C_mstory2);
