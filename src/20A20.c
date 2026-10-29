#include "common.h"
#include "mallocblock.h"

#define CLAMP_S16(x) ((x) > 0x7FFF ? 0x7FFF : ((x) < -0x8000 ? -0x8000 : (x)))
#define READ16(p) (((p)[0] << 8) | (p)[1])
#define READ32(p) ((p)[0] << 24 | (p)[1] << 16 | (p)[2] << 8 | (p)[3])

typedef struct CollisionGridCell {
    /* 0x00 */ s32 faceOffset;
    /* 0x04 */ s16 faceCount;
} CollisionGridCell; // sizeof 0x8

typedef struct CollisionGrid {
    /* 0x00 */ s32 width;
    /* 0x04 */ s32 depth;
    /* 0x08 */ f32 cellWidth;
    /* 0x0C */ f32 cellDepth;
    /* 0x10 */ s16 *faces;
    /* 0x14 */ s16 *unk_14;
    /* 0x18 */ s16 *unk_18;
    /* 0x1C */ s16 *unk_1C;
    /* 0x20 */ CollisionGridCell *cells;
} CollisionGrid; // sizeof 0x24

typedef struct Hu3DSphere {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 radius;
} Hu3DSphere; // sizeof 0x10

typedef struct CollisionCircle {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 radius;
} CollisionCircle; // sizeof 0x10

typedef struct CollisionExtent {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 z;
} CollisionExtent; // sizeof 0x8

typedef struct CollisionRect {
    /* 0x00 */ f32 angle;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 z;
    /* 0x0C */ CollisionExtent extent;
} CollisionRect; // sizeof 0x14

typedef struct CollisionFanShape {
    /* 0x00 */ f32 spread;
    /* 0x04 */ f32 length;
    /* 0x08 */ f32 offset;
} CollisionFanShape; // sizeof 0xC

typedef struct CollisionFan {
    /* 0x00 */ f32 angle;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 z;
    /* 0x0C */ CollisionFanShape shape;
} CollisionFan; // sizeof 0x18

extern s16 D_800B19E0_main;
extern s16 D_800B19E2_main;
extern s16 D_800B19E4_main;
extern s16 *D_800B19E8_main;
extern CollisionGrid *D_800D1104_main;
extern s32 D_800C9940_main;
extern HuCamera *D_800D10F4_main;
extern s16 D_800D418E_main;
extern Mtx *MTXBuf;
extern s16 MTXBufNum;

void func_80017CD0_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80017D24_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80018044_main(HuMtx4F a, HuMtx4F b, HuMtx4F out);
void func_80019668_main(HmfData_UnkD0 *light);
void func_80024DF0_main(HmfData *hmf, s16 objectIndex, Mtx *dest, HuMtx4F mtx);

s32 func_80021550_main(f32 x, f32 z, Hu3DPoint *tri);
f32 func_80021F98_main(Hu3DPoint *points, s16 i0, s16 i1, s16 i2, f32 *centerX, f32 *centerZ);

void Hu3DAnimInit(s16 count) {
    s32 i;

    D_800B19E2_main = 0;
    D_800D1104_main = HuMemAllocTag(count * sizeof(CollisionGrid), 0x55F0);
    D_800B19E0_main = count;
    D_800B19E8_main = HuMemAllocTag(count * sizeof(s16), 0x55F0);
    for (i = 0; i < count; i++) {
        D_800B19E8_main[i] = i + 1;
    }
    D_800B19E4_main = 0;
}

s32 func_8001FED0_main(s16 index) {
    return D_800D1104_main[index].width == D_800D1104_main[index].depth;
}

