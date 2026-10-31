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

typedef struct WindowFont {
    u32 unk00[2];
    u32 glyphOffset;
} WindowFont;

typedef struct WindowFrameDefinition {
    u32 file;
    u32 shadowFile;
    s16 width;
    s16 height;
    u16 textX;
    u16 textY;
    u16 textWidth;
    u16 textHeight;
    u16 spriteWidth;
    u16 spriteHeight;
    u8 speed;
    u8 attributes;
    u8 pad1A[2];
} WindowFrameDefinition;

extern u8 D_800A2154_main[];
extern u16 D_800A2174_main[];
extern WindowFrameDefinition D_800A2384_main[];
extern WindowIconDefinition D_800A2294_main[];
extern TextWindow *winData;
extern s32 D_800D209C_main;
extern u8 D_800A2194_main[];
extern u16 D_800A2186_main[];
extern u8 D_800A2150_main;
extern u8 D_800D6A90_main;
extern u8 gLanguageIndex;
extern u8 D_800A2324_main[];
extern u8 D_800A2325_main[];
extern u8 D_800A232C_main[];
extern u8 *D_800A2344_main[];
extern s16 D_800BDA50_main[12];
extern s8 D_800BDA6D_main;
extern s16 D_800BDA68_main;
extern u8 cancelCRF;
extern void *D_800CE2C4_main;
extern Process *winProc;
extern u8 comKeyIdx;
extern u8 D_800D2008_main;
extern WindowFont *D_800D1FE4_main;
extern void *D_800D4084_main;
extern u8 mesWInsert[5];
extern s8 winTabSize;
extern s8 comKeyIdxNow;
extern s16 winPrio;
extern s32 D_800A25D0_main[];
extern u8 winInsertF;
extern u16 winMaxWidth;
extern u16 winMaxHeight;
extern u8 mesWInsert[5];
extern s8 winTabSize;

void func_8005B040_main(u8 *, s16, s16);
void func_8005B238_main(u8 *, s16, s16);
s16 HuWinSprIDGet(s16, s16);
void HuWinScaleSet(s16, f32, f32);
void func_800615B8_main(s16, s32);
s32 func_8005CC3C_main(TextWindow *, s16);
void func_8005CD84_main(TextWindow *);
void _HuWinHomeClear(TextWindow *);
void *func_8005DAA4_main(s16);
void func_8005D83C_main(s16, s16, s16, s16, s16);
void HuWinComKeyGet(s16 *);
s16 func_8005B614_main(s32);
void func_8005CF94_main(s16);
void HuWinMesSizeCancelCRSet(void);
void func_8005DD14_main(s16);
s32 HuWinDrawMes(s16);
s32 func_8005CC18_main(TextWindow *);
void func_8005CEB0_main(s16);
s32 HuWinSpcFontEntry(s16, s16);
void func_8005D30C_main(s16, u8, u8, s16, s16);
s32 HuWinChoice(s16);
void func_8005EEE4_main(TextWindow *, TextWindowSprite *);
s32 HuWinActivePadGet(TextWindow *);

void HuWinInit(void) {
    Process *temp_v0_4;
    void *temp_v0_6;
    s16 i;

    if (D_800A2150_main == 0) {
        winData = HuMemMemoryAllocTemp(sizeof(TextWindow) * WINDOWS_MAX);

        for (i = 0; i < WINDOWS_MAX; i++) {
            winData[i].unk5E = -1;
        }

        winData[0].unk62 = -1;
        winData[0].unk64 = 1;
        winData[0].unk5E = 0;
        winData[1].unk62 = 0;
        winData[1].unk64 = -1;
        winData[1].unk5E = -0x218;
        comKeyIdxNow = 0;
        comKeyIdx = 0;
        winPrio = 0x2710;
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

        temp_v0_4 = omAddPrcObj(HuWinProc, 0x1001, 0x800, 0);
        winProc = temp_v0_4;
        omPrcSetStatBit(temp_v0_4, 0xA0);

        D_800A2150_main = 1;
        D_800CB99C_main = 0;
        D_800D4084_main = DataReadTemp(0x00000029);
        D_800CE2C4_main = DataReadTemp(0x0000002A);

        for (i = 0; i < ARRAY_COUNT(D_800BDA50_main); i++) {
            D_800BDA50_main[i] = -1;
        }

        temp_v0_6 = DataRead(0x00000033);
        D_800BDA68_main = HuSprAnimRead(temp_v0_6);
        DataClose(temp_v0_6);

        for (i = 0; i < ARRAY_COUNT(mesWInsert); i++) {
            mesWInsert[i] = 0;
        }

        winTabSize = 0xC;
        cancelCRF = 0;
    }
}

s16 HuWinCreate(s16 x, s16 y, s16 width, s16 height, s32 arg4, s16 flags) {
    s16 winId;
    s16 i;
    s16 group;
    TextWindow *window;
    HuSprite *sprite;
    s32 size;
    s32 pixelHeight;
    s32 pixelWidth;

    for (winId = 2; winId < WINDOWS_MAX; winId++) {
        if (winData[winId].unk5E == -1) {
            break;
        }
    }
    if (winId == WINDOWS_MAX) {
        return -1;
    }
    if (width & 1) {
        width++;
    }
    window = &winData[winId];
    window->unk64 = 1;
    window->unk62 = winData[1].unk62;
    window->unk5E = 0x7D00;
    winData[winData[1].unk62].unk64 = winId;
    winData[1].unk62 = winId;
    window->w = width;
    window->h = height;
    if (flags & 2) {
        window->pos_x = (320 - width) / 2;
        window->pos_y = (240 - height) / 2;
    } else if (!(flags & 4)) {
        if (x + width > 296) {
            window->pos_x = 296 - width;
        } else {
            window->pos_x = x;
        }
        if (y + height > 224) {
            window->pos_y = 224 - height;
        } else {
            window->pos_y = y;
        }
    } else {
        window->pos_x = x;
        window->pos_y = y;
    }
    window->unk44 = (width + 15) & 0xFFF0;
    window->unk46 = height + 16;
    window->scaleX = window->scaleY = 1.0f;
    window->mess_rect_x = window->mess_rect_y = window->mess_x = window->mess_y = 4;
    window->mess_rect_w = width - 8;
    window->mess_rect_h = height - 8;
    window->stat = 0;
    window->mess_color = 7;
    window->unk_23 = 7;
    window->mess_shadow_color = 0;
    window->speed = window->unk_26 = 1;
    window->unk_27 = 10;
    window->unk_28 = 12;
    window->spacing_x = 0;
    window->spacing_y = 2;
    window->unk58 = window->w - window->unk_27 - 4;
    window->unk5A = window->h - window->unk_28;
    window->unk48 = window->unk4A = 0;
    window->backgroundRed = D_800A2154_main[0];
    window->backgroundGreen = D_800A2154_main[1];
    window->backgroundBlue = D_800A2154_main[2];
    window->active_pad = 15;
    window->choice = window->unk_32 = 0;
    window->attr = 0;
    window->unk_D0 = NULL;
    window->push_key = 0;
    window->insertionIndex = -1;
    window->tab_w = 12;
    for (i = 0; i < 5; i++) {
        window->insert_mess[i] = NULL;
        window->unk_B2[i] = -1;
    }
    window->unk_E0[0] = NULL;
    window->cursor_sprite = -1;
    window->unk_24 = 0;
    for (i = 0; i < 22; i++) {
        window->sprite_id[i] = i >= 3 ? -1 : 0;
    }
    window->unk_9A = 0;
    window->unk66 = HuSprAnimRead(D_800D4084_main);
    window->unk68 = HuSprAnimRead(D_800CE2C4_main);
    group = HuSprGrpCreate(22, 5);
    window->group = group;
    HuSprTPLvlSet(group, 0, 0x100);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 0x1009000);
    func_80055024_main(group, 0, window->unk66, 0);
    func_800550F4_main(group, 0, 0);
    func_800554C4_main(group, 0, -1);
    HuSprPosSet(group, 0, window->pos_x, window->pos_y);
    HuSprColorSet(window->group, 0, 64, 32, 176);
    sprite = HuSprGet(group, 0);
    if (!(flags & 8)) {
        sprite->unk_84->unk00->unk04 = width;
        sprite->unk_84->unk00->unk06 = height;
        HuMemFree(sprite->unk_84->unk00->unk00);
        pixelWidth = width;
        pixelHeight = height;
        size = pixelWidth * pixelHeight / 2;
        sprite->unk_84->unk00->unk00 = window->pixels = HuMemAlloc(size);
        memset(window->pixels, 0xFF, size);
        if (!(flags & 1)) {
            if (flags & 16) {
                func_8005B238_main(window->pixels, pixelWidth, pixelHeight);
            } else {
                func_8005B040_main(window->pixels, width, height);
            }
        }
        HuSprTPLvlSet(group, 0, 100);
        HuSprAttrReset(group, 0, 0x8000);
        func_800550F4_main(group, 0, 0);
    } else {
        HuSprTPLvlSet(group, 0, 0);
        HuSprAttrSet(group, 0, 0x8000);
        func_800550F4_main(group, 0, 0);
    }
    HuSprTPLvlSet(group, 1, 0x100);
    HuSprAttrReset(group, 1, 0xFFFF);
    HuSprAttrSet(group, 1, 0x1009000);
    func_80055024_main(group, 1, window->unk68, 0);
    func_800550F4_main(group, 1, 0);
    HuSprPosSet(group, 1, 0, 0);
    func_800554C4_main(group, 1, 0);
    bcopy(D_800A2174_main, window, 32);
    for (i = 0; i < 22; i++) {
        HuSprPriSet(group, i, winPrio);
    }
    HuSprPriSet(group, 2, winPrio - 1);
    window->prio = winPrio;
    winPrio -= 32;
    window->unk_AA = 312;
    return winId;
}

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

