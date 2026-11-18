#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/printfunc.h"
#include "macros.h"

#define MAX_STRINGS 512

#define RGBA32_R(color) ((color) >> 24)
#define RGBA32_G(color) (((color) >> 16) & 0xFF)
#define RGBA32_B(color) (((color) >> 8) & 0xFF)
#define RGBA32_A(color) ((color) & 0xFF)
#define FILL_COLOR_RGBA5551(r, g, b, a) ((GPACK_RGBA5551(r, g, b, a) << 16) | GPACK_RGBA5551(r, g, b, a))

typedef struct strline_data {
    /* 0x00 */ u16 color;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 empstrline_next;
    /* 0x08 */ u8 str[64];
} strline_data;

// unreferenced: restores the render state that pfDrawFonts leaves behind
static Gfx pfInitGfx[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};
static Gfx *pfInitGfxP = pfInitGfx; // unreferenced
u16 fontcolorBak = 0xFFFF; // palette currently loaded for the font texture

static strline_data strline[MAX_STRINGS];
extern u16 strlinecnt;
extern u16 empstrline;
extern u16 printWinNum;
extern u16 saftyFrameF;         // screen border enabled
extern u8 ank8x8_4b[];        // 64x64 CI4 font texture, 8x8 glyphs starting at ' '
extern u16 ank8x8_pal[16][16]; // font palettes

void pfInit(void) {
    s32 i;

    fontcolor = FONT_COLOR_WHITE;
    empstrline = 0;

    // null every string by setting the first byte to 0
    for (i = 0; i < MAX_STRINGS; i++) {
        strline[i].str[0] = '\0';
    }

    pfClsScr();

    printWinNum = 0;
    for (i = 0; i < 4; i++) {
        printWinData[i].unk_00 = 0;
    }
    saftyFrameF = 0;
}

void pfClsScr(void) {
    s32 i;

    empstrline = 0;
    strlinecnt = 0;
    for (i = 0; i < MAX_STRINGS; i++) {
        strline[i].empstrline_next = i + 1;
        if (strline[i].str[0] != 0) {
            strline[i].str[0] = 0;
        }
    }
}

void pfClrStrLine(s16 arg0) {
    strline_data *temp_v1;

    if ((strline[arg0].str[0] != '\0') && (strlinecnt != 0)) {
        strlinecnt -= 1;
        strline[arg0].str[0] = '\0';
        strline[arg0].empstrline_next = empstrline;
        empstrline = arg0;
    }
}

// unsure if this should be char* src or u8* src
s32 print8(u16 x, u16 y, char *src) {
    u8 *dst;
    strline_data *strLine;
    s16 prevStrIndex;

    strLine = &strline[empstrline];
    if (strlinecnt < MAX_STRINGS) {
        strlinecnt += 1;
        prevStrIndex = empstrline;
        empstrline = strLine->empstrline_next;
        strLine->color = fontcolor;
        strLine->x = x;
        strLine->y = y;
        dst = strLine->str;
        while (*(u8 *)src != '\0') {
            *dst++ = *(u8 *)src++;
        }
        *dst = '\0';
        return prevStrIndex;
    } else {
        return -1;
    }
}

s16 printWin(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Unk_D_800CC440 *temp;
    s32 i;

    if (printWinNum >= 4) {
        return -1;
    }
    for (i = 0; i < 4; i++) {
        if (printWinData[i].unk_00 == 0) {
            break;
        }
    }
    temp = &printWinData[i];
    temp->unk_00 = 1;
    temp->unk_04 = arg0;
    temp->unk_08 = arg1;
    temp->unk_0C = arg2;
    temp->unk_10 = arg3;
    temp->unk_14 = arg4;
    printWinNum++;
    return i;
}

void pfWinKill(s16 arg0) {
    if (printWinNum != 0) {
        printWinData[arg0].unk_00 = 0;
        printWinNum -= 1;
    }
}

void pfWinClose(void) {
    s32 i;

    printWinNum = 0;
    for (i = 0; i < 4; i++) {
        printWinData[i].unk_00 = 0;
    }
}

