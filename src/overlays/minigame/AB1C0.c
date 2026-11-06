#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfcoll.h"
#include "game/hmfspr.h"
#include "game/hu3d.h"
#include "game/mapspace.h"
#include "math.h"

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

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 radius;
    /* 0x10 */ Vec prev;
} func_800DBCF4_minigame_Arg; // Size 0x1C

extern Vec D_800EBDD0_minigame;
extern f32 D_800EB760_minigame;
extern f32 D_800EB764_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;
extern f32 D_800EB770_minigame;
extern f32 D_800EBE2C_minigame;
extern f32 D_800EC5D8_minigame;
extern Vec D_800EC298_minigame[];
extern HuMtx4F D_800EC240_minigame;
extern HuMtx4F D_800EBE30_minigame;
extern omObjData *D_800EBE70_minigame[];
extern s8 D_800EC286_minigame;
extern u16 D_800EC288_minigame;

void func_800DFCDC_minigame(f32 x, f32 z, f32 scale);
void func_800E19FC_minigame(func_800E1BA8_minigame_ObjData *, s32);
f32 func_800E2ED4_minigame(f32, f32, f32, f32);
void func_800E0430_minigame(f32 x, f32 y, f32 z);
void func_800E048C_minigame(f32 arg0, f32 arg1, f32 arg2);
void func_800E2CA4_minigame(omObjData *, f32);
void func_800E2C68_minigame(HuMtx4F mtx, Vec *arg1);
void func_800E2BD4_minigame(HuMtx4F mtx, Vec *arg1);
s8 func_800DD530_minigame(omObjData *arg0, func_800DC7D8_minigame_Arg *arg1, f32 arg2);
s32 func_800E1510_minigame(s8 arg0);
s32 func_800E2DA4_minigame(omObjData *arg0, omObjData *item);
s32 func_800E4510_minigame(omObjData *arg0, omObjData *arg1);
void func_800E454C_minigame(omObjData *arg0, omObjData *arg1, f32 x, f32 z, u16 arg4);
void func_800E4C88_minigame(omObjData *arg0, u8 arg1, f32 x, f32 y, f32 z, f32 rotX, f32 rotY);

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

f32 func_800D8818_minigame(f32 x, f32 y, f32 z, Hu3DPoint *points, Hu3DQuad *quad, Vec *dir, Vec *out) {
    Vec normal;
    Hu3DPoint *p0 = &points[quad->vtx[1]];
    f32 px = p0->x;
    f32 py = p0->y;
    f32 pz = p0->z;
    f32 dx = dir->x;
    f32 dy = dir->y;
    f32 dz = dir->z;
    f32 nx, ny, nz;
    f32 denom;
    f32 t;

    func_8002038C_main(p0, &points[quad->vtx[2]], &points[quad->vtx[3]], &normal);
    nx = normal.x;
    ny = normal.y;
    nz = normal.z;
    denom = nx * dx + ny * dy + nz * dz;
    t = (nx * (px - x) + ny * (py - y) + nz * (pz - z)) / denom;
    out->x = x += dx * t;
    out->y = y += dy * t;
    out->z = z += dz * t;
    return y;
}

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

s32 func_800DA054_minigame(func_800DC7D8_minigame_Arg *pos, Hu3DQuad *quad, Hu3DPoint *points) {
    Vec normal;
    Hu3DPoint *p0;
    f32 px;
    f32 py;
    f32 pz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 proj;
    s32 side = -1;
    s32 flags;

    flags = (u16)quad->vtx[0] & 0x3F00;
    if (flags <= 0x200) {
        return FALSE;
    }
    func_8002038C_main(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]], &normal);
    p0 = &points[quad->vtx[1]];
    px = p0->x;
    py = p0->y;
    pz = p0->z;
    dx = px - pos->x;
    dy = py - pos->y;
    dz = pz - pos->z;
    dist = dx * normal.x + dy * normal.y + dz * normal.z;
    if (dist >= 0.0f) {
        side = 1;
    }
    if (fabsf(dist) > pos->unk0C) {
        return FALSE;
    }
    proj = dx * normal.x + dy * normal.y + dz * normal.z;
    pos->x += proj * normal.x;
    pos->y += proj * normal.y;
    pos->z += proj * normal.z;
    return side;
}

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