s16 func_8001FF04_main(s16 model) {
    s16 index;
    u8 *data;
    u32 size;
    CollisionGrid *grid;
    CollisionGridCell *cell;
    s16 *faces;
    u16 x;
    u16 z;
    u32 i;
    union {
        s32 i;
        f32 f;
    } bits;

    if (D_800B19E2_main == D_800B19E0_main) {
        return -1;
    }
    index = D_800B19E4_main;
    D_800B19E4_main = D_800B19E8_main[index];
    data = HmfModelData[model].hmf->unk38;
    size = READ32(&data[4]) - 0x10;
    grid = &D_800D1104_main[index];
    grid->width = READ16(&data[8]);
    grid->depth = READ16(&data[10]);
    bits.i = READ32(&data[0x10]);
    grid->cellWidth = bits.f;
    bits.i = READ32(&data[0x14]);
    grid->cellDepth = bits.f;
    cell = grid->cells = HuMemAllocTag(grid->width * sizeof(CollisionGridCell) * grid->depth, 0x55F0);
    data += 0x18;
    grid->unk_14 = HuMemAllocTag(grid->width * sizeof(s16) * grid->depth, 0x55F0);
    grid->unk_18 = HuMemAllocTag(grid->width * sizeof(s16) * grid->depth, 0x55F0);
    grid->unk_1C = HuMemAllocTag(grid->width * sizeof(s16) * grid->depth, 0x55F0);
    for (z = 0; z < grid->depth; z++) {
        for (x = 0; x < grid->width; x++) {
            grid->unk_14[z * grid->width + x] = READ16(&data[0]);
            grid->unk_18[z * grid->width + x] = READ16(&data[2]);
            grid->unk_1C[z * grid->width + x] = READ16(&data[4]);
            cell->faceOffset = READ32(&data[6]);
            cell->faceCount = READ16(&data[10]);
            data += 12;
            cell++;
            size -= 12;
        }
    }
    faces = grid->faces = HuMemAllocTag(size, 0x55F0);
    for (i = 0; i < size; i += 2) {
        *faces++ = READ16(data);
        data += 2;
    }
    D_800B19E2_main++;
    return index;
}

f32 func_800202A8_main(f32 angle) {
    if (angle >= 360.0f) {
        angle -= 360.0f;
    } else if (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

s32 func_800202FC_main(Vec *vec) {
    f32 x = vec->x, y = vec->y, z = vec->z;
    f32 length = HuSqrtf(x * x + y * y + z * z);

    if (length == 0.0f) {
        return FALSE;
    }
    vec->x /= length;
    vec->y /= length;
    vec->z /= length;
    return TRUE;
}

s32 func_8002038C_main(Hu3DPoint *p0, Hu3DPoint *p1, Hu3DPoint *p2, Vec *out) {
    f32 d1x = (f32)p1->x - (f32)p0->x;
    f32 d1y = (f32)p1->y - (f32)p0->y;
    f32 d1z = (f32)p1->z - (f32)p0->z;
    f32 d2x = (f32)p2->x - (f32)p0->x;
    f32 d2y = (f32)p2->y - (f32)p0->y;
    f32 d2z = (f32)p2->z - (f32)p0->z;
    out->x = d1y * d2z - d1z * d2y;
    out->y = d1z * d2x - d1x * d2z;
    out->z = d1x * d2y - d1y * d2x;
    return func_800202FC_main(out);
}

f32 func_8002048C_main(f32 x, f32 z, Hu3DPoint *p, Hu3DPoint *q) {
    f32 px = p->x - x;
    f32 pz = p->z - z;
    f32 qx = q->x - x;
    f32 qz = q->z - z;
    return -(pz * qx - px * qz);
}

f32 func_800204F4_main(f32 x, f32 y, f32 z, Hu3DPoint *points, Hu3DQuad *quad) {
    Vec normal;
    Vec p;
    f32 nx, ny, nz;
    Hu3DPoint *p0 = &points[quad->vtx[1]];

    p.x = p0->x;
    p.y = p0->y;
    p.z = p0->z;
    func_8002038C_main(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]], &normal);
    nx = normal.x;
    ny = normal.y;
    nz = normal.z;
    return y + (nx * (p.x - x) + ny * (p.y - y) + nz * (p.z - z)) / ny;
}

