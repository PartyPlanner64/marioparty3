#include "common.h"
#include "game_guys_magic_boxes.h"

typedef struct GameGuysMagicBoxesBanner { // 0x14 bytes
    /* 0x00 */ HuSprite *sprite;
    /* 0x04 */ void *unk_04[3];
    /* 0x10 */ s16 group;
    /* 0x12 */ s16 timer;
} GameGuysMagicBoxesBanner;

typedef struct GameGuysMagicBoxesRing { // 0x18 bytes
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 color;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 radius;
    /* 0x0A */ s16 freqX;
    /* 0x0C */ s16 freqY;
    /* 0x10 */ f32 angle;
    /* 0x14 */ f32 speed;
} GameGuysMagicBoxesRing;

typedef struct GameGuysMagicBoxesRingHistory { // 0x20 bytes
    /* 0x00 */ s16 active[4];
    /* 0x08 */ s16 x[4];
    /* 0x10 */ s16 y[4];
    /* 0x18 */ s16 radius[4];
} GameGuysMagicBoxesRingHistory;

typedef struct GameGuysMagicBoxesRingFreq {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} GameGuysMagicBoxesRingFreq;

s16 D_8010C260_game_guys_magic_boxes = 0;   // intro timer
s16 D_8010C262_game_guys_magic_boxes = 120; // intro start y
s16 D_8010C264_game_guys_magic_boxes = 0;   // outro timer

GameGuysMagicBoxesRing D_8010CA20_game_guys_magic_boxes[3] BSS;
s16 D_8010CA68_game_guys_magic_boxes BSS;                              // center x
s16 D_8010CA6A_game_guys_magic_boxes BSS;                              // center y
s16 D_8010CA6C_game_guys_magic_boxes BSS;                              // radius
s16 D_8010CA6E_game_guys_magic_boxes BSS;                              // target x
s16 D_8010CA70_game_guys_magic_boxes BSS;                              // target y
u8 D_8010CA74_game_guys_magic_boxes[4] BSS;                            /* Unreferenced. */
GameGuysMagicBoxesRingHistory D_8010CA78_game_guys_magic_boxes[3] BSS; // per-buffer ring state
u8 D_8010CAD8_game_guys_magic_boxes[8] BSS;                            /* Unreferenced. */
GameGuysMagicBoxesBanner D_8010CAE0_game_guys_magic_boxes BSS;
u8 D_8010CAF4_game_guys_magic_boxes[4] BSS; /* Unreferenced. */
GameGuysMagicBoxesBanner D_8010CAF8_game_guys_magic_boxes BSS;
s16 D_8010CB0C_game_guys_magic_boxes BSS; // current buffer index

void func_8010BA0C_game_guys_magic_boxes(void);
void func_8010BB70_game_guys_magic_boxes(void);
void func_8010BC00_game_guys_magic_boxes(s16 active, s16 x, s16 y, s16 radius);
void func_8010BD5C_game_guys_magic_boxes(s16 active, s16 x, s16 y, s16 color);
void func_8010BD9C_game_guys_magic_boxes(s16 active, s16 x, s16 y, s16 radius, s16 color);
void func_8010BF94_game_guys_magic_boxes(s16 x0, s16 y0, s16 x1, s16 y1);