void HuWinMesSet(s16 winId, u32 message, s16 x, s16 y) {
    TextWindow *window = &winData[winId];
    s16 width;

    if (window->unk_D0 != NULL && window->unk_D4 != 0) {
        func_800365E8_main(window->unk_D0);
    }
    if ((u8)window->stat == 2) {
        func_8005CF94_main(winId);
    }
    window->mess_time = 1;
    if (0x80000000 < message) {
        window->unk_D4 = 0;
        window->mess = (u8 *)message;
    } else {
        window->unk_D4 = 1;
        window->unk_D0 = func_800364DC_main((void *)message);
        window->mess = window->unk_D0;
    }
    if (x >= 0) {
        window->mess_x = x;
    } else if (x == -2) {
        if (window->attr & 0x40000) {
            HuWinMesSizeCancelCRSet();
        }
        width = func_8005B614_main((s32)window->mess);
        cancelCRF = 0;
        window->mess_x = (window->w - width) / 2;
        window->attr |= 0x800;
    }
    if (y >= 0) {
        window->mess_y = y;
    } else if (y == -2) {
        window->mess_y = (window->h - 12) / 2;
        window->attr |= 0x1000;
    }
    window->stat = 1;
    window->num_choices = 0;
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

    HuWinMesMaxSizeGet(1, size, arg0);
    return size[0];
}

void func_8005B63C_main(s16 winId, s32 arg1, s32 arg2) {
    TextWindow *window = &winData[winId];

    window->attr = arg2 | (window->attr & ~arg1);
    if (arg2 & 0x20) {
        window->unk_AA = 0;
    }
}

s32 func_8005B68C_main(s16 win_id) {
    return winData[win_id].attr;
}

void HuWinInsertMesSet(s16 win_id, u32 arg1, s8 arg2) {
    TextWindow *textWindow = &winData[win_id];

    if (textWindow->insert_mess[arg2] != 0) {
        if (textWindow->usingStringIDBool[arg2] != 0) {
            func_800365E8_main(textWindow->insert_mess[arg2]);
        }
    }
    // pointer check
    if (0x80000000 < arg1) {
        textWindow->usingStringIDBool[arg2] = 0;
        textWindow->insert_mess[arg2] = (char *)arg1;
    } else {
        textWindow->usingStringIDBool[arg2] = 1;
        textWindow->insert_mess[arg2] = func_800364DC_main((void *)arg1);
    }
    textWindow->unk_B2[arg2] = -1;
}

s16 HuWinAnimSet(s16 win_id, u32 spriteMainFsPair, s16 arg2, s16 arg3, s16 arg4) {
    TextWindow *window = &winData[win_id];
    s16 spriteId;
    void *spriteBytes;
    s16 i;

    for (i = 4; i < 12; i++) {
        if (window->sprite_id[i] != -1) {
            continue;
        }
        break;
    }
    if (i >= 12) {
        return -1;
    }

    spriteBytes = DataRead(spriteMainFsPair);
    spriteId = HuSprAnimRead(spriteBytes);
    window->sprite_id[i] = spriteId;
    HuMemMemoryFreePerm(spriteBytes);
    func_80055024_main(window->group, i, spriteId, arg4);
    HuSprPosSet(window->group, i, arg2, arg3);
    func_800554C4_main(window->group, i, 0);
    return i;
}

void HuWinSprKill(s16 arg0, s16 arg1) {
    HuSprKill(HuWinSprIDGet(arg0, arg1));
    winData[arg0].sprite_id[arg1] = -1;
}

s16 func_8005B974_main(s16 winId, u32 spriteMainFsPair, s16 x, s16 y, s16 arg4) {
    TextWindow *window = &winData[winId];
    TextWindowSprite *sprite;
    s16 spriteId;

    spriteId = HuWinAnimSet(winId, spriteMainFsPair, x, y, arg4);
    sprite = &window->choice_data[window->num_choices];
    sprite->x = x;
    sprite->y = y;
    sprite->unk_06 = 0;
    sprite->unk_08 = 0;
    sprite->stat = 1;
    window->num_choices++;
    return spriteId;
}

TextWindow *HuWinGet(s16 win_id) {
    return &winData[win_id];
}

s16 HuWinSprIDGet(s16 arg0, s16 arg1) {
    TextWindow *window = &winData[arg0];
    return window->sprite_id[arg1];
}

void HuWinPosSet(s16 winId, s16 arg1, s16 arg2) {
    TextWindow *window;

    window = &winData[winId];

    HuSprPosSet(window->group, 0, arg1, arg2);
    window->pos_x = arg1;
    window->pos_y = arg2;
}

void HuWinScaleSet(s16 winId, f32 scaleX, f32 scaleY) {
    TextWindow *window = &winData[winId];
    s16 i;

    window->scaleX = scaleX;
    window->scaleY = scaleY;
    for (i = 0; i < 22; i++) {
        HuSprScaleSet(window->group, i, scaleX, scaleY);
    }
}

void func_8005BBC0_main(s16 winId, f32 scaleX, f32 scaleY) {
    TextWindow *window = &winData[winId];
    s16 i;

    window->scaleX = scaleX;
    window->scaleY = scaleY;
    for (i = 0; i < 4; i++) {
        HuSprScaleSet(window->group, i, scaleX, scaleY);
    }
    for (i = 12; i < 22; i++) {
        HuSprScaleSet(window->group, i, scaleX, scaleY);
    }
}

void func_8005BCA4_main(s16 arg0, s16 arg1, s16 arg2) {
    TextWindow *window = &winData[arg0];
    HuSprite *spr;
    s16 i;

    window->unk48 = arg1;
    window->unk4A = arg2;
    spr = HuSprGet(window->group, 0);
    spr->unk_84->unk00->unk08 = arg1;
    spr->unk_84->unk00->unk0A = arg2;
    spr = HuSprGet(window->group, 1);
    for (i = 0; i < spr->unk_84->unk12; i++) {
        spr->unk_84->unk00[i].unk08 = arg1;
        spr->unk_84->unk00[i].unk0A = arg2;
    }
}

void HuWinZRotSet(s16 winId, f32 arg1) {
    TextWindow *window;

    window = &winData[winId];
    HuSprZRotSet(window->group, 0, arg1);
}

void HuWinMesSpeedSet(s16 winId, s32 arg1) {
    TextWindow *window;

    window = &winData[winId];
    window->speed = arg1;
    window->unk_26 = arg1;
}

void HuWinPriSet(s16 winId, s32 priority) {
    TextWindow *window = &winData[winId];
    s16 i;

    window->prio = priority;
    for (i = 0; i < 22; i++) {
        HuSprPriSet(window->group, i, priority);
    }
    if (window->cursor_sprite != -1) {
        HuSprPriSet(window->group, 2, priority - 1);
    }
}

void HuWinBGTPLvlSet(s16 winId, s16 arg1) {
    TextWindow *window;

    window = &winData[winId];

    if (arg1 == 0) {
        HuSprAttrSet(window->group, 0, 0x8000);
    } else {
        HuSprAttrReset(window->group, 0, 0x8000);
    }
    HuSprTPLvlSet(window->group, 0, arg1 & 0xFFFF);
}

void func_8005BF70_main(s16 winId, s32 arg1) {
    TextWindow *window = &winData[winId];
    s16 i;

    HuSprTPLvlSet(window->group, 1, arg1 & 0xFFFF);
    for (i = 12; i < 22; i++) {
        if (window->sprite_id[i] != -1) {
            HuSprTPLvlSet(window->group, i, arg1 & 0xFFFF);
        }
    }
}

void HuWinMesColSet(s16 winId, s32 arg1) {
    TextWindow *window;

    window = &winData[winId];
    window->mess_color = arg1;
    window->unk_23 = arg1;
}

void HuWinMesPalSet(s16 winId, u8 index, u8 red, u8 green, u8 blue) {
    TextWindow *window = &winData[winId];
    HuSprite *sprite;
    u16 *palette;

    sprite = HuSprGet(window->group, 1);
    window->palette[index + 1] = ((red << 8) & 0xF800) | ((green << 3) & 0x7C0) | (u8)((blue >> 2) & 0x3E) | 1;
    palette = HuMemAlloc(sizeof(window->palette));
    bcopy(window, palette, sizeof(window->palette));
    func_80019C00_main(sprite->unk_84->unk0C);
    sprite->unk_84->unk0C = palette;
}

void func_8005C154_main(s16 winId, s32 red, s32 green, s32 blue) {
    HuWinMesPalSet(winId, 0, red & 0xFF, green & 0xFF, blue & 0xFF);
}

