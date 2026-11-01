#ifndef _GAME_GRAPHICS_H
#define _GAME_GRAPHICS_H

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

void func_8000EA10_main(void **arg1, s32 arg2, s32 arg3, u64 **arg4, s32 *arg5);
void *func_8000EB60_main(void);
graphicsMessage *func_8000EF10_main(void);
u8 func_8000EF64_main(Gfx *arg0, u16 arg1, s32 arg2, OSMesgQueue *arg3, s32 arg4);
void func_8000F040_main(u16 size);


#endif
