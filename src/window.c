#include "game/window.h"
#include "game/sprite.h"
#include "common.h"
#include "malloc.h"
#include "mallocblock.h"
#include "input.h"
#include "stdarg.h"

typedef struct WindowIconDefinition {
    u32 highlightedFile;
    u32 file;
    u8 bank;
    u8 width;
    u8 padA[2];
} WindowIconDefinition;

extern WindowIconDefinition D_800A2294_main[];
extern TextWindow *D_800CC69C_main;
extern s32 D_800D209C_main;
extern u8 D_800A2194_main[];
extern u8 D_800A2150_main;
extern u8 gLanguageIndex;
extern u8 D_800A2324_main[];
extern u8 D_800A2325_main[];
extern u8 D_800A232C_main[];
extern u8 *D_800A2344_main[];
extern s16 D_800BDA50_main[12];
extern s8 D_800BDA6D_main;
extern s16 D_800BDA68_main;
extern s8 D_800CD2A4_main;
extern void *D_800CE2C4_main;
extern Process *D_800D040C_main;
extern u8 D_800D1F34_main;
extern void *D_800D1FE4_main;
extern void *D_800D4084_main;
extern u8 D_800D5206_main[5];
extern s8 D_800D5540_main;
extern s8 D_800D6A26_main;
extern s16 D_800D6B62_main;
extern s32 D_800A25D0_main[];
extern s8 D_800BDA6A_main;
extern u16 D_800BDA6C_main;
extern u16 D_800BDA6E_main;
extern u8 D_800D5206_main[5];
extern s8 D_800D5540_main;

s16 func_8005BA54_main(s16, s16);
void func_8005BB18_main(s16, f32, f32);
void func_800615B8_main(s16, s32);
s32 func_8005CC3C_main(TextWindow *, s16);
void func_8005CD84_main(TextWindow *);
void func_8005CE10_main(TextWindow *);
void *func_8005DAA4_main(s16);
void func_8005F7F4_main(s16 *);
s16 func_8005B614_main(s32);
void func_8005CF94_main(s16);
void func_80060848_main(void);
void func_8005DD14_main(s16);