s32 func_80020604_main(f32 x, f32 z, s16 *face, Hu3DPoint *points) {
    Vec normal;
    s32 count;
    s32 i;
    s32 next;

    func_8002038C_main(&points[face[1]], &points[face[2]], &points[face[3]], &normal);
    if (normal.y == 0.0f) {
        return FALSE;
    }
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

void func_8002087C_main(HmfModel *model, HuMtx4F mtx) {
    HmfSkeletonNode *node;
    HuMtx4F temp;

    D_800C9940_main = model->unk18;
    guMtxL2F(mtx, &D_800D10F4_main->mtxs[D_800D418E_main].lookAtMtx);
    if (model->pos.x != 0.0f || model->pos.y != 0.0f || model->pos.z != 0.0f) {
        func_80017C10_main(mtx, model->pos.x, model->pos.y, model->pos.z);
    }
    if (model->rot.x != 0.0f || model->rot.y != 0.0f || model->rot.z != 0.0f) {
        func_80017D24_main(mtx, model->rot.x, model->rot.y, model->rot.z);
    }
    if (model->scale.x != 1.0f || model->scale.y != 1.0f || model->scale.z != 1.0f) {
        func_80017CD0_main(mtx, model->scale.x, model->scale.y, model->scale.z);
    }
    func_80018044_main(model->mtx, mtx, mtx);
    node = model->hmf->unk68;
    guMtxIdentF(temp);
    if (node->unk08.x == 0.0f || node->unk08.y == 0.0f || node->unk08.z == 0.0f) {
        func_80017C10_main(temp, node->unk08.x, node->unk08.y, node->unk08.z);
    }
    if (node->unk14.x == 0.0f || node->unk14.y == 0.0f || node->unk14.z == 0.0f) {
        func_80017D24_main(temp, node->unk14.x, node->unk14.y, node->unk14.z);
    }
    if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
        func_80017CD0_main(temp, node->scale.x, node->scale.y, node->scale.z);
    }
    guMtxCatF(temp, mtx, mtx);
    guMtxF2L(mtx, &MTXBuf[MTXBufNum]);
}

#ifdef NON_MATCHING
/* Loop-invariant grid offset temps are allocated differently (extra spills, frame 0xD0 vs 0xC0) */
void func_80020B48_main(CollisionRect *rect, HmfModel *model) {
    HuMtx4F mtx;
    HuMtx4F ident;
    CollisionExtent *extent;
    s16 gridIndex;
    s32 minX;
    s32 maxX;
    s32 minZ;
    s32 maxZ;
    s32 x;
    s32 z;
    s32 cell;

    model->hmf->unkD0 = model->unkB4;
    extent = &rect->extent;
    if (model->unkB4 != NULL) {
        func_80019668_main(model->unkB4);
    }
    gridIndex = model->unk10;
    func_8002087C_main(model, mtx);
    guMtxIdentF(ident);
    x = (D_800D1104_main[gridIndex].width * D_800D1104_main[gridIndex].cellWidth / 2.0f + rect->x + model->pos.x -
         2.0f * sindf(rect->angle) * D_800D1104_main[gridIndex].cellWidth) /
        D_800D1104_main[gridIndex].cellWidth;
    x = abs(x);
    z = (D_800D1104_main[gridIndex].depth * D_800D1104_main[gridIndex].cellDepth / 2.0f + rect->z + model->pos.z -
         2.0f * cosdf(rect->angle) * D_800D1104_main[gridIndex].cellDepth) /
        D_800D1104_main[gridIndex].cellDepth;
    z = abs(z);
    minX = x - extent->x;
    maxX = x + extent->x + 1;
    minZ = z - extent->z;
    maxZ = z + extent->z + 1;
    if (minX < 0) {
        minX = 0;
    }
    if (minZ < 0) {
        minZ = 0;
    }
    if (maxX > D_800D1104_main[gridIndex].width) {
        maxX = D_800D1104_main[gridIndex].width;
    }
    if (maxZ > D_800D1104_main[gridIndex].depth) {
        maxZ = D_800D1104_main[gridIndex].depth;
    }
    for (z = minZ; z < maxZ; z++) {
        for (x = minX; x < maxX; x++) {
            cell = z * D_800D1104_main[gridIndex].width + x;
            if (D_800D1104_main[gridIndex].unk_14[cell] != -1) {
                func_80024DF0_main(model->hmf, D_800D1104_main[gridIndex].unk_14[cell], &MTXBuf[MTXBufNum], mtx);
            }
            if (D_800D1104_main[gridIndex].unk_18[cell] != -1) {
                func_80024DF0_main(model->hmf, D_800D1104_main[gridIndex].unk_18[cell], &MTXBuf[MTXBufNum], mtx);
            }
            if (D_800D1104_main[gridIndex].unk_1C[cell] != -1) {
                func_80024DF0_main(model->hmf, D_800D1104_main[gridIndex].unk_1C[cell], &MTXBuf[MTXBufNum], mtx);
            }
        }
    }
    MTXBufNum++;
}
#else
INCLUDE_ASM("asm/nonmatchings/20A20", func_80020B48_main);
#endif