s32 func_800DBCF4_minigame(s32 count, s16 *vtx, Hu3DPoint *points, func_800DBCF4_minigame_Arg *arg3) {
    func_800DC7D8_minigame_Arg sphere;
    func_800DC7D8_minigame_Arg prev;
    Vec closest;
    Vec quad[4];
    Vec tri[3];
    Vec dir;
    s32 side;
    s32 hit;
    f32 dx;
    f32 dz;
    f32 depth;
    s16 *face;

    prev.x = sphere.x = arg3->pos.x + D_800EBE2C_minigame;
    prev.y = sphere.y = arg3->pos.y;
    prev.z = sphere.z = arg3->pos.z + D_800EC5D8_minigame;
    sphere.unk0C = prev.unk0C = arg3->radius;
    face = vtx - 1;
    side = func_800DA054_minigame(&sphere, (Hu3DQuad *)face, points);
    if (side == 0) {
        return 0;
    }
    if (((u16)face[0] >> 14) + 2 == 4) {
        quad[0].x = points[vtx[0]].x;
        quad[0].y = points[vtx[0]].y;
        quad[0].z = points[vtx[0]].z;
        quad[1].x = points[vtx[1]].x;
        quad[1].y = points[vtx[1]].y;
        quad[1].z = points[vtx[1]].z;
        quad[2].x = points[vtx[2]].x;
        quad[2].y = points[vtx[2]].y;
        quad[2].z = points[vtx[2]].z;
        quad[3].x = points[vtx[3]].x;
        quad[3].y = points[vtx[3]].y;
        quad[3].z = points[vtx[3]].z;
        hit = Hitcheck_Quadrangle_with_Sphere(quad, (Vec *)&prev, sphere.unk0C, &closest);
    } else {
        tri[0].x = points[vtx[0]].x;
        tri[0].y = points[vtx[0]].y;
        tri[0].z = points[vtx[0]].z;
        tri[1].x = points[vtx[1]].x;
        tri[1].y = points[vtx[1]].y;
        tri[1].z = points[vtx[1]].z;
        tri[2].x = points[vtx[2]].x;
        tri[2].y = points[vtx[2]].y;
        tri[2].z = points[vtx[2]].z;
        hit = Hitcheck_Triangle_with_Sphere(tri, (Vec *)&prev, sphere.unk0C, &closest);
    }
    if (hit == 1) {
        prev.x = arg3->prev.x + D_800EBE2C_minigame;
        prev.y = arg3->prev.y;
        prev.z = arg3->prev.z + D_800EC5D8_minigame;
        func_800E2BD4_minigame(D_800EC240_minigame, &closest);
        func_800E048C_minigame(closest.x, closest.y, closest.z);
        func_8002038C_main(&points[vtx[0]], &points[vtx[1]], &points[vtx[2]], &D_800EC298_minigame[D_800EB736_minigame]);
        D_800EB736_minigame++;
        dx = closest.x - prev.x;
        dz = closest.z - prev.z;
        depth = sphere.unk0C - HuSqrtf(dx * dx + dz * dz);
        if (side > 0) {
            sphere.x = D_800EBDD0_minigame.x;
            sphere.y = D_800EBDD0_minigame.y;
            sphere.z = D_800EBDD0_minigame.z;
            func_800E2BD4_minigame(D_800EBE30_minigame, (Vec *)&sphere);
            if (func_800D9F3C_minigame((Vec *)&sphere, (Hu3DQuad *)(vtx - 1), points) < 0) {
                dir.x = sphere.x - prev.x;
                dir.y = sphere.y - prev.y;
                dir.z = sphere.z - prev.z;
                func_800202FC_main(&dir);
                if (func_800DA2E0_minigame((Vec *)&prev, vtx - 1, points, &dir) == hit) {
                    depth = HuSqrtf(dx * dx + dz * dz) + sphere.unk0C;
                }
            } else {
                depth = 0.0f;
            }
        }
        if (0.0f <= depth) {
            func_800DFCDC_minigame(-dx, -dz, depth);
        }
    }
    return hit;
}

