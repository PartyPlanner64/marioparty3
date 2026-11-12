#include "staff.h"

#define ROT_XY(x, y, z, angle) ((x) * (y) * (1.0f - cosdf(angle)) - (z) * sindf(angle))
#define ROT_YY(x, y, z, angle) ((y) * (y) + (1.0f - (y) * (y)) * cosdf(angle))
#define ROT_ZY(x, y, z, angle) ((y) * (z) * (1.0f - cosdf(angle)) + (x) * sindf(angle))

typedef struct StaffCreditEntry { // sizeof 0x4
    /* 0x00 */ s8 type;
    /* 0x01 */ s8 wait;
    /* 0x02 */ u16 arg;
} StaffCreditEntry;

typedef struct StaffCreditSlot { // sizeof 0x20
    /* 0x00 */ Vec pos;
    /* 0x0C */ s16 x;
    /* 0x0E */ s16 y;
    /* 0x10 */ s16 win0;
    /* 0x12 */ s16 win1;
    /* 0x14 */ s16 sprite;
    /* 0x16 */ s16 model;
    /* 0x18 */ s16 motion;
    /* 0x1A */ s16 linkModel;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 type;
} StaffCreditSlot;

extern s32 D_80110B80_staff[];
extern StaffCreditEntry *D_80110F04_staff[];
extern u8 D_801111E0_staff[4][4];

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

