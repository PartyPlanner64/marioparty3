#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/texload.h"

extern u32 D_800A11F0_main[4]; // = { 0, 1, 2, 4 }; //sSizBytes
extern u32 D_800A1200_main[4]; // = { 0, 1, 2, 2 }; //sSizLineBytes
extern u32 D_800A1210_main[4]; // = { 2, 2, 2, 3 }; //sSizLoadBlock
extern u32 D_800A1220_main[4]; // = { 3, 1, 0, 0 }; //sSizIncr
extern u32 D_800A1230_main[4]; // = { 2, 1, 0, 0 }; //sSizShift

void func_800341D0_main(Gfx **gdl, u16 *timg, s32 fmt, s32 siz,
                        s32 width, s32 height,
                        s32 uls, s32 ult, s32 lrs, s32 lrt,
                        s32 pal, s32 cms, s32 cmt,
                        s32 masks, s32 maskt, s32 shifts, s32 shiftt) {
    Gfx *gfx = *gdl;

    gDPSetTextureImage(gfx++, fmt, siz, width, timg);
    gDPSetTile(gfx++, fmt, siz, (((lrs - uls) + 1) * D_800A1200_main[siz] + 7) >> 3, 0,
               G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts);
    gDPLoadSync(gfx++);
    gDPLoadTile(gfx++, G_TX_LOADTILE, uls << 2, ult << 2, lrs << 2, lrt << 2);
    gDPPipeSync(gfx++);
    gDPSetTile(gfx++, fmt, siz, (((lrs - uls) + 1) * D_800A1200_main[siz] + 7) >> 3, 0,
               G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, uls << 2, ult << 2, lrs << 2, lrt << 2);

    *gdl = gfx;
}

void func_800343FC_main(Gfx **gdl, void *timg, s32 fmt, s32 siz,
                        s32 width, s32 height,
                        s32 uls, s32 ult, s32 lrs, s32 lrt,
                        s32 pal, s32 cms, s32 cmt,
                        s32 masks, s32 maskt, s32 shifts, s32 shiftt, s32 tile, s32 tmem) {
    Gfx *gfx = *gdl;

    gDPSetTextureImage(gfx++, fmt, siz, width, timg);
    gDPSetTile(gfx++, fmt, siz, (((lrs - uls) + 1) * D_800A1200_main[siz] + 7) >> 3, tmem,
               G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts);
    gDPLoadSync(gfx++);
    gDPLoadTile(gfx++, G_TX_LOADTILE, uls << 2, ult << 2, lrs << 2, lrt << 2);
    gDPPipeSync(gfx++);
    gDPSetTile(gfx++, fmt, siz, (((lrs - uls) + 1) * D_800A1200_main[siz] + 7) >> 3, tmem,
               tile, pal, cmt, maskt, shiftt, cms, masks, shifts);
    gDPSetTileSize(gfx++, tile, uls << 2, ult << 2, lrs << 2, lrt << 2);

    *gdl = gfx;
}

// isn't this just gDPLoadTextureBlock?
void func_8003465C_main(Gfx **gdl, void *timg, s32 fmt, s32 siz,
                        s32 width, s32 height,
                        s32 uls, s32 ult, s32 lrs, s32 lrt,
                        s32 pal, s32 cms, s32 cmt,
                        s32 masks, s32 maskt, s32 shifts, s32 shiftt) {
    Gfx *gfx = *gdl;
    timg = (u8 *)timg + ((width * ult) << (siz - 1));

    gDPSetTextureImage(gfx++, fmt, D_800A1210_main[siz], 1,
                       timg);
    gDPSetTile(gfx++, fmt, D_800A1210_main[siz], 0, 0, G_TX_LOADTILE,
               0, cmt, maskt, shiftt, cms, masks, shifts);
    gDPLoadSync(gfx++);
    gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0,
                 (((width * height) + D_800A1220_main[siz]) >> D_800A1230_main[siz]) - 1,
                 CALC_DXT(width, D_800A11F0_main[siz]));
    gDPPipeSync(gfx++);
    gDPSetTile(gfx++, fmt, siz, ((width * D_800A1200_main[siz]) + 7) >> 3, 0,
               G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, uls << 2, ult << 2, lrs << 2, lrt << 2);

    *gdl = gfx;
}

void func_80034998_main(Gfx **gdl, void *timg, s32 fmt, u32 width, u32 height,
                        s32 uls, s32 ult, s32 lrs, s32 lrt,
                        s32 pal, s32 cms, s32 cmt,
                        s32 masks, s32 maskt, s32 shifts, s32 shiftt) {
    Gfx *gfx = *gdl;
    timg = (u8 *)timg + ((width * ult) >> 1);

    gDPSetTextureImage(gfx++, fmt, G_IM_SIZ_16b, 1, timg);
    gDPSetTile(gfx++, fmt, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts);
    gDPLoadSync(gfx++);
    gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, (((width * height) + 3) >> 2) - 1, CALC_DXT_4b(width));
    gDPPipeSync(gfx++);
    gDPSetTile(gfx++, fmt, G_IM_SIZ_4b, (((width >> 1) + 7) >> 3), 0, G_TX_RENDERTILE, pal, cmt, maskt, shiftt,
               cms, masks, shifts);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, uls << 2, ult << 2, lrs << 2, lrt << 2);

    *gdl = gfx;
}

