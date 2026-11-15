#ifndef _LIBM_H_
#define _LIBM_H_

#include "humath.h"

extern const s32 __sinCosSignTbl[12];
extern const f64 __invFactTbl[100];
extern const f32 __invFactTblF[100];
extern const f32 __sinTblF[91];
extern const f64 __sinTbl[91];

extern f64 __libmPrecision;
extern f64 __cosSign;
extern f32 __cosSignF;

#endif
