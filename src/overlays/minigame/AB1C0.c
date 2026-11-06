#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfcoll.h"
#include "game/hmfspr.h"
#include "game/hu3d.h"

typedef struct {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ u8 unk04;
} func_800D8778_minigame_ObjData;

typedef struct {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ char unk08[0xC];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ char unk18[0x80];
    /* 0x98 */ f32 unk98;
} func_800D8640_minigame_ObjData;

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 unk0C;
} func_800DC7D8_minigame_Arg; // Size 0x10

extern Vec D_800EBDD0_minigame;
extern f32 D_800EB764_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;
extern f32 D_800EB770_minigame;
extern f32 D_800EBE2C_minigame;
extern f32 D_800EC5D8_minigame;
extern Vec D_800EC298_minigame[];
extern HuMtx4F D_800EC240_minigame;

void func_800DFCDC_minigame(f32 x, f32 z, f32 scale);
void func_800E0430_minigame(f32 x, f32 y, f32 z);
void func_800E048C_minigame(f32 arg0, f32 arg1, f32 arg2);
void func_800E2CA4_minigame(omObjData *, f32);
void func_800E2C68_minigame(HuMtx4F mtx, Vec *arg1);

f32 func_800D8640_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, f32 arg2) {
    func_800D8640_minigame_ObjData *data = arg0->data;
    Vec pos;
    f32 y;

    if (data->unk06 & 0x50) {
        y = data->unk14 - data->unk98;
        if ((y < arg2 + arg1->unk34) & (arg2 < y)) {
            pos.x = 0.0f;
            pos.y = y;
            pos.z = 0.0f;
            if (arg0->trans.x != 0.0f || arg0->trans.y != 0.0f || arg0->trans.z != 0.0f || arg0->rot.x != 0.0f ||
                arg0->rot.y != 0.0f || arg0->rot.z != 0.0f) {
                func_800E2C68_minigame(D_800EC240_minigame, &pos);
            }
            arg1->unk8C = pos.y;
            arg1->unk53[3] = data->unk04;
        }
    }
    return data->unk14;
}

f32 func_800D8778_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, f32 arg2, f32 arg3, Vec *arg4) {
    func_800D8778_minigame_ObjData *data = arg0->data;
    Vec unused;

    if ((arg2 < arg3 + arg1->unk34) & (arg3 < arg2)) {
        if (arg4->y < 0.0f) {
            unused.x = 0.0f;
            unused.y = arg2;
            unused.z = 0.0f;
            arg1->unk8C = arg2;
            arg1->unk53[3] = data->unk04;
            (void)unused;
            return -65536.0f;
        }
    }
    return arg2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D8818_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D89CC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D9028_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D972C_minigame);

f32 func_800D9F10_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    u8 player = data->unk53[0];
    f32 ret = arg0->trans.y;

    if (data->unk00[player] & 2) {
        ret = arg1;
    }
    return ret;
}

s32 func_800D9F3C_minigame(Vec *pos, Hu3DQuad *quad, Hu3DPoint *points) {
    Vec normal;
    Hu3DPoint *p0;
    f32 px;
    f32 py;
    f32 pz;

    func_8002038C_main(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]], &normal);
    p0 = &points[quad->vtx[1]];
    px = p0->x;
    py = p0->y;
    pz = p0->z;
    px -= pos->x;
    py -= pos->y;
    pz -= pos->z;
    return (px * normal.x + py * normal.y + pz * normal.z < 0.0f) ? -1 : 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA054_minigame);

f32 func_800DA204_minigame(f32 x, f32 y, f32 z, Hu3DPoint *p, Hu3DPoint *q, Vec *normal) {
    f32 ax = p->x - x;
    f32 ay = p->y - y;
    f32 az = p->z - z;
    f32 bx = q->x - x;
    f32 by = q->y - y;
    f32 bz = q->z - z;

    return (ay * bz - az * by) * normal->x + (az * bx - ax * bz) * normal->y + (ax * by - ay * bx) * normal->z;
}

