#ifndef _WIPE_H
#define _WIPE_H

#include "ultra64.h"

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

extern u8 wipeType;
extern u8 wipeMode;
extern u8 wipeStat;
extern f32 wipeDuration;
extern f32 wipeTime;

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
void func_8006265C_main(Gfx **gfx, u16 *image);
void WipeFrameStill(Gfx **gfx);
void func_80062884_main(Gfx **gfx, u16 *image);
s32 func_80062A30_main(Gfx **gfx);
s32 func_80063454_main(Gfx **gfx);
s32 func_80063510_main(Gfx **gfx);
u8 *func_800635F4_main(s32 file);
void func_800636D8_main(Gfx **gfx, f32 scale, f32 alpha);
s32 func_800640EC_main(Gfx **gfx);
void func_800641C8_main(Gfx **gfx, f32 progress);
s32 func_80065094_main(Gfx **gfx);
s32 func_8006515C_main(Gfx **gfx);
void func_800651F0_main(Gfx **gfx, f32 progress);
s32 WipeImageOut(Gfx **gfx, s32 file);
s32 func_80065D80_main(Gfx **gfx);
s32 func_80065E88_main(Gfx **gfx);
void func_80065F8C_main(void);
s32 func_80066048_main(void);
void func_8006608C_main(void);
void func_80066164_main(void);
void func_8006619C_main(Gfx **arg0, s32 arg1, s32 arg2);
void func_800661D4_main(Gfx **arg0, s32 arg1, s32 arg2);
void func_800661F8_main(void);
void func_80066228_main(void);

#endif //_WIPE_H
