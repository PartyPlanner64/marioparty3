#include "common.h"

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

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;

extern Vec D_80114A8C_mstory1;
extern Vec D_80114A98_mstory1;
extern Vec D_80114AA4_mstory1;

extern s32 D_80114A80_mstory1;
extern s32 D_80114A84_mstory1;
extern s8 D_80114A88_mstory1;
extern s32 D_80114AB0_mstory1;
extern s32 D_80114AC0_mstory1;
extern const Vec D_80114CEC_mstory1;
extern Vec D_80114E40_mstory1;
extern Vec D_80114E4C_mstory1;
extern Vec D_80114F00_mstory1;
extern Vec D_80114F0C_mstory1;
extern Vec D_80114F84_mstory1;
extern Vec D_80114F90_mstory1;
extern Vec D_80114F9C_mstory1;
extern Vec D_80114FA8_mstory1;
extern Vec D_80114FB4_mstory1;
extern Vec D_80114FC0_mstory1;
extern Vec D_80114FCC_mstory1;
extern Vec D_80114FD8_mstory1;
extern Vec D_80114FE4_mstory1;
extern Vec D_80114FF0_mstory1;
extern Vec D_80114FFC_mstory1;
extern Vec D_80115008_mstory1;
extern Vec D_80115038_mstory1;
extern Vec D_80115050_mstory1;
extern s16 D_801158B0_mstory1;
extern s16 D_801158B2_mstory1;
extern u16 D_801158B8_mstory1;
extern s32 D_801158B4_mstory1;
extern s32 D_801158E4_mstory1;
extern UnkStoryObj D_801158F0_mstory1[8];
extern Vec D_801159C8_mstory1;
extern const Vec D_80114CC8_mstory1;
extern Vec D_801159D4_mstory1;
extern const Vec D_80114CD4_mstory1;
extern Vec D_801159EC_mstory1;
extern s16 D_80115A10_mstory1;
extern s16 D_80115A1E_mstory1;
extern s16 D_80115A22_mstory1;
extern s16 D_80115A26_mstory1;
extern s16 D_80115A28_mstory1;
extern Vec D_80114E64_mstory1;
extern Vec D_80114E7C_mstory1;
extern Vec D_80114E94_mstory1;
extern Vec D_80114EA0_mstory1;
extern Vec D_80114EAC_mstory1;
extern Vec D_80114EB8_mstory1;
extern Vec D_80114EC4_mstory1;
extern Vec D_80114ED0_mstory1;
extern Vec D_80114EDC_mstory1;
extern Vec D_80114EE8_mstory1;
extern s32 D_80115A1C_mstory1[3];
extern Vec D_801159BC_mstory1;
extern const Vec D_80114CBC_mstory1;
extern Vec D_80115A04_mstory1;
extern const Vec D_80114D04_mstory1;
extern s16 D_80115A12_mstory1;
extern s16 D_80115A14_mstory1[4];
extern Vec D_801159B0_mstory1;
extern const Vec D_80114CB0_mstory1;
extern const s32 D_80114D10_mstory1[];
extern const s32 D_80114D30_mstory1[];
extern const s32 D_80114D50_mstory1[];
extern const s32 D_80114D70_mstory1[];
extern s32 D_800A178C_main[][6];
extern Vec D_80114AC4_mstory1[];
extern Vec D_80114AF4_mstory1[];
extern const s32 D_8011505C_mstory1[];
extern Vec D_801159E0_mstory1;
extern const Vec D_80114CE0_mstory1;
extern Vec D_801159F8_mstory1;
extern const Vec D_80114CF8_mstory1;