void func_8005A6B0_main(void) {
    Process *temp_v0_4;
    void *temp_v0_6;
    s16 i;

    if (D_800A2150_main == 0) {
        D_800CC69C_main = HuMemMemoryAllocTemp(sizeof(TextWindow) * WINDOWS_MAX);

        for (i = 0; i < WINDOWS_MAX; i++) {
            D_800CC69C_main[i].unk5E = -1;
        }

        D_800CC69C_main[0].unk62 = -1;
        D_800CC69C_main[0].unk64 = 1;
        D_800CC69C_main[0].unk5E = 0;
        D_800CC69C_main[1].unk62 = 0;
        D_800CC69C_main[1].unk64 = -1;
        D_800CC69C_main[1].unk5E = -0x218;
        D_800D6A26_main = 0;
        D_800D1F34_main = 0;
        D_800D6B62_main = 0x2710;
        gLanguageIndex = GwCommon.languageIndex;

        if (gLanguageIndex >= LANGUAGE_MAX || gLanguageIndex == LANGUAGE_NONE) {
            gLanguageIndex = LANGUAGE_ENGLISH;
        }
        if (gLanguageIndex == LANGUAGE_JAPANESE) {
            D_800D1FE4_main = DataReadTemp(0x0000002B);
            func_80036414_main((u32)strings_japanese_ROM_START);
        } else {
            D_800D1FE4_main = DataReadTemp(0x0000002C);
            switch (gLanguageIndex) {
                case LANGUAGE_ENGLISH:
                    func_80036414_main((u32)strings_english_ROM_START);
                    break;
                case LANGUAGE_FRENCH:
                    func_80036414_main((u32)strings_french_ROM_START);
                    break;
                case LANGUAGE_GERMAN:
                    func_80036414_main((u32)strings_german_ROM_START);
                    break;
                case LANGUAGE_SPANISH:
                    func_80036414_main((u32)strings_spanish_ROM_START);
                    break;
                case LANGUAGE_ITALIAN:
                    func_80036414_main((u32)strings_italian_ROM_START);
                    break;
            }
        }

        temp_v0_4 = omAddPrcObj(func_8005DDDC_main, 0x1001, 0x800, 0);
        D_800D040C_main = temp_v0_4;
        omPrcSetStatBit(temp_v0_4, 0xA0);

        D_800A2150_main = 1;
        D_800CB99C_main = 0;
        D_800D4084_main = DataReadTemp(0x00000029);
        D_800CE2C4_main = DataReadTemp(0x0000002A);

        for (i = 0; i < ARRAY_COUNT(D_800BDA50_main); i++) {
            D_800BDA50_main[i] = -1;
        }

        temp_v0_6 = DataRead(0x00000033);
        D_800BDA68_main = func_80055810_main(temp_v0_6);
        DataClose(temp_v0_6);

        for (i = 0; i < ARRAY_COUNT(D_800D5206_main); i++) {
            D_800D5206_main[i] = 0;
        }

        D_800D5540_main = 0xC;
        D_800CD2A4_main = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/window", func_8005A968_main);

void func_8005B040_main(u8 *pixels, s16 width, s16 height) {
    s16 stride = width / 2;
    s16 x;
    s16 y;
    u8 left;
    u8 right;
    u8 *row;

    for (x = 0; x < stride; x++) {
        pixels[x] = 0x44;
        (pixels + stride)[x] = 0x77;
        (pixels + (height - 2) * stride)[x] = 0x77;
        (pixels + (height - 1) * stride)[x] = 0x44;
    }
    for (y = 0; y < height; y++) {
        row = pixels + stride * y;
        row[0] = 0x47;
        row += stride;
        row[-1] = 0x74;
    }
    for (y = 0; y < 4; y++) {
        pixels[y * stride] = D_800A2324_main[(s16)(y * 2)];
        pixels[y * stride + 1] = D_800A2325_main[(s16)(y * 2)];
        pixels[(height - y - 1) * stride] = D_800A2324_main[(s16)(y * 2)];
        pixels[(height - y - 1) * stride + 1] = D_800A2325_main[(s16)(y * 2)];
        left = (D_800A2324_main[(s16)(y * 2)] >> 4) | (D_800A2324_main[(s16)(y * 2)] << 4);
        right = (D_800A2325_main[(s16)(y * 2)] >> 4) | (D_800A2325_main[(s16)(y * 2)] << 4);
        pixels[y * stride + stride - 2] = right;
        pixels[y * stride + stride - 1] = left;
        pixels[(height - y - 1) * stride + stride - 2] = right;
        pixels[(height - y - 1) * stride + stride - 1] = left;
    }
}

void func_8005B238_main(u8 *pixels, s16 width, s16 height) {
    s16 radius;
    s16 x;
    s16 y;
    s16 right;

    if (width > height) {
        radius = height / 2;
    } else {
        radius = width / 2;
    }
    width /= 2;
    for (y = 0; y < radius; y++) {
        for (x = 0; x < radius - y; x++) {
            (pixels + y * width)[x / 2] &= (x & 1) ? 0xF0 : 0x0F;
            (pixels + (height - y - 1) * width)[x / 2] &= (x & 1) ? 0xF0 : 0x0F;
            right = width * 2 - x - 1;
            (pixels + y * width)[right / 2] &= (right & 1) ? 0xF0 : 0x0F;
            (pixels + (height - y - 1) * width)[right / 2] &= (right & 1) ? 0xF0 : 0x0F;
        }
    }
}

void func_8005B43C_main(s16 winId, u32 message, s16 x, s16 y) {
    TextWindow *window = &D_800CC69C_main[winId];
    s16 width;

    if (window->unk_D0 != NULL && window->unk_D4 != 0) {
        func_800365E8_main(window->unk_D0);
    }
    if ((u8)window->unk20 == 2) {
        func_8005CF94_main(winId);
    }
    window->unk5C = 1;
    if (0x80000000 < message) {
        window->unk_D4 = 0;
        window->unk_CC = (u8 *)message;
    } else {
        window->unk_D4 = 1;
        window->unk_D0 = func_800364DC_main((void *)message);
        window->unk_CC = window->unk_D0;
    }
    if (x >= 0) {
        window->unk54 = x;
    } else if (x == -2) {
        if (window->unk_38 & 0x40000) {
            func_80060848_main();
        }
        width = func_8005B614_main((s32)window->unk_CC);
        D_800CD2A4_main = 0;
        window->unk54 = (window->unk40 - width) / 2;
        window->unk_38 |= 0x800;
    }
    if (y >= 0) {
        window->unk56 = y;
    } else if (y == -2) {
        window->unk56 = (window->unk42 - 12) / 2;
        window->unk_38 |= 0x1000;
    }
    window->unk20 = 1;
    window->unk_30 = 0;
}

s16 func_8005B5EC_main(u8 *str) {
    s16 len = 0;

    while (*str != 0) {
        str++;
        len++;
    }
    return len;
}

s16 func_8005B614_main(s32 arg0) {
    s16 size[2];

    func_80060394_main(1, size, arg0);
    return size[0];
}

void func_8005B63C_main(s16 winId, s32 arg1, s32 arg2) {
    TextWindow *window = &D_800CC69C_main[winId];

    window->unk_38 = arg2 | (window->unk_38 & ~arg1);
    if (arg2 & 0x20) {
        window->unk_AA = 0;
    }
}

s32 func_8005B68C_main(s16 win_id) {
    return D_800CC69C_main[win_id].unk_38;
}

void func_8005B6BC_main(s16 win_id, u32 arg1, s8 arg2) {
    TextWindow *textWindow = &D_800CC69C_main[win_id];

    if (textWindow->unk_B8[arg2] != 0) {
        if (textWindow->usingStringIDBool[arg2] != 0) {
            func_800365E8_main(textWindow->unk_B8[arg2]);
        }
    }
    // pointer check
    if (0x80000000 < arg1) {
        textWindow->usingStringIDBool[arg2] = 0;
        textWindow->unk_B8[arg2] = (char *)arg1;
    } else {
        textWindow->usingStringIDBool[arg2] = 1;
        textWindow->unk_B8[arg2] = func_800364DC_main((void *)arg1);
    }
    textWindow->unk_B2[arg2] = -1;
}

s16 func_8005B7B8_main(s16 win_id, u32 spriteMainFsPair, s16 arg2, s16 arg3, s16 arg4) {
    TextWindow *window = &D_800CC69C_main[win_id];
    s16 spriteId;
    void *spriteBytes;
    s16 i;

    for (i = 4; i < 12; i++) {
        if (window->unk_6E[i] != -1) {
            continue;
        }
        break;
    }
    if (i >= 12) {
        return -1;
    }

    spriteBytes = DataRead(spriteMainFsPair);
    spriteId = func_80055810_main(spriteBytes);
    window->unk_6E[i] = spriteId;
    HuMemMemoryFreePerm(spriteBytes);
    func_80055024_main(window->unk_6C, i, spriteId, arg4);
    func_80054904_main(window->unk_6C, i, arg2, arg3);
    func_800554C4_main(window->unk_6C, i, 0);
    return i;
}

void func_8005B8F8_main(s16 arg0, s16 arg1) {
    HuSprKill(func_8005BA54_main(arg0, arg1));
    D_800CC69C_main[arg0].unk_6E[arg1] = -1;
}

s16 func_8005B974_main(s16 winId, u32 spriteMainFsPair, s16 x, s16 y, s16 arg4) {
    TextWindow *window = &D_800CC69C_main[winId];
    TextWindowSprite *sprite;
    s16 spriteId;

    spriteId = func_8005B7B8_main(winId, spriteMainFsPair, x, y, arg4);
    sprite = &window->unk_F4[window->unk_30];
    sprite->unk_02 = x;
    sprite->unk_04 = y;
    sprite->unk_06 = 0;
    sprite->unk_08 = 0;
    sprite->unk_00 = 1;
    window->unk_30++;
    return spriteId;
}

TextWindow *func_8005BA28_main(s16 win_id) {
    return &D_800CC69C_main[win_id];
}

s16 func_8005BA54_main(s16 arg0, s16 arg1) {
    TextWindow *window = &D_800CC69C_main[arg0];
    return window->unk_6E[arg1];
}

void func_8005BA90_main(s16 winId, s16 arg1, s16 arg2) {
    TextWindow *window;

    window = &D_800CC69C_main[winId];

    func_80054904_main(window->unk_6C, 0, arg1, arg2);
    window->unk3C = arg1;
    window->unk3E = arg2;
}

void func_8005BB18_main(s16 winId, f32 scaleX, f32 scaleY) {
    TextWindow *window = &D_800CC69C_main[winId];
    s16 i;

    window->scaleX = scaleX;
    window->scaleY = scaleY;
    for (i = 0; i < 22; i++) {
        HuSprScaleSet(window->unk_6C, i, scaleX, scaleY);
    }
}

void func_8005BBC0_main(s16 winId, f32 scaleX, f32 scaleY) {
    TextWindow *window = &D_800CC69C_main[winId];
    s16 i;

    window->scaleX = scaleX;
    window->scaleY = scaleY;
    for (i = 0; i < 4; i++) {
        HuSprScaleSet(window->unk_6C, i, scaleX, scaleY);
    }
    for (i = 12; i < 22; i++) {
        HuSprScaleSet(window->unk_6C, i, scaleX, scaleY);
    }
}

void func_8005BCA4_main(s16 arg0, s16 arg1, s16 arg2) {
    TextWindow *window = &D_800CC69C_main[arg0];
    HuSprite *spr;
    s16 i;

    window->unk48 = arg1;
    window->unk4A = arg2;
    spr = HuSprGet(window->unk_6C, 0);
    spr->unk_84->unk00->unk08 = arg1;
    spr->unk_84->unk00->unk0A = arg2;
    spr = HuSprGet(window->unk_6C, 1);
    for (i = 0; i < spr->unk_84->unk12; i++) {
        spr->unk_84->unk00[i].unk08 = arg1;
        spr->unk_84->unk00[i].unk0A = arg2;
    }
}

void func_8005BDA8_main(s16 winId, f32 arg1) {
    TextWindow *window;

    window = &D_800CC69C_main[winId];
    func_800552DC_main(window->unk_6C, 0, arg1);
}

void func_8005BDFC_main(s16 winId, s32 arg1) {
    TextWindow *window;

    window = &D_800CC69C_main[winId];
    window->unk_25 = arg1;
    window->unk_26 = arg1;
}

void func_8005BE30_main(s16 winId, s32 priority) {
    TextWindow *window = &D_800CC69C_main[winId];
    s16 i;

    window->unk60 = priority;
    for (i = 0; i < 22; i++) {
        HuSprPriSet(window->unk_6C, i, priority);
    }
    if (window->unk6A != -1) {
        HuSprPriSet(window->unk_6C, 2, priority - 1);
    }
}

void func_8005BEE0_main(s16 winId, s16 arg1) {
    TextWindow *window;

    window = &D_800CC69C_main[winId];

    if (arg1 == 0) {
        HuSprAttrSet(window->unk_6C, 0, 0x8000);
    } else {
        HuSprAttrReset(window->unk_6C, 0, 0x8000);
    }
    func_80055458_main(window->unk_6C, 0, arg1 & 0xFFFF);
}

void func_8005BF70_main(s16 winId, s32 arg1) {
    TextWindow *window = &D_800CC69C_main[winId];
    s16 i;

    func_80055458_main(window->unk_6C, 1, arg1 & 0xFFFF);
    for (i = 12; i < 22; i++) {
        if (window->unk_6E[i] != -1) {
            func_80055458_main(window->unk_6C, i, arg1 & 0xFFFF);
        }
    }
}

void func_8005C02C_main(s16 winId, s32 arg1) {
    TextWindow *window;

    window = &D_800CC69C_main[winId];
    window->unk_22 = arg1;
    window->unk_23 = arg1;
}

void func_8005C060_main(s16 winId, u8 index, u8 red, u8 green, u8 blue) {
    TextWindow *window = &D_800CC69C_main[winId];
    HuSprite *sprite;
    u16 *palette;

    sprite = HuSprGet(window->unk_6C, 1);
    window->palette[index + 1] = ((red << 8) & 0xF800) | ((green << 3) & 0x7C0) | (u8)((blue >> 2) & 0x3E) | 1;
    palette = HuMemAlloc(sizeof(window->palette));
    bcopy(window, palette, sizeof(window->palette));
    func_80019C00_main(sprite->unk_84->unk0C);
    sprite->unk_84->unk0C = palette;
}

void func_8005C154_main(s16 winId, s32 red, s32 green, s32 blue) {
    func_8005C060_main(winId, 0, red & 0xFF, green & 0xFF, blue & 0xFF);
}

INCLUDE_ASM("asm/nonmatchings/window", func_8005C190_main);

s32 func_8005CC18_main(TextWindow *window) {
    return func_8005CC3C_main(window, window->unk_34 + (u8)window->unk_29);
}

s32 func_8005CC3C_main(TextWindow *window, s16 advance) {
    s32 width;

    D_800D209C_main = advance;
    window->unk54 += advance;
    if (gLanguageIndex == LANGUAGE_JAPANESE) {
        width = window->unk_27;
    } else if (window->unk_38 & 0x80000) {
        width = 10;
    } else {
        width = D_800A2194_main[*window->unk_CC];
    }
    if (width + (s16)window->unk54 > (s16)window->unk4C + window->unk50 && *window->unk_CC >= 0x20) {
        return func_8005CCF0_main(window);
    }
    return 1;
}

s32 func_8005CCF0_main(TextWindow *window) {
    window->unk54 = window->unk4C;
    window->unk56 = window->unk56 + (window->unk_28 + window->unk_2A);
    return ((s16)window->unk56 + window->unk_28) <= (window->unk4E + window->unk52);
}

s32 func_8005CD38_main(TextWindow *window) {
    window->unk54 = window->unk4C;
    window->unk56 = window->unk56 + ((window->unk_28 >> 2) + window->unk_2A);
    return ((s16)window->unk56 + window->unk_28) <= (window->unk4E + window->unk52);
}

void func_8005CD84_main(TextWindow *window) {
    void *pixels;

    func_8005DD54_main(window);
    pixels = func_8005DAA4_main(((u32)window - (u32)D_800CC69C_main) / sizeof(TextWindow));
    if (window->unk_E0[0] != NULL) {
        memset(pixels, 0, (window->unk44 * window->unk46) / 2);
    }
    func_8005CE10_main(window);
}

void func_8005CE10_main(TextWindow *window) {
    s16 i;

    window->unk54 = window->unk4C;
    window->unk56 = window->unk4E;
    window->unk_30 = 0;
    window->unk_9A = 0;
    for (i = 12; i < 22; i++) {
        if (window->unk_6E[i] != -1) {
            HuSprAttrSet(window->unk_6C, i, 0x8000);
            window->unk_6E[i] = -1;
        }
    }
}

void func_8005CEB0_main(s16 winId) {
    TextWindow *window = &D_800CC69C_main[winId];

    func_80055024_main(window->unk_6C, 3, D_800BDA68_main, 0);
    HuSprAttrReset(window->unk_6C, 3, 0xFFFF);
    HuSprAttrSet(window->unk_6C, 3, 0x1000000);
    HuSprPriSet(window->unk_6C, 3, window->unk60 - 1);
    func_80054904_main(window->unk_6C, 3, window->unk58 - window->unk48, window->unk5A - window->unk4A);
    if (window->unk_38 & 8) {
        HuSprAttrSet(window->unk_6C, 3, 0x8000);
    }
}

void func_8005CF94_main(s16 winId) {
    TextWindow *window = &D_800CC69C_main[winId];

    HuSprAttrSet(window->unk_6C, 3, 0x8000);
}

s32 func_8005CFE0_main(s16 winId, s16 icon) {
    TextWindow *window = &D_800CC69C_main[winId];
    s16 sprite;
    s16 graphic;
    void *data;

    graphic = D_800BDA50_main[icon];
    if (graphic == -1) {
        if (window->unk_38 & 0x2000) {
            data = DataRead(D_800A2294_main[icon].highlightedFile);
        } else {
            data = DataRead(D_800A2294_main[icon].file);
        }
        D_800BDA50_main[icon] = graphic = func_80055810_main(data);
        HuMemMemoryFreePerm(data);
    }
    for (sprite = 12; sprite < 22; sprite++) {
        if (window->unk_6E[sprite] == -1) {
            break;
        }
    }
    if (sprite >= 22) {
        return 0;
    }
    window->unk_6E[sprite] = graphic;
    HuSprAttrSet(window->unk_6C, sprite, 0x1000);
    func_80055024_main(window->unk_6C, sprite, graphic, D_800A2294_main[icon].bank);
    func_80054904_main(window->unk_6C, sprite, window->unk54 - window->unk48, window->unk56 - window->unk4A);
    func_800554C4_main(window->unk_6C, sprite, 0);
    if ((u8)window->unk_22 == 0) {
        func_80055420_main(window->unk_6C, sprite, 0, 0, 0);
    } else if (window->unk_38 & 0x2000) {
        func_80055420_main(window->unk_6C, sprite, 0x61, 0x61, 0xF8);
    } else {
        func_80055420_main(window->unk_6C, sprite, 0x38, 0xF8, 0x25);
    }
    if (window->unk_38 & 8) {
        HuSprAttrSet(window->unk_6C, sprite, 0x8000);
    } else {
        HuSprAttrReset(window->unk_6C, sprite, 0x8000);
    }
    return D_800A2294_main[icon].width;
}

void func_8005D294_main(s16 winId) {
    func_8005CD84_main(&D_800CC69C_main[winId]);
}

void func_8005D2D4_main(s16 win_id) {
    func_8005B63C_main(win_id, 0x40000, 0x40000);
}

void func_8005D2FC_main(void) {
    D_800CD2A4_main = 1;
}

INCLUDE_ASM("asm/nonmatchings/window", func_8005D30C_main);

void func_8005D83C_main(s16 winId, s16 x, s16 y, s16 width, s16 height) {
    TextWindow *window = &D_800CC69C_main[winId];
    u8 *pixels;
    s16 i;
    s16 j;

    func_8005DD14_main(winId);
    if (y < 0) {
        y = 0;
    }
    if (x < 0) {
        x = 0;
    }
    if (window->unk_E0[0] != NULL) {
        pixels = func_8005DAA4_main(winId);
        pixels += (x + y * window->unk44) / 2;
        if (x & 1) {
            for (i = 0; i < height; i++) {
                for (j = 0; j < width / 2; j++) {
                    pixels[j] &= 0xF0;
                    pixels[j + 1] &= 0x0F;
                }
                pixels += window->unk44 / 2;
            }
        } else {
            for (i = 0; i < height; i++) {
                for (j = 0; j < width / 2; j++) {
                    pixels[j] = 0;
                }
                pixels += window->unk44 / 2;
            }
        }
    }
}

void *func_8005DAA4_main(s16 winId) {
    TextWindow *window = &D_800CC69C_main[winId];
    s16 group = window->unk_6C;
    s16 width;
    s16 height;
    s16 i;
    HuSprite *sprite;

    if (window->unk_E0[0] != NULL) {
        return HuSprGet(group, 1)->unk_84->unk00[window->unk_24].unk00;
    } else {
        width = window->unk44;
        height = window->unk46;
        sprite = HuSprGet(group, 1);
        for (i = 0; i < 3; i++) {
            HuMemFree(sprite->unk_84->unk00[i].unk00);
            sprite->unk_84->unk00[i].unk04 = width;
            sprite->unk_84->unk00[i].unk06 = window->unk42;
            sprite->unk_84->unk00[i].unk00 = window->unk_E0[i] = HuMemAlloc(width * height / 2);
            memset(window->unk_E0[i], 0, width * height / 2);
        }
        HuMemFree(sprite->unk_84->unk0C);
        sprite->unk_84->unk0C = HuMemAlloc(0x20);
        bcopy(window, sprite->unk_84->unk0C, 0x20);
        if (!(window->unk_38 & 8)) {
            HuSprAttrReset(group, 1, 0x8000);
        }
    }
    return sprite->unk_84->unk00[window->unk_24].unk00;
}

void func_8005DC94_main(s16 winId) {
    TextWindow *window = &D_800CC69C_main[winId];

    func_80054FF8_main(window->unk_6C, 1, window->unk_24);
    window->unk_24++;
    if (window->unk_24 >= 3) {
        window->unk_24 = 0;
    }
    window->unk_38 &= ~0x100;
}

void func_8005DD14_main(s16 winId) {
    func_8005DD54_main(&D_800CC69C_main[winId]);
}

void func_8005DD54_main(TextWindow *window) {
    u8 prevBuf;

    if (window->unk_24 == 0) {
        prevBuf = 2;
    } else {
        prevBuf = window->unk_24 - 1;
    }

    if (window->unk_38 & 0x100) {
        return;
    }
    window->unk_38 |= 0x100;

    if (window->unk_E0[0] != NULL) {
        bcopy(window->unk_E0[prevBuf], window->unk_E0[window->unk_24], (window->unk44 * window->unk46) / 2);
    }
}

INCLUDE_ASM("asm/nonmatchings/window", func_8005DDDC_main);

s16 func_8005E0C0_main(s16 winId) {
    s16 status = 0;
    s16 i;

    if (winId != -1) {
        return (u8)D_800CC69C_main[winId].unk20;
    }
    for (i = D_800CC69C_main[0].unk64; D_800CC69C_main[i].unk64 != -1; i = D_800CC69C_main[i].unk64) {
        status |= (u8)D_800CC69C_main[i].unk20;
    }
    return status;
}

void func_8005E1A8_main(s16 winId, s16 arg1) {
    D_800CC69C_main[winId].unk_35 = arg1;
}

s32 func_8005E1D8_main(s16 winId, s16 arg1, s32 arg2) {
    TextWindow *window = &D_800CC69C_main[winId];
    void *data;

    if (window->unk_30 == 0) {
        return -1;
    }
    if (window->unk6A == -1) {
        data = DataRead(0x00000030);
        window->unk6A = func_80055810_main(data);
        HuMemMemoryFreePerm(data);
        func_80055024_main(window->unk_6C, 2, window->unk6A, 0);
        func_80055458_main(window->unk_6C, 2, 0x100);
        HuSprAttrReset(window->unk_6C, 2, 0xFFFF);
        HuSprAttrSet(window->unk_6C, 2, 0x1009000);
        HuSprPriSet(window->unk_6C, 2, window->unk60 - 1);
    }
    if (arg2 != 0) {
        window->unk_38 |= 1;
    }
    window->unk_31 = arg1;
    window->unk20 = 5;
    window->unk_9A = 1;
    window->unk_A4 = 0;
    while (func_8005E0C0_main(winId) == 5) {
        HuPrcVSleep();
    }
    return window->unk_31;
}

INCLUDE_ASM("asm/nonmatchings/window", func_8005E348_main);

INCLUDE_ASM("asm/nonmatchings/window", func_8005EEE4_main);

void func_8005F364_main(s16 winId) {
    TextWindow *window = &D_800CC69C_main[winId];
    s16 i;

    if (window->unk_D0 != NULL && window->unk_D4 != 0) {
        func_800365E8_main(window->unk_D0);
    }
    for (i = 0; i < 5; i++) {
        if (window->unk_B8[i] != NULL && window->usingStringIDBool[i] != 0) {
            func_800365E8_main(window->unk_B8[i]);
        }
    }
    HuSprGrpKill(window->unk_6C);
    HuSprKill(window->unk66);
    HuSprKill(window->unk68);
    for (i = 4; i < 12; i++) {
        if (window->unk_6E[i] != -1) {
            HuSprKill(func_8005BA54_main(winId, i));
        }
    }
    if (window->unk6A != -1) {
        HuSprKill(window->unk6A);
    }
    window->unk5E = -1;
    D_800CC69C_main[window->unk64].unk62 = window->unk62;
    D_800CC69C_main[window->unk62].unk64 = window->unk64;
    D_800D6B62_main += 0x20;
}

void func_8005F524_main(void) {
    s16 i;

    if (D_800A2150_main != 0) {
        for (i = D_800CC69C_main[0].unk64; D_800CC69C_main[i].unk64 != -1; i = D_800CC69C_main[i].unk64) {
            func_8005F364_main(i);
        }
        DataCloseTemp(D_800D1FE4_main);
        DataCloseTemp(D_800D4084_main);
        DataCloseTemp(D_800CE2C4_main);
        HuMemMemoryFreeTemp(D_800CC69C_main);
        omDelPrcObj(D_800D040C_main);
        D_800A2150_main = 0;
        for (i = 0; i < ARRAY_COUNT(D_800BDA50_main); i++) {
            if (D_800BDA50_main[i] != -1) {
                HuSprKill(D_800BDA50_main[i]);
            }
        }
        HuSprKill(D_800BDA68_main);
    }
}

void func_8005F698_main(s16 up, s16 down, s16 left, s16 right, u8 frames) {
    func_8005F784_main(-(up == -1), -(down == -1), -(left == -1), -(right == -1), frames);
    func_8005F784_main(up, down, left, right, 1);
}

void func_8005F744_main(s16 up, s16 down, s16 left, s16 right) {
    func_8005F784_main(up, down, left, right, 1);
}

void func_8005F784_main(s16 up, s16 down, s16 left, s16 right, s16 frames) {
    D_800CDA88_main[D_800D1F34_main].up = up;
    D_800CDA88_main[D_800D1F34_main].down = down;
    D_800CDA88_main[D_800D1F34_main].left = left;
    D_800CDA88_main[D_800D1F34_main].right = right;
    D_800CDA88_main[D_800D1F34_main].frames = frames;
    D_800D1F34_main = (D_800D1F34_main + 1) & 0x1F;
}

INCLUDE_ASM("asm/nonmatchings/window", func_8005F7F4_main);

void func_8005F904_main(void) {
    D_800D1F34_main = 0;
    D_800D6A26_main = 0;
}

s16 func_8005F918_main(TextWindow *window) {
    s16 queuedInputs[4];
    s16 input = 0;

    if (window->unk_38 & 2) {
        func_8005F7F4_main(queuedInputs);
    }
    if (window->unk21 & 1) {
        if (window->unk_38 & 2) {
            input = queuedInputs[0] | input;
        } else {
            input |= (D_800D0590_main[0] & 0x3FFF) | (D_800C9520_main[0] & 0xC000);
        }
    }
    if (window->unk21 & 2) {
        if (window->unk_38 & 2) {
            input = queuedInputs[1] | input;
        } else {
            input |= (D_800D0590_main[1] & 0x3FFF) | (D_800C9520_main[1] & 0xC000);
        }
    }
    if (window->unk21 & 4) {
        if (window->unk_38 & 2) {
            input = queuedInputs[2] | input;
        } else {
            input |= (D_800D0590_main[2] & 0x3FFF) | (D_800C9520_main[2] & 0xC000);
        }
    }
    if (window->unk21 & 8) {
        if (window->unk_38 & 2) {
            input = queuedInputs[3] | input;
        } else {
            input |= (D_800D0590_main[3] & 0x3FFF) | (D_800C9520_main[3] & 0xC000);
        }
    }
    return input;
}

u8 func_8005FA90_main(u8 *arg0) {
    s16 i, j;

    for (i = 0; i < 10; i += 2) {
        if (D_800A232C_main[i] == arg0[0] && D_800A232C_main[i + 1] == arg0[1]) {
            return i / 2;
        }
    }
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 32; j += 2) {
            if (D_800A2344_main[i][j] == arg0[0] && D_800A2344_main[i][j + 1] == arg0[1]) {
                return i * 16 + j / 2;
            }
        }
    }
    return 16;
}