void func_800DC354_minigame(omObjData *arg0, func_800DC7D8_minigame_Arg *arg1, Vec *arg2) {
    s32 i = D_800EB736_minigame;
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 minX = data->unkA0 + arg1->unk0C;
    f32 minZ = data->unkA4 + arg1->unk0C;
    f32 maxX = data->unkA8.f - arg1->unk0C;
    f32 maxZ = data->unkAC - arg1->unk0C;
    f32 half;

    if (arg1->x <= minX) {
        func_800E048C_minigame(data->unkA0, arg1->y, arg1->z);
        func_800E0430_minigame(1.0f, 0.0f, 0.0f);
        D_800EB736_minigame++;
    }
    if (maxX <= arg1->x) {
        func_800E048C_minigame(data->unkA8.f, arg1->y, arg1->z);
        func_800E0430_minigame(-1.0f, 0.0f, 0.0f);
        D_800EB736_minigame++;
    }
    if (arg1->z <= minZ) {
        func_800E048C_minigame(arg1->x, arg1->y, data->unkA4);
        func_800E0430_minigame(0.0f, 0.0f, 1.0f);
        D_800EB736_minigame++;
    }
    if (maxZ <= arg1->z) {
        func_800E048C_minigame(arg1->x, arg1->y, data->unkAC);
        func_800E0430_minigame(0.0f, 0.0f, -1.0f);
        D_800EB736_minigame++;
    }
    if (i == D_800EB736_minigame) {
        half = arg1->unk0C * 0.5f;
        if (arg1->x <= minX - half) {
            func_800E048C_minigame(data->unkA0, arg1->y, arg1->z);
            func_800E0430_minigame(1.0f, 0.0f, 0.0f);
            D_800EB736_minigame++;
        }
        if (maxX + half <= arg1->x) {
            func_800E048C_minigame(data->unkA8.f, arg1->y, arg1->z);
            func_800E0430_minigame(-1.0f, 0.0f, 0.0f);
            D_800EB736_minigame++;
        }
        if (arg1->z <= minZ - half) {
            func_800E048C_minigame(arg1->x, arg1->y, data->unkA4);
            func_800E0430_minigame(0.0f, 0.0f, 1.0f);
            D_800EB736_minigame++;
        }
        if (maxZ + half <= arg1->z) {
            func_800E048C_minigame(arg1->x, arg1->y, data->unkAC);
            func_800E0430_minigame(0.0f, 0.0f, -1.0f);
            D_800EB736_minigame++;
        }
    }
    // minX/minZ are reused as the offset to each new contact point.
    while (i < D_800EB736_minigame) {
        minX = D_800EBEB8_minigame[i].unk00 - arg1->x;
        minZ = D_800EBEB8_minigame[i].unk08 - arg1->z;
        func_800DFCDC_minigame(-minX, -minZ, arg1->unk0C - HuSqrtf(minX * minX + minZ * minZ));
        if (arg0->trans.x != 0.0f || arg0->trans.y != 0.0f || arg0->trans.z != 0.0f || arg0->rot.x != 0.0f ||
            arg0->rot.y != 0.0f || arg0->rot.z != 0.0f) {
            func_800E2BD4_minigame(D_800EC240_minigame, (Vec *)&D_800EBEB8_minigame[i]);
        }
        i++;
    }
}

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