void func_80105FF4_mstory1(void);
void func_80106B14_mstory1(omObjData *obj, const Vec *pos, s32 frames);
void func_80106B30_mstory1(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_80106D80_mstory1(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_8010704C_mstory1(omObjData *obj, const Vec *pos, s32 frames);
s32 func_8010726C_mstory1(s16 model);
void func_801081D8_mstory1(omObjData *obj);
MstoryPath *func_801074C0_mstory1(Vec *points, s32 flags);
void func_801077C4_mstory1(MstoryPath *path, f32 t, Vec *out);
void func_8010806C_mstory1(MstoryPath *path);
void func_80109C20_mstory1(void);
void func_80109FD0_mstory1(void);
void func_80109C28_mstory1(omObjData *obj);
void func_80109478_mstory1(omObjData *obj);
void func_8010BB08_mstory1(s32 index, s32 seNo);
void func_8010BBEC_mstory1(s32 index);
void func_80106984_mstory1(void);
void func_801081E0_mstory1(void);
void func_80109140_mstory1(void);
void func_80109470_mstory1(void);
void func_801085F0_mstory1(void);
void func_801085F8_mstory1(omObjData *obj);
void func_80109014_mstory1(omObjData *obj);
void func_801090D8_mstory1(omObjData *obj);
void func_8010B384_mstory1(omObjData *obj);
void func_8010B6A4_mstory1(omObjData *obj);
void func_801099F8_mstory1(void);
void func_80109DC0_mstory1(void);
void func_8010A424_mstory1(void);
void func_8010AA98_mstory1(void);
void func_8010B108_mstory1(void);
void func_8010B110_mstory1(void);
void func_8010B3B8_mstory1(void);
void func_8010B4E4_mstory1(void);
void func_8010BC68_mstory1(void);
void func_8010A608_mstory1(void);
void func_8010B300_mstory1(void);
void func_8010B69C_mstory1(void);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C50_mstory1);

void func_80105C90_mstory1(omObjData *obj) {
    u32 state = D_80114A80_mstory1;
    s32 btn;

    switch (state) {
        case 0:
            HuAudSeqPlay(0x26);
            state++;
            break;
        case 1:
            state += WipeStatGet() == 0;
            break;
        case 2:
            if (D_80114A84_mstory1 == 1) {
                btn = D_800D5558_main[D_801158B4_mstory1] & START_BUTTON;
                state += btn != 0;
            }
            break;
        case 3:
            WipeCreateOut(2, 20);
            HuAudSeqFadeOut(30);
            state++;
            break;
        case 4:
            if (WipeStatGet() == 0) {
                HuWinAllKill();
                SLCommonSet(1);
                omOvlReturnEx(1);
            }
            break;
    }
    D_80114A80_mstory1 = state;
}

void func_80105D80_mstory1(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_80114A88_mstory1 == 0) {
            WipeCreateOut(2, 20);
            HuAudSeqFadeOut(30);
            D_80114A88_mstory1 = 1;
        } else if (WipeStatGet() == 0) {
            HuWinAllKill();
            SLCommonSet(1);
            omOvlReturnEx(1);
        }
    }
}

void func_80105E00_mstory1(void) {
    D_801158B8_mstory1 = espEntry(func_8000B838_main(0x1D0012), 0, 0);
    espPosSet(D_801158B8_mstory1, 160, 120);
    espAttrSet(D_801158B8_mstory1, 0x4000);
    D_801158B2_mstory1 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_801158B2_mstory1, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_801158B2_mstory1, 2, 0);
    func_8001C814_main(D_801158B2_mstory1, 1, 1);
}