// Converts a two byte per character string into a one byte per character string.
void func_8005FBA4_main(u8 *buffer, s32 message) {
    u8 *str = (u8 *)message;

    if (*str != 0) {
        do {
            *buffer = func_8005FA90_main(str);
            str += 2;
            buffer++;
        } while (*str != 0);
    }
    *buffer = 0;
}

INCLUDE_ASM("asm/nonmatchings/window", func_8005FBF8_main);

void func_8005FE54_main(s16 winId, s16 arg1) {
    TextWindow *window = &D_800CC69C_main[winId];

    window->unk21 = (window->unk21 & 0xF0) | arg1;
}

void func_8005FE90_main(s16 winId) {
    TextWindow *window = &D_800CC69C_main[winId];
    s16 i;

    HuSprAttrSet(window->unk_6C, 0, 0x8000);
    HuSprAttrSet(window->unk_6C, 1, 0x8000);
    for (i = 4; i < 22; i++) {
        if (window->unk_6E[i] != -1) {
            HuSprAttrSet(window->unk_6C, i, 0x8000);
        }
    }
    if (window->unk6A != -1) {
        HuSprAttrSet(window->unk_6C, 2, 0x8000);
    }
    if (window->unk20 & 2) {
        HuSprAttrSet(window->unk_6C, 3, 0x8000);
    }
    func_8005B63C_main(winId, 0x4008, 8);
}

