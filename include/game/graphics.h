#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include "ultra64.h"
#include "game/nnsched.h"

typedef struct {
    Gfx *unk00;
    u16 unk04;
    s32 unk08;
    OSMesgQueue *unk0C;
    s32 unk10;     // OSMesg to send to unk0C
} graphicsMessage; // OSMesg

typedef struct combinedStruct {
    OSTask task;
    OSMesgQueue *completionQueue;
    OSMesg completionMsg;
} swapChainTaskQueue;

void func_8000F024_main(void **pool, u16 size, u16 segment); // Init graphics frame buffer pool
void func_8000F04C_main(u64 **);            // Set gThreadStacks
void func_8000F088_main(s32 *);             // Set graphics state
void func_8000F094_main(u32);               // Set unk swap chain state
void func_8000EBEC_main(void *);            // Swap Chain Loop


typedef struct {
    u8 unk00[0x20];
} unkGraphicsMessage2; // OSMesg

void func_8004D85C_main(void);
void func_8004D878_main(void);

#endif