void func_8010A8C0_game_guys_magic_boxes(s16 x, s16 y) {
    s16 i;
    u8 pattern;
    GameGuysMagicBoxesRingFreq freqs[3] = { { 10, 7 }, { 10, 8 }, { 10, 10 } };

    D_8010CA68_game_guys_magic_boxes = 160;
    D_8010CA6A_game_guys_magic_boxes = 120;
    D_8010CA6C_game_guys_magic_boxes = 95;
    D_8010CA6E_game_guys_magic_boxes = x;
    D_8010CA70_game_guys_magic_boxes = y;
    pattern = rand8() % 3;
    for (i = 0; i < 3; i++) {
        D_8010CA20_game_guys_magic_boxes[i].active = 0;
        D_8010CA20_game_guys_magic_boxes[i].freqX = freqs[pattern].x;
        D_8010CA20_game_guys_magic_boxes[i].freqY = freqs[pattern].y;
        D_8010CA20_game_guys_magic_boxes[i].speed = 1.5f;
        if (pattern == 0) {
            D_8010CA20_game_guys_magic_boxes[i].speed = 1.75f;
        }
        D_8010CA20_game_guys_magic_boxes[i].angle = i * 120;
        D_8010CA20_game_guys_magic_boxes[i].x =
            D_8010CA68_game_guys_magic_boxes + cosdf(D_8010CA20_game_guys_magic_boxes[i].freqX * D_8010CA20_game_guys_magic_boxes[i].angle) * D_8010CA6C_game_guys_magic_boxes;
        D_8010CA20_game_guys_magic_boxes[i].y =
            D_8010CA6A_game_guys_magic_boxes + sindf(D_8010CA20_game_guys_magic_boxes[i].freqY * D_8010CA20_game_guys_magic_boxes[i].angle) * D_8010CA6C_game_guys_magic_boxes;
        D_8010CA20_game_guys_magic_boxes[i].radius = 0;
    }
    D_8010CA20_game_guys_magic_boxes[0].color = 1;
    D_8010CA20_game_guys_magic_boxes[1].color = 2;
    D_8010CA20_game_guys_magic_boxes[2].color = 4;
    D_8010CAF8_game_guys_magic_boxes.timer = 128;
    D_8010CAE0_game_guys_magic_boxes.timer = 256;
    func_8010BA0C_game_guys_magic_boxes();
    func_8010BB70_game_guys_magic_boxes();
    D_8010CB0C_game_guys_magic_boxes = 0;
}

void func_8010AB8C_game_guys_magic_boxes(void) {
    func_8010BB70_game_guys_magic_boxes();
    D_8010CB0C_game_guys_magic_boxes = 0;
    D_8010CAF8_game_guys_magic_boxes.timer = 0;
    HuSprTPLvlSet(D_8010CAF8_game_guys_magic_boxes.group, 0, 0);
    HuSprAttrReset(D_8010CAF8_game_guys_magic_boxes.group, 0, 0xFFFF);
    HuSprAttrSet(D_8010CAF8_game_guys_magic_boxes.group, 0, 0x1000);
    D_8010CAF8_game_guys_magic_boxes.sprite->unk_84->unk00->unk00 =
        D_8010CAF8_game_guys_magic_boxes.unk_04[D_8010CB0C_game_guys_magic_boxes];
}