s32 HuWinDrawMes(s16 winId) {
    TextWindow *window = &winData[winId];
    TextWindowSprite *sprite;
    s16 colorSkip = 0;
    s16 tab;
    s16 width;
    s32 code;

    if ((u8)window->speed == 0xFF) {
        return 1;
    }
    while (window->mess_time >= (u8)window->unk_26) {
        while (*window->mess <= 0x20) {
            if (*window->mess == 0) {
                if (window->insertionIndex >= 0) {
                    if (window->unk_B2[window->insertionIndex] != -1) {
                        window->mess_color = window->unk_B2[5];
                    }
                    window->insertionIndex = -1;
                    window->mess = window->unk_D8;
                    continue;
                }
                if (window->unk_D4 != 0) {
                    func_800365E8_main(window->unk_D0);
                }
                window->unk_D0 = NULL;
                window->stat = 0;
                return 0;
            }
            if (*window->mess < 9) {
                if ((window->insertionIndex == -1) & (colorSkip != 0)) {
                    colorSkip--;
                } else {
                    window->mess_color = *window->mess - 1;
                    colorSkip = 0;
                    if (window->insertionIndex != -1) {
                        colorSkip = (window->mess[1] == 0) * 2;
                    }
                }
            }
            code = *window->mess - 0x11;
            if ((u8)code < 5) {
                window->insertionIndex = code;
                if (window->insert_mess[window->insertionIndex] != NULL) {
                    window->mess++;
                    window->unk_D8 = window->mess;
                    window->mess = window->insert_mess[window->insertionIndex];
                    if (window->unk_B2[window->insertionIndex] != -1) {
                        window->unk_B2[5] = window->mess_color;
                        window->mess_color = window->unk_B2[window->insertionIndex];
                    }
                    continue;
                }
                window->insertionIndex = -1;
            }
            if (window->attr & 4) {
                if (((*window->mess == 0x10) | (*window->mess == 0x20)) || *window->mess == 0x1A) {
                    if (*window->mess == 0x1A) {
                        *window->mess = 0x60;
                    } else {
                        *window->mess = 0x40;
                    }
                    break;
                }
            }
            switch (*window->mess) {
                case 0x10:
                case 0x1A:
                case 0x20:
                    if (gLanguageIndex == LANGUAGE_JAPANESE) {
                        window->unk_34 = 10;
                    } else if (*window->mess == 0x1A || (window->attr & 0x80000)) {
                        window->unk_34 = 10;
                    } else {
                        window->unk_34 = 4;
                    }
                    window->mess++;
                    if (!func_8005CC18_main(window)) {
                        window->stat = 6;
                        func_8005CEB0_main(winId);
                        return 1;
                    }
                    continue;
                case 0xA:
                    if (!(window->attr & 0x40000) && !HuWinCR(window) && window->mess[1] != 0) {
                        window->stat = 6;
                        func_8005CEB0_main(winId);
                        window->mess++;
                        return 1;
                    }
                    break;
                case 0x17:
                    if (!(window->attr & 0x40000) && !func_8005CD38_main(window)) {
                        window->mess++;
                        return 1;
                    }
                    break;
                case 0xB:
                    if (window->attr & 4) {
                        _HuWinHomeClear(window);
                    } else if (window->insertionIndex < 0 && !(window->attr & 0x1800)) {
                        func_8005CD84_main(window);
                    }
                    break;
                case 0xC:
                    sprite = &window->choice_data[window->num_choices];
                    sprite->x = window->mess_x - window->unk48;
                    sprite->y = window->mess_y - window->unk4A;
                    window->unk_26 = 0;
                    window->mess_time = 0;
                    break;
                case 0xD:
                    sprite = &window->choice_data[window->num_choices];
                    sprite->unk_06 = window->mess_x - (u16)sprite->x;
                    sprite->unk_08 = window->mess_y - (u16)sprite->y + window->unk_28;
                    sprite->stat = 0;
                    window->unk_26 = window->speed;
                    window->num_choices++;
                    if (window->num_choices >= TEXT_WINDOW_SPRITES_MAX) {
                        osSyncPrintf("Select Max Over!\n");
                        window->num_choices--;
                    }
                    break;
                case 0xE:
                    tab = ((s16)(window->mess_x - window->mess_rect_x) + window->tab_w) / window->tab_w * window->tab_w;
                    if (tab < window->mess_rect_w) {
                        window->mess_x = tab + window->mess_rect_x;
                    }
                    break;
                case 0xF:
                    window->attr |= 0x20000;
                    break;
                case 0x16:
                    window->attr &= ~0x20000;
                    break;
                case 0x18:
                    window->mess++;
                    break;
                case 0x19:
                    if ((window->insertionIndex == -1) & (colorSkip != 0)) {
                        colorSkip--;
                    } else {
                        window->mess_color = window->unk_23;
                    }
                    break;
            }
            window->mess++;
        }
        if ((u32)(*window->mess - 0x21) < 0xF) {
            width = HuWinSpcFontEntry(winId, *window->mess - 0x21) + (u8)window->spacing_x;
            window->mess++;
            if (!func_8005CC3C_main(window, width)) {
                window->stat = 6;
                func_8005CEB0_main(winId);
                return 1;
            }
            continue;
        }
        if (*window->mess == 0xFF) {
            window->stat = 2;
            func_8005CEB0_main(winId);
            window->mess++;
            return 1;
        }
        window->mess_time -= (u8)window->unk_26;
        if ((s16)window->mess_y + window->unk_28 > window->mess_rect_y + window->mess_rect_h) {
            window->stat = 6;
            func_8005CEB0_main(winId);
            return 1;
        }
        if (*window->mess >= 0x30) {
            if (window->attr & 0x10000) {
                if ((u8)(*window->mess - 0x30) < 10) {
                    *window->mess += 0x70;
                }
            }
            if (window->attr & 0x80) {
                if ((u8)window->mess_color != 0) {
                    func_8005D30C_main(winId, *window->mess, 0, window->mess_x + 2, window->mess_y + 1);
                }
                func_8005D30C_main(winId, *window->mess, window->mess_color, window->mess_x, window->mess_y);
                func_8005D30C_main(winId, *window->mess, window->mess_color, window->mess_x + 1, window->mess_y);
            } else if (window->attr & 0x20000) {
                func_8005D30C_main(winId, *window->mess, window->mess_shadow_color, window->mess_x, window->mess_y - 1);
                func_8005D30C_main(winId, *window->mess, window->mess_shadow_color, window->mess_x, window->mess_y + 1);
                func_8005D30C_main(winId, *window->mess, window->mess_shadow_color, window->mess_x + 1, window->mess_y);
                func_8005D30C_main(winId, *window->mess, window->mess_shadow_color, window->mess_x - 1, window->mess_y);
                func_8005D30C_main(winId, *window->mess, window->mess_color, window->mess_x, window->mess_y);
            } else {
                if ((u8)window->mess_color != 0) {
                    func_8005D30C_main(winId, *window->mess, 0, window->mess_x + 1, window->mess_y + 1);
                }
                func_8005D30C_main(winId, *window->mess, window->mess_color, window->mess_x, window->mess_y);
            }
        }
        window->mess++;
        if ((u8)(*window->mess + 0x80) < 2) {
            if (window->attr & 0x20000) {
                func_8005D30C_main(winId, *window->mess, window->mess_shadow_color, window->unk_27 + window->mess_x - 3, window->mess_y - 2);
                func_8005D30C_main(winId, *window->mess, window->mess_shadow_color, window->unk_27 + window->mess_x - 3, window->mess_y);
                func_8005D30C_main(winId, *window->mess, window->mess_shadow_color, window->unk_27 + window->mess_x - 4, window->mess_y - 1);
                func_8005D30C_main(winId, *window->mess, window->mess_shadow_color, window->unk_27 + window->mess_x - 2, window->mess_y - 1);
            } else if ((u8)window->mess_color != 0) {
                func_8005D30C_main(winId, *window->mess, 0, window->unk_27 + window->mess_x - 2, window->mess_y);
            }
            func_8005D30C_main(winId, *window->mess, window->mess_color, window->unk_27 + window->mess_x - 3, window->mess_y - 1);
            window->mess++;
        }
        if (!func_8005CC18_main(window)) {
            return 1;
        }
    }
    window->mess_time++;
    return 1;
}

s32 func_8005CC18_main(TextWindow *window) {
    return func_8005CC3C_main(window, window->unk_34 + (u8)window->spacing_x);
}

s32 func_8005CC3C_main(TextWindow *window, s16 advance) {
    s32 width;

    D_800D209C_main = advance;
    window->mess_x += advance;
    if (gLanguageIndex == LANGUAGE_JAPANESE) {
        width = window->unk_27;
    } else if (window->attr & 0x80000) {
        width = 10;
    } else {
        width = D_800A2194_main[*window->mess];
    }
    if (width + (s16)window->mess_x > (s16)window->mess_rect_x + window->mess_rect_w && *window->mess >= 0x20) {
        return HuWinCR(window);
    }
    return 1;
}

s32 HuWinCR(TextWindow *window) {
    window->mess_x = window->mess_rect_x;
    window->mess_y = window->mess_y + (window->unk_28 + window->spacing_y);
    return ((s16)window->mess_y + window->unk_28) <= (window->mess_rect_y + window->mess_rect_h);
}

s32 func_8005CD38_main(TextWindow *window) {
    window->mess_x = window->mess_rect_x;
    window->mess_y = window->mess_y + ((window->unk_28 >> 2) + window->spacing_y);
    return ((s16)window->mess_y + window->unk_28) <= (window->mess_rect_y + window->mess_rect_h);
}

void func_8005CD84_main(TextWindow *window) {
    void *pixels;

    func_8005DD54_main(window);
    pixels = func_8005DAA4_main(((u32)window - (u32)winData) / sizeof(TextWindow));
    if (window->unk_E0[0] != NULL) {
        memset(pixels, 0, (window->unk44 * window->unk46) / 2);
    }
    _HuWinHomeClear(window);
}