void func_8005FFA8_main(s16 winId) {
    TextWindow *window = &D_800CC69C_main[winId];
    s16 i;

    HuSprAttrReset(window->unk_6C, 0, 0x8000);
    HuSprAttrReset(window->unk_6C, 1, 0x8000);
    for (i = 4; i < 22; i++) {
        if (window->unk_6E[i] != -1) {
            HuSprAttrReset(window->unk_6C, i, 0x8000);
        }
    }
    if (window->unk6A != -1) {
        HuSprAttrReset(window->unk_6C, 2, 0x8000);
    }
    if (window->unk20 & 2) {
        HuSprAttrReset(window->unk_6C, 3, 0x8000);
    }
    func_8005B63C_main(winId, 0x4008, 0x4000);
}

void func_800600C0_main(s16 winId, s32 arg1) {
    TextWindow *window;

    window = &D_800CC69C_main[winId];
    if (arg1 != 0) {
        window->unk_38 |= 0x10;
    } else {
        window->unk_38 &= ~0x10;
    }
}

// Sets an option disabled.
void func_8006010C_main(s32 winId, s16 spriteIndex) {
    TextWindow *window = &D_800CC69C_main[winId];

    window->unk_F4[spriteIndex].unk_00 = 2;
}

void func_80060144_main(s16 obj) {
#ifdef DEBUG

#endif
}