s32 func_800DA2E0_minigame(Vec *pos, s16 *face, Hu3DPoint *points, Vec *normal) {
    f32 x = pos->x;
    f32 y = pos->y;
    f32 z = pos->z;
    s32 count;
    s32 i;
    s32 next;

    count = ((u16)face[0] >> 14) + 2;
    face++;
    if (func_800DA204_minigame(x, y, z, &points[face[0]], &points[face[1]], normal) > 0.0f) {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (func_800DA204_minigame(x, y, z, &points[face[i]], &points[face[next]], normal) < 0.0f) {
                return FALSE;
            }
        }
    } else {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (func_800DA204_minigame(x, y, z, &points[face[i]], &points[face[next]], normal) > 0.0f) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

s32 func_800DA540_minigame(Vec *pos, s16 *face, Hu3DPoint *points) {
    f32 x;
    f32 z;
    s32 count;
    s32 i;
    s32 next;

    if (((u16)face[0] & 0x3F00) > 0x200) {
        return FALSE;
    }
    x = pos->x;
    z = pos->z;
    count = ((u16)face[0] >> 14) + 2;
    face++;
    if (func_8002048C_main(x, z, &points[face[0]], &points[face[1]]) > 0.0f) {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (func_8002048C_main(x, z, &points[face[i]], &points[face[next]]) < 0.0f) {
                return FALSE;
            }
        }
    } else {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (func_8002048C_main(x, z, &points[face[i]], &points[face[next]]) > 0.0f) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA768_minigame);

void func_800DB628_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 limit = data->unk48;
    f32 angle;

    if (HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame) > limit ||
        fabs(D_800EBE2C_minigame) > limit || fabs(D_800EC5D8_minigame) > limit) {
        angle = data->unk3C;
        D_800EBE2C_minigame = -sindf(angle) * data->unk40;
        D_800EC5D8_minigame = -cosdf(angle) * data->unk40;
    }
}

s32 func_800DB704_minigame(s32 count, s16 *vtx, Hu3DPoint *points, Vec *pos) {
    return func_800DA540_minigame(pos, vtx - 1, points);
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DB724_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DBCF4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DC354_minigame);

void func_800DC7D8_minigame(omObjData *arg0, func_800DC7D8_minigame_Arg *arg1) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 x = arg1->x;
    f32 z = arg1->z;
    f32 dist;
    Vec dir;

    dist = data->unk9C - (HuSqrtf(x * x + z * z) + arg1->unk0C);
    if (dist <= 0.0f) {
        func_800DFCDC_minigame(x, z, dist);
        dir.x = x;
        dir.y = 0.0f;
        dir.z = z;
        func_800202FC_main(&dir);
        func_800E048C_minigame(arg1->x * dir.x, arg1->y, arg1->z * dir.z);
        func_800E0430_minigame(-arg1->x, 0.0f, -arg1->z);
        D_800EB736_minigame++;
    }
}

void func_800DC8E4_minigame(omObjData *arg0, func_800DC7D8_minigame_Arg *arg1, f32 arg2) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 x = arg1->x;
    f32 z = arg1->z;
    f32 dist;
    Vec dir;

    if (arg1->y < arg2 + data->unk14 && data->unk14 - data->unk98 - arg2 < arg1->y) {
        dist = HuSqrtf(x * x + z * z) - data->unk9C;
        if (0.0f <= dist && dist <= arg1->unk0C) {
            func_800DFCDC_minigame(x, z, arg1->unk0C - dist);
            dir.x = x;
            dir.y = 0.0f;
            dir.z = z;
            func_800202FC_main(&dir);
            func_800E048C_minigame(-arg1->x * dir.x, arg1->y, -arg1->z * dir.z);
            func_800E0430_minigame(arg1->x, 0.0f, arg1->z);
            D_800EB736_minigame++;
        }
    }
}

