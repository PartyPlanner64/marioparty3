#ifndef _GAME_TEXLOAD_H
#define _GAME_TEXLOAD_H

#include "ultra64.h"
#include "types.h"

void HuLoadTextureTile(Gfx **gdl, u16 *timg, s32 fmt, s32 siz, s32 width, s32 height, s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void HuLoadMultiTile(Gfx **gdl, void *timg, s32 fmt, s32 siz, s32 width, s32 height, s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt, s32 tile, s32 tmem);
void HuLoadTextureBlock(Gfx **gdl, void *timg, s32 fmt, s32 siz, s32 width, s32 height, s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void HuLoadTextureBlock_4b(Gfx **gdl, void *timg, s32 fmt, u32 width, u32 height, s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void HuLoadMultiBlock(Gfx **gdl, void *timg, s32 fmt, s32 siz, s32 width, s32 height, s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt, s32 tile, s32 tmem);
void HuLoadMultiBlock_4b(Gfx **gdl, void *timg, s32 fmt, u32 width, u32 height, s32 uls, s32 ult, s32 lrs, s32 lrt, s32 pal, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt, s32 tile, s32 tmem);
void HuMtx2DRotTrans(HuMtx4F mf, f64 x, f64 y, f64 angle);
void HuMtxF2LTrans(f32 *pos, HuMtx4F mf, Mtx *m);

#endif