void saftyFrameSet(u8 arg0, u8 arg1, u8 arg2) {
    saftyFrameData.unk_00 = arg0;
    saftyFrameData.unk_01 = arg1;
    saftyFrameData.unk_02 = arg2;
    saftyFrameData.unk_03 = saftyFrameData.unk_04 = saftyFrameData.unk_05 = 0;
    saftyFrameF = 1;
}

void saftyFrameFlashSet(s8 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8) {
    saftyFrameData.unk_03 = arg0;
    saftyFrameData.unk_04 = arg1;
    saftyFrameData.unk_05 = arg2;
    saftyFrameData.unk_06 = arg3;
    saftyFrameData.unk_07 = arg4;
    saftyFrameData.unk_08 = arg5;
    saftyFrameData.unk_09 = arg6;
    saftyFrameData.unk_0A = arg7;
    saftyFrameData.unk_0B = arg8;
}

void saftyFrameFlashReset(void) {
    saftyFrameData.unk_03 = saftyFrameData.unk_04 = saftyFrameData.unk_05 = 0;
}

void saftyFrameReset(void) {
    saftyFrameF = 0;
}

void pfStrLineSet(s16 arg0, u8 *src) {
    u8 *dst;

    if ((u32)strline[arg0].str != 0) {
        dst = strline[arg0].str;
        while (*src != '\0') {
            *dst++ = *src++;
        }
        *dst = '\0';
    }
}