#ifdef NON_MATCHING
/* Prologue differs (target has dead code around the initial sindf/cosdf calls); register allocation */
void func_80020E94_main(CollisionFan *fan, HmfModel *model) {
    Hu3DPoint tri[3];
    HuMtx4F mtx;
    HuMtx4F ident;
    CollisionFanShape *shape;
    s16 gridIndex;
    s32 value;
    s32 x;
    s32 z;
    s32 cell;
    s16 object;
    f32 x0;
    f32 x1;
    f32 z0;
    f32 z1;

    model->hmf->unkD0 = model->unkB4;
    shape = &fan->shape;
    if (model->unkB4 != NULL) {
        func_80019668_main(model->unkB4);
    }
    gridIndex = model->unk10;
    func_8002087C_main(model, mtx);
    guMtxIdentF(ident);
    sindf(fan->angle);
    cosdf(fan->angle);
    tri[0].y = tri[1].y = tri[2].y = 0;
    value = D_800D1104_main[gridIndex].width * D_800D1104_main[gridIndex].cellWidth / 2.0f + fan->x +
            sindf(fan->angle) * shape->offset;
    tri[0].x = CLAMP_S16(value);
    value = D_800D1104_main[gridIndex].depth * D_800D1104_main[gridIndex].cellDepth / 2.0f + fan->z +
            cosdf(fan->angle) * shape->offset;
    tri[0].z = CLAMP_S16(value);
    value = tri[0].x - sindf(shape->spread / 2.0f + fan->angle) * shape->length;
    tri[1].x = CLAMP_S16(value);
    value = tri[0].z - cosdf(shape->spread / 2.0f + fan->angle) * shape->length;
    tri[1].z = CLAMP_S16(value);
    value = tri[0].x - sindf(fan->angle - shape->spread / 2.0f) * shape->length;
    tri[2].x = CLAMP_S16(value);
    value = tri[0].z - cosdf(fan->angle - shape->spread / 2.0f) * shape->length;
    tri[2].z = CLAMP_S16(value);
    for (z = 0; z < D_800D1104_main[gridIndex].depth; z++) {
        z0 = z * D_800D1104_main[gridIndex].cellDepth + model->pos.z;
        z1 = z0 + D_800D1104_main[gridIndex].cellDepth;
        for (x = 0; x < D_800D1104_main[gridIndex].width; x++) {
            cell = z * D_800D1104_main[gridIndex].width + x;
            x0 = x * D_800D1104_main[gridIndex].cellWidth + model->pos.x;
            x1 = x0 + D_800D1104_main[gridIndex].cellWidth;
            object = D_800D1104_main[gridIndex].unk_14[cell];
            if (object != -1) {
                if (func_80021550_main(x0, z0, tri) == TRUE || func_80021550_main(x1, z0, tri) == TRUE ||
                    func_80021550_main(x0, z1, tri) == TRUE || func_80021550_main(x1, z1, tri) == TRUE) {
                    func_80024DF0_main(model->hmf, object, &MTXBuf[MTXBufNum], ident);
                }
            }
            object = D_800D1104_main[gridIndex].unk_18[cell];
            if (object != -1) {
                if (func_80021550_main(x0, z0, tri) == TRUE || func_80021550_main(x1, z0, tri) == TRUE ||
                    func_80021550_main(x0, z1, tri) == TRUE || func_80021550_main(x1, z1, tri) == TRUE) {
                    func_80024DF0_main(model->hmf, object, &MTXBuf[MTXBufNum], mtx);
                }
            }
            object = D_800D1104_main[gridIndex].unk_1C[cell];
            if (object != -1) {
                if (func_80021550_main(x0, z0, tri) == TRUE || func_80021550_main(x1, z0, tri) == TRUE ||
                    func_80021550_main(x0, z1, tri) == TRUE || func_80021550_main(x1, z1, tri) == TRUE) {
                    func_80024DF0_main(model->hmf, object, &MTXBuf[MTXBufNum], mtx);
                }
            }
        }
    }
    MTXBufNum++;
}
#else
INCLUDE_ASM("asm/nonmatchings/20A20", func_80020E94_main);
#endif

