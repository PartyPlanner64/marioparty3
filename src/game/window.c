#include "game/window.h"
#include "game/sprite.h"
#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "include_asm.h"
#include "game/gamework_data.h"
#include "enums.h"
#include "game/data.h"
#include "game/messdata.h"
#include "ld_addrs.h"
#include "game/pause.h"
#include "macros.h"
#include "game/audio.h"
#include "game/malloc.h"
#include "game/mallocblock.h"
#include "game/input.h"
#include "stdarg.h"
#include "gcc/memory.h"

#define HUWIN_CURSOR_POS(posX, posY, sprite) \
    do {                                     \
        (posX) = (sprite)->x - 12;           \
        (posY) = (sprite)->y + 8;            \
    } while (0)

typedef struct WindowIconDefinition {
    u32 highlightedFile;
    u32 file;
    u8 bank;
    u8 width;
} WindowIconDefinition; // Size 0xC

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
} WindowFrameDefinition; // Size 0x1C

extern s32 winLastAdvance;
extern u8 omAllPauseF;
u8 winInitF = 0;
u8 gLanguageIndex = 2;
static u8 winBGColTbl[] = {
    0x40, 0x20, 0xB0, 0x00, 0x00, 0x00, 0x20, 0x0E, 0x71, 0xFF, 0x3C, 0x52, 0xFF, 0x00, 0xFF, 0x50,
    0xFF, 0x50, 0x00, 0x3E, 0xF9, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x80, 0xFF, 0x80, 0x00, 0x00,
};
static u16 winPalTbl[] = {
    0x0000, 0x0001, 0x003F, 0xFA11, 0xF83F, 0x07C1, 0x07FF, 0xFFC1,
    0xFFFF, 0x0021, 0x8109, 0x8021, 0x0401, 0x0421, 0x8401, 0x8421,
};
u8 winFontWidthTbl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    4, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 10, 10, 6, 6, 6, 6,
    4, 6, 6, 6, 6, 6, 6, 6, 6, 4, 6, 6, 6, 8, 8, 6,
    6, 8, 6, 6, 6, 6, 6, 8, 8, 6, 6, 6, 2, 4, 4, 6,
    10, 6, 6, 6, 6, 6, 4, 6, 6, 2, 4, 6, 2, 8, 6, 6,
    6, 6, 6, 6, 4, 6, 6, 8, 6, 6, 6, 2, 6, 4, 8, 10,
    4, 4, 4, 4, 10, 4, 6, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 6, 6, 6, 6, 8,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    6, 6, 4, 6, 8, 8, 6, 4, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 6, 6, 6, 6, 6,
    6, 4, 4, 6, 6, 6, 6, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 8, 10,
};
static WindowIconDefinition winSpcFontTbl[] = {
    { 0x34, 0x34, 0, 10 },
    { 0x34, 0x34, 1, 10 },
    { 0x34, 0x34, 2, 10 },
    { 0x34, 0x34, 3, 10 },
    { 0x34, 0x34, 4, 10 },
    { 0x34, 0x34, 5, 10 },
    { 0x34, 0x34, 6, 10 },
    { 0x34, 0x34, 7, 10 },
    { 0x34, 0x34, 8, 10 },
    { 0x34, 0x34, 9, 10 },
    { 0x34, 0x34, 10, 10 },
    { 0x34, 0x34, 11, 10 },
};
static u8 winBGEdgeTbl[] = { 0x00, 0x44, 0x04, 0x77, 0x47, 0xCF, 0x47, 0xFF };
// 零一二三四五六七八九
static u8 winKanjiNumTbl[] = "\x97\xEB\x88\xEA\x93\xF1\x8E\x4F\x8E\x6C\x8C\xDC\x98\x5A\x8E\xB5\x94\xAA\x8B\xE3";
extern u8 *winKanjiNumAltTbl[];
static s16 winSpcFontAnim[12];
static s16 winKeyWaitAnim;
static u8 winInsertF;
static u16 winMaxWidth;
static u16 winMaxHeight;
extern u8 cancelCRF;
extern void *winCursorData;
extern Process *winProc;
extern u8 comKeyIdx;
extern u8 Hu3DBufNo;
extern WindowFont *winFontData;
extern void *winFrameData;
extern u8 mesWInsert[5];
extern s8 winTabSize;
extern s8 comKeyIdxNow;
extern s16 winPrio;
extern u8 mesWInsert[5];
extern s8 winTabSize;

void HuWinInit(void) {
    Process *temp_v0_4;
    void *temp_v0_6;
    s16 i;

    if (winInitF == 0) {
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
            winFontData = DataReadTemp(0x0000002B);
            MessDataSet((u32)strings_japanese_ROM_START);
        } else {
            winFontData = DataReadTemp(0x0000002C);
            switch (gLanguageIndex) {
                case LANGUAGE_ENGLISH:
                    MessDataSet((u32)strings_english_ROM_START);
                    break;
                case LANGUAGE_FRENCH:
                    MessDataSet((u32)strings_french_ROM_START);
                    break;
                case LANGUAGE_GERMAN:
                    MessDataSet((u32)strings_german_ROM_START);
                    break;
                case LANGUAGE_SPANISH:
                    MessDataSet((u32)strings_spanish_ROM_START);
                    break;
                case LANGUAGE_ITALIAN:
                    MessDataSet((u32)strings_italian_ROM_START);
                    break;
            }
        }

        temp_v0_4 = omAddPrcObj(HuWinProc, 0x1001, 0x800, 0);
        winProc = temp_v0_4;
        omPrcSetStatBit(temp_v0_4, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);

        winInitF = 1;
        winPauseF = 0;
        winFrameData = DataReadTemp(0x00000029);
        winCursorData = DataReadTemp(0x0000002A);

        for (i = 0; i < ARRAY_COUNT(winSpcFontAnim); i++) {
            winSpcFontAnim[i] = -1;
        }

        temp_v0_6 = DataRead(0x00000033);
        winKeyWaitAnim = HuSprAnimRead(temp_v0_6);
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
    window->stat = HUWIN_STAT_NONE;
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
    window->backgroundRed = winBGColTbl[0];
    window->backgroundGreen = winBGColTbl[1];
    window->backgroundBlue = winBGColTbl[2];
    window->active_pad = HUWIN_PLAYER_ALL;
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
    window->unk66 = HuSprAnimRead(winFrameData);
    window->unk68 = HuSprAnimRead(winCursorData);
    group = HuSprGrpCreate(22, 5);
    window->group = group;
    HuSprTPLvlSet(group, 0, 0x100);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 0x1009000);
    HuSprGrpMemberSet(group, 0, window->unk66, 0);
    HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_STOP);
    HuSprParentSet(group, 0, -1);
    HuSprPosSet(group, 0, window->pos_x, window->pos_y);
    HuSprColorSet(window->group, 0, 64, 32, 176);
    sprite = HuSprGet(group, 0);
    if (!(flags & 8)) {
        sprite->data->pat->sizeX = width;
        sprite->data->pat->sizeY = height;
        HuMemFree(sprite->data->pat->data);
        pixelWidth = width;
        pixelHeight = height;
        size = pixelWidth * pixelHeight / 2;
        sprite->data->pat->data = window->pixels = HuMemAlloc(size);
        memset(window->pixels, 0xFF, size);
        if (!(flags & 1)) {
            if (flags & 16) {
                winBGCornerMake(window->pixels, pixelWidth, pixelHeight);
            } else {
                winBGMake(window->pixels, width, height);
            }
        }
        HuSprTPLvlSet(group, 0, 100);
        HuSprDispOn(group, 0);
        HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_STOP);
    } else {
        HuSprTPLvlSet(group, 0, 0);
        HuSprDispOff(group, 0);
        HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_STOP);
    }
    HuSprTPLvlSet(group, 1, 0x100);
    HuSprAttrReset(group, 1, 0xFFFF);
    HuSprAttrSet(group, 1, 0x1009000);
    HuSprGrpMemberSet(group, 1, window->unk68, 0);
    HuSprAnimModeSet(group, 1, HUSPR_ANIM_MODE_STOP);
    HuSprPosSet(group, 1, 0, 0);
    HuSprParentSet(group, 1, 0);
    bcopy(winPalTbl, window, 32);
    for (i = 0; i < 22; i++) {
        HuSprPriSet(group, i, winPrio);
    }
    HuSprPriSet(group, 2, winPrio - 1);
    window->prio = winPrio;
    winPrio -= 32;
    window->unk_AA = 312;
    return winId;
}

