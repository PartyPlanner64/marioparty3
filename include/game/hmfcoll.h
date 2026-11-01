#ifndef _GAME_HMFCOLL_H
#define _GAME_HMFCOLL_H

#include "ultra64.h"
#include "humath.h"
#include "common_structs.h"
#include "game/hu3d.h"
#include "types.h"

void Hu3DAnimInit(s16 count);
s32 func_8001FED0_main(s16 index);
s16 func_8001FF04_main(s16 model);
f32 func_800202A8_main(f32 angle);
s32 func_800202FC_main(Vec *vec);
s32 func_8002038C_main(Hu3DPoint *p0, Hu3DPoint *p1, Hu3DPoint *p2, Vec *out);
f32 func_8002048C_main(f32 x, f32 z, Hu3DPoint *p, Hu3DPoint *q);
f32 func_800204F4_main(f32 x, f32 y, f32 z, Hu3DPoint *points, Hu3DQuad *quad);
s32 func_80020604_main(f32 x, f32 z, s16 *face, Hu3DPoint *points);
void func_8002087C_main(HmfModel *model, HuMtx4F mtx);
void func_80020E94_main(void *, struct HmfModel *);
s32 func_80021550_main(f32 x, f32 z, Hu3DPoint *tri);
void func_80021AF4_main(void);
void func_80021B20_main(s16 index);
void func_80021BE0_main(Hu3DQuadPool *pool, u16 numQuads);
void func_80021C14_main(s16 model, Hu3DQuadPool *pool, s32 (*callback)(s32, s16 *, Hu3DPoint *, Vec *), Vec *pos);
f32 func_80021F98_main(Hu3DPoint *points, s16 i0, s16 i1, s16 i2, f32 *centerX, f32 *centerZ);
Hu3DQuad *func_80022198_main(Hu3DQuadPool *pool);
void func_800221CC_main(Hu3DQuadPool *pool, s32 offset, u16 mode);
void func_80022288_main(Hu3DQuadPool *pool);

#endif