void func_801088F4_staff(StaffPath *path, f32 t, Vec *out) {
    f32 value[4];
    f32 time[4];
    StaffPathSeg *segs;
    Vec *points;
    s16 i;

    if (t >= 1.0f) {
        out->x = path->points[path->count - 1].x;
        out->y = path->points[path->count - 1].y;
        out->z = path->points[path->count - 1].z;
        return;
    }
    segs = path->segs;
    for (i = 0; i < path->count; i++, segs++) {
        if (t <= segs->start) {
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
    segs = path->segs;
    if (path->flags & 1) {
        if (i == 0) {
            time[0] = -(1.0f - segs[path->count - 1].start);
        } else {
            time[0] = segs[i - 1].start;
        }
        time[1] = segs[i].start;
        if (i >= path->count - 1) {
            time[2] = segs[path->count - 1].end;
        } else {
            time[2] = segs[i + 1].start;
        }
        if (i + 1 >= path->count - 1) {
            time[3] = segs[path->count - 1].end;
        } else {
            time[3] = segs[i + 2].start;
        }
        points = path->points;
        if (i == 0) {
            value[0] = points[path->count - 1].x;
        } else {
            value[0] = points[i - 1].x;
        }
        value[1] = points[i].x;
        if (i >= path->count - 1) {
            value[2] = points[0].x;
        } else {
            value[2] = points[i + 1].x;
        }
        if (i + 1 >= path->count - 1) {
            value[3] = points[0].x;
        } else {
            value[3] = points[i + 2].x;
        }
        out->x = InterpolateBMLine(value, time, t);
        if (i == 0) {
            value[0] = points[path->count - 1].y;
        } else {
            value[0] = points[i - 1].y;
        }
        value[1] = points[i].y;
        if (i >= path->count - 1) {
            value[2] = points[0].y;
        } else {
            value[2] = points[i + 1].y;
        }
        if (i + 1 >= path->count - 1) {
            value[3] = points[0].y;
        } else {
            value[3] = points[i + 2].y;
        }
        out->y = InterpolateBMLine(value, time, t);
        if (i == 0) {
            value[0] = points[path->count - 1].z;
        } else {
            value[0] = points[i - 1].z;
        }
        value[1] = points[i].z;
        if (i >= path->count - 1) {
            value[2] = points[0].z;
        } else {
            value[2] = points[i + 1].z;
        }
        if (i + 1 >= path->count - 1) {
            value[3] = points[0].z;
        } else {
            value[3] = points[i + 2].z;
        }
        out->z = InterpolateBMLine(value, time, t);
    } else {
        if (i == 0) {
            time[0] = -1.0f;
        } else {
            time[0] = segs[i - 1].start;
        }
        time[1] = segs[i].start;
        if (i >= path->count - 1) {
            time[2] = segs[path->count - 1].end;
        } else {
            time[2] = segs[i + 1].start;
        }
        if (i + 1 >= path->count - 1) {
            time[3] = segs[path->count - 1].end;
        } else {
            time[3] = segs[i + 2].start;
        }
        points = path->points;
        if (i == 0) {
            value[0] = points[0].x;
        } else {
            value[0] = points[i - 1].x;
        }
        value[1] = points[i].x;
        if (i >= path->count - 1) {
            value[2] = points[path->count - 1].x;
        } else {
            value[2] = points[i + 1].x;
        }
        if (i + 1 >= path->count - 1) {
            value[3] = points[path->count - 1].x;
        } else {
            value[3] = points[i + 2].x;
        }
        out->x = InterpolateBMLine(value, time, t);
        if (i == 0) {
            value[0] = points[0].y;
        } else {
            value[0] = points[i - 1].y;
        }
        value[1] = points[i].y;
        if (i >= path->count - 1) {
            value[2] = points[path->count - 1].y;
        } else {
            value[2] = points[i + 1].y;
        }
        if (i + 1 >= path->count - 1) {
            value[3] = points[path->count - 1].y;
        } else {
            value[3] = points[i + 2].y;
        }
        out->y = InterpolateBMLine(value, time, t);
        if (i == 0) {
            value[0] = points[0].z;
        } else {
            value[0] = points[i - 1].z;
        }
        value[1] = points[i].z;
        if (i >= path->count - 1) {
            value[2] = points[path->count - 1].z;
        } else {
            value[2] = points[i + 1].z;
        }
        if (i + 1 >= path->count - 1) {
            value[3] = points[path->count - 1].z;
        } else {
            value[3] = points[i + 2].z;
        }
        out->z = InterpolateBMLine(value, time, t);
    }
}

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
INCLUDE_ASM("asm/nonmatchings/overlays/staff/544E70", func_801095E4_staff);
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

#ifdef NON_MATCHING
// Register allocation differs in the motion block: the target keeps the motion temp in s1 and
// reloads `motion` from its stack slot for the unk_1E store.
StaffModelEntry *func_80109F34_staff(UnkStaff_3 *work, StaffModelEntry *entry) {
    void *data;
    s32 i;
    s16 hasAnim;
    s16 model;
    s16 motion;
    s16 member;
    s16 link;

    work->unk_3A = 0;
    switch (work->unk_34) {
        case 7:
            for (i = 0; i < 4; i++) {
                Hu3DModelKill(work->unk_28[i]);
            }
            Hu3DAnimKill(work->unk_20);
            Hu3DAnimKill(work->unk_30);
            break;
        case 4:
        case 8:
        case 10:
            Hu3DModelKill(work->unk_28[0]);
            break;
        case 12:
            func_80046558_main(work->unk_1C);
            break;
    }
    if (work->unk_32 >= 0) {
        Hu3DAnimKill(work->unk_32);
    }
    if (work->unk_1C >= 0) {
        Hu3DModelKill(work->unk_1C);
    }
    if (work->unk_1E >= 0) {
        Hu3DModelKill(work->unk_1E);
    }
    work->unk_1C = -1;
    work->unk_1E = -1;
    HuPrcVSleep();
    if (entry->scale == 0.0f) {
        return entry;
    }
    work->unk_34 = entry->unk_12;
    hasAnim = FALSE;
    data = DataRead(entry->dataId);
    HuPrcVSleep();
    HuPrcVSleep();
    model = Hu3DModelCreate(data, 0x2AD);
    work->unk_1C = model;
    func_8001C814_main(model, -1, 2);
    Hu3DModelScaleSet(model, entry->scale, entry->scale, entry->scale);
    work->unk_22 = entry->unk_0C;
    HuPrcVSleep();
    HuPrcVSleep();
    work->unk_32 = -1;
    if (entry->animNo != 0) {
        i = entry->animNo - 1;
        hasAnim = TRUE;
        data = DataRead(D_80110674_staff[i].dataNum);
        HuPrcVSleep();
        HuPrcVSleep();
        work->unk_32 = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, D_80110674_staff[i].name);
        HuMemMemoryFreePerm(data);
        HuPrcVSleep();
    }
    if (entry->motDataId != 0) {
        data = DataRead(entry->motDataId);
        HuPrcVSleep();
        HuPrcVSleep();
        motion = member = Hu3DModelCreate(data, 0x1D);
        HuPrcVSleep();
        func_8001C5B4_main(model, member);
        func_8001C814_main(model, -1, 2);
        work->unk_1E = motion;
    }
    switch (work->unk_34) {
        case 1:
            work->unk_36 = 0;
            work->unk_0C.x = work->unk_0C.y = work->unk_0C.z = 0.0f;
            work->unk_18 = 90.0f;
            Hu3DModelRotSet(model, 0.0f, 90.0f, 0.0f);
            break;
        case 2:
            work->unk_36 = 0;
            work->unk_38 = entry->unk_14;
            work->unk_18 = 0.0f;
            work->unk_0C.x = work->unk_0C.y = work->unk_0C.z = work->unk_18;
            break;
        case 3:
            work->unk_18 = 0.0f;
            work->unk_36 = 30;
            work->unk_0C.x = 0.0f;
            func_8001FA68_main(model);
            func_8001F9E4_main(model, 0xFF);
            break;
        case 4:
            work->unk_36 = entry->unk_14;
            data = DataRead(0xA00C3);
            HuPrcVSleep();
            HuPrcVSleep();
            link = Hu3DModelCreate(data, 0x2AD);
            work->unk_28[0] = link;
            Hu3DModelScaleSet(link, entry->scale, entry->scale, entry->scale);
            func_8001C5B4_main(link, motion);
            func_8001C814_main(link, -1, 2);
            HuPrcVSleep();
            func_8001C514_main(link);
            HuPrcVSleep();
            break;
        case 5:
        case 11:
            work->unk_18 = 0.0f;
            break;
        case 6:
            work->unk_18 = work->unk_0C.x = work->unk_0C.y = work->unk_0C.z = 0.0f;
            work->unk_38 = 0;
            work->unk_36 = 0;
            break;
        case 7:
            data = DataRead(0xA008C);
            HuPrcVSleep();
            hasAnim = TRUE;
            HuPrcVSleep();
            work->unk_20 = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, "c201n_00_DEF");
            func_80034048_main(work->unk_20, 5);
            HuMemMemoryFreePerm(data);
            HuPrcVSleep();
            for (i = 0; i < 4; i++) {
                switch (i) {
                    case 0:
                        data = DataRead(entry->dataId);
                        HuPrcVSleep();
                        HuPrcVSleep();
                        member = link = Hu3DModelCreate(data, 0x2AD);
                        HuPrcVSleep();
                        data = DataRead(0xA008D);
                        HuPrcVSleep();
                        HuPrcVSleep();
                        work->unk_30 = Hu3DAnimCreate(Hu3DData[link].hmf, data, 0, "c201n_00_DEF");
                        HuMemMemoryFreePerm(data);
                        HuPrcVSleep();
                        func_80034048_main(work->unk_30, 8);
                        Hu3DModelRemakeStatic(link);
                        func_8001C514_main(link);
                        break;
                    case 1:
                        data = DataRead(entry->dataId);
                        HuPrcVSleep();
                        HuPrcVSleep();
                        member = link = Hu3DModelCreate(data, 0x2AD);
                        HuPrcVSleep();
                        data = DataRead(0xA008D);
                        HuPrcVSleep();
                        HuPrcVSleep();
                        work->unk_32 = Hu3DAnimCreate(Hu3DData[link].hmf, data, 0, "c201n_00_DEF");
                        HuMemMemoryFreePerm(data);
                        HuPrcVSleep();
                        Hu3DModelRemakeStatic(link);
                        func_8001C514_main(link);
                        break;
                    case 2:
                        member = Hu3DModelLink(work->unk_28[1]);
                        break;
                    case 3:
                        member = Hu3DModelLink(work->unk_28[0]);
                        break;
                }
                work->unk_28[i] = member;
                func_8001C814_main(member, -1, 2);
                Hu3DModelScaleSet(member, entry->scale, entry->scale, entry->scale);
                HuPrcVSleep();
            }
            HuPrcVSleep();
            HuPrcVSleep();
            break;
        case 8:
            link = Hu3DModelLink(model);
            work->unk_28[0] = link;
            work->unk_36 = entry->unk_14;
            func_8001C814_main(link, -1, 2);
            Hu3DMotionTimeSet(link, D_800CCF58_main[Hu3DData[link].motId].unk02 * 0.5f);
            Hu3DModelScaleSet(link, entry->scale, entry->scale, entry->scale);
            Hu3DModelRotSet(model, -15.0f, 80.0f, 0.0f);
            Hu3DModelRotSet(link, -15.0f, -80.0f, 0.0f);
            break;
        case 10:
            link = Hu3DModelLink(model);
            work->unk_28[0] = link;
            work->unk_36 = entry->unk_14;
            func_8001C814_main(link, -1, 2);
            Hu3DMotionTimeSet(link, D_800CCF58_main[Hu3DData[link].motId].unk02 * 0.5f);
            Hu3DModelScaleSet(link, entry->scale, entry->scale, entry->scale);
            Hu3DModelRotSet(model, 0.0f, -30.0f, 0.0f);
            Hu3DModelRotSet(link, 0.0f, 30.0f, 0.0f);
            break;
        case 12:
            func_800461B4_main(model);
            break;
        case 9:
            Hu3DModelRotSet(model, -30.0f, entry->unk_14, 0.0f);
            break;
        case 0:
        default:
            if (entry->unk_14 != 0) {
                Hu3DModelRotSet(model, 0.0f, entry->unk_14, 0.0f);
            }
            break;
    }
    if (hasAnim) {
        Hu3DModelRemakeStatic(model);
    }
    func_8001C514_main(model);
    work->unk_3A = 1;
    entry++;
    HuPrcVSleep();
    return entry;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/544E70", func_80109F34_staff);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/staff/544E70", func_8010A848_staff);

