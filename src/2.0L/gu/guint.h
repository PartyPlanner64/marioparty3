#ifndef _GUINT_H_
#define _GUINT_H_

#include "ultra64.h"

typedef union {
    struct {
        unsigned int hi;
        unsigned int lo;
    } word;

    double d;
} du;

typedef union {
    unsigned int i;
    float f;
} fu;

typedef float Matrix[4][4];

extern float __libm_qnan_f;

#define ROUND(d) (int)(((d) >= 0.0) ? ((d) + 0.5) : ((d) - 0.5))
#define ABS(d) ((d) > 0) ? (d) : -(d)

#endif