s16 func_8006014C_main(s32 winId) {
    return D_800CC69C_main[winId].unk_31;
}

// Copies a string, dropping any newline characters it contains.
void func_80060174_main(u8 *str, u8 *buffer) {
    if (*str != 0) {
        do {
            if (*str == '\n') {
                str++;
            } else {
                *buffer = *str;
                str++;
                buffer++;
            }
        } while (*str != 0);
    }
    *buffer = *str;
}

void func_800601BC_main(s16 winId, u32 arg1, s8 arg2) {
    TextWindow *window = &D_800CC69C_main[winId];

    func_8005B6BC_main(winId, arg1, arg2);
    func_80060174_main(window->unk_B8[arg2], window->unk_B8[arg2]);
}

// Called to indicate that `str` should be the replacement at a
// "replacement index" location in the main string.
void func_8006022C_main(u32 str, s16 index) {
    D_800BDA6A_main = 1;
    D_800BDA6E_main = 0;
    D_800BDA6C_main = 0;
    func_800605A4_main(str);
    D_800CD2A4_main = 0;
    D_800D5206_main[index] = D_800BDA6D_main;
}

void func_80060290_main(u32 str, s16 index) {
    u8 *text;
    u8 allocated;

    D_800BDA6A_main = 1;
    D_800BDA6E_main = 0;
    D_800BDA6C_main = 0;
    if (str > 0x80000000) {
        allocated = 0;
        text = (u8 *)str;
    } else {
        allocated = 1;
        text = func_800364DC_main((void *)str);
    }
    func_80060174_main(text, text);
    func_800605A4_main((u32)text);
    D_800CD2A4_main = 0;
    if (allocated) {
        func_800365E8_main(text);
    }
    D_800D5206_main[index] = D_800BDA6D_main;
}