s16 func_8010AC18_game_guys_magic_boxes(void) {
    s16 i;

    if (WipeStatGet() == 1) {
        return 0;
    }
    if (D_8010C260_game_guys_magic_boxes >= 5) {
        if (D_8010C260_game_guys_magic_boxes < 15) {
            for (i = 0; i < 3; i++) {
                D_8010CA20_game_guys_magic_boxes[i].active = 1;
                D_8010CA20_game_guys_magic_boxes[i].radius = sindf((D_8010C260_game_guys_magic_boxes - 5) * 9.0f) * 45.0f;
            }
        } else if (D_8010C260_game_guys_magic_boxes < 20) {
            for (i = 0; i < 3; i++) {
                D_8010CA20_game_guys_magic_boxes[i].radius = 45;
            }
        } else if (D_8010C260_game_guys_magic_boxes < 47) {
            for (i = 0; i < 3; i++) {
                D_8010CA20_game_guys_magic_boxes[i].angle += D_8010CA20_game_guys_magic_boxes[i].speed;
                if (D_8010CA20_game_guys_magic_boxes[i].angle >= 360.0f) {
                    D_8010CA20_game_guys_magic_boxes[i].angle -= 360.0f;
                }
                if (D_8010CA20_game_guys_magic_boxes[i].angle < 0.0f) {
                    D_8010CA20_game_guys_magic_boxes[i].angle += 360.0f;
                }
                D_8010CA20_game_guys_magic_boxes[i].x = D_8010CA68_game_guys_magic_boxes +
                                                        cosdf(D_8010CA20_game_guys_magic_boxes[i].freqX * D_8010CA20_game_guys_magic_boxes[i].angle) * D_8010CA6C_game_guys_magic_boxes;
                D_8010CA20_game_guys_magic_boxes[i].y = D_8010CA6A_game_guys_magic_boxes +
                                                        sindf(D_8010CA20_game_guys_magic_boxes[i].freqY * D_8010CA20_game_guys_magic_boxes[i].angle) * D_8010CA6C_game_guys_magic_boxes;
            }
        } else if (D_8010C260_game_guys_magic_boxes < 80) {
            if (D_8010CA6C_game_guys_magic_boxes > 0) {
                if ((D_8010CA6C_game_guys_magic_boxes -= 3) <= 0) {
                    D_8010CA6C_game_guys_magic_boxes = 0;
                }
            }
            D_8010CA6A_game_guys_magic_boxes =
                D_8010C262_game_guys_magic_boxes - sindf((D_8010C260_game_guys_magic_boxes - 47) * 2.7272727f) *
                                                       (D_8010C262_game_guys_magic_boxes - D_8010CA70_game_guys_magic_boxes);
            if (D_8010C260_game_guys_magic_boxes == 79) {
                D_8010CA6A_game_guys_magic_boxes = D_8010CA70_game_guys_magic_boxes;
            }
            for (i = 0; i < 3; i++) {
                D_8010CA20_game_guys_magic_boxes[i].angle += D_8010CA20_game_guys_magic_boxes[i].speed;
                if (D_8010CA20_game_guys_magic_boxes[i].angle >= 360.0f) {
                    D_8010CA20_game_guys_magic_boxes[i].angle -= 360.0f;
                }
                if (D_8010CA20_game_guys_magic_boxes[i].angle < 0.0f) {
                    D_8010CA20_game_guys_magic_boxes[i].angle += 360.0f;
                }
                D_8010CA20_game_guys_magic_boxes[i].x = D_8010CA68_game_guys_magic_boxes +
                                                        cosdf(D_8010CA20_game_guys_magic_boxes[i].freqX * D_8010CA20_game_guys_magic_boxes[i].angle) * D_8010CA6C_game_guys_magic_boxes;
                D_8010CA20_game_guys_magic_boxes[i].y = D_8010CA6A_game_guys_magic_boxes +
                                                        sindf(D_8010CA20_game_guys_magic_boxes[i].freqY * D_8010CA20_game_guys_magic_boxes[i].angle) * D_8010CA6C_game_guys_magic_boxes;
            }
        } else if (D_8010C260_game_guys_magic_boxes < 90) {
            for (i = 1; i < 3; i++) {
                D_8010CA20_game_guys_magic_boxes[i].active = 0;
            }
            D_8010CA20_game_guys_magic_boxes[0].color = 7;
        } else if (D_8010C260_game_guys_magic_boxes >= 120) {
            func_8010B8B4_game_guys_magic_boxes();
            return 1;
        } else {
            D_8010CA20_game_guys_magic_boxes[0].radius = sindf((D_8010C260_game_guys_magic_boxes - 90) * 3.0f) * 50.0f + 45.0f;
            D_8010CAF8_game_guys_magic_boxes.timer = 128.0f - sindf((D_8010C260_game_guys_magic_boxes - 90) * 3.0f) * 128.0f;
            D_8010CAE0_game_guys_magic_boxes.timer = 256.0f - sindf((D_8010C260_game_guys_magic_boxes - 90) * 3.0f) * 256.0f;
        }
    }
    if (D_8010C260_game_guys_magic_boxes == 15) {
        HuAudFXPlay(0x52B);
    }
    if (D_8010C260_game_guys_magic_boxes == 90) {
        func_8004AB0C_main(30);
        HuAudSeqPlay(0x43);
    }
    if (D_8010C260_game_guys_magic_boxes == 115) {
        HuAudFXPlay(0x2A1);
    }
    if (D_8010CAF8_game_guys_magic_boxes.timer <= 0) {
        D_8010CAF8_game_guys_magic_boxes.timer = 0;
    }
    HuSprTPLvlSet(D_8010CAF8_game_guys_magic_boxes.group, 0, D_8010CAF8_game_guys_magic_boxes.timer);
    if (D_8010CAE0_game_guys_magic_boxes.timer <= 0) {
        D_8010CAE0_game_guys_magic_boxes.timer = 0;
    }
    HuSprTPLvlSet(D_8010CAE0_game_guys_magic_boxes.group, 0, D_8010CAE0_game_guys_magic_boxes.timer);
    if (D_8010C260_game_guys_magic_boxes < 90) {
        for (i = 0; i < 3; i++) {
            func_8010BC00_game_guys_magic_boxes(D_8010CA78_game_guys_magic_boxes[D_8010CB0C_game_guys_magic_boxes].active[i], D_8010CA78_game_guys_magic_boxes[D_8010CB0C_game_guys_magic_boxes].x[i],
                                                D_8010CA78_game_guys_magic_boxes[D_8010CB0C_game_guys_magic_boxes].y[i], D_8010CA78_game_guys_magic_boxes[D_8010CB0C_game_guys_magic_boxes].radius[i]);
            D_8010CA78_game_guys_magic_boxes[D_8010CB0C_game_guys_magic_boxes].active[i] = D_8010CA20_game_guys_magic_boxes[i].active;
            D_8010CA78_game_guys_magic_boxes[D_8010CB0C_game_guys_magic_boxes].x[i] = D_8010CA20_game_guys_magic_boxes[i].x;
            D_8010CA78_game_guys_magic_boxes[D_8010CB0C_game_guys_magic_boxes].y[i] = D_8010CA20_game_guys_magic_boxes[i].y;
            D_8010CA78_game_guys_magic_boxes[D_8010CB0C_game_guys_magic_boxes].radius[i] = D_8010CA20_game_guys_magic_boxes[i].radius;
        }
    }
    if (D_8010C260_game_guys_magic_boxes < 20) {
        for (i = 0; i < 3; i++) {
            func_8010BD9C_game_guys_magic_boxes(D_8010CA20_game_guys_magic_boxes[i].active, D_8010CA20_game_guys_magic_boxes[i].x, D_8010CA20_game_guys_magic_boxes[i].y, D_8010CA20_game_guys_magic_boxes[i].radius, D_8010CA20_game_guys_magic_boxes[i].color);
        }
    } else if (D_8010C260_game_guys_magic_boxes < 81) {
        for (i = 0; i < 3; i++) {
            func_8010BD5C_game_guys_magic_boxes(D_8010CA20_game_guys_magic_boxes[i].active, D_8010CA20_game_guys_magic_boxes[i].x, D_8010CA20_game_guys_magic_boxes[i].y, D_8010CA20_game_guys_magic_boxes[i].color);
        }
    } else {
        func_8010BD9C_game_guys_magic_boxes(D_8010CA20_game_guys_magic_boxes[0].active, D_8010CA20_game_guys_magic_boxes[0].x, D_8010CA20_game_guys_magic_boxes[0].y, D_8010CA20_game_guys_magic_boxes[0].radius, D_8010CA20_game_guys_magic_boxes[0].color);
    }
    D_8010CAF8_game_guys_magic_boxes.sprite->unk_84->unk00->unk00 = D_8010CAF8_game_guys_magic_boxes.unk_04[D_8010CB0C_game_guys_magic_boxes];
    D_8010CAE0_game_guys_magic_boxes.sprite->unk_84->unk00->unk00 = D_8010CAE0_game_guys_magic_boxes.unk_04[D_8010CB0C_game_guys_magic_boxes];
    D_8010CB0C_game_guys_magic_boxes = (s16)(D_8010CB0C_game_guys_magic_boxes + 1) % 3;
    D_8010C260_game_guys_magic_boxes++;
    return 0;
}

