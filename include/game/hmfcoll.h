#ifndef _GAME_HMFCOLL_H
#define _GAME_HMFCOLL_H

#include "ultra64.h"
#include "humath.h"
#include "common_structs.h"
#include "game/hu3d.h"
#include "types.h"

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

typedef struct Hu3DSphere {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 radius;
} Hu3DSphere; // sizeof 0x10

void MapCollInit(s16 count);
s32 MapCollSquareCheck(s16 index);
s16 MapCollCreate(s16 model);
f32 HuAngleWrap(f32 angle);
s32 MapVecNormalize(Vec *vec);
s32 MapTriNormalGet(Hu3DPoint *p0, Hu3DPoint *p1, Hu3DPoint *p2, Vec *out);
f32 MapXZCross(f32 x, f32 z, Hu3DPoint *p, Hu3DPoint *q);
f32 MapCalcPoint(f32 x, f32 y, f32 z, Hu3DPoint *points, Hu3DQuad *quad);
s32 MapIflnnerPolygon(f32 x, f32 z, s16 *face, Hu3DPoint *points);
void Hu3DModelMtxGet(HmfModel *model, HuMtx4F mtx);
void MapCullFan(struct CollisionFan *fan, struct HmfModel *model);
s32 MapIflnnerTriangle(f32 x, f32 z, Hu3DPoint *tri);
void MapCollAllKill(void);
void MapCollKill(s16 index);
void Hu3DQuadPoolInit(Hu3DQuadPool *pool, u16 numQuads);
void Hu3DQuadPoolCollect(s16 model, Hu3DQuadPool *pool, s32 (*callback)(s32, s16 *, Hu3DPoint *, Vec *), Vec *pos);
f32 MapCircumcircleGet(Hu3DPoint *points, s16 i0, s16 i1, s16 i2, f32 *centerX, f32 *centerZ);
Hu3DQuad *Hu3DQuadPoolNext(Hu3DQuadPool *pool);
void Hu3DQuadPoolSeek(Hu3DQuadPool *pool, s32 offset, u16 mode);
void Hu3DQuadPoolFree(Hu3DQuadPool *pool);

#endif