void _HuWinHomeClear(TextWindow *window) {
    s16 i;

    window->mess_x = window->mess_rect_x;
    window->mess_y = window->mess_rect_y;
    window->num_choices = 0;
    window->unk_9A = 0;
    for (i = 12; i < 22; i++) {
        if (window->sprite_id[i] != -1) {
            HuSprAttrSet(window->group, i, 0x8000);
            window->sprite_id[i] = -1;
        }
    }
}

void func_8005CEB0_main(s16 winId) {
    TextWindow *window = &winData[winId];

    func_80055024_main(window->group, 3, D_800BDA68_main, 0);
    HuSprAttrReset(window->group, 3, 0xFFFF);
    HuSprAttrSet(window->group, 3, 0x1000000);
    HuSprPriSet(window->group, 3, window->prio - 1);
    HuSprPosSet(window->group, 3, window->unk58 - window->unk48, window->unk5A - window->unk4A);
    if (window->attr & 8) {
        HuSprAttrSet(window->group, 3, 0x8000);
    }
}

void func_8005CF94_main(s16 winId) {
    TextWindow *window = &winData[winId];

    HuSprAttrSet(window->group, 3, 0x8000);
}

s32 HuWinSpcFontEntry(s16 winId, s16 icon) {
    TextWindow *window = &winData[winId];
    s16 sprite;
    s16 graphic;
    void *data;

    graphic = D_800BDA50_main[icon];
    if (graphic == -1) {
        if (window->attr & 0x2000) {
            data = DataRead(D_800A2294_main[icon].highlightedFile);
        } else {
            data = DataRead(D_800A2294_main[icon].file);
        }
        D_800BDA50_main[icon] = graphic = HuSprAnimRead(data);
        HuMemMemoryFreePerm(data);
    }
    for (sprite = 12; sprite < 22; sprite++) {
        if (window->sprite_id[sprite] == -1) {
            break;
        }
    }
    if (sprite >= 22) {
        return 0;
    }
    window->sprite_id[sprite] = graphic;
    HuSprAttrSet(window->group, sprite, 0x1000);
    func_80055024_main(window->group, sprite, graphic, D_800A2294_main[icon].bank);
    HuSprPosSet(window->group, sprite, window->mess_x - window->unk48, window->mess_y - window->unk4A);
    func_800554C4_main(window->group, sprite, 0);
    if ((u8)window->mess_color == 0) {
        HuSprColorSet(window->group, sprite, 0, 0, 0);
    } else if (window->attr & 0x2000) {
        HuSprColorSet(window->group, sprite, 0x61, 0x61, 0xF8);
    } else {
        HuSprColorSet(window->group, sprite, 0x38, 0xF8, 0x25);
    }
    if (window->attr & 8) {
        HuSprAttrSet(window->group, sprite, 0x8000);
    } else {
        HuSprAttrReset(window->group, sprite, 0x8000);
    }
    return D_800A2294_main[icon].width;
}

void HuWinHomeClear(s16 winId) {
    func_8005CD84_main(&winData[winId]);
}

void func_8005D2D4_main(s16 win_id) {
    func_8005B63C_main(win_id, 0x40000, 0x40000);
}

void func_8005D2FC_main(void) {
    cancelCRF = 1;
}

#ifdef NON_MATCHING
/* Seven register uses differ: the saved buffer/window ID and glyph character index. */
void func_8005D30C_main(s16 winId, u8 character, u8 color, s16 x, s16 y) {
    TextWindow *window = &winData[winId];
    u8 *pixels;
    u8 *pixelData;
    u8 *glyph;
    s16 width;
    s16 stride;
    u16 height = 12;
    s16 glyphStride = 5;
    s16 i;
    s16 j;
    u8 background;
    u8 backgroundHigh;

    func_8005DD14_main(winId);
    if (y < 0) {
        y = 0;
    }
    if (x < 0) {
        x = 0;
    }
    pixelData = func_8005DAA4_main(winId);
    glyph = (u8 *)D_800D1FE4_main + D_800D1FE4_main->glyphOffset;
    glyph += (character - 0x30) * 60;
    width = 10;
    if (gLanguageIndex != LANGUAGE_JAPANESE && !(window->attr & 0x80000)) {
        width = D_800A2194_main[character];
    }
    window->unk_34 = width;
    if (((window->attr >> 2) & 1) & (character != 0x80)) {
        if ((character != 0x81) & (color == 0)) {
            func_8005D83C_main(winId, x - 1, y - 2, width + ((u8)window->spacing_x + 3), 14);
        }
    }
    pixels = pixelData;
    pixels += (x + y * window->unk44) / 2;
    stride = window->unk44 / 2;
    background = window->mess_shadow_color + 1;
    backgroundHigh = background << 4;
    color++;
    if (x & 1) {
        for (i = 0; i < height; i++) {
            for (j = 0; j < width / 2; j++, glyph++) {
                if ((*glyph & 0xF0) == 0xF0) {
                    pixels[j] = (pixels[j] & 0xF0) | color;
                } else if ((pixels[j] & 0xF) != 1 && (pixels[j] & 0xF) != background) {
                    if (((*glyph & 0xF0) != 0) & (color != 1)) {
                        pixels[j] = (pixels[j] & 0xF0) | (color + 7);
                    }
                }
                if ((*glyph & 0xF) == 0xF) {
                    (pixels + j)[1] = ((pixels + j)[1] & 0xF) | (color << 4);
                } else if (((pixels + j)[1] & 0xF0) != 0x10 && ((pixels + j)[1] & 0xF0) != backgroundHigh) {
                    if (((*glyph & 0xF) != 0) & (color != 1)) {
                        (pixels + j)[1] = ((pixels + j)[1] & 0xF) | ((color + 7) << 4);
                    }
                }
            }
            glyph += glyphStride - j;
            pixels += stride;
        }
    } else {
        width >>= 1;
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                if ((*glyph & 0xF0) == 0xF0) {
                    *pixels = (*pixels & 0xF) | (color << 4);
                } else if ((*pixels & 0xF0) != 0x10 && (*pixels & 0xF0) != backgroundHigh) {
                    if (((*glyph & 0xF0) != 0) & (color != 1)) {
                        *pixels = (*pixels & 0xF) | ((color + 7) << 4);
                    }
                }
                if ((*glyph & 0xF) == 0xF) {
                    *pixels = (*pixels & 0xF0) | color;
                } else if ((*pixels & 0xF) != 1 && (*pixels & 0xF) != background) {
                    if (((*glyph & 0xF) != 0) & (color != 1)) {
                        *pixels = (*pixels & 0xF0) | (color + 7);
                    }
                }
                glyph++;
                pixels++;
            }
            glyph += glyphStride - j;
            pixels += stride - j;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/window", func_8005D30C_main);
#endif

void func_8005D83C_main(s16 winId, s16 x, s16 y, s16 width, s16 height) {
    TextWindow *window = &winData[winId];
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
    TextWindow *window = &winData[winId];
    s16 group = window->group;
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
            sprite->unk_84->unk00[i].unk06 = window->h;
            sprite->unk_84->unk00[i].unk00 = window->unk_E0[i] = HuMemAlloc(width * height / 2);
            memset(window->unk_E0[i], 0, width * height / 2);
        }
        HuMemFree(sprite->unk_84->unk0C);
        sprite->unk_84->unk0C = HuMemAlloc(0x20);
        bcopy(window, sprite->unk_84->unk0C, 0x20);
        if (!(window->attr & 8)) {
            HuSprAttrReset(group, 1, 0x8000);
        }
    }
    return sprite->unk_84->unk00[window->unk_24].unk00;
}

void func_8005DC94_main(s16 winId) {
    TextWindow *window = &winData[winId];

    func_80054FF8_main(window->group, 1, window->unk_24);
    window->unk_24++;
    if (window->unk_24 >= 3) {
        window->unk_24 = 0;
    }
    window->attr &= ~0x100;
}

void func_8005DD14_main(s16 winId) {
    func_8005DD54_main(&winData[winId]);
}

void func_8005DD54_main(TextWindow *window) {
    u8 prevBuf;

    if (window->unk_24 == 0) {
        prevBuf = 2;
    } else {
        prevBuf = window->unk_24 - 1;
    }

    if (window->attr & 0x100) {
        return;
    }
    window->attr |= 0x100;

    if (window->unk_E0[0] != NULL) {
        bcopy(window->unk_E0[prevBuf], window->unk_E0[window->unk_24], (window->unk44 * window->unk46) / 2);
    }
}

void HuWinProc(void) {
    TextWindow *window;
    s32 input;
    s16 winId;

    while (1) {
        HuPrcVSleep();
        winId = winData[0].unk64;
        while (winData[winId].unk64 != -1) {
            window = &winData[winId];
            if ((window->attr & 0x400) ||
                ((!D_800CB99C_main || (window->attr & 0x40)) &&
                 (omPauseChk() + D_800D6A90_main != 0))) {
                if (window->attr & 0x100) {
                    func_8005DC94_main(winId);
                }
                winId = winData[winId].unk64;
                continue;
            }
            window->attr &= ~0x200;
            switch ((u8)window->stat) {
                case 1:
                    HuWinDrawMes(winId);
                    break;
                case 2:
                case 6:
                    if (!(window->attr & 0x10) || (u8)window->stat == 6) {
                        input = HuWinActivePadGet(window);
                        if ((input & 0xC000) || (input & (u16)window->push_key)) {
                            if (window->unk_AA != -1) {
                                HuAudFXPlay(window->unk_AA);
                            }
                            if ((u8)window->stat == 6) {
                                HuWinHomeClear(winId);
                            }
                            window->stat = 1;
                            window->attr |= 0x200;
                            window->input = input;
                            func_8005CF94_main(winId);
                        }
                    }
                    break;
                case 5:
                    if (HuWinChoice(winId) == 0) {
                        window->stat = 0;
                    }
                    break;
            }
            if (window->attr & 0x100) {
                func_8005DC94_main(winId);
            }
            func_8005EEE4_main(window, &window->choice_data[window->choice]);
            winId = winData[winId].unk64;
        }
    }
}

