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

void HuGfxFBPoolSet(void **pool, u16 size, u16 segment); // Init graphics frame buffer pool
void HuGfxStackSet(u64 **);            // Set gThreadStacks
void HuGfxUcodeSet(s32 *);             // Set graphics state
void HuGfxModeSet(u32);               // Set unk swap chain state
void HuGfxThreadMain(void *);            // Swap Chain Loop


typedef struct {
    u8 unk00[0x20];
} unkGraphicsMessage2; // OSMesg

void HuGfxInit(void **arg1, s32 arg2, s32 arg3, u64 **arg4, s32 *arg5);
void *HuGfxFBNextGet(void);
graphicsMessage *HuGfxMesgAlloc(void);
u8 HuGfxTaskSend(Gfx *arg0, u16 arg1, s32 arg2, OSMesgQueue *arg3, s32 arg4);
void HuGfxFBCountSet(u16 size);


#endif
