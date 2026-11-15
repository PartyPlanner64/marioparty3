#include "staff.h"

s32 D_801105F0_staff[2] = { 0xA0075, 0xA0122 };
Vec D_801105F8_staff[2] = {
    { -755.0f, 580.0f, 0.0f },
    { 755.0f, 580.0f, 0.0f },
};
f32 D_80110610_staff[2] = { 360.0f, 180.0f };
Vec D_80110618_staff[4] = {
    { 0.0f, 70.0f, 546.0f },
    { 0.0f, 200.0f, 315.0f },
    { -402.0f, 296.0f, -37.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
Vec D_80110648_staff[3] = {
    { -402.0f, 296.0f, -37.0f },
    { 48.0f, 4.0f, 1298.0f },
    { 9999.0f, 9999.0f, 9999.0f },
};
s16 D_8011066C_staff[4] = { -160, -80, 80, 160 };

extern StaffAnimEntry D_80110674_staff[18];
extern StaffModelEntry D_80110704_staff[38];
extern s32 D_80110AA0_staff[27];
extern s32 D_80110B0C_staff[28];

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
    f32 cosAngle;

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
    for (state = 0; state >= 0;) {
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
            cosAngle = cosdf(angle);
            cosAngle += 1.0f;
            func_801088F4_staff(path, cosAngle * 0.5f, &pos);
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
        motion = Hu3DModelCreate(data, 0x1D);
        HuPrcVSleep();
        func_8001C5B4_main(model, motion);
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
                // do-while (0) raises the loop weighting of member so it gets a register before entry.
                do {
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
                } while (0);
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

void func_8010A848_staff(void) {
    UnkStaff_3 *works;
    UnkStaff_3 *work;
    s32 i;
    s32 j;
    f32 x;
    f32 y;
    f32 z;
    f32 temp;
    f32 rot;
    f32 temp2;
    f32 vel;
    s16 model;

    works = HuPrcCurrentGet()->user_data;
    while (TRUE) {
        for (work = works, i = 0; i < 3; i++, work++) {
            if (work->unk_3A != 3) {
                continue;
            }
            x = work->unk_22.unk_00 + work->unk_00.x;
            y = work->unk_22.unk_02 + work->unk_00.y;
            z = work->unk_22.unk_04 + work->unk_00.z;
            model = work->unk_1C;
            switch (work->unk_34) {
                case 1:
                    temp = work->unk_0C.y;
                    temp += 2.0f;
                    if (temp >= 360.0f) {
                        temp -= 360.0f;
                        work->unk_36 = 0;
                    }
                    work->unk_0C.y = temp;
                    temp2 = sindf(temp) * 120.0f;
                    rot = work->unk_18;
                    switch (work->unk_36) {
                        case 0:
                            if (temp > 60.0f) {
                                work->unk_36++;
                            }
                            break;
                        case 1:
                            rot -= 6.0f;
                            if (rot <= -90.0f) {
                                rot = -90.0f;
                                work->unk_36++;
                            }
                            break;
                        case 2:
                            if (temp > 240.0f) {
                                work->unk_36++;
                            }
                            break;
                        case 3:
                            rot += 6.0f;
                            if (rot >= 90.0f) {
                                rot = 90.0f;
                                work->unk_36++;
                            }
                            break;
                        case 4:
                            break;
                    }
                    work->unk_18 = rot;
                    if (rot >= 360.0f) {
                        rot -= 360.0f;
                    } else if (rot < 0.0f) {
                        rot += 360.0f;
                    }
                    Hu3DModelPosSet(model, temp2 + x, y, z);
                    Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
                    break;
                case 2:
                    switch (work->unk_36) {
                        case 0:
                            temp = work->unk_38 / 15.0f;
                            work->unk_0C.y += temp;
                            if (work->unk_0C.y >= work->unk_38) {
                                work->unk_18 = 8.0f;
                                work->unk_36++;
                            }
                            break;
                        case 1:
                            work->unk_18 += 8.0f;
                            work->unk_0C.y -= work->unk_18;
                            if (work->unk_0C.y <= 0.0f) {
                                work->unk_0C.y = 0.0f;
                                work->unk_18 = 0.0f;
                                work->unk_36++;
                            }
                            break;
                        case 2:
                            work->unk_18 += 60.0f;
                            if (work->unk_18 >= 180.0f) {
                                work->unk_18 = 0.0f;
                                work->unk_36++;
                            }
                            temp = sindf(work->unk_18) * 10.0f;
                            work->unk_0C.y = temp;
                            break;
                        case 3:
                            work->unk_18 += 1.0f;
                            if (work->unk_18 > 15.0f) {
                                work->unk_18 = 0.0f;
                                work->unk_36 = 0;
                            }
                            break;
                    }
                    Hu3DModelPosSet(model, x, y + work->unk_0C.y, z);
                    break;
                case 4:
                    Hu3DModelPosSet(model, x - work->unk_36, y, z);
                    Hu3DModelPosSet(work->unk_28[0], x + work->unk_36, y, z);
                    break;
                case 11:
                    temp2 = work->unk_18;
                    temp2 += 4.0f;
                    if (temp2 >= 360.0f) {
                        temp2 -= 360.0f;
                    }
                    work->unk_18 = temp2;
                    temp = sindf(temp2) * 15.0f;
                    Hu3DModelPosSet(model, x, temp + y, z);
                    break;
                case 5:
                    temp = work->unk_18;
                    temp += 2.4f;
                    if (temp >= 360.0f) {
                        temp -= 360.0f;
                    }
                    work->unk_18 = temp;
                    temp2 = sindf(temp) * 50.0f;
                    Hu3DModelPosSet(model, temp2 + x, y, z);
                    break;
                case 6:
                    switch (work->unk_36) {
                        case 0:
                            if (work->unk_38 == 0) {
                                j = func_80106044_staff(380) - 190;
                                work->unk_0C.x = j;
                                Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
                                vel = 6.0f;
                                work->unk_36++;
                            } else {
                                work->unk_38--;
                            }
                            break;
                        case 1:
                            work->unk_0C.y += vel;
                            vel -= 0.2f;
                            if (work->unk_0C.y <= 0.0f) {
                                work->unk_0C.y = 0.0f;
                                Hu3DModelScaleSet(model, 1.0f, 0.75f, 1.0f);
                                work->unk_36++;
                            }
                            break;
                        case 2:
                            work->unk_38 = (rand8() & 0xF) + 15;
                            work->unk_36 = 0;
                            Hu3DModelScaleSet(model, 1.0f, 0.5f, 1.0f);
                            break;
                    }
                    Hu3DModelPosSet(model, x + work->unk_0C.x, y + work->unk_0C.y, z);
                    break;
                case 7:
                    Hu3DModelPosSet(model, x, y, z);
                    for (j = 0; j < 4; j++) {
                        Hu3DModelPosSet(work->unk_28[j], x + D_8011066C_staff[j], y, z);
                    }
                    break;
                case 8:
                    Hu3DModelPosSet(model, x - work->unk_36, y, z);
                    Hu3DModelPosSet(work->unk_28[0], x + work->unk_36, y, z);
                    break;
                case 10:
                    Hu3DModelPosSet(model, x - work->unk_36, y, z);
                    Hu3DModelPosSet(work->unk_28[0], x + work->unk_36, y, z);
                    break;
                case 3:
                    if (work->unk_36 == 0) {
                        work->unk_0C.x += 12.0f;
                        if (work->unk_0C.x >= 360.0f) {
                            work->unk_0C.x = 0.0f;
                            work->unk_36 = 30;
                        }
                        vel = (cosdf(work->unk_0C.x) + 1.0f) * 127.0f;
                        func_8001F9E4_main(model, vel);
                    } else {
                        func_8001F9E4_main(model, 0xFF);
                        work->unk_36--;
                    }
                    work->unk_18 += 3.0f;
                    if (work->unk_18 > 360.0f) {
                        work->unk_18 -= 360.0f;
                    }
                    vel = cosdf(work->unk_18) * 60.0f;
                    Hu3DModelRotSet(model, 0.0f, vel, 0.0f);
                case 0:
                default:
                    Hu3DModelPosSet(model, x, y, z);
                    break;
            }
        }
        HuPrcVSleep();
    }
}

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

void func_8010B514_staff(s16 arg0, s16 arg1) {
    UnkStaff_6 *recs;
    UnkStaff_6 *rec;
    s32 *files;
    s16 *animTbl;
    s16 *anims;
    s16 memberCount;
    s8 animCount;
    s32 i;
    s32 j;
    s16 grpId;

    switch (arg0) {
        case 0:
        default:
            animTbl = D_80111490_staff;
            memberCount = 24;
            files = D_80110AA0_staff;
            animCount = ARRAY_COUNT(D_80111490_staff);
            break;
        case 1:
            animTbl = D_801114D0_staff;
            memberCount = 28;
            files = D_80110B0C_staff;
            animCount = ARRAY_COUNT(D_801114D0_staff);
            break;
    }

    for (i = 0, anims = animTbl; i < animCount; i++, anims++) {
        *anims = HuSprAnimDataRead(*files++);
    }
    recs = HuMemAllocTag(arg1 * sizeof(UnkStaff_6), TAG_OVERLAY);
    for (i = 0, rec = recs; i < arg1; i++, rec++) {
        rec->unk_02 = 160;
        rec->unk_04 = 120;
        rec->unk_06 = 0;
        grpId = rec->unk_00 = HuSprGrpCreate(memberCount, 2);
        for (j = 0; j < memberCount; j++) {
            HuSprTPLvlSet(grpId, j, 0x100);
            HuSprAttrReset(grpId, j, 0xFFFF);
            HuSprAttrSet(grpId, j, 0x9000);
            HuSprScaleSet(grpId, j, 1.0f, 1.0f);
            HuSprAnimModeSet(grpId, j, 0);
            HuSprPriSet(grpId, j, 400);
            HuSprColorSet(grpId, j, 255, 255, 255);
            if (j != 0) {
                func_800554C4_main(grpId, j, 0);
            } else {
                func_800554C4_main(grpId, 0, -1);
            }
        }
    }
    switch (arg0) {
        case 0:
        default:
            D_801114C8_staff = recs;
            D_8011150C_staff = arg1;
            break;
        case 1:
            D_80111508_staff = recs;
            D_8011150E_staff = arg1;
            break;
    }
}

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

void func_8010BA30_staff(s16 arg0, s16 arg1, u32 arg2, s16 arg3, s16 arg4) {
    s16 xs[24];
    UnkStaff_6 *rec;
    s16 *anims;
    u8 *text;
    u8 *str;
    u8 *allocatedText;
    u8 allocated;
    s32 i;
    s16 maxCount;
    s16 spacing;
    s16 grpId;
    s16 narrowAdjust;
    s16 count;
    s16 x;
    s16 offset;
    s16 y;
    u8 c;

    switch (arg0) {
        case 0:
        default:
            rec = &D_801114C8_staff[arg1];
            anims = D_80111490_staff;
            maxCount = 24;
            narrowAdjust = -2;
            spacing = 10;
            break;
        case 1:
            rec = &D_80111508_staff[arg1];
            anims = D_801114D0_staff;
            maxCount = 28;
            narrowAdjust = 0;
            spacing = 10;
            break;
    }
    grpId = rec->unk_00;
    count = rec->unk_06;
    if (count != 0) {
        for (i = 0; i < count; i++) {
            HuSprDispOff(grpId, i);
        }
    }
    rec->unk_02 = arg3;
    rec->unk_04 = arg4;
    allocatedText = NULL;
    if (arg2 > 0x80000000) {
        allocated = FALSE;
        text = (u8 *)arg2;
    } else {
        text = func_800364DC_main((void *)arg2);
        allocated = TRUE;
        allocatedText = text;
    }
    str = text;
    x = 0;
    for (count = 1; count < maxCount; str++) {
        c = *str;
        if (c == 0) {
            break;
        }
        if (c >= 'a' && c <= 'z') {
            c -= 0x20;
        }
        if (c == 0x10 || c == 0x20 || c == 0x1A) {
            x += spacing;
        } else if (c >= 'A' && c <= 'Z') {
            c -= 'A';
            HuSprGrpMemberSet(grpId, count, anims[c], 0);
            if (count != 0) {
                func_800554C4_main(grpId, count, 0);
            }
            xs[count] = x;
            x += spacing;
            if (c == 8) {
                x += narrowAdjust;
            }
            count++;
        } else if (c == 0x33) {
            HuSprGrpMemberSet(grpId, count, anims[26], 0);
            if (count != 0) {
                func_800554C4_main(grpId, count, 0);
            }
            xs[count] = x;
            x += spacing;
            count++;
        } else if (c >= 0x5B && c <= 0x5C) {
            c -= 'A';
            HuSprGrpMemberSet(grpId, count, anims[c], 0);
            if (count != 0) {
                func_800554C4_main(grpId, count, 0);
            }
            xs[count] = x;
            x += spacing;
            count++;
        }
    }
    if (x > spacing) {
        x -= spacing;
    }
    offset = -(x >> 1);
    y = 0;
    HuSprPosSet(grpId, 0, rec->unk_02, rec->unk_04);
    for (i = 1; i < count; i++) {
        x = offset + xs[i];
        HuSprPosSet(grpId, i, x, y);
        HuSprDispOn(grpId, i);
    }
    rec->unk_06 = count;
    if (allocatedText != NULL) {
        func_800365E8_main(allocatedText);
    }
    (void)allocated; // Unused, but its store keeps the call result in v0.
}

StaffAnimEntry D_80110674_staff[18] = {
    { 0x200A4, "c000l_0_DEF" },
    { 0x300A4, "c001l_0_DEF" },
    { 0x700AB, "c002l_0_DEF" },
    { 0x400A4, "c003l_0_DEF" },
    { 0x500A9, "c004l_0_DEF" },
    { 0x600A4, "c005l_0_DEF" },
    { 0x90027, "c301l_0_DEF" },
    { 0x800A4, "c300l_0_DEF" },
    { 0xA0046, "c161n_0_DEF" },
    { 0xA0100, "c162n_0_DEF" },
    { 0xA00A3, "c103m_0_DEF" },
    { 0xA00B7, "c164m_0_DEF" },
    { 0xA002B, "c160n_0_DEF" },
    { 0xA00E5, "c165n_4_DEF" },
    { 0xA00A3, "c103m_0_DEF" },
    { 0xA00B7, "c164m_0_DEF" },
    { 0xA002B, "c180n_0_DEF" },
    { 0xA007E, "c204n_0_DEF" },
};
StaffModelEntry D_80110704_staff[38] = {
    { 0.8f, 0x200A0, 0x2009D, { 0, 0, 0 }, 0, 0, 1 },
    { 0.8f, 0x300A0, 0x3009D, { 0, 0, 0 }, 0, 0, 2 },
    { 0.8f, 0x700A0, 0x7009D, { 0, 0, 0 }, 0, 0, 3 },
    { 0.8f, 0x400A0, 0x4009D, { 0, 0, 0 }, 0, 0, 4 },
    { 0.8f, 0x500A0, 0x5009D, { -26, 2, 0 }, 0, 0, 5 },
    { 0.8f, 0x600A0, 0x6009D, { 30, 0, 0 }, 0, 0, 6 },
    { 0.8f, 0x90001, 0x90019, { 28, 0, 0 }, 0, 0, 7 },
    { 0.8f, 0x16004B, 0x8009D, { 0, 0, 0 }, 0, 0, 8 },
    { 0.6f, 0xA002E, 0xA0040, { 0, 30, 0 }, 0, 0, 9 },
    { 0.8f, 0xA00EE, 0xA00F4, { 0, -2, 0 }, 0, 0, 10 },
    { 0.8f, 0xA008E, 0xA00A1, { 0, 0, 0 }, 0, 0, 11 },
    { 0.8f, 0xA00A5, 0, { 0, 32, 0 }, 1, 0, 12 },
    { 0.8f, 0xA0000, 0xA000A, { 0, -45, -80 }, 0, 0, 13 },
    { 0.55f, 0xA00C4, 0xA00CB, { 0, 100, 0 }, 3, 0, 0 },
    { 0.9f, 0xA00BA, 0xA00C3, { 0, 30, 0 }, 4, 160, 0 },
    { 0.8f, 0xA00CE, 0xA00D8, { 0, 0, 0 }, 0, 0, 0 },
    { 0.8f, 0xA0136, 0xA0138, { 0, 30, 0 }, 1, 0, 0 },
    { 0.5f, 0xA010D, 0xA0116, { 0, 30, 0 }, 0, -15, 0 },
    { 0.5f, 0xA00D9, 0xA00DD, { 0, 30, 0 }, 1, 0, 0 },
    { 0.8f, 0xA00E7, 0, { 0, 35, 0 }, 2, 140, 0 },
    { 1.2f, 0xA013F, 0xA0141, { 0, 30, 0 }, 0, 0, 0 },
    { 0.6f, 0xA011B, 0xA011D, { 0, 30, 0 }, 0, 0, 0 },
    { 0.8f, 0xA0089, 0, { 0, 110, 0 }, 5, 0, 0 },
    { 0.8f, 0xA00A2, 0xA0090, { 0, 30, 0 }, 1, 0, 15 },
    { 0.8f, 0xA00B0, 0xA00B1, { 0, 30, 0 }, 0, 0, 16 },
    { 0.8f, 0xA0028, 0xA0019, { 0, 30, 0 }, 0, 0, 17 },
    { 0.8f, 0xA0063, 0xA006C, { 0, 30, 0 }, 0, 0, 0 },
    { 0.6f, 0xA0086, 0xA0088, { 0, 10, -80 }, 1, 0, 0 },
    { 0.4f, 0xA0154, 0, { 0, 30, -40 }, 8, 140, 0 },
    { 0.8f, 0xA014D, 0xA0153, { 0, 0, 0 }, 0, 0, 0 },
    { 0.8f, 0xA0156, 0, { 0, -25, -50 }, 6, 0, 0 },
    { 0.8f, 0xA008B, 0, { 0, 30, 0 }, 7, 0, 0 },
    { 0.75f, 0xA0117, 0, { 0, 30, -20 }, 10, 165, 0 },
    { 0.38f, 0x1301F4, 0, { 0, 116, 0 }, 11, 0, 0 },
    { 0.5f, 0x1301F5, 0, { 0, 45, 0 }, 0, 0, 0 },
    { 0.95f, 0xA0122, 0xA0128, { 0, 138, 0 }, 12, 0, 0 },
    { 0.8f, 0xA0075, 0x1D0084, { 0, 30, 0 }, 0, 0, 18 },
    { 0.0f, 0, 0, { 0, 0, 0 }, -1, 0, 0 },
};
s32 D_80110A94_staff[3] = { 0 }; /* Unreferenced. */
s32 D_80110AA0_staff[27] = {
    0x160000,
    0x160001,
    0x160002,
    0x160003,
    0x160004,
    0x160005,
    0x160006,
    0x160007,
    0x160008,
    0x160009,
    0x16000A,
    0x16000B,
    0x16000C,
    0x16000D,
    0x16000E,
    0x16000F,
    0x160010,
    0x160011,
    0x160012,
    0x160013,
    0x160014,
    0x160015,
    0x160016,
    0x160017,
    0x160018,
    0x160019,
    0x16004A,
};
s32 D_80110B0C_staff[28] = {
    0x160026,
    0x160027,
    0x160028,
    0x160029,
    0x16002A,
    0x16002B,
    0x16002C,
    0x16002D,
    0x16002E,
    0x16002F,
    0x160030,
    0x160031,
    0x160032,
    0x160033,
    0x160034,
    0x160035,
    0x160036,
    0x160037,
    0x160038,
    0x160039,
    0x16003A,
    0x16003B,
    0x16003C,
    0x16003D,
    0x16003E,
    0x16003F,
    0x160041,
    0x160040,
};