void func_8006034C_main(s16 winId, s16 arg1, u8 arg2) {
    D_800CC69C_main[winId].unk_B2[arg1] = arg2;
}

void func_80060388_main(s8 arg0) {
    D_800D5540_main = arg0;
}

void func_80060394_main(s16 count, s16 *size, ...) {
    va_list args;
    s16 i;

    D_800BDA6A_main = 0;
    va_start(args, size);
    D_800BDA6E_main = 0;
    D_800BDA6C_main = 0;
    for (i = 0; i < count; i++) {
        func_800605A4_main(va_arg(args, u32));
    }
    va_end(args);
    for (i = 0; i < ARRAY_COUNT(D_800D5206_main); i++) {
        D_800D5206_main[i] = 0;
    }
    D_800D5540_main = 0xC;
    size[0] = D_800BDA6C_main + 10;
    size[1] = D_800BDA6E_main + 6;
}

void func_800604A8_main(s16 *arg0, s16 arg1, s16 arg2) {
    u32 i;

    if (arg2 < arg1) {
        arg0[1] = 0x64;
        arg0[0] = 0x64;
        return;
    }

    D_800BDA6A_main = 0;
    D_800BDA6E_main = 0;
    D_800BDA6C_main = 0;

    for (i = arg1; arg2 >= i; i++) {
        func_800605A4_main(i);
    }

    for (i = 0; i < ARRAY_COUNT(D_800D5206_main); i++) {
        D_800D5206_main[i] = 0;
    }

    D_800D5540_main = 0xC;
    arg0[0] = D_800BDA6C_main + 10;
    arg0[1] = D_800BDA6E_main + 6;
}

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7CB0_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7CD4_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7CF8_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7D1C_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7D40_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7D64_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7D88_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7DAC_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7DD0_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7DF4_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7E18_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7E3C_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7E60_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7E84_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7EA8_main);