s32 func_80021550_main(f32 x, f32 z, Hu3DPoint *tri) {
    s32 i;
    s32 next;
    f32 side;

    if (func_8002048C_main(x, z, &tri[0], &tri[1]) > 0.0f) {
        for (i = 1; i < 3; i++) {
            next = (i + 1) % 3;
            side = func_8002048C_main(x, z, &tri[i], &tri[next]);
            if (side == 0.0f) {
                return TRUE;
            }
            if (side < 0.0f) {
                return FALSE;
            }
        }
    } else {
        for (i = 1; i < 3; i++) {
            next = (i + 1) % 3;
            side = func_8002048C_main(x, z, &tri[i], &tri[next]);
            if (side == 0.0f) {
                return TRUE;
            }
            if (side > 0.0f) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

#ifdef NON_MATCHING
/* Loop-invariant grid offset temps are allocated differently (extra spill, frame 0xE8 vs 0xE0) */
void func_800216F8_main(CollisionCircle *circle, HmfModel *model) {
    HuMtx4F mtx;
    HuMtx4F ident;
    s16 gridIndex;
    s32 minX;
    s32 maxX;
    s32 minZ;
    s32 maxZ;
    s32 x;
    s32 z;
    s32 cell;
    f32 dx;
    f32 dz;
    f32 *radius = &circle->radius;

    model->hmf->unkD0 = model->unkB4;
    if (model->unkB4 != NULL) {
        func_80019668_main(model->unkB4);
    }
    gridIndex = model->unk10;
    func_8002087C_main(model, mtx);
    guMtxIdentF(ident);
    minX = (circle->x - *radius + D_800D1104_main[gridIndex].width * D_800D1104_main[gridIndex].cellWidth / 2.0f) / D_800D1104_main[gridIndex].cellWidth;
    maxX = (circle->x + *radius + D_800D1104_main[gridIndex].width * D_800D1104_main[gridIndex].cellWidth / 2.0f) / D_800D1104_main[gridIndex].cellWidth;
    minZ = (circle->z - *radius + D_800D1104_main[gridIndex].depth * D_800D1104_main[gridIndex].cellDepth / 2.0f) / D_800D1104_main[gridIndex].cellDepth;
    maxZ = (circle->z + *radius + D_800D1104_main[gridIndex].depth * D_800D1104_main[gridIndex].cellDepth / 2.0f) / D_800D1104_main[gridIndex].cellDepth;
    if (minX < 0) {
        minX = 0;
    }
    if (minZ < 0) {
        minZ = 0;
    }
    if (D_800D1104_main[gridIndex].width < maxX) {
        maxX = D_800D1104_main[gridIndex].width;
    }
    if (D_800D1104_main[gridIndex].depth < maxZ) {
        maxZ = D_800D1104_main[gridIndex].depth;
    }
    for (z = minZ; z < maxZ; z++) {
        dz = (z * D_800D1104_main[gridIndex].cellDepth + model->pos.z + D_800D1104_main[gridIndex].cellDepth / 2.0f) -
             (D_800D1104_main[gridIndex].depth * D_800D1104_main[gridIndex].cellDepth / 2.0f + circle->z);
        for (x = minX; x < maxX; x++) {
            dx = (x * D_800D1104_main[gridIndex].cellWidth + model->pos.x + D_800D1104_main[gridIndex].cellWidth / 2.0f) -
                 (D_800D1104_main[gridIndex].width * D_800D1104_main[gridIndex].cellWidth / 2.0f + circle->x);
            if (HuSqrtf(dx * dx + dz * dz) < *radius) {
                cell = z * D_800D1104_main[gridIndex].width + x;
                if (D_800D1104_main[gridIndex].unk_14[cell] != -1) {
                    func_80024DF0_main(model->hmf, D_800D1104_main[gridIndex].unk_14[cell], &MTXBuf[MTXBufNum], mtx);
                }
                if (D_800D1104_main[gridIndex].unk_18[cell] != -1) {
                    func_80024DF0_main(model->hmf, D_800D1104_main[gridIndex].unk_18[cell], &MTXBuf[MTXBufNum], mtx);
                }
                if (D_800D1104_main[gridIndex].unk_1C[cell] != -1) {
                    func_80024DF0_main(model->hmf, D_800D1104_main[gridIndex].unk_1C[cell], &MTXBuf[MTXBufNum], mtx);
                }
            }
        }
    }
    MTXBufNum++;
}
#else
INCLUDE_ASM("asm/nonmatchings/20A20", func_800216F8_main);
#endif

void func_80021AF4_main(void) {
    HuMemFreeAllWithTag(0x55F0);
    D_800B19E0_main = 0;
    D_800B19E2_main = 0;
}

void func_80021B20_main(s16 index) {
    CollisionGrid *grid;

    if (D_800B19E2_main != 0) {
        grid = &D_800D1104_main[index];
        HuMemFree(grid->cells);
        HuMemFree(grid->unk_14);
        HuMemFree(grid->unk_18);
        HuMemFree(grid->unk_1C);
        HuMemFree(grid->faces);
        D_800B19E2_main--;
        D_800B19E8_main[index] = D_800B19E4_main;
        D_800B19E4_main = index;
    }
}

void func_80021BE0_main(Hu3DQuadPool *pool, u16 numQuads) {
    pool->quads = HuMemAllocTag(numQuads * sizeof(Hu3DQuad *), 0x55F0);
}

#ifdef NON_MATCHING
/* Register allocation: pool and maxX are swapped (s7/s8) */
void func_80021C14_main(s16 model, Hu3DQuadPool *pool, s32 (*callback)(s32, s16 *, Hu3DPoint *, Vec *), Vec *pos) {
    s32 i;
    s32 x;
    s32 z;
    s32 maxX;
    s32 minX;
    s32 maxZ;
    s32 minZ;
    Hu3DQuad **out;
    s16 *face;
    CollisionGridCell *cell;
    CollisionGrid *grid;
    HmfData *hmf;

    pool->curQuad = 0;
    pool->numQuads = 0;
    hmf = HmfModelData[model].hmf;
    grid = &D_800D1104_main[HmfModelData[model].unk10];
    x = (grid->width * grid->cellWidth / 2.0f + pos->x) / grid->cellWidth;
    z = (grid->depth * grid->cellDepth / 2.0f + pos->z) / grid->cellDepth;
    minX = x - 1;
    maxX = x + 2;
    minZ = z - 1;
    maxZ = z + 2;
    if (minX < 0) {
        minX = 0;
    }
    if (minZ < 0) {
        minZ = 0;
    }
    if (maxX > grid->width) {
        maxX = grid->width;
    }
    if (maxZ > grid->depth) {
        maxZ = grid->depth;
    }
    out = pool->quads;
    for (z = minZ; z < maxZ; z++) {
        for (x = minX; x < maxX; x++) {
            cell = &grid->cells[z * grid->width + x];
            if (cell->faceCount != 0) {
                face = &grid->faces[cell->faceOffset];
                for (i = 0; i < cell->faceCount; i++) {
                    if (callback(((u16)face[0] >> 14) + 2, &face[1], (Hu3DPoint *)hmf->unk50, pos)) {
                        *out++ = (Hu3DQuad *)face;
                        pool->numQuads++;
                    }
                    face += ((u16)face[0] >> 14) + 3;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/20A20", func_80021C14_main);
#endif

s32 func_80021E64_main(u16 count, s16 *vtx, Hu3DPoint *points, Hu3DSphere *sphere) {
    f32 centerX;
    f32 centerZ;
    f32 dist;

    if (count == 4) {
        dist = func_80021F98_main(points, vtx[0], vtx[2], vtx[3], &centerX, &centerZ) + sphere->radius;
        centerX -= sphere->pos.x;
        centerZ -= sphere->pos.z;
        if (centerX * centerX + centerZ * centerZ < dist * dist) {
            return TRUE;
        }
    }
    dist = func_80021F98_main(points, vtx[0], vtx[1], vtx[2], &centerX, &centerZ) + sphere->radius;
    centerX -= sphere->pos.x;
    centerZ -= sphere->pos.z;
    if (centerX * centerX + centerZ * centerZ < dist * dist) {
        return TRUE;
    }
    return FALSE;
}

f32 func_80021F98_main(Hu3DPoint *points, s16 i0, s16 i1, s16 i2, f32 *centerX, f32 *centerZ) {
    f32 dx;
    f32 dz;
    f32 dx2;
    f32 dz2;

    *centerX = (points[i0].x + points[i1].x + points[i2].x) / 3;
    *centerZ = (points[i0].z + points[i1].z + points[i2].z) / 3;
    dx = points[i0].x - *centerX;
    dz = points[i0].z - *centerZ;
    dx2 = points[i1].x - *centerX;
    dz2 = points[i1].z - *centerZ;
    if (dx * dx + dz * dz < dx2 * dx2 + dz2 * dz2) {
        dx = dx2;
        dz = dz2;
    }
    dx2 = points[i2].x - *centerX;
    dz2 = points[i2].z - *centerZ;
    if (dx * dx + dz * dz < dx2 * dx2 + dz2 * dz2) {
        dx = dx2;
        dz = dz2;
    }
    return HuSqrtf(dx * dx + dz * dz);
}

Hu3DQuad *func_80022198_main(Hu3DQuadPool *pool) {
    if (pool->curQuad == pool->numQuads) {
        return NULL;
    }
    return pool->quads[pool->curQuad++];
}

void func_800221CC_main(Hu3DQuadPool *pool, s32 offset, u16 mode) {
    s32 pos;

    switch (mode) {
        case 0:
            if (offset >= 0 && offset + pool->curQuad < pool->numQuads) {
                pool->curQuad = offset;
            }
            break;
        case 1:
            pos = offset + pool->curQuad;
            if (pos >= 0 && pos < pool->numQuads) {
                pool->curQuad += offset;
            }
            break;
        case 2:
            if (offset <= 0 && offset + pool->curQuad >= 0) {
                pool->curQuad = pool->numQuads - 1 + offset;
            }
            break;
    }
}

void func_80022288_main(Hu3DQuadPool *pool) {
    HuMemFree(pool->quads);
}