void winBGMake(u8 *pixels, s16 width, s16 height) {
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
        pixels[y * stride] = winBGEdgeTbl[(s16)(y * 2)];
        pixels[y * stride + 1] = winBGEdgeTbl[(s16)(y * 2) + 1];
        pixels[(height - y - 1) * stride] = winBGEdgeTbl[(s16)(y * 2)];
        pixels[(height - y - 1) * stride + 1] = winBGEdgeTbl[(s16)(y * 2) + 1];
        left = (winBGEdgeTbl[(s16)(y * 2)] >> 4) | (winBGEdgeTbl[(s16)(y * 2)] << 4);
        right = (winBGEdgeTbl[(s16)(y * 2) + 1] >> 4) | (winBGEdgeTbl[(s16)(y * 2) + 1] << 4);
        pixels[y * stride + stride - 2] = right;
        pixels[y * stride + stride - 1] = left;
        pixels[(height - y - 1) * stride + stride - 2] = right;
        pixels[(height - y - 1) * stride + stride - 1] = left;
    }
}

void winBGCornerMake(u8 *pixels, s16 width, s16 height) {
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
        MessDataMesFree(window->unk_D0);
    }
    if ((u8)window->stat == HUWIN_STAT_KEYWAIT) {
        HuWinKeyWaitIconOff(winId);
    }
    window->mess_time = 1;
    if (0x80000000 < message) {
        window->unk_D4 = 0;
        window->mess = (u8 *)message;
    } else {
        window->unk_D4 = 1;
        window->unk_D0 = MessDataMesGet((void *)message);
        window->mess = window->unk_D0;
    }
    if (x >= 0) {
        window->mess_x = x;
    } else if (x == HUWIN_POS_CENTER) {
        if (window->attr & HUWIN_ATTR_NOCR) {
            HuWinMesSizeCancelCRSet();
        }
        width = HuWinMesWidthGet((s32)window->mess);
        cancelCRF = 0;
        window->mess_x = (window->w - width) / 2;
        window->attr |= HUWIN_ATTR_ALIGN_CENTER;
    }
    if (y >= 0) {
        window->mess_y = y;
    } else if (y == HUWIN_POS_CENTER) {
        window->mess_y = (window->h - 12) / 2;
        window->attr |= HUWIN_ATTR_VALIGN_CENTER;
    }
    window->stat = HUWIN_STAT_DRAWMES;
    window->num_choices = 0;
}

s16 HuWinStrLen(u8 *str) {
    s16 len = 0;

    while (*str != 0) {
        str++;
        len++;
    }
    return len;
}

s16 HuWinMesWidthGet(s32 arg0) {
    s16 size[2];

    HuWinMesMaxSizeGet(1, size, arg0);
    return size[0];
}

void HuWinAttrSet(s16 winId, s32 arg1, s32 arg2) {
    TextWindow *window = &winData[winId];

    window->attr = arg2 | (window->attr & ~arg1);
    if (arg2 & HUWIN_ATTR_MUTE) {
        window->unk_AA = 0;
    }
}

s32 HuWinAttrGet(s16 win_id) {
    return winData[win_id].attr;
}