INCLUDE_RODATA("asm/nonmatchings/window", D_800A7ECC_main);

INCLUDE_ASM("asm/nonmatchings/window", func_800605A4_main);

void func_80060848_main() {
    D_800CD2A4_main = 1;
}

void func_80060858_main(s32 winId, s16 arg1) {
    TextWindow *window;

    window = &D_800CC69C_main[winId];
    window->unk_A6 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/window", func_80060880_main);

void func_80060C14_main(s32 winId, s32 playSound) {
    TextWindow *window = &D_800CC69C_main[winId];
    s16 i;
    f32 scale;

    if (!(window->unk_38 & 0x4000)) {
        func_800600C0_main(winId, 1);
        if (playSound) {
            if (window->unk_38 & 0x20) {
                HuAudFXPlay(0);
            } else {
                HuAudFXPlay(0x11D);
            }
        }
        for (i = 0; i < 10; i++) {
            scale = sindf(i * 10.0f) * ((f32)(window->unk40 + 4) / window->unk40);
            HuSprScaleSet(window->unk_6C, window->unk274, scale, scale);
            func_8005BB18_main(winId, scale, scale);
            if (window->unk276 != 0) {
                HuSprScaleSet(window->unk_6C, window->unk276, scale, scale);
            }
            HuPrcVSleep();
        }
        HuSprScaleSet(window->unk_6C, window->unk274, 1.0f, 1.0f);
        if (window->unk276 != 0) {
            HuSprScaleSet(window->unk_6C, window->unk276, 1.0f, 1.0f);
        }
        func_8005BB18_main(winId, 1.0f, 1.0f);
        func_800600C0_main(winId, 0);
        func_8005B63C_main(winId, 0x4000, 0x4000);
        HuPrcVSleep();
    }
}

void func_80060DEC_main(s32 win_id) {
    TextWindow *window = &D_800CC69C_main[win_id];

    func_800600C0_main(win_id, 1);
    HuSprScaleSet(window->unk_6C, window->unk274, 1.0f, 1.0f);
    if (window->unk276 != 0) {
        HuSprScaleSet(window->unk_6C, window->unk276, 1.0f, 1.0f);
    }
    func_8005BB18_main(win_id, 1.0f, 1.0f);
    func_800600C0_main(win_id, 0);
    func_8005B63C_main(win_id, 0x4000, 0x4000);
}

void func_80060EA8_main(s32 winId, s32 playSound) {
    TextWindow *window = &D_800CC69C_main[winId];
    f32 scale = 1.0f;

    if (window->unk_38 & 0x4000) {
        func_800600C0_main(winId, 1);
        if (playSound) {
            if (window->unk_38 & 0x20) {
                HuAudFXPlay(0);
            } else {
                HuAudFXPlay(0x137);
            }
        }
        while (scale > 0.0f) {
            HuSprScaleSet(window->unk_6C, window->unk274, scale, scale);
            if (window->unk276 != 0) {
                HuSprScaleSet(window->unk_6C, window->unk276, scale, scale);
            }
            func_8005BB18_main(winId, scale, scale);
            scale -= 0.1f;
            HuPrcVSleep();
        }
        HuSprScaleSet(window->unk_6C, window->unk274, scale, scale);
        if (window->unk276 != 0) {
            HuSprScaleSet(window->unk_6C, window->unk276, scale, scale);
        }
        func_8005BB18_main(winId, scale, scale);
        func_800600C0_main(winId, 0);
        func_8005B63C_main(winId, 0x4000, 0);
    }
}

void func_8006105C_main(s32 winId, s32 alpha) {
    TextWindow *window = &D_800CC69C_main[winId];

    HuSprAttrSet(window->unk_6C, window->unk274, 0x1000);
    alpha &= 0xFF;
    func_80055458_main(window->unk_6C, window->unk274, alpha);
    if (window->unk276 != 0) {
        func_80055458_main(window->unk_6C, window->unk276, alpha);
    }
}

void func_800610E0_main(s16 win_id) {
    func_8005F364_main(win_id);
}

void func_80061100_main(s16 win_id, s32 priority) {
    TextWindow *window = &D_800CC69C_main[win_id];

    func_8005BE30_main(win_id, (s16)priority);
    HuSprPriSet(window->unk_6C, window->unk274, priority + 1);
    if (window->unk276 != 0) {
        HuSprPriSet(window->unk_6C, window->unk276, priority + 2);
    }
}

// Obtains a window handle
s32 func_80061188_main(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5) {
    TextWindow *temp_s2;
    s32 temp_v0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s0 = arg3 + 2;

    if ((arg0 != -1) & (arg4 < 0x30)) {
        arg4 = 0x30;
    }

    temp_v0 = func_8005A968_main(arg1, arg2, temp_s0, arg4, 0, arg5);
    func_8005BDFC_main(temp_v0, 0);
    temp_s2 = &D_800CC69C_main[temp_v0];
    func_8005BCA4_main(temp_v0, temp_s0 / 2, arg4 / 2);
    func_8005BA90_main(temp_v0, (temp_s2->unk3C + temp_s0 / 2), (temp_s2->unk3E + arg4 / 2));
    temp_s2->unk276 = arg0;

    if (arg0 != -1) {
        temp_s2->unk274 = func_8005B7B8_main(temp_v0, D_800A25D0_main[arg0], (0x18 - temp_s2->unk48), (0x18 - temp_s2->unk4A), 0);
    }

    temp_s2->unk54 = 6;
    temp_s2->unk4C = 6;
    func_8005BEE0_main(temp_v0, 0xD0);
    func_8005C060_main(temp_v0, 1, 0x40, 0xF0, 0xFF);
    func_8005FBF8_main(temp_v0, 0x40, 0x20, 0xB0);
    func_8005D294_main(temp_v0);
    func_8005FE90_main(temp_v0);
    func_8005F904_main();
    return temp_v0;
}

void func_80061388_main(s16 winId) {
    TextWindow *window = &D_800CC69C_main[winId];
    s16 i;

    func_800600C0_main(winId, 1);
    if (window->unk276 != -1) {
        HuSprScaleSet(window->unk_6C, window->unk274, 0.0f, 0.0f);
    }
    func_8005FFA8_main(winId);
    for (i = 1; i < 6; i++) {
        func_8005BBC0_main(winId, 1.0f - cosdf(i * 18.0f), 2.0f / window->unk42);
        HuPrcVSleep();
    }
    for (i = 1; i < 4; i++) {
        func_8005BBC0_main(winId, 1.0f, sindf(i * 30.0f) * 1.05f);
        HuPrcVSleep();
    }
    func_8005BBC0_main(winId, 1.0f, 1.0f);
    if (window->unk276 != -1) {
        func_80054904_main(window->unk_6C, window->unk274, 0x18 - window->unk48, 0x18 - window->unk4A);
        HuSprScaleSet(window->unk_6C, window->unk274, 1.0f, 1.0f);
        func_800615B8_main(winId, 1);
    }
    func_800600C0_main(winId, 0);
}

INCLUDE_ASM("asm/nonmatchings/window", func_800615B8_main);

void func_80061934_main(s16 winId, s16 arg1) {
    s16 temp_v0;
    TextWindow *temp_s0;

    temp_s0 = &D_800CC69C_main[winId];
    func_800600C0_main(winId, 1);
    func_800615B8_main(winId, 0);
    func_8005B8F8_main(winId, temp_s0->unk274);
    temp_v0 = func_8005B7B8_main(winId, D_800A25D0_main[arg1], 0x18 - temp_s0->unk48, 0x18 - temp_s0->unk4A, 0);
    temp_s0->unk274 = temp_v0;
    func_80054904_main(temp_s0->unk_6C, temp_v0, 0x18 - temp_s0->unk48, 0x18 - temp_s0->unk4A);
    HuSprScaleSet(temp_s0->unk_6C, temp_s0->unk274, 1.0f, 1.0f);
    func_800615B8_main(winId, 1);
    func_800600C0_main(winId, 0);
}

void func_80061A5C_main(s16 arg0, s16 arg1) {
    s16 i;

    if (arg1 == 0) {
        func_8005D294_main(arg0);

        for (i = 0; i < 5; i++) {
            func_8005BB18_main(arg0, 1.0f, 1.0f - sindf(i * 18.0f));
            HuPrcVSleep();
        }

        func_8005FE90_main(arg0);
        HuPrcVSleep();
        return;
    }
    func_8005FE90_main(arg0);
}