void func_80105EC0_mstory1(void) {
    func_8001C258_main(D_801158B2_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    espDispOff(D_801158B8_mstory1);
}

void func_80105EF4_mstory1(void) {
    func_8001C258_main(D_801158B2_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    espDispOn(D_801158B8_mstory1);
}

void func_80105F28_mstory1(omObjData *obj) {
    D_800CE17C_main[0] = D_80114A8C_mstory1.x;
    D_800CE17C_main[1] = D_80114A8C_mstory1.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &D_80114A8C_mstory1, &D_80114A98_mstory1, &D_80114AA4_mstory1);
    Hu3DCamUpdateMtx(0);
}

void func_80105FA8_mstory1(void) {
    D_80114A80_mstory1 = 3;
}

void func_80105FB8_mstory1(s32 arg0) {
    D_801158E4_mstory1 = arg0;
    D_80114AB0_mstory1 = 0;
    omAddPrcObj(func_80105FF4_mstory1, 0x1000, 0x800, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80105FF4_mstory1);

s32 func_80106894_mstory1(void) {
    return D_80114AB0_mstory1;
}

void func_801068A0_mstory1(void) {
}

void func_801068A8_mstory1(void) {
}

void func_801068B0_mstory1(s16 model, s16 animSlot, s16 anim) {
    HmfAnim *entry;

    if (animSlot >= 0) {
        if (anim == -1) {
            func_80033910_main(Hu3DData[model].hmf);
        } else {
            func_80033970_main(Hu3DData[model].hmf);
            entry = &D_800D1714_main[animSlot];
            entry->animIdx = anim;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}

void func_80106984_mstory1(void) {
    D_801158B0_mstory1 = func_80060880_main(160, 194, 20);
    HuWinActivePlayerSet(D_801158B0_mstory1, 1 << D_801158B4_mstory1);
    HuWinInsertMesSet(D_801158B0_mstory1, GwStory.unk1 + 0x1C00, 0);
}

void func_801069EC_mstory1(void) {
    HuWinHomeClear(D_801158B0_mstory1);
    func_80060C14_main(D_801158B0_mstory1, 1);
}

void func_80106A1C_mstory1(void) {
    func_80060EA8_main(D_801158B0_mstory1, 1);
}

void func_80106A40_mstory1(s32 mess) {
    HuWinMesSet(D_801158B0_mstory1, mess, -1, -1);
    while (HuWinStatGet(D_801158B0_mstory1) != 0) {
        HuPrcVSleep();
    }
}

void func_80106A94_mstory1(s32 mess) {
    HuWinMesSet(D_801158B0_mstory1, mess, -1, -1);
}

void func_80106AC0_mstory1(void) {
    while (HuWinStatGet(D_801158B0_mstory1) != 0) {
        HuPrcVSleep();
    }
}

s32 func_80106AFC_mstory1(s32 character) {
    return -(character == GwStory.unk1);
}

void func_80106B14_mstory1(omObjData *obj, const Vec *pos, s32 frames) {
    func_80106B30_mstory1(obj, pos, frames, 1);
}

void func_80106B30_mstory1(omObjData *obj, const Vec *pos, s32 frames, s32 arg3) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[1];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = pos->x - start.x;
    diff.y = pos->y - start.y;
    diff.z = pos->z - start.z;
    if (arg3 != 0) {
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
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], cur.x, -5.0f, cur.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], pos->x, -5.0f, pos->z);
    }
    HuPrcVSleep();
}

void func_80106D64_mstory1(omObjData *obj, Vec *pos, s32 frames) {
    func_80106D80_mstory1(obj, pos, frames, 1);
}

void func_80106D80_mstory1(omObjData *obj, Vec *pos, s32 frames, s32 arg3) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[1];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = pos->x - start.x;
    diff.y = pos->y - start.y;
    diff.z = pos->z - start.z;
    if (arg3 != 0) {
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
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], cur.x, cur.y, cur.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    HuPrcVSleep();
}

void func_80106F94_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106B14_mstory1(obj, &pos, frames);
}

void func_80106FC0_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106B30_mstory1(obj, &pos, frames, arg3);
}

void func_80106FF0_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106D64_mstory1(obj, &pos, frames);
}

void func_8010701C_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106D80_mstory1(obj, &pos, frames, arg3);
}

void func_8010704C_mstory1(omObjData *obj, const Vec *target, s32 frames) {
    Vec start;
    Vec delta;
    Vec rot;
    s16 model = obj->model[1];
    f32 t;
    f32 angle;

    start.x = Hu3DData[model].rot.x;
    start.y = Hu3DData[model].rot.y;
    start.z = Hu3DData[model].rot.z;
    delta.x = target->x - start.x;
    delta.y = target->y - start.y;
    delta.z = target->z - start.z;
    for (t = 0.0f; t < frames; t += 1.0f) {
        angle = 90.0f / frames * t;
        rot.x = sindf(angle) * delta.x + start.x;
        rot.y = sindf(angle) * delta.y + start.y;
        rot.z = sindf(angle) * delta.z + start.z;
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, target->x, target->y, target->z);
    HuPrcVSleep();
}

void func_801071F4_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_8010704C_mstory1(obj, &pos, frames);
}

void func_80107220_mstory1(s16 model) {
    HuPrcSleep(10);
    while (!func_8010726C_mstory1(model)) {
        HuPrcVSleep();
    }
}