s32 func_8010B700_game_guys_magic_boxes(s32 x) {
    s16 i;

    D_8010CAF8_game_guys_magic_boxes.sprite->unk_84->unk00->unk00 = D_8010CAF8_game_guys_magic_boxes.unk_04[0];
    if (D_8010C264_game_guys_magic_boxes++ < 10) {
        D_8010CAF8_game_guys_magic_boxes.timer = 0;
    } else if (D_8010C264_game_guys_magic_boxes < 30) {
        D_8010CAF8_game_guys_magic_boxes.timer = sindf((D_8010C264_game_guys_magic_boxes - 10) * 4.5f) * 128.0f;
        HuSprTPLvlSet(D_8010CAF8_game_guys_magic_boxes.group, 0, D_8010CAF8_game_guys_magic_boxes.timer);
    } else if (D_8010C264_game_guys_magic_boxes >= 40) {
        if (D_8010C264_game_guys_magic_boxes < 90) {
            for (i = 0; i < 5; i++) {
                func_8010BF94_game_guys_magic_boxes(x, -100, x + (D_8010C264_game_guys_magic_boxes - 40) + i, 240);
                func_8010BF94_game_guys_magic_boxes(x, -100, x - (D_8010C264_game_guys_magic_boxes - 40) - i, 240);
            }
            D_8010C264_game_guys_magic_boxes += 4;
        } else {
            return 1;
        }
    }
    return 0;
}