s16 HuWinStatGet(s16 winId) {
    s16 status = 0;
    s16 i;

    if (winId != -1) {
        return (u8)winData[winId].stat;
    }
    for (i = winData[0].unk64; winData[i].unk64 != -1; i = winData[i].unk64) {
        status |= (u8)winData[i].stat;
    }
    return status;
}

void func_8005E1A8_main(s16 winId, s16 arg1) {
    winData[winId].tab_w = arg1;
}

s32 HuWinChoiceGet(s16 winId, s16 arg1, s32 arg2) {
    TextWindow *window = &winData[winId];
    void *data;

    if (window->num_choices == 0) {
        return -1;
    }
    if (window->cursor_sprite == -1) {
        data = DataRead(0x00000030);
        window->cursor_sprite = HuSprAnimRead(data);
        HuMemMemoryFreePerm(data);
        func_80055024_main(window->group, 2, window->cursor_sprite, 0);
        HuSprTPLvlSet(window->group, 2, 0x100);
        HuSprAttrReset(window->group, 2, 0xFFFF);
        HuSprAttrSet(window->group, 2, 0x1009000);
        HuSprPriSet(window->group, 2, window->prio - 1);
    }
    if (arg2 != 0) {
        window->attr |= 1;
    }
    window->choice = arg1;
    window->stat = 5;
    window->unk_9A = 1;
    window->unk_A4 = 0;
    while (HuWinStatGet(winId) == 5) {
        HuPrcVSleep();
    }
    return window->choice;
}

#ifdef NON_MATCHING
/*
 * Remaining diff: `sprite` is allocated to v1 instead of a0 (6 instructions).
 * The do/while blocks give the CSE block boundary the target needs, so the
 * cursor target index is recomputed from `selected` instead of reusing the
 * compare's sign extension. An empty `if` there has the same effect.
 * `sprite` has two deaths, so global-alloc places it. It only conflicts with
 * `window`, `selected` and `input`, which all cross calls and so cannot exclude
 * v1. The original likely has another pseudo live across this block (or an a0
 * preference) that is not yet understood.
 */