s32 func_8010726C_mstory1(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && D_800CCF58_main[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

// Code matches, but the target is followed by alignment padding, which suggests
// a file boundary at func_801074C0_mstory1.
#ifdef NON_MATCHING
void func_80107318_mstory1(omObjData *obj, f32 speed, s16 frames) {
    f32 dx;
    f32 dz;
    f32 t;

    dx = speed * sindf(Hu3DData[obj->model[1]].rot.y);
    dz = speed * cosdf(Hu3DData[obj->model[1]].rot.y);
    for (t = 0.0f; t < frames; t += 1.0f) {
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[1]].pos.x += dx;
        Hu3DData[obj->model[2]].pos.z = Hu3DData[obj->model[1]].pos.z += dz;
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80107318_mstory1);
#endif

MstoryPath *func_801074C0_mstory1(Vec *points, s32 flags) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801077C4_mstory1);

void func_8010806C_mstory1(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010809C_mstory1(void) {
    func_80106984_mstory1();
    D_80115A10_mstory1 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_801081E0_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80109140_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_801099F8_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80109DC0_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A424_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010AA98_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010B110_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010B3B8_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010B4E4_mstory1, 0x384, 0x800, 0);
    omAddPrcObj(func_8010BC68_mstory1, 0x384, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115A10_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_801081D8_mstory1(omObjData *obj) {
}

void func_801081E0_mstory1(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 16, -1, NULL);
    D_801158F0_mstory1[0].obj = obj;
    D_801158F0_mstory1[0].unk_08 = 0;
    D_801158F0_mstory1[0].unk_0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
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
    func_8000B460_main(obj, 5, D_80114D10_mstory1[chr]);
    func_8000B460_main(obj, 6, D_80114D30_mstory1[chr]);
    func_8000B460_main(obj, 7, D_80114D50_mstory1[chr]);
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 9, D_80114D70_mstory1[chr]);
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x9B));
    D_80115A14_mstory1[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80115A14_mstory1[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80115A14_mstory1[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80115A14_mstory1[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115A14_mstory1[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_801159B0_mstory1 = D_80114CB0_mstory1;
    Hu3DModelPosSet(obj->model[1], D_801159B0_mstory1.x, D_801159B0_mstory1.y, D_801159B0_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_801159B0_mstory1.x, -5.0f, D_801159B0_mstory1.z);
    Hu3DModelPosSet(obj->model[4], D_801159B0_mstory1.x, D_801159B0_mstory1.y, D_801159B0_mstory1.z);
    omPrcSetDestructor(0, func_801085F0_mstory1);
    D_801158F0_mstory1[0].func = func_801081D8_mstory1;
    while (TRUE) {
        D_801158F0_mstory1[0].func(obj);
        HuPrcVSleep();
    }
}

void func_801085F0_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C6C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C88_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CB0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CBC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CC8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CD4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CE0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CEC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CF8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D04_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D10_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D30_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D50_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D70_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D90_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D9C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114DA8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114DCC_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801085F8_mstory1);

void func_80109014_mstory1(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 10, 0);
    func_80107220_mstory1(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801158F0_mstory1[0].func = func_801081D8_mstory1;
}

void func_801090D8_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80114E40_mstory1, 10);
    D_801158F0_mstory1[0].func = func_801081D8_mstory1;
}

void func_8010910C_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80114E4C_mstory1, 10);
    D_801158F0_mstory1[0].func = func_801081D8_mstory1;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114DFC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E08_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E14_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E20_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E30_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E38_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E40_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E4C_mstory1);

const char D_80114E58_mstory1[] = "c204n_0_DEF";

