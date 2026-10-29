#ifndef _INITIALIZE_H
#define _INITIALIZE_H

#include "ultra64.h"

typedef struct {
    /* 0x0 */ u32 inst1;
    /* 0x4 */ u32 inst2;
    /* 0x8 */ u32 inst3;
    /* 0xC */ u32 inst4;
} __osExceptionVector;

extern char *(*__printfunc)(char *dst, const char *src, unsigned int count);

#endif