s32 HuWinChoice(s16 winId) {
    TextWindow *window = &winData[winId];
    TextWindowSprite *sprite;
    s16 current = window->choice;
    s16 selected = current;
    s16 direction = -1;
    s16 input;
    s16 x;
    s16 y;
    s16 count;
    s16 i;
    s16 edge;
    s16 delta;
    s16 square;
    f32 bestX;
    f32 bestY;

    if (window->unk_9A != 3) {
        input = HuWinActivePadGet(window);
    } else {
        input = 0;
    }
    if (input & 0x200) {
        direction = 0;
    }
    if (input & 0x100) {
        direction = 2;
    }
    if (input & 0x800) {
        direction = 1;
    }
    if (input & 0x400) {
        direction = 3;
    }
    x = window->choice_data[current].x;
    y = window->choice_data[current].y;
    bestX = bestY = 100000.0f;
    count = window->num_choices;
    switch (direction) {
        case 0:
            for (i = 0; i < count; i++) {
                if (i != current && window->choice_data[i].y == y && window->choice_data[i].x < x) {
                    break;
                }
            }
            if (i != count) {
                for (i = 0; i < count; i++) {
                    if (i != current && window->choice_data[i].y == y && window->choice_data[i].x < x) {
                        if (x - window->choice_data[i].x < bestY) {
                            bestY = x - window->choice_data[i].x;
                            selected = i;
                        }
                    }
                }
            } else {
                edge = -1000;
                for (i = 0; i < count; i++) {
                    if (i != current && window->choice_data[i].y == y && window->choice_data[i].x > edge) {
                        edge = window->choice_data[i].x;
                        selected = i;
                    }
                }
            }
            break;
        case 1:
            for (i = 0; i < count; i++) {
                if (i != current && window->choice_data[i].y < y) {
                    break;
                }
            }
            if (i != count) {
                for (i = 0; i < count; i++) {
                    if (i != current && window->choice_data[i].y < y) {
                        delta = y - window->choice_data[i].y;
                        if (delta <= bestY) {
                            if (delta < bestY) {
                                bestX = 100000.0f;
                            }
                            square = x - window->choice_data[i].x;
                            square *= square;
                            if (square < bestX) {
                                bestY = delta;
                                bestX = square;
                                selected = i;
                            }
                        }
                    }
                }
            } else {
                edge = -1000;
                for (i = 0; i < count; i++) {
                    if (i != current && window->choice_data[i].y > edge) {
                        edge = window->choice_data[i].y;
                    }
                }
                bestX = 100000.0f;
                for (i = 0; i < count; i++) {
                    if (i != current && window->choice_data[i].y == edge) {
                        square = x - window->choice_data[i].x;
                        square *= square;
                        if (square < bestX) {
                            bestX = square;
                            selected = i;
                        }
                    }
                }
            }
            break;
        case 2:
            for (i = 0; i < count; i++) {
                if (i != current && window->choice_data[i].y == y && window->choice_data[i].x > x) {
                    break;
                }
            }
            if (i != count) {
                for (i = 0; i < count; i++) {
                    if (i != current && window->choice_data[i].y == y && window->choice_data[i].x > x) {
                        if (window->choice_data[i].x - x < bestY) {
                            bestY = window->choice_data[i].x - x;
                            selected = i;
                        }
                    }
                }
            } else {
                edge = 1000;
                for (i = 0; i < count; i++) {
                    if (i != current && window->choice_data[i].y == y && window->choice_data[i].x < edge) {
                        edge = window->choice_data[i].x;
                        selected = i;
                    }
                }
            }
            break;
        case 3:
            for (i = 0; i < count; i++) {
                if (i != current && window->choice_data[i].y > y) {
                    break;
                }
            }
            if (i != count) {
                for (i = 0; i < count; i++) {
                    if (i != current && window->choice_data[i].y > y) {
                        delta = window->choice_data[i].y - y;
                        if (delta <= bestY) {
                            if (delta < bestY) {
                                bestX = 100000.0f;
                            }
                            square = x - window->choice_data[i].x;
                            square *= square;
                            if (square < bestX) {
                                bestY = delta;
                                bestX = square;
                                selected = i;
                            }
                        }
                    }
                }
            } else {
                edge = 1000;
                for (i = 0; i < count; i++) {
                    if (i != current && window->choice_data[i].y < edge) {
                        edge = window->choice_data[i].y;
                    }
                }
                bestX = 100000.0f;
                for (i = 0; i < count; i++) {
                    if (i != current && window->choice_data[i].y == edge) {
                        square = x - window->choice_data[i].x;
                        square *= square;
                        if (square < bestX) {
                            bestX = square;
                            selected = i;
                        }
                    }
                }
            }
            break;
    }
    if (window->choice != selected) {
        sprite = &window->choice_data[window->choice];
        window->choice = window->unk_32 = selected;
        window->unk_9A = 3;
        do {
            window->cursorStartX = sprite->x - 12;
            window->cursorStartY = sprite->y + 8;
        } while (0);
        do {
            sprite = &window->choice_data[selected];
            window->cursorTargetX = sprite->x - 12;
            window->cursorTargetY = sprite->y + 8;
        } while (0);
        window->unk_A4 = 0;
        if (window->attr & 0x20) {
            HuAudFXPlay(0);
        } else {
            HuAudFXPlay(1);
        }
    }
    i = window->attr & 1 ? 0 : 0x4000;
    if (input & 0x8000) {
        if (window->choice_data[window->choice].stat == 2) {
            if (window->unk_AA != -1) {
                if (window->attr & 0x20) {
                    HuAudFXPlay(0);
                } else {
                    HuAudFXPlay(5);
                }
            }
            return 1;
        }
        window->unk_9A = 4;
        window->unk_A4 = 0;
        if (window->unk_AA != -1) {
            if (window->attr & 0x20) {
                HuAudFXPlay(0);
            } else {
                HuAudFXPlay(3);
            }
        }
        window->attr |= 0x200;
        window->input = input;
        return 0;
    }
    if ((input & i) || (input & window->push_key)) {
        window->unk_9A = 0;
        window->unk_A4 = 0;
        window->choice = -1;
        if (input & i) {
            if (window->unk_AA != -1) {
                if (window->attr & 0x20) {
                    HuAudFXPlay(0);
                } else {
                    HuAudFXPlay(4);
                }
            }
        }
        window->attr |= 0x200;
        window->input = input;
        return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/window", HuWinChoice);
#endif

void func_8005EEE4_main(TextWindow *window, TextWindowSprite *sprite) {
    f32 dx;
    f32 dy;
    f32 scaleY;
    f32 x;
    f32 y;
    f32 scaleX;
    f32 distance;
    f32 stepX;
    f32 stepY;
    f32 spriteScaleX;
    f32 spriteScaleY;

    scaleX = scaleY = 1.0f;
    x = sprite->x - 12;
    y = sprite->y + 8;
    switch (window->unk_9A) {
        case 0:
            if (window->cursor_sprite != -1) {
                HuSprAttrSet(window->group, 2, 0x8000);
            }
            return;
        case 1:
            if (window->attr & 0x8000) {
                window->unk_A4 = 0;
                window->unk_9A = 2;
            } else {
                scaleX = scaleY = window->unk_A4 / 8.0f;
                if (++window->unk_A4 >= 8) {
                    window->unk_A4 = 0;
                    window->unk_9A = 2;
                }
            }
            break;
        case 3:
            window->unk_A4++;
            dx = window->cursorTargetX - window->cursorStartX;
            dy = window->cursorTargetY - window->cursorStartY;
            distance = HuSqrtf(dx * dx + dy * dy);
            stepX = dx / distance * 10.0f * window->unk_A4;
            stepY = dy / distance * 10.0f * window->unk_A4;
            dx = window->cursorStartX + stepX - window->cursorTargetX;
            dy = window->cursorStartY + stepY - window->cursorTargetY;
            if (dx * dx + dy * dy < 100.0f) {
                x = window->cursorTargetX;
                y = window->cursorTargetY;
                window->unk_A4 = 0;
                window->unk_9A = 2;
            } else {
                x = window->cursorStartX + stepX;
                y = window->cursorStartY + stepY;
            }
            break;
        case 2:
            window->unk_A4 += 10.0f;
            if (window->unk_A4 > 180) {
                window->unk_A4 = 0;
            }
            x += sindf(window->unk_A4) * 4.0f;
            break;
        case 4:
            if (window->attr & 0x8000) {
                scaleX = scaleY = 0.0f;
            } else if (window->unk_A4 >= 11) {
                scaleX = scaleY = 1.3333334f;
            } else {
                window->unk_A4++;
                scaleX = scaleY = window->unk_A4 / 30.0f + 1.0f;
            }
            break;
        case 5:
            if (--window->unk_A4 == 0) {
                window->unk_A4 = 0;
                window->unk_9A = 2;
            }
            break;
    }
    if ((scaleX == 0.0f) | (scaleY == 0.0f)) {
        HuSprAttrSet(window->group, 2, 0x8000);
    } else {
        dy = 0.8f;
        dx = scaleX * dy;
        spriteScaleX = window->scaleX;
        dy = scaleY * dy;
        spriteScaleY = window->scaleY;
        HuSprScaleSet(window->group, 2, dx * spriteScaleX, dy * spriteScaleY);
        HuSprPosSet(window->group, 2, dx = x / dx * window->scaleX, dy = y / dy * window->scaleY);
        if (!(window->attr & 8)) {
            HuSprAttrReset(window->group, 2, 0x8000);
        }
    }
}

void HuWinKill(s16 winId) {
    TextWindow *window = &winData[winId];
    s16 i;

    if (window->unk_D0 != NULL && window->unk_D4 != 0) {
        func_800365E8_main(window->unk_D0);
    }
    for (i = 0; i < 5; i++) {
        if (window->insert_mess[i] != NULL && window->usingStringIDBool[i] != 0) {
            func_800365E8_main(window->insert_mess[i]);
        }
    }
    HuSprGrpKill(window->group);
    HuSprKill(window->unk66);
    HuSprKill(window->unk68);
    for (i = 4; i < 12; i++) {
        if (window->sprite_id[i] != -1) {
            HuSprKill(HuWinSprIDGet(winId, i));
        }
    }
    if (window->cursor_sprite != -1) {
        HuSprKill(window->cursor_sprite);
    }
    window->unk5E = -1;
    winData[window->unk64].unk62 = window->unk62;
    winData[window->unk62].unk64 = window->unk64;
    winPrio += 0x20;
}

void HuWinAllKill(void) {
    s16 i;

    if (D_800A2150_main != 0) {
        for (i = winData[0].unk64; winData[i].unk64 != -1; i = winData[i].unk64) {
            HuWinKill(i);
        }
        DataCloseTemp(D_800D1FE4_main);
        DataCloseTemp(D_800D4084_main);
        DataCloseTemp(D_800CE2C4_main);
        HuMemMemoryFreeTemp(winData);
        omDelPrcObj(winProc);
        D_800A2150_main = 0;
        for (i = 0; i < ARRAY_COUNT(D_800BDA50_main); i++) {
            if (D_800BDA50_main[i] != -1) {
                HuSprKill(D_800BDA50_main[i]);
            }
        }
        HuSprKill(D_800BDA68_main);
    }
}

void HuWinComKeyWait(s16 up, s16 down, s16 left, s16 right, u8 frames) {
    _HuWinComKeySet(-(up == -1), -(down == -1), -(left == -1), -(right == -1), frames);
    _HuWinComKeySet(up, down, left, right, 1);
}

void HuWinComKeySet(s16 up, s16 down, s16 left, s16 right) {
    _HuWinComKeySet(up, down, left, right, 1);
}

void _HuWinComKeySet(s16 up, s16 down, s16 left, s16 right, s16 frames) {
    winComKeyBuf[comKeyIdx][0] = up;
    winComKeyBuf[comKeyIdx][1] = down;
    winComKeyBuf[comKeyIdx][2] = left;
    winComKeyBuf[comKeyIdx][3] = right;
    winComKeyBuf[comKeyIdx][WINDOW_INPUT_RECORD_FRAMES] = frames;
    comKeyIdx = (comKeyIdx + 1) & 0x1F;
}

void HuWinComKeyGet(s16 *inputs) {
    s16 i;

    if ((u8)comKeyIdxNow == comKeyIdx) {
        inputs[0] = inputs[1] = inputs[2] = inputs[3] = 0;
        return;
    }
    for (i = 0; i < MAXCONTROLLERS; i++) {
        inputs[i] = winComKeyBuf[(u8)comKeyIdxNow][i];
        if (inputs[i] == -1) {
            inputs[i] = D_800D0590_main[i];
        }
    }
    winComKeyBuf[(u8)comKeyIdxNow][WINDOW_INPUT_RECORD_FRAMES]--;
    if (winComKeyBuf[(u8)comKeyIdxNow][WINDOW_INPUT_RECORD_FRAMES] == 0) {
        comKeyIdxNow = (comKeyIdxNow + 1) & 0x1F;
    }
}

void HuWinComKeyReset(void) {
    comKeyIdx = 0;
    comKeyIdxNow = 0;
}

s32 HuWinActivePadGet(TextWindow *window) {
    s16 queuedInputs[4];
    s16 input = 0;

    if (window->attr & 2) {
        HuWinComKeyGet(queuedInputs);
    }
    if (window->active_pad & 1) {
        if (window->attr & 2) {
            input = queuedInputs[0] | input;
        } else {
            input |= (D_800D0590_main[0] & 0x3FFF) | (D_800C9520_main[0] & 0xC000);
        }
    }
    if (window->active_pad & 2) {
        if (window->attr & 2) {
            input = queuedInputs[1] | input;
        } else {
            input |= (D_800D0590_main[1] & 0x3FFF) | (D_800C9520_main[1] & 0xC000);
        }
    }
    if (window->active_pad & 4) {
        if (window->attr & 2) {
            input = queuedInputs[2] | input;
        } else {
            input |= (D_800D0590_main[2] & 0x3FFF) | (D_800C9520_main[2] & 0xC000);
        }
    }
    if (window->active_pad & 8) {
        if (window->attr & 2) {
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

void HuWinBGColSet(s16 winId, s32 red, s32 green, s32 blue) {
    TextWindow *window = &winData[winId];
    HuSprite *sprite;
    u16 *palette;
    s16 i;
    s16 r;
    s16 g;
    s16 b;
    u16 color;

    window->backgroundRed = red;
    window->backgroundGreen = green;
    window->backgroundBlue = blue;
    HuSprColorSet(window->group, 0, red, green, blue);
    sprite = HuSprGet(window->group, 1);
    for (i = 0; i < 7; i++) {
        color = D_800A2186_main[i];
        r = ((color >> 8) & 0xF8) * 0.3f + (u8)red * 0.7f;
        if (r >= 256) {
            r = 255;
        }
        g = ((color >> 3) & 0xF8) * 0.3f + (u8)green * 0.7f;
        if (g >= 256) {
            g = 255;
        }
        b = ((color << 2) & 0xF8) * 0.3f + (u8)blue * 0.7f;
        if (b >= 256) {
            b = 255;
        }
        window->palette[i + 9] = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1;
    }
    palette = HuMemAlloc(sizeof(window->palette));
    bcopy(window, palette, sizeof(window->palette));
    func_80019C00_main(sprite->unk_84->unk0C);
    sprite->unk_84->unk0C = palette;
}

void func_8005FE54_main(s16 winId, s16 arg1) {
    TextWindow *window = &winData[winId];

    window->active_pad = (window->active_pad & 0xF0) | arg1;
}

void HuWinDispOff(s16 winId) {
    TextWindow *window = &winData[winId];
    s16 i;

    HuSprAttrSet(window->group, 0, 0x8000);
    HuSprAttrSet(window->group, 1, 0x8000);
    for (i = 4; i < 22; i++) {
        if (window->sprite_id[i] != -1) {
            HuSprAttrSet(window->group, i, 0x8000);
        }
    }
    if (window->cursor_sprite != -1) {
        HuSprAttrSet(window->group, 2, 0x8000);
    }
    if (window->stat & 2) {
        HuSprAttrSet(window->group, 3, 0x8000);
    }
    func_8005B63C_main(winId, 0x4008, 8);
}

void HuWinDispOn(s16 winId) {
    TextWindow *window = &winData[winId];
    s16 i;

    HuSprAttrReset(window->group, 0, 0x8000);
    HuSprAttrReset(window->group, 1, 0x8000);
    for (i = 4; i < 22; i++) {
        if (window->sprite_id[i] != -1) {
            HuSprAttrReset(window->group, i, 0x8000);
        }
    }
    if (window->cursor_sprite != -1) {
        HuSprAttrReset(window->group, 2, 0x8000);
    }
    if (window->stat & 2) {
        HuSprAttrReset(window->group, 3, 0x8000);
    }
    func_8005B63C_main(winId, 0x4008, 0x4000);
}

void func_800600C0_main(s16 winId, s32 arg1) {
    TextWindow *window;

    window = &winData[winId];
    if (arg1 != 0) {
        window->attr |= 0x10;
    } else {
        window->attr &= ~0x10;
    }
}

// Sets an option disabled.
void HuWinChoiceDisable(s32 winId, s16 spriteIndex) {
    TextWindow *window = &winData[winId];

    window->choice_data[spriteIndex].stat = 2;
}

void func_80060144_main(s16 obj) {
#ifdef DEBUG

#endif
}

s16 func_8006014C_main(s32 winId) {
    return winData[winId].choice;
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
    TextWindow *window = &winData[winId];

    HuWinInsertMesSet(winId, arg1, arg2);
    func_80060174_main(window->insert_mess[arg2], window->insert_mess[arg2]);
}

// Called to indicate that `str` should be the replacement at a
// "replacement index" location in the main string.
void HuWinInsertMesSizeGet(u32 str, s16 index) {
    winInsertF = 1;
    winMaxHeight = 0;
    winMaxWidth = 0;
    GetMesMaxSizeSub(str);
    cancelCRF = 0;
    mesWInsert[index] = D_800BDA6D_main;
}

void func_80060290_main(u32 str, s16 index) {
    u8 *text;
    u8 allocated;

    winInsertF = 1;
    winMaxHeight = 0;
    winMaxWidth = 0;
    if (str > 0x80000000) {
        allocated = 0;
        text = (u8 *)str;
    } else {
        allocated = 1;
        text = func_800364DC_main((void *)str);
    }
    func_80060174_main(text, text);
    GetMesMaxSizeSub((u32)text);
    cancelCRF = 0;
    if (allocated) {
        func_800365E8_main(text);
    }
    mesWInsert[index] = D_800BDA6D_main;
}

void func_8006034C_main(s16 winId, s16 arg1, u8 arg2) {
    winData[winId].unk_B2[arg1] = arg2;
}

void func_80060388_main(s8 arg0) {
    winTabSize = arg0;
}

void HuWinMesMaxSizeGet(s16 count, s16 *size, ...) {
    va_list args;
    s16 i;

    winInsertF = 0;
    va_start(args, size);
    winMaxHeight = 0;
    winMaxWidth = 0;
    for (i = 0; i < count; i++) {
        GetMesMaxSizeSub(va_arg(args, u32));
    }
    va_end(args);
    for (i = 0; i < ARRAY_COUNT(mesWInsert); i++) {
        mesWInsert[i] = 0;
    }
    winTabSize = 0xC;
    size[0] = winMaxWidth + 10;
    size[1] = winMaxHeight + 6;
}

void HuWinMesMaxSizeBetGet(s16 *arg0, s16 arg1, s16 arg2) {
    u32 i;

    if (arg2 < arg1) {
        arg0[1] = 0x64;
        arg0[0] = 0x64;
        return;
    }

    winInsertF = 0;
    winMaxHeight = 0;
    winMaxWidth = 0;

    for (i = arg1; arg2 >= i; i++) {
        GetMesMaxSizeSub(i);
    }

    for (i = 0; i < ARRAY_COUNT(mesWInsert); i++) {
        mesWInsert[i] = 0;
    }

    winTabSize = 0xC;
    arg0[0] = winMaxWidth + 10;
    arg0[1] = winMaxHeight + 6;
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

// Measures a message or string, accounting for layout and replacement control codes.
void GetMesMaxSizeSub(u32 str) {
    u8 *text;
    u8 *allocatedText = NULL;
    u8 allocated;
    s16 width;
    s16 height;
    s16 advance;
    s16 heightAdvance;

    if (str > 0x80000000) {
        allocated = 0;
        text = (u8 *)str;
    } else {
        allocated = 1;
        allocatedText = func_800364DC_main((void *)str);
        text = allocatedText;
    }
    height = 14;
    width = 0;
    for (; *text != 0; text++) {
        heightAdvance = 0;
        if (gLanguageIndex == LANGUAGE_JAPANESE) {
            advance = (*text == 0x80 || *text == 0x81) ? 0 : 10;
        } else {
            advance = D_800A2194_main[*text];
        }
        if ((*text > 0) && (*text < 9)) {
            advance = 0;
        }
        switch (*text) {
            case 0x10:
            case 0x1A:
            case 0x20:
                advance = 10;
                if (gLanguageIndex != LANGUAGE_JAPANESE) {
                    advance = *text == 0x1A ? 10 : 4;
                }
                break;
            case 0x0A:
                if (cancelCRF != 0) {
                    advance = 0;
                } else {
                    if ((s16)winMaxWidth < width) {
                        winMaxWidth = width;
                    }
                    advance = 0;
                    width = 0;
                    if (text[1] != 0) {
                        heightAdvance = 14;
                    }
                }
                break;
            case 0x17:
                heightAdvance = 5;
                advance = 0;
                break;
            case 0x0C:
            case 0x0D:
            case 0x0F:
            case 0x16:
            case 0x19:
                advance = 0;
                break;
            case 0x0B:
                if (winInsertF == 0) {
                    if ((s16)winMaxWidth < width) {
                        winMaxWidth = width;
                    }
                    if ((s16)winMaxHeight < height) {
                        winMaxHeight = height;
                    }
                    height = 14;
                    heightAdvance = 0;
                    advance = 0;
                    width = 0;
                }
                break;
            case 0x0E:
                advance = ((width + (u8)winTabSize) / (u8)winTabSize) * (u8)winTabSize - width;
                break;
            case 0x18:
                text++;
                break;
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
                advance = mesWInsert[*text - 0x11];
                break;
        }
        width += advance;
        height += heightAdvance;
    }
    if ((s16)winMaxWidth < width) {
        winMaxWidth = width;
    }
    if ((s16)winMaxHeight < height) {
        winMaxHeight = height;
    }
    if (allocated) {
        func_800365E8_main(allocatedText);
    }
}

void HuWinMesSizeCancelCRSet() {
    cancelCRF = 1;
}

void HuWinPushKeySet(s32 winId, s16 arg1) {
    TextWindow *window;

    window = &winData[winId];
    window->push_key = arg1;
}

s32 func_80060880_main(s32 x, s32 y, s32 frameIndex) {
    s32 winId;
    s32 member;
    TextWindow *window;
    WindowFrameDefinition *frame;
    HuSprite *sprite;

    frame = &D_800A2384_main[frameIndex];
    winId = HuWinCreate(x, y, frame->width, frame->height, 0, 12);
    HuWinMesSpeedSet(winId, 0);
    HuWinMesPalSet(winId, 2, 255, 0, 0);
    HuWinMesPalSet(winId, 4, 70, 224, 70);
    HuWinMesPalSet(winId, 5, 0, 176, 192);
    HuWinMesPalSet(winId, 6, 255, 173, 0);
    window = &winData[winId];
    window->mess_x = window->mess_rect_x = frame->textX;
    window->mess_y = window->mess_rect_y = frame->textY;
    window->mess_rect_w = frame->textWidth;
    window->mess_rect_h = frame->textHeight;
    func_8005BCA4_main(winId, frame->spriteWidth, frame->spriteHeight);
    window->unk58 = window->mess_x + frame->textWidth - window->unk_27;
    window->unk5A = window->mess_y + frame->textHeight - window->unk_28;
    window->mess_shadow_color = 7;
    HuWinMesPalSet(winId, 7, 64, 64, 64);
    if (frameIndex == 5) {
        window->spacing_x = 0;
    }
    member = HuWinAnimSet(winId, frame->file, 0, 0, 0);
    window->unk274 = member;
    HuSprPriSet(window->group, member, 15000);
    HuSprPosSet(window->group, member, 0, 0);
    HuSprScaleSet(window->group, member, 0, 0);
    HuSprAttrSet(window->group, member, frame->attributes);
    sprite = HuSprGet(window->group, member);
    sprite->unk_84->unk00->unk08 = frame->spriteWidth;
    sprite->unk_84->unk00->unk0A = frame->spriteHeight;
    if (frame->shadowFile != 0) {
        member = HuWinAnimSet(winId, frame->shadowFile, 0, 0, 0);
        window->unk276 = member;
        HuSprTPLvlSet(window->group, member, 255);
        HuSprPriSet(window->group, member, 15001);
        HuSprPosSet(window->group, member, 0, 0);
        HuSprScaleSet(window->group, member, 0, 0);
        HuSprColorSet(window->group, member, 27, 27, 255);
        HuSprAttrSet(window->group, member, frame->attributes | 0x1000);
        sprite = HuSprGet(window->group, member);
        sprite->unk_84->unk00->unk08 = frame->spriteWidth;
        sprite->unk_84->unk00->unk0A = frame->spriteHeight;
    } else {
        window->unk276 = 0;
    }
    window->attr |= 0x2000;
    HuWinBGTPLvlSet(winId, 0);
    func_8005C154_main(winId, 192, 192, 192);
    HuWinMesColSet(winId, frame->speed);
    HuWinBGColSet(winId, 255, 255, 255);
    HuWinScaleSet(winId, 0, 0);
    return winId;
}

void func_80060C14_main(s32 winId, s32 playSound) {
    TextWindow *window = &winData[winId];
    s16 i;
    f32 scale;

    if (!(window->attr & 0x4000)) {
        func_800600C0_main(winId, 1);
        if (playSound) {
            if (window->attr & 0x20) {
                HuAudFXPlay(0);
            } else {
                HuAudFXPlay(0x11D);
            }
        }
        for (i = 0; i < 10; i++) {
            scale = sindf(i * 10.0f) * ((f32)(window->w + 4) / window->w);
            HuSprScaleSet(window->group, window->unk274, scale, scale);
            HuWinScaleSet(winId, scale, scale);
            if (window->unk276 != 0) {
                HuSprScaleSet(window->group, window->unk276, scale, scale);
            }
            HuPrcVSleep();
        }
        HuSprScaleSet(window->group, window->unk274, 1.0f, 1.0f);
        if (window->unk276 != 0) {
            HuSprScaleSet(window->group, window->unk276, 1.0f, 1.0f);
        }
        HuWinScaleSet(winId, 1.0f, 1.0f);
        func_800600C0_main(winId, 0);
        func_8005B63C_main(winId, 0x4000, 0x4000);
        HuPrcVSleep();
    }
}

void func_80060DEC_main(s32 win_id) {
    TextWindow *window = &winData[win_id];

    func_800600C0_main(win_id, 1);
    HuSprScaleSet(window->group, window->unk274, 1.0f, 1.0f);
    if (window->unk276 != 0) {
        HuSprScaleSet(window->group, window->unk276, 1.0f, 1.0f);
    }
    HuWinScaleSet(win_id, 1.0f, 1.0f);
    func_800600C0_main(win_id, 0);
    func_8005B63C_main(win_id, 0x4000, 0x4000);
}

void func_80060EA8_main(s32 winId, s32 playSound) {
    TextWindow *window = &winData[winId];
    f32 scale = 1.0f;

    if (window->attr & 0x4000) {
        func_800600C0_main(winId, 1);
        if (playSound) {
            if (window->attr & 0x20) {
                HuAudFXPlay(0);
            } else {
                HuAudFXPlay(0x137);
            }
        }
        while (scale > 0.0f) {
            HuSprScaleSet(window->group, window->unk274, scale, scale);
            if (window->unk276 != 0) {
                HuSprScaleSet(window->group, window->unk276, scale, scale);
            }
            HuWinScaleSet(winId, scale, scale);
            scale -= 0.1f;
            HuPrcVSleep();
        }
        HuSprScaleSet(window->group, window->unk274, scale, scale);
        if (window->unk276 != 0) {
            HuSprScaleSet(window->group, window->unk276, scale, scale);
        }
        HuWinScaleSet(winId, scale, scale);
        func_800600C0_main(winId, 0);
        func_8005B63C_main(winId, 0x4000, 0);
    }
}

void func_8006105C_main(s32 winId, s32 alpha) {
    TextWindow *window = &winData[winId];

    HuSprAttrSet(window->group, window->unk274, 0x1000);
    alpha &= 0xFF;
    HuSprTPLvlSet(window->group, window->unk274, alpha);
    if (window->unk276 != 0) {
        HuSprTPLvlSet(window->group, window->unk276, alpha);
    }
}

void HuWinExCleanup(s16 win_id) {
    HuWinKill(win_id);
}

void func_80061100_main(s16 win_id, s32 priority) {
    TextWindow *window = &winData[win_id];

    HuWinPriSet(win_id, (s16)priority);
    HuSprPriSet(window->group, window->unk274, priority + 1);
    if (window->unk276 != 0) {
        HuSprPriSet(window->group, window->unk276, priority + 2);
    }
}

// Obtains a window handle
s32 HuWinExCreate(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5) {
    TextWindow *temp_s2;
    s32 temp_v0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s0 = arg3 + 2;

    if ((arg0 != -1) & (arg4 < 0x30)) {
        arg4 = 0x30;
    }

    temp_v0 = HuWinCreate(arg1, arg2, temp_s0, arg4, 0, arg5);
    HuWinMesSpeedSet(temp_v0, 0);
    temp_s2 = &winData[temp_v0];
    func_8005BCA4_main(temp_v0, temp_s0 / 2, arg4 / 2);
    HuWinPosSet(temp_v0, (temp_s2->pos_x + temp_s0 / 2), (temp_s2->pos_y + arg4 / 2));
    temp_s2->unk276 = arg0;

    if (arg0 != -1) {
        temp_s2->unk274 = HuWinAnimSet(temp_v0, D_800A25D0_main[arg0], (0x18 - temp_s2->unk48), (0x18 - temp_s2->unk4A), 0);
    }

    temp_s2->mess_x = 6;
    temp_s2->mess_rect_x = 6;
    HuWinBGTPLvlSet(temp_v0, 0xD0);
    HuWinMesPalSet(temp_v0, 1, 0x40, 0xF0, 0xFF);
    HuWinBGColSet(temp_v0, 0x40, 0x20, 0xB0);
    HuWinHomeClear(temp_v0);
    HuWinDispOff(temp_v0);
    HuWinComKeyReset();
    return temp_v0;
}

void HuWinExAnimIn(s16 winId) {
    TextWindow *window = &winData[winId];
    s16 i;

    func_800600C0_main(winId, 1);
    if (window->unk276 != -1) {
        HuSprScaleSet(window->group, window->unk274, 0.0f, 0.0f);
    }
    HuWinDispOn(winId);
    for (i = 1; i < 6; i++) {
        func_8005BBC0_main(winId, 1.0f - cosdf(i * 18.0f), 2.0f / window->h);
        HuPrcVSleep();
    }
    for (i = 1; i < 4; i++) {
        func_8005BBC0_main(winId, 1.0f, sindf(i * 30.0f) * 1.05f);
        HuPrcVSleep();
    }
    func_8005BBC0_main(winId, 1.0f, 1.0f);
    if (window->unk276 != -1) {
        HuSprPosSet(window->group, window->unk274, 0x18 - window->unk48, 0x18 - window->unk4A);
        HuSprScaleSet(window->group, window->unk274, 1.0f, 1.0f);
        func_800615B8_main(winId, 1);
    }
    func_800600C0_main(winId, 0);
}

void func_800615B8_main(s16 winId, s32 opening) {
    u8 *buffers[3];
    TextWindow *window = &winData[winId];
    HuSprite *sprite;
    u8 *original;
    u8 *source;
    u8 transparent;
    u8 *dest;
    s16 i;
    s16 x;
    s16 y;
    s16 dx;
    s16 dy;
    s16 frames;
    f32 radius;

    sprite = HuSprGet(window->group, window->unk274);
    original = sprite->unk_84->unk00->unk00;
    for (i = 0; i < 3; i++) {
        buffers[i] = HuMemAllocTag(0x640, 0x7918);
        memset(buffers[i], 0, 0x640);
    }
    source = sprite->unk_84->unk0C;
    source++;
    for (transparent = 0; transparent < sprite->unk_84->unk1A; transparent++, source += 2) {
        if (!(*source & 1)) {
            break;
        }
    }
    frames = opening ? 6 : 3;
    for (i = 1; i <= frames; i++) {
        source = original;
        dest = buffers[D_800D2008_main];
        radius = HuSqrtf(1800.0f);
        radius *= 1.0f - cosdf((90.0f / frames) * i);
        for (y = 0; y < 40; y++) {
            for (x = 0; x < 40; x++, dest++) {
                if (opening) {
                    dx = x - 10;
                    dy = y - 10;
                    if (dx * dx + dy * dy < radius * radius) {
                        *dest = (source + y * 40)[x];
                    } else {
                        *dest = transparent;
                    }
                } else {
                    dx = x - 30;
                    dy = y - 30;
                    if (dx * dx + dy * dy < radius * radius) {
                        *dest = transparent;
                    } else {
                        *dest = (source + y * 40)[x];
                    }
                }
            }
        }
        sprite->unk_84->unk00->unk00 = buffers[D_800D2008_main];
        HuPrcVSleep();
    }
    for (i = 0; i < 3; i++) {
        func_80019C00_main(buffers[i]);
    }
    sprite->unk_84->unk00->unk00 = original;
}

void HuWinExAnimPopIn(s16 winId, s16 arg1) {
    s16 temp_v0;
    TextWindow *temp_s0;

    temp_s0 = &winData[winId];
    func_800600C0_main(winId, 1);
    func_800615B8_main(winId, 0);
    HuWinSprKill(winId, temp_s0->unk274);
    temp_v0 = HuWinAnimSet(winId, D_800A25D0_main[arg1], 0x18 - temp_s0->unk48, 0x18 - temp_s0->unk4A, 0);
    temp_s0->unk274 = temp_v0;
    HuSprPosSet(temp_s0->group, temp_v0, 0x18 - temp_s0->unk48, 0x18 - temp_s0->unk4A);
    HuSprScaleSet(temp_s0->group, temp_s0->unk274, 1.0f, 1.0f);
    func_800615B8_main(winId, 1);
    func_800600C0_main(winId, 0);
}

void HuWinExAnimOut(s16 arg0, s16 arg1) {
    s16 i;

    if (arg1 == 0) {
        HuWinHomeClear(arg0);

        for (i = 0; i < 5; i++) {
            HuWinScaleSet(arg0, 1.0f, 1.0f - sindf(i * 18.0f));
            HuPrcVSleep();
        }

        HuWinDispOff(arg0);
        HuPrcVSleep();
        return;
    }
    HuWinDispOff(arg0);
}