Gfx *pfDrawFonts(Gfx *gfx) {
    u16 count;
    s32 i;
    u16 pal;
    u16 color;
    u16 x;
    u16 y;
    u8 *str;
    u8 c;
    s8 speed;

    count = strlinecnt;

    if (printWinNum != 0) {
        gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, 319, 339);
        gDPPipeSync(gfx++);
        gDPSetTextureLOD(gfx++, G_TL_LOD);
        gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
        gDPSetTexturePersp(gfx++, G_TP_NONE);
        gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
        for (i = 0; i < 4; i++) {
            if (printWinData[i].unk_00 != 0) {
                if (RGBA32_A(printWinData[i].unk_14) == 0xFF) {
                    gDPPipeSync(gfx++);
                    gDPSetCycleType(gfx++, G_CYC_FILL);
                    gDPSetRenderMode(gfx++, G_RM_NOOP, G_RM_NOOP2);
                    gDPSetFillColor(gfx++, FILL_COLOR_RGBA5551(RGBA32_R(printWinData[i].unk_14),
                                                               RGBA32_G(printWinData[i].unk_14),
                                                               RGBA32_B(printWinData[i].unk_14),
                                                               RGBA32_A(printWinData[i].unk_14)));
                } else {
                    gDPPipeSync(gfx++);
                    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
                    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
                    gDPSetRenderMode(gfx++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
                    gDPSetPrimColor(gfx++, 0, 0, RGBA32_R(printWinData[i].unk_14),
                                    RGBA32_G(printWinData[i].unk_14), RGBA32_B(printWinData[i].unk_14),
                                    RGBA32_A(printWinData[i].unk_14));
                }
                gDPFillRectangle(gfx++, printWinData[i].unk_04, printWinData[i].unk_08,
                                 printWinData[i].unk_0C, printWinData[i].unk_10);
            }
        }
    }

    if (saftyFrameF != 0) {
        if (saftyFrameData.unk_03 != 0) {
            speed = saftyFrameData.unk_03;
            if (speed < 0) {
                if (saftyFrameData.unk_00 + speed >= saftyFrameData.unk_09) {
                    saftyFrameData.unk_00 += speed;
                } else {
                    saftyFrameData.unk_00 = saftyFrameData.unk_09;
                    saftyFrameData.unk_03 = -saftyFrameData.unk_03;
                }
            } else {
                if (saftyFrameData.unk_00 + speed <= saftyFrameData.unk_06) {
                    saftyFrameData.unk_00 += speed;
                } else {
                    saftyFrameData.unk_00 = saftyFrameData.unk_06;
                    saftyFrameData.unk_03 = -saftyFrameData.unk_03;
                }
            }
        }
        if (saftyFrameData.unk_04 != 0) {
            speed = saftyFrameData.unk_04;
            if (speed < 0) {
                if (saftyFrameData.unk_01 + speed >= saftyFrameData.unk_0A) {
                    saftyFrameData.unk_01 += speed;
                } else {
                    saftyFrameData.unk_01 = saftyFrameData.unk_0A;
                    saftyFrameData.unk_04 = -saftyFrameData.unk_04;
                }
            } else {
                if (saftyFrameData.unk_01 + speed <= saftyFrameData.unk_07) {
                    saftyFrameData.unk_01 += speed;
                } else {
                    saftyFrameData.unk_01 = saftyFrameData.unk_07;
                    saftyFrameData.unk_04 = -saftyFrameData.unk_04;
                }
            }
        }
        if (saftyFrameData.unk_05 != 0) {
            speed = saftyFrameData.unk_05;
            if (speed < 0) {
                if (saftyFrameData.unk_02 + speed >= saftyFrameData.unk_0B) {
                    saftyFrameData.unk_02 += speed;
                } else {
                    saftyFrameData.unk_02 = saftyFrameData.unk_0B;
                    saftyFrameData.unk_05 = -saftyFrameData.unk_05;
                }
            } else {
                if (saftyFrameData.unk_02 + speed <= saftyFrameData.unk_08) {
                    saftyFrameData.unk_02 += speed;
                } else {
                    saftyFrameData.unk_02 = saftyFrameData.unk_08;
                    saftyFrameData.unk_05 = -saftyFrameData.unk_05;
                }
            }
        }
        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_FILL);
        gDPSetRenderMode(gfx++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetFillColor(gfx++, FILL_COLOR_RGBA5551(saftyFrameData.unk_00, saftyFrameData.unk_01,
                                                   saftyFrameData.unk_02, 1));
        gDPFillRectangle(gfx++, 24, 16, 296, 16);
        gDPFillRectangle(gfx++, 24, 224, 296, 224);
        gDPFillRectangle(gfx++, 24, 16, 24, 224);
        gDPFillRectangle(gfx++, 296, 16, 296, 224);
    }

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, 319, 339);
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_COPY);
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
    gDPSetTextureLOD(gfx++, G_TL_LOD);
    gDPSetRenderMode(gfx++, G_RM_NOOP, G_RM_NOOP2);
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPSetBlendColor(gfx++, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPLoadTextureBlock_4b(gfx++, ank8x8_4b, G_IM_FMT_CI, 64, 64, fontcolorBak,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                           G_TX_NOLOD, G_TX_NOLOD);
    gDPSetBlendColor(gfx++, 0, 0, 0, 1);
    for (pal = 0; pal < 16; pal++) {
        gDPLoadTLUT_pal16(gfx++, pal, ank8x8_pal[pal]);
    }

    for (i = 0; i < MAX_STRINGS; i++) {
        if (strline[i].str[0] != '\0') {
            str = strline[i].str;
            color = strline[i].color;
            x = strline[i].x;
            y = strline[i].y;
            if (color != fontcolorBak) {
                fontcolorBak = color;
                gDPTileSync(gfx++);
                gDPSetTile(gfx++, G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, color, 0, 0, 0, 0, 0, 0);
            }
            for (; *str != '\0'; str++) {
                if (*str >= ' ') {
                    c = *str - ' ';
                    gSPTextureRectangle(gfx++, x << 2, y << 2, (x + 7) << 2, (y + 7) << 2, G_TX_RENDERTILE,
                                        ((c % 8) * 8) << 5, ((c / 8) * 8) << 5, 4 << 10, 1 << 10);
                    x += 8;
                    if (x >= SCREEN_WIDTHI) {
                        x = 0;
                        y += 8;
                    }
                }
            }
            if (--count == 0) {
                break;
            }
        }
    }

    gDPPipeSync(gfx++);
    gSPTexture(gfx++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCombineMode(gfx++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(gfx++, G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    return gfx;
}