void func_8010B8B4_game_guys_magic_boxes(void) {
    HuSprDispOff(D_8010CAF8_game_guys_magic_boxes.group, 0);
    HuSprDispOff(D_8010CAE0_game_guys_magic_boxes.group, 0);
    D_8010CAF8_game_guys_magic_boxes.sprite->unk_84->unk00->unk00 =
        D_8010CAF8_game_guys_magic_boxes.unk_04[0];
    D_8010CAE0_game_guys_magic_boxes.sprite->unk_84->unk00->unk00 =
        D_8010CAE0_game_guys_magic_boxes.unk_04[0];
}

s16 func_8010B938_game_guys_magic_boxes(s32 dataNum, s32 attr, s32 priority, s32 tpLvl) {
    s16 sprite;
    s16 group;

    sprite = func_8000B838_main(dataNum);
    group = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group, 0, sprite, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, attr | 0x1000);
    HuSprPriSet(group, 0, priority);
    HuSprPosSet(group, 0, 160, 120);
    HuSprTPLvlSet(group, 0, tpLvl);
    return group;
}

void func_8010BA0C_game_guys_magic_boxes(void) {
    s16 *pal;

    D_8010CAF8_game_guys_magic_boxes.group = func_8010B938_game_guys_magic_boxes(0x650005, 0, 10, 128);
    D_8010CAF8_game_guys_magic_boxes.sprite = HuSprGet(D_8010CAF8_game_guys_magic_boxes.group, 0);
    D_8010CAF8_game_guys_magic_boxes.unk_04[0] = D_8010CAF8_game_guys_magic_boxes.sprite->unk_84->unk00->unk00;
    pal = D_8010CAF8_game_guys_magic_boxes.sprite->unk_84->unk0C;
    D_8010CAF8_game_guys_magic_boxes.unk_04[1] = HuMemAllocTag(0x9600, 0x7918);
    D_8010CAF8_game_guys_magic_boxes.unk_04[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 0x0001;
    pal[1] = 0x003F;
    pal[2] = 0x07C1;
    pal[3] = 0x07FF;
    pal[4] = 0xF801;
    pal[5] = 0xF83F;
    pal[6] = 0xFFC1;
    pal[7] = 0xFFFE;

    D_8010CAE0_game_guys_magic_boxes.group = func_8010B938_game_guys_magic_boxes(0x650005, 0, 10, 256);
    D_8010CAE0_game_guys_magic_boxes.sprite = HuSprGet(D_8010CAE0_game_guys_magic_boxes.group, 0);
    D_8010CAE0_game_guys_magic_boxes.unk_04[0] = D_8010CAE0_game_guys_magic_boxes.sprite->unk_84->unk00->unk00;
    pal = D_8010CAE0_game_guys_magic_boxes.sprite->unk_84->unk0C;
    D_8010CAE0_game_guys_magic_boxes.unk_04[1] = HuMemAllocTag(0x9600, 0x7918);
    D_8010CAE0_game_guys_magic_boxes.unk_04[2] = HuMemAllocTag(0x9600, 0x7918);
    pal[0] = 0x0001;
    pal[1] = 0x0000;
}

void func_8010BB70_game_guys_magic_boxes(void) {
    s32 i, j;
    u8 *ptr;

    for (i = 0; i < 3; i++) {
        ptr = D_8010CAF8_game_guys_magic_boxes.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        ptr = D_8010CAE0_game_guys_magic_boxes.unk_04[i];
        for (j = 0; j <= 0x95FF; j++) {
            *ptr++ = 0;
        }
    }
}

void func_8010BC00_game_guys_magic_boxes(s16 active, s16 x, s16 y, s16 radius) {
    s32 px;
    s32 py;
    u8 *pixels;
    u8 *mask;

    if ((active == 0) | (radius < 1)) {
        return;
    }
    pixels = (u8 *)D_8010CAF8_game_guys_magic_boxes.unk_04[D_8010CB0C_game_guys_magic_boxes] + (x + radius) / 2 + (y - (radius + 1)) * 160 + 1;
    mask = (u8 *)D_8010CAE0_game_guys_magic_boxes.unk_04[D_8010CB0C_game_guys_magic_boxes] + (x + radius) / 2 + (y - (radius + 1)) * 160 + 1;
    for (py = y - radius; py < y + radius; py++) {
        pixels += 159 - radius;
        mask += 159 - radius;
        for (px = x - radius; px < x + (radius + 1); px += 2) {
            if (px >= 0 && px < 320 && py >= 0 && py < 240) {
                *pixels = 0;
                *mask = 0;
            }
            pixels++;
            mask++;
        }
    }
}

void func_8010BD5C_game_guys_magic_boxes(s16 active, s16 x, s16 y, s16 color) {
    func_8010BD9C_game_guys_magic_boxes(active, x, y, 45, color);
}

void func_8010BD9C_game_guys_magic_boxes(s16 active, s16 x, s16 y, s16 radius, s16 color) {
    s32 radiusSq;
    s32 distXSq;
    s32 distYSq;
    s32 px;
    s32 py;
    u8 *pixels;
    u8 *mask;

    radiusSq = radius * radius;
    if ((active == 0) | (radius < 1)) {
        return;
    }
    for (py = y - radius; py < y + radius; py++) {
        pixels = (u8 *)D_8010CAF8_game_guys_magic_boxes.unk_04[D_8010CB0C_game_guys_magic_boxes] + (x - radius) / 2 + py * 160;
        mask = (u8 *)D_8010CAE0_game_guys_magic_boxes.unk_04[D_8010CB0C_game_guys_magic_boxes] + (x - radius) / 2 + py * 160;
        distYSq = (py - y) * (py - y);
        for (px = x - radius; px < x + radius; px++) {
            distXSq = (px - x) * (px - x);
            if (px >= 0 && px < 320 && py >= 0 && py < 240) {
                if (distXSq + distYSq < radiusSq) {
                    if (px & 1) {
                        *pixels |= color;
                        *mask |= 1;
                    } else {
                        *pixels |= color << 4;
                        *mask |= 0x10;
                    }
                }
            }
            if (px & 1) {
                pixels++;
                mask++;
            }
        }
    }
}

void func_8010BF94_game_guys_magic_boxes(s16 x0, s16 y0, s16 x1, s16 y1) {
    s16 dx;
    s16 dy;
    s16 err;
    u8 *pixels;

    dx = (x0 > x1) ? x0 - x1 : x1 - x0;
    dy = (y0 > y1) ? y0 - y1 : y1 - y0;
    err = dy / 2;
    if (x0 <= x1) {
        for (; y0 <= y1; y0++) {
            err -= dx;
            if (err < 0) {
                err += dy;
                x0++;
            }
            if (x0 >= 0 && x0 < 320 && y0 >= 0 && y0 < 240) {
                pixels = (u8 *)D_8010CAF8_game_guys_magic_boxes.unk_04[D_8010CB0C_game_guys_magic_boxes] + x0 / 2 + y0 * 160;
                if (x0 & 1) {
                    *pixels |= 7;
                } else {
                    *pixels |= 0x70;
                }
            }
        }
    } else {
        for (; y0 <= y1; y0++) {
            err -= dx;
            if (err < 0) {
                err += dy;
                x0--;
            }
            if (x0 >= 0 && x0 < 320 && y0 >= 0 && y0 < 240) {
                pixels = (u8 *)D_8010CAF8_game_guys_magic_boxes.unk_04[D_8010CB0C_game_guys_magic_boxes] + x0 / 2 + y0 * 160;
                if (x0 & 1) {
                    *pixels |= 7;
                } else {
                    *pixels |= 0x70;
                }
            }
        }
    }
}
