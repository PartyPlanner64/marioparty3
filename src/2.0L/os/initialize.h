#ifndef _INITIALIZE_H
#define _INITIALIZE_H

#include "ultra64.h"

typedef struct {
    /* 0x00 */ u32 magic;
    /* 0x04 */ u32 get;
    /* 0x08 */ u8 unk_08[0x14 - 0x08];
    /* 0x14 */ u32 put;
    /* 0x18 */ u8 unk_18[0x20 - 0x18];
    /* 0x20 */ u8 data[0x10000 - 0x20];
} ISVDbg;

typedef struct {
    /* 0x0 */ u32 inst1;
    /* 0x4 */ u32 inst2;
    /* 0x8 */ u32 inst3;
    /* 0xC */ u32 inst4;
} __osExceptionVector;

extern char *(*__printfunc)(char *dst, const char *src, unsigned int count);

#endif