void func_8010B1E0_staff(void) {
    UnkStaff_3 works[3];
    UnkStaff_4 *staff;
    Process *prc;
    StaffModelEntry *entry;
    UnkStaff_3 *work;
    s32 i;
    s16 state;

    staff = HuMemAllocTag(sizeof(UnkStaff_4), TAG_OVERLAY);
    memset(staff, 0, sizeof(UnkStaff_4));
    state = 0;
    HuPrcCurrentGet()->user_data = staff;
    prc = omAddPrcObj(func_8010A848_staff, 0x4000, 0x800, 0);
    prc->user_data = works;
    staff->unk_00 = works;
    entry = func_80109D74_staff(works, D_80110704_staff);
    while (state >= 0) {
        if (state != staff->unk_04) {
            switch (staff->unk_04) {
                case 0:
                    break;
                case 1:
                    state = -1;
                    continue;
            }
            state = staff->unk_04;
        }
        for (work = works, i = 0; i < 3; i++, work++) {
            if (work->unk_3A != 0 && (work->unk_3A & 4)) {
                entry = func_80109F34_staff(work, entry);
            }
        }
        HuPrcVSleep();
    }
    omDelPrcObj(prc);
    for (work = works, i = 0; i < 3; i++, work++) {
        if (work->unk_3A == 0) {
            continue;
        }
        work->unk_3A = 0;
        switch (work->unk_34) {
            case 7:
                // Bug: reuses the outer loop counter.
                for (i = 0; i < 4; i++) {
                    Hu3DModelKill(work->unk_28[i]);
                }
                Hu3DAnimKill(work->unk_20);
                Hu3DAnimKill(work->unk_30);
                break;
            case 4:
            case 8:
            case 10:
                Hu3DModelKill(work->unk_28[0]);
                break;
            case 12:
                func_80046558_main(work->unk_1C);
                break;
        }
        if (work->unk_32 >= 0) {
            Hu3DAnimKill(work->unk_32);
        }
        if (work->unk_1C >= 0) {
            Hu3DModelKill(work->unk_1C);
        }
        if (work->unk_1E >= 0) {
            Hu3DModelKill(work->unk_1E);
        }
        work->unk_1C = -1;
        work->unk_1E = -1;
    }
    HuMemFree(staff);
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

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

INCLUDE_ASM("asm/nonmatchings/overlays/staff/544E70", func_8010B514_staff);

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

INCLUDE_ASM("asm/nonmatchings/overlays/staff/544E70", func_8010BA30_staff);

void func_8010BE20_staff(s16 *windows, s16 count) {
    s32 i;
    s16 window;

    for (i = 0; i < count; i++, windows++) {
        window = *windows = HuWinCreate(-120, -50, 240, 20, 0, 12);
        HuWinCenterPosSet(window, 120, 10);
        HuWinMesSpeedSet(window, 0);
        HuWinBGTPLvlSet(window, 0);
        HuWinMesPalSet(window, 2, 255, 0, 0);
        HuWinMesPalSet(window, 4, 0, 144, 0);
        HuWinMesPalSet(window, 5, 0, 176, 192);
        HuWinMesPalSet(window, 6, 255, 173, 0);
        func_8005C154_main(window, 64, 64, 64);
        HuWinBGColSet(window, 0, 0, 0);
        HuWinMesColSet(window, 7);
        func_8005BF70_main(window, 0x100);
        HuWinDispOff(window);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_8011133C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_80111348_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_80111354_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_80111360_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_8011136C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_80111378_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_80111384_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_80111390_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_8011139C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_801113A8_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_801113B4_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_801113C0_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_801113CC_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_801113D8_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_801113E4_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_801113F0_staff);

void func_8010BF84_staff(void) {
    StaffCreditSlot slots[12];
    s16 models[16];
    s16 anims[1];
    s16 sprites[1];
    Process *prc;
    UnkStaff_4 *prcWork;
    s16 *state;
    StaffCreditSlot *slot;
    StaffCreditEntry *entry;
    s32 i;
    s16 model;
    s16 link;
    s16 curState;
    s16 wait;
    s16 entryIdx;
    s16 modelIdx;
    s16 win0Idx;
    s16 win1Idx;
    s16 active;
    s16 done;

    state = HuPrcCurrentGet()->user_data;
    prc = omAddPrcObj(func_8010B1E0_staff, 0x4000, 0x1000, 0);
    HuPrcVSleep();
    prcWork = prc->user_data;
    for (slot = slots, i = 0; i < 12; i++, slot++) {
        slot->type = 0;
        slot->model = -1;
        slot->motion = -1;
        slot->win0 = -1;
        slot->win1 = -1;
        slot->sprite = -1;
        slot->linkModel = -1;
        slot->unk_1C = -1;
    }
    model = -1;
    for (i = 0; i < 3; i++) {
        if (model < 0) {
            model = link = func_8000B108_main(0x160025, 0x2B9);
        } else {
            link = Hu3DModelLink(model);
        }
        models[i] = link;
        func_8001C258_main(link, 4, 4);
    }
    for (i = 0; i < 1; i++) {
        anims[i] = func_8000B838_main(D_80110B80_staff[i]);
        sprites[i] = espEntry(anims[i], 0, 0);
        espDispOff(sprites[i]);
    }
    modelIdx = 0;
    win0Idx = 0;
    win1Idx = 0;
    curState = 0;
    while (curState >= 0) {
        if (curState != *state) {
            switch (*state) {
                case 0:
                    break;
                case 1:
                    wait = 1;
                    entry = D_80110F04_staff[0];
                    entryIdx = 1;
                    break;
            }
            curState = *state;
        }
        if (curState == 1) {
            if (entryIdx >= 0 && --wait == 0) {
                if (entry->type == -1) {
                    entry = D_80110F04_staff[entryIdx];
                    entryIdx++;
                    if (entry == NULL) {
                        entryIdx = -1;
                    }
                    wait += 127;
                } else {
                    for (slot = slots, i = 0; i < 12; i++, slot++) {
                        if (slot->type == 0) {
                            break;
                        }
                    }
                    if (i < 12) {
                        slot->x = 160;
                        slot->y = 320;
                        slot->pos.x = 0.0f;
                        slot->pos.y = -480.0f;
                        slot->pos.z = 380.0f;
                        slot->type = entry->type;
                        switch (slot->type) {
                            case 1:
                                func_8010BA30_staff(1, win1Idx, entry->arg, slot->x, slot->y);
                                slot->win1 = win1Idx;
                                if (++win1Idx >= 12) {
                                    win1Idx = 0;
                                }
                                break;
                            case 4:
                                slot->linkModel = models[modelIdx];
                                func_8001C258_main(slot->linkModel, 4, 0);
                                Hu3DModelPosSet(slot->linkModel, slot->pos.x, slot->pos.y, slot->pos.z);
                                func_8010998C_staff(prc, &slot->model, &slot->motion, &slot->pos);
                                if (++modelIdx >= 3) {
                                    modelIdx = 0;
                                }
                                /* fallthrough */
                            case 3:
                                func_8010BA30_staff(0, win0Idx, entry->arg, slot->x, slot->y);
                                slot->win0 = win0Idx;
                                if (++win0Idx >= 6) {
                                    win0Idx = 0;
                                }
                                wait += 22;
                                break;
                            case 2:
                                slot->sprite = sprites[entry->arg];
                                espDispOn(slot->sprite);
                                break;
                        }
                        wait += entry->wait;
                        entry++;
                        if (slot->type == 1 && entry->type >= 3) {
                            wait += 22;
                        }
                        wait += 30;
                    } else {
                        wait = 1;
                    }
                }
            }
            for (slot = slots, i = 0, active = 0; i < 12; i++, slot++) {
                if (slot->type == 0) {
                    continue;
                }
                active++;
                done = 0;
                slot->y--;
                if (slot->type == 4) {
                    done = slot->y < -63;
                } else if (slot->y < -15) {
                    done++;
                }
                if (done) {
                    slot->type = 0;
                    if (slot->model >= 0) {
                        func_8001C258_main(slot->model, 4, 4);
                        func_8010992C_staff(prc, slot->model);
                    }
                    slot->model = -1;
                    slot->motion = -1;
                    if (slot->win1 >= 0) {
                        func_8010B8C0_staff(1, slot->win1, 0);
                        slot->win1 = -1;
                    }
                    if (slot->sprite >= 0) {
                        espDispOff(slot->sprite);
                        slot->sprite = -1;
                    }
                    if (slot->win0 >= 0) {
                        func_8010B8C0_staff(0, slot->win0, 0);
                        slot->win0 = -1;
                    }
                    if (slot->linkModel >= 0) {
                        func_8001C258_main(slot->linkModel, 4, 4);
                        slot->linkModel = -1;
                    }
                } else {
                    switch (slot->type) {
                        case 1:
                            if (slot->win1 >= 0) {
                                func_8010B9BC_staff(1, slot->win1, slot->x, slot->y);
                            }
                            break;
                        case 4:
                            slot->pos.y = 288.0 - slot->y * 2.4;
                            Hu3DModelPosSet(slot->linkModel, slot->pos.x, slot->pos.y, slot->pos.z);
                            if (slot->model >= 0) {
                                func_80109D08_staff(prc, slot->model, &slot->pos);
                            }
                            /* fallthrough */
                        case 3:
                            func_8010B9BC_staff(0, slot->win0, slot->x, slot->y);
                            break;
                        case 2:
                            espPosSet(slot->sprite, slot->x, slot->y);
                            break;
                    }
                }
            }
            if (active == 0 && entryIdx < 0) {
                *state = -1;
            }
        }
        HuPrcVSleep();
    }
    prcWork->unk_04 = 1;
    for (i = 0; i < 3; i++) {
        Hu3DModelKill(models[i]);
    }
    for (i = 0; i < 1; i++) {
        espKill(sprites[i]);
        HuSprAnimKill(anims[i]);
    }
    HuPrcVSleep();
    *state = 0;
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_8010C680_staff(s16 *state, f32 *angle, f32 *rotY, UnkStaff *work) {
    Vec pos = work->pos;
    Vec *p = &pos;
    f32 dx;
    f32 rot;

    switch (*state) {
        case 0:
            p->x += 6.266667f;
            if (p->x >= 260.0f) {
                (*state)++;
                *angle = 0.0f;
            }
            break;
        case 1:
            *angle += 12.0f;
            if (*angle >= 180.0f) {
                *angle = 180.0f;
                (*state)++;
            }
            dx = cosdf(*angle) * 6.266667f;
            p->x += dx;
            rot = 90.0f - *angle;
            *rotY = rot;
            break;
        case 2:
            p->x -= 6.266667f;
            if (p->x <= -680.0f) {
                (*state)++;
                *angle = 0.0f;
            }
            break;
        case 3:
            *angle += 12.0f;
            if (*angle >= 180.0f) {
                *angle = 180.0f;
                *state = 0;
            }
            dx = cosdf(*angle) * -6.266667f;
            p->x += dx;
            rot = *angle + -90.0f;
            *rotY = rot;
            break;
    }
    work->pos.x = p->x;
    Hu3DModelPosSet(work->unk_18, p->x, p->y, p->z);
    Hu3DModelPosSet(work->unk_1E, p->x, 0.0f, p->z);
    Hu3DModelRotSet(work->unk_18, work->rot.x, *rotY - 8.0f, work->rot.z);
}

void func_8010C8F4_staff(UnkStaff_1 *works) {
    Vec pos[3];
    UnkStaff_1 *work;
    Vec *p;
    s32 i;
    f32 temp;
    f32 dx;
    f32 dz;
    f32 rot;

    for (work = works, p = pos, i = 0; i < 3; i++, work++, p++) {
        *p = work->pos;
        work->unk_18.z += 180.0f / 7.0f;
        if (work->unk_18.z >= 180.0f) {
            work->unk_18.z -= 180.0f;
            temp = (f32)(func_8010601C_staff() & 0x1F) - 15.0f;
            temp += 20.0f;
            work->unk_24 = temp;
        }
        temp = sindf(work->unk_18.z) * work->unk_24;
        p->y += temp;
    }

    work = works;
    p = pos;
    switch (work->unk_2A) {
        case 0:
            p->x += 6.266667f;
            if (p->x >= 260.0f) {
                work->unk_2A++;
                work->unk_18.x = 0.0f;
            }
            break;
        case 1:
            work->unk_18.x += 12.0f;
            if (work->unk_18.x >= 180.0f) {
                work->unk_18.x = 180.0f;
                work->unk_2A++;
            }
            dx = cosdf(work->unk_18.x) * 6.266667f;
            p->x += dx;
            rot = work->unk_18.x + -90.0f;
            work->rot.y = rot;
            break;
        case 2:
            p->x -= 6.266667f;
            if (p->x <= -680.0f) {
                work->unk_2A++;
                work->unk_18.x = 0.0f;
            }
            break;
        case 3:
            work->unk_18.x += 12.0f;
            if (work->unk_18.x >= 180.0f) {
                work->unk_18.x = 180.0f;
                work->unk_2A = 0;
            }
            dx = cosdf(work->unk_18.x) * -6.266667f;
            p->x += dx;
            rot = 90.0f - work->unk_18.x;
            work->rot.y = rot;
            break;
    }
    work->pos.x = p->x;

    for (work = works + 1, p = pos + 1, i = 1; i < 3; i++, work++, p++) {
        temp = work->unk_18.x;
        switch (i) {
            case 1:
                temp += 6.0f;
                rot = -90.0f;
                break;
            case 2:
                temp -= 5.0f;
                rot = 90.0f;
                break;
        }
        if (temp < 0.0f) {
            temp += 360.0f;
        } else if (temp >= 360.0f) {
            temp -= 360.0f;
        }
        work->unk_18.x = temp;
        dx = sindf(temp) * work->unk_18.y;
        dz = cosdf(temp) * work->unk_18.y;
        p->x += dx;
        p->z += dz;
        rot += temp;
        if (rot < 0.0f) {
            rot += 360.0f;
        } else if (rot >= 360.0f) {
            rot -= 360.0f;
        }
        work->rot.y = rot;
    }

    for (work = works, p = pos, i = 0; i < 3; i++, work++, p++) {
        Hu3DModelPosSet(work->unk_28, p->x, p->y, p->z);
        Hu3DModelRotSet(work->unk_28, work->rot.x, work->rot.y, work->rot.z);
    }
}

void func_8010CD74_staff(UnkStaff_1 *works) {
    s16 base = -1;
    UnkStaff_1 *work;
    s32 i;
    s16 model;

    for (work = works, i = 0; i < 3; i++, work++) {
        if (base < 0) {
            base = model = Hu3DModelCreate(DataReadTemp(0xA015E), 0x2B9);
        } else {
            model = Hu3DModelLink(base);
        }
        work->unk_28 = model;
        func_8001C814_main(model, -1, 2);
        work->pos = D_80110FA0_staff[i];
        Hu3DModelPosSet(model, work->pos.x, work->pos.y, work->pos.z);
        work->rot.x = work->rot.y = work->rot.z = 0.0f;
        work->unk_24 = 30.0f;
        switch (i) {
            case 0:
                Hu3DModelScaleSet(model, 0.8f, 0.8f, 0.8f);
                work->rot.y = -90.0f;
                Hu3DModelRotSet(model, 0.0f, -90.0f, 0.0f);
                work->unk_18.y = work->unk_18.x = work->unk_18.z = 0.0f;
                break;
            case 1:
                Hu3DModelScaleSet(model, 0.4f, 0.4f, 0.4f);
                work->unk_18.z = 60.0f;
                work->unk_18.x = 0.0f;
                work->unk_18.y = 50.0f;
                break;
            case 2:
                Hu3DModelScaleSet(model, 0.4f, 0.4f, 0.4f);
                work->unk_18.z = 120.0f;
                work->unk_18.x = 180.0f;
                work->unk_18.y = 80.0f;
                break;
        }
        work->unk_2A = 0;
    }
}

void func_8010CFD4_staff(UnkStaff *works) {
    StaffDecoEntry *entry = D_80111094_staff;
    UnkStaff *work = works;
    s16 shadowBase = -1;
    s32 i;
    s16 model;
    s16 shadow;
    void *data;

    for (i = 0; i < 8; i++, work++, entry++) {
        model = work->unk_18 = Hu3DModelCreate(DataReadTemp(entry->dataId), 0x2A9);
        data = DataReadTemp(entry->animDataId);
        work->unk_1C = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, entry->animName);
        HuMemMemoryFreePerm(data);
        Hu3DModelRemakeStatic(model);
        func_8001C514_main(model);
        work->unk_1A = Hu3DModelCreate(DataReadTemp(entry->subDataId), 0x1D);
        func_8001C5B4_main(model, work->unk_1A);
        func_8001C814_main(model, -1, 2);
        Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
        work->pos = entry->pos;
        Hu3DModelPosSet(model, work->pos.x, work->pos.y, work->pos.z);
        work->rot = entry->rot;
        Hu3DModelRotSet(model, entry->rot.x, entry->rot.y, entry->rot.z);
        work->unk_1E = -1;
        if (i != 0) {
            if (shadowBase < 0) {
                shadowBase = shadow = Hu3DModelCreate(DataReadTemp(9), 0x299);
            } else {
                shadow = Hu3DModelLink(shadowBase);
            }
            work->unk_1E = shadow;
            Hu3DModelPosSet(shadow, work->pos.x, 0.0f, work->pos.z);
            Hu3DModelScaleSet(shadow, 1.2f, 1.2f, 1.2f);
        }
    }
}

void func_8010D1E8_staff(void) {
    MsetupModelHandle sp10[3];
    UnkStaff sp20[8];
    UnkStaff_1 sp120[3];
    s16 sp1A8;
    f32 sp1AC;
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
    sp1AC = 0.0f;
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

void func_8010D450_staff(s16 model, Vec *pos) {
    f32 height = pos->y;
    f32 scale = 400.0f - height;
    f32 offsetX;
    f32 offsetZ;

    if (scale < 0.0f) {
        scale = 0.0f;
    }
    scale *= 0.0015f;
    Hu3DModelScaleSet(model, scale, scale, scale);
    offsetX = height * (f64)0.2f;
    offsetZ = height * (0.2f * 1.732);
    offsetX += pos->x;
    offsetZ += pos->z;
    Hu3DModelPosSet(model, offsetX, 0.0f, offsetZ);
    if (height >= 80.0f) {
        func_8001C258_main(model, 4, 4);
    } else {
        func_8001C258_main(model, 4, 0);
    }
}

void func_8010D580_staff(s16 model, s16 shadow, Vec *start) {
    Vec pos;
    f32 rotX;
    f32 rotY;
    f32 rotZ;
    f32 *spinAxis;
    s32 count;
    f32 angle;
    f32 speed;
    f32 remain;
    s32 i;

    rotZ = 0.0f;
    rotY = rotZ;
    rotX = rotZ;
    count = func_8010601C_staff();
    i = count & 0xF;
    if (i >= 10) {
        rotZ = -90.0f;
        spinAxis = &rotY;
    } else {
        spinAxis = &rotX;
    }
    count >>= 4;
    i = (count & 3) * 90;
    angle = i;
    speed = 0.0f;
    i = 0;
    pos = *start;
    do {
        angle -= 10.0f;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        speed += 2.0f;
        pos.y -= speed;
        if (pos.y <= 0.0f) {
            pos.y = 0.0f;
            speed *= -0.5;
            RepeatVibrator(D_80111510_staff, 5, 0, 5);
            i++;
        }
        pos.z -= 8.0f;
        Hu3DModelPosSet(model, pos.x, pos.y + 22.0f, pos.z);
        *spinAxis = angle;
        Hu3DModelRotSet(model, rotX, rotY, rotZ);
        func_8010D450_staff(shadow, &pos);
        HuPrcVSleep();
    } while (i < 2);

    i = angle;
    remain = i % 90;
    if (remain >= 10.0f) {
        i = remain;
        count = i / 10;
        speed = pos.y / count;
        for (; count != 0; count--) {
            angle -= 10.0f;
            pos.y -= speed;
            pos.z -= 8.0f;
            Hu3DModelPosSet(model, pos.x, pos.y + 22.0f, pos.z);
            *spinAxis = angle;
            Hu3DModelRotSet(model, rotX, rotY, rotZ);
            func_8010D450_staff(shadow, &pos);
            HuPrcVSleep();
        }
    }
    pos.y = 0.0f;
    Hu3DModelPosSet(model, pos.x, 22.0f, pos.z);
    *spinAxis -= 8.0f;
    Hu3DModelRotSet(model, rotX, rotY, rotZ);
    HuPrcVSleep();
    *spinAxis += 12.0f;
    Hu3DModelRotSet(model, rotX, rotY, rotZ);
    HuPrcVSleep();
    *spinAxis -= 4.0f;
    Hu3DModelRotSet(model, rotX, rotY, rotZ);
    HuPrcVSleep();
}

#ifdef NON_MATCHING
// Register allocation differs: the target keeps &work in a saved register for the
// sprite setup loop, shifting the model/shadow/grp saved registers.
void func_8010D998_staff(void) {
    UnkStaff_9 work;
    s16 *stat;
    s16 model;
    s16 shadow;
    s16 motion;
    s16 grp;
    s16 state;
    s16 x;
    s16 tpLvl;
    s16 step;
    u16 esp;
    s32 i;

    stat = HuPrcCurrentGet()->user_data;
    Hu3DGLightDirSet(1, -21.0f, 235.0f, 181.0f);
    esp = espEntry(func_8000B838_main(0x160024), 0, 0);
    espAttrSet(esp, 0x4000);
    espPosSet(esp, 160, 120);
    espPriSet(esp, 0xFFF0);
    D_80110538_staff = 1;
    D_80111540_staff.x = -300.578f;
    D_80111540_staff.y = 542.5f;
    D_80111540_staff.z = 595.0f;
    D_80111534_staff.x = 10.3905f;
    D_80111534_staff.y = 0.0f;
    D_80111534_staff.z = 48.0235f;
    D_80110534_staff = 32.0f;
    Hu3DCameraPerspectiveSet(0, 32.0f, D_80111564_staff, D_80111560_staff);
    motion = func_8000B13C_main(0xA007D);
    model = func_8000B108_main(0xA0075, 0x2A9);
    func_8001C514_main(model);
    Hu3DModelScaleSet(model, 0.6f, 0.6f, 0.6f);
    HuPrcVSleep();
    func_8001C5B4_main(model, motion);
    func_8001C814_main(model, 2, 2);
    shadow = func_8000B108_main(9, 0x299);
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(shadow, 4, 0);
    work.pos = D_80110FDC_staff;
    Hu3DModelPosSet(model, work.pos.x, work.pos.y + 22.0f, work.pos.z);
    func_8010D450_staff(shadow, &work.pos);
    for (i = 0; i < 3; i++) {
        work.anims[i] = func_8000B838_main(D_80110FE8_staff[i]);
    }
    grp = HuSprGrpCreate(3, 0);
    for (i = 0, x = 268; i < 3; i++, x += 12) {
        HuSprTPLvlSet(grp, i, 0);
        HuSprAttrReset(grp, i, 0xFFFF);
        HuSprAttrSet(grp, i, 0x9000);
        HuSprScaleSet(grp, i, 1.0f, 1.0f);
        HuSprGrpMemberSet(grp, i, work.anims[i], 0);
        func_800550F4_main(grp, i, 0);
        HuSprPriSet(grp, i, 400);
        HuSprPosSet(grp, i, x, 214);
    }
    *stat = 0;
    state = 0;
    while (TRUE) {
        if (state != *stat) {
            if (*stat == 1) {
                func_8001C258_main(model, 4, 0);
                func_8001C258_main(shadow, 4, 0);
            }
            state = *stat;
        }
        if (state == 1) {
            func_8010D580_staff(model, shadow, &work.pos);
            for (i = 0; i < 3; i++) {
                HuSprDispOn(grp, i);
                HuSprTPLvlSet(grp, i, 0);
            }
            tpLvl = 0;
            step = 2;
            do {
                tpLvl += step;
                if (tpLvl >= 256) {
                    tpLvl = 256;
                    step = 0;
                }
                for (i = 0; i < 3; i++) {
                    HuSprTPLvlSet(grp, i, tpLvl);
                }
                HuPrcVSleep();
            } while (step != 0);
            *stat = 0;
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/544E70", func_8010D998_staff);
#endif

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

INCLUDE_ASM("asm/nonmatchings/overlays/staff/544E70", func_8010DF34_staff);

#ifdef NON_MATCHING
// Register allocation differs throughout; the target also loads the image width/height
// with signed halfword loads, suggesting those fields are s16 in the original struct.
void func_8010F04C_staff(s16 model, s32 dataNum) {
    s16 anim;
    s16 grp;
    HuSprite *sprite;
    HuSprite_Unk84_Unk00_Struct *img;
    u16 *pixels;
    HmfModelData_UnkBC_Struct *bc;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count;
    s16 width;
    s16 height;
    s16 used;
    s16 i;
    s16 x;
    s16 y;

    anim = func_8000B838_main(dataNum);
    grp = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(grp, 0, anim, 0);
    sprite = HuSprGet(grp, 0);
    img = sprite->unk_84->unk00;
    pixels = img->unk00;
    width = img->unk04;
    height = img->unk06;
    for (i = 0; i < width * height; i++) {
        pixels++;
    }
    pixels = sprite->unk_84->unk00->unk00;
    bc = Hu3DData[model].unkBC;
    count = Hu3DData[model].hmf->unk1A;
    particle = bc->unk58;
    used = 0;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            if (*pixels++ == 0xFFFF && used < count) {
                particle = &bc->unk58[used];
                particle->unk18 = rand8() & 0xF;
                particle->unk24 = (x - width / 2) * 12;
                particle->unk28 = (height / 2 - y) * 12;
                particle->unk2C = 1.0f;
                particle->unk08 = 3.0f;
                particle->unk04 = (rand8() * 5 >> 7) * 0.1f + 3.0f;
                used++;
                particle++;
            }
        }
    }
    for (i = 0; i < count - used; i++, particle++) {
        particle->unk14 = particle->unk10 = particle->unk0C = particle->unk2C = particle->unk08 = 0.0f;
    }
    HuSprGrpKill(grp);
    HuSprAnimKill(anim);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/staff/544E70", func_8010F04C_staff);
#endif

HmfModelData_UnkBC_Unk58_Struct *func_8010F3E4_staff(s16 model, f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz, u8 r,
                                                     u8 g, u8 b) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Unk58_Struct *particle = Hu3DData[model].unkBC->unk58;
    s16 count = hmf->unk1A;
    s16 i;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 <= 0.0f) {
            particle->unk0C = x;
            particle->unk10 = y;
            particle->unk14 = z;
            particle->unk24 = vx;
            particle->unk28 = vy;
            particle->unk2C = vz;
            particle->unk00[0] = r;
            particle->unk00[1] = g;
            particle->unk00[2] = b;
            particle->unk08 = 2.0f;
            break;
        }
    }
    return particle;
}

void func_8010F4C4_staff(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    s16 count = hmf->unk1A;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    HmfModelData_UnkBC_Unk58_Struct *src;
    HmfModelData_UnkBC_Unk58_Struct *dst;
    s16 i;
    s16 j;
    s16 dead;
    u8 r;
    u8 g;
    u8 b;
    f32 angle;

    if (bc->unk02 == 0) {
        bc->unk04 &= ~4;
        particle = bc->unk58;
        for (i = 0; i < count; i++, particle++) {
            if (particle->unk2C > 0.0f) {
                particle->unk08 = 1.0f;
            }
        }
    }
    particle = bc->unk58;
    r = rand8() | 0x80;
    g = rand8() | 0x80;
    b = rand8() | 0x80;
    if (bc->unk02 <= bc->unk08.f) {
        if (bc->unk02 > 20) {
            for (j = 0; j < 2; j++) {
                src = &bc->unk58[(rand8() * count) >> 8];
                if (src->unk2C > 0.0f) {
                    dst = &bc->unk58[(rand8() * count) >> 8];
                    if (dst->unk2C <= 0.0f) {
                        dst->unk0C = src->unk0C;
                        dst->unk10 = src->unk10;
                        dst->unk14 = src->unk14;
                        dst->unk08 = 1.0f;
                    }
                }
            }
        }
        for (i = 0; i < count; i++, particle++) {
            if (particle->unk08 > 0.0f) {
                particle->unk00[0] = r;
                particle->unk00[1] = g;
                particle->unk00[2] = b;
                if (particle->unk2C > 0.0f) {
                    angle = bc->unk02 * particle->unk04;
                    if (angle > 90.0f) {
                        angle = 90.0f;
                    }
                    particle->unk0C = sindf(angle) * particle->unk24;
                    particle->unk10 = sindf(angle) * particle->unk28;
                    particle->unk14 = 0.0f;
                    particle->unk08 = ((bc->unk02 + i) & 1) * 0.5f + 1.0f;
                } else {
                    particle->unk10 -= 10.0f;
                    particle->unk08 -= 0.04f;
                }
            } else {
                particle->unk08 = 0.0f;
            }
        }
    } else {
        for (i = 0, dead = 0; i < count; i++, particle++) {
            if (particle->unk08 > 0.0f) {
                particle->unk00[0] = r;
                particle->unk00[1] = g;
                particle->unk00[2] = b;
                if (particle->unk2C > 0.0f) {
                    if (particle->unk18 <= 0.0f) {
                        particle->unk10 -= particle->unk04 * 5.0f;
                        particle->unk08 -= 0.02f;
                        if (particle->unk08 < 0.0f) {
                            particle->unk08 = 0.0f;
                        }
                    } else {
                        particle->unk18 -= 1.0f;
                        particle->unk08 = ((bc->unk02 + i) & 1) * 0.5f + 1.0f;
                    }
                } else {
                    particle->unk10 -= 10.0f;
                    particle->unk08 -= 0.04f;
                }
            } else {
                particle->unk08 = 0.0f;
                dead++;
            }
        }
        if (dead >= i) {
            bc->unk04 |= 2;
            return;
        }
    }
    bc->unk02++;
}

void func_8010F9D4_staff(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    s16 count = hmf->unk1A;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;

    if (bc->unk02 == 0) {
        bc->unk04 &= ~4;
        particle = bc->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk08 = particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        }
        bc->unk02++;
    }
    particle = bc->unk58;
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 > 0.0f) {
            particle->unk0C += particle->unk24;
            particle->unk10 += particle->unk28;
            particle->unk14 += particle->unk2C;
            particle->unk10 -= 5.0f;
            particle->unk08 -= 0.05f;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}

void func_8010FB28_staff(void) {
    Process *prc = omAddPrcObj(func_8010FB88_staff, 0x3F00, 0x2000, 0);
    UnkStaff_5 *data = HuMemAllocTag(sizeof(UnkStaff_5), TAG_OVERLAY);

    prc->user_data = data;
    data->unk_18.x = 0.0f;
    data->unk_18.y = 100.0f;
    data->unk_18.z = 0.0f;
}

void func_8010FB88_staff(void) {
    s16 angle[2];
    Vec cur[2];
    Vec prev[2];
    f32 rot[2];
    f32 tilt[2];
    UnkStaff_5 *work;
    s16 model;
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *effect;
    HmfModelData_Unk64_Unk60_Unk54_Struct *face;
    s16 count;
    s16 i;
    s16 j;
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 vx;
    f32 vy;
    f32 vz;
    s16 color;

    work = HuPrcCurrentGet()->user_data;
    model = func_8000B108_main(0xB0034, 0x6A8);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    hmf = Hu3DData[model].hmf;
    for (j = 0; j < hmf->unk10; j++) {
        count = hmf->unk60[j].unk22;
        face = hmf->unk60[j].unk54;
        for (i = 0; i < count; i++, face++) {
            face->unk00 |= 0x80;
        }
    }
    Hu3DModelRemakeStatic(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    func_80013390_main(model, -1, NULL, func_8010F4C4_staff);
    func_800138EC_main(model, 8, 8);
    effect = Hu3DData[model].unkBC;
    func_8001C258_main(model, 4, 4);
    func_8001C258_main(model, 4, 0);
    func_80013954_main(model, 0);
    effect->unk18 = func_8010F9D4_staff;
    func_800138EC_main(model, 2, 0);
    work->unk_30 = work->unk_18;
    cur[0].x = sindf(0.0f) * 150.0f + work->unk_30.x;
    cur[0].y = work->unk_30.y;
    cur[0].z = cosdf(0.0f) * 150.0f + work->unk_30.z;
    prev[0] = cur[0];
    tilt[0] = rot[0] = 0.0f;
    angle[0] = 0;
    cur[1].x = sindf(180.0f) * 150.0f + work->unk_30.x;
    cur[1].y = work->unk_30.y;
    cur[1].z = cosdf(180.0f) * 150.0f + work->unk_30.z;
    prev[1] = cur[1];
    tilt[1] = rot[1] = 180.0f;
    angle[1] = 180;
    while (TRUE) {
        HuPrcVSleep();
        for (i = 0; i < 2; i++) {
            prev[i] = cur[i];
            dx = sindf(angle[i]) * 150.0f;
            dz = cosdf(angle[i]) * 150.0f;
            t = sindf(tilt[i]) * 10.0f;
            cur[i].x = dx * cosdf(t) + work->unk_30.x;
            cur[i].y = dx * -sindf(t) + work->unk_30.y;
            cur[i].z = dz + work->unk_30.z;
            angle[i] += 5;
            if (angle[i] > 360) {
                angle[i] -= 360;
            }
            rot[i] += 20.0f;
            if (rot[i] > 360.0f) {
                rot[i] -= 360.0f;
            }
            tilt[i] += 1.0f;
            if (tilt[i] > 360.0f) {
                tilt[i] -= 360.0f;
            }
            dx = prev[i].x - cur[i].x;
            dy = prev[i].y - cur[i].y;
            dz = prev[i].z - cur[i].z;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (dist == 0.0f) {
                continue;
            }
            dx /= dist;
            dy /= dist;
            dz /= dist;
            t = rot[i];
            vx = ROT_XY(dx, dy, dz, t);
            vy = ROT_YY(dx, dy, dz, t);
            vz = ROT_ZY(dx, dy, dz, t);
            vx = (dx * 0.7f + vx * 0.3f) * dist * 0.7f;
            vy = (dy * 0.7f + vy * 0.3f) * dist * 0.7f;
            vz = (dz * 0.7f + vz * 0.3f) * dist * 0.7f;
            color = rand8() & 3;
            func_8010F3E4_staff(model, cur[i].x, cur[i].y, cur[i].z, vx, vy, vz, D_801111E0_staff[color][0],
                                D_801111E0_staff[color][1], D_801111E0_staff[color][2])
                ->unk08 = 1.0f;
            vx = -ROT_XY(dx, dy, dz, t);
            vy = -ROT_YY(dx, dy, dz, t);
            vz = -ROT_ZY(dx, dy, dz, t);
            vx = (dx * 0.7f + vx * 0.3f) * dist * 0.7f;
            vy = (dy * 0.7f + vy * 0.3f) * dist * 0.7f;
            vz = (dz * 0.7f + vz * 0.3f) * dist * 0.7f;
            color = rand8() & 3;
            func_8010F3E4_staff(model, cur[i].x, cur[i].y, cur[i].z, vx, vy, vz, D_801111E0_staff[color][0],
                                D_801111E0_staff[color][1], D_801111E0_staff[color][2])
                ->unk08 = 1.0f;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_80111430_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_8011143C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_80111448_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_80111454_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_80111460_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_8011146C_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_80111478_staff);

INCLUDE_RODATA("asm/nonmatchings/overlays/staff/544E70", D_80111484_staff);