void HuWinInsertMesSet(s16 win_id, u32 arg1, s8 arg2) {
    TextWindow *textWindow = &winData[win_id];

    if (textWindow->insert_mess[arg2] != 0) {
        if (textWindow->usingStringIDBool[arg2] != 0) {
            MessDataMesFree(textWindow->insert_mess[arg2]);
        }
    }
    // pointer check
    if (0x80000000 < arg1) {
        textWindow->usingStringIDBool[arg2] = 0;
        textWindow->insert_mess[arg2] = (char *)arg1;
    } else {
        textWindow->usingStringIDBool[arg2] = 1;
        textWindow->insert_mess[arg2] = MessDataMesGet((void *)arg1);
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
    HuSprGrpMemberSet(window->group, i, spriteId, arg4);
    HuSprPosSet(window->group, i, arg2, arg3);
    HuSprParentSet(window->group, i, 0);
    return i;
}

void HuWinSprKill(s16 arg0, s16 arg1) {
    HuSprAnimKill(HuWinSprIDGet(arg0, arg1));
    winData[arg0].sprite_id[arg1] = -1;
}

s16 HuWinSprSet(s16 winId, u32 spriteMainFsPair, s16 x, s16 y, s16 arg4) {
    TextWindow *window = &winData[winId];
    TextWindowSprite *sprite;
    s16 spriteId;

    spriteId = HuWinAnimSet(winId, spriteMainFsPair, x, y, arg4);
    sprite = &window->choice_data[window->num_choices];
    sprite->x = x;
    sprite->y = y;
    sprite->unk_06 = 0;
    sprite->unk_08 = 0;
    sprite->stat = HUWIN_CHOICE_STAT_SPR;
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

void HuWinFrameScaleSet(s16 winId, f32 scaleX, f32 scaleY) {
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

void HuWinCenterPosSet(s16 arg0, s16 arg1, s16 arg2) {
    TextWindow *window = &winData[arg0];
    HuSprite *spr;
    s16 i;

    window->unk48 = arg1;
    window->unk4A = arg2;
    spr = HuSprGet(window->group, 0);
    spr->data->pat->centerX = arg1;
    spr->data->pat->centerY = arg2;
    spr = HuSprGet(window->group, 1);
    for (i = 0; i < spr->data->bankNum; i++) {
        spr->data->pat[i].centerX = arg1;
        spr->data->pat[i].centerY = arg2;
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
        HuSprDispOff(window->group, 0);
    } else {
        HuSprDispOn(window->group, 0);
    }
    HuSprTPLvlSet(window->group, 0, arg1 & 0xFFFF);
}

void HuWinTPLvlSet(s16 winId, s32 arg1) {
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
    HuMemDelayFree(sprite->data->pal);
    sprite->data->pal = palette;
}

void HuWinMesDefColSet(s16 winId, s32 red, s32 green, s32 blue) {
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
                    MessDataMesFree(window->unk_D0);
                }
                window->unk_D0 = NULL;
                window->stat = HUWIN_STAT_NONE;
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
            if (window->attr & HUWIN_ATTR_SHOWSPACE) {
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
                    } else if (*window->mess == 0x1A || (window->attr & HUWIN_ATTR_MONOSPACE)) {
                        window->unk_34 = 10;
                    } else {
                        window->unk_34 = 4;
                    }
                    window->mess++;
                    if (!winCharAdvance(window)) {
                        window->stat = HUWIN_STAT_KEYWAIT_CLEAR;
                        HuWinKeyWaitEntry(winId);
                        return 1;
                    }
                    continue;
                case 0xA:
                    if (!(window->attr & HUWIN_ATTR_NOCR) && !HuWinCR(window) && window->mess[1] != 0) {
                        window->stat = HUWIN_STAT_KEYWAIT_CLEAR;
                        HuWinKeyWaitEntry(winId);
                        window->mess++;
                        return 1;
                    }
                    break;
                case 0x17:
                    if (!(window->attr & HUWIN_ATTR_NOCR) && !winLineFeed(window)) {
                        window->mess++;
                        return 1;
                    }
                    break;
                case 0xB:
                    if (window->attr & HUWIN_ATTR_SHOWSPACE) {
                        _HuWinHomeClear(window);
                    } else if (window->insertionIndex < 0 && !(window->attr & (HUWIN_ATTR_ALIGN_CENTER | HUWIN_ATTR_VALIGN_CENTER))) {
                        winPageClear(window);
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
                    sprite->stat = HUWIN_CHOICE_STAT_MES;
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
                    window->attr |= HUWIN_ATTR_OUTLINE;
                    break;
                case 0x16:
                    window->attr &= ~HUWIN_ATTR_OUTLINE;
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
            if (!winCursorAdvance(window, width)) {
                window->stat = HUWIN_STAT_KEYWAIT_CLEAR;
                HuWinKeyWaitEntry(winId);
                return 1;
            }
            continue;
        }
        if (*window->mess == 0xFF) {
            window->stat = HUWIN_STAT_KEYWAIT;
            HuWinKeyWaitEntry(winId);
            window->mess++;
            return 1;
        }
        window->mess_time -= (u8)window->unk_26;
        if ((s16)window->mess_y + window->unk_28 > window->mess_rect_y + window->mess_rect_h) {
            window->stat = HUWIN_STAT_KEYWAIT_CLEAR;
            HuWinKeyWaitEntry(winId);
            return 1;
        }
        if (*window->mess >= 0x30) {
            if (window->attr & HUWIN_ATTR_ALTDIGITS) {
                if ((u8)(*window->mess - 0x30) < 10) {
                    *window->mess += 0x70;
                }
            }
            if (window->attr & HUWIN_ATTR_BOLD) {
                if ((u8)window->mess_color != 0) {
                    charEntry(winId, *window->mess, 0, window->mess_x + 2, window->mess_y + 1);
                }
                charEntry(winId, *window->mess, window->mess_color, window->mess_x, window->mess_y);
                charEntry(winId, *window->mess, window->mess_color, window->mess_x + 1, window->mess_y);
            } else if (window->attr & HUWIN_ATTR_OUTLINE) {
                charEntry(winId, *window->mess, window->mess_shadow_color, window->mess_x, window->mess_y - 1);
                charEntry(winId, *window->mess, window->mess_shadow_color, window->mess_x, window->mess_y + 1);
                charEntry(winId, *window->mess, window->mess_shadow_color, window->mess_x + 1, window->mess_y);
                charEntry(winId, *window->mess, window->mess_shadow_color, window->mess_x - 1, window->mess_y);
                charEntry(winId, *window->mess, window->mess_color, window->mess_x, window->mess_y);
            } else {
                if ((u8)window->mess_color != 0) {
                    charEntry(winId, *window->mess, 0, window->mess_x + 1, window->mess_y + 1);
                }
                charEntry(winId, *window->mess, window->mess_color, window->mess_x, window->mess_y);
            }
        }
        window->mess++;
        if ((u8)(*window->mess + 0x80) < 2) {
            if (window->attr & HUWIN_ATTR_OUTLINE) {
                charEntry(winId, *window->mess, window->mess_shadow_color, window->unk_27 + window->mess_x - 3, window->mess_y - 2);
                charEntry(winId, *window->mess, window->mess_shadow_color, window->unk_27 + window->mess_x - 3, window->mess_y);
                charEntry(winId, *window->mess, window->mess_shadow_color, window->unk_27 + window->mess_x - 4, window->mess_y - 1);
                charEntry(winId, *window->mess, window->mess_shadow_color, window->unk_27 + window->mess_x - 2, window->mess_y - 1);
            } else if ((u8)window->mess_color != 0) {
                charEntry(winId, *window->mess, 0, window->unk_27 + window->mess_x - 2, window->mess_y);
            }
            charEntry(winId, *window->mess, window->mess_color, window->unk_27 + window->mess_x - 3, window->mess_y - 1);
            window->mess++;
        }
        if (!winCharAdvance(window)) {
            return 1;
        }
    }
    window->mess_time++;
    return 1;
}

s32 winCharAdvance(TextWindow *window) {
    return winCursorAdvance(window, window->unk_34 + (u8)window->spacing_x);
}

s32 winCursorAdvance(TextWindow *window, s16 advance) {
    s32 width;

    winLastAdvance = advance;
    window->mess_x += advance;
    if (gLanguageIndex == LANGUAGE_JAPANESE) {
        width = window->unk_27;
    } else if (window->attr & HUWIN_ATTR_MONOSPACE) {
        width = 10;
    } else {
        width = winFontWidthTbl[*window->mess];
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

s32 winLineFeed(TextWindow *window) {
    window->mess_x = window->mess_rect_x;
    window->mess_y = window->mess_y + ((window->unk_28 >> 2) + window->spacing_y);
    return ((s16)window->mess_y + window->unk_28) <= (window->mess_rect_y + window->mess_rect_h);
}

void winPageClear(TextWindow *window) {
    void *pixels;

    winBGBufCopy(window);
    pixels = HuWinBGBufGet(((u32)window - (u32)winData) / sizeof(TextWindow));
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
            HuSprDispOff(window->group, i);
            window->sprite_id[i] = -1;
        }
    }
}

void HuWinKeyWaitEntry(s16 winId) {
    TextWindow *window = &winData[winId];

    HuSprGrpMemberSet(window->group, 3, winKeyWaitAnim, 0);
    HuSprAttrReset(window->group, 3, 0xFFFF);
    HuSprAttrSet(window->group, 3, HUSPR_ATTR_NOPAUSE);
    HuSprPriSet(window->group, 3, window->prio - 1);
    HuSprPosSet(window->group, 3, window->unk58 - window->unk48, window->unk5A - window->unk4A);
    if (window->attr & HUWIN_ATTR_DISPOFF) {
        HuSprDispOff(window->group, 3);
    }
}

void HuWinKeyWaitIconOff(s16 winId) {
    TextWindow *window = &winData[winId];

    HuSprDispOff(window->group, 3);
}

s32 HuWinSpcFontEntry(s16 winId, s16 icon) {
    TextWindow *window = &winData[winId];
    s16 sprite;
    s16 graphic;
    void *data;

    graphic = winSpcFontAnim[icon];
    if (graphic == -1) {
        if (window->attr & HUWIN_ATTR_EX) {
            data = DataRead(winSpcFontTbl[icon].highlightedFile);
        } else {
            data = DataRead(winSpcFontTbl[icon].file);
        }
        winSpcFontAnim[icon] = graphic = HuSprAnimRead(data);
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
    HuSprGrpMemberSet(window->group, sprite, graphic, winSpcFontTbl[icon].bank);
    HuSprPosSet(window->group, sprite, window->mess_x - window->unk48, window->mess_y - window->unk4A);
    HuSprParentSet(window->group, sprite, 0);
    if ((u8)window->mess_color == 0) {
        HuSprColorSet(window->group, sprite, 0, 0, 0);
    } else if (window->attr & HUWIN_ATTR_EX) {
        HuSprColorSet(window->group, sprite, 0x61, 0x61, 0xF8);
    } else {
        HuSprColorSet(window->group, sprite, 0x38, 0xF8, 0x25);
    }
    if (window->attr & HUWIN_ATTR_DISPOFF) {
        HuSprDispOff(window->group, sprite);
    } else {
        HuSprDispOn(window->group, sprite);
    }
    return winSpcFontTbl[icon].width;
}

void HuWinHomeClear(s16 winId) {
    winPageClear(&winData[winId]);
}

void HuWinNoCRSet(s16 win_id) {
    HuWinAttrSet(win_id, HUWIN_ATTR_NOCR, HUWIN_ATTR_NOCR);
}

void HuWinCancelCRSet(void) {
    cancelCRF = 1;
}

void charEntry(s16 winId, u8 character, u8 color, s16 x, s16 y) {
    TextWindow *window = &winData[winId];
    u8 *pixels;
    u8 *pixelData;
    u8 *glyph;
    s16 width;
    s16 stride;
    s16 height = 12;
    s16 glyphStride = 5;
    s16 i;
    s16 j;
    u8 background;
    u8 backgroundHigh;

    HuWinBGBufCopy(winId);
    if (y < 0) {
        y = 0;
    }
    if (x < 0) {
        x = 0;
    }
    pixelData = HuWinBGBufGet(winId);
    glyph = (u8 *)winFontData + winFontData->glyphOffset;
    glyph += (character - 0x30) * 60;
    if (gLanguageIndex != LANGUAGE_JAPANESE && !(window->attr & HUWIN_ATTR_MONOSPACE)) {
        width = winFontWidthTbl[character];
    } else {
        width = 10;
    }
    window->unk_34 = width;
    if ((window->attr & HUWIN_ATTR_SHOWSPACE) && character != 0x80 && character != 0x81 && color == 0) {
        HuWinBGRectClear(winId, x - 1, y - 2, width + ((u8)window->spacing_x + 3), 14);
    }
    pixels = pixelData + (x + y * window->unk44) / 2;
    stride = window->unk44 / 2;
    color++;
    background = window->mess_shadow_color + 1;
    backgroundHigh = background << 4;
    if (x & 1) {
        for (i = 0; i < height; i++) {
            for (j = 0; j < width / 2; j++, glyph++) {
                if ((*glyph & 0xF0) == 0xF0) {
                    pixels[j] = (pixels[j] & 0xF0) | color;
                } else if ((pixels[j] & 0xF) != 1 && (pixels[j] & 0xF) != background) {
                    if ((*glyph & 0xF0) && color != 1) {
                        pixels[j] = (pixels[j] & 0xF0) | (color + 7);
                    }
                }
                if ((*glyph & 0xF) == 0xF) {
                    (pixels + j)[1] = ((pixels + j)[1] & 0xF) | (color << 4);
                } else if (((pixels + j)[1] & 0xF0) != 0x10 && ((pixels + j)[1] & 0xF0) != backgroundHigh) {
                    if ((*glyph & 0xF) && color != 1) {
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
                    if ((*glyph & 0xF0) && color != 1) {
                        *pixels = (*pixels & 0xF) | ((color + 7) << 4);
                    }
                }
                if ((*glyph & 0xF) == 0xF) {
                    *pixels = (*pixels & 0xF0) | color;
                } else if ((*pixels & 0xF) != 1 && (*pixels & 0xF) != background) {
                    if ((*glyph & 0xF) && color != 1) {
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

void HuWinBGRectClear(s16 winId, s16 x, s16 y, s16 width, s16 height) {
    TextWindow *window = &winData[winId];
    u8 *pixels;
    s16 i;
    s16 j;

    HuWinBGBufCopy(winId);
    if (y < 0) {
        y = 0;
    }
    if (x < 0) {
        x = 0;
    }
    if (window->unk_E0[0] != NULL) {
        pixels = HuWinBGBufGet(winId);
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

void *HuWinBGBufGet(s16 winId) {
    TextWindow *window = &winData[winId];
    s16 group = window->group;
    s16 width;
    s16 height;
    s16 i;
    HuSprite *sprite;

    if (window->unk_E0[0] != NULL) {
        return HuSprGet(group, 1)->data->pat[window->unk_24].data;
    } else {
        width = window->unk44;
        height = window->unk46;
        sprite = HuSprGet(group, 1);
        for (i = 0; i < 3; i++) {
            HuMemFree(sprite->data->pat[i].data);
            sprite->data->pat[i].sizeX = width;
            sprite->data->pat[i].sizeY = window->h;
            sprite->data->pat[i].data = window->unk_E0[i] = HuMemAlloc(width * height / 2);
            memset(window->unk_E0[i], 0, width * height / 2);
        }
        HuMemFree(sprite->data->pal);
        sprite->data->pal = HuMemAlloc(0x20);
        bcopy(window, sprite->data->pal, 0x20);
        if (!(window->attr & HUWIN_ATTR_DISPOFF)) {
            HuSprDispOn(group, 1);
        }
    }
    return sprite->data->pat[window->unk_24].data;
}

void HuWinBGBufSwap(s16 winId) {
    TextWindow *window = &winData[winId];

    HuSprPatNoSet(window->group, 1, window->unk_24);
    window->unk_24++;
    if (window->unk_24 >= 3) {
        window->unk_24 = 0;
    }
    window->attr &= ~HUWIN_ATTR_BUFDIRTY;
}

void HuWinBGBufCopy(s16 winId) {
    winBGBufCopy(&winData[winId]);
}

void winBGBufCopy(TextWindow *window) {
    u8 prevBuf;

    if (window->unk_24 == 0) {
        prevBuf = 2;
    } else {
        prevBuf = window->unk_24 - 1;
    }

    if (window->attr & HUWIN_ATTR_BUFDIRTY) {
        return;
    }
    window->attr |= HUWIN_ATTR_BUFDIRTY;

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
            if ((window->attr & HUWIN_ATTR_PROCOFF) ||
                ((!winPauseF || (window->attr & HUWIN_ATTR_PAUSE)) &&
                 (omPauseChk() + omAllPauseF != 0))) {
                if (window->attr & HUWIN_ATTR_BUFDIRTY) {
                    HuWinBGBufSwap(winId);
                }
                winId = winData[winId].unk64;
                continue;
            }
            window->attr &= ~HUWIN_ATTR_INPUT;
            switch ((u8)window->stat) {
                case HUWIN_STAT_DRAWMES:
                    HuWinDrawMes(winId);
                    break;
                case HUWIN_STAT_KEYWAIT:
                case HUWIN_STAT_KEYWAIT_CLEAR:
                    if (!(window->attr & HUWIN_ATTR_KEYLOCK) || (u8)window->stat == HUWIN_STAT_KEYWAIT_CLEAR) {
                        input = HuWinActivePadGet(window);
                        if ((input & (A_BUTTON | B_BUTTON)) || (input & (u16)window->push_key)) {
                            if (window->unk_AA != -1) {
                                HuAudFXPlay(window->unk_AA);
                            }
                            if ((u8)window->stat == HUWIN_STAT_KEYWAIT_CLEAR) {
                                HuWinHomeClear(winId);
                            }
                            window->stat = HUWIN_STAT_DRAWMES;
                            window->attr |= HUWIN_ATTR_INPUT;
                            window->input = input;
                            HuWinKeyWaitIconOff(winId);
                        }
                    }
                    break;
                case HUWIN_STAT_CHOICE:
                    if (HuWinChoice(winId) == 0) {
                        window->stat = HUWIN_STAT_NONE;
                    }
                    break;
            }
            if (window->attr & HUWIN_ATTR_BUFDIRTY) {
                HuWinBGBufSwap(winId);
            }
            HuWinChoiceCursorExec(window, &window->choice_data[window->choice]);
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

void HuWinTabWidthSet(s16 winId, s16 arg1) {
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
        HuSprGrpMemberSet(window->group, 2, window->cursor_sprite, 0);
        HuSprTPLvlSet(window->group, 2, 0x100);
        HuSprAttrReset(window->group, 2, 0xFFFF);
        HuSprAttrSet(window->group, 2, 0x1009000);
        HuSprPriSet(window->group, 2, window->prio - 1);
    }
    if (arg2 != 0) {
        window->attr |= HUWIN_ATTR_NOCANCEL;
    }
    window->choice = arg1;
    window->stat = HUWIN_STAT_CHOICE;
    window->unk_9A = 1;
    window->unk_A4 = 0;
    while (HuWinStatGet(winId) == HUWIN_STAT_CHOICE) {
        HuPrcVSleep();
    }
    return window->choice;
}

#ifdef NON_MATCHING
/*
 * Remaining diff: `sprite` is allocated to v1 instead of a0 (6 instructions).
 * The do/while(0) in HUWIN_CURSOR_POS after the cursor start stores gives the
 * CSE block boundary the target needs, so the cursor target index is
 * recomputed from `selected` instead of reusing the compare's sign extension.
 * `sprite` has two sets, so global-alloc places it. Its only conflicts are
 * `window`, `selected` and `input` (plus v0); they all cross calls, so
 * prune_preferences drops any v1 preference they have and nothing in
 * regs_someone_prefers excludes v1. `sprite` has no hard reg preference of its
 * own, so find_reg takes v1 first. The original must give `sprite` an a0
 * preference or a v1 conflict that is not yet understood. None of the visible
 * insns can supply one: the address set is (plus window tmp), so
 * set_preference only sees `window`, and the loads use (plus sprite 2/4).
 * `sprite` cannot be local either, because local-alloc would tie it to the
 * index temp (target keeps the temp in v0 and the pointer in a0). A single-death
 * `sprite += ...` form does make the chain local and puts it in a0, but it is
 * still tied. Tried without success: two separate pointers, a saved s8/s16/s32
 * previous choice, pointer arithmetic, reversed or casted compares, block-scope
 * or `register` declarations, copies inside the macro, wrapping the stores in
 * the do/while, static inline helpers, and folded `if` blocks.
 * Also tried: reusing `sprite` for the A_BUTTON `stat` check, indexing through
 * `i`/`current`, pointer compares, do/while(0) around each single statement,
 * different do/while placements (only one after the start stores keeps the
 * score), and moving the `sprite` declaration. expand_preferences cannot help
 * either: the only global dying in a `sprite` set would be T (the choice << 24
 * temp in a0), and T only prefers v0/v1. So the original probably had an insn
 * that existed during allocation and was deleted later, for example a no-op
 * copy or a branch removed after reload. Mario Party 2 has the same code
 * (its unnamed HuWinChoice at 0x8008BCB8, without the mute check) and it
 * also keeps `sprite` in a0.
 * Also tried: static inline cursor setters (the unused return label is
 * removed before CSE, so they give no block boundary), a static inline
 * `&choice_data[n]` getter, and reusing `sprite` in a switch loop, at the
 * initial x/y read, or for the A_BUTTON `stat` read. Each of these changes
 * other code (folded 0xF4/0xF6 offsets become explicit pointer offsets).
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
    if (input & L_JPAD) {
        direction = 0;
    }
    if (input & R_JPAD) {
        direction = 2;
    }
    if (input & U_JPAD) {
        direction = 1;
    }
    if (input & D_JPAD) {
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
        HUWIN_CURSOR_POS(window->cursorStartX, window->cursorStartY, sprite);
        sprite = &window->choice_data[selected];
        HUWIN_CURSOR_POS(window->cursorTargetX, window->cursorTargetY, sprite);
        window->unk_A4 = 0;
        if (window->attr & HUWIN_ATTR_MUTE) {
            HuAudFXPlay(0);
        } else {
            HuAudFXPlay(1);
        }
    }
    i = window->attr & HUWIN_ATTR_NOCANCEL ? 0 : B_BUTTON;
    if (input & A_BUTTON) {
        if (window->choice_data[window->choice].stat == HUWIN_CHOICE_STAT_DISABLED) {
            if (window->unk_AA != -1) {
                if (window->attr & HUWIN_ATTR_MUTE) {
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
            if (window->attr & HUWIN_ATTR_MUTE) {
                HuAudFXPlay(0);
            } else {
                HuAudFXPlay(3);
            }
        }
        window->attr |= HUWIN_ATTR_INPUT;
        window->input = input;
        return 0;
    }
    if ((input & i) || (input & window->push_key)) {
        window->unk_9A = 0;
        window->unk_A4 = 0;
        window->choice = -1;
        if (input & i) {
            if (window->unk_AA != -1) {
                if (window->attr & HUWIN_ATTR_MUTE) {
                    HuAudFXPlay(0);
                } else {
                    HuAudFXPlay(4);
                }
            }
        }
        window->attr |= HUWIN_ATTR_INPUT;
        window->input = input;
        return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game/window", HuWinChoice);
#endif

void HuWinChoiceCursorExec(TextWindow *window, TextWindowSprite *sprite) {
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
                HuSprDispOff(window->group, 2);
            }
            return;
        case 1:
            if (window->attr & HUWIN_ATTR_NOCURSORANIM) {
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
            if (window->attr & HUWIN_ATTR_NOCURSORANIM) {
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
        HuSprDispOff(window->group, 2);
    } else {
        dy = 0.8f;
        dx = scaleX * dy;
        spriteScaleX = window->scaleX;
        dy = scaleY * dy;
        spriteScaleY = window->scaleY;
        HuSprScaleSet(window->group, 2, dx * spriteScaleX, dy * spriteScaleY);
        HuSprPosSet(window->group, 2, dx = x / dx * window->scaleX, dy = y / dy * window->scaleY);
        if (!(window->attr & HUWIN_ATTR_DISPOFF)) {
            HuSprDispOn(window->group, 2);
        }
    }
}

void HuWinKill(s16 winId) {
    TextWindow *window = &winData[winId];
    s16 i;

    if (window->unk_D0 != NULL && window->unk_D4 != 0) {
        MessDataMesFree(window->unk_D0);
    }
    for (i = 0; i < 5; i++) {
        if (window->insert_mess[i] != NULL && window->usingStringIDBool[i] != 0) {
            MessDataMesFree(window->insert_mess[i]);
        }
    }
    HuSprGrpKill(window->group);
    HuSprAnimKill(window->unk66);
    HuSprAnimKill(window->unk68);
    for (i = 4; i < 12; i++) {
        if (window->sprite_id[i] != -1) {
            HuSprAnimKill(HuWinSprIDGet(winId, i));
        }
    }
    if (window->cursor_sprite != -1) {
        HuSprAnimKill(window->cursor_sprite);
    }
    window->unk5E = -1;
    winData[window->unk64].unk62 = window->unk62;
    winData[window->unk62].unk64 = window->unk64;
    winPrio += 0x20;
}

void HuWinAllKill(void) {
    s16 i;

    if (winInitF != 0) {
        for (i = winData[0].unk64; winData[i].unk64 != -1; i = winData[i].unk64) {
            HuWinKill(i);
        }
        DataCloseTemp(winFontData);
        DataCloseTemp(winFrameData);
        DataCloseTemp(winCursorData);
        HuMemMemoryFreeTemp(winData);
        omDelPrcObj(winProc);
        winInitF = 0;
        for (i = 0; i < ARRAY_COUNT(winSpcFontAnim); i++) {
            if (winSpcFontAnim[i] != -1) {
                HuSprAnimKill(winSpcFontAnim[i]);
            }
        }
        HuSprAnimKill(winKeyWaitAnim);
    }
}

void HuWinComKeyWait(s16 player1, s16 player2, s16 player3, s16 player4, u8 frames) {
    _HuWinComKeySet(-(player1 == HUWIN_COMKEY_PAD), -(player2 == HUWIN_COMKEY_PAD), -(player3 == HUWIN_COMKEY_PAD), -(player4 == HUWIN_COMKEY_PAD), frames);
    _HuWinComKeySet(player1, player2, player3, player4, 1);
}

void HuWinComKeySet(s16 player1, s16 player2, s16 player3, s16 player4) {
    _HuWinComKeySet(player1, player2, player3, player4, 1);
}

void _HuWinComKeySet(s16 player1, s16 player2, s16 player3, s16 player4, s16 frames) {
    winComKeyBuf[comKeyIdx][0] = player1;
    winComKeyBuf[comKeyIdx][1] = player2;
    winComKeyBuf[comKeyIdx][2] = player3;
    winComKeyBuf[comKeyIdx][3] = player4;
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
        if (inputs[i] == HUWIN_COMKEY_PAD) {
            inputs[i] = ContBtnRep[i];
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

    if (window->attr & HUWIN_ATTR_COMKEY) {
        HuWinComKeyGet(queuedInputs);
    }
    if (window->active_pad & HUWIN_PLAYER_1) {
        if (window->attr & HUWIN_ATTR_COMKEY) {
            input = queuedInputs[0] | input;
        } else {
            input |= (ContBtnRep[0] & (u16)~(A_BUTTON | B_BUTTON)) | (ContBtnDown[0] & (A_BUTTON | B_BUTTON));
        }
    }
    if (window->active_pad & HUWIN_PLAYER_2) {
        if (window->attr & HUWIN_ATTR_COMKEY) {
            input = queuedInputs[1] | input;
        } else {
            input |= (ContBtnRep[1] & (u16)~(A_BUTTON | B_BUTTON)) | (ContBtnDown[1] & (A_BUTTON | B_BUTTON));
        }
    }
    if (window->active_pad & HUWIN_PLAYER_3) {
        if (window->attr & HUWIN_ATTR_COMKEY) {
            input = queuedInputs[2] | input;
        } else {
            input |= (ContBtnRep[2] & (u16)~(A_BUTTON | B_BUTTON)) | (ContBtnDown[2] & (A_BUTTON | B_BUTTON));
        }
    }
    if (window->active_pad & HUWIN_PLAYER_4) {
        if (window->attr & HUWIN_ATTR_COMKEY) {
            input = queuedInputs[3] | input;
        } else {
            input |= (ContBtnRep[3] & (u16)~(A_BUTTON | B_BUTTON)) | (ContBtnDown[3] & (A_BUTTON | B_BUTTON));
        }
    }
    return input;
}

u8 HuWinMesCharConv(u8 *arg0) {
    s16 i, j;

    for (i = 0; i < 10; i += 2) {
        if (winKanjiNumTbl[i] == arg0[0] && winKanjiNumTbl[i + 1] == arg0[1]) {
            return i / 2;
        }
    }
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 32; j += 2) {
            if (winKanjiNumAltTbl[i][j] == arg0[0] && winKanjiNumAltTbl[i][j + 1] == arg0[1]) {
                return i * 16 + j / 2;
            }
        }
    }
    return 16;
}

// Converts a two byte per character string into a one byte per character string.
void HuWinMesConv(u8 *buffer, s32 message) {
    u8 *str = (u8 *)message;

    if (*str != 0) {
        do {
            *buffer = HuWinMesCharConv(str);
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
        color = winPalTbl[i + 9];
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
    HuMemDelayFree(sprite->data->pal);
    sprite->data->pal = palette;
}

void HuWinActivePlayerSet(s16 winId, s16 arg1) {
    TextWindow *window = &winData[winId];

    window->active_pad = (window->active_pad & 0xF0) | arg1;
}

void HuWinDispOff(s16 winId) {
    TextWindow *window = &winData[winId];
    s16 i;

    HuSprDispOff(window->group, 0);
    HuSprDispOff(window->group, 1);
    for (i = 4; i < 22; i++) {
        if (window->sprite_id[i] != -1) {
            HuSprDispOff(window->group, i);
        }
    }
    if (window->cursor_sprite != -1) {
        HuSprDispOff(window->group, 2);
    }
    if (window->stat & HUWIN_STAT_KEYWAIT) {
        HuSprDispOff(window->group, 3);
    }
    HuWinAttrSet(winId, HUWIN_ATTR_DISPOFF | HUWIN_ATTR_OPEN, HUWIN_ATTR_DISPOFF);
}

void HuWinDispOn(s16 winId) {
    TextWindow *window = &winData[winId];
    s16 i;

    HuSprDispOn(window->group, 0);
    HuSprDispOn(window->group, 1);
    for (i = 4; i < 22; i++) {
        if (window->sprite_id[i] != -1) {
            HuSprDispOn(window->group, i);
        }
    }
    if (window->cursor_sprite != -1) {
        HuSprDispOn(window->group, 2);
    }
    if (window->stat & HUWIN_STAT_KEYWAIT) {
        HuSprDispOn(window->group, 3);
    }
    HuWinAttrSet(winId, HUWIN_ATTR_DISPOFF | HUWIN_ATTR_OPEN, HUWIN_ATTR_OPEN);
}

void HuWinKeyLockSet(s16 winId, s32 arg1) {
    TextWindow *window;

    window = &winData[winId];
    if (arg1 != 0) {
        window->attr |= HUWIN_ATTR_KEYLOCK;
    } else {
        window->attr &= ~HUWIN_ATTR_KEYLOCK;
    }
}

// Sets an option disabled.
void HuWinChoiceDisable(s32 winId, s16 spriteIndex) {
    TextWindow *window = &winData[winId];

    window->choice_data[spriteIndex].stat = HUWIN_CHOICE_STAT_DISABLED;
}

void HuWinDummy(s32 obj) {
#ifdef DEBUG

#endif
}

s16 HuWinChoiceNowGet(s32 winId) {
    return winData[winId].choice;
}

// Copies a string, dropping any newline characters it contains.
void HuWinMesLFStrip(u8 *str, u8 *buffer) {
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

void HuWinInsertMesSetNoLF(s16 winId, u32 arg1, s8 arg2) {
    TextWindow *window = &winData[winId];

    HuWinInsertMesSet(winId, arg1, arg2);
    HuWinMesLFStrip(window->insert_mess[arg2], window->insert_mess[arg2]);
}

// Called to indicate that `str` should be the replacement at a
// "replacement index" location in the main string.
void HuWinInsertMesSizeGet(u32 str, s16 index) {
    winInsertF = 1;
    winMaxHeight = 0;
    winMaxWidth = 0;
    GetMesMaxSizeSub(str);
    cancelCRF = 0;
    mesWInsert[index] = winMaxWidth;
}

void HuWinInsertMesSizeGetNoLF(u32 str, s16 index) {
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
        text = MessDataMesGet((void *)str);
    }
    HuWinMesLFStrip(text, text);
    GetMesMaxSizeSub((u32)text);
    cancelCRF = 0;
    if (allocated) {
        MessDataMesFree(text);
    }
    mesWInsert[index] = winMaxWidth;
}

void HuWinChoiceSet(s16 winId, s16 arg1, u8 arg2) {
    winData[winId].unk_B2[arg1] = arg2;
}

void HuWinTabSizeSet(s8 arg0) {
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

// The following data is defined here rather than at the top of the file so that the
// character set strings are placed in the middle of this file's .rodata.
u8 *winKanjiNumAltTbl[] = {
    // 終黒青赤紫緑水黄白※行頁＜＞間［
    (u8 *)"\x8F\x49\x8D\x95\x90\xC2\x90\xD4\x8E\x87\x97\xCE\x90\x85\x89\xA9\x94\x92\x81\xA6\x8D\x73\x95\xC5\x81\x83\x81\x84\x8A\xD4\x81\x6D",
    // 　①②③④⑤］半特基※※※※※※
    (u8 *)"\x81\x40\x87\x40\x87\x41\x87\x42\x87\x43\x87\x44\x81\x6E\x94\xBC\x93\xC1\x8A\xEE\x81\xA6\x81\xA6\x81\xA6\x81\xA6\x81\xA6\x81\xA6",
    // ※αβ㊤㊨㊧㊦Ζ〒●★始右※※※
    (u8 *)"\x81\xA6\x83\xBF\x83\xC0\x87\x85\x87\x89\x87\x88\x87\x87\x83\xA4\x81\xA7\x81\x9C\x81\x9A\x8E\x6E\x89\x45\x81\xA6\x81\xA6\x81\xA6",
    // ０１２３４５６７８９○☆＋－×→
    (u8 *)"\x82\x4F\x82\x50\x82\x51\x82\x52\x82\x53\x82\x54\x82\x55\x82\x56\x82\x57\x82\x58\x81\x9B\x81\x99\x81\x7B\x81\x7C\x81\x7E\x81\xA8",
    // ※ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯ
    (u8 *)"\x81\xA6\x82\x60\x82\x61\x82\x62\x82\x63\x82\x64\x82\x65\x82\x66\x82\x67\x82\x68\x82\x69\x82\x6A\x82\x6B\x82\x6C\x82\x6D\x82\x6E",
    // ＰＱＲＳＴＵＶＷＸＹＺ”’（）／
    (u8 *)"\x82\x6F\x82\x70\x82\x71\x82\x72\x82\x73\x82\x74\x82\x75\x82\x76\x82\x77\x82\x78\x82\x79\x81\x68\x81\x66\x81\x69\x81\x6A\x81\x5E",
    // ※ａｂｃｄｅｆｇｈｉｊｋｌｍｎｏ
    (u8 *)"\x81\xA6\x82\x81\x82\x82\x82\x83\x82\x84\x82\x85\x82\x86\x82\x87\x82\x88\x82\x89\x82\x8A\x82\x8B\x82\x8C\x82\x8D\x82\x8E\x82\x8F",
    // ｐｑｒｓｔｕｖｗｘｙｚ：％・※※
    (u8 *)"\x82\x90\x82\x91\x82\x92\x82\x93\x82\x94\x82\x95\x82\x96\x82\x97\x82\x98\x82\x99\x82\x9A\x81\x46\x81\x93\x81\x45\x81\xA6\x81\xA6",
    // ゛゜、。ー．をぁぃぅぇぉゃゅょっ
    (u8 *)"\x81\x4A\x81\x4B\x81\x41\x81\x42\x81\x5B\x81\x44\x82\xF0\x82\x9F\x82\xA1\x82\xA3\x82\xA5\x82\xA7\x82\xE1\x82\xE3\x82\xE5\x82\xC1",
    // ※あいうえおかきくけこさしすせそ
    (u8 *)"\x81\xA6\x82\xA0\x82\xA2\x82\xA4\x82\xA6\x82\xA8\x82\xA9\x82\xAB\x82\xAD\x82\xAF\x82\xB1\x82\xB3\x82\xB5\x82\xB7\x82\xB9\x82\xBB",
    // たちつてとなにぬねのはひふへほま
    (u8 *)"\x82\xBD\x82\xBF\x82\xC2\x82\xC4\x82\xC6\x82\xC8\x82\xC9\x82\xCA\x82\xCB\x82\xCC\x82\xCD\x82\xD0\x82\xD3\x82\xD6\x82\xD9\x82\xDC",
    // みむめもやゆよらりるれろわん※※
    (u8 *)"\x82\xDD\x82\xDE\x82\xDF\x82\xE0\x82\xE2\x82\xE4\x82\xE6\x82\xE7\x82\xE8\x82\xE9\x82\xEA\x82\xEB\x82\xED\x82\xF1\x81\xA6\x81\xA6",
    // 「」！？♯♭ヲァィゥェォャュョッ
    (u8 *)"\x81\x75\x81\x76\x81\x49\x81\x48\x81\xF2\x81\xF3\x83\x92\x83\x40\x83\x42\x83\x44\x83\x46\x83\x48\x83\x83\x83\x85\x83\x87\x83\x62",
    // ※アイウエオカキクケコサシスセソ
    (u8 *)"\x81\xA6\x83\x41\x83\x43\x83\x45\x83\x47\x83\x49\x83\x4A\x83\x4C\x83\x4E\x83\x50\x83\x52\x83\x54\x83\x56\x83\x58\x83\x5A\x83\x5C",
    // タチツテトナニヌネノハヒフヘホマ
    (u8 *)"\x83\x5E\x83\x60\x83\x63\x83\x65\x83\x67\x83\x69\x83\x6A\x83\x6B\x83\x6C\x83\x6D\x83\x6E\x83\x71\x83\x74\x83\x77\x83\x7A\x83\x7D",
    // ミムメモヤユヨラリルレロワン…▼
    (u8 *)"\x83\x7E\x83\x80\x83\x81\x83\x82\x83\x84\x83\x86\x83\x88\x83\x89\x83\x8A\x83\x8B\x83\x8C\x83\x8D\x83\x8F\x83\x93\x81\x63\x81\xA5",
};

static WindowFrameDefinition winExFrameTbl[] = {
    { 0x87, 0x0, 220, 46, 24, 9, 190, 28, 3, 22, 1, 1 },
    { 0x93, 0x0, 220, 62, 23, 12, 190, 42, 4, 38, 1, 0 },
    { 0x11000A, 0x0, 220, 74, 27, 9, 190, 56, 3, 36, 1, 0 },
    { 0x110009, 0x0, 214, 42, 15, 9, 190, 28, 33, 54, 1, 0 },
    { 0x11000B, 0x0, 214, 75, 13, 27, 190, 42, 31, 5, 1, 0 },
    { 0x11000C, 0x0, 214, 75, 13, 27, 190, 42, 45, 0, 1, 0 },
    { 0x11000D, 0x0, 220, 62, 23, 12, 180, 42, 4, 38, 1, 0 },
    { 0x86, 0x0, 224, 74, 23, 12, 190, 56, 0, 32, 1, 0 },
    { 0x87, 0x0, 224, 46, 15, 10, 190, 28, 226, 23, 1, 0 },
    { 0x89, 0x8A, 180, 90, 23, 28, 130, 42, 60, 4, 1, 0 },
    { 0x8B, 0x8C, 158, 64, 20, 16, 128, 30, 96, 62, 1, 0 },
    { 0x8B, 0x8C, 158, 64, 17, 16, 130, 30, 96, 62, 1, 0 },
    { 0x89, 0x8A, 180, 90, 24, 23, 130, 42, 60, 86, 1, 2 },
    { 0x89, 0x8A, 180, 90, 24, 23, 130, 42, 120, 86, 1, 3 },
    { 0x8D, 0x8E, 180, 90, 24, 23, 130, 42, 36, 88, 1, 0 },
    { 0x8D, 0x8E, 180, 90, 24, 23, 130, 42, 144, 88, 1, 1 },
    { 0x8F, 0x0, 226, 62, 27, 12, 186, 45, 0, 31, 1, 0 },
    { 0x90, 0x0, 206, 62, 27, 12, 180, 45, 0, 31, 1, 0 },
    { 0x93, 0x0, 220, 62, 14, 12, 190, 42, 216, 38, 1, 1 },
    { 0x91, 0x0, 230, 42, 9, 8, 210, 30, 115, 21, 1, 0 },
    { 0x92, 0x0, 230, 52, 9, 6, 210, 45, 115, 26, 1, 0 },
};

static s32 winExAnimTbl[] = {
    0x35, 0x36, 0x3C, 0x3D, 0x3E, 0x42, 0x3F, 0x40,
    0x37, 0x38, 0x41, 0x39, 0x3A, 0x3B, 0x46, 0x47,
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x43, 0x44, 0x140036,
    0x140037, 0x140038, 0x140039, 0x14003A, 0x14003B, 0x14003C, 0x14003D, 0x14003E,
    0x14003F, 0x140040, 0x140041, 0x4D, 0x4E, 0x4F, 0x50, 0x51,
    0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
    0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x45,
    0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
};

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
        allocatedText = MessDataMesGet((void *)str);
        text = allocatedText;
    }
    height = 14;
    width = 0;
    for (; *text != 0; text++) {
        heightAdvance = 0;
        if (gLanguageIndex == LANGUAGE_JAPANESE) {
            advance = (*text == 0x80 || *text == 0x81) ? 0 : 10;
        } else {
            advance = winFontWidthTbl[*text];
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
        MessDataMesFree(allocatedText);
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

s32 HuWinExCreateStyled(s32 x, s32 y, s32 frameIndex) {
    s32 winId;
    s32 member;
    TextWindow *window;
    WindowFrameDefinition *frame;
    HuSprite *sprite;

    frame = &winExFrameTbl[frameIndex];
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
    HuWinCenterPosSet(winId, frame->spriteWidth, frame->spriteHeight);
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
    sprite->data->pat->centerX = frame->spriteWidth;
    sprite->data->pat->centerY = frame->spriteHeight;
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
        sprite->data->pat->centerX = frame->spriteWidth;
        sprite->data->pat->centerY = frame->spriteHeight;
    } else {
        window->unk276 = 0;
    }
    window->attr |= HUWIN_ATTR_EX;
    HuWinBGTPLvlSet(winId, 0);
    HuWinMesDefColSet(winId, 192, 192, 192);
    HuWinMesColSet(winId, frame->speed);
    HuWinBGColSet(winId, 255, 255, 255);
    HuWinScaleSet(winId, 0, 0);
    return winId;
}

void HuWinExOpen(s32 winId, s32 playSound) {
    TextWindow *window = &winData[winId];
    s16 i;
    f32 scale;

    if (!(window->attr & HUWIN_ATTR_OPEN)) {
        HuWinKeyLockSet(winId, 1);
        if (playSound) {
            if (window->attr & HUWIN_ATTR_MUTE) {
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
        HuWinKeyLockSet(winId, 0);
        HuWinAttrSet(winId, HUWIN_ATTR_OPEN, HUWIN_ATTR_OPEN);
        HuPrcVSleep();
    }
}

void HuWinExOpenNow(s32 win_id) {
    TextWindow *window = &winData[win_id];

    HuWinKeyLockSet(win_id, 1);
    HuSprScaleSet(window->group, window->unk274, 1.0f, 1.0f);
    if (window->unk276 != 0) {
        HuSprScaleSet(window->group, window->unk276, 1.0f, 1.0f);
    }
    HuWinScaleSet(win_id, 1.0f, 1.0f);
    HuWinKeyLockSet(win_id, 0);
    HuWinAttrSet(win_id, HUWIN_ATTR_OPEN, HUWIN_ATTR_OPEN);
}

void HuWinExClose(s32 winId, s32 playSound) {
    TextWindow *window = &winData[winId];
    f32 scale = 1.0f;

    if (window->attr & HUWIN_ATTR_OPEN) {
        HuWinKeyLockSet(winId, 1);
        if (playSound) {
            if (window->attr & HUWIN_ATTR_MUTE) {
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
        HuWinKeyLockSet(winId, 0);
        HuWinAttrSet(winId, HUWIN_ATTR_OPEN, HUWIN_ATTR_NONE);
    }
}

void HuWinExTPLvlSet(s32 winId, s32 alpha) {
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

void HuWinExPriSet(s16 win_id, s32 priority) {
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
    HuWinCenterPosSet(temp_v0, temp_s0 / 2, arg4 / 2);
    HuWinPosSet(temp_v0, (temp_s2->pos_x + temp_s0 / 2), (temp_s2->pos_y + arg4 / 2));
    temp_s2->unk276 = arg0;

    if (arg0 != -1) {
        temp_s2->unk274 = HuWinAnimSet(temp_v0, winExAnimTbl[arg0], (0x18 - temp_s2->unk48), (0x18 - temp_s2->unk4A), 0);
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

    HuWinKeyLockSet(winId, 1);
    if (window->unk276 != -1) {
        HuSprScaleSet(window->group, window->unk274, 0.0f, 0.0f);
    }
    HuWinDispOn(winId);
    for (i = 1; i < 6; i++) {
        HuWinFrameScaleSet(winId, 1.0f - cosdf(i * 18.0f), 2.0f / window->h);
        HuPrcVSleep();
    }
    for (i = 1; i < 4; i++) {
        HuWinFrameScaleSet(winId, 1.0f, sindf(i * 30.0f) * 1.05f);
        HuPrcVSleep();
    }
    HuWinFrameScaleSet(winId, 1.0f, 1.0f);
    if (window->unk276 != -1) {
        HuSprPosSet(window->group, window->unk274, 0x18 - window->unk48, 0x18 - window->unk4A);
        HuSprScaleSet(window->group, window->unk274, 1.0f, 1.0f);
        HuWinExFrameAnim(winId, 1);
    }
    HuWinKeyLockSet(winId, 0);
}

void HuWinExFrameAnim(s16 winId, s32 opening) {
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
    original = sprite->data->pat->data;
    for (i = 0; i < 3; i++) {
        buffers[i] = HuMemAllocTag(0x640, TAG_OVERLAY);
        memset(buffers[i], 0, 0x640);
    }
    source = sprite->data->pal;
    source++;
    for (transparent = 0; transparent < sprite->data->palNum; transparent++, source += 2) {
        if (!(*source & 1)) {
            break;
        }
    }
    frames = opening ? 6 : 3;
    for (i = 1; i <= frames; i++) {
        source = original;
        dest = buffers[Hu3DBufNo];
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
        sprite->data->pat->data = buffers[Hu3DBufNo];
        HuPrcVSleep();
    }
    for (i = 0; i < 3; i++) {
        HuMemDelayFree(buffers[i]);
    }
    sprite->data->pat->data = original;
}

void HuWinExAnimPopIn(s16 winId, s16 arg1) {
    s16 temp_v0;
    TextWindow *temp_s0;

    temp_s0 = &winData[winId];
    HuWinKeyLockSet(winId, 1);
    HuWinExFrameAnim(winId, 0);
    HuWinSprKill(winId, temp_s0->unk274);
    temp_v0 = HuWinAnimSet(winId, winExAnimTbl[arg1], 0x18 - temp_s0->unk48, 0x18 - temp_s0->unk4A, 0);
    temp_s0->unk274 = temp_v0;
    HuSprPosSet(temp_s0->group, temp_v0, 0x18 - temp_s0->unk48, 0x18 - temp_s0->unk4A);
    HuSprScaleSet(temp_s0->group, temp_s0->unk274, 1.0f, 1.0f);
    HuWinExFrameAnim(winId, 1);
    HuWinKeyLockSet(winId, 0);
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