void func_800DCCB0_minigame(omObjData *arg0, func_800DC7D8_minigame_Arg *arg1, Vec *arg2, f32 arg3) {
    s32 i = D_800EB736_minigame;
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 x = arg1->x;
    f32 z = arg1->z;
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
    f32 edgeX;
    f32 edgeZ;

    if (arg1->y < arg3 + data->unk14 && data->unk14 - data->unk98 - arg3 < arg1->y) {
        minX = data->unkA0 - arg1->unk0C;
        minZ = data->unkA4 - arg1->unk0C;
        maxX = data->unkA8.f + arg1->unk0C;
        maxZ = data->unkAC + arg1->unk0C;
        if (((minX <= x) & (x < maxX)) && ((minZ < z) & (z < maxZ))) {
            if (func_800DCA34_minigame(arg1, data) == 1) {
                if (minX <= x && x <= data->unkA0) {
                    if (data->unkA4 <= arg1->z && arg1->z <= data->unkAC) {
                        edgeX = data->unkA0;
                        if (edgeX == arg1->x) {
                            edgeX += 1.0f;
                        }
                        func_800E048C_minigame(edgeX, arg1->y, arg1->z);
                        func_800E0430_minigame(-1.0f, 0.0f, 0.0f);
                        D_800EB736_minigame++;
                    }
                } else if (x <= maxX && data->unkA8.f <= x) {
                    if (data->unkA4 <= arg1->z && arg1->z <= data->unkAC) {
                        edgeX = data->unkA8.f;
                        if (edgeX == arg1->x) {
                            edgeX -= 1.0f;
                        }
                        func_800E048C_minigame(edgeX, arg1->y, arg1->z);
                        func_800E0430_minigame(1.0f, 0.0f, 0.0f);
                        D_800EB736_minigame++;
                    }
                } else if (minZ <= z && z <= data->unkA4) {
                    if (data->unkA0 <= arg1->x && arg1->x <= data->unkA8.f) {
                        edgeZ = data->unkA4;
                        if (edgeZ == arg1->z) {
                            edgeZ += 1.0f;
                        }
                        func_800E048C_minigame(arg1->x, arg1->y, edgeZ);
                        func_800E0430_minigame(0.0f, 0.0f, -1.0f);
                        D_800EB736_minigame++;
                    }
                } else if (z <= maxZ && data->unkAC <= z) {
                    if (data->unkA0 <= arg1->x && arg1->x <= data->unkA8.f) {
                        edgeZ = data->unkAC;
                        if (edgeZ == arg1->z) {
                            edgeZ -= 1.0f;
                        }
                        func_800E048C_minigame(arg1->x, arg1->y, edgeZ);
                        func_800E0430_minigame(0.0f, 0.0f, 1.0f);
                        D_800EB736_minigame++;
                    }
                }
            }
            for (; i < D_800EB736_minigame; i++) {
                if (arg0->trans.x != 0.0f || arg0->trans.y != 0.0f || arg0->trans.z != 0.0f || arg0->rot.x != 0.0f ||
                    arg0->rot.y != 0.0f || arg0->rot.z != 0.0f) {
                    func_800E2BD4_minigame(D_800EC240_minigame, (Vec *)&D_800EBEB8_minigame[i]);
                }
                minX = D_800EBEB8_minigame[i].unk00 - arg2->x;
                minZ = D_800EBEB8_minigame[i].unk08 - arg2->z;
                func_800DFCDC_minigame(minX, minZ, HuSqrtf(minX * minX + minZ * minZ) - arg1->unk0C);
            }
        }
    }
}

