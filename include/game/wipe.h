#ifndef _GAME_WIPE_H
#define _GAME_WIPE_H

#include "ultra64.h"

typedef struct {
    s16 width;
    s16 height;
    u8 *pixels;
} WipeTexture;

typedef enum
{
    WIPE_STRIPES = 0,
    WIPE_CIRCLE = 1,
    WIPE_STARS = 2,
    WIPE_STRIPES2 = 3,
    WIPE_FADE = 11,
    WIPE_BOO = 12,
} EWipeType;

#define WIPE_TYPE_NORMAL 0
#define WIPE_TYPE_CROSS 0xFE
#define WIPE_TYPE_PREV 0xFF

#define WIPE_MODE_DUMMY 0
#define WIPE_MODE_IN 1
#define WIPE_MODE_OUT 2
#define WIPE_MODE_BLANK 3

#ifndef NO_EXTERN_VARIABLES
extern u8 wipeType;
extern u8 wipeMode;
extern u8 wipeStat;
extern f32 wipeDuration;
extern f32 wipeTime;
#endif

void WipeInit(void);
void WipeCreateIn(s16, s16);
void WipeCreateOut(s16, s16);
s32 WipeStatGet(void);
void WipeColorSet(u8, u8, u8);

void WipeExecAlways(Gfx **gfx);
u8 *WipeMalloc(u32 size);
s32 WipeFadeIn(Gfx **gfx);
s32 WipeFadeOut(Gfx **gfx);
void WipeColorFill(Gfx **gfx, u8 alpha, Gfx *displayList);
s32 WipeCrossFadeIn(Gfx **gfx);
s32 WipeCrossFadeOut(Gfx **gfx);
void WipeScreenCopy(Gfx **gfx, u16 *image);
void WipeFrameStill(Gfx **gfx);
void WipeScreenDraw(Gfx **gfx, u16 *image);
s32 WipeFrameStillExec(Gfx **gfx);
s32 WipeShapeIn(Gfx **gfx);
s32 WipeShapeOut(Gfx **gfx);
u8 *WipeTexRead(s32 file);
void WipeCircleDraw(Gfx **gfx, f32 scale, f32 alpha);
s32 WipeTileIn(Gfx **gfx);
void WipeTileDraw(Gfx **gfx, f32 progress);
s32 WipeTileOut(Gfx **gfx);
s32 WipeBlindExec(Gfx **gfx);
void WipeBlindDraw(Gfx **gfx, f32 progress);
s32 WipeImageOut(Gfx **gfx, s32 file);
s32 WipeShape2In(Gfx **gfx);
s32 WipeShape2Out(Gfx **gfx);
void WipeScreenCapture(void);
s32 WipeScreenCaptureEnd(void);
void WipeScreenHookCreate(void);
void WipeScreenHookKill(void);
void WipeScreenHook(Gfx **arg0, s32 arg1, s32 arg2);
void WipeScreenHook2(Gfx **arg0, s32 arg1, s32 arg2);
void WipeScreenStillSet(void);
void WipeScreenStillReset(void);

#endif //_GAME_WIPE_H