void func_80034C08_main(Gfx **gdl, void *timg, s32 fmt, s32 siz,
                        s32 width, s32 height,
                        s32 uls, s32 ult, s32 lrs, s32 lrt,
                        s32 pal, s32 cms, s32 cmt,
                        s32 masks, s32 maskt, s32 shifts, s32 shiftt, s32 tile, s32 tmem) {
    Gfx *gfx = *gdl;
    timg = (u8 *)timg + ((width * ult) << (siz - 1));

    gDPSetTextureImage(gfx++, fmt, D_800A1210_main[siz], 1, timg);
    gDPSetTile(gfx++, fmt, D_800A1210_main[siz], 0, tmem, G_TX_LOADTILE,
               0, cmt, maskt, shiftt, cms, masks, shifts);
    gDPLoadSync(gfx++);
    gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0,
                 (((width * height) + D_800A1220_main[siz]) >> D_800A1230_main[siz]) - 1,
                 CALC_DXT(width, D_800A11F0_main[siz]));
    gDPPipeSync(gfx++);
    gDPSetTile(gfx++, fmt, siz, ((width * D_800A1200_main[siz]) + 7) >> 3, tmem,
               tile, pal, cmt, maskt, shiftt, cms, masks, shifts);
    gDPSetTileSize(gfx++, tile, uls << 2, ult << 2, lrs << 2, lrt << 2);

    *gdl = gfx;
}

void func_80034F70_main(Gfx **gdl, void *timg, s32 fmt, u32 width, u32 height,
                        s32 uls, s32 ult, s32 lrs, s32 lrt,
                        s32 pal, s32 cms, s32 cmt,
                        s32 masks, s32 maskt, s32 shifts, s32 shiftt, s32 tile, s32 tmem) {
    Gfx *gfx = *gdl;
    timg = (u8 *)timg + ((width * ult) >> 1);

    gDPSetTextureImage(gfx++, fmt, G_IM_SIZ_16b, 1, timg);
    gDPSetTile(gfx++, fmt, G_IM_SIZ_16b, 0, tmem, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts);
    gDPLoadSync(gfx++);
    gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, (((width * height) + 3) >> 2) - 1, CALC_DXT_4b(width));
    gDPPipeSync(gfx++);
    gDPSetTile(gfx++, fmt, G_IM_SIZ_4b, (((width >> 1) + 7) >> 3), tmem, tile, pal, cmt, maskt, shiftt,
               cms, masks, shifts);
    gDPSetTileSize(gfx++, tile, uls << 2, ult << 2, lrs << 2, lrt << 2);

    *gdl = gfx;
}

void func_8003521C_main(HuMtx4F mf, f64 x, f64 y, f64 angle) {
    f32 rad;

    angle -= (s32)(angle / 360.0) * 360;
    rad = angle * 3.14159 / 180.0;
    mf[0][0] = cosf(rad);
    mf[0][1] = sinf(rad);
    mf[1][0] = -sinf(rad);
    mf[1][1] = cosf(rad);
    mf[3][0] = x;
    mf[3][1] = y;
}

void func_80035300_main(f32 *pos, HuMtx4F mf, Mtx *m) {
    u16 *intPart = (u16 *)m;
    u16 *fracPart = (u16 *)m + 16;

    mf[3][0] = pos[0] * mf[0][0] + mf[3][0] + pos[1] * mf[1][0];
    mf[3][1] = pos[0] * mf[0][1] + mf[3][1] + pos[1] * mf[1][1];
    intPart[0] = (s32)(mf[0][0] * 65536.0f) >> 16;
    intPart[1] = (s32)(mf[0][1] * 65536.0f) >> 16;
    intPart[4] = (s32)(mf[1][0] * 65536.0f) >> 16;
    intPart[5] = (s32)(mf[1][1] * 65536.0f) >> 16;
    intPart[12] = (s32)(mf[3][0] * 65536.0f) >> 16;
    intPart[13] = (s32)(mf[3][1] * 65536.0f) >> 16;
    fracPart[0] = (s32)(mf[0][0] * 65536.0f);
    fracPart[1] = (s32)(mf[0][1] * 65536.0f);
    fracPart[4] = (s32)(mf[1][0] * 65536.0f);
    fracPart[5] = (s32)(mf[1][1] * 65536.0f);
    fracPart[12] = (s32)(mf[3][0] * 65536.0f);
    fracPart[13] = (s32)(mf[3][1] * 65536.0f);
}