void func_800DD1F4_minigame(omObjData *obj, Vec *pos, f32 arg2) {
    func_800E1BA8_minigame_ObjData *data;
    f32 speed;
    f32 dx, dy, dz;
    f32 limit;
    s32 i;

    if (D_800EB736_minigame == 0) {
        return;
    }
    data = obj->data;
    if (data->unk52 == 0) {
        f32 base = data->unk40;
        f32 scale = data->unkB4;

        if (data->unk50 & 6) {
            speed = base * 0.6f * scale;
        } else {
            speed = base * scale;
        }
    } else {
        speed = data->unk40;
    }
    if (data->unk38 != 1000.0f) {
        speed *= data->unk4C;
    }
    for (i = 0; i < D_800EB736_minigame; i++) {
        dx = D_800EBEB8_minigame[i].unk00 - pos->x;
        dy = D_800EBEB8_minigame[i].unk04 - pos->y;
        dz = D_800EBEB8_minigame[i].unk08 - pos->z;
        HuSqrtf(dx * dx + dy * dy + dz * dz);
        if (func_800E2ED4_minigame(sindf(data->unk3C) * speed + D_800EBE2C_minigame,
                                   cosdf(data->unk3C) * speed + D_800EC5D8_minigame, dx, dz) > 0.9f &&
            data->unk38 != 1000.0f && data->unk40 > D_800EB764_minigame) {
            limit = data->unk40;
            if (data->unk50 & 6) {
                limit *= 0.6f;
            }
            limit *= data->unk4C * data->unkB4 * 0.98f;
            if (HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame) <
                limit) {
                if (data->unk50 & 8) {
                    data->unk40 = -D_800EB760_minigame;
                } else {
                    data->unk40 = -D_800EB76C_minigame;
                }
                func_800E5690_minigame(obj, 30);
                func_800E19FC_minigame(data, 7);
                omVibrate(data->unk59, 5, 0, 5);
                return;
            }
        }
        if (arg2 != 0.0f) {
            data->unk40 = arg2;
            func_800E19FC_minigame(data, 7);
            omVibrate(data->unk59, 2, 3, 10);
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DD530_minigame);

void func_800DDB60_minigame(omObjData *obj, Vec *dir) {
    func_800E1BA8_minigame_ObjData *data = obj->data;
    f32 rotX;
    f32 rotZ;
    f32 curX;
    f32 curZ;

    if (data->unk40 > D_800EB764_minigame) {
        rotX = -(atan2df(dir->y, dir->z) - 90.0f);
        rotZ = atan2df(dir->y, dir->x) - 90.0f;
        curX = data->unk9C;
        curZ = data->unkA4;
        if (curX < rotX) {
            if (rotX < (data->unk9C += 4.0f)) {
                data->unk9C = rotX;
            }
        } else if (rotX < curX) {
            if ((data->unk9C -= 4.0f) < rotX) {
                data->unk9C = rotX;
            }
        }
        if (curZ < rotZ) {
            if (rotZ < (data->unkA4 += 4.0f)) {
                data->unkA4 = rotZ;
            }
        } else if (rotZ < curZ) {
            if ((data->unkA4 -= 4.0f) < rotZ) {
                data->unkA4 = rotZ;
            }
        }
    } else {
        if (fabs(data->unk9C) > 2.0) {
            obj->rot.x = data->unk9C *= 0.3;
        }
        if (fabs(data->unkA4) > 2.0) {
            obj->rot.z = data->unkA4 *= 0.3;
        }
    }
    obj->rot.x = data->unk9C;
    obj->rot.z = data->unkA4;
}

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

void func_800DFF3C_minigame(omObjData *arg0, f32 x, f32 y, f32 z) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    func_800E1BA8_minigame_ObjData *otherData;
    A96F0_ObjData *itemData;
    omObjData *other;
    func_800DC7D8_minigame_Arg pos;
    f32 time;
    f32 angle;
    f32 dist;
    f32 dx, dy, dz;
    f32 px, py, pz;
    f32 rot;
    u16 i;

    time = Hu3DMotionShiftTimeGet(arg0->model[0]);
    if (time == -1.0f) {
        time = HmfModelData[arg0->model[0]].motTime;
    }
    if ((time < 16.0f) | (time > 20.0f)) {
        return;
    }
    if (data->unkBE != 0) {
        D_800EC288_minigame++;
        return;
    }
    if (data->unk50 & 0x400) {
        return;
    }
    dist = data->unk64 + data->unk48;
    angle = data->unk3C;
    px = x + sindf(angle) * dist;
    py = y;
    pz = z + cosdf(angle) * dist;
    data->unkF0 = 1;
    for (i = 0; i < D_800EC280_minigame; i++) {
        other = D_800EC598_minigame[i];
        otherData = other->data;
        if (otherData->unk5C & 0x8C00) {
            continue;
        }
        if (otherData->unk50 & 7) {
            continue;
        }
        if (otherData->unkBE != 0) {
            continue;
        }
        if (otherData->unk50 & 0x400) {
            continue;
        }
        if (data == otherData) {
            continue;
        }
        if (func_800E4510_minigame(arg0, other) != 1) {
            continue;
        }
        dx = other->trans.x - px;
        dy = other->trans.y - py;
        dz = other->trans.z - pz;
        if (HuSqrtf(dx * dx + dy * dy + dz * dz) < otherData->unk48 + 30.0f) {
            func_800E454C_minigame(arg0, other, dx, dz, i);
        }
    }
    if (!(data->unk50 & 0x17)) {
        for (i = 0; i < D_800EC1B8_minigame; i++) {
            other = D_800EBE70_minigame[i];
            itemData = other->data;
            if (!(itemData->unk50 & 0x20)) {
                continue;
            }
            if (itemData->unk50 & 0x10) {
                continue;
            }
            if (data->unkBE != 0) {
                D_800EC288_minigame++;
                continue;
            }
            dx = other->trans.x - px;
            dy = other->trans.y - py;
            dz = other->trans.z - pz;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz) - (itemData->unk48 + data->unk48);
            if (dist < 0.0f) {
                if (data->unkEC == NULL || data->unkEC(arg0, other) != 1) {
                    func_800E2DA4_minigame(arg0, other);
                }
            }
        }
    }
    pos.x = sindf(angle) * data->unk48 + arg0->trans.x;
    pos.y = py;
    pos.z = cosdf(angle) * data->unk48 + arg0->trans.z;
    pos.unk0C = data->unk64;
    data->unk53[2] = func_800DD530_minigame(arg0, &pos, -D_800EB760_minigame);
    if (D_800EB736_minigame != 0 && func_800E1510_minigame(D_800EC286_minigame) == 1) {
        rot = atan2df(D_800EBEB8_minigame[0].unk00 - arg0->trans.x, D_800EBEB8_minigame[0].unk08 - arg0->trans.z);
        func_800E4C88_minigame(arg0, 6, px, py, pz, 0.0f, rot + 180.0f);
    }
    D_800EB736_minigame = 0;
    D_800EBE2C_minigame = D_800EC5D8_minigame = 0.0f;
}

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