void func_80109140_mstory1(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 4, 8, -1, NULL);
    D_801158F0_mstory1[1].obj = obj;
    D_801158F0_mstory1[1].unk_08 = 0;
    D_801158F0_mstory1[1].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_801159BC_mstory1 = D_80114CBC_mstory1;
    Hu3DModelPosSet(obj->model[1], D_801159BC_mstory1.x, D_801159BC_mstory1.y, D_801159BC_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_801159BC_mstory1.x, -5.0f, D_801159BC_mstory1.z);
    data = DataRead(0xA007E);
    D_80115A1C_mstory1[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_80114E58_mstory1);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115A1E_mstory1, 1, 0);
    Hu3DAnimBankSet(D_80115A1E_mstory1, 0);
    D_80115A28_mstory1 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115A1E_mstory1, 0, D_80114E58_mstory1);
    D_80115A1C_mstory1[0] = D_800D1714_main[D_80115A1C_mstory1[0]].animIdx;
    data = DataRead(0xA0080);
    D_80115A1C_mstory1[1] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80115A1C_mstory1[2] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_801068B0_mstory1(obj->model[1], D_80115A28_mstory1, D_80115A1E_mstory1);
    omPrcSetDestructor(0, func_80109470_mstory1);
    D_801158F0_mstory1[1].func = func_801081D8_mstory1;
    while (TRUE) {
        D_801158F0_mstory1[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80109470_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E64_mstory1);

const Vec D_80114E70_mstory1 = { 10.0f, 378.9f, 0.0f };

void func_80109478_mstory1(omObjData *obj) {
    D_801158F0_mstory1[0].func = func_80109014_mstory1;
    D_801158F0_mstory1[6].func = func_8010B384_mstory1;
    func_8010704C_mstory1(obj, &D_80114E70_mstory1, 30);
    func_80106B14_mstory1(obj, &D_80114ED0_mstory1, 20);
    HuPrcSleep(30);
    func_8010704C_mstory1(obj, &D_80114EA0_mstory1, 10);
    func_80106B14_mstory1(obj, &D_80114EC4_mstory1, 15);
    D_801158F0_mstory1[0].func = func_801090D8_mstory1;
    if (func_80106AFC_mstory1(4) == 0) {
        func_801071F4_mstory1(D_801158F0_mstory1[0].obj, 0.0f, 162.4744f, 0.0f, 10);
        func_8010704C_mstory1(obj, &D_80114E7C_mstory1, 15);
        HuPrcSleep(20);
        func_8010704C_mstory1(obj, &D_80114E94_mstory1, 10);
        func_8010704C_mstory1(D_801158F0_mstory1[6].obj, &D_80114EDC_mstory1, 10);
    } else {
        func_8010704C_mstory1(obj, &D_80114E7C_mstory1, 10);
        func_801068B0_mstory1(obj->model[1], D_80115A28_mstory1, D_80115A22_mstory1);
        func_801069EC_mstory1();
        func_80106A40_mstory1(0x5B04);
        func_80106A1C_mstory1();
        func_801068B0_mstory1(obj->model[1], D_80115A28_mstory1, D_80115A1E_mstory1);
        func_801071F4_mstory1(D_801158F0_mstory1[0].obj, 0.0f, 162.4744f, 0.0f, 10);
        func_8010704C_mstory1(D_801158F0_mstory1[6].obj, &D_80114EDC_mstory1, 10);
        func_8010704C_mstory1(obj, &D_80114E94_mstory1, 20);
    }
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(D_801158F0_mstory1[6].obj->model[1], Hu3DData[D_801158F0_mstory1[6].obj->motion[1]].motId, 0, 10, 2);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(4) == 0 ? 0x5A15 : 0x5B05);
    func_80106A1C_mstory1();
    Hu3DMotionShiftSet(D_801158F0_mstory1[6].obj->model[1], Hu3DData[D_801158F0_mstory1[6].obj->motion[0]].motId, 0, 10, 2);
    func_8010704C_mstory1(D_801158F0_mstory1[6].obj, &D_80114EE8_mstory1, 10);
    D_801158F0_mstory1[7].func = func_8010B6A4_mstory1;
    func_8010704C_mstory1(obj, &D_80114E64_mstory1, 20);
    Hu3DMotionShiftSet(D_801158F0_mstory1[0].obj->model[1], Hu3DData[D_801158F0_mstory1[0].obj->motion[10]].motId, 0, 10, 2);
    while (!(D_801158F0_mstory1[7].unk_08 & 2)) {
        HuPrcVSleep();
    }
    D_801158F0_mstory1[0].func = func_801085F8_mstory1;
    HuPrcSleep(40);
    func_8010704C_mstory1(obj, &D_80114EB8_mstory1, 50);
    func_8010704C_mstory1(obj, &D_80114EAC_mstory1, 40);
    D_801158F0_mstory1[1].func = func_801081D8_mstory1;
}

void func_8010980C_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80114F0C_mstory1, 10);
    func_80106B14_mstory1(obj, &D_80114F00_mstory1, 50);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801158F0_mstory1[1].func = func_801081D8_mstory1;
}

void func_80109888_mstory1(omObjData *obj) {
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
    func_801068B0_mstory1(obj->model[1], D_80115A28_mstory1, D_80115A26_mstory1);
    D_801158F0_mstory1[1].func = func_801081D8_mstory1;
}