s32 func_800DCA34_minigame(func_800DC7D8_minigame_Arg *arg0, func_800E1BA8_minigame_ObjData *data) {
    f32 x = arg0->x;
    f32 y = arg0->y;
    f32 z = arg0->z;
    f32 dx;
    f32 dz;

    if (x <= data->unkA0) {
        dx = data->unkA0 - x;
        if (z <= data->unkA4) {
            dz = data->unkA4 - z;
            if (HuSqrtf(dx * dx + dz * dz) - arg0->unk0C < 0.0f) {
                func_800E048C_minigame(data->unkA0, y, data->unkA4);
                func_800E0430_minigame(x - data->unkA0, 0.0f, z - data->unkA4);
                D_800EB736_minigame++;
                return 0;
            }
        } else if (data->unkAC <= z) {
            dz = data->unkAC - z;
            if (HuSqrtf(dx * dx + dz * dz) - arg0->unk0C < 0.0f) {
                func_800E048C_minigame(data->unkA0, y, data->unkAC);
                func_800E0430_minigame(x - data->unkA0, 0.0f, z - data->unkAC);
                D_800EB736_minigame++;
                return 0;
            }
        }
    } else if (arg0->x >= data->unkA8.f) {
        dx = data->unkA8.f - x;
        if (z <= data->unkA4) {
            dz = data->unkA4 - z;
            if (HuSqrtf(dx * dx + dz * dz) - arg0->unk0C < 0.0f) {
                func_800E048C_minigame(data->unkA8.f, y, data->unkA4);
                func_800E0430_minigame(x - data->unkA8.f, 0.0f, z - data->unkA4);
                D_800EB736_minigame++;
                return 0;
            }
        } else if (data->unkAC <= z) {
            dz = data->unkAC - z;
            if (HuSqrtf(dx * dx + dz * dz) - arg0->unk0C < 0.0f) {
                func_800E048C_minigame(data->unkA8.f, y, data->unkAC);
                func_800E0430_minigame(x - data->unkA8.f, 0.0f, z - data->unkAC);
                D_800EB736_minigame++;
                return 0;
            }
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DCCB0_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DD1F4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DD530_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DDB60_minigame);

void func_800DDD70_minigame(omObjData *arg0) {
    D_800EBDD0_minigame.x = arg0->trans.x;
    D_800EBDD0_minigame.y = arg0->trans.y;
    D_800EBDD0_minigame.z = arg0->trans.z;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DDD94_minigame);

void func_800DFCDC_minigame(f32 x, f32 z, f32 scale) {
    Vec dir;

    dir.x = x;
    dir.y = 0.0f;
    dir.z = z;
    func_800202FC_main(&dir);
    D_800EBE2C_minigame += scale * dir.x;
    D_800EC5D8_minigame += scale * dir.z;
}

f32 func_800DFD48_minigame(f32 arg0) {
    if (arg0 < D_800EB76C_minigame) {
        return D_800EB76C_minigame;
    }
    if (arg0 < D_800EB768_minigame) {
        return D_800EB768_minigame;
    }
    if (arg0 < D_800EB764_minigame) {
        return D_800EB764_minigame;
    }
    return arg0;
}

void func_800DFD9C_minigame(omObjData *arg0, f32 x, f32 y, f32 z) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    s16 temp;

    func_800E5690_minigame(arg0, 0x10);
    temp = data->unk21[2];
    func_80014850_main(temp);
    func_800146DC_main(temp, 4, 4);
    Hu3DModelPosSet(arg0->model[2], x, y, z);
    data->unk40 = D_800EB770_minigame;
    func_800E1810_minigame();
}

void func_800DFE44_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 time;

    time = Hu3DMotionShiftTimeGet(arg0->model[0]);
    if (time == -1.0f) {
        time = HmfModelData[arg0->model[0]].motTime;
    }
    if (time >= 28.0f && time <= 29.0f) {
        func_800E2CA4_minigame(arg0, (data->unk40 + D_800EB768_minigame) * data->unkCC);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DFF3C_minigame);

void func_800E0430_minigame(f32 x, f32 y, f32 z) {
    D_800EC298_minigame[D_800EB736_minigame].x = x;
    D_800EC298_minigame[D_800EB736_minigame].y = y;
    D_800EC298_minigame[D_800EB736_minigame].z = z;
    func_800202FC_main(&D_800EC298_minigame[D_800EB736_minigame]);
}

void func_800E048C_minigame(f32 arg0, f32 arg1, f32 arg2) {
    D_800EBEB8_minigame[D_800EB736_minigame].unk00 = arg0;
    D_800EBEB8_minigame[D_800EB736_minigame].unk04 = arg1;
    D_800EBEB8_minigame[D_800EB736_minigame].unk08 = arg2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800E04C8_minigame);
