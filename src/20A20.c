#include "common.h"
#include "mallocblock.h"

typedef struct Hu3DPoint {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
} Hu3DPoint; // sizeof 0x6

typedef struct Hu3DQuad {
    /* 0x00 */ s16 vtx[4];
} Hu3DQuad; // sizeof 0x8

typedef struct Hu3DQuadPool {
    /* 0x00 */ Hu3DQuad **quads;
    /* 0x04 */ u16 numQuads;
    /* 0x06 */ u16 curQuad;
} Hu3DQuadPool; // sizeof 0x8

typedef struct Hu3DAnimPlayer {
    /* 0x00 */ s32 numFrames;
    /* 0x04 */ s32 numTracks;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ void *unk_10;
    /* 0x14 */ s16 *unk_14;
    /* 0x18 */ s16 *unk_18;
    /* 0x1C */ s16 *unk_1C;
    /* 0x20 */ void *unk_20;
} Hu3DAnimPlayer; // sizeof 0x24

extern s16 D_800B19E0_main;
extern s16 D_800B19E2_main;
extern Hu3DAnimPlayer *D_800D1104_main;

INCLUDE_ASM("asm/nonmatchings/20A20", Hu3DAnimInit);

s32 func_8001FED0_main(s16 index) {
    return D_800D1104_main[index].numFrames == D_800D1104_main[index].numTracks;
}

INCLUDE_ASM("asm/nonmatchings/20A20", func_8001FF04_main);

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

INCLUDE_ASM("asm/nonmatchings/20A20", func_800204F4_main);

INCLUDE_ASM("asm/nonmatchings/20A20", func_80020604_main);

INCLUDE_ASM("asm/nonmatchings/20A20", func_8002087C_main);

INCLUDE_ASM("asm/nonmatchings/20A20", func_80020B48_main);

INCLUDE_ASM("asm/nonmatchings/20A20", func_80020E94_main);

INCLUDE_ASM("asm/nonmatchings/20A20", func_80021550_main);

INCLUDE_ASM("asm/nonmatchings/20A20", func_800216F8_main);

void func_80021AF4_main(void) {
    HuMemFreeAllWithTag(0x55F0);
    D_800B19E0_main = 0;
    D_800B19E2_main = 0;
}

INCLUDE_ASM("asm/nonmatchings/20A20", func_80021B20_main);

void func_80021BE0_main(Hu3DQuadPool *pool, u16 numQuads) {
    pool->quads = HuMemAllocTag(numQuads * sizeof(Hu3DQuad *), 0x55F0);
}

INCLUDE_ASM("asm/nonmatchings/20A20", func_80021C14_main);

INCLUDE_ASM("asm/nonmatchings/20A20", func_80021E64_main);

INCLUDE_ASM("asm/nonmatchings/20A20", func_80021F98_main);

Hu3DQuad *func_80022198_main(Hu3DQuadPool *pool) {
    if (pool->curQuad == pool->numQuads) {
        return NULL;
    }
    return pool->quads[pool->curQuad++];
}

INCLUDE_ASM("asm/nonmatchings/20A20", func_800221CC_main);

INCLUDE_ASM("asm/nonmatchings/20A20", func_80022288_main);