void func_801099F8_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801158F0_mstory1[2].obj = obj;
    D_801158F0_mstory1[2].unk_08 = 0;
    D_801158F0_mstory1[2].unk_0C = 0;
    if (func_80106AFC_mstory1(4) == 0) {
        obj->model[1] = func_8000B108_main(0x500A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
        func_8000B460_main(obj, 0, 0x50000);
        func_8000B460_main(obj, 1, 0x1D0063);
        func_8000B460_main(obj, 2, 0x1D0064);
    } else {
        obj->model[1] = func_8000B108_main(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
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
    D_801159C8_mstory1 = D_80114CC8_mstory1;
    Hu3DModelPosSet(obj->model[1], D_801159C8_mstory1.x, D_801159C8_mstory1.y, D_801159C8_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_801159C8_mstory1.x, -5.0f, D_801159C8_mstory1.z);
    omPrcSetDestructor(0, func_80109C20_mstory1);
    D_801158F0_mstory1[2].func = func_80109C28_mstory1;
    while (1) {
        D_801158F0_mstory1[2].func(obj);
        HuPrcVSleep();
    }
}

void func_80109C20_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E7C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E94_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EA0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EAC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EB8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EC4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114ED0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EDC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EE8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F00_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F0C_mstory1);

const Vec D_80114F24_mstory1 = { 200.0f, 0.0f, 1200.0f };

void func_80109C28_mstory1(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106AFC_mstory1(4) == 0) {
        CharFXPlay(0x26B, 4);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    if (func_80106AFC_mstory1(4) == 0) {
        func_801068B0_mstory1(D_801158F0_mstory1[1].obj->model[1], D_80115A28_mstory1, D_80115A22_mstory1);
        func_801069EC_mstory1();
        func_80106A40_mstory1(0x5A14);
        func_80106A1C_mstory1();
        func_801068B0_mstory1(D_801158F0_mstory1[1].obj->model[1], D_80115A28_mstory1, D_80115A1E_mstory1);
    }
    D_801158F0_mstory1[1].func = func_80109478_mstory1;
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    if (func_80106AFC_mstory1(4) == 0) {
        CharFXPlay(0x286, 4);
    } else {
        CharFXPlay(0x286, 1);
    }
    func_8010BB08_mstory1(2, 40);
    func_80106B14_mstory1(obj, &D_80114F24_mstory1, 40);
    func_8010BBEC_mstory1(2);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801158F0_mstory1[2].func = func_801081D8_mstory1;
}

void func_80109DC0_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801158F0_mstory1[3].obj = obj;
    D_801158F0_mstory1[3].unk_08 = 0;
    D_801158F0_mstory1[3].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8000B460_main(obj, 3, 0x1D0035);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_801159D4_mstory1 = D_80114CD4_mstory1;
    Hu3DModelPosSet(obj->model[1], D_801159D4_mstory1.x, D_801159D4_mstory1.y, D_801159D4_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_801159D4_mstory1.x, -5.0f, D_801159D4_mstory1.z);
    omPrcSetDestructor(0, func_80109FD0_mstory1);
    D_801158F0_mstory1[3].func = func_801081D8_mstory1;
    while (1) {
        D_801158F0_mstory1[3].func(obj);
        HuPrcVSleep();
    }
}

void func_80109FD0_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F30_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109FD8_mstory1);

