#ifndef _GAME_MAPSPACE_H
#define _GAME_MAPSPACE_H

#include "ultra64.h"
#include "types.h"
#include "humath.h"

void func_8000D960_main(HuMtx4F in, HuMtx4F out);
s32 Hitcheck_Triangle_with_Sphere(Vec *triangle, Vec *sphereOrigin, f32 sphereRadius, Vec *closestPoint);
s32 PrecalcPntToTriangle(Vec *origin, Vec *u, Vec *v, Vec *normal, Vec *point, Vec *out);
s32 Hitcheck_Quadrangle_with_Sphere(Vec *quad, Vec *sphereOrigin, f32 sphereRadius, Vec *closestPoint);
void func_8000E344_main(Vec *a, Vec *b, Vec *out);

#endif