void func_8010A424_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801158F0_mstory1[4].obj = obj;
    D_801158F0_mstory1[4].unk_08 = 0;
    D_801158F0_mstory1[4].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
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
    D_801159E0_mstory1 = D_80114CE0_mstory1;
    Hu3DModelPosSet(obj->model[1], D_801159E0_mstory1.x, D_801159E0_mstory1.y, D_801159E0_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_801159E0_mstory1.x, -5.0f, D_801159E0_mstory1.z);
    omPrcSetDestructor(0, func_8010A608_mstory1);
    D_801158F0_mstory1[4].func = func_801081D8_mstory1;
    while (1) {
        D_801158F0_mstory1[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A608_mstory1(void) {
}

void func_8010A610_mstory1(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80106B14_mstory1(obj, &D_80114F84_mstory1, 30);
    func_8010704C_mstory1(obj, &D_80114F9C_mstory1, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (!(D_801158F0_mstory1[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    func_80107220_mstory1(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    func_80107220_mstory1(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_80114FB4_mstory1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_80114FA8_mstory1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_80114F9C_mstory1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_80114FC0_mstory1, 10);
    HuAudFXPlay(0x2A0);
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(4) == 0 ? 0x5A1B : 0x5B0B);
    func_80106A1C_mstory1();
    D_801158F0_mstory1[4].unk_08 |= 1;
    while (!(D_801158F0_mstory1[3].unk_08 & 4)) {
        HuPrcVSleep();
    }
    model = obj->model[1];
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_80114FA8_mstory1, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106B14_mstory1(obj, &D_80114F90_mstory1, 20);
    D_801158F0_mstory1[4].func = func_801081D8_mstory1;
}

void func_8010AA98_mstory1(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801158F0_mstory1[5].obj = obj;
    D_801158F0_mstory1[5].unk_08 = 0;
    D_801158F0_mstory1[5].unk_0C = 0;
    src = D_801158F0_mstory1[4].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
    func_8001C5B4_main(obj->model[1], src->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_801159EC_mstory1 = D_80114CEC_mstory1;
    Hu3DModelPosSet(obj->model[1], D_801159EC_mstory1.x, D_801159EC_mstory1.y, D_801159EC_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_801159EC_mstory1.x, -5.0f, D_801159EC_mstory1.z);
    omPrcSetDestructor(0, func_8010B108_mstory1);
    D_801158F0_mstory1[5].func = func_801081D8_mstory1;
    while (1) {
        D_801158F0_mstory1[5].func(obj);
        HuPrcVSleep();
    }
}

void func_8010AC40_mstory1(omObjData *obj) {
    omObjData *src = D_801158F0_mstory1[4].obj;
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80106B14_mstory1(obj, &D_80114FCC_mstory1, 30);
    func_8010704C_mstory1(obj, &D_80114FE4_mstory1, 10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    while (!(D_801158F0_mstory1[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[2]].motId, 0, 10, 0);
    func_80107220_mstory1(model);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[2]].motId, 0, 10, 0);
    func_80107220_mstory1(model);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_80114FF0_mstory1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_80114FFC_mstory1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_80114FE4_mstory1, 5);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_80115008_mstory1, 5);
    while (!(D_801158F0_mstory1[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    func_801069EC_mstory1();
    func_80106A40_mstory1(func_80106AFC_mstory1(4) == 0 ? 0x5A1D : 0x5B0D);
    func_80106A1C_mstory1();
    D_801158F0_mstory1[5].unk_08 |= 1;
    while (!(D_801158F0_mstory1[3].unk_08 & 4)) {
        HuPrcVSleep();
    }
    model = obj->model[1];
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    func_8010704C_mstory1(obj, &D_80114FF0_mstory1, 10);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    func_80106B14_mstory1(obj, &D_80114FD8_mstory1, 20);
    D_801158F0_mstory1[5].func = func_801081D8_mstory1;
}

void func_8010B108_mstory1(void) {
}

void func_8010B110_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801158F0_mstory1[6].obj = obj;
    D_801158F0_mstory1[6].unk_08 = 0;
    D_801158F0_mstory1[6].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_80115A10_mstory1);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_801159F8_mstory1 = D_80114CF8_mstory1;
    Hu3DModelPosSet(obj->model[1], D_801159F8_mstory1.x, D_801159F8_mstory1.y, D_801159F8_mstory1.z);
    Hu3DModelPosSet(obj->model[2], D_801159F8_mstory1.x, -5.0f, D_801159F8_mstory1.z);
    omPrcSetDestructor(0, func_8010B300_mstory1);
    D_801158F0_mstory1[6].func = func_801081D8_mstory1;
    D_80114AC0_mstory1 = 1;
    while (1) {
        D_801158F0_mstory1[6].func(obj);
        HuPrcVSleep();
    }
}

void func_8010B300_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F48_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F54_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F6C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F78_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F84_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F90_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F9C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FA8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FB4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FC0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FCC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FD8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FE4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FF0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FFC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80115008_mstory1);

const Vec D_80115020_mstory1 = { 700.0f, 0.0f, 150.0f };
const Vec D_8011502C_mstory1 = { 216.66666f, 0.0f, 150.0f };

void func_8010B308_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115038_mstory1, 10);
    func_80106B14_mstory1(obj, &D_80115020_mstory1, 50);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801158F0_mstory1[6].func = func_801081D8_mstory1;
}

void func_8010B384_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115050_mstory1, 20);
    D_801158F0_mstory1[6].func = func_801081D8_mstory1;
}

void func_8010B3B8_mstory1(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80114AC0_mstory1 != 0) {
        model = D_801158F0_mstory1[6].obj->model[1];
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

void func_8010B4E4_mstory1(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_801158F0_mstory1[7].obj = obj;
    D_801158F0_mstory1[7].unk_08 = 0;
    D_801158F0_mstory1[7].unk_0C = 0;
    obj->model[1] = func_8000B108_main(D_8011505C_mstory1[0], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80115A04_mstory1 = D_80114D04_mstory1;
    Hu3DModelPosSet(obj->model[1], D_80115A04_mstory1.x, D_80115A04_mstory1.y, D_80115A04_mstory1.z);
    D_80115A12_mstory1 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80115A12_mstory1, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_80115A12_mstory1, 60.0f);
    func_800138EC_main(D_80115A12_mstory1, 1, 0);
    func_8001C258_main(D_80115A12_mstory1, 4, 4);
    omPrcSetDestructor(0, func_8010B69C_mstory1);
    D_801158F0_mstory1[7].func = func_801081D8_mstory1;
    while (1) {
        D_801158F0_mstory1[7].func(obj);
        HuPrcVSleep();
    }
}

void func_8010B69C_mstory1(void) {
}

void func_8010B6A4_mstory1(omObjData *obj) {
    Vec pos;
    MstoryPath *paths[2];
    omObjData *target;
    f32 rotY;
    s32 i;

    paths[0] = func_801074C0_mstory1(D_80114AC4_mstory1, 0);
    paths[1] = func_801074C0_mstory1(D_80114AF4_mstory1, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_80115A12_mstory1, 4, 0);
    func_800138EC_main(D_80115A12_mstory1, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        func_801077C4_mstory1(paths[0], (i * 0.02f) * (i * 0.02f), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115A12_mstory1, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    target = D_801158F0_mstory1[6].obj;
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(20);
    D_801158F0_mstory1[7].unk_08 |= 2;
    HuAudFXPlay(0x218);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[0]].motId, 0, 10, 2);
    rotY = 0.0f;
    for (i = 0; i < 120; i++) {
        func_801077C4_mstory1(paths[1], (i * 0.008333334f) * (i * 0.008333334f), &pos);
        rotY -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        Hu3DModelRotSet(obj->model[1], 0.0f, rotY, 0.0f);
        func_8000CFA4_main(D_80115A12_mstory1, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(D_80115A12_mstory1, 4, 4);
    HuAudFXPlay(0x21A);
    func_8010806C_mstory1(paths[0]);
    func_8010806C_mstory1(paths[1]);
    D_801158F0_mstory1[7].unk_08 = 1;
    D_801158F0_mstory1[7].func = func_801081D8_mstory1;
}

void func_8010B9C0_mstory1(omObjData *obj, omObjData *target) {
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

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80115038_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80115050_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_8011505C_mstory1);

void func_8010BB08_mstory1(s32 index, s32 seNo) {
    if (D_801158F0_mstory1[index].unk_0C == 0) {
        D_801158F0_mstory1[index].unk_0C = 1;
        D_801158F0_mstory1[index].unk_10 = seNo;
        switch (index) {
            case 0:
                D_801158F0_mstory1[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                if (func_80106AFC_mstory1(4) == 0) {
                    D_801158F0_mstory1[index].unk_14 = CharFXPlay(seNo, 4);
                } else {
                    D_801158F0_mstory1[index].unk_14 = CharFXPlay(seNo, 1);
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

void func_8010BBEC_mstory1(s32 index) {
    if (D_801158F0_mstory1[index].unk_0C == 1) {
        D_801158F0_mstory1[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop((s16)D_801158F0_mstory1[index].unk_14);
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

void func_8010BC68_mstory1(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 8; i++) {
            if (D_801158F0_mstory1[i].unk_0C == 1 && Hu3DData[D_801158F0_mstory1[i].obj->model[1]].motTime == 0.0f) {
                seNo = D_801158F0_mstory1[i].unk_10;
                switch (i) {
                    case 0:
                        D_801158F0_mstory1[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                        break;
                    case 2:
                        if (func_80106AFC_mstory1(4) == 0) {
                            D_801158F0_mstory1[i].unk_14 = CharFXPlay(seNo, 4);
                        } else {
                            D_801158F0_mstory1[i].unk_14 = CharFXPlay(seNo, 1);
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
